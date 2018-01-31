#include <vector>
#include <iostream>
#include <llvm/IR/Dominators.h>

#include "OxigenVectorizationPass.h"

using namespace oxigen;

OxigenVectorizationPass* oxigen::createOxigenVectorizationPass(int vectorizationFactor){
    return new OxigenVectorizationPass(vectorizationFactor);
}

void OxigenVectorizationPass::initializeLoopMetadata() {

    for(Loop* l : *LI){
        BasicBlock* header = l->getHeader();
        LoopMetadata metadata;

        if(BranchInst* br = dyn_cast<BranchInst>(header->getTerminator())){
            if(ICmpInst* cond = dyn_cast<ICmpInst>(br->getCondition())) {

                metadata.exit_condition = cond;

                if (ConstantInt *c = dyn_cast<ConstantInt>(cond->getOperand(1))) {

                    uint64_t loop_max_iters = c->getSExtValue();
                    metadata.iterations = loop_max_iters;

                }else{
                    llvm::errs() << "ERROR: non-constant iterations for loop, terminating\n";
                    cond->getOperand(1)->dump();
                    exit(EXIT_FAILURE);
                }
                if(PHINode* phi = dyn_cast<PHINode>(cond->getOperand(0))){
                    metadata.iteration_phi = phi;

                    if(ConstantInt* offset = dyn_cast<ConstantInt>(phi->getIncomingValue(0))){
                        metadata.iterations_offset = offset->getSExtValue();
                    }else{
                        llvm::errs() << "ERROR: non constant offset in phi node for loop,terminating\n";
                        phi->getIncomingValue(0)->dump();
                        exit(EXIT_FAILURE);
                    }
                }else{
                    llvm::errs() << "ERROR: non phi-based condition, terminating\n";
                    cond->getOperand(0)->dump();
                    exit(EXIT_FAILURE);
                }
            }else{
                llvm::errs() << "ERROR: could not process exit condition, terminating\n";
                cond->dump();
                exit(EXIT_FAILURE);
            }
        }

        loopsMap.insert(std::pair<Loop*,LoopMetadata>(l,metadata));
    }
}

void OxigenVectorizationPass::addVectorizationLoops() {

    IRBuilder<> builder = IRBuilder<>(*context);

    int ID = 0;

    for(Loop* outerLoop : *LI){

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

    this->F->dump();

    return true;
}

void OxigenVectorizationPass::getAnalysisUsage(AnalysisUsage &AU) const {

    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}

