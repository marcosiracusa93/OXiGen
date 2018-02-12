#ifndef DFGCONSTRUCTOR_H
#define DFGCONSTRUCTOR_H

#include "llvm/Support/raw_ostream.h"
#include "StreamsAnalyzer.h"
#include "AnalysisManager.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"


namespace oxigen{

    class DFGLoopNode;

    class TickBasedCondition{

    protected:

        std::string tickName;
        std::string conditionAsString;

    public:

        TickBasedCondition(std::string tickName ){ this->tickName = tickName; }

        std::string getConditionAsString(){ return this->conditionAsString; }
        std::string getTickName(){ return this->tickName; }
    };

    class TickBasedConstantCondition : public TickBasedCondition{

    private:

        int U;
        int L;

    public:

        TickBasedConstantCondition(std::string tickName, int U,int L) : TickBasedCondition(tickName){
            this->U = U;
            this->L = L;
        }

        int getTickLowerBound(){ return this->L; }
        int getTickUpperBound(){ return this->U; }
    };

    enum NodeType { Node =          1,
                    WriteNode =     2,
                    ReadNode =      3,
                    OffsetRead =    4,
                    OffsetWrite =   5,
                    Offset =        6,
                    MuxNode =       7,
                    CounterNode =   8,
                    AccumulNode =   9,
                    LoopNode = 10
    };

    const NodeType ENUM_FIRST = NodeType::Node;
    const NodeType ENUM_LAST = NodeType::LoopNode;

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

    protected:

        NodeType typeID;

        llvm::Value* node;
        std::vector<DFGNode*> predecessors;
        std::vector<DFGNode*> successors;
        std::vector<DFGNode*> loopCarriedPredecessors;
        std::vector<DFGNode*> loopCarriedSuccessors;
        DFGLoopNode* loop;
        
        std::string name;
        bool markedFlag;
        bool isDeclared;
        int position;
        int loopDepth;

        std::pair<int,int> streamWindow; //the window for which this stream will be processed
        int globalDelay;
        
    public:

        NodeType getType(){ return this->typeID; }
        
        /**
         * @brief Constructor for the DFGNode class. 
         * @param value - the llvm::Value which this node of the graph contains
         */
        DFGNode(llvm::Value* value,int loopTripCount = -1){

            this->node = value;
            this->markedFlag = false;
            this->name = "unnamed";
            this->typeID = NodeType::Node;
            this->streamWindow = std::pair<int,int>(0,loopTripCount-1);
            this->predecessors = std::vector<DFGNode*>();
            this->successors = std::vector<DFGNode*>();
            this->globalDelay = 999;
            this->loopDepth = -1;
            this->isDeclared = false;
            this->loop = nullptr;
        }
        
        //getter methods for the class
        
        llvm::Value* getValue();

        std::vector<DFGNode*> &getPredecessors(){ return predecessors; }

        std::vector<DFGNode*> getLoopCarriedSuccessors(){ return loopCarriedSuccessors; }

        std::vector<DFGNode*> getLoopCarriedPredecessors(){ return  loopCarriedPredecessors; }

        std::vector<DFGNode*> getSuccessors(){ return successors; }

        std::vector<DFGNode*> getCrossScopePredecessors();

        std::vector<DFGNode*> getCrossScopeSuccessors();

        int getPredecessorPosition(DFGNode* n);

        int getSuccessorPosition(DFGNode* n);

        std::string getName();

        bool getFlag() { return markedFlag; }

        bool isAlreadyDeclared(){ return isDeclared; }
        
        int getPosition() { return position; }

        int getGlobalDelay() { return this->globalDelay; }

        int getLoopDepth(){ return loopDepth; }

        DFGLoopNode* getLoop(){ return this->loop; }

        void setLoop(DFGLoopNode* loop){ this->loop = loop; }

        std::pair<int,int> getStreamWindow(){ return this->streamWindow; }

        void setStreamWindow(int L,int U){ this->streamWindow = std::pair<int,int>(L,U); }
        
        //setter methods for the class
        
