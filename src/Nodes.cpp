
#include "llvm-c/Core.h"
#include "llvm/IR/Constants.h"
#include "DFG/Nodes.h"

using namespace llvm;
using namespace simple_dfg;

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
    
    errs() << "\nNode: " << name << "\n";
    node->dump();
    errs() << "Predecessors\n";
    
    for(DFGNode* predecessor : predecessors){
        predecessor->getValue()->dump();
    }
}

///DFGWriteNode methods implementation

DFGWriteNode::DFGWriteNode(Value* value, Utils::IOStreams* loopStreams) : DFGNode(value) {
    
    for(Value* stream : loopStreams->getOutputStreams()){
        if(Instruction* instr = dyn_cast<Instruction>(value)){
            if(((Instruction*)(instr->getOperand(1)))->getOperand(0) == stream)
            {
                writingStream = stream;
            }   
        }
    }
}

///DFGReadNode methods implementation

DFGReadNode::DFGReadNode(Value* value, Utils::IOStreams* loopStreams) : DFGNode(value) {
    
    for(Value* stream : loopStreams->getInputStreams()){
        if(Instruction* instr = dyn_cast<Instruction>(value))
            if(((Instruction*)(instr->getOperand(0)))->getOperand(0) == stream)
            {
                sourceStream = stream;
            }
    }
}

///DFG methods implementation

void DFG::resetFlags(DFGNode* node){
    
    node->setFlag(false);
    
    for(DFGNode* pred : node->getPredecessors())
        resetFlags(pred);
}


int DFG::getNodesCount(){
    
    int count = 1;
    
    DFG::endNode->setFlag(true);
    
    count = DFG::countChildren(DFG::endNode,count);
    
    DFG::resetFlags(DFG::endNode);
    
    return count;
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

void DFG::setNameVector(std::vector<std::string> &nodeNames, DFGNode* node,std::vector<DFGReadNode*> &readNodes){
    
    if(nodeNames.size() < 1)
    {
        errs() << "Not enough node names...\n";
        return;
    }
    
    
    if(Instruction* instr = dyn_cast<Instruction>(node->getValue()))
    {
        if(instr->getOpcodeName() == std::string("load")){}
        node->setName(nodeNames.back());
        nodeNames.pop_back();
    }
    
    if(ConstantFP* CFP = dyn_cast<ConstantFP>(node->getValue()))
    {
        node->setName(std::to_string(CFP->getValueAPF().convertToFloat()));
        nodeNames.pop_back();
    }
    
    if(ConstantInt* CFP = dyn_cast<ConstantInt>(node->getValue()))
    {
        node->setName(std::to_string(CFP->getZExtValue()));
        nodeNames.pop_back();
    }
    
    for(DFGNode* pred : node->getPredecessors())
    {
        DFG::setNameVector(nodeNames,pred,readNodes);
    }       
}

std::vector<DFGReadNode*> DFG::getReadNodes(DFGNode* baseNode){

    std::vector<DFGReadNode*> readNodes;
    
    if(Instruction* instr = dyn_cast<Instruction>(baseNode->getValue()))
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
    
    if(Instruction* instr = dyn_cast<Instruction>(baseNode->getValue()))
        if(instr->getOpcodeName() == std::string("store"))
            writeNodes.push_back((DFGWriteNode*)baseNode);
    
    for(DFGNode* pred : baseNode->getPredecessors())
    {
        std::vector<DFGWriteNode*> succWriteNodes = getWriteNodes(pred);  
        writeNodes.insert(writeNodes.end(),succWriteNodes.begin(),succWriteNodes.end());
    }
    
    return writeNodes;
}

void DFG::printDFG(DFGNode* startingNode){
    
    startingNode->printNode();
 
    for(DFGNode* pred : startingNode->getPredecessors())
        printDFG(pred);
}

void DFG::printDFG(){
    
    errs() << "\n--------PRINTING DFG----------\n";
    endNode->printNode();
 
    for(DFGNode* pred : endNode->getPredecessors())
        printDFG(pred);
}

