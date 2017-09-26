
#include "DFGConstructor.h"

using namespace oxigen;

///DFGNode methods implementation

int DFGNode::countSubgraphNodes(){
    int count = 0;
    
    for(DFGNode* pred : DFGNode::predecessors)
    {
        count += pred->countSubgraphNodes();
    }
    count++;
    
    return count;
}

void DFGNode::printNode(){
    
    llvm::errs() << "\nNode: " << name << "\n";
    node->dump();
    llvm::errs() << "Predecessors\n";
    
    for(DFGNode* predecessor : predecessors){
        predecessor->getValue()->dump();
    }
}

///DFGWriteNode methods implementation

DFGWriteNode::DFGWriteNode(llvm::Value* value, IOStreams* loopStreams) : DFGNode(value) {

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){
        for(llvm::Value* stream : loopStreams->getOutputStreams()){
            if(((llvm::Instruction*)(instr->getOperand(1)))->getOperand(0) == stream)
            {
                writingStream = stream;
                return;
            }   
        }
            writingStream = ((llvm::Instruction*)(instr->getOperand(1)))->getOperand(0);
    }
}


///DFGReadNode methods implementation

DFGReadNode::DFGReadNode(llvm::Value* value, IOStreams* loopStreams) : DFGNode(value) {
    

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){
        for(llvm::Value* stream : loopStreams->getInputStreams()){
            if(((llvm::Instruction*)(instr->getOperand(0)))->getOperand(0) == stream)
            {
                sourceStream = stream;
                return;
            }
        }
        sourceStream = ((llvm::Instruction*)(instr->getOperand(0)))->getOperand(0);
    }
}

///DFG methods implementation

void DFG::getReadNodes(DFGNode* baseNode,std::vector<DFGReadNode*> &readNodes){
    
    DFG::resetFlags(baseNode);
    
    DFG::collectReadNodes(baseNode,readNodes);

}

void DFG::collectReadNodes(DFGNode* baseNode,std::vector<DFGReadNode*> &readNodes){
    
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(baseNode->getValue()))
        if(instr->getOpcodeName() == std::string("load") && !baseNode->getFlag())
            readNodes.push_back((DFGReadNode*)baseNode);

    baseNode->setFlag(true);
    
    for(DFGNode* succ : baseNode->getSuccessors())
        if(!succ->getFlag())
            descendAndCollectReads(succ,readNodes);
    
    for(DFGNode* pred : baseNode->getPredecessors())
        if(!pred->getFlag())
            collectReadNodes(pred,readNodes);  
}

void DFG::descendAndCollectReads(DFGNode* node, std::vector<DFGReadNode*> &readNodes){
    
    DFGNode* startingNode = node;

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
            }
    if(startingNode != node)
        collectReadNodes(startingNode,readNodes);
    else
        if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(startingNode->getValue()))
            if(instr->getOpcodeName() == std::string("load") && !startingNode->getFlag())
                readNodes.push_back((DFGReadNode*)startingNode);
            
}    

void DFG::getWriteNodes(DFGNode* baseNode,std::vector<DFGWriteNode*> &writeNodes){
    
    DFG::resetFlags(baseNode);
    
    DFG::collectWriteNodes(baseNode,writeNodes);

}

void DFG::collectWriteNodes(DFGNode* baseNode,std::vector<DFGWriteNode*> &writeNodes){

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(baseNode->getValue()))
        if(instr->getOpcodeName() == std::string("store") && !baseNode->getFlag())
            writeNodes.push_back((DFGWriteNode*)baseNode);

    baseNode->setFlag(true);
    
    for(DFGNode* succ : baseNode->getSuccessors())
        if(!succ->getFlag())
            descendAndCollectWrites(succ,writeNodes);
    
    for(DFGNode* pred : baseNode->getPredecessors())
        if(!pred->getFlag())
            collectWriteNodes(pred,writeNodes);  
}

void DFG::descendAndCollectWrites(DFGNode* node, std::vector<DFGWriteNode*> &writeNodes){
    
    DFGNode* startingNode = node;

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
            }
    if(startingNode != node)
        collectWriteNodes(startingNode,writeNodes);
    else
    {
        if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(startingNode->getValue()))
            if(instr->getOpcodeName() == std::string("store") && !startingNode->getFlag())
                writeNodes.push_back((DFGWriteNode*)startingNode);
        startingNode->setFlag(true);
    }
            
} 