        void setName(std::string name){ this->name = name; }
        
        void setPosition(int pos) { this->position = pos; }

        void setGlobalDelay(int delay){ this->globalDelay = delay; }

        void setLoopDepth(int loopDepth){ this->loopDepth = loopDepth; }
        
        void setFlag(bool value){ this->markedFlag = value; }

        void setIsDeclared(){ this->isDeclared = true; }

        void setSuccessor(DFGNode* succ){
            if(std::find(successors.begin(),successors.end(),succ) == successors.end())
                successors.push_back(succ);
        }
        void setLoopCarriedSuccessor(DFGNode* succ){
            if(std::find(loopCarriedSuccessors.begin(),loopCarriedSuccessors.end(),succ) == loopCarriedSuccessors.end()){
                loopCarriedSuccessors.push_back(succ);
            }
        }
        
        /**
         * @brief Method used to set a predecessor to this DFGNode,
         *        while simultaneously setting this node as that
         *        node's successor
         * 
         * @param pred - the DFGNode to link to this node
         */
        void linkPredecessor(DFGNode* pred){

            bool isDuplicateConstant = false;
            if(predecessors.size() == 0)
                predecessors.push_back(pred);
            else {

                if(llvm::dyn_cast<llvm::Constant>(pred->getValue())){
                    for(DFGNode* p : predecessors){
                        if(p->equals(pred)){
                            isDuplicateConstant = true;
                        }
                    }
                }
                if (std::find(predecessors.begin(), predecessors.end(), pred) == predecessors.end()
                    && !isDuplicateConstant)
                    predecessors.insert(predecessors.begin(), pred);
            }
            if(!isDuplicateConstant)
                pred->setSuccessor(this);
        }

        void linkLoopCarriedPredecessor(DFGNode* pred){

            bool isDuplicateConstant = false;
            if(loopCarriedPredecessors.size() == 0)
                loopCarriedPredecessors.push_back(pred);
            else {

                if(llvm::dyn_cast<llvm::Constant>(pred->getValue())){
                    for(DFGNode* p : loopCarriedPredecessors){
                        if(p->equals(pred)){
                            isDuplicateConstant = true;
                        }
                    }
                }
                if (std::find(loopCarriedPredecessors.begin(), loopCarriedPredecessors.end(), pred)
                    == loopCarriedPredecessors.end() && !isDuplicateConstant)

                    loopCarriedPredecessors.insert(loopCarriedPredecessors.begin(), pred);
            }
            if(!isDuplicateConstant)
                pred->setLoopCarriedSuccessor(this);
        }

        void linkPredecessor(DFGNode* pred,int pos){

            bool isDuplicateConstant = false;
            pred->setSuccessor(this);

            if(llvm::dyn_cast<llvm::Constant>(pred->getValue())) {
                for (DFGNode *p : predecessors) {
                    if (p->equals(pred)) {
                        isDuplicateConstant = true;
                    }
                }
            }

            if (std::find(predecessors.begin(), predecessors.end(), pred) == predecessors.end()
                    && !isDuplicateConstant)
                predecessors.insert(predecessors.begin()+pos,pred);

            if(!isDuplicateConstant)
                pred->setSuccessor(this);
        }

        void forgetSuccessor(int pos){
            successors.erase(successors.begin()+pos);
        }

        void forgetPredecessor(int pos){
            predecessors.erase(predecessors.begin()+pos);
        }

        void unlinkPredecessor(DFGNode* pred){

            std::vector<DFGNode*> predSucc = pred->getSuccessors();

            int predPos = std::find(predecessors.begin(),predecessors.end(),pred)-predecessors.begin();
            int thisPos = std::find(predSucc.begin(),predSucc.end(),this)-predSucc.begin();

            if(predPos >= 0 && predPos < predecessors.size())
                predecessors.erase(predecessors.begin()+predPos);

            if(thisPos >= 0 && thisPos < predSucc.size())
                pred->forgetSuccessor(thisPos);
        }

