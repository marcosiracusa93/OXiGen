#include <vector>
#include <iostream>
#include <llvm/IR/Dominators.h>

#include "OxigenVectorizationPass.h"

using namespace oxigen;

OxigenVectorizationPass* oxigen::createOxigenVectorizationPass(int vectorizationFactor){
    return new OxigenVectorizationPass(vectorizationFactor);
}

void OxigenVectorizationPass::initializeLoopMetadata() {

    for (Loop *l : *LI) {
        BasicBlock *header = l->getHeader();
        LoopMetadata metadata;

        if (BranchInst *br = dyn_cast<BranchInst>(header->getTerminator())) {
            if (ICmpInst *cond = dyn_cast<ICmpInst>(br->getCondition())) {

                metadata.exit_condition = cond;

                if (ConstantInt *c = dyn_cast<ConstantInt>(cond->getOperand(1))) {

                    uint64_t loop_max_iters = c->getSExtValue();
                    metadata.iterations = loop_max_iters;

                } else {
                    llvm::errs() << "ERROR: non-constant iterations for loop, terminating\n";
                    cond->getOperand(1)->dump();
                    exit(EXIT_FAILURE);
                }
                if (PHINode *phi = dyn_cast<PHINode>(cond->getOperand(0))) {
                    metadata.iteration_phi = phi;

                    if (ConstantInt *offset = dyn_cast<ConstantInt>(phi->getIncomingValue(0))) {
                        metadata.iterations_offset = offset->getSExtValue();
                    } else {
                        llvm::errs() << "ERROR: non constant offset in phi node for loop,terminating\n";
                        phi->getIncomingValue(0)->dump();
                        exit(EXIT_FAILURE);
                    }
                } else {
                    llvm::errs() << "ERROR: non phi-based condition, terminating\n";
                    cond->getOperand(0)->dump();
                    exit(EXIT_FAILURE);
                }
            } else {
                llvm::errs() << "ERROR: could not process exit condition, terminating\n";
                cond->dump();
                exit(EXIT_FAILURE);
            }
        }
        loopsMap.insert(std::pair<Loop *, LoopMetadata>(l, metadata));
    }
}

