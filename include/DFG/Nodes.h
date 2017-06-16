#ifndef NODES_H
#define NODES_H

#include "Utils/IOStreams.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace SimpleDFG {
    
    class DFGNode{
    
    private:
        Value* node;
        std::vector<DFGNode*> predecessors;
        DFGNode* successor;
        
    public:
        DFGNode(Value* value){ this->node = value;} 
        
        Value* getValue(){ return node; }

        std::vector<DFGNode*> getPredecessors(){ return predecessors; }
        
        DFGNode* getSuccessor(){ return successor; }
        
        void linkPredecessor(DFGNode* pred){
            predecessors.push_back(pred);
            pred->setSuccessor(this);
        }
        
        void setSuccessor(DFGNode* succ){ successor = succ; }
        
        void printNode();
        
    };
    
    class DFGWriteNode : public DFGNode {
    
    private:
        
        Value* writingStream;
        
    public:
        
        DFGWriteNode(Value* value, Utils::IOStreams* loopStreams);
        
        Value* getWritingStream(){ return writingStream; }
    };
    
    class DFGReadNode : public DFGNode {
    
    private:
        
        Value* sourceStream;
        
    public:
        
        DFGReadNode(Value* value, Utils::IOStreams* loopStreams);
        
        Value* getReadingStream(){ return sourceStream; }
    };
        
    class DFG{
    
    private:
        DFGNode* endNode;
        
    public:
    
        DFG(DFGNode* initNode){ this->endNode = initNode; }
        
        DFGNode* getEndNode(){ return endNode; }
        
        void printDFG(DFGNode* startingNode);
        
        void printDFG();
        
    };

}

#endif