        void setPredecessorAt(int pos,DFGNode* n){

            if(pos >= predecessors.size()){
                llvm::errs() << "Invalid positon...";
                return;
            }
            predecessors.erase(predecessors.begin()+pos);
            predecessors.insert(predecessors.begin()+pos,n);
        }

        void setSuccessorAt(int pos,DFGNode* n){

            if(pos >= successors.size()){
                llvm::errs() << "Invalid positon...";
                return;
            }
            successors.erase(successors.begin()+pos);
            successors.insert(successors.begin()+pos,n);
        }

        void changeParent(DFGNode* oldParent,DFGNode* newParent){
            int pos = getPredecessorPosition(oldParent);
            this->unlinkPredecessor(oldParent);
            this->linkPredecessor(newParent,pos);
        }

        void insertPredecessor(DFGNode* pred,DFGNode* newPred){

            for(DFGNode* p : this->predecessors){
                if(p == pred){
                    std::vector<DFGNode*> predSucc = p->getSuccessors();

                    int thisPos = std::find(predSucc.begin(),predSucc.end(),this)-predSucc.begin();
                    int predPos = std::find(predecessors.begin(),predecessors.end(),pred)-predecessors.begin();

                    pred->setSuccessorAt(thisPos,newPred);
                    newPred->getPredecessors().push_back(pred);

                    this->setPredecessorAt(predPos,newPred);
                    newPred->setSuccessor(this);

                    return;
                }
            }
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

        bool equals(DFGNode* n_2){

            if(node == n_2->getValue())
                return true;

            return false;
        }

        bool isInTheSameLoop(DFGNode* n,llvm::LoopInfo* LI){

            if(llvm::Instruction* i_1 = llvm::dyn_cast<llvm::Instruction>(this->getValue())){
                if(llvm::Instruction* i_2 = llvm::dyn_cast<llvm::Instruction>(n->getValue())){

                    llvm::Loop* L1 = LI->getLoopFor(i_1->getParent());
                    llvm::Loop* L2 = LI->getLoopFor(i_2->getParent());

                    if(L1 == L2)
                        return true;

                }else{
                    return false;
                }
            }else{
                return false;
            }
            return false;
        }

        int firstOccurrenceInNodeVector(std::vector<DFGNode*> nodes){

            int pos = 0;

            for(DFGNode* n : nodes){
                if(n == this)
                    return pos;
                else
                    pos++;
            }
            return -1;
        }
    };

    typedef std::pair<DFGNode*,DFGNode*> NodePort;

    class DFGCounterNode : public DFGNode {

    private:

        int start;
        int step;

    public:

        DFGCounterNode(llvm::PHINode* value,int loopTripCount = -1) :
                DFGNode(value,loopTripCount) {

            this->typeID = NodeType::CounterNode;
            this->step = 1;

            if(llvm::ConstantInt* c = llvm::dyn_cast<llvm::ConstantInt>(value->getIncomingValue(0))){
                start = c->getSExtValue();
            }else{
                llvm::errs() << "INFO: unable to compute start for counter \n";
                start = 0;
            }
        }

        int getStart(){ return this->start; }

        int getStep(){ return this->step; }
    };

    class DFGAccNode : public DFGNode {

    private:

        bool isCounter;

    public:

        DFGAccNode(llvm::Value* value,int loopTripCount = -1) : DFGNode(value,loopTripCount) {

            this->typeID = NodeType::AccumulNode;
            this->isCounter = false;
        }

        bool getIsCounter(){ return isCounter; }

        void setIsCounter(bool value){ this->isCounter = value; }
    };

    class DFGOffsetNode : public DFGNode {

    private:

        static long UID;
        int offsetAsInt;
        long nodeID;

    public:

        long getUID(){ return nodeID; }

        int getOffsetAsInt(){ return offsetAsInt; }

        void setOffsetAsInt(int offset){ offsetAsInt = offset; }

        DFGOffsetNode(DFGNode* baseNode);

        llvm::Value* getValue();

        void printNode();

    };

    class DFGLoopNode : public DFGNode {

    private:

