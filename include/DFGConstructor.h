#ifndef DFGCONSTRUCTOR_H
#define DFGCONSTRUCTOR_H

#include "llvm/Support/raw_ostream.h"
#include "StreamsAnalyzer.h"
#include "AnalysisManager.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen{
    
    /**
     * @class DFGNode
     * @brief Basic component of a DataFlow graph structure. Is a simple
     *        node containing a llvm::Value, which has a std::vector of
     *        DFGNode pointers as predecessor, and a DFGNode pointer as
     *        successor. It also has a name, expressed as a std::string,
     *        which evaluates to "unnamed" if it has not been modified.
     *        A boolean markedFlag parameter is used in some graph-related
     *        argorithms whithin the program
     */
    class DFGNode{
    
    private:
        llvm::Value* node;
        std::vector<DFGNode*> predecessors;
        DFGNode* successor;
        
        std::string name;
        bool markedFlag;
        
    public:
        
        /**
         * @brief Constructor for the DFGNode class. 
         * @param value - the llvm::Value which this node of the graph contains
         */
        DFGNode(llvm::Value* value){
            this->node = value;
            this->markedFlag = false;
            this->name = "unnamed";
        } 
        
        //getter methods for the class
        
        llvm::Value* getValue(){ return node; }

        std::vector<DFGNode*> getPredecessors(){ return predecessors; }
        
        DFGNode* getSuccessor(){ return successor; }
        
        std::string getName() { return name; }
        
        bool getFlag() { return markedFlag; }
        
        //setter methods for the class
        
        void setName(std::string name){ this->name = name; }
        
        void setFlag(bool value){ this->markedFlag = value; }

        void setSuccessor(DFGNode* succ){ successor = succ; }
        
        /**
         * @brief Method used to set a predecessor to this DFGNode,
         *        while simultaneously setting this node as that
         *        node's successor
         * 
         * @param pred - the DFGNode to link to this node
         */
        void linkPredecessor(DFGNode* pred){
            predecessors.insert(predecessors.begin(),pred);
            pred->setSuccessor(this);
        }
        
        /**
         * @brief Prints the llvm::Value of this node and that of
         *        its predecessors. Should only be used as debug 
         *        info
         */
        void printNode();
        
        /**
         * @brief Recursive method which counts the nodes of the
         *        subgraph having this node as it's root
         * 
         * @return the number of nodes in the subgraph
         */
        int countSubgraphNodes();
        
        /**
         * @brief Implementation of the '==' operator for the class.
         *        Equality is evaluated on the node names of
         *        its predecessors and successor. Therefore it should
         *        only be used after node names in the graph have been
         *        properely initialized
         * 
         * @param ln - lefthand side operand
         * @param rn - righthand side operand
         * @return true if equality is verified, false otherwise
         */
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
        
        /**
         * @brief Implementation of the '!=' operator for the class.
         *        Inequality is evaluated on the node names of
         *        its predecessors and successor. Therefore it should
         *        only be used after node names in the graph have been
         *        properely initialized
         * 
         * @param ln - lefthand side operand
         * @param rn - righthand side operand
         * @return true if inequality is verified, false otherwise
         */
        friend bool operator!=(DFGNode &ln, DFGNode &rn) {
            return !(ln == rn);
        }
        
    };
    
    /**
     * @class DFGWriteNode
     * @brief DFGNode which represents a write node in the DataFlow graph, corresponding
     *        to a store operation which has as argument a pointer to the value of an 
     *        output stream. In addition to the node's value, it also contains the
     *        llvm::Value of its corresponding output stream
     */
    class DFGWriteNode : public DFGNode {
    
    private:
        
        llvm::Value* writingStream;
        
    public:
        
        /**
         * @brief Constructor for the DFGWriteNode class, takes as parameters
         *        the llvm::Value of this node, as well as an IOStreams pointer,
         *        which is used to verify whether the value of the node actually
         *        refers to a store operation on one of the loop's output
         *        streams
         * 
         * @param value - the llvm::Value of this node
         * @param loopStreams pointer to a IOStreams object corresponding to the
         *        input and output streams for a loop
         */
        DFGWriteNode(llvm::Value* value, IOStreams* loopStreams);
        
        //getter for the writingStream of this node
        llvm::Value* getWritingStream(){ return writingStream; }
    };
    
    /**
     * @class DFGReadNode
     * @brief DFGNode which represents a read node in the DataFlow graph, corresponding
     *        to a load operation which has as argument a pointer to the value of an 
     *        input stream. In addition to the node's value, it also contains the
     *        llvm::Value of its corresponding input stream
     */
    class DFGReadNode : public DFGNode {
    
    private:
        
        llvm::Value* sourceStream;
        
    public:
        
        /**
         * @brief Constructor for the DFGReadNode class, takes as parameters
         *        the llvm::Value of this node, as well as an IOStreams pointer,
         *        which is used to verify whether the value of the node actually
         *        refers to a load operation on one of the loop's input
         *        streams
         * 
         * @param value - the llvm::Value of this node
         * @param loopStreams pointer to a IOStreams object corresponding to the
         *        input and output streams for a loop
         */
        DFGReadNode(llvm::Value* value, IOStreams* loopStreams);
        
        //getter for the sourceStream of this node
        llvm::Value* getReadingStream(){ return sourceStream; }
    };
      
    /**
     * @class DFG
     * @brief Class representing a DataFlow graph in the program. It acts as a
     *        wrapper for the DFGNode at the root of the graph (used to initialize
     *        the graph) and offers different service methods to perform operations
     *        on the graph
     */
    class DFG{
    
    private:
        DFGNode* endNode;
        
    public:
        
        /**
         * @brief Constructor for the DFG class, initializes the endNode field
         * @param initNode - DFGNode pointer acts as the root node for the graph
         */
        DFG(DFGNode* initNode){ this->endNode = initNode; }
        
        //getter for the root node of this graph
        DFGNode* getEndNode(){ return endNode; }
        
        /**
         * @brief Used to retrieve the DFGReadNodes in this graph. It
         *        actually just searches for 'load' operations and then
         *        attempts to cast the DFGNode wrapper object to a 
         *        DFGReadNode. Therefore it should only be used when
         *        it is safe to do so.
         * 
         * @param baseNode - the base node of this graph
         * @return a std::vector containing pointers to the DFGReadNodes
         *         of this graph
         */
        std::vector<DFGReadNode*> getReadNodes(DFGNode* baseNode);
        
        /**
         * @brief Used to retrieve the DFGWriteNode in this graph. It
         *        actually just searches for 'store' operations and then
         *        attempts to cast the DFGNode wrapper object to a 
         *        DFGWriteNode. Therefore it should only be used when
         *        it is safe to do so.
         * 
         * @param baseNode - the base node of this graph
         * @return a std::vector containing pointers to the DFGWriteNode
         *         of this graph
         */
        std::vector<DFGWriteNode*> getWriteNodes(DFGNode* baseNode);
        
        /**
         * @brief This method used the DFG::getReadNodes method to retrieve
         *        the DFGReadNodes of this graph, and then performs a check
         *        on thier names, making sure that two nodes referring to the
         *        same input streams have the same name, otherwise their name is
         *        set as the name of the first node. Then it eliminates the
         *        nodes with duplicate names in the vector
         * 
         * @param baseNode - the base node of this graph
         * @return a std::vector of DFGReadNodes with unique names 
         */
        std::vector<DFGReadNode*> getUniqueReadNodes(DFGNode* baseNode);
        
        /**
         * @brief Returns the DFGNodes containing llvm::Arguments as values
         * @param baseNode - the base node for this graph
         * @return a srd::vector of DFGNodes containing llvm::Arguments as values
         */
        std::vector<DFGNode*> getScalarArguments(DFGNode* baseNode);
        
        /**
         * @brief Counts the number of nodes in this graph
         *        WARNING: does not work for a non-tree graph
         * 
         * @return the number of nodes in the graph 
         */
        int getNodesCount();
        
        /**
         * @brief Uses a std::vector of names to assign names to the nodes in the
         *        graph recursively
         * 
         * @param nodeNames - a std::vector of std::strings
         * @param node - the starting node for the given call to this method
         */
        void setNameVector(std::vector<std::string> &nodeNames, DFGNode* node);
        
        void printDFG(DFGNode* startingNode);

        void printDFG();
    
    private:
        
        /**
         * @brief Recursive method used in the count of the nodes of a DFG
         */
        int countChildren(DFGNode* parent, int count);
        
        /**
         * @brief Set all the markedFlag fields of the nodes to false, starting
         *        from the DFGNode passed as a parameter, whihch acts as root
         *
         * @param node - the DFGNode acting as root
         */
        void resetFlags(DFGNode* node);
        
    };
    
    /**
     * @class DFGLinker
     * @author 
     * @date 26/07/17
     * @file DFGConstructor.h
     * @brief 
     */
    class DFGLinker : public ProcessingComponent{
        
    private:
        std::vector<DFG*> dfgs;
    
    public:
    
        DFGLinker(std::vector<DFG*> dfgs){ this->dfgs = dfgs; }
        
        void acceptExecutor(ProcessingScheduler* scheduler){
            scheduler->execute(this);
        }
        
        DFG* linkDFG(llvm::LoopInfo* LI, 
                        llvm::ScalarEvolution* SE,
                        std::vector<IOStreams*> ioStreams){
            
            std::map<int,DFGNode*> nodesOrder;
            std::vector<DFGReadNode*> readNodes;
            std::vector<DFGWriteNode*> writeNodes;
            int baseSize = 0;
            
            for(DFG* dfg : dfgs)
            {
                int graphSize = dfg->getNodesCount();
                DFGNode* base = dfg->getEndNode();
                std::vector<DFGReadNode*> rNodes = dfg->getReadNodes(base);
                std::vector<DFGWriteNode*> wNodes = dfg->getWriteNodes(base);
                llvm::errs() << "Read nodes single graph\n";
                for(DFGNode* n : rNodes){ n->getValue()->dump();}
                llvm::errs() << "Write nodes single graph\n";
                for(DFGNode* n : wNodes){ n->getValue()->dump();}
                
                mapNode(nodesOrder,dfg->getEndNode(),baseSize+graphSize-1);
                
                baseSize += graphSize;
                
                readNodes.insert(readNodes.end(),rNodes.begin(),rNodes.end());
                writeNodes.insert(writeNodes.end(),wNodes.begin(),wNodes.end());
            }
            llvm::errs() << "Read nodes\n";
            for(DFGNode* n : readNodes){ n->getValue()->dump();}
            
            for(int i = 0; i < nodesOrder.size(); i++)
            {
                if(std::find(readNodes.begin(), readNodes.end(), nodesOrder.at(i)) != readNodes.end())
                {
                    DFGReadNode* readNode = (DFGReadNode*)(nodesOrder.at(i));
                    llvm::errs() << "Considering "; readNode->getValue()->dump();
                    
                    for(int j = i-1; j >= 0; j--)
                    {
                        
                        if(std::find(writeNodes.begin(), writeNodes.end(), nodesOrder.at(j)) != writeNodes.end())
                        {
                            DFGWriteNode* writeNode = (DFGWriteNode*)nodesOrder.at(j);
                            
                            if(readNode->getReadingStream() == writeNode->getWritingStream()){
                                
                                DFGNode * readSucc = readNode->getSuccessor();
                                readSucc->linkPredecessor(writeNode->getPredecessors().at(0));
                                
                                std::vector<DFGNode*> linkedNodes = readSucc->getPredecessors();
                                
                                int pos = std::find(linkedNodes.begin(),linkedNodes.end(),readNode)-linkedNodes.begin();
                                llvm::errs() << "Node to remove: "; linkedNodes.at(pos)->getValue()->dump();
                                linkedNodes.erase(linkedNodes.begin() + pos);
                                readNode->setSuccessor(nullptr);
                                j = 0;
                            }
                        }
                    }
                }
            }
            
            dfgs.back()->printDFG();

            return dfgs.at(0);
        }
        
    private:
         
        void mapNode(std::map<int,DFGNode*> &nodeMap, DFGNode* node,int pos)
        {
            
            nodeMap.insert(std::pair<int,DFGNode*>(pos,node));
            
            for(int i = 0; i < node->getPredecessors().size(); i++)
            {
                mapNode(nodeMap,node->getPredecessors().at(i),pos-i-1);
            }
        }
            
    };
    
    /**
     * @class DFGConstructor
     * @author 
     * @date 26/07/17
     * @file DFGConstructor.h
     * @brief 
     */
    class DFGConstructor : public ProcessingComponent{
        
        protected:
        
            ProcessingScheduler* scheduler;
      
        public:
    
            void acceptExecutor(ProcessingScheduler* scheduler){
                this->scheduler = scheduler;
                scheduler->execute(this);
            }
            
            DFG* computeIOStreamBasedDFG(llvm::Loop* topLevelLoop, llvm::Function* F, IOStreams* IOs);
            
        private:

            void populateDFG(DFGNode* node,llvm::Loop* loop, IOStreams* IOs);

            DFG* computeDFGFromBase(DFGWriteNode* baseNode,llvm::Loop* loop, IOStreams* IOs);

            llvm::Instruction* getInstrFromOperand(llvm::Value* value, std::string opcodeName);

            DFGNode* shortcutSoreGetelementPtr(DFGWriteNode* storeNode);

            bool hasSextOnIndvar(llvm::Instruction* instr,llvm::Loop* loop);
    };
    
    /**
     * @class SubloopHandler
     * @author 
     * @date 26/07/17
     * @file DFGConstructor.h
     * @brief 
     */
    class SubloopHandler : public ProcessingComponent{
        
        public:
            DFG* computeSubloop(llvm::Loop &L){
                llvm::errs() << "subloop computation not implemented \n";
                return nullptr;
            } 
    };
    
    /**
     * @class AliasAnalyzer
     * @author 
     * @date 26/07/17
     * @file DFGConstructor.h
     * @brief 
     */
    class AliasAnalyzer{
    
    public:
        bool disambiguate(DFGNode* n_1, DFGNode* n_2, DFGAnalysisResult &R){
            llvm::errs() << "DFG node disambiguation not yet implemented \n";
            return false;
        }
        
    };

} // End OXiGen namespace

#endif