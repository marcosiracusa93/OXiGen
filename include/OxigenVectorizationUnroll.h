
#ifndef OXIGEN_OXIGENVECTORIZATIONUNROLL_H
#define OXIGEN_OXIGENVECTORIZATIONUNROLL_H

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"
#include <llvm/IR/Dominators.h>

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Transforms/Utils/UnrollLoop.h"

#include "llvm/Transforms/Scalar/LoopUnrollPass.h"
#include "llvm/Analysis/OptimizationDiagnosticInfo.h"

using namespace llvm;

namespace oxigen {

    class OxigenVectorizationUnroll : public FunctionPass {

    private:

        char ID = 0;

        Function *F;
        LoopInfo *LI;
        ScalarEvolution *SE;

        LLVMContext *context;

    public:

        OxigenVectorizationUnroll() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override;

        void getAnalysisUsage(AnalysisUsage &AU) const override;
    };

    OxigenVectorizationUnroll* createOxigenVectorizationUnroll();
}

#endif //OXIGEN_OXIGENVECTORIZATIONUNROLL_H