        std::vector<NodePort> inputPorts;
        std::vector<NodePort> outputPorts;
        std::vector<DFGNode*> endNodes;
        llvm::Loop* loop;
        int constTripCount;

        static  int LOOP_ID_COUNTER;
        int loopID = 0;
        int operationsMultiplier = 1;

    public:

        DFGLoopNode(llvm::Loop* loop);

        llvm::Loop* getLoopPtr(){ return loop; }

        std::vector<DFGNode*> getEndNodes(){ return endNodes; }
        void addEndNode(DFGNode* node){ endNodes.push_back(node); }

        void insertInputPort(DFGNode* in,DFGNode* out);
        void insertOutputPort(DFGNode* in,DFGNode* out);
        std::vector<DFGNode*> getInPortSuccessors(DFGNode *outerNode);
        std::vector<DFGNode*> getInPortPredecessors(DFGNode *innerNode);
        std::vector<DFGNode*> getOutPortSuccessors(DFGNode *innerNode);
        std::vector<DFGNode*> getOutPortPredecessors(DFGNode *outerNode);

        std::vector<DFGNode*> getOutPortInnerNodes();
        std::vector<DFGNode*> getOutPortOuterNodes();
        std::vector<DFGNode*> getInPortInnerNodes();
        std::vector<DFGNode*> getInPortOuterNodes();

        void printNode();

        int getTripCount(){ return constTripCount; }
        void setTripCount(int iters){ constTripCount = iters; }

        std::vector<DFG*> getIndipendentLoopGraphs();

        int getLoopID(){
            if(!loopID){
                LOOP_ID_COUNTER++;
                loopID = LOOP_ID_COUNTER;
            }
            return loopID;
        }

        int getOperationsMultiplier(){ return operationsMultiplier; }
        void setOperationsMultiplier(int m){ operationsMultiplier = m; }

    };

    class AccessChain{

    private:

        std::vector<llvm::Value*> accessVector;

    public:
        AccessChain(llvm::Value* innermostAccess);

        std::vector<llvm::Value*> getAccessVector(){ return this->accessVector; }

        std::vector<llvm::Value*> getAccessIndexesIfAny();

        void addOuterAccess(llvm::Value* accessValue){
            accessVector.insert(accessVector.begin(),accessValue);
        }
        void addInnerAccess(llvm::Value* accessValue){
            accessVector.push_back(accessValue);
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
    
    protected:
        
        StreamPair writingStream;
        AccessChain* accessChain;
        
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
        DFGWriteNode(llvm::Value* value, IOStreams* loopStreams, int loopTripCount);

        DFGWriteNode(llvm::Value* value, IOStreams* loopStreams, int windowStart,int windowEnd);
        
        //getter for the writingStream of this node
        StreamPair getWritingStream(){ return writingStream; }

        bool equals(DFGNode* n_2){

            if(!DFGNode::equals(n_2))
                return false;

            DFGWriteNode* w_2 = (DFGWriteNode*)n_2;

            if(w_2->getWritingStream().first == writingStream.first)
                    return true;

            return false;
        }

        void printNode(){

            DFGNode::printNode();
            llvm::errs() << " \nWriting stream: ";
            writingStream.first->dump();
            llvm::errs() << "\nAccess chain:\n";
            for(auto el : accessChain->getAccessVector()){
                llvm::errs() << "Access: ";
                el->dump();
            }
            llvm::errs() << "Indexes:\n";
            for(auto el : accessChain->getAccessIndexesIfAny()){
                llvm::errs() << "Index: ";
                el->dump();
            }
            llvm::errs() << "\n";
        }

        AccessChain* getAccessChain(){ return accessChain; }
    };

    class DFGOffsetWriteNode : public DFGWriteNode {

    public:

        DFGOffsetWriteNode(llvm::Value* value,IOStreams* IOs,const llvm::SCEV* offset, int loopTripCount);

        bool equals(DFGNode* n_2){

            if(!DFGWriteNode::equals(n_2))
                return false;

            DFGOffsetWriteNode* ow_2 = (DFGOffsetWriteNode*)n_2;

            if(ow_2->getWritingStream().second == writingStream.second)
                return true;

            return false;
        }

