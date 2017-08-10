
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
    
    for(llvm::Value* stream : loopStreams->getOutputStreams()){
        if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){
            if(((llvm::Instruction*)(instr->getOperand(1)))->getOperand(0) == stream)
            {
                writingStream = stream;
            }   
        }
    }
}


///DFGReadNode methods implementation

DFGReadNode::DFGReadNode(llvm::Value* value, IOStreams* loopStreams) : DFGNode(value) {
    
    for(llvm::Value* stream : loopStreams->getInputStreams()){
        if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value))
            if(((llvm::Instruction*)(instr->getOperand(0)))->getOperand(0) == stream)
            {
                sourceStream = stream;
            }
    }
}

///DFG methods implementation

std::vector<DFGReadNode*> DFG::getReadNodes(DFGNode* baseNode){

    std::vector<DFGReadNode*> readNodes;
    
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(baseNode->getValue()))
        if(instr->getOpcodeName() == std::string("load"))
            readNodes.push_back((DFGReadNode*)baseNode);
    
    for(DFGNode* pred : baseNode->getPredecessors())
    {
        std::vector<DFGReadNode*> succReadNodes = getReadNodes(pred);  
        readNodes.insert(readNodes.end(),succReadNodes.begin(),succReadNodes.end());
    }
    
    return readNodes;
}

std::vector<DFGWriteNode*> DFG::getWriteNodes(DFGNode* baseNode){

    std::vector<DFGWriteNode*> writeNodes;
    
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(baseNode->getValue()))
        if(instr->getOpcodeName() == std::string("store"))
            writeNodes.push_back((DFGWriteNode*)baseNode);
    
    for(DFGNode* pred : baseNode->getPredecessors())
    {
        std::vector<DFGWriteNode*> succWriteNodes = getWriteNodes(pred);  
        writeNodes.insert(writeNodes.end(),succWriteNodes.begin(),succWriteNodes.end());
    }
    
    return writeNodes;
}

std::vector<DFGReadNode*> DFG::getUniqueReadNodes(DFGNode* baseNode){
    
    std::vector<DFGReadNode*> readNodes = DFG::getReadNodes(baseNode);
    std::vector<DFGReadNode*> uniqueReadNodes;
    
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

std::vector<DFGNode*> DFG::getScalarArguments(DFGNode* baseNode){
    
    std::vector<DFGNode*> scalarArgs;
    
    //if the llvm::Value is a function argument, add it to the vector
    if(llvm::dyn_cast<llvm::Argument>(baseNode->getValue()))
    {
        scalarArgs.push_back(baseNode);
    }
    
    for(DFGNode* pred : baseNode->getPredecessors())
    {
        std::vector<DFGNode*> predScalarArgs = getScalarArguments(pred);
        scalarArgs.insert(scalarArgs.end(),predScalarArgs.begin(),predScalarArgs.end());
    }
    return scalarArgs;
}

int DFG::getNodesCount(){
    
    int count = 1;

    DFG::endNode->setFlag(true);
    
    count = DFG::countChildren(DFG::endNode,count);
    
    DFG::resetFlags(DFG::endNode);

    return count;
}

void DFG::resetFlags(DFGNode* node){
    
    node->setFlag(false);
    
    for(DFGNode* pred : node->getPredecessors())
        resetFlags(pred);
}

void DFG::setNameVector(std::vector<std::string> &nodeNames, DFGNode* node){
    
    if(nodeNames.size() < 1)
    {
        llvm::errs() << "Not enough node names...\n";
        return;
    }
    
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
    
    for(DFGNode* pred : node->getPredecessors())
    {
        DFG::setNameVector(nodeNames,pred);
    }       
}

void DFG::printDFG(DFGNode* startingNode){
    
    startingNode->printNode();
 
    for(DFGNode* pred : startingNode->getPredecessors())
        printDFG(pred);
}

void DFG::printDFG(){
    
    llvm::errs() << "\n--------PRINTING DFG----------\n";
    endNode->printNode();
 
    for(DFGNode* pred : endNode->getPredecessors())
        printDFG(pred);
}

int DFG::countChildren(DFGNode* parent, int count){
        
    for(DFGNode* pred : parent->getPredecessors())
    {
        if(!pred->getFlag())
        {
            count++;
            pred->setFlag(true);
        }
        
        if(pred->getPredecessors().size() > 0)
            count = DFG::countChildren(pred,count);
    }
    return count;
}

//DFGConstructor methods implementation

DFG* DFGConstructor::computeIOStreamBasedDFG(llvm::Loop* topLevelLoop, llvm::Function* F, IOStreams* IOs){
    
    std::vector<DFG*> computedDFGs;
    
    //iterates over the loop body instructions
    for(llvm::Value* outStream : IOs->getOutputStreams()){

        for(llvm::BasicBlock *BB : topLevelLoop->blocks()){
            if(BB != topLevelLoop->getHeader() &&
                BB != topLevelLoop->getLoopLatch()){
                
                for(llvm::Instruction &instr : BB->getInstList()){
                    
                    //if a store is found, and the store refers to an output stream,
                    //a DFG is computed with the store as its base, and it is added 
                    //to the DFG vector
                    if(instr.getOpcodeName() == std::string("store"))
                        if(llvm::Instruction* storeAddr = llvm::dyn_cast<llvm::Instruction>(instr.getOperand(1)))
                            if(storeAddr->getOperand(0) == outStream ){
                                
                                llvm::errs() << "Computing DFG\n";
                                computedDFGs.push_back(computeDFGFromBase(new DFGWriteNode(&instr,IOs),topLevelLoop, IOs));
                            }
                }
            }
        }
    }
    llvm::errs() << "Assumed single DFG during loop dfg construction...\n";
    return computedDFGs.at(0);
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