std::vector<DFGReadNode*> DFG::getUniqueReadNodes(DFGNode* baseNode){
    
    std::vector<DFGReadNode*> readNodes;
    std::vector<DFGReadNode*> uniqueReadNodes;
    
    getReadNodes(baseNode,readNodes);
    
    for(DFGReadNode* node : readNodes){
        for(DFGReadNode* n : readNodes)
        {
            if(node->getReadingStream() == n->getReadingStream() &&
                (node->getName() != n->getName()))
            {
                n->setName(node->getName());
            }
        }
    }
    
    //fill the uniqueReadNodes vector
    for(DFGReadNode* node : readNodes)
    {
        bool isUnique = true;
        
        for(DFGReadNode* n : uniqueReadNodes)
            if(node->getName() == n->getName())
                isUnique = false;
                
        if(isUnique)
            uniqueReadNodes.push_back(node);
    }

    return uniqueReadNodes;
}

std::vector<DFGWriteNode*> DFG::getUniqueWriteNodes(DFGNode* baseNode){
    
    std::vector<DFGWriteNode*> writeNodes;
    std::vector<DFGWriteNode*> uniqueWriteNodes;
    
    getWriteNodes(baseNode,writeNodes);
    
    for(DFGWriteNode* node : writeNodes){
        for(DFGWriteNode* n : writeNodes)
        {
            if(node->getWritingStream() == n->getWritingStream() &&
                (node->getName() != n->getName()))
            {
                n->setName(node->getName());
            }
        }
    }
    
    //fill the uniqueReadNodes vector
    for(DFGWriteNode* node : writeNodes)
    {
        bool isUnique = true;
        
        for(DFGWriteNode* n : uniqueWriteNodes)
            if(node->getName() == n->getName())
                isUnique = false;
                
        if(isUnique)
            uniqueWriteNodes.push_back(node);
    }

    return uniqueWriteNodes;
}

std::vector<DFGNode*> DFG::getScalarArguments(DFGNode* baseNode){
    
    int startingPos = 0;
    std::vector<DFGNode*> sortedNodes(getNodesCount());
    std::vector<DFGNode*> scalarArgs;
    
    resetFlags(baseNode);
    orderNodes(baseNode,startingPos,sortedNodes);
    
    for(DFGNode* n : sortedNodes)
    {
        if(llvm::dyn_cast<llvm::Argument>(n->getValue()))
        {
            scalarArgs.push_back(n);
        }
    }
    
    return scalarArgs;
}

std::vector<DFGNode*> DFG::getUniqueScalarArguments(DFGNode* baseNode){
    
    std::vector<DFGNode*> scalarArguments;
    std::vector<DFGNode*> uniqueScalarArguments;
    
    scalarArguments = getScalarArguments(baseNode);
    
    for(DFGNode* node : scalarArguments){
        for(DFGNode* n : scalarArguments)
        {
            if(node->getValue() == n->getValue() &&
                (node->getName() != n->getName()))
            {
                n->setName(node->getName());
            }
        }
    }
    
    //fill the uniqueReadNodes vector
    for(DFGNode* node : scalarArguments)
    {
        bool isUnique = true;
        
        for(DFGNode* n : uniqueScalarArguments)
            if(node->getName() == n->getName())
                isUnique = false;
                
        if(isUnique)
            uniqueScalarArguments.push_back(node);
    }

    return uniqueScalarArguments;
}

int DFG::getNodesCount(){
    
    int count = 0;
    DFG::resetFlags(DFG::endNode);
    
    count = DFG::countChildren(DFG::endNode,count);

    return count;
}

void DFG::resetFlags(DFGNode* node){
    
    node->setFlag(false);
    
    for(DFGNode* succ : node->getSuccessors())
        if(succ->getFlag())
            descendAndReset(node);

    for(DFGNode* pred : node->getPredecessors())
        if(pred->getFlag())
            resetFlags(pred);
}

void DFG::descendAndReset(DFGNode* node){

    DFGNode* nodeToReset = node;

    while(nodeToReset->getSuccessors().size() != 0){
        for(DFGNode* succ : nodeToReset->getSuccessors()){
            if(succ->getFlag()){
                nodeToReset = succ;
                break;
            }
        }
    }
    if(nodeToReset != node)
        resetFlags(nodeToReset);
    else
        nodeToReset->setFlag(false);
}

