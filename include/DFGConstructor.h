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
        std::vector<DFGNode*> successors;
        
        std::string name;
        bool markedFlag;
        int position;
        
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

        std::vector<DFGNode*> &getPredecessors(){ return predecessors; }
        
        std::vector<DFGNode*> getSuccessors(){ return successors; }
        
        std::string getName() { return name; }
        
        bool getFlag() { return markedFlag; }
        
        int getPosition() { return position; }
        
        //setter methods for the class
        
        void setName(std::string name){ this->name = name; }
        
        void setPosition(int pos) { this->position = pos; }
        
        void setFlag(bool value){ this->markedFlag = value; }

        void setSuccessor(DFGNode* succ){ successors.push_back(succ); }
        
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
        
        void linkPredecessor(DFGNode* pred, int pos){
            predecessors.insert(predecessors.begin()+pos,pred);
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
         */
        void getReadNodes(DFGNode* baseNode,std::vector<DFGReadNode*> &readNodes);
        
        /**
         * @brief Used to retrieve the DFGWriteNode in this graph. It
         *        actually just searches for 'store' operations and then
         *        attempts to cast the DFGNode wrapper object to a 
         *        DFGWriteNode. Therefore it should only be used when
         *        it is safe to do so.
         * 
         * @param baseNode - the base node of this graph
         */
        void getWriteNodes(DFGNode* baseNode,std::vector<DFGWriteNode*> &writeNodes);
        
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
        
        std::vector<DFGWriteNode*> getUniqueWriteNodes(DFGNode* baseNode);
        
        /**
         * @brief Returns the DFGNodes containing llvm::Arguments as values
         * @param baseNode - the base node for this graph
         * @return a srd::vector of DFGNodes containing llvm::Arguments as values
         */
        std::vector<DFGNode*> getScalarArguments(DFGNode* baseNode);
        
        std::vector<DFGNode*> getUniqueScalarArguments(DFGNode* baseNode);
        
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
        
        void descendAndPrint(DFGNode* node);
        
        /**
         * @brief Set all the markedFlag fields of the nodes to false, starting
         *        from the DFGNode passed as a parameter, whihch acts as root
         *
         * @param node - the DFGNode acting as root
         */
        void resetFlags(DFGNode* node);
        
        void orderNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted, int baseSize=0);

        void setDFGFlags();
    
    private:
        
        /**
         * @brief Recursive method used in the count of the nodes of a DFG
         */
        int countChildren(DFGNode* parent, int count);

        int descendAndCount(DFGNode* node, int count);
        
        void descendAndReset(DFGNode* node);
        
        void collectReadNodes(DFGNode* baseNode,std::vector<DFGReadNode*> &readNodes);
        
        void descendAndCollectReads(DFGNode* node, std::vector<DFGReadNode*> &readNodes);
        
        void collectWriteNodes(DFGNode* baseNode,std::vector<DFGWriteNode*> &writeNodes);
        
        void descendAndCollectWrites(DFGNode* node, std::vector<DFGWriteNode*> &writeNodes);
        
        void setNames(std::vector<std::string> &nodeNames, DFGNode* node);
        
        void descendAndSetNames(std::vector<std::string> &nodeNames, DFGNode* node);

        void setFlags(DFGNode *node);

        void descendAndSet(DFGNode* node);
        
    };
    
    /**
     * @class DFGLinker
     * @author 
     * @date 26/07/17
     * @file DFGConstructor.h
     * @brief 
     */
    class DFGLinker : public ProcessingComponent{
        
    protected:
        std::vector<DFG*> dfgs;
    
    public:
    
        DFGLinker(std::vector<DFG*> dfgs){ this->dfgs = dfgs;
            llvm::errs() << "graphs to link:\n";
        for(DFG* d : dfgs )
            d->printDFG();
        }
        
        void acceptExecutor(ProcessingScheduler* scheduler){
            scheduler->execute(this);
        }
        
        std::vector<DFG*> linkDFG();
           
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
            
            std::vector<DFG*> computeIOStreamBasedDFG(llvm::Loop* topLevelLoop, llvm::Function* F, IOStreams* IOs);
            
        private:

            void populateDFG(DFGNode* node,llvm::Loop* loop, IOStreams* IOs);

            DFG* computeDFGFromBase(DFGWriteNode* baseNode,llvm::Loop* loop, IOStreams* IOs);

            llvm::Instruction* getInstrFromOperand(llvm::Value* value, std::string opcodeName);

            DFGNode* shortcutSoreGetelementPtr(DFGWriteNode* storeNode,IOStreams* IOs);

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