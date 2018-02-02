#include <vector>
#include <iostream>
#include <llvm/IR/Dominators.h>

#include "OxigenGenVectorizedPass.h"

using namespace oxigen;

OxigenGenVectorizedPass* oxigen::createOxigenGenVectorizedPass(int vectorizationFactor) {
    return new OxigenGenVectorizedPass(vectorizationFactor);
}

void OxigenGenVectorizedPass::setUsesType(Value *usedVal, Type *newType) {

    for(User* user: usedVal->users()){
        for(Value* op : user->operands()){
            if(op == usedVal){
                if(Instruction* instr = dyn_cast<Instruction>(user)){

                }
            }
        }
    }
}

void OxigenGenVectorizedPass::getStreamArguments() {

    loopIterationVariablesMap = new LoopIterationVariablesMap();

    for(Argument &arg : F->args()){
        llvm::errs() << "argument: ";
        arg.dump();

        for(User* usr : arg.users()){
            if(GetElementPtrInst* gepUsr = dyn_cast<GetElementPtrInst>(usr)){
                for(auto it = gepUsr->idx_begin(); it != gepUsr->idx_end(); ++it){
                    if(SExtInst* sext = dyn_cast<SExtInst>(*it)){
                        if(PHINode* phi = dyn_cast<PHINode>(sext->getOperand(0))){

                            for(Loop* loop : *LI){
                                llvm::Instruction * terminator = loop->getHeader()->getTerminator();
                                if(BranchInst* br = dyn_cast<BranchInst>(terminator)){
                                    if(ICmpInst* icmp = dyn_cast<ICmpInst>(br->getCondition())){
                                        if(phi == icmp->getOperand(0)){
                                            loopIterationVariablesMap->insert(std::pair<Loop*,PHINode*>(loop,phi));
                                            if(loop->getLoopDepth() == 1)
                                                streams.push_back(&arg);
                                                llvm::errs() << "INFO: stream found: ";
                                                arg.dump();
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
}

void OxigenGenVectorizedPass::changeTypeForLocalStreams() {

    IRBuilder<> builder = IRBuilder<>(F->getParent()->getContext());
    std::vector<std::pair<AllocaInst*,AllocaInst*>> allocaPairs;

    for(BasicBlock &BB : *newF){
        for(Instruction &instr : BB){
            if(AllocaInst* alloca = dyn_cast<AllocaInst>(&instr)) {
                if (alloca->getAllocatedType()->isArrayTy()) {
                    ArrayType *arrayType = (ArrayType *) (alloca->getAllocatedType());
                    for (Loop *l : *LI) {
                        const SCEV *tripCount = SE->getBackedgeTakenCount(l);
                        if (tripCount->getSCEVType() == SCEVTypes::scConstant) {
                            SCEVConstant* c = (SCEVConstant*)tripCount;
                            int tripCountAsInt = c->getValue()->getSExtValue();
                            int elements = arrayType->getNumElements();
                            if (tripCountAsInt == elements){
                                Type* vectorizedElement =
                                        ArrayType::get(arrayType->getElementType(),vectorizationFactor);
                                Type* finalType =
                                        ArrayType::get(vectorizedElement,arrayType->getNumElements()/vectorizationFactor);
                                AllocaInst* newAlloca = builder.CreateAlloca(finalType, nullptr,"");
                                newAlloca->setAlignment(16);
                                allocaPairs.push_back(std::pair<AllocaInst*,AllocaInst*>(alloca,newAlloca));
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for(auto pair : allocaPairs){
        ReplaceInstWithInst(pair.first,pair.second);
    }
}

bool OxigenGenVectorizedPass::runOnFunction(Function &F){

    llvm::errs() << "OxigenGenVectorizedPass(): in vectorization pass\n";

    this->F = &F;

    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

    //identify streams
    getStreamArguments();

    Type* params[F.getArgumentList().size()];

    //initialize new function signature
    int arrayIdx = 0;
    for(Argument &arg : F.args()){
        if(std::find(streams.begin(),streams.end(),&arg) != streams.end()){
            Type* argType = arg.getType();

            if(argType->isPointerTy()){
                PointerType* ptrTy = (PointerType*)argType;
                Type* scalarType = ptrTy->getPointerElementType();
                Type* newType = ArrayType::get(scalarType,vectorizationFactor);
                PointerType* pointerToNewType = PointerType::get(newType,ptrTy->getAddressSpace());
                params[arrayIdx] = pointerToNewType;
            }
        }else{
            params[arrayIdx] = arg.getType();
        }
        arrayIdx++;
    }

    ArrayRef<Type*> paramsArray = ArrayRef<Type*>(params,F.getArgumentList().size());
    FunctionType* functionType = FunctionType::get(F.getReturnType(),paramsArray, false);
    Twine new_name = "vectorized_" + F.getName();

    newF = Function::Create(functionType,F.getLinkage(),new_name,F.getParent());

    //clone old function into the new one

    SmallVector<ReturnInst*,1> returns;

    for(auto it = F.begin(); it != F.end(); ++it){
        for(auto i = it->begin(); i != it->end(); ++i){
            if(ReturnInst* instr = dyn_cast<ReturnInst>(i)){
                returns.push_back(instr);
            }
        }
    }

    ValueToValueMapTy valueMap;
    CloneFunctionInto(newF,&F,valueMap,true,returns,"",0);

    //change type for local streams
    changeTypeForLocalStreams();

    for(Argument &arg : F.args())
        for(Argument &arg_2 : newF->args())
            if(arg.getArgNo() == arg_2.getArgNo())
                arg.replaceAllUsesWith(&arg_2);

    F.getParent()->getOrInsertFunction(newF->getName(),newF->getFunctionType());

    return true;
}

void OxigenGenVectorizedPass::getAnalysisUsage(AnalysisUsage &AU) const {

    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}

