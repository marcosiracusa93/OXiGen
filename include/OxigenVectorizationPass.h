
#ifndef OXIGEN_OXIGENVECTORIZATIONPASS_H
#define OXIGEN_OXIGENVECTORIZATIONPASS_H

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"
#include <llvm/Transforms/Utils/CodeExtractor.h>
#include <llvm/IR/Dominators.h>

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"

using namespace llvm;

namespace oxigen {

    struct LoopMetadata{

        PHINode* iteration_phi;
        PHINode* vectorization_phi;
        CmpInst* exit_condition;
        uint64_t iterations;
        uint64_t iterations_offset;

    };

    typedef std::map<Loop*,LoopMetadata> LoopsMap;

    class OxigenVectorizationPass : public FunctionPass {

    private:

        char ID = 0;
        int vectorizationFactor;

        Function* F;
        LoopInfo* LI;
        ScalarEvolution* SE;

        LoopsMap loopsMap;
        LLVMContext* context;

    public:

        OxigenVectorizationPass(int v) : FunctionPass(ID) { vectorizationFactor = v; }

        bool runOnFunction(Function &F) override;

        void getAnalysisUsage(AnalysisUsage &AU) const override;

    private:

        void initializeLoopMetadata();

        void adaptOuterLoopsTripCount();

        void addVectorizationLoops();

        void fixGEPUsersTypes();

        void adjustVectorAccesses();

    };

    OxigenVectorizationPass* createOxigenVectorizationPass(int vectorizationFactor);
}


#endif //OXIGEN_OXIGENVECTORIZATIONPASS_H
