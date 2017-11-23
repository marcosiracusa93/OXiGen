
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
        if(n->getStreamWindow().first != 0 && n->getPredecessors().size() == 0){
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

std::pair<int,int> DFGStreamsOverlapHandler::computeLoopCarriedDependencyWindow(DFGWriteNode *write, DFGReadNode *read){

    std::pair<int,int> dependenceWindow = std::pair<int,int>(-1,-1);    //default response for no dependence

    if(scheduler->getType() != SchedulerType::Default) {
        llvm::errs() << "Loop carried dependence analysis not implemented for this scheduler...\n";
        exit(EXIT_FAILURE);
    }else{
        DefaultScheduler* dSched = (DefaultScheduler*)scheduler;
        llvm::LoopInfo* loopInfo = dSched->getLoopInfo();

        std::pair<int,int> posWriteWindow =
                std::pair<int,int>(-(write->getStreamWindow().first),
                                   -2*(write->getStreamWindow().first)+write->getStreamWindow().second);

        if(!write->isInTheSameLoop(read,loopInfo))
            return dependenceWindow;

        int rw_min = read->getStreamWindow().first;
        int rw_max = read->getStreamWindow().second;
        int ww_min = posWriteWindow.first;
        int ww_max = posWriteWindow.second;

        if(rw_min >= ww_min-1 )
            return dependenceWindow;

        llvm::errs() << "Loop carried dependenece found from\n ";
        write->getValue()->dump();
        llvm::errs() << " \nto\n";
        read->getValue()->dump();

        int L = ww_min - rw_min;
        int U = std::min(rw_max,ww_max);

        dependenceWindow.first = U;
        dependenceWindow.second = L;

        return dependenceWindow;
    }
}

std::vector<DFG*> DFGStreamsOverlapHandler::computeFallbackWrites(){

    std::vector<DFGNode*>  nodesOrder;
    std::vector<DFGWriteNode*> writeNodes;
    int baseSize = 0;

    for(DFG* dfg : DFGStreamsOverlapHandler::graphs)
    {
        int graphSize = dfg->getNodesCount();
        DFGNode* base = dfg->getEndNode();
        std::vector<DFGWriteNode*> wNodes;
        std::vector<DFGNode*> sortedNodes(graphSize);

        dfg->getWriteNodes(base,wNodes);

        dfg->resetFlags(dfg->getEndNode());

        dfg->orderNodes(dfg->getEndNode(),baseSize,sortedNodes,baseSize);

        nodesOrder.insert(nodesOrder.end(),sortedNodes.begin(),sortedNodes.end());

        baseSize += graphSize;

        writeNodes.insert(writeNodes.end(),wNodes.begin(),wNodes.end());
    }

    for(int i = 0; i < nodesOrder.size(); i++)
    {
        if(std::find(writeNodes.begin(), writeNodes.end(), nodesOrder.at(i)) != writeNodes.end())
        {
            DFGWriteNode* write_1 = (DFGWriteNode*)(nodesOrder.at(i));

            for(int j = i-1; j >= 0; j--)
            {
                if(std::find(writeNodes.begin(), writeNodes.end(), nodesOrder.at(j)) != writeNodes.end())
                {
                    DFGWriteNode *write_2 = (DFGWriteNode *) nodesOrder.at(j);

                    if(write_1->getWritingStream().first == write_2->getWritingStream().first){

                        int posWStart_1 = -write_1->getStreamWindow().first;
                        int posWStart_2 = -write_2->getStreamWindow().first;
                        int posWEnd_1 = write_1->getStreamWindow().second+2*posWStart_1;
                        int posWEnd_2 = write_2->getStreamWindow().second+2*posWStart_2;

                        int overlapStart = std::max(posWStart_1,posWStart_2);
                        int overlapEnd = std::min(posWEnd_1,posWEnd_2);

                        if(overlapEnd-overlapStart !=0){

                            TickBasedCondition* cond;

                            cond = new TickBasedConstantCondition(defaultTickCounterName,overlapEnd,overlapStart);

                            if(overlapEnd-overlapStart < 0 && posWStart_1-posWEnd_1 == 0){
                                cond = new TickBasedConstantCondition(defaultTickCounterName,posWEnd_1,posWStart_1);
                            }

                            if(overlapEnd-overlapStart < 0 && posWStart_2-posWEnd_2 == 0){
                                cond = new TickBasedConstantCondition(defaultTickCounterName,posWEnd_2,posWStart_2);
                            }

                            DFGMuxNode* linkingMux = new DFGMuxNode(write_1,write_2,cond);

                            oxigen::insertNode(linkingMux,write_1->getPredecessors().at(0),write_1,true);
                            linkingMux->linkPredecessor(write_2->getPredecessors().at(0));

                            j = 0;
                        }
                    }
                }
            }
        }
    }

    std::vector<DFG*> indipendentGraphs;
    std::vector<DFG*> reverseGraphs(graphs.size());
    std::reverse_copy(std::begin(graphs),std::end(graphs),std::begin(reverseGraphs));

    for(DFG* dfg : graphs) {
        dfg->resetFlags(dfg->getEndNode());
    }

    for(DFG* dfg : reverseGraphs){

        if(!dfg->getEndNode()->getFlag())
            indipendentGraphs.push_back(dfg);

        dfg->setDFGFlags();
    }

    graphs = indipendentGraphs;

    return indipendentGraphs;
}
