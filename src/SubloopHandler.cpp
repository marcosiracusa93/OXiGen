
#include "SubloopHandler.h"

using namespace oxigen;

DFG* SubloopHandler::extractSubloops(llvm::Function* F,llvm::ScalarEvolution *SE, llvm::LoopInfo *LI, DFG *graph) {

    /*
    llvm::errs() << "\nExtracting subloops for graph with base: ";
    graph->getEndNode()->getValue()->dump();


    int maxNestingDepth = getMaxNestingDepth(graph,LI,F);

    llvm::errs() << "INFO: max nesting depth for the graph: " << maxNestingDepth << "\n";

    for(int nestingLevel = maxNestingDepth; nestingLevel > 1; nestingLevel--) {

        reduceLoopsToNodes(graph, LI, F, SE, nestingLevel);

        bool graphWasModified = true;

        while (graphWasModified) {

            std::vector <DFGNode*> orderedNodes = graph->orderNodesWithFunc(F);

            graphWasModified = false;

            for (DFGNode *node : orderedNodes) {
                for (DFGNode *succ : node->getSuccessors()) {
                    if (succ->getType() == NodeType::LoopNode ){
                        llvm::errs() << "Fixing connections for loop ";
                        succ->getValue()->dump();
                    }
                    if (succ->getType() == NodeType::LoopNode && node->getType() != NodeType::LoopNode &&
                        succ->getLoopDepth() < node->getLoopDepth()) {
                        llvm::errs() << " Mismatching depths for\n";
                        node->getValue()->dump();
                        succ->getValue()->dump();
                        llvm::Loop *nodeLoop = getNodeLoop(node, LI, F);
                        DFGLoopNode *loopNode;

                        if (nodeLoop != nullptr)
                            loopNode = loopNodesMap[nodeLoop];
                        else {
                            llvm::errs() << "ERROR: nesting error, terminating\n";
                            exit(EXIT_FAILURE);
                        }
                        if (loopNode != nullptr) {
                            succ->unlinkPredecessor(node);
                            succ->linkPredecessor(loopNodesMap[nodeLoop]);
                            graphWasModified = true;
                        } else {
                            llvm::errs() << "ERROR: nesting error, terminating\n";
                            exit(EXIT_FAILURE);
                        }
                    } else if (node->getType() == NodeType::LoopNode && succ->getType() != NodeType::LoopNode &&
                               node->getLoopDepth() < succ->getLoopDepth()) {

                        llvm::errs() << " Mismatching depths for\n";
                        node->getValue()->dump();
                        succ->getValue()->dump();
                        llvm::Loop *nodeLoop = getNodeLoop(succ, LI, F);
                        DFGLoopNode *loopNode;

                        if (nodeLoop != nullptr)
                            loopNode = loopNodesMap[nodeLoop];
                        else {
                            llvm::errs() << "ERROR: nesting error, terminating\n";
                            exit(EXIT_FAILURE);
                        }
                        if (loopNode != nullptr) {
                            succ->unlinkPredecessor(node);
                            loopNodesMap[nodeLoop]->linkPredecessor(node);
                            graphWasModified = true;
                        } else {
                            llvm::errs() << "ERROR: nesting error, terminating\n";
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
        }
    }
*/

    std::vector<DFGNode*> sortedNodes = graph->orderNodesWithFunc(F);

    for(DFGNode* n : sortedNodes){
        n->setLoopDepth(getNodeLoopDepth(n,LI,F));
    }

    for(auto it = sortedNodes.rbegin(); it != sortedNodes.rend(); ++it){
        createLoopNodes(*it,LI,F,SE,graph);
    }

    return nullptr;
}