void DFG::setNameVector(std::vector<std::string> &nodeNames, DFGNode* node){
    
    resetFlags(node);
    
    setNames(nodeNames,node);

}

void DFG::setNames(std::vector<std::string> &nodeNames, DFGNode* node){

    if(nodeNames.size() < 1)
    {
        llvm::errs() << "Not enough node names...\n";
        return;
    }
    
    if(!node->getFlag()){
    
        //account for different llvm::Value subtypes

        if(llvm::dyn_cast<llvm::Instruction>(node->getValue()))
        {
            node->setName(nodeNames.back());
            nodeNames.pop_back();
        }
        if(llvm::dyn_cast<llvm::Argument>(node->getValue()))
        {
            node->setName(nodeNames.back());
            nodeNames.pop_back();
        }

        if(llvm::ConstantFP* CFP = llvm::dyn_cast<llvm::ConstantFP>(node->getValue()))
        {
            node->setName(std::to_string(CFP->getValueAPF().convertToFloat()));
            nodeNames.pop_back();
        }

        if(llvm::ConstantInt* CFP = llvm::dyn_cast<llvm::ConstantInt>(node->getValue()))
        {
            node->setName(std::to_string(CFP->getZExtValue()));
            nodeNames.pop_back();
        }

    }
    
    node->setFlag(true);
    
    for(DFGNode* succ : node->getSuccessors())
        if(!succ->getFlag())
            descendAndSetNames(nodeNames,node);
            
    std::vector<DFGNode*> pred = node->getPredecessors();
    std::vector<DFGNode*> revPred(pred.size()); 
    std::reverse_copy(std::begin(pred),std::end(pred),std::begin(revPred));
    
    for(DFGNode* pred : revPred)
        if(!pred->getFlag())
            setNames(nodeNames,pred);
}

void DFG::descendAndSetNames(std::vector<std::string> &nodeNames, DFGNode* node){
    
    DFGNode* nodeToSet = node;

    while(nodeToSet->getSuccessors().size() != 0){
        for(DFGNode* succ : nodeToSet->getSuccessors()){
            if(!succ->getFlag()){
                nodeToSet = succ;
                break;
            }
        }
    }
    if(nodeToSet != node)
        setNames(nodeNames, nodeToSet);
    else
        if(!nodeToSet->getFlag()){
            
            if(llvm::dyn_cast<llvm::Instruction>(node->getValue()))
            {
                node->setName(nodeNames.back());
                nodeNames.pop_back();
            }
            if(llvm::dyn_cast<llvm::Argument>(node->getValue()))
            {
                node->setName(nodeNames.back());
                nodeNames.pop_back();
            }

            if(llvm::ConstantFP* CFP = llvm::dyn_cast<llvm::ConstantFP>(node->getValue()))
            {
                node->setName(std::to_string(CFP->getValueAPF().convertToFloat()));
                nodeNames.pop_back();
            }

            if(llvm::ConstantInt* CFP = llvm::dyn_cast<llvm::ConstantInt>(node->getValue()))
            {
                node->setName(std::to_string(CFP->getZExtValue()));
                nodeNames.pop_back();
            }
            nodeToSet->setFlag(true);
        }
}

void DFG::printDFG(DFGNode* startingNode){
    
    startingNode->printNode();
    startingNode->setFlag(true);
    
    for(DFGNode* succ : startingNode->getSuccessors())
        if(!succ->getFlag())   
            descendAndPrint(startingNode);
    
    for(DFGNode* pred : startingNode->getPredecessors())
        if(!pred->getFlag())
            printDFG(pred);
}

void DFG::printDFG(){
    
    llvm::errs() << "\n--------PRINTING DFG----------\n";
    
    DFG::resetFlags(endNode);
    endNode->printNode();
    endNode->setFlag(true);
 
    for(DFGNode* pred : endNode->getPredecessors())
        printDFG(pred);
}

void DFG::descendAndPrint(DFGNode* node){
    
    DFGNode* nodeToPrint = node;

    while(nodeToPrint->getSuccessors().size() != 0)
        for(DFGNode* succ : nodeToPrint->getSuccessors())
            if(!succ->getFlag()){
                nodeToPrint = succ;
                break;
            }
    if(nodeToPrint != node)
        printDFG(nodeToPrint);
            
}

