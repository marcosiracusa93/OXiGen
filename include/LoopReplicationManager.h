
#ifndef OXIGEN_LOOPREPLICATIONMANAGER_H_H
#define OXIGEN_LOOPREPLICATIONMANAGER_H_H

#include "DFGConstructor.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen {

    enum LoopType { Neutral = 0, Expansion = 1,Accumul = 2 };

    class LoopGraphNode{

    private:

        int tilingFactor;
        int tilingDelay;

        DFGLoopNode* loopNode;
        std::vector<DFGNode*> nestedVectorStores;
        std::vector<DFGNode*> nestedVectorReads;
        LoopType typeID;

        std::vector<LoopGraphNode*> precedingLoops;
        std::vector<LoopGraphNode*> succedingLoops;

    public:

        LoopGraphNode(DFGLoopNode* loopNode,std::vector<DFGNode*> nestedVectorStores){
            this->loopNode = loopNode;
            this->nestedVectorStores = nestedVectorStores;
            this->tilingFactor = 0;
            this->tilingDelay = 0;
        }

        LoopType getLoopType(){ return typeID; }
        DFGLoopNode* getLoopNode(){ return loopNode; }
        std::vector<LoopGraphNode*> getPredecessors(){ return precedingLoops; }
        std::vector<LoopGraphNode*> getSuccessors(){ return succedingLoops; }
        std::vector<DFGNode*> getNestedVectorStores(){ return nestedVectorStores; }
        std::vector<DFGNode*> getNestedVectorReads(){ return nestedVectorReads; }
        int getTilingFactor(){ return tilingFactor; }
        int getTilingDelay(){ return tilingDelay; }

        int getReplication(){

            int iters = loopNode->getTripCount();
            return iters % tilingFactor ? (iters / tilingFactor + 1) : iters / tilingFactor;
        }

        void insertPredecessor(LoopGraphNode* node){ precedingLoops.push_back(node); }
        void insertSuccessor(LoopGraphNode* node){ succedingLoops.push_back(node); }
        void setLoopType(LoopType type){ this->typeID = type; }
        void insertNestedVectorRead(DFGNode* node){ nestedVectorReads.push_back(node); }
        void setTilingDelay(int delay){ this->tilingDelay = delay; }
        void setTilingFactor(int T){

            tilingFactor = T;

            if(loopNode->getTripCount() % tilingFactor){
                llvm::errs() << "INFO: replication will be rounded up\n";
            }

            for(auto succ : succedingLoops){
                if(succ->getTilingFactor() && succ->getTilingFactor() != T) {
                    llvm::errs() << "WARNING: ovrewritten tiling factor for ";
                    succ->getLoopNode()->getValue()->dump();
                }
                succ->setTilingFactor(T);
            }
        }

        void printLoopGraphNode();
    };

    class LoopDependencyGraph{

    private:

        std::vector<LoopGraphNode*> beginLoopNodes;
        std::vector<LoopGraphNode*> orderedLoopNodes;
        int graphLoopDepth;

    public:

        LoopDependencyGraph(DFG* dfg,llvm::Function*);

        std::vector<LoopGraphNode*> getBeginLoopNodes(){ return beginLoopNodes; }
        int getGraphLoopDepth(){ return graphLoopDepth; }
        int getFinalDelay();

        LoopGraphNode* getNodeForLoop(DFGLoopNode* loopNode);

        void printDependencyGraph();
        void setTilingDelay();

    private:

        std::vector<DFGNode*> getDependentLoopNodes(DFGNode* parentNode);

        void connectAccumulDependencies();
        void printGraphNode(LoopGraphNode* gn);

        LoopGraphNode* getNodeForLoop(DFGLoopNode* loopNode,LoopGraphNode* node);

    };

    class LoopReplicationManager : public ProcessingComponent{

    private:

        llvm::Function* F;

    public:

        LoopReplicationManager(llvm::Function* F){
            this->F = F;
        }

        void acceptExecutor(ProcessingScheduler* scheduler){
            scheduler->execute(this);
        }

        LoopDependencyGraph* analyzeDFGLoops(DFG* dfg);

    };

    std::vector<DFGNode*> getExpansionLoopNestedVectorWrites(DFGLoopNode* loopNode,llvm::Function* F);

    bool isAccumulationLoop(DFGLoopNode* loopNode,llvm::Function* F);

    bool isExpansionLoop(DFGLoopNode* loopNode,llvm::Function* F);
}


#endif //OXIGEN_LOOPREPLICATIONMANAGER_H_H