void OxigenVectorizationPass::adjustVectorAccesses() {

    std::vector<std::pair<GetElementPtrInst*,Loop*>> outerDimAccesses;

    for(BasicBlock &BB : *F){
        for(Instruction &instr : BB){
            if(GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(&instr)){
                for(auto it = gep->idx_begin(); it != gep->idx_end(); ++it){
                    if(SExtInst* sext = dyn_cast<SExtInst>(*it)) {
                        if (PHINode *phi = dyn_cast<PHINode>(sext->getOperand(0))) {
                            for (auto loop : loopsMap) {
                                if (loop.second.iteration_phi == phi) {
                                    outerDimAccesses.push_back(std::make_pair(gep, loop.first));
                                }
                            }
                        }else if(SubOperator* sub = dyn_cast<SubOperator>(sext->getOperand(0))){
                            for(Value* op : sub->operands()){
                                if (PHINode *phi = dyn_cast<PHINode>(op)) {
                                    for (auto loop : loopsMap) {
                                        if (loop.second.iteration_phi == phi) {
                                            outerDimAccesses.push_back(std::make_pair(gep, loop.first));
                                        }
                                    }
                                }
                            }
                        }else if(AddOperator* add = dyn_cast<AddOperator>(sext->getOperand(0))){
                            for(Value* op : add->operands()){
                                if (PHINode *phi = dyn_cast<PHINode>(op)) {
                                    for (auto loop : loopsMap) {
                                        if (loop.second.iteration_phi == phi) {
                                            outerDimAccesses.push_back(std::make_pair(gep, loop.first));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int ID = 0;

    for(auto accessPair : outerDimAccesses){

        IRBuilder<> builder = IRBuilder<>(*context);

        GetElementPtrInst* outerGep = accessPair.first;
        PHINode* vectoriaztionLoopAccessPhi = loopsMap[accessPair.second].vectorization_phi;

        builder.SetInsertPoint(outerGep->getNextNode());

        Value* sext = builder.CreateSExt(vectoriaztionLoopAccessPhi,builder.getInt64Ty(),"v_idx_ext_"+std::to_string(ID));

        Type* gepType = ((PointerType*)outerGep->getType())->getPointerElementType();
        std::vector<Value*> gepIdxVector;

        gepIdxVector.push_back(builder.getInt64(0));
        gepIdxVector.push_back(sext);

        Value* vectorizationGep = builder.CreateInBoundsGEP(gepType,outerGep,gepIdxVector,"v_access_"+std::to_string(ID));

        outerGep->replaceAllUsesWith(vectorizationGep);

        if(GetElementPtrInst* v_gep = dyn_cast<GetElementPtrInst>(vectorizationGep)){
            v_gep->getOperandUse(0).set(outerGep);
        }
        ID++;
    }
}

void OxigenVectorizationPass::fixGEPUsersTypes() {

    IRBuilder<> builder = IRBuilder<>(*context);

    std::vector<std::pair<GetElementPtrInst*,GetElementPtrInst*>> gepPairs;

    for(Argument &arg : F->args()){
        for(User* usr : arg.users()){
            if(GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(usr)){
                if(gep->getPointerOperand() == &arg){
                    Type* pointedType = ((PointerType*)arg.getType())->getPointerElementType();
                    std::vector<Value*> indexes;
                    indexes.insert(indexes.begin(),gep->idx_begin(),gep->idx_end());

                    Value* retVal = builder.CreateInBoundsGEP(pointedType,gep->getPointerOperand(),indexes);

                    if(GetElementPtrInst* newGep = dyn_cast<GetElementPtrInst>(retVal)){
                        gepPairs.push_back(std::pair<GetElementPtrInst*,GetElementPtrInst*>(gep,newGep));
                    }else{
                        llvm::errs() << "ERROR: unexpected type returned from builder";
                    }
                }else{
                    llvm::errs() << "ERROR: unsupported gep use: \n";
                    gep->dump();
                }
            }else{
                llvm::errs() << "ERROR: unsupported user type: \n";
                usr->dump();
            }
        }
    }

    for(BasicBlock &BB : *F){
        for(Instruction &instr : BB){
            if(AllocaInst* alloca = dyn_cast<AllocaInst>(&instr)){
                for(User* user : alloca->users()){
                    if(GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(user)){
                        if(gep->getPointerOperand() == alloca){
                            Type* pointedType = alloca->getType()->getPointerElementType();
                            std::vector<Value*> indexes;
                            indexes.insert(indexes.begin(),gep->idx_begin(),gep->idx_end());

                            Value* retVal = builder.CreateInBoundsGEP(pointedType,gep->getPointerOperand(),indexes);

                            if(GetElementPtrInst* newGep = dyn_cast<GetElementPtrInst>(retVal)){
                                gepPairs.push_back(std::pair<GetElementPtrInst*,GetElementPtrInst*>(gep,newGep));
                            }else{
                                llvm::errs() << "ERROR: unexpected type returned from builder";
                            }
                        }
                    }
                }
            }
        }
    }

    for(auto pair : gepPairs){
        ReplaceInstWithInst(pair.first,pair.second);
    }
}

void OxigenVectorizationPass::addVectorizationLoops() {

    IRBuilder<> builder = IRBuilder<>(*context);

    int ID = 0;

    for(Loop* outerLoop : *LI){

        //create preheader for vectorized loop
        SplitEdge(outerLoop->getHeader(),outerLoop->getHeader()->getTerminator()->getSuccessor(0));

        //create header for vectorized loop
        BasicBlock* vectPreHeader = outerLoop->getHeader()->getTerminator()->getSuccessor(0);
        SplitEdge(vectPreHeader,vectPreHeader->getTerminator()->getSuccessor(0));

        //create latch for vectorized loop
        BasicBlock* latchPred = outerLoop->getLoopLatch()->getUniquePredecessor();
        SplitEdge(latchPred,outerLoop->getLoopLatch());

        //crete exit block for the vectorized loop
        latchPred = latchPred->getTerminator()->getSuccessor(0);
        BasicBlock* loopLatch = latchPred->getTerminator()->getSuccessor(0);

        BasicBlock* res = SplitEdge(latchPred,loopLatch);

        BasicBlock* vectLatch = latchPred;
        BasicBlock* vectExit = loopLatch;
        loopLatch = res;

        BasicBlock* vectLoopHeader = vectPreHeader->getTerminator()->getSuccessor(0);
        BasicBlock* firstBody = vectLoopHeader->getTerminator()->getSuccessor(0);

        //insert instructions into the vectorized loop header
        builder.SetInsertPoint(vectLoopHeader);

        PHINode* vectorPhi = builder.CreatePHI(Type::getInt32Ty(*context),2,"vectPhi_"+std::to_string(ID));
        vectorPhi->addIncoming(builder.getInt32(0),vectPreHeader);
        vectorPhi->addIncoming(builder.getInt32(1),vectLatch);
        loopsMap[outerLoop].vectorization_phi = vectorPhi;

        Value* icmp = builder.CreateICmpSLT(vectorPhi,builder.getInt32(vectorizationFactor),"v_icmp_"+std::to_string(ID));
        builder.CreateCondBr(icmp,firstBody,vectExit);

        Instruction* i = &(*(vectLoopHeader->begin()));
        if(dyn_cast<BranchInst>(i))
            i->eraseFromParent();

        //create instructions for the vector loop latch
        builder.SetInsertPoint(vectLatch);
        Value* add = builder.CreateAdd(vectorPhi,builder.getInt32(1),"v_step"+std::to_string(ID),false,true);
        builder.CreateBr(vectLoopHeader);

        i = &(*(vectLatch->begin()));
        if(dyn_cast<BranchInst>(i))
            i->eraseFromParent();

        vectorPhi->setIncomingValue(1,add);

        ID++;
    }
}

void OxigenVectorizationPass::adaptOuterLoopsTripCount() {

    for(Loop* l : *LI){

        LoopMetadata loopMetadata = loopsMap[l];

        uint64_t iterations = loopMetadata.iterations;
        uint64_t offset = loopMetadata.iterations_offset;
        CmpInst* cond = loopMetadata.exit_condition;

        uint64_t vectorized_offset = offset / vectorizationFactor;
        uint64_t vectorized_max_iters =  iterations/ vectorizationFactor;

        Constant* intVal = ConstantInt::get(cond->getOperand(1)->getType(),vectorized_max_iters);
        ReplaceInstWithInst(cond,
                            ICmpInst::Create(Instruction::OtherOpsBegin,
                                             cond->getPredicate(),
                                             cond->getOperand(0),
                                             intVal));

        PHINode* phi = loopMetadata.iteration_phi;
        phi->setIncomingValue(0,ConstantInt::get(phi->getIncomingValue(0)->getType(),vectorized_offset));
    }

    IRBuilder<> builder = IRBuilder<>(*context);

    for(BasicBlock &BB : *F){
        for(Instruction &instr : BB){
            if(BinaryOperator* b_op = dyn_cast<BinaryOperator>(&instr)){
                ConstantInt* int_op;
                PHINode* phi_op;
                int int_op_ops;

                for(int i = 0; i < 2; i++){
                    Value* op = b_op->getOperand(i);
                    if(ConstantInt* c = dyn_cast<ConstantInt>(op)){
                        int_op = c;
                        int_op_ops = i;
                    }else if(PHINode* phi = dyn_cast<PHINode>(op)){
                        phi_op = phi;
                    }
                }

                if(int_op != nullptr && phi_op != nullptr){
                    for(auto pair : loopsMap){
                        if(pair.second.iteration_phi == phi_op &&
                                ((ConstantInt*)phi_op->getIncomingValue(0))->getSExtValue() != 0 &&
                                ((ConstantInt*)phi_op->getIncomingValue(0))->getSExtValue() == int_op->getSExtValue()/vectorizationFactor){
                            b_op->setOperand(int_op_ops,builder.getInt32(int_op->getSExtValue()/vectorizationFactor));
                        }
                    }
                }
            }
        }
    }
}

bool OxigenVectorizationPass::runOnFunction(Function &F) {

    llvm::errs() << "OxigenVectorizationPass(): executing\n";

    this->F = &F;
    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    context = &(F.getParent()->getContext());

    initializeLoopMetadata();
    adaptOuterLoopsTripCount();
    addVectorizationLoops();
    fixGEPUsersTypes();
    adjustVectorAccesses();

    F.dump();
    return true;
}

void OxigenVectorizationPass::getAnalysisUsage(AnalysisUsage &AU) const {

    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}