        void printNode(){

            DFGWriteNode::printNode();
            llvm::errs() << "Offset: ";
            writingStream.second->dump();
        }

    };

    /**
     * @class DFGReadNode
     * @brief DFGNode which represents a read node in the DataFlow graph, corresponding
     *        to a load operation which has as argument a pointer to the value of an 
     *        input stream. In addition to the node's value, it also contains the
     *        llvm::Value of its corresponding input stream
     */
    class DFGReadNode : public DFGNode {
    
    protected:

        AccessChain* accessChain;
        StreamPair sourceStream;
        
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
        DFGReadNode(llvm::Value* value, IOStreams* loopStreams, int loopTripCount);

        DFGReadNode(llvm::Value* value,IOStreams* loopStreams,int windowSart,int windowEnd);
        
        //getter for the sourceStream of this node
        StreamPair getReadingStream(){ llvm::errs() <<"strval ";sourceStream.first->dump(); return sourceStream; }

        bool equals(DFGNode* n_2){

            if(!DFGNode::equals(n_2))
                return false;

            DFGReadNode* w_2 = (DFGReadNode*)n_2;

            if(w_2->getReadingStream().first == sourceStream.first)
                return true;

            return false;
        }

        void printNode(){

            DFGNode::printNode();
            llvm::errs() << "\nSource stream: ";
            sourceStream.first->dump();
            llvm::errs() << "\nAccess chain:\n";
            for(auto el : accessChain->getAccessVector()){
                llvm::errs() << "Access: ";
                el->dump();
            }
            llvm::errs() << "Indexes:\n";
            for(auto el : accessChain->getAccessIndexesIfAny()){
                llvm::errs() << "Index: ";
                el->dump();
            }
            llvm::errs() << "\n";
        }

        AccessChain* getAccessChain(){ return accessChain; }
    };


    class DFGOffsetReadNode : public DFGReadNode {

    public:

        DFGOffsetReadNode(llvm::Value* value,IOStreams* IOs,const llvm::SCEV* offset, int loopTripCount);

        bool equals(DFGNode* n_2){

            if(!DFGReadNode::equals(n_2))
                return false;

            DFGOffsetWriteNode* ow_2 = (DFGOffsetWriteNode*)n_2;

            if(ow_2->getWritingStream().second == sourceStream.second)
                return true;

            return false;
        }

        void printNode(){

            DFGReadNode::printNode();
            llvm::errs() << "Offset: ";
            sourceStream.second->dump();
        }
    };

    class DFGMuxNode : public DFGNode {

    private:
        TickBasedCondition* cond;

    public:

        DFGMuxNode(DFGNode* node_1,DFGNode* node_2,TickBasedCondition* cond) : DFGNode(nullptr) {

            this->cond = cond;

            llvm::LLVMContext c;
            llvm::Constant* zero =
                    llvm::ConstantInt::get(llvm::IntegerType::get(c,1),llvm::APInt(1,0));

            llvm::Value* value =
                    llvm::SelectInst::Create(zero, node_1->getValue(), node_2->getValue());

            this->node = value;
            this->typeID = NodeType ::MuxNode;


        }

        llvm::Value* getValue();

        TickBasedCondition* getCond(){ return this->cond; }

        void printNode();
    };

    class DFGNodeFactory{

    public:

        DFGNode* createDFGNode(llvm::Value* value,int loopTripCount = -1);

        DFGWriteNode* createDFGWriteNode(llvm::Value* value, IOStreams* loopStreams, int loopTripCount);
        DFGWriteNode* createDFGWriteNode(llvm::Value* value, IOStreams* loopStreams, int windowStart,int windowEnd);

        DFGReadNode* createDFGReadNode(llvm::Value* value, IOStreams* loopStreams, int loopTripCount);
        DFGReadNode* createDFGReadNode(llvm::Value* value,IOStreams* loopStreams,int windowSart,int windowEnd);

