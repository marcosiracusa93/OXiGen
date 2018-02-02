
#ifndef OXIGEN_OXYGENGENVECTORIZEDPASS_H_H
#define OXIGEN_OXYGENGENVECTORIZEDPASS_H_H

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

using namespace llvm;

namespace oxigen{

    typedef std::map<Loop*,PHINode*> LoopIterationVariablesMap;

    class OxigenGenVectorizedPass : public FunctionPass{

        char ID = 0;
        int vectorizationFactor;

        Function *F;
        Function *newF;
        LoopInfo *LI;
        ScalarEvolution* SE;
        LoopIterationVariablesMap* loopIterationVariablesMap;
        std::vector<Argument*> streams;

    public:

        OxigenGenVectorizedPass(int vectorizationFactor) : FunctionPass(ID){
            this->vectorizationFactor = vectorizationFactor;
        }

        bool runOnFunction(Function &F) override;

        void getAnalysisUsage(AnalysisUsage &AU) const override;

    private:

        void setUsesType(Value* usedVal,Type* newType);

        void getStreamArguments();

        void changeTypeForLocalStreams();
    };

    OxigenGenVectorizedPass* createOxigenGenVectorizedPass(int vectorizationFactor);
}

#endif //OXIGEN_OXYGENGENVECTORIZEDPASS_H_H
