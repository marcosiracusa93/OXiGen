
#include "SubloopHandler.h"

using namespace oxigen;

DFG* SubloopHandler::extractSubloops(llvm::Function* F,llvm::ScalarEvolution *SE, llvm::LoopInfo *LI, DFG *graph) {

    llvm::errs() << "\nExtracting subloops for graph with base: ";
    graph->getEndNode()->getValue()->dump();


    int maxNestingDepth = getMaxNestingDepth(graph,LI,F);

    llvm::errs() << "INFO: max nesting depth for the graph: " << maxNestingDepth;

    for(int nestingLevel = maxNestingDepth; nestingLevel > 1; nestingLevel--){
        reduceLoopsToNodes(graph,LI,F,SE,nestingLevel);
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

    DFGNodeFactory* nodeFactory = new DFGNodeFactory();
    DFGNode* node = dfg->getEndNode();
    dfg->resetFlags(node);
    promoteIfIndipendentNode(node,getNodeLoop(node, LI, F));

    llvm::errs() << "INFO: considering node: ";
    node->getValue()->dump();

    if(node->getLoopDepth() == nestingDepth){

        DFGLoopNode* loopNode;
        llvm::Loop* nodeLoop = getNodeLoop(node,LI,F);
        llvm::errs() << "INFO: reduce to nodes: loop: ";
        nodeLoop->getCanonicalInductionVariable()->dump();

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
        loopNode->addEndNode(node);
        node->setFlag(true);
        dfg->setEndNode(loopNode);

        for(DFGNode* pred : node->getPredecessors())
            insertIntoLoopNode(pred,LI,F,SE,nestingDepth);
    }else {
        insertIntoLoopNode(node, LI, F, SE, nestingDepth);
    }
}

void SubloopHandler::insertIntoLoopNode(DFGNode* node,llvm::LoopInfo* LI, llvm::Function* F, llvm::ScalarEvolution* SE,
                                        int nestingDepth){

    DFGNodeFactory* nodeFactory = new DFGNodeFactory();
    node->setFlag(true);
    promoteIfIndipendentNode(node,getNodeLoop(node, LI, F));

    llvm::errs() << "INFO: considering node: ";
    node->getValue()->dump();

    if(node->getLoopDepth() == nestingDepth) {
        llvm::Loop *nodeLoop = getNodeLoop(node, LI, F);
        DFGLoopNode* loopNode;

        if (loopNodesMap[nodeLoop] != nullptr) {
            //node is already initialized. Insert this node into the loop graph
            loopNode = loopNodesMap[nodeLoop];
            llvm::errs() << "INFO: loop node found: ";
            loopNode->getValue()->dump();

        } else {
            //initialize a new loop node
            loopNode = nodeFactory->createDFGLoopNode(nodeLoop);
            loopNode->setLoopDepth(node->getLoopDepth()-1);
            loopNode->setTripCount(getBackedgeTakenCount(nodeLoop,SE));
            loopNodesMap.insert(std::pair<llvm::Loop*,DFGLoopNode*>(nodeLoop,loopNode));
            loopNodesMap[nodeLoop] = loopNode;
            llvm::errs() << "New loop node added: ";
            loopNode->getValue()->dump();
        }

        node->setLoop(loopNode);

        for(DFGNode* pred : node->getPredecessors()){
            promoteIfIndipendentNode(pred,nodeLoop);
            if(pred->getLoopDepth() < node->getLoopDepth()){
                loopNode->insertInputPort(pred,node);
            }
        }

        for(DFGNode* succ : node->getSuccessors()){
            promoteIfIndipendentNode(succ,nodeLoop);
            if(succ->getLoopDepth() < node->getLoopDepth()){
                loopNode->insertOutputPort(node,succ);
            }
        }
    }

    for(DFGNode* pred : node->getPredecessors()){
        if(!pred->getFlag())
            insertIntoLoopNode(pred,LI,F,SE,nestingDepth);
    }

    for(DFGNode* succ : node->getSuccessors()){
        if(!succ->getFlag())
            insertIntoLoopNode(succ,LI,F,SE,nestingDepth);
    }
}

void SubloopHandler::promoteIfIndipendentNode(DFGNode *node, llvm::Loop *loop) {

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
                node->setLoopDepth(node->getLoopDepth()-1);
                llvm::errs() << "INFO: Read node promoted outside loop\n";
            }
        }

    }else if(llvm::StoreInst* store = llvm::dyn_cast<llvm::StoreInst>(node->getValue())){

        llvm::Value* storePtr = store->getPointerOperand();
        if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(storePtr)){
            llvm::Value* gep_idx = *(gep->idx_end() - 1);
            if(((llvm::Instruction*)gep_idx)->getOperand(0) != loopCounter){
                node->setLoopDepth(node->getLoopDepth()-1);
                llvm::errs() << "INFO: Write node promoted outside loop\n";
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
