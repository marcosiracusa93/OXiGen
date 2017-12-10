//
// Created by user on 11/30/17.
//

#ifndef OXIGEN_SUBLOOPHANDLER_H
#define OXIGEN_SUBLOOPHANDLER_H

#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"
#include "DFGConstructor.h"

namespace oxigen{

    typedef std::map<llvm::Loop*,DFGLoopNode*> LoopNodesMap;

    /**
     * @class SubloopHandler
     * @author
     * @date 26/07/17
     * @file DFGConstructor.h
     * @brief
     */
    class SubloopHandler : public ProcessingComponent {

    public:

        DFG *extractSubloops(llvm::Function* F,llvm::ScalarEvolution *SE, llvm::LoopInfo *LI, DFG *graph);

        SubloopHandler(llvm::Function* F){
            loopNodesMap = LoopNodesMap();
            this->F = F;
        }

        void acceptExecutor(ProcessingScheduler *scheduler) {
            scheduler->execute(this);
        }

    private:

        LoopNodesMap loopNodesMap;
        llvm::Function* F;

        int getNodeLoopDepth(DFGNode* node,llvm::LoopInfo* LI,llvm::Function* F);

        int calculateMaxNestingDepth(DFGNode* node,llvm::LoopInfo* LI,llvm::Function* F,int maxDepth);

        llvm::Loop *getNodeLoop(DFGNode *node, llvm::LoopInfo *LI, llvm::Function *F);

        int getMaxNestingDepth(DFG *dfg, llvm::LoopInfo *LI, llvm::Function *F);

        void reduceLoopsToNodes(DFG *dfg, llvm::LoopInfo *LI, llvm::Function *F, llvm::ScalarEvolution* SE, int nestingDepth);

        void insertIntoLoopNode(DFGNode *node, llvm::LoopInfo *LI, llvm::Function *F,llvm::ScalarEvolution* SE,
                                int nestingDepth,DFG* dfg);

        bool isIndipendent(DFGNode *node, llvm::Loop *loop);

        void promoteIfIndipendentNode(DFGNode* node,llvm::Loop* loop);

        int getBackedgeTakenCount(llvm::Loop* nodeLoop,llvm::ScalarEvolution* SE);
    };

}
#endif //OXIGEN_SUBLOOPHANDLER_H