int DFG::countChildren(DFGNode* node, int count){

    if(!node->getFlag())
        count++;
        
    node->setFlag(true);
    
    for(DFGNode* succ : node->getSuccessors())
        if(!succ->getFlag())
            count = descendAndCount(node,count);

    for(DFGNode* pred : node->getPredecessors())
        if(!pred->getFlag())
            count = countChildren(pred,count);
            
    return count;
}

int DFG::descendAndCount(DFGNode* node, int count){
    
    DFGNode* startingNode = node;

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
            }
    if(startingNode != node)
        count = countChildren(startingNode,count);
    else
        if(!startingNode->getFlag()){
            startingNode->setFlag(true);
            count++;
        }
        
    return count;
}

//DFGConstructor methods implementation

DFG* DFGConstructor::computeIOStreamBasedDFG(llvm::Loop* topLevelLoop, llvm::Function* F, IOStreams* IOs){

    std::vector<DFG*> computedDFGs;
    
    //iterates over the loop body instructions

        for(llvm::BasicBlock *BB : topLevelLoop->blocks()){
            if(BB != topLevelLoop->getHeader() &&
                BB != topLevelLoop->getLoopLatch()){
                
                for(llvm::Instruction &instr : BB->getInstList()){
                    
                    //if a store is found, and the store refers to an output stream,
                    //a DFG is computed with the store as its base, and it is added 
                    //to the DFG vector
                    if(instr.getOpcodeName() == std::string("store")){
                        if(llvm::Instruction* storeAddr = llvm::dyn_cast<llvm::Instruction>(instr.getOperand(1)))
                            for(llvm::Value* outStream : IOs->getOutputStreams()){
                                if(storeAddr->getOperand(0) == outStream ||
                                    llvm::dyn_cast<llvm::Instruction>(storeAddr->getOperand(0))->getOpcodeName() == std::string("alloca")){
                                    computedDFGs.push_back(computeDFGFromBase(new DFGWriteNode(&instr,IOs),topLevelLoop, IOs));
                                }
                            }
                    }
                }
            }
        }
    
    if(computedDFGs.size() > 1){
        DFGConstructor::scheduler->schedule(new DFGLinker(computedDFGs));
        DFGConstructor::scheduler->executeNextComponent();
        
        return DFGConstructor::scheduler->dataflowGraph;
        
    }else{
        llvm::errs() << "Single DFG during loop dfg construction...\n";
        return computedDFGs.at(0);
    }
}

void DFGConstructor::populateDFG(DFGNode* node,llvm::Loop* loop, IOStreams* IOs){
    
    llvm::Value* parentVal = node->getValue();

    if(llvm::Instruction* parentInstr = llvm::dyn_cast<llvm::Instruction>(parentVal)){
        
        for(llvm::Value* operandVal : parentInstr->operands()){
            
            if(llvm::Instruction* operandAsInstr = llvm::dyn_cast<llvm::Instruction>(operandVal))
            {
                //these checks identify a DFGReadNode which accesses a stream
                //through the exact value of the canonical induction variable
                //at any given iteration
                if(operandAsInstr->getOpcodeName() == std::string("load"))
                {
                    llvm::Instruction* getelemPtrInstr = getInstrFromOperand(
                        operandAsInstr->getOperand(0), std::string("getelementptr"));
                    
                    if(getelemPtrInstr != nullptr && (hasSextOnIndvar(getelemPtrInstr,loop) ||
                    getelemPtrInstr->getOperand(1) == loop->getCanonicalInductionVariable()))
                    {
                        DFGReadNode* childNode = new DFGReadNode(operandVal,IOs);
                        node->linkPredecessor(childNode);
                    }
                }
                else
                {
                    //Node initialization for a generic instruction
                    DFGNode* childNode = new DFGNode(operandVal);
                    node->linkPredecessor(childNode);
                        
                    populateDFG(childNode,loop,IOs);
                    
                }
            }
            else
            {
                //Node initializaton for a generic llvm::Value which is not an 
                //instruction
                DFGNode* childNode = new DFGNode(operandVal);
                node->linkPredecessor(childNode);
            }
        }
    }
    else
    {
        llvm::errs() << "Non instr parent\n";
        return;
    }
    
}

DFG* DFGConstructor::computeDFGFromBase(DFGWriteNode* baseNode,llvm::Loop* loop, IOStreams* IOs){
        
    //intializes a new DFG object 
    DFG* graph = new DFG(baseNode);
    //populates it from its base node
    populateDFG(shortcutSoreGetelementPtr(baseNode),loop,IOs);
    
    return graph;
}

