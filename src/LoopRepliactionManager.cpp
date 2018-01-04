
#include "LoopReplicationManager.h"

using namespace oxigen;

void LoopDependencyGraph::setTilingDelay() {

    for(LoopGraphNode* graphNode : orderedLoopNodes){

        std::vector<LoopGraphNode*> predecessors = graphNode->getPredecessors();
        int maxDelay = 0;

        for(LoopGraphNode* n : predecessors){

            int predDelay = n->getTilingDelay();

            if(n->getLoopType() == LoopType::Accumul)
                predDelay += n->getTilingFactor() - 1;

            if(predDelay > maxDelay){
                maxDelay = predDelay;
            }
        }
        graphNode->setTilingDelay(maxDelay);
    }
}

std::vector<DFGNode*> LoopDependencyGraph::getDependentLoopNodes(DFGNode *parentNode) {

    std::vector<DFGNode*> dependentLoopNodes;

    if(parentNode->getType() == NodeType::LoopNode){
        dependentLoopNodes.push_back(parentNode);
        return dependentLoopNodes;
    }

    for(DFGNode* succ : parentNode->getSuccessors()){
        if(succ->getType() == NodeType::LoopNode){
            dependentLoopNodes.push_back(succ);
        }else{
            std::vector<DFGNode*> v = getDependentLoopNodes(succ);
            dependentLoopNodes.insert(dependentLoopNodes.end(),v.begin(),v.end());
        }
    }

    return  dependentLoopNodes;
}

void LoopDependencyGraph::connectAccumulDependencies() {

    for(auto n_it = orderedLoopNodes.begin(); n_it != orderedLoopNodes.end(); ++n_it){
        if((*n_it)->getLoopType() == LoopType::Accumul){

            DFGLoopNode* dfgLoopNode = (*n_it)->getLoopNode();

            std::vector<DFGNode*> outPortInnerNodes = dfgLoopNode->getInPortInnerNodes();

            std::set<DFGNode*> connectedLoops;

            for(DFGNode* n : outPortInnerNodes){

                if(n->getType() == NodeType::AccumulNode){

                    std::vector<DFGNode*> n_successors = dfgLoopNode->getOutPortSuccessors(n);

                    for(DFGNode* succ : n_successors){
                        std::vector<DFGNode*> dependentLoops = getDependentLoopNodes(succ);

                        for(auto el : dependentLoops){
                            connectedLoops.insert(el);
                        }
                    }
                }
            }

            for(auto n_it_2 = n_it+1; n_it_2 != orderedLoopNodes.end(); ++n_it_2){

                LoopGraphNode* succNode = (*n_it_2);

                for(DFGNode* connectedLoop : connectedLoops){
                    DFGLoopNode* l = (DFGLoopNode*)connectedLoop;

                    if(succNode->getLoopNode() == l){
                        std::vector<LoopGraphNode*> preds = succNode->getPredecessors();

                        if(std::find(preds.begin(),preds.end(),*n_it) == preds.end()){
                            succNode->insertPredecessor(*n_it);
                            (*n_it)->insertSuccessor(*n_it_2);
                        }
                    }
                }
            }
        }
    }
}

LoopDependencyGraph::LoopDependencyGraph(DFG *dfg,llvm::Function* F) {

    DFGNode* dfgEndNode = dfg->getEndNode();

    this->graphLoopDepth = dfgEndNode->getLoopDepth();

    std::vector<DFGNode*> orderedNodes = dfg->orderNodesWithFunc(F);

    for(DFGNode* n : orderedNodes){
        if(n->getType() == NodeType::LoopNode){
            DFGLoopNode* loopNode = (DFGLoopNode*)n;
            std::vector<DFGNode*> nestedVectorWrites =
                    oxigen::getExpansionLoopNestedVectorWrites(loopNode,F);

            LoopGraphNode* lgn = new LoopGraphNode(loopNode,nestedVectorWrites);
            orderedLoopNodes.push_back(lgn);

            if(nestedVectorWrites.size() != 0){
                ///Add to graph as 'begin' node

                if(oxigen::isAccumulationLoop(loopNode,F)){
                    llvm::errs() << "ERROR: accumulation node with nested vector writes\n";
                    exit(EXIT_FAILURE);
                }else{
                    lgn->setLoopType(LoopType::Expansion);
                    beginLoopNodes.push_back(lgn);
                }

            }else if(oxigen::isAccumulationLoop(loopNode,F)){
                lgn->setLoopType(LoopType::Accumul);
            }else{
                lgn->setLoopType(LoopType::Neutral);
            }

            std::vector<DFGNode*> inPortOuterNodes = loopNode->getInPortOuterNodes();

            ///find nested vector reads
            for(auto w_it = beginLoopNodes.rbegin(); w_it != beginLoopNodes.rend(); ++w_it){
                std::vector<DFGNode*> vecorWrites = (*w_it)->getNestedVectorStores();

                ///if write is read in loop -> connect nodes
                for(DFGNode* store : vecorWrites){

                    auto pos = std::find(inPortOuterNodes.begin(),inPortOuterNodes.end(),store);

                    if(pos != inPortOuterNodes.end()){

                        llvm::errs() << "INFO: data dependency found between:\n";
                        (*w_it)->getLoopNode()->getValue()->dump();
                        loopNode->getValue()->dump();
                        llvm::errs() << "\n";

                        std::vector<LoopGraphNode*> preds = lgn->getPredecessors();

                        if(std::find(preds.begin(),preds.end(),*w_it) == preds.end()){

                            lgn->insertPredecessor(*w_it);
                            (*w_it)->insertSuccessor(lgn);
                        }

                        lgn->insertNestedVectorRead(*pos);
                    }
                }
            }
        }
    }
    connectAccumulDependencies();
}

