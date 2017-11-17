
#include "DFGStreamsOverlapHandler.h"

using namespace oxigen;

std::string defaultTickCounterName = "def_counter";

void DFGStreamsOverlapHandler::addOffsetIfFinalStore(DFGNode* n){

    n->setFlag(true);

    if(llvm::dyn_cast<llvm::StoreInst>(n->getValue()))
        if(n->getStreamWindow().first < 0 && n->getPredecessors().at(0)->getSuccessors().size() == 1){
            DFGOffsetNode* offsetNode = new DFGOffsetNode(n);
            oxigen::insertNode(offsetNode,n->getPredecessors().at(0),n,true);
        }

    for(DFGNode* s : n->getSuccessors())
        if(!s->getFlag())
            addOffsetIfFinalStore(s);

    for(DFGNode* p : n->getPredecessors())
        if(!p->getFlag())
            addOffsetIfFinalStore(p);

}

void DFGStreamsOverlapHandler::addOffsetIfInitialRead(DFGNode *n) {

    n->setFlag(true);

    if(llvm::dyn_cast<llvm::LoadInst>(n->getValue()))
        if(n->getStreamWindow().first > 0 && n->getPredecessors().size() == 0){
            DFGOffsetNode* offsetNode = new DFGOffsetNode(n);
            oxigen::insertNode(offsetNode,n,n->getSuccessors().at(0),true);
        }

    for(DFGNode* s : n->getSuccessors())
        if(!s->getFlag())
            addOffsetIfInitialRead(s);

    for(DFGNode* p : n->getPredecessors())
        if(!p->getFlag())
            addOffsetIfInitialRead(p);
}

void DFGStreamsOverlapHandler::addFinalStoreOffsets(DFG *dfg) {

    DFGNode* baseNode = dfg->getEndNode();
    dfg->resetFlags(baseNode);

    addOffsetIfFinalStore(baseNode);
}

void DFGStreamsOverlapHandler::addInitialReadsOffsets(DFG *dfg) {

    DFGNode* baseNode = dfg->getEndNode();
    dfg->resetFlags(baseNode);

    addOffsetIfInitialRead(baseNode);
}


void DFGStreamsOverlapHandler::descendAndComputeDelay(DFGNode* node){

    DFGNode *startingNode = node;
    int succSize = startingNode->getSuccessors().size();

    while (succSize != 0)
        for (DFGNode *succ : startingNode->getSuccessors()){
            if (!succ->getFlag()) {
                startingNode = succ;
                succSize = startingNode->getSuccessors().size();
                break;
            }
            succSize--;
        }

    if (startingNode != node)
        computeDelayForNode(startingNode);
}

void DFGStreamsOverlapHandler::computeDelayForNode(DFGNode* node){

    llvm::errs() << "Computing delay for ";
    node->getValue()->dump();

    if(node->getPredecessors().size() == 0){
        node->setGlobalDelay(0);
        node->setFlag(true);
        return;
    }

    for(DFGNode* p : node->getPredecessors()){
        if(!p->getFlag()){
            computeDelayForNode(p);
        }
    }

    if(node->getType() == NodeType::Offset){
        DFGOffsetNode* offsetNode = (DFGOffsetNode*)node;
        int offsetAsInt = offsetNode->getOffsetAsInt();

        if(offsetAsInt < 0){
            offsetNode->setGlobalDelay(std::min(offsetNode->getPredecessors().at(0)->getGlobalDelay(),offsetAsInt));
            int offsetDiffAsInt = offsetAsInt-offsetNode->getPredecessors().at(0)->getGlobalDelay();
            llvm::errs() << "offsetDiff: " << offsetDiffAsInt << "for: "; node->getValue()->dump();

            offsetNode->setOffsetAsInt(offsetDiffAsInt);
            offsetNode->setFlag(true);

            if(offsetNode->getOffsetAsInt() == 0){
                oxigen::eliminateNode(offsetNode);
                return;
            }else{
                offsetNode->setFlag(true);
            }
        }else{

            node->setGlobalDelay(node->getPredecessors().at(0)->getGlobalDelay());
            node->setFlag(true);
            return;
        }
    }else{

        int minDelay = 0;

        for(DFGNode* p : node->getPredecessors()){
            if(p->getGlobalDelay() < minDelay)
                minDelay = p->getGlobalDelay();
        }

        for(DFGNode* p : node->getPredecessors()){
            if(p->getGlobalDelay() > minDelay){
                if(p->getType() == NodeType::Offset){
                    DFGOffsetNode* offsetP = (DFGOffsetNode*)p;
                    offsetP->setOffsetAsInt(offsetP->getOffsetAsInt() + (minDelay-p->getGlobalDelay()));

                    if(offsetP->getOffsetAsInt() == 0)
                        oxigen::eliminateNode(offsetP);
                }else{

                    DFGOffsetNode* newOffset = new DFGOffsetNode(p);

                    newOffset->setOffsetAsInt(minDelay-p->getGlobalDelay());

                    oxigen::insertNode(newOffset,p,node,true);

                    newOffset->setGlobalDelay(minDelay);
                    newOffset->setFlag(true);
                }
            }
        }

        node->setGlobalDelay(minDelay);
        node->setFlag(true);

        for(DFGNode* p : node->getPredecessors()){
            DFGNode* crossroadNode = p;

            while(crossroadNode->getSuccessors().size() < 2){

                if(crossroadNode->getPredecessors().size() == 0)
                    break;

                crossroadNode = crossroadNode->getPredecessors().at(0);
            }

            for(DFGNode* c_succ : crossroadNode->getSuccessors()){
                if(!c_succ->getFlag())
                    descendAndComputeDelay(c_succ);
            }
        }

    }
}

void DFGStreamsOverlapHandler::computeGlobalDelay(DFG* dfg){

    DFGNode* baseNode = dfg->getEndNode();
    dfg->resetFlags(baseNode);

    computeDelayForNode(baseNode);
}

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