llvm::Loop* SubloopHandler::getCommonLoopParent(DFGNode *n_1, DFGNode *n_2,llvm::LoopInfo *LI, llvm::Function *F) {

    llvm::Loop* loop_1 = getNodeLoop(n_1,LI,F);
    llvm::Loop* loop_2 = getNodeLoop(n_2,LI,F);

    if(loop_1 != nullptr && loop_2 == nullptr){
        loop_2 = loop_1;
        loop_1 = nullptr;
    }

    if(loop_1 == nullptr && loop_2 != nullptr){
        while(loop_2->getLoopDepth() > 1){
            loop_2 = loop_2->getParentLoop();
        }
        return loop_2;
    }

    if(loop_1 == loop_2){
        return loop_1;
    }else{
        llvm::Loop* moreNested = loop_1->getLoopDepth() >= loop_2->getLoopDepth() ? loop_1 : loop_2;
        llvm::Loop* other = moreNested == loop_1 ? loop_2 : loop_1;

        while(moreNested != other && moreNested->getLoopDepth() != 1){
            moreNested = moreNested->getParentLoop();
            if(moreNested == other){
                return moreNested;
            }
            loop_1 = moreNested;
            loop_2 = other;
            moreNested = loop_1->getLoopDepth() >= loop_2->getLoopDepth() ? loop_1 : loop_2;
            other = moreNested == loop_1 ? loop_2 : loop_1;
        }
        return  moreNested;
    }
}

void SubloopHandler::createLoopNodes(DFGNode *node, llvm::LoopInfo *LI, llvm::Function *F,
                                     llvm::ScalarEvolution* SE,DFG* dfg) {

    llvm::errs() << "INFO: createLoopNodes() for node: ";
    node->getValue()->dump();
    llvm::errs() << "\n";

    DFGNodeFactory nodeFactory = DFGNodeFactory();
    llvm::Loop* nodeLoop = getNodeLoop(node,LI,F);
    DFGLoopNode* loopNode;
    bool isAlreadyDeclared = false;

    if(nodeLoop == nullptr || nodeLoop->getLoopDepth() <= 1){
        llvm::errs() << "INFO: no action taken for ";
        node->getValue()->dump();
        return;
    }

    if(loopNodesMap[nodeLoop] != nullptr) {
        loopNode = loopNodesMap[nodeLoop];
        isAlreadyDeclared = true;
        llvm::errs() << "INFO: loop node found: ";
        loopNode->getValue()->dump();
    }else{
        loopNode = nodeFactory.createDFGLoopNode(nodeLoop);
        loopNode->setLoopDepth(node->getLoopDepth()-1);
        loopNode->setTripCount(getBackedgeTakenCount(nodeLoop,SE));
        loopNodesMap.insert(std::pair<llvm::Loop*,DFGLoopNode*>(nodeLoop,loopNode));
        loopNodesMap[nodeLoop] = loopNode;
        llvm::errs() << "New loop node added: ";
        loopNode->getValue()->dump();
    }
    node->setLoop(loopNode);

    ///handle graph end node cases

    if(node->getSuccessors().size() == 0){
        loopNode->addEndNode(node);
        llvm::errs() << "INFO: added as end node for loop: ";
        node->getValue()->dump();
    }

    if(node == dfg->getEndNode()){
        dfg->setEndNode(loopNode);
        llvm::errs() << "INFO: set loop node as end node: ";
        loopNode->getValue()->dump();
    }

    ///create loop node for nested inner loop

    if(loopNode->getLoopDepth() > 1 && !isAlreadyDeclared)
        createLoopNodes(loopNode,LI,F,SE,dfg);

    ///transfer extern predecessors to loop node

    for(DFGNode* pred : node->getPredecessors()){
        llvm::Loop* predLoop = getNodeLoop(pred,LI,F);

        if(((predLoop == nullptr && nodeLoop->getLoopDepth() != 1) || predLoop != nodeLoop)) {

            if (pred->getType() != NodeType::LoopNode) {
                if (node->getType() != NodeType::LoopNode) {
                    loopNode->insertInputPort(pred, node);
                }
            } else {
                llvm::errs() << "ERROR: unexpected loop node predecessor, terminating\n";
                exit(EXIT_FAILURE);
            }
            ///make pred-->node opaque

            llvm::Loop* commonLoop = getCommonLoopParent(node,pred,LI,F);
            llvm::Loop* loopToConnect = nodeLoop;

            while(loopToConnect->getLoopDepth() - 1 > commonLoop->getLoopDepth()){
                loopToConnect = loopToConnect->getParentLoop();
            }
            DFGLoopNode* loopNodeToConnect = loopNodesMap[loopToConnect];

            if(loopToConnect == nullptr){
                llvm::errs() << "ERROR: uninitialized loop\n";
                exit(EXIT_FAILURE);
            }
            node->unlinkPredecessor(pred);
            loopNodeToConnect->linkPredecessor(pred);
            llvm::errs() << "INFO: linked:\n";
            pred->getValue()->dump();
            loopNodeToConnect->getValue()->dump();
        }
    }

    ///transfer extern successors to loop node

    for(DFGNode* succ : node->getSuccessors()){
        llvm::Loop* succLoop = getNodeLoop(succ,LI,F);

        if(((succLoop == nullptr && nodeLoop->getLoopDepth() != 1) || succLoop != nodeLoop)){

            if(node->getType() != NodeType::LoopNode && succ->getType() != NodeType::LoopNode){
                loopNode->insertOutputPort(node,succ);
            }

            llvm::Loop* commonLoop = getCommonLoopParent(succ,node,LI,F);
            llvm::Loop* loopToConnect = nodeLoop;

            while(loopToConnect->getLoopDepth() - 1 > commonLoop->getLoopDepth()){
                loopToConnect = loopToConnect->getParentLoop();
            }

            DFGLoopNode* loopNodeToConnect = loopNodesMap[loopToConnect];

            if(loopToConnect == nullptr){
                llvm::errs() << "ERROR: uninitialized loop\n";
                exit(EXIT_FAILURE);
            }
            succ->unlinkPredecessor(node);
            succ->linkPredecessor(loopNodeToConnect);
            llvm::errs() << "INFO: linked:\n";
            loopNodeToConnect->getValue()->dump();
            succ->getValue()->dump();
        }
    }
}

