#ifndef NODES_H
#define NODES_H

#include "Utils/IOStreams.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace simple_dfg {
    
    class DFGNode{
    
    private:
        Value* node;
        std::vector<DFGNode*> predecessors;
        DFGNode* successor;
        
        std::string name;
        bool markedFlag;
        
    public:
        DFGNode(Value* value){
            this->node = value;
            this->markedFlag = false;
            this->name = "unnamed";
        } 
        
        Value* getValue(){ return node; }

        std::vector<DFGNode*> getPredecessors(){ return predecessors; }
        
        DFGNode* getSuccessor(){ return successor; }
        
        std::string getName() { return name; }
        
        bool getFlag() { return markedFlag; }
        
        void setName(std::string name){ this->name = name; }
        
        void setFlag(bool value){ this->markedFlag = value; }
         
        void linkPredecessor(DFGNode* pred){
            predecessors.push_back(pred);
            pred->setSuccessor(this);
        }
        
        void setSuccessor(DFGNode* succ){ successor = succ; }
        
        void printNode();
        
        int countSubgraphNodes();
        
        friend bool operator==(DFGNode &ln, DFGNode &rn) {
            
            bool hasPred = false;
            
            for(DFGNode* n_1 : ln.getPredecessors())
            {
                for(DFGNode* n_2 : rn.getPredecessors())
                {
                    if(n_1->getName() == n_2->getName())
                        hasPred = true;
                }
                if(hasPred)
                    hasPred = false;
                else
                    return false;
            }
            return (ln.getSuccessor()->getName() == rn.getSuccessor()->getName());
        }

        friend bool operator!=(DFGNode &ln, DFGNode &rn) {
            return !(ln == rn);
        }
        
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
        
        std::vector<DFGReadNode*> getReadNodes(DFGNode* baseNode);
        
        std::vector<DFGWriteNode*> getWriteNodes(DFGNode* baseNode);
        
        std::vector<DFGReadNode*> getUniqueReadNodes(DFGNode* baseNode);
        
        std::vector<DFGNode*> getScalarArguments(DFGNode* baseNode);
        
        int getNodesCount();
        
        void setNameVector(std::vector<std::string> &nodeNames, DFGNode* node);
        
        void printDFG(DFGNode* startingNode);
        
        void printDFG();
    
    private:
    
        int countChildren(DFGNode* parent,int count);
        
        void resetFlags(DFGNode* node);
        
    };

}

#endif