        DFGOffsetNode* createDFGOffsetNode(DFGNode* baseNode);
        DFGOffsetReadNode* createDFGOffsetReadNode(llvm::Value* value,IOStreams* IOs,const llvm::SCEV* offset, int loopTripCount);
        DFGOffsetWriteNode* createDFGOffsetWriteNode(llvm::Value* value,IOStreams* IOs,const llvm::SCEV* offset, int loopTripCount);

        DFGMuxNode* createDFGMuxNode(DFGNode* node_1,DFGNode* node_2,TickBasedCondition* cond);

        DFGCounterNode* createDFGCounterNode(llvm::PHINode* value,int loopTripCount = -1);
        DFGAccNode* createDFGAccNode(llvm::Value* value,int loopTripCount = -1);

        DFGLoopNode* createDFGLoopNode(llvm::Loop* loop);

    private:

        DFGNode* getNodeIfListed(llvm::Value* nVal,NodeType type);

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

        void setEndNode(DFGNode* node){ endNode = node; }

        /**
         * @brief Used to retrieve the DFGWriteNode in this graph. It
         *        actually just searches for 'store' operations and then
         *        attempts to cast the DFGNode wrapper object to a 
         *        DFGWriteNode. Therefore it should only be used when
         *        it is safe to do so.
         * 
         * @param baseNode - the base node of this graph
         */

        std::vector<DFGNode*> getCrossScopeNodes(DFG* dfg,llvm::Function* F);

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

        std::vector<DFGReadNode*> getUniqueReadNodes(DFG* dfg, llvm::Function* F);

        std::vector<DFGWriteNode*> getUniqueWriteNodes(DFG* baseNode, llvm::Function* F);

        void getUniqueOrderedNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted,int baseSize);

        std::vector<DFGNode*> getGraphNodes();

        std::vector<DFGNode*> orderNodesWithFunc(llvm::Function* F);
        
        /**
         * @brief Returns the DFGNodes containing llvm::Arguments as values
         * @param baseNode - the base node for this graph
         * @return a srd::vector of DFGNodes containing llvm::Arguments as values
         */
        std::vector<DFGNode*> getScalarArguments(DFG* dfg,llvm::Function* F);
        
        std::vector<DFGNode*> getUniqueScalarArguments(DFG* dfg,llvm::Function *F);

        std::vector<DFGReadNode*> collectReadNodes(DFG* dfg,llvm::Function* F);

        std::vector<DFGWriteNode*> collectWriteNodes(DFG* dfg,llvm::Function* F);
        
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

        void simplePrintDFG(DFGNode* startingNode);

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

        void resetMarkedFlags(DFGNode* node);

        void orderNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted, int baseSize=0);

        void setDFGFlags();

        void fuseIdenticalNodes();
    
    private:

        int countChildren(DFGNode* parent, int count);

        int simpleCount(DFGNode* n);

        int descendAndCount(DFGNode* node, int count);
        
        void descendAndReset(DFGNode* node);

        void simpleSetNames(std::vector<std::string> &nodeNames, DFGNode* node);
        
        void setNames(std::vector<std::string> &nodeNames, DFGNode* node);
        
        void descendAndSetNames(std::vector<std::string> &nodeNames, DFGNode* node);

        void setFlags(DFGNode *node);

        void descendAndSet(DFGNode* node);

        void collectNode(DFGNode* n,std::vector<DFGNode*> &nodes);

        std::pair<int,int> getMinWindowInSubgraph(DFGNode* start);

        std::pair<int,int> getResultingWindow(std::pair<int,int> w_1,std::pair<int,int> w_2);

        void orderMissingNode(DFGNode* n,std::vector<DFGNode*> &sortedNodes);
        
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
        ProcessingScheduler* scheduler;
        llvm::Function* F;
    
    public:
    
        DFGLinker(std::vector<DFG*> dfgs,llvm::Function* F){
            this->dfgs = dfgs;
            this->F = F;
            llvm::errs() << "graphs to link:\n";
        for(DFG* d : dfgs )
            d->printDFG();
        }
        