int SubloopHandler::getNodeLoopDepth(DFGNode* node,llvm::LoopInfo* LI,llvm::Function* F){

    llvm::Value* nodeValue = node->getValue();

    for(llvm::BasicBlock &BB : *F){
        for(llvm::Instruction &I : BB){
            if(&I == nodeValue){
                return LI->getLoopDepth(&BB);
            }
        }
    }

    return 0;
}

llvm::Loop* SubloopHandler::getNodeLoop(DFGNode* node,llvm::LoopInfo* LI,llvm::Function* F){

    llvm::Loop* loop = nullptr;
    llvm::Value* nodeValue = node->getValue();

    if(node->getType() == NodeType::Offset){
        DFGOffsetNode* offset = (DFGOffsetNode*)node;

        if(offset->getOffsetAsInt() < 0){
            nodeValue = node->getPredecessors().at(0)->getValue();
            llvm::errs() << "INFO: getNodeLoop(): loop of offset node set to pred for ";
            offset->getValue()->dump();
        }else{
            nodeValue = node->getSuccessors().at(0)->getValue();
            llvm::errs() << "INFO: getNodeLoop(): loop of offset node set to succ for ";
            offset->getValue()->dump();
        }
    }

    for(llvm::BasicBlock &BB : *F){
        for(llvm::Instruction &I : BB){
            if(&I == nodeValue){
                loop =  LI->getLoopFor(&BB);
            }
        }
    }

    if(node->getType() == NodeType::LoopNode){
        loop = loop->getParentLoop();
    }

    if(loop != nullptr){
        return loop;
    }else if(llvm::dyn_cast<llvm::Constant>(nodeValue))
        return nullptr;
    else{
        llvm::errs() << "ERROR: loop not found for ";
        nodeValue->dump();
        exit(EXIT_FAILURE);
    }
}

int SubloopHandler::getMaxNestingDepth(DFG* dfg, llvm::LoopInfo* LI,llvm::Function* F){

    DFGNode* node = dfg->getEndNode();

    dfg->resetFlags(node);

    int maxDepth = -1;
    maxDepth = calculateMaxNestingDepth(node,LI,F,maxDepth);

    return maxDepth;
}