llvm::Instruction* DFGConstructor::getInstrFromOperand(llvm::Value* value, std::string opcodeName){
        
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value))
        if(instr->getOpcodeName() == opcodeName)
            return instr;
    return nullptr;
}

DFGNode* DFGConstructor::shortcutSoreGetelementPtr(DFGWriteNode* storeNode){
            
            llvm::Instruction* storeInstr = (llvm::Instruction*) storeNode->getValue();
            DFGNode* startingNode = new DFGNode(storeInstr->getOperand(0));
            storeNode->linkPredecessor(startingNode);
            return startingNode;
}

bool DFGConstructor::hasSextOnIndvar(llvm::Instruction* instr,llvm::Loop* loop){
        
    for(llvm::Value* operand : instr->operands()){
        
        if(llvm::Instruction* childInstr = llvm::dyn_cast<llvm::Instruction>(operand)){
            if(childInstr->getOperand(0) == loop->getCanonicalInductionVariable() &&
                childInstr->getOpcodeName() == std::string("sext"))
                return true;
        }
    }
    return false;
}

//DFGLinker methods implementation

DFG* DFGLinker::linkDFG(){
    
    std::vector<DFGNode*>  nodesOrder;
    std::vector<DFGReadNode*> readNodes;
    std::vector<DFGWriteNode*> writeNodes;
    int baseSize = 0;
    
    for(DFG* dfg : DFGLinker::dfgs)
    {
        int graphSize = dfg->getNodesCount();
        DFGNode* base = dfg->getEndNode();
        std::vector<DFGReadNode*> rNodes;
        std::vector<DFGWriteNode*> wNodes;
        std::vector<DFGNode*> sortedNodes(graphSize);
        
        dfg->getWriteNodes(base,wNodes);
        dfg->getReadNodes(base,rNodes);
        
        dfg->resetFlags(dfg->getEndNode());

        dfg->orderNodes(dfg->getEndNode(),baseSize,sortedNodes,baseSize);
        
        nodesOrder.insert(nodesOrder.end(),sortedNodes.begin(),sortedNodes.end());

        baseSize += graphSize;
        
        readNodes.insert(readNodes.end(),rNodes.begin(),rNodes.end());
        writeNodes.insert(writeNodes.end(),wNodes.begin(),wNodes.end());
        
    }

    for(int i = 0; i < nodesOrder.size(); i++)
    {
        if(std::find(readNodes.begin(), readNodes.end(), nodesOrder.at(i)) != readNodes.end())
        {
            DFGReadNode* readNode = (DFGReadNode*)(nodesOrder.at(i));
            
            for(int j = i-1; j >= 0; j--)
            {
                if(std::find(writeNodes.begin(), writeNodes.end(), nodesOrder.at(j)) != writeNodes.end())
                {  
                    DFGWriteNode* writeNode = (DFGWriteNode*)nodesOrder.at(j);
                    
                    if(readNode->getReadingStream() == writeNode->getWritingStream()){
                        
                        DFGNode * readSucc = readNode->getSuccessors().at(0);   //assumes that reads have one successor
                        std::vector<DFGNode*> &linkedNodes = readSucc->getPredecessors();
                        
                        int pos = std::find(linkedNodes.begin(),linkedNodes.end(),readNode)-linkedNodes.begin();
                        
                        readSucc->linkPredecessor(writeNode->getPredecessors().at(0),pos);
                        linkedNodes.erase(linkedNodes.begin() + pos+1);
                        j = 0;
                    }
                }
            }
        }
    }
    llvm::errs() << "Linked graph: \n";

    DFGLinker::dfgs.back()->printDFG();

    return DFGLinker::dfgs.back();
}

void DFG::orderNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted,int baseSize){
    
    bool hasPred = false;
    
    for(DFGNode* pred : n->getPredecessors())
        if(!pred->getFlag())
            hasPred = true;
            
    if(!n->getFlag() && !hasPred){
        n->setPosition(pos);
        sorted.at(pos-baseSize) = n;
        n->setFlag(true);
        pos++;

    }else{
        for(DFGNode* pred : n->getPredecessors()){
            if(!pred->getFlag()){
                orderNodes(pred,pos,sorted,baseSize);
            }
        }
    }
    
    for(DFGNode* succ : n->getSuccessors()){
        if(!succ->getFlag()){
            orderNodes(succ,pos,sorted,baseSize);
        }
    }
    
} 