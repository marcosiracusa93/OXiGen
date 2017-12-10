
#include "SubloopHandler.h"

using namespace oxigen;

DFG* SubloopHandler::extractSubloops(llvm::Function* F,llvm::ScalarEvolution *SE, llvm::LoopInfo *LI, DFG *graph) {

    llvm::errs() << "\nExtracting subloops for graph with base: ";
    graph->getEndNode()->getValue()->dump();


    int maxNestingDepth = getMaxNestingDepth(graph,LI,F);

    llvm::errs() << "INFO: max nesting depth for the graph: " << maxNestingDepth;

    for(int nestingLevel = maxNestingDepth; nestingLevel > 1; nestingLevel--){
        reduceLoopsToNodes(graph,LI,F,SE,nestingLevel);

        std::vector<DFGNode*> orderedNodes = graph->orderNodesWithFunc(F);

        for(DFGNode* node : orderedNodes){
            for(DFGNode* succ : node->getSuccessors()){
                if(succ->getType() == NodeType::LoopNode && node->getType() != NodeType::LoopNode &&
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
                    }else{
                        llvm::errs() << "ERROR: nesting error, terminating\n";
                        exit(EXIT_FAILURE);
                    }
                }else if(node->getType() == NodeType::LoopNode && succ->getType() != NodeType::LoopNode &&
                        node->getLoopDepth() < succ->getLoopDepth()){

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
                    }else{
                        llvm::errs() << "ERROR: nesting error, terminating\n";
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    return nullptr;
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

    llvm::Value* nodeValue = node->getValue();

    for(llvm::BasicBlock &BB : *F){
        for(llvm::Instruction &I : BB){
            if(&I == nodeValue){
                return LI->getLoopFor(&BB);
            }
        }
    }
    llvm::errs() << "ERROR: loop not found for ";
    nodeValue->dump();
    return nullptr;
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

void SubloopHandler::reduceLoopsToNodes(DFG* dfg,llvm::LoopInfo* LI,llvm::Function* F,
                                        llvm::ScalarEvolution* SE,int nestingDepth){

    std::vector<DFGNode*> orderedNodes = dfg->orderNodesWithFunc(F);

    for(DFGNode* node : orderedNodes)
        insertIntoLoopNode(node,LI,F,SE,nestingDepth,dfg);

}

void SubloopHandler::insertIntoLoopNode(DFGNode* node,llvm::LoopInfo* LI, llvm::Function* F, llvm::ScalarEvolution* SE,
                                        int nestingDepth,DFG* dfg){

    DFGNodeFactory* nodeFactory = new DFGNodeFactory();
    llvm::errs() << "INFO: considering node: ";
    node->getValue()->dump();

    promoteIfIndipendentNode(node,getNodeLoop(node, LI, F));

    if(node->getLoopDepth() == nestingDepth){

        DFGLoopNode* loopNode;
        llvm::Loop* nodeLoop = getNodeLoop(node,LI,F);

        if(loopNodesMap[nodeLoop] != nullptr) {
            loopNode = loopNodesMap[nodeLoop];
            llvm::errs() << "INFO: loop node found: ";
            loopNode->getValue()->dump();
        }else{
            loopNode = nodeFactory->createDFGLoopNode(nodeLoop);
            loopNode->setLoopDepth(node->getLoopDepth()-1);
            loopNode->setTripCount(getBackedgeTakenCount(nodeLoop,SE));
            loopNodesMap.insert(std::pair<llvm::Loop*,DFGLoopNode*>(nodeLoop,loopNode));
            loopNodesMap[nodeLoop] = loopNode;
            llvm::errs() << "New loop node added: ";
            loopNode->getValue()->dump();
        }
        node->setLoop(loopNode);

        if(node->getSuccessors().size() == 0)
            loopNode->addEndNode(node);

        if(node == dfg->getEndNode())
            dfg->setEndNode(loopNode);

        ///port insertion

        for(DFGNode* pred : node->getCrossScopePredecessors()){
            promoteIfIndipendentNode(pred,getNodeLoop(node, LI, F));
            if(pred->getLoopDepth() != node->getLoopDepth() ||
               nodeLoop != getNodeLoop(pred,LI,F) || isIndipendent(pred, nodeLoop)){
                loopNode->insertInputPort(pred,node);
            }
        }
        for(DFGNode* succ : node->getSuccessors()){
            if(succ->getLoopDepth() != node->getLoopDepth() ||
               nodeLoop != getNodeLoop(succ,LI,F) || isIndipendent(succ, nodeLoop)){
                loopNode->insertOutputPort(node,succ);
            }
        }
    }
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

    if(llvm::LoadInst* load = llvm::dyn_cast<llvm::LoadInst>(node->getValue())){

        llvm::Value* loadPtr = load->getPointerOperand();
        if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(loadPtr)){
            llvm::Value* gep_idx = *(gep->idx_end() - 1);
            if(((llvm::Instruction*)gep_idx)->getOperand(0) != loopCounter){
                return true;
            }
        }

    }else if(llvm::StoreInst* store = llvm::dyn_cast<llvm::StoreInst>(node->getValue())){

        llvm::Value* storePtr = store->getPointerOperand();
        if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(storePtr)){
            llvm::Value* gep_idx = *(gep->idx_end() - 1);
            if(((llvm::Instruction*)gep_idx)->getOperand(0) != loopCounter){
                return true;
            }
        }
    }
    return false;
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

    if(llvm::LoadInst* load = llvm::dyn_cast<llvm::LoadInst>(node->getValue())){

        llvm::Value* loadPtr = load->getPointerOperand();
        if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(loadPtr)){
            llvm::Value* gep_idx = *(gep->idx_end() - 1);
            if(((llvm::Instruction*)gep_idx)->getOperand(0) != loopCounter){
                if(node->getLoopDepth() > 1) {
                    node->setLoopDepth(node->getLoopDepth() - 1);
                    llvm::errs() << "INFO: Read node promoted outside loop\n";
                }
            }
        }

    }else if(llvm::StoreInst* store = llvm::dyn_cast<llvm::StoreInst>(node->getValue())){

        llvm::Value* storePtr = store->getPointerOperand();
        if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(storePtr)){
            llvm::Value* gep_idx = *(gep->idx_end() - 1);
            if(((llvm::Instruction*)gep_idx)->getOperand(0) != loopCounter){
                if(node->getLoopDepth() > 1) {
                    node->setLoopDepth(node->getLoopDepth() - 1);
                    llvm::errs() << "INFO: Write node promoted outside loop\n";
                }
            }
        }
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
