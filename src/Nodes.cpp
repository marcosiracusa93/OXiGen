
#include "llvm-c/Core.h"
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
            if(((Instruction*)(instr->getOperand(1)))->getOperand(0) == stream){

                writingStream = stream;
                errs() << "WriteStream found\n";
            }   
        }
    }
}

///DFGReadNode methods implementation

DFGReadNode::DFGReadNode(Value* value, Utils::IOStreams* loopStreams) : DFGNode(value) {
    
    for(Value* stream : loopStreams->getInputStreams()){
        if(Instruction* instr = dyn_cast<Instruction>(value))
            if(((Instruction*)(instr->getOperand(0)))->getOperand(0) == stream){
                
                sourceStream = stream;
                errs() << "SourceStream found\n";
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
            pred->getValue()->dump();
            count++;
            pred->setFlag(true);
        }
        
        if(pred->getPredecessors().size() > 0)
            count = DFG::countChildren(pred,count);
    }
    return count;
}

void DFG::setNameVector(std::vector<std::string> &nodeNames, DFGNode* node){
    
    if(nodeNames.size() < 1)
    {
        errs() << "Not enough node names...\n";
        return;
    }
    
    node->setName(nodeNames.back());
    nodeNames.pop_back();
    
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
    
    errs() << "\n--------PRINTING DFG----------\n";
    endNode->printNode();
 
    for(DFGNode* pred : endNode->getPredecessors())
        printDFG(pred);
}

