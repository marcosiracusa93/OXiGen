
#include "llvm-c/Core.h"
#include "DFG/Nodes.h"

using namespace llvm;
using namespace SimpleDFG;

///DFGNode methods implementation

void DFGNode::printNode(){
    
    errs() << "Node \n";
    node->dump();
    errs() << "\nPredecessors\n";
    
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

void DFG::printDFG(DFGNode* startingNode){
    
    startingNode->printNode();
 
    for(DFGNode* pred : startingNode->getPredecessors())
        printDFG(pred);
}

void DFG::printDFG(){
    
    endNode->printNode();
 
    for(DFGNode* pred : endNode->getPredecessors())
        printDFG(pred);
}