int LoopDependencyGraph::getFinalDelay() {

    LoopGraphNode* lastNode = orderedLoopNodes.back();

    int finalDelay = lastNode->getTilingDelay();

    if(lastNode->getLoopType() == LoopType::Accumul){
        finalDelay+= lastNode->getTilingFactor()-1;
    }
    return finalDelay;
}

LoopGraphNode* LoopDependencyGraph::getNodeForLoop(DFGLoopNode *loopNode) {

    LoopGraphNode* graphNode = nullptr;

    for(auto n : beginLoopNodes){
        loopNode->getValue()->dump();
        if(n->getLoopNode() == loopNode) {
            return n;
        }
    }

    for(auto n : beginLoopNodes) {
        graphNode = getNodeForLoop(loopNode, n);
        if (graphNode != nullptr) {
            return  graphNode;
        }
    }

    return graphNode;
}

LoopGraphNode* LoopDependencyGraph::getNodeForLoop(DFGLoopNode *loopNode,LoopGraphNode* node) {

    std::vector<LoopGraphNode*> successors = node->getSuccessors();
    LoopGraphNode* graphNode = nullptr;

    for(auto succ : successors){
        if(succ->getLoopNode() == loopNode){
            return succ;
        }
    }
    for(auto succ : successors){
        graphNode = getNodeForLoop(loopNode,succ);
        if(graphNode != nullptr)
            return graphNode;
    }
    return graphNode;
}

void LoopDependencyGraph::printGraphNode(LoopGraphNode *gn) {

    gn->printLoopGraphNode();

    for(LoopGraphNode* n : gn->getSuccessors())
        printGraphNode(n);
}

void LoopDependencyGraph::printDependencyGraph() {

    for(LoopGraphNode* gn : beginLoopNodes){
        printGraphNode(gn);
    }
}

void LoopGraphNode::printLoopGraphNode(){

    llvm::errs() << "\nLOOP: ";
    loopNode->getValue()->dump();

    llvm::errs() << "TYPE: ";

    switch(typeID){
        case LoopType::Expansion:
        {
            llvm::errs() << "expansion\n";
            break;
        }
        case LoopType::Accumul:
        {
            llvm::errs() << "accumulation\n";
            break;
        }
        case LoopType::Neutral:
        {
            llvm::errs() << "neutral\n";
            break;
        }
        default:
        llvm::errs() << "unidentified\n";
    }

    llvm::errs() << "NESTED_VECTOR_WRITES:\n";

    for(DFGNode* n : nestedVectorStores)
        n->getValue()->dump();

    llvm::errs() << "NESTED_VECTOR_READS:\n";

    for(DFGNode* n : nestedVectorReads)
        n->getValue()->dump();

    llvm::errs() << "PREDECESSORS:\n";

    for(LoopGraphNode* ln : precedingLoops)
        ln->getLoopNode()->getValue()->dump();

    llvm::errs() << "SUCCESSORS\n";

    for(LoopGraphNode* ln : succedingLoops)
        ln->getLoopNode()->getValue()->dump();

    llvm::errs() << "TILING DELAY: " << tilingDelay << "\n";
}

LoopDependencyGraph* LoopReplicationManager::analyzeDFGLoops(DFG *dfg) {

    ///STUB
    std::vector<DFGNode*> orderedNodes = dfg->orderNodesWithFunc(F);

    for(DFGNode* n : orderedNodes){
        if(n->getType() == NodeType::LoopNode){
            llvm::errs() << "RESULT: Is accumulation loop for ";
            n->getValue()->dump();
            llvm::errs() << "RESULT: " << oxigen::isAccumulationLoop((DFGLoopNode*)n,F) << "\n";

            llvm::errs() << "RESULT: Is expansion loop for ";
            n->getValue()->dump();
            llvm::errs() << "RESULT: " << oxigen::isExpansionLoop((DFGLoopNode*)n,F) << "\n";
        }
    }

    LoopDependencyGraph* dependencyGraph = new LoopDependencyGraph(dfg,F);

    return dependencyGraph;

}

std::vector<DFGNode*> oxigen::getExpansionLoopNestedVectorWrites(DFGLoopNode *loopNode, llvm::Function *F) {

    std::vector<DFG*> indipendentGraphs = loopNode->getIndipendentLoopGraphs();
    std::vector<DFGNode*> nestedVectorWrites;

    if(indipendentGraphs.size() > 1)
        llvm::errs() << "WARNING: indipendent graphs in the same nested loop\n"
                "WARNING: some optimizations may not be possible\n";

    for(DFG* dfg : indipendentGraphs){

        std::vector<DFGNode*> orderedNodes = dfg->orderNodesWithFunc(F);

        for(DFGNode* n : orderedNodes){

            if(oxigen::isNestedVectorWrite(n)){
                nestedVectorWrites.push_back(n);
            }
        }
    }
    return nestedVectorWrites;
}

bool oxigen::isAccumulationLoop(DFGLoopNode *loopNode, llvm::Function *F) {

    std::vector<DFGNode *> loopDependentNodes;

    std::vector<DFG *> dfgs = loopNode->getIndipendentLoopGraphs();

    for (DFG *dfg : dfgs) {

        loopDependentNodes = oxigen::getLoopCarriedDependencies(dfg);

        for(DFGNode* n : loopDependentNodes){
            if(n->getType() == NodeType::AccumulNode){
                return true;
            }
        }

    }
    return false;
}

bool oxigen::isExpansionLoop(DFGLoopNode *loopNode, llvm::Function *F) {

    return oxigen::getExpansionLoopNestedVectorWrites(loopNode,F).size() != 0;
}