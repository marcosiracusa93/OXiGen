
#include "DFGStreamsOverlapHandler.h"

using namespace oxigen;

std::string defaultTickCounterName = "def_counter";

void DFGStreamsOverlapHandler::computeFallbackWrites(DFG* dfg){

    if(dfg != nullptr){
        llvm::errs() << "Adding condition nodes to DFG with base ";
        dfg->getEndNode()->getValue()->dump();

        dfg->resetFlags(dfg->getEndNode());

        llvm::errs() << "INFO: inserting forward mux nodes...\n";
        insertForwardMuxNodes(dfg->getEndNode());

        DFGNode* n = dfg->getEndNode()->getPredecessors().at(0)->getPredecessors().at(0);

        TickBasedCondition* cond  = new TickBasedConstantCondition("k",0,0);
        DFGMuxNode* muxNode = new DFGMuxNode(n,n,*cond);

        llvm::errs() << "\nNEW MUX NODE\n";
        muxNode->getValue()->dump();
    }else{
        llvm::errs() << "ERROR: null pointer passed as DFG to DFGStreamsOverlapHandler\n";
    }

}

DFGNode* DFGStreamsOverlapHandler::getFallbackPredecessor(DFGNode* n){


}

void DFGStreamsOverlapHandler::insertForwardMuxNodes(DFGNode *startingNode) {

    llvm::errs() << "INFO: \"insertForwardMuxNodes\" visiting ";
    startingNode->getValue()->dump();
    llvm::errs() << "Flag at entry: " << startingNode->getFlag() << "\n";

    startingNode->setFlag(true);

    llvm::errs() << "Flag after set: " << startingNode->getFlag() << "\n";

    if(startingNode->getSuccessors().size() > 1) {
        for (DFGNode* writeNode : startingNode->getSuccessors()) {

            if (writeNode->getType() == NodeType::WriteNode ||
                    writeNode->getType() == NodeType::OffsetWrite) {

                DFGNode* linkedOpNode = startingNode;

                llvm::errs() << "\nINFO: comparing windows of:\n";
                linkedOpNode->getValue()->dump();
                writeNode->getValue()->dump();

                int rw_0 = linkedOpNode->getStreamWindow().first;
                int ww_0 = writeNode->getStreamWindow().first;

                if(rw_0 - (-ww_0) != 0 ||
                   linkedOpNode->getStreamWindow().second - writeNode->getStreamWindow().second != 0){

                    int L = (-ww_0) - rw_0; //lower bound for the validity of the RAW relation
                    int U = writeNode->getStreamWindow().second;

                    if(L < 0)
                        L = 0;  //the minimum real tick is 0

                    llvm::errs() << "INFO: lower bound: " << L << "\n";
                    llvm::errs() << "INFO: upper bound:"  << U << "\n";

                    TickBasedConstantCondition* cond =
                            new TickBasedConstantCondition(defaultTickCounterName,U,L);

                    DFGNode* fallbackPredecessor = getFallbackPredecessor(linkedOpNode);

                    //DFGMuxNode* implicitMuxNode = DFGMuxNode(...);
                }
            }
        }

        for(DFGNode* succ : startingNode->getSuccessors()){
            if(!succ->getFlag()){
                insertForwardMuxNodes(succ);
            }
        }
    }

    for(DFGNode* pred : startingNode->getPredecessors()){
        if(!pred->getFlag()){
            insertForwardMuxNodes(pred);
        }
    }

}