int SubloopHandler::calculateMaxNestingDepth(DFGNode *node, llvm::LoopInfo *LI,llvm::Function* F,int maxDepth) {

    node->setFlag(true);

    int nestingDepth = getNodeLoopDepth(node,LI,F);
    node->setLoopDepth(nestingDepth);

    if(nestingDepth > maxDepth)
        maxDepth = nestingDepth;

    for(DFGNode* pred : node->getPredecessors()){
        if(!pred->getFlag())
            maxDepth = calculateMaxNestingDepth(pred,LI,F,maxDepth);
    }
    for(DFGNode* succ : node->getSuccessors()){
        if(!succ->getFlag())
            maxDepth = calculateMaxNestingDepth(succ,LI,F,maxDepth);
    }
    return maxDepth;

}

bool SubloopHandler::isIndipendent(DFGNode *node, llvm::Loop *loop) {

    if(loop == nullptr){
        llvm::errs() << "INFO: loop not found for node ";
        return true;
    }
    llvm::PHINode* loopCounter = oxigen::getLoopCounterIfAny(loop);

    if(node->getLoopDepth() != loop->getLoopDepth()){
        llvm::errs() << "INFO: unmatching nesting depths\n";
        return true;
    }

    bool isIndipendent = false;

    if(llvm::dyn_cast<llvm::LoadInst>(node->getValue())){

        isIndipendent = true;

        DFGReadNode* rNode = (DFGReadNode*) node;
        std::vector<llvm::Value*> accesses = rNode->getAccessChain()->getAccessIndexesIfAny();

        for(llvm::Value* access : accesses){
            if(access == loopCounter)
                isIndipendent = false;
        }

    }else if(llvm::dyn_cast<llvm::StoreInst>(node->getValue())){

        isIndipendent = true;

        DFGWriteNode* wNode = (DFGWriteNode*) node;
        std::vector<llvm::Value*> accesses = wNode->getAccessChain()->getAccessIndexesIfAny();

        for(llvm::Value* access : accesses){
            if(access == loopCounter)
                isIndipendent = false;
        }
    }
    return isIndipendent;
}

void SubloopHandler::promoteIfIndipendentNode(DFGNode *node, llvm::Loop *loop) {

    if(loop == nullptr){
        llvm::errs() << "INFO: loop not found for node ";
        node->getValue()->dump();
        if(node->getLoopDepth() > 1)
            node->setLoopDepth(node->getLoopDepth()-1);
        return;
    }
    llvm::PHINode* loopCounter = oxigen::getLoopCounterIfAny(loop);

    llvm::errs() << "INFO: computing proper loop depth for ";
    node->getValue()->dump();
    if(node->getLoopDepth() != loop->getLoopDepth()){
        llvm::errs() << "INFO: unmatching nesting depths\n";
        return;
    }

    bool isIndipendent = false;

    if(llvm::dyn_cast<llvm::LoadInst>(node->getValue())){

        isIndipendent = true;

        DFGReadNode* rNode = (DFGReadNode*) node;
        std::vector<llvm::Value*> accesses = rNode->getAccessChain()->getAccessIndexesIfAny();

        for(llvm::Value* access : accesses){
            if(access == loopCounter)
                isIndipendent = false;
        }

    }else if(llvm::dyn_cast<llvm::StoreInst>(node->getValue())){

        isIndipendent = true;

        DFGWriteNode* wNode = (DFGWriteNode*) node;
        std::vector<llvm::Value*> accesses = wNode->getAccessChain()->getAccessIndexesIfAny();

        for(llvm::Value* access : accesses){
            if(access == loopCounter)
                isIndipendent = false;
        }
    }

    if(isIndipendent){
        llvm::errs() << "INFO: promoting ";
        node->getValue()->dump();
        node->setLoopDepth(node->getLoopDepth()-1);
    }

}

int SubloopHandler::getBackedgeTakenCount(llvm::Loop *nodeLoop, llvm::ScalarEvolution *SE) {

    if(SE->hasLoopInvariantBackedgeTakenCount(nodeLoop)){
        const llvm::SCEV* scev = SE->getBackedgeTakenCount(nodeLoop);
        if(const llvm::SCEVConstant* scev_c  = llvm::dyn_cast<llvm::SCEVConstant>(scev)){
            return scev_c->getValue()->getSExtValue();
        }
    }

    return -1;
}