        void acceptExecutor(ProcessingScheduler* scheduler){
            this->scheduler = scheduler;
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

        typedef std::pair<llvm::Loop*,DFGCounterNode*> CounterPair;
        
        protected:
        
            ProcessingScheduler* scheduler;
            std::vector<CounterPair> loopCounters;
            llvm::Function* F;
      
        public:

            DFGConstructor(llvm::Function* F){
                this->F = F;
            }

            void acceptExecutor(ProcessingScheduler* scheduler){
                this->scheduler = scheduler;
                scheduler->execute(this);
            }
            
            std::vector<DFG*> computeIOStreamBasedDFG(llvm::Loop* topLevelLoop, IOStreams* IOs,
                                                      llvm::ScalarEvolution* SE, int loopIndex);

            std::vector<DFG*> computeStaticDFG(IOStreams* IOs,llvm::ScalarEvolution* SE,
                                                llvm::LoopInfo* LI,llvm::Function* F,llvm::BasicBlock* start);

        private:

            void initiateDFGConstruction(std::vector<DFG*> &computedDFGs,IOStreams* IOs,
                                         llvm::Loop* topLevelLoop,llvm::ScalarEvolution* SE,
                                         int loopTripCount,llvm::BasicBlock* BB);

            void initiateStaticDFGConstruction(std::vector<DFG *> &computedDFGs, IOStreams *IOs,
                                                           llvm::ScalarEvolution *SE, llvm::BasicBlock *BB);

            void populateDFG(DFGNode* node, IOStreams* IOs, int loopTripCount,
                             llvm::Loop* loop);

            void constructNodeForOperands(std::vector<llvm::Value*> instructionOperands,DFGNode* node,
                                          llvm::Loop* loop, DFGNodeFactory* nodeFactory, IOStreams* IOs, int loopTripCount);

            DFGNode* constructNode(llvm::Value* value,DFGNode* parentNode, llvm::Loop* loop, DFGNodeFactory* nodeFactory,
                               IOStreams* IOs, int loopTripCount);

            DFG* computeDFGFromBase(DFGWriteNode* baseNode, IOStreams* IOs,int loopTripCount,llvm::Loop* loop);

            llvm::Instruction* getInstrFromOperand(llvm::Value* value, std::string opcodeName);

            DFGNode* shortcutSoreGetelementPtr(DFGWriteNode* storeNode,IOStreams* IOs,llvm::Loop* loop, int loopTripCount);

            bool hasSextOnIndvar(llvm::Instruction* instr,llvm::Loop* loop);

            StreamPair storedOutputStream(llvm::StoreInst* store, IOStreams* IOs, llvm::ScalarEvolution* SE);


    };

    void insertNode(DFGNode* n,DFGNode* pred,DFGNode* succ,bool areConsecutive);

    void eliminateNode(DFGNode* node);

    void  fuseNodes(DFGNode* n_1, DFGNode* n_2,std::vector<DFGNode*> &exceptionVector);

    void transferSuccessors(DFGNode* currentParent,DFGNode* newParent);

    void transferPredecessors(oxigen::DFGNode *currentSuccessor, oxigen::DFGNode *newSuccessor);

    bool isCounterForLoop(llvm::PHINode* phi,llvm::Loop* L);

    bool isExitPhi(llvm::PHINode* phi);

    bool isNestedVectorWrite(DFGNode *node,bool onlyAlloca = false);

    llvm::PHINode* getLoopCounterIfAny(llvm::Loop* loop);

    std::vector<DFGNode*> getElementarPredecessors(std::vector<DFGNode*> nodes,DFGNode* succNode);

    std::vector<DFGNode*> getNodePredecessors(DFGNode* n,NodeType type,DFGNode* succNode);

    bool  isComposite(NodeType type);

    std::vector<NodeType> getCompositeTypes();

    std::vector<DFGNode*> getLoopCarriedDependencies(DFG* dfg);

    llvm::Value* getGEPBaseAddress(llvm::GetElementPtrInst* gep);

} // End OXiGen namespace

#endif