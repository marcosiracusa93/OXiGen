
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/Scalar.h>
#include "llvm/IR/Dominators.h"
#include "DFGConstructor.h"

using namespace oxigen;

///DFGNode methods implementation

llvm::Value* DFGNode::getValue(){

        if(typeID == Offset){
            DFGOffsetNode* off = (DFGOffsetNode*)this;
            return off->getValue();
        }
        if(typeID == MuxNode){
            DFGMuxNode* mux = (DFGMuxNode*)this;
            return mux->getValue();
        }

        return node;
}

std::string DFGNode::getName() { return name; }

llvm::Value* DFGOffsetNode::getValue() {

    llvm::LLVMContext c;

    llvm::Constant* offset =
            llvm::ConstantInt::get(llvm::IntegerType::get(c,32),llvm::APInt(32,offsetAsInt));

    return offset;
}

llvm::Value* DFGMuxNode::getValue(){

    TickBasedConstantCondition* cond = (TickBasedConstantCondition*)getCond();

    llvm::LLVMContext c;
    llvm::Constant* zero =
            llvm::ConstantInt::get(llvm::IntegerType::get(c,1),llvm::APInt(1,0));

    llvm::Constant* selOP_1 =
            llvm::ConstantInt::get(llvm::IntegerType::get(c,32),llvm::APInt(32,cond->getTickLowerBound()));

    llvm::Value* selOP_2 =
            llvm::ConstantInt::get(llvm::IntegerType::get(c,32),llvm::APInt(32,cond->getTickUpperBound()));

    llvm::Value* value =
            llvm::SelectInst::Create(zero, selOP_1, selOP_2);

    return value;
}

void DFGOffsetNode::printNode() {

    llvm::errs() << "\nNode: " << name << "\n";
    getValue()->dump();

    llvm::errs() << "Streaming window: [" << streamWindow.first << "," << streamWindow.second << "]\n";
    llvm::errs() << "Global delay for node: " << globalDelay << "\n";

    llvm::errs() << "Predecessors\n";

    for(DFGNode* predecessor : predecessors){
        predecessor->getValue()->dump();
        if(std::find(predecessor->getSuccessors().begin(),predecessor->getSuccessors().end(),this) ==
           predecessor->getSuccessors().end()){
            llvm::errs() << "Pred has not this as succ\n";
        }
    }

    for(DFGNode* succ : successors){
        if(std::find(succ->getPredecessors().begin(),succ->getPredecessors().end(),this)==succ->getPredecessors().end())
            llvm::errs() << "Succ has not this as pred\n";
    }
}

void DFGMuxNode::printNode() {

    llvm::errs() << "\nNode: " << name << "\n";
    getValue()->dump();

    llvm::errs() << "Streaming window: [" << streamWindow.first << "," << streamWindow.second << "]\n";
    llvm::errs() << "Global delay for node: " << globalDelay << "\n";

    llvm::errs() << "Predecessors\n";

    for(DFGNode* predecessor : predecessors){
        predecessor->getValue()->dump();
        if(std::find(predecessor->getSuccessors().begin(),predecessor->getSuccessors().end(),this) ==
           predecessor->getSuccessors().end()){
            llvm::errs() << "Pred has not this as succ\n";
        }
    }

    for(DFGNode* succ : successors){
        if(std::find(succ->getPredecessors().begin(),succ->getPredecessors().end(),this)==succ->getPredecessors().end())
            llvm::errs() << "Succ has not this as pred\n";
    }
}

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

    NodeType type = getType();

    if(!getFlag())
        switch(type){
            case NodeType::ReadNode: {
                DFGReadNode* r = (DFGReadNode*)this;
                setFlag(true);
                r->printNode();
                return;
            }

            case NodeType::WriteNode: {
                DFGWriteNode* w = (DFGWriteNode*)this;
                setFlag(true);
                w->printNode();
                return;
            }

            case NodeType::OffsetRead: {
                DFGOffsetReadNode* ofs_r = (DFGOffsetReadNode*)this;
                setFlag(true);
                ofs_r->printNode();
                return;
            }

            case NodeType::OffsetWrite: {
                DFGOffsetWriteNode* ofs_w = (DFGOffsetWriteNode*)this;
                setFlag(true);
                ofs_w->printNode();
                return;
            }
            case NodeType::Offset: {
                DFGOffsetNode* ofs_w = (DFGOffsetNode*)this;
                setFlag(true);
                ofs_w->printNode();
                return;
            }
            case NodeType::MuxNode: {
                DFGMuxNode* ofs_w = (DFGMuxNode*)this;
                setFlag(true);
                ofs_w->printNode();
                return;
            }
            case NodeType::LoopNode: {
                DFGLoopNode* loopNode = (DFGLoopNode*)this;
                setFlag(true);
                loopNode->printNode();
            }

            default:
                break;
        }
    else
    {
        setFlag(false);
    }
    
    llvm::errs() << "\nNode: " << name << " - " << node << "\n";
    getValue()->dump();

    llvm::errs() << "Streaming window: [" << streamWindow.first << "," << streamWindow.second << "]\n";
    llvm::errs() << "Global delay for node: " << globalDelay << "\n";

    llvm::errs() << "Predecessors\n";

    for(DFGNode* predecessor : predecessors){
        predecessor->getValue()->dump();
        if(std::find(predecessor->getSuccessors().begin(),predecessor->getSuccessors().end(),this) ==
           predecessor->getSuccessors().end()){
            llvm::errs() << "Pred has not this as succ\n";
        }
    }
    llvm::errs() << "Successors\n";

    for(DFGNode* successor : successors){
        successor->getValue()->dump();
        if(std::find(successor->getPredecessors().begin(),successor->getPredecessors().end(),this) ==
                successor->getPredecessors().end()){
            llvm::errs() << "Succ has not this as pred\n";
        }
    }

    llvm::errs() << "LoopCarriedPredecessors\n";

    for(DFGNode* n : loopCarriedPredecessors)
        n->getValue()->dump();

    llvm::errs() << "LoopCarriedSuccessors\n";

    for(DFGNode* n : loopCarriedSuccessors)
        n->getValue()->dump();
}

int DFGNode::getPredecessorPosition(DFGNode *n) {
    for(auto it = predecessors.begin(); it != predecessors.end(); ++it){
        if(*it == n){
            return it-predecessors.begin();
        }
    }
    return -1;
}

int DFGNode::getSuccessorPosition(DFGNode *n) {
    for(auto it = successors.begin(); it != successors.end(); ++it){
        if(*it == n){
            return it-successors.begin();
        }
    }
    return -1;
}

std::vector<DFGNode*> DFGNode::getCrossScopePredecessors() {

    std::vector<DFGNode*> crossScopePredecessors = oxigen::getElementarPredecessors(predecessors,this);

    if(loop != nullptr){
        for(DFGNode* n : loop->getInPortPredecessors(this)){
            std::vector<DFGNode*> v = std::vector<DFGNode*>();
            v.push_back(n);
            std::vector<DFGNode*> elNodes = getElementarPredecessors(v,this);
            crossScopePredecessors.insert(crossScopePredecessors.end(),elNodes.begin(),elNodes.end());
        }
    }

    return crossScopePredecessors;
}

///DFGLoopNode methods implementation

DFGLoopNode::DFGLoopNode(llvm::Loop *loop) : DFGNode(oxigen::getLoopCounterIfAny(loop)){

    if(node == nullptr)
        llvm::errs() << "\nERROR: loop counter not found, initialization failed...\n";

    this->typeID = NodeType::LoopNode;
    this->inputPorts = std::vector<NodePort>();
    this->outputPorts = std::vector<NodePort>();
    this->endNodes = std::vector<DFGNode*>();
    this->loop = loop;
}

void DFGLoopNode::insertInputPort(DFGNode *in, DFGNode *out) {

    out->unlinkPredecessor(in);
    this->linkPredecessor(in);
    this->inputPorts.push_back(NodePort(in,out));

    llvm::errs() << "\nInserted ports for " << this << " :\n";
    for(NodePort p : outputPorts){
        p.first->getValue()->dump();
        p.second->getValue()->dump();
        llvm::errs() << "\n";
    }
    for(NodePort p : inputPorts){
        p.first->getValue()->dump();
        p.second->getValue()->dump();
        llvm::errs() << "\n";
    }
}

void DFGLoopNode::insertOutputPort(DFGNode *in, DFGNode *out) {

    out->unlinkPredecessor(in);
    out->linkPredecessor(this);
    this->outputPorts.push_back(NodePort(in,out));
    llvm::errs() << "\nInserted ports for " << this << " :\n";
    for(NodePort p : outputPorts){
        p.first->getValue()->dump();
        p.second->getValue()->dump();
        llvm::errs() << "\n";
    }
    for(NodePort p : inputPorts){
        p.first->getValue()->dump();
        p.second->getValue()->dump();
        llvm::errs() << "\n";
    }
}

std::vector<DFGNode*> DFGLoopNode::getInPortSuccessors(DFGNode *outerNode) {

    std::vector<DFGNode*> inPortSuccessors = std::vector<DFGNode*>();

    for(NodePort inPort : inputPorts){
        if(inPort.first->equals(outerNode))
            inPortSuccessors.push_back(inPort.second);
    }
    return inPortSuccessors;
}

std::vector<DFGNode*> DFGLoopNode::getInPortPredecessors(DFGNode *innerNode){

    std::vector<DFGNode*> inPortPredecessors = std::vector<DFGNode*>();

    for(NodePort inPort : inputPorts){
        if(inPort.second->equals(innerNode))
            inPortPredecessors.push_back(inPort.first);
    }
    return inPortPredecessors;
}

std::vector<DFGNode*> DFGLoopNode::getOutPortSuccessors(DFGNode *innerNode){

    std::vector<DFGNode*> outPortSucessors = std::vector<DFGNode*>();

    for(NodePort outPort : outputPorts){
        if(outPort.first->equals(innerNode))
            outPortSucessors.push_back(outPort.second);
    }
    return outPortSucessors;
}

std::vector<DFGNode*> DFGLoopNode::getOutPortPredecessors(DFGNode *outerNode) {

    std::vector<DFGNode*> outPortPredecessors = std::vector<DFGNode*>();

    for(NodePort outPort : outputPorts){
        if(outPort.second->equals(outerNode))
            outPortPredecessors.push_back(outPort.first);
    }
    return outPortPredecessors;
}

std::vector<DFGNode*> DFGLoopNode::getOutPortInnerNodes(){

    std::vector<DFGNode*> outPortInnerNodes;

    for(NodePort outPort: outputPorts){
        outPortInnerNodes.push_back(outPort.first);
    }
    return outPortInnerNodes;
}

std::vector<DFGNode*> DFGLoopNode::getOutPortOuterNodes(){

    std::vector<DFGNode*> outPortOuterNodes;

    for(NodePort outPort: outputPorts){
        outPortOuterNodes.push_back(outPort.second);
    }
    return outPortOuterNodes;
}

std::vector<DFGNode*> DFGLoopNode::getInPortInnerNodes(){

    std::vector<DFGNode*> inPortInnerNodes;

    for(NodePort inPort: inputPorts){
        inPortInnerNodes.push_back(inPort.second);
    }
    return inPortInnerNodes;
}

std::vector<DFGNode*> DFGLoopNode::getInPortOuterNodes(){

    std::vector<DFGNode*> inPortOuterNodes;

    for(NodePort inPort: inputPorts){
        inPortOuterNodes.push_back(inPort.first);
    }
    return inPortOuterNodes;
}

void DFGLoopNode::printNode(){

    llvm::errs() << "\nLoopNode structure for" << this << ":\n->input ports:\n";
    for(NodePort inPort : inputPorts){
        llvm::errs() << "----------------\n";
        llvm::errs() << "\t";
        inPort.first->getValue()->dump();
        llvm::errs() << "\t";
        inPort.second->getValue()->dump();
        llvm::errs() << "----------------\n";
    }

    llvm::errs() << "->output ports:\n";
    for(NodePort outPort : outputPorts){
        llvm::errs() << "----------------\n";
        llvm::errs() << "\t";
        outPort.first->getValue()->dump();
        llvm::errs() << "\t";
        outPort.second->getValue()->dump();
        llvm::errs() << "----------------\n";
    }

    llvm::errs() << "Graph base nodes in this loop:\n";
    for(DFGNode* node : endNodes)
        node->getValue()->dump();

}

std::vector<DFG *> DFGLoopNode::getIndipendentLoopGraphs() {

    std::vector<DFG*> edgeNodeGraphs;
    std::vector<DFG*> indipendentGraphs = std::vector<DFG*>();

    for(DFGNode* endNode : endNodes){
        DFG* edgeNodeGraph = new DFG(endNode);
        edgeNodeGraph->resetFlags(endNode);
        edgeNodeGraphs.push_back(edgeNodeGraph);
    }

    for(NodePort outPort : outputPorts){
        DFG* edgeNodeGraph = new DFG(outPort.first);
        edgeNodeGraph->resetFlags(outPort.first);
        edgeNodeGraphs.push_back(edgeNodeGraph);
    }

    for(DFG* graph : edgeNodeGraphs){
        if(!(graph->getEndNode()->getFlag())){
            graph->setDFGFlags();
            indipendentGraphs.push_back(graph);
        }
    }

    for(DFG* edgeNodeGraph : edgeNodeGraphs){
        edgeNodeGraph->resetFlags(edgeNodeGraph->getEndNode());
    }
    return indipendentGraphs;
}


///DFGWriteNode methods implementation

DFGWriteNode::DFGWriteNode(llvm::Value* value, IOStreams* loopStreams, int loopTripCount) :
        DFGNode(value,loopTripCount) {

    this->typeID = NodeType::WriteNode;

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){
        for(auto stream : loopStreams->getOutputStreams()){
            if(((llvm::Instruction*)(instr->getOperand(1)))->getOperand(0) == stream.first)
            {
                writingStream = stream;
                return;
            }   
        }
        writingStream = loopStreams->getInStreamFromGEP((llvm::GetElementPtrInst*)(instr->getOperand(1)));
        llvm::errs() << "Attributed default writing stream for "; value->dump();
    }
}

DFGWriteNode::DFGWriteNode(llvm::Value* value, IOStreams* loopStreams, int windowStart,int windowEnd) :
    DFGNode(value,windowEnd){

    this->typeID = NodeType::WriteNode;

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)) {
        for (auto stream : loopStreams->getOutputStreams()) {
            if (((llvm::Instruction *) (instr->getOperand(1)))->getOperand(0) == stream.first) {
                writingStream = stream;
                this->streamWindow = std::pair<int, int>(windowStart, windowEnd);
                return;
            }
        }
        writingStream = loopStreams->getInStreamFromGEP((llvm::GetElementPtrInst *) (instr->getOperand(1)));
        llvm::errs() << "Attributed default writing stream for ";
        value->dump();
    }
    this->streamWindow = std::pair<int, int>(windowStart, windowEnd);
}

///DFGReadNode methods implementation

DFGReadNode::DFGReadNode(llvm::Value* value, IOStreams* loopStreams, int loopTripCount) :
        DFGNode(value,loopTripCount) {

    this->typeID = NodeType::ReadNode;

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){
        for(auto stream : loopStreams->getInputStreams()){
            if(((llvm::Instruction*)(instr->getOperand(0)))->getOperand(0) == stream.first)
            {
                sourceStream = stream;
                return;
            }
        }
        sourceStream = loopStreams->getInStreamFromGEP((llvm::GetElementPtrInst*)(instr->getOperand(0)));
        llvm::errs() << "Attributed default reading stream for "; value->dump();
    }
}

DFGReadNode::DFGReadNode(llvm::Value* value,IOStreams* loopStreams,int windowStart,int windowEnd) :
        DFGNode(value,windowEnd) {

    this->typeID = NodeType::ReadNode;

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){
        for(auto stream : loopStreams->getInputStreams()){
            if(((llvm::Instruction*)(instr->getOperand(0)))->getOperand(0) == stream.first)
            {
                sourceStream = stream;
                this->streamWindow = std::pair<int, int>(windowStart, windowEnd);
                return;
            }
        }
        sourceStream = loopStreams->getInStreamFromGEP((llvm::GetElementPtrInst*)(instr->getOperand(0)));
        llvm::errs() << "Attributed default reading stream for "; value->dump();
    }
    this->streamWindow = std::pair<int,int>(windowStart,windowEnd);

}

DFGOffsetWriteNode::DFGOffsetWriteNode(llvm::Value* value,IOStreams* IOs, const llvm::SCEV* offset, int loopTripCount) :
        DFGWriteNode(value,IOs,loopTripCount){

    this->typeID = NodeType::OffsetWrite;

    llvm::Value* valuePtr = ((llvm::Instruction*)(((llvm::Instruction*)value)->getOperand(1)))->getOperand(0);

    for(StreamPair p : IOs->getOutputStreams()){

        if(valuePtr == p.first && offset == p.second){
            writingStream = p;

            if(offset->getSCEVType() == llvm::SCEVTypes::scConstant) {
                llvm::ConstantInt *intOfs = ((llvm::SCEVConstant *) offset)->getValue();

                int startingOffset = intOfs->getSExtValue();
                streamWindow.first = streamWindow.first - startingOffset;
                streamWindow.second = streamWindow.second - startingOffset;
            }
            return;
        }

    }
    llvm::errs() << "Offset not in IOStreams, assigning new offset...\n";
    writingStream = StreamPair(valuePtr,offset);

    if(offset->getSCEVType() == llvm::SCEVTypes::scConstant){
        llvm::ConstantInt* intOfs = ((llvm::SCEVConstant*)offset)->getValue();

        int startingOffset = intOfs->getSExtValue();
        streamWindow.first = streamWindow.first - startingOffset;
        streamWindow.second = streamWindow.second - startingOffset;

    }else{
        llvm::errs() << "Non constant offset while computing stream window, terminating...\n";
        exit(EXIT_FAILURE);
    }

}

DFGOffsetNode::DFGOffsetNode(DFGNode* baseNode) : DFGNode((baseNode->getValue()),baseNode->getStreamWindow().second){

    this->typeID = NodeType::Offset;
    this->streamWindow = baseNode->getStreamWindow();
    this->offsetAsInt = streamWindow.first;

    llvm::LLVMContext c;

    llvm::Constant* offset =
            llvm::ConstantInt::get(llvm::IntegerType::get(c,32),llvm::APInt(32,offsetAsInt));

    this->node = offset;
    llvm::errs() << "OFFSET: ";
    node->dump();

}

DFGOffsetReadNode::DFGOffsetReadNode(llvm::Value* value,IOStreams* IOs, const llvm::SCEV* offset, int loopTripCount) :
        DFGReadNode(value,IOs,loopTripCount){

    this->typeID = NodeType::OffsetRead;

    llvm::Value* valuePtr = ((llvm::Instruction*)(((llvm::Instruction*)value)->getOperand(0)))->getOperand(0);

    for(StreamPair p : IOs->getInputStreams()){

        if(valuePtr == p.first && offset == p.second){
            sourceStream = p;

            if(offset->getSCEVType() == llvm::SCEVTypes::scConstant) {
                llvm::ConstantInt *intOfs = ((llvm::SCEVConstant *) offset)->getValue();

                int startingOffset = intOfs->getSExtValue();
                streamWindow.first = streamWindow.first + startingOffset;
                streamWindow.second = streamWindow.second + startingOffset;
            }
            return;
        }

    }
    llvm::errs() << "Offset not in IOStreams, assigning new offset...";
    sourceStream = StreamPair(valuePtr,offset);

    if(offset->getSCEVType() == llvm::SCEVTypes::scConstant){
        llvm::ConstantInt* intOfs = ((llvm::SCEVConstant*)offset)->getValue();

        int startingOffset = intOfs->getSExtValue();
        streamWindow.first = streamWindow.first + startingOffset;
        streamWindow.second = streamWindow.second + startingOffset;

    }else{
        llvm::errs() << "Non constant offset while computing stream window, terminating...\n";
        exit(EXIT_FAILURE);
    }
}

///DFG methods implementation

void DFG::getReadNodes(DFGNode* baseNode,std::vector<DFGReadNode*> &readNodes){

    DFG::resetFlags(baseNode);

    DFG::collectReadNodes(baseNode,readNodes);

}

void DFG::collectReadNodes(DFGNode* baseNode,std::vector<DFGReadNode*> &readNodes){
    
    if((baseNode->getType() == NodeType::ReadNode || baseNode->getType() == NodeType::OffsetRead)
        && !baseNode->getFlag())
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
    int trueSucc = 0;

    while(startingNode->getSuccessors().size() != trueSucc)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                trueSucc=0;
                break;
            }else{
                trueSucc++;
            }

    if(startingNode != node)
        collectReadNodes(startingNode,readNodes);
    else
        if((startingNode->getType() == NodeType::ReadNode || startingNode->getType() == NodeType::OffsetRead)
           && !startingNode->getFlag())
            readNodes.push_back((DFGReadNode*)startingNode);
}    

void DFG::getWriteNodes(DFGNode* baseNode,std::vector<DFGWriteNode*> &writeNodes){
    
    DFG::resetFlags(baseNode);
    
    DFG::collectWriteNodes(baseNode,writeNodes);

}

void DFG::collectWriteNodes(DFGNode* baseNode,std::vector<DFGWriteNode*> &writeNodes){

    if((baseNode->getType() == NodeType::WriteNode || baseNode->getType() == NodeType::OffsetWrite)
       && !baseNode->getFlag())
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
    int trueSuccCount = 0;

    while(startingNode->getSuccessors().size() != trueSuccCount)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                trueSuccCount=0;
                break;
            }else{
                trueSuccCount++;
            }
    if(startingNode != node)
        collectWriteNodes(startingNode,writeNodes);
    else
    {
        if((startingNode->getType() == NodeType::WriteNode || startingNode->getType() == NodeType::OffsetWrite)
           && !startingNode->getFlag())
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

std::vector<DFGNode*> DFG::getScalarArguments(DFGNode* baseNode,llvm::Function* F){

    std::vector<DFGNode*> sortedNodes;
    std::vector<DFGNode*> scalarArgs;
    
    resetFlags(baseNode);
    sortedNodes = orderNodesWithFunc(F);
    
    for(DFGNode* n : sortedNodes)
    {
        if(llvm::dyn_cast<llvm::Argument>(n->getValue()))
        {
            scalarArgs.push_back(n);
        }
    }
    
    return scalarArgs;
}

std::vector<DFGNode*> DFG::getUniqueScalarArguments(DFGNode* baseNode,llvm::Function *F){
    
    std::vector<DFGNode*> scalarArguments;
    std::vector<DFGNode*> uniqueScalarArguments;
    
    scalarArguments = getScalarArguments(baseNode,F);
    
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

void DFG::fuseIdenticalNodes(){
    //TODO delete this method
    resetFlags(endNode);

}

int DFG::getNodesCount(){
    
    int count;

    DFG::resetFlags(DFG::endNode);
    //count = DFG::countChildren(DFG::endNode,count);
    count = DFG::simpleCount(DFG::endNode);
    llvm::errs() << "Count end: " << count << "\n";
    DFG::resetFlags(DFG::endNode);

    return count;
}

void DFG::resetFlags(DFGNode* node){

    resetMarkedFlags(node);
}

void DFG::resetMarkedFlags(DFGNode* node){

    node->setFlag(false);

    for(DFGNode* succ : node->getSuccessors()){
        if(succ->getFlag())
            resetFlags(succ);
    }

    for(DFGNode* pred : node->getPredecessors()) {
        if (pred->getFlag())
            resetFlags(pred);
    }
}

void DFG::descendAndReset(DFGNode* node){

    DFGNode* nodeToReset = node;
    int trueSuccCount = 0;

    while(nodeToReset->getSuccessors().size() != trueSuccCount){
        for(DFGNode* succ : nodeToReset->getSuccessors()){
            if(succ->getFlag()){
                nodeToReset = succ;
                trueSuccCount++;
                break;
            } else {
                trueSuccCount++;
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
    
    simpleSetNames(nodeNames,node);
    // setNames(nodeNames,node);

}

void DFG::simpleSetNames(std::vector<std::string> &nodeNames, DFGNode *node) {

    if(nodeNames.size() < 1 && node->getFlag())
    {
        llvm::errs() << "Exhausted node names\n";
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
            if(CFP->getType()->isDoubleTy()) {
                double val = CFP->getValueAPF().convertToDouble();
                node->setName(std::to_string(val));
            }else{
                float val = CFP->getValueAPF().convertToFloat();
                node->setName(std::to_string(val));
            }
            nodeNames.pop_back();
        }

        if(llvm::ConstantInt* CFP = llvm::dyn_cast<llvm::ConstantInt>(node->getValue()))
        {
            if(node->getType() == NodeType::Offset){
                node->setName(nodeNames.back());
                nodeNames.pop_back();
            }else{
                node->setName(std::to_string(CFP->getZExtValue()));
                nodeNames.pop_back();
            }
        }

    }

    node->setFlag(true);

    for(DFGNode* succ : node->getSuccessors()){
        if(!succ->getFlag())
            simpleSetNames(nodeNames,succ);
    }
    for(DFGNode* pred : node->getPredecessors()){
        if(!pred->getFlag())
            simpleSetNames(nodeNames,pred);
    }
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
            if(CFP->getType()->isDoubleTy()) {
                double val = CFP->getValueAPF().convertToDouble();
                node->setName(std::to_string(val));
            }else{
                float val = CFP->getValueAPF().convertToFloat();
                node->setName(std::to_string(val));
            }
            nodeNames.pop_back();
        }

        if(llvm::ConstantInt* CFP = llvm::dyn_cast<llvm::ConstantInt>(node->getValue()))
        {
            if(node->getType() == NodeType::Offset){
                node->setName(nodeNames.back());
                nodeNames.pop_back();
            }else{
                node->setName(std::to_string(CFP->getZExtValue()));
                nodeNames.pop_back();
            }
        }

    }

    node->setFlag(true);
    
    for(DFGNode* succ : node->getSuccessors())
        if(!succ->getFlag())
            descendAndSetNames(nodeNames,node);
            
    std::vector<DFGNode*> pred;
    pred = node->getPredecessors();
    std::vector<DFGNode*> revPred(pred.size());
    std::reverse_copy(std::begin(pred),std::end(pred),std::begin(revPred));
    
    for(DFGNode* pred : revPred)
        if(!pred->getFlag())
            setNames(nodeNames,pred);
}

void DFG::descendAndSetNames(std::vector<std::string> &nodeNames, DFGNode* node){
    
    DFGNode* nodeToSet = node;
    int trueSuccCount = 0;

    while(nodeToSet->getSuccessors().size() != trueSuccCount){
        for(DFGNode* succ : nodeToSet->getSuccessors()){
            if(!succ->getFlag()){
                nodeToSet = succ;
                trueSuccCount=0;
                break;
            }else{
                trueSuccCount++;
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

void DFG::simplePrintDFG(DFGNode *startingNode) {

    startingNode->printNode();
    startingNode->setFlag(true);

    for(DFGNode* pred : startingNode->getPredecessors()){
        if(!pred->getFlag())
            simplePrintDFG(pred);
    }

    for(DFGNode* succ : startingNode->getSuccessors()){
        if(!succ->getFlag())
            simplePrintDFG(succ);
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

    simplePrintDFG(endNode);
    //printDFG(endNode);
}

void DFG::descendAndPrint(DFGNode* node){
    
    DFGNode* nodeToPrint = node;
    int trueSuccCount = 0;

    while(nodeToPrint->getSuccessors().size() != trueSuccCount) {
        for (DFGNode* succ : nodeToPrint->getSuccessors()) {
            if(!succ->getFlag()){
                nodeToPrint = succ;
                trueSuccCount = 0;
                break;
            } else {
                trueSuccCount++;
            }
        }
    }
    if(nodeToPrint != node)
        printDFG(nodeToPrint);
}

int DFG::simpleCount(DFGNode *n) {

    int count = 1;
    n->setFlag(true);

    for(DFGNode* succ : n->getSuccessors()){
        if(!succ->getFlag())
            count += simpleCount(succ);
    }
    for(DFGNode* pred : n->getPredecessors()){
        if(!pred->getFlag())
            count += simpleCount(pred);
    }
    return count;

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
    int trueSuccCount = 0;
    std::vector<DFGNode*> visitedNodes;

    while(startingNode->getSuccessors().size() != trueSuccCount) {
        for (DFGNode *succ : startingNode->getSuccessors()) {
            if (!succ->getFlag()) {
                if(std::find(visitedNodes.begin(),visitedNodes.end(),succ) != visitedNodes.end()){

                }
                startingNode = succ;
                visitedNodes.push_back(startingNode);
                trueSuccCount = 0;
                break;
            } else {
                trueSuccCount++;
            }
        }
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

void DFG::setDFGFlags(){

    setFlags(DFG::getEndNode());
}

void DFG::setFlags(DFGNode* node) {

    node->setFlag(true);

    for(DFGNode* succ : node->getSuccessors())
        if(!succ->getFlag())
            setFlags(succ);

    for(DFGNode* pred : node->getPredecessors())
        if(!pred->getFlag())
            setFlags(pred);

    return;
}

void DFG::descendAndSet(DFGNode* node){

    DFGNode* startingNode = node;
    int trueSuccCount = 0;

    while(startingNode->getSuccessors().size() != trueSuccCount)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                trueSuccCount=0;
                break;
            }else{
                trueSuccCount++;
            }
    if(startingNode != node)
        setFlags(startingNode);
    else
        if(!startingNode->getFlag()){
            startingNode->setFlag(true);
        }

    return;
}

void DFG::orderNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted, int baseSize){

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

std::vector<DFGNode*> DFG::orderNodesWithFunc(llvm::Function *F) {

    std::vector<DFGNode*> nodes = getGraphNodes();
    std::vector<DFGNode*> sortedNodes;

    for(llvm::BasicBlock &BB : *F){
        for(llvm::Instruction &instr : BB){
            for(auto it = nodes.begin(); it != nodes.end(); ++it){
                if(&instr == (*it)->getValue() && !(*it)->getFlag()) {
                    for(DFGNode* pred : (*it)->getPredecessors())
                        if(!pred->getFlag()) {
                            pred->setFlag(true);
                            sortedNodes.push_back(pred);
                            auto pred_it = std::find(nodes.begin(),nodes.end(),pred);
                            if(pred_it != nodes.end())
                                nodes.erase(pred_it);

                        }
                    (*it)->setFlag(true);
                    sortedNodes.push_back(*it);
                    break;
                }

            }
        }
    }
    resetFlags(endNode);
    return sortedNodes;
}

std::vector<DFGNode*> DFG::getGraphNodes() {

    std::vector<DFGNode*> nodes;

    resetFlags(endNode);
    collectNode(endNode,nodes);
    resetFlags(endNode);

    return nodes;
}

void DFG::collectNode(DFGNode *n, std::vector<DFGNode*> &nodes) {

    n->setFlag(true);
    nodes.push_back(n);

    for(DFGNode* pred : n->getPredecessors())
        if(!pred->getFlag())
            collectNode(pred,nodes);

    for(DFGNode* succ : n->getSuccessors())
        if(!succ->getFlag())
            collectNode(succ,nodes);
}

void DFG::getUniqueOrderedNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted,int baseSize){

    orderNodes(n,pos,sorted,baseSize);

    for(auto n_it = sorted.begin(); n_it != sorted.end(); ++n_it)
        for(DFGNode* n_2 : sorted)
            if(*n_it != n_2 && (*n_it)->getValue() == n_2->getValue()) {
                sorted.erase(std::remove(sorted.begin(), sorted.end(), n_2), sorted.end());
            }
}

//DFGConstructor methods implementation

std::vector<DFG*> DFGConstructor::computeIOStreamBasedDFG(llvm::Loop* topLevelLoop, IOStreams* IOs,
                                                          llvm::ScalarEvolution* SE, int loopIndex){

    std::vector<DFG*> computedDFGs;

    LoopAnalysisResult* loopInfo = scheduler->analysisResult->getLoopInfo(loopIndex);
    int loopTripCount = loopInfo->getLoopTripCount()->getTripCount();

    //iterates over the loop body instructions

    for(llvm::BasicBlock *BB : topLevelLoop->blocks()){
        if(BB != topLevelLoop->getHeader() &&
            BB != topLevelLoop->getLoopLatch()){

            initiateDFGConstruction(computedDFGs,IOs,topLevelLoop,SE,loopTripCount,BB);
        }
    }

    //TODO: chech if dfgs are indipendent

    std::vector<DFG*> indipendentGraphs;

    for(DFG* dfg : computedDFGs)
        dfg->resetFlags(dfg->getEndNode());

    for(DFG* dfg : computedDFGs){

        if(!dfg->getEndNode()->getFlag())
            indipendentGraphs.push_back(dfg);

        dfg->setDFGFlags();
    }

    computedDFGs = indipendentGraphs;

    for(DFG* dfg : indipendentGraphs)
        dfg->resetFlags(dfg->getEndNode());

    if(computedDFGs.size() != 0){
        DFGConstructor::scheduler->schedule(new DFGLinker(computedDFGs,F));
        DFGConstructor::scheduler->executeNextComponent();
        
        return DFGConstructor::scheduler->dataflowGraph;
        
    }else{
        llvm::errs() << "Single DFG during loop dfg construction...\n";
        return computedDFGs;
    }
}

void DFGConstructor::initiateDFGConstruction(std::vector<DFG*> &computedDFGs,IOStreams* IOs,
                                             llvm::Loop* topLevelLoop,llvm::ScalarEvolution* SE,
                                             int loopTripCount,llvm::BasicBlock* BB){

    DFGNodeFactory* nodeFactory = new DFGNodeFactory();

    for(llvm::Instruction &instr : BB->getInstList()){

        //if a store is found, and the store refers to an output stream,
        //a DFG is computed with the store as its base, and it is added
        //to the DFG vector
        if(llvm::StoreInst* store = llvm::dyn_cast<llvm::StoreInst>(&instr)){
            if(llvm::Instruction* storeAddr = llvm::dyn_cast<llvm::Instruction>(store->getOperand(1))) {

                llvm::Instruction *allocaInstr = nullptr;
                StreamPair stream;

                if (llvm::Instruction *i = llvm::dyn_cast<llvm::Instruction>(storeAddr->getOperand(0))) {
                    allocaInstr = i;
                }
                if(allocaInstr != nullptr && allocaInstr->getOpcodeName() == std::string("alloca")) {
                    stream = IOs->getInStreamFromGEP((llvm::GetElementPtrInst *) storeAddr);

                    if (stream.second != nullptr) {

                        DFGOffsetWriteNode *offsetNode = nodeFactory->createDFGOffsetWriteNode(&instr, IOs, stream.second,loopTripCount);
                        computedDFGs.push_back(
                                computeDFGFromBase(offsetNode, IOs,loopTripCount,topLevelLoop));
                    } else {

                        computedDFGs.push_back(
                                computeDFGFromBase(nodeFactory->createDFGWriteNode(&instr, IOs,loopTripCount), IOs,loopTripCount,topLevelLoop));
                    }
                }

                stream = storedOutputStream(store,IOs,SE);

                if (stream.first != nullptr) {
                    if(stream.second == nullptr)
                        computedDFGs.push_back(
                                computeDFGFromBase(nodeFactory->createDFGWriteNode(&instr, IOs,loopTripCount),IOs,loopTripCount, topLevelLoop));
                    else{
                        DFGOffsetWriteNode* offsetNode = nodeFactory->createDFGOffsetWriteNode(&instr,IOs,stream.second,loopTripCount);
                        llvm::errs() << "Equals: " << offsetNode->equals(offsetNode);
                        computedDFGs.push_back(
                                computeDFGFromBase(offsetNode, IOs,loopTripCount, topLevelLoop));
                    }
                }

            }
        }
    }
}

void DFGConstructor::initiateStaticDFGConstruction(std::vector<DFG *> &computedDFGs, IOStreams *IOs,
                                                   llvm::ScalarEvolution *SE, llvm::BasicBlock *BB) {

    DFGNodeFactory* nodeFactory = new DFGNodeFactory();

    for (llvm::Instruction &instr : BB->getInstList()) {

        //if a store is found, and the store refers to an output stream,
        //a DFG is computed with the store as its base, and it is added
        //to the DFG vector
        if (llvm::StoreInst *store = llvm::dyn_cast<llvm::StoreInst>(&instr)) {
            if (llvm::Instruction *storeAddr = llvm::dyn_cast<llvm::Instruction>(store->getOperand(1))) {

                StreamPair stream;

                stream = IOs->getInStreamFromGEP((llvm::GetElementPtrInst*) storeAddr);
                const llvm::SCEV *streamOfs = stream.second;

                if (streamOfs != nullptr && streamOfs->getSCEVType() != llvm::SCEVTypes::scConstant) {

                    llvm::errs() << "Non const offset in static DFG\n";
                    streamOfs->dump();
                    exit(EXIT_FAILURE);

                } else {

                    llvm::Value *ofsVal = (*(SE->getSCEVValues(streamOfs)->begin())).first;

                    if (llvm::ConstantInt *constIndex = llvm::dyn_cast<llvm::ConstantInt>(ofsVal)) {
                        int accessIndex = constIndex->getSExtValue();

                        computedDFGs.push_back(
                                computeDFGFromBase(nodeFactory->createDFGWriteNode(&instr, IOs, accessIndex,accessIndex), IOs, accessIndex,
                                                   nullptr));

                    } else {
                        llvm::errs() << "INFO: invalid index in constant access...\n";
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }
}

DFGNode* DFGConstructor::constructNode(llvm::Value *value, DFGNode *parentNode, llvm::Loop *loop,
                                   DFGNodeFactory *nodeFactory, IOStreams *IOs, int loopTripCount) {

    if(loop != nullptr) {

        if (llvm::Instruction *operandAsInstr = llvm::dyn_cast<llvm::Instruction>(value)) {
            //these checks identify a DFGReadNode which accesses a stream
            //through the exact value of the canonical induction variable
            //at any given iteration
            if (operandAsInstr->getOpcodeName() == std::string("load")) {
                //TODO: rewrite this code...
                llvm::Instruction *getelemPtrInstr = getInstrFromOperand(
                        operandAsInstr->getOperand(0), std::string("getelementptr"));

                bool cond_1 = getelemPtrInstr->getNumOperands() == 2 &&
                              getelemPtrInstr->getOperand(1) == loop->getCanonicalInductionVariable();
                bool cond_2 = getelemPtrInstr->getNumOperands() == 3 &&
                              getelemPtrInstr->getOperand(2) == loop->getCanonicalInductionVariable();

                if (getelemPtrInstr != nullptr &&
                    (hasSextOnIndvar(getelemPtrInstr, loop) || cond_1 || cond_2)) {
                    DFGReadNode *childNode = nodeFactory->createDFGReadNode(value, IOs, loopTripCount);

                    if(parentNode != nullptr)
                        parentNode->linkPredecessor(childNode);

                    return childNode;
                } else {
                    llvm::errs() << "Getelemptr may be offset node: ";
                    getelemPtrInstr->dump();
                    llvm::GetElementPtrInst *gep = llvm::dyn_cast<llvm::GetElementPtrInst>(getelemPtrInstr);

                    StreamPair stream = StreamPair(nullptr, nullptr);

                    if (gep != nullptr)
                        stream = IOs->getInStreamFromGEP(gep);

                    if (stream.second != nullptr) {
                        llvm::errs() << "Creating offset read node...\n";
                        DFGOffsetReadNode *childNode = nodeFactory->createDFGOffsetReadNode(value, IOs, stream.second,
                                                                                            loopTripCount);
                        if(parentNode != nullptr)
                            parentNode->linkPredecessor(childNode);

                        return childNode;
                    } else {
                        llvm::errs() << "Node was without offset after all...\n";
                        DFGReadNode *childNode = nodeFactory->createDFGReadNode(value, IOs, loopTripCount);
                        if(parentNode != nullptr)
                            parentNode->linkPredecessor(childNode);

                        return childNode;
                    }

                }

            } else {
                //Node initialization for a generic instruction

                if (llvm::PHINode *phi = llvm::dyn_cast<llvm::PHINode>(operandAsInstr)) {
                    if (oxigen::isCounterForLoop(phi, loop)) {

                        DFGCounterNode *loopCounter = nodeFactory->createDFGCounterNode(phi);

                        if(parentNode != nullptr)
                            parentNode->linkPredecessor(loopCounter);

                        loopCounters.push_back(CounterPair(loop, loopCounter));
                        populateDFG(loopCounter, IOs, loopTripCount, loop);
                        return loopCounter;

                    }else{

                        DFGAccNode* accVariable = nodeFactory->createDFGAccNode(operandAsInstr);
                        parentNode->linkPredecessor(accVariable);

                        if(parentNode != nullptr)
                            parentNode->linkPredecessor(accVariable);

                        populateDFG(accVariable, IOs, loopTripCount, loop);
                        return accVariable;
                    }

                } else {

                    DFGNode *childNode = nodeFactory->createDFGNode(value);

                    if(parentNode != nullptr)
                        parentNode->linkPredecessor(childNode);

                    populateDFG(childNode, IOs, loopTripCount, loop);
                    return childNode;
                }
            }
        } else {
            //Node initializaton for a generic llvm::Value which is not an
            //instruction

            if((!llvm::dyn_cast<llvm::Function>(value))){
                DFGNode *childNode = nodeFactory->createDFGNode(value);

                if(parentNode != nullptr)
                    parentNode->linkPredecessor(childNode);

                return childNode;
            }else{
                llvm::errs() << "INFO: function called found. Node ignored...\n";
                return nullptr;
            }
        }
    }else{

        if(llvm::LoadInst* load = llvm::dyn_cast<llvm::LoadInst>(value)){

            if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(load->getPointerOperand())){

                llvm::Value* gep_idx = *(gep->idx_end() - 1);

                if(llvm::ConstantInt* const_idx = llvm::dyn_cast<llvm::ConstantInt>(gep_idx)){

                    int index = const_idx->getSExtValue();

                    if(index-loopTripCount == 0){
                        DFGReadNode *childNode = nodeFactory->createDFGReadNode(
                                value, IOs, index-loopTripCount, index-loopTripCount);

                        if(parentNode != nullptr)
                            parentNode->linkPredecessor(childNode);

                        return childNode;
                    }else{

                        DFGReadNode *childNode = nodeFactory->createDFGReadNode(
                                value, IOs, index-loopTripCount, index-loopTripCount);

                        if(parentNode != nullptr)
                            parentNode->linkPredecessor(childNode);

                        return childNode;
                    }

                }else{
                    llvm::errs() << "ERROR: non constant index in static DFG\n";
                    exit(EXIT_FAILURE);
                }
            }else{
                llvm::errs() << "ERROR: unexpected load pointer operand in static DFG\n";
                exit(EXIT_FAILURE);
            }

        } else if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value)){

            //Node initialization for a generic instruction
            if (instr->getOpcodeName() == std::string("sext")) {
                llvm::errs() << "INFO: attempting to insert sext in static DFG\n";
                return nullptr;
            }

            DFGNode *childNode = nodeFactory->createDFGNode(value);

            if(parentNode != nullptr)
                parentNode->linkPredecessor(childNode);

            populateDFG(childNode, IOs, loopTripCount, loop);
            return childNode;

        } else {
            //Node initializaton for a generic llvm::Value which is not an
            //instruction
            if((!llvm::dyn_cast<llvm::Function>(value))){
                DFGNode *childNode = nodeFactory->createDFGNode(value);

                if(parentNode != nullptr)
                    parentNode->linkPredecessor(childNode);

                return childNode;
            }else{
                llvm::errs() << "INFO: function called found. Node ignored...\n";
                return nullptr;
            }
        }
    }

}

void DFGConstructor::constructNodeForOperands(std::vector<llvm::Value*> instructionOperands,DFGNode* node,
                                              llvm::Loop* loop, DFGNodeFactory* nodeFactory, IOStreams* IOs, int loopTripCount) {

    for(llvm::Value* operandVal : instructionOperands){
        constructNode(operandVal,node,loop,nodeFactory,IOs,loopTripCount);
    }


}

void DFGConstructor::populateDFG(DFGNode* node, IOStreams* IOs,int loopTripCount,
                                 llvm::Loop* loop){

    DFGNodeFactory* nodeFactory = new DFGNodeFactory();
    llvm::Value* parentVal = node->getValue();
    llvm::errs() << "\nINFO: initializing node for ";
    parentVal->dump();

    std::vector<llvm::Value*> operands;

    if(llvm::dyn_cast<llvm::LoadInst>(parentVal))
        return;
    else if(llvm::PHINode* phiNode = llvm::dyn_cast<llvm::PHINode>(parentVal)) {
        if(!node->getFlag()) {
            node->setFlag(true);
            operands.push_back(phiNode->getIncomingValue(0));
            llvm::Value *dependenceCarryingPredecessor = phiNode->getIncomingValue(1);
            DFGNode* childNode = constructNode(dependenceCarryingPredecessor,nullptr,loop,nodeFactory,IOs,loopTripCount);
            node->linkLoopCarriedPredecessor(childNode);
            constructNodeForOperands(operands,node,loop,nodeFactory,IOs,loopTripCount);
        }

    }else if(llvm::Instruction* parentInstr = llvm::dyn_cast<llvm::Instruction>(parentVal)) {
        for(llvm::Value* v : parentInstr->operands())
            operands.push_back(v);

        constructNodeForOperands(operands,node,loop,nodeFactory,IOs,loopTripCount);
    }else {
        llvm::errs() << "Non instr parent\n";
    }
}

DFG* DFGConstructor::computeDFGFromBase(DFGWriteNode* baseNode, IOStreams* IOs,int loopTripCount,llvm::Loop* loop){
        
    //intializes a new DFG object
    DFG* graph = new DFG(baseNode);
    //populates it from its base node
    populateDFG(shortcutSoreGetelementPtr(baseNode,IOs,loop,loopTripCount),IOs,loopTripCount,loop);

    graph->resetFlags(baseNode);

    return graph;
}

std::vector<DFG*> DFGConstructor::computeStaticDFG(IOStreams* IOs,llvm::ScalarEvolution* SE,
                                                   llvm::LoopInfo* LI,llvm::Function* F,llvm::BasicBlock* start){

    std::vector<DFG*> dfgs = std::vector<DFG*>();
    bool atCurrentBlock = false;

    for(llvm::Function::iterator BB_it = F->begin(); BB_it != F->end(); ++BB_it){

        if(&(*BB_it) == start)
            atCurrentBlock = true;

        //TODO: clean up
        if(LI->getLoopDepth(&(*BB_it)) == 22 && atCurrentBlock){

            initiateStaticDFGConstruction(dfgs,IOs,SE,&(*BB_it));

        }else{

            if(atCurrentBlock)
                break;
        }
    }

    return dfgs;
}

llvm::Instruction* DFGConstructor::getInstrFromOperand(llvm::Value* value, std::string opcodeName){
        
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(value))
        if(instr->getOpcodeName() == opcodeName)
            return instr;
    return nullptr;
}

DFGNode* DFGConstructor::shortcutSoreGetelementPtr(DFGWriteNode* storeNode,IOStreams* IOs,llvm::Loop* loop,int loopTripCount){

    llvm::Instruction* storeInstr = (llvm::Instruction*) storeNode->getValue();
    DFGNodeFactory* nodeFactory = new DFGNodeFactory();

    DFGNode* startingNode;

    if(llvm::Instruction* cInstr = llvm::dyn_cast<llvm::Instruction>(storeInstr->getOperand(0))){
        if (cInstr->getOpcodeName() == std::string("load")) {
            startingNode = nodeFactory->createDFGReadNode(cInstr, IOs,loopTripCount);
            storeNode->linkPredecessor(startingNode);
            return startingNode;
        }
        if (cInstr->getOpcodeName() == std::string("store")) {
            startingNode = nodeFactory->createDFGWriteNode(cInstr, IOs,loopTripCount);
            storeNode->linkPredecessor(startingNode);
            return startingNode;
        }
    }

    if (llvm::Instruction *operandAsInstr = llvm::dyn_cast<llvm::Instruction>(storeInstr->getOperand(0))) {

        //Node initialization for a generic instruction
        if (llvm::PHINode *phi = llvm::dyn_cast<llvm::PHINode>(operandAsInstr)) {
            if (oxigen::isCounterForLoop(phi, loop)) {

                DFGCounterNode *loopCounter = nodeFactory->createDFGCounterNode(phi);
                storeNode->linkPredecessor(loopCounter);
                loopCounters.push_back(CounterPair(loop, loopCounter));
                return loopCounter;
            }else{
                //TODO: check graph continuation after acc var
                DFGAccNode* accVariable = nodeFactory->createDFGAccNode(operandAsInstr);
                storeNode->linkPredecessor(accVariable);
                llvm::errs() << "Acc node created in shortcut\n";
                return accVariable;
            }
        } else {
            DFGNode *childNode = nodeFactory->createDFGNode(storeInstr->getOperand(0));
            storeNode->linkPredecessor(childNode);
            return childNode;
        }

    } else {
        //Node initializaton for a generic llvm::Value which is not an
        //instruction

        if((!llvm::dyn_cast<llvm::Function>(storeInstr->getOperand(0)))){
            DFGNode *childNode = nodeFactory->createDFGNode(storeInstr->getOperand(0));
            storeNode->linkPredecessor(childNode);
            return childNode;
        }else{
            llvm::errs() << "INFO: function called found. Node ignored...\n";
        }
    }

    startingNode = nodeFactory->createDFGNode(storeInstr->getOperand(0));
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

StreamPair DFGConstructor::storedOutputStream(llvm::StoreInst* store, IOStreams* IOs, llvm::ScalarEvolution* SE){

    if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(store->getPointerOperand())){
        const llvm::SCEV* idx_scev = SE->getSCEV(*(gep->idx_begin()));

        if(idx_scev != nullptr)
            if(const llvm::SCEVAddRecExpr* addRec = llvm::dyn_cast<llvm::SCEVAddRecExpr>(idx_scev))
                for(StreamPair p : IOs->getOutputStreams()){
                    if(p.first == gep->getPointerOperand() &&
                            (p.second == addRec->getStart() || (p.second == nullptr && addRec->getStart()->isZero())))
                        return p;
                }
    }

    return StreamPair(nullptr, nullptr);
}

///DFGFactory methods implementations

DFGNode* DFGNodeFactory::createDFGNode(llvm::Value *value, int loopTripCount){

    DFGNode* listedNode = getNodeIfListed(value,NodeType::Node);
    bool isConstant = llvm::dyn_cast<llvm::Constant>(value);

    if(listedNode != nullptr && !isConstant)
        return listedNode;
    else {
        DFGNode* n = new DFGNode(value, loopTripCount);
        globalNodesList.push_back(n);
        llvm::errs() << "\nINFO: created node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGAccNode* DFGNodeFactory::createDFGAccNode(llvm::Value *value, int loopTripCount) {

    DFGAccNode* listedNode = (DFGAccNode*)getNodeIfListed(value,NodeType::AccumulNode);

    if(listedNode != nullptr) {
        return listedNode;
    } else{
        DFGAccNode* n = new DFGAccNode(value,loopTripCount);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created acc node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGCounterNode* DFGNodeFactory::createDFGCounterNode(llvm::PHINode *value, int loopTripCount) {

    DFGCounterNode* listedNode = (DFGCounterNode*)getNodeIfListed(value,NodeType::CounterNode);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGCounterNode* n =  new DFGCounterNode(value,loopTripCount);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created counter node: ";
        n->getValue()->dump();
        return n;
    }

}

DFGLoopNode* DFGNodeFactory::createDFGLoopNode(llvm::Loop *loop) {

    DFGLoopNode* n = new DFGLoopNode(loop);

    DFGLoopNode* listedNode = (DFGLoopNode*)getNodeIfListed(n->getValue(),NodeType::LoopNode);

    if(listedNode != nullptr){
        delete(n);
        return listedNode;
    }else{
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created loop node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGNode* DFGNodeFactory::getNodeIfListed(llvm::Value *nVal, NodeType type) {

    for(DFGNode* el : globalNodesList){
        if(el->getValue() == nVal && el->getType() == type)
            return el;
    }
    return nullptr;

}

DFGMuxNode* DFGNodeFactory::createDFGMuxNode(DFGNode *node_1, DFGNode *node_2, TickBasedCondition *cond) {

    DFGMuxNode* n = new DFGMuxNode(node_1,node_2,cond);

    DFGMuxNode* listedNode = (DFGMuxNode*)getNodeIfListed(n->getValue(),NodeType::MuxNode);

    if(listedNode != nullptr){
        delete(n);
        return listedNode;
    }else{
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created mux node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGOffsetNode* DFGNodeFactory::createDFGOffsetNode(DFGNode *baseNode) {

    DFGOffsetNode* n = new DFGOffsetNode(baseNode);

    DFGOffsetNode* listedNode = (DFGOffsetNode*)getNodeIfListed(n->getValue(),NodeType::Offset);
    bool isConstant = llvm::dyn_cast<llvm::Constant>(n->getValue());

    if(listedNode != nullptr && !isConstant){
        delete(n);
        return listedNode;
    }else{
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created offset node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGOffsetReadNode* DFGNodeFactory::createDFGOffsetReadNode(llvm::Value *value, IOStreams *IOs, const llvm::SCEV *offset,
                                                           int loopTripCount) {

    DFGOffsetReadNode* listedNode = (DFGOffsetReadNode*)getNodeIfListed(value,NodeType::OffsetRead);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGOffsetReadNode* n =  new DFGOffsetReadNode(value,IOs,offset,loopTripCount);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created offset read node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGOffsetWriteNode* DFGNodeFactory::createDFGOffsetWriteNode(llvm::Value *value, IOStreams *IOs,
                                                             const llvm::SCEV *offset, int loopTripCount) {

    DFGOffsetWriteNode* listedNode = (DFGOffsetWriteNode*)getNodeIfListed(value,NodeType::OffsetWrite);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGOffsetWriteNode* n =  new DFGOffsetWriteNode(value,IOs,offset,loopTripCount);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created offset write node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGReadNode* DFGNodeFactory::createDFGReadNode(llvm::Value *value, IOStreams *loopStreams, int loopTripCount) {

    DFGReadNode* listedNode = (DFGReadNode*)getNodeIfListed(value,NodeType::ReadNode);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGReadNode* n =  new DFGReadNode(value,loopStreams,loopTripCount);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created read node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGReadNode* DFGNodeFactory::createDFGReadNode(llvm::Value *value, IOStreams *loopStreams, int windowSart,
                                               int windowEnd) {

    DFGReadNode* listedNode = (DFGReadNode*)getNodeIfListed(value,NodeType::ReadNode);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGReadNode* n =  new DFGReadNode(value,loopStreams,windowSart,windowEnd);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created read node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGWriteNode* DFGNodeFactory::createDFGWriteNode(llvm::Value *value, IOStreams *loopStreams, int loopTripCount) {

    DFGWriteNode* listedNode = (DFGWriteNode*)getNodeIfListed(value,NodeType::WriteNode);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGWriteNode* n =  new DFGWriteNode(value,loopStreams,loopTripCount);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created write node: ";
        n->getValue()->dump();
        return n;
    }
}

DFGWriteNode* DFGNodeFactory::createDFGWriteNode(llvm::Value *value, IOStreams *loopStreams, int windowStart,
                                                 int windowEnd) {

    DFGWriteNode* listedNode = (DFGWriteNode*)getNodeIfListed(value,NodeType::WriteNode);

    if(listedNode != nullptr)
        return listedNode;
    else{
        DFGWriteNode* n =  new DFGWriteNode(value,loopStreams,windowStart,windowEnd);
        globalNodesList.push_back((DFGNode*)n);
        llvm::errs() << "\nINFO: created write node: ";
        n->getValue()->dump();
        return n;
    }
}

///Namespace helper methods declarations

void oxigen::insertNode(DFGNode* n,DFGNode* pred,DFGNode* succ,bool areConsecutive = false){

    if(areConsecutive){
        succ->insertPredecessor(pred,n);
    }else{
        succ->linkPredecessor(n);
        n->linkPredecessor(pred);
    }

}

bool oxigen::isCounterForLoop(llvm::PHINode *phi, llvm::Loop *L) {

    for(auto it = L->getHeader()->begin(); it != L->getHeader()->end(); ++it) {

        if (llvm::BranchInst *br = llvm::dyn_cast<llvm::BranchInst>(it)) {
            if (llvm::CmpInst *cmp = llvm::dyn_cast<llvm::CmpInst>(br->getCondition())) {
                if (llvm::PHINode *exitPhi = llvm::dyn_cast<llvm::PHINode>(cmp->getOperand(0))) {
                    if(exitPhi == phi)
                        return true;
                }
            }
        }
    }
    return false;
}

llvm::PHINode* oxigen::getLoopCounterIfAny(llvm::Loop* loop){

    llvm::BasicBlock* header = loop->getHeader();

    for(llvm::Instruction &instr : *header){
        if(llvm::PHINode* phi = llvm::dyn_cast<llvm::PHINode>(&instr)){
            if(oxigen::isCounterForLoop(phi,loop))
                return phi;
        }
    }
    return nullptr;
}

void oxigen::transferSuccessors(DFGNode* currentParent,DFGNode* newParent){

    for(DFGNode* child : currentParent->getSuccessors()){
        if(child != newParent){
            child->changeParent(currentParent,newParent);
        }
    }
}

void oxigen::transferPredecessors(DFGNode* currentSuccessor,DFGNode* newSuccessor){

    for(DFGNode* pred : currentSuccessor->getPredecessors()){
        if(pred != newSuccessor) {
            int pos = currentSuccessor->getPredecessorPosition(pred);
            currentSuccessor->unlinkPredecessor(pred);
            newSuccessor->linkPredecessor(pred,pos);
        }
    }
}

void oxigen::eliminateNode(DFGNode* node){

    llvm::errs() << "Attempting elimination of "; node->getValue()->dump();
    if((node->getSuccessors().size() > 1 && node->getPredecessors().size() > 1) ||
            node->getSuccessors().size() == 0 || node->getPredecessors().size() == 0) {
        llvm::errs() << "Node elimination impossible: ambiguous dependencies\n";
        return;
    }

    if(node->getSuccessors().size() > 1){

        node->unlinkPredecessor(node->getPredecessors().at(0));
        for(DFGNode* s : node->getSuccessors()){
            s->changeParent(node,node->getPredecessors().at(0));
        }

    }else{

        DFGNode* newSucc = node->getSuccessors().at(0);
        newSucc->unlinkPredecessor(node);

        for(DFGNode* p : node->getPredecessors()){
            node->unlinkPredecessor(p);
            newSucc->linkPredecessor(p);
        }
    }
}

void oxigen::fuseNodes(DFGNode *n_1, DFGNode *n_2,std::vector<DFGNode*> &exceptionVector) {
/*
    transferSuccessors(n_1,n_2);
    transferPredecessors(n_1,n_2);

    if(n_1->getSuccessors().size() == 0 && n_1->getPredecessors().size() == 0){
        llvm::errs() << "Deleting disconnected node \n";
        if(n_1 != nullptr)
            delete(n_1);
    }
*/
}


std::vector<DFGNode*> oxigen::getElementarPredecessors(std::vector<DFGNode*> nodes, DFGNode* succNode){

    std::vector<NodeType> compositeNodeTypes = oxigen::getCompositeTypes();
    std::vector<DFGNode*> predecessors;

    for(DFGNode* n : nodes){
        for(NodeType type : compositeNodeTypes){
            if(n->getType() == type){
                std::vector<DFGNode *> n_preds = oxigen::getNodePredecessors(n, type, succNode);
                predecessors.insert(predecessors.end(), n_preds.begin(), n_preds.end());
            }
        }
        if(!oxigen::isComposite(n->getType()))
            predecessors.push_back(n);
    }

    if(predecessors != nodes){
        predecessors = oxigen::getElementarPredecessors(predecessors,succNode);
    }
    return predecessors;
}

std::vector<DFGNode*> oxigen::getNodePredecessors(DFGNode* n,NodeType type,DFGNode* succNode){

    std::vector<DFGNode*> predecessors;

    switch(type){

        case NodeType::LoopNode:
        {
            DFGLoopNode* loopNode = (DFGLoopNode*)n;
            predecessors = loopNode->getOutPortPredecessors(succNode);
            break;
        }
        default:
        {
            predecessors.push_back(n);
        }
    }
    return predecessors;
}

bool oxigen::isComposite(NodeType type) {

    if(type == NodeType::LoopNode)
        return  true;
    return false;
}

std::vector<NodeType> oxigen::getCompositeTypes() {

    std::vector<NodeType> c = std::vector<NodeType>();

    for(NodeType enum_val = oxigen::ENUM_FIRST; enum_val <= oxigen::ENUM_LAST; enum_val = (NodeType)(enum_val+1)){
        if(oxigen::isComposite(enum_val)){
            c.push_back(enum_val);
        }
    }
    return c;
}

//DFGLinker methods implementation

std::vector<DFG*> DFGLinker::linkDFG(){

    DefaultScheduler* dScheduler = nullptr;
    DFGNodeFactory* nodeFactory = new DFGNodeFactory();

    if(scheduler->getType() == SchedulerType::Default)
        dScheduler = (DefaultScheduler*)scheduler;

    std::vector<DFGNode*>  nodesOrder;
    std::vector<DFGReadNode*> readNodes;
    std::vector<DFGWriteNode*> writeNodes;
    
    for(DFG* dfg : DFGLinker::dfgs)
    {
        DFGNode* base = dfg->getEndNode();
        std::vector<DFGReadNode*> rNodes;
        std::vector<DFGWriteNode*> wNodes;
        std::vector<DFGNode*> sortedNodes;
        
        dfg->getWriteNodes(base,wNodes);
        dfg->getReadNodes(base,rNodes);
        
        dfg->resetFlags(dfg->getEndNode());

        sortedNodes = dfg->orderNodesWithFunc(F);
        
        nodesOrder.insert(nodesOrder.end(),sortedNodes.begin(),sortedNodes.end());
        
        readNodes.insert(readNodes.end(),rNodes.begin(),rNodes.end());
        writeNodes.insert(writeNodes.end(),wNodes.begin(),wNodes.end());
        
    }

    llvm::errs() << "Ordered nodes\n";
    for(DFGNode* n : nodesOrder)
        n->getValue()->dump();

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
                    
                    if(readNode->getReadingStream().first == writeNode->getWritingStream().first &&
                            (readNode->getStreamWindow().first <= -(writeNode->getStreamWindow().first) ||
                                    (dScheduler != nullptr && !readNode->isInTheSameLoop(writeNode,dScheduler->getLoopInfo())))){

                        if(readNode->getSuccessors().size() == 0){
                            llvm::errs() << "No succ read: ";
                            readNode->getValue()->dump();
                            writeNode->getValue()->dump();
                            for(DFGNode* s : readNode->getPredecessors()){
                                s->getValue()->dump();
                            }
                        }
                        DFGNode* readSucc = readNode->getSuccessors().at(0);   //assumes that reads have one successor

                        for(DFGNode* rSucc : readNode->getSuccessors())
                            if(llvm::Instruction* readSuccAsInstr = llvm::dyn_cast<llvm::Instruction>(rSucc->getValue()))
                                if(readSuccAsInstr->getOpcodeName() != std::string("store")){
                                    readSucc = rSucc;
                                    break;
                                }
                        llvm::errs() << "\nRS\n";
                        for(DFGNode* rs : readNode->getSuccessors()){
                            rs->getValue()->dump();
                        }
                        llvm::errs() << "\nRead Node\n";
                        readNode->getValue()->dump();
                        llvm::errs() << "\nWrite Node\n";
                        writeNode->getValue()->dump();
                        llvm::errs() << "\nWP\n";
                        for(DFGNode* wp : writeNode->getPredecessors()){
                            wp->getValue()->dump();
                        }
                        std::vector<DFGNode*> &linkedNodes = readSucc->getPredecessors();


                        int pos = std::find(linkedNodes.begin(),linkedNodes.end(),readNode)-linkedNodes.begin();
                        readSucc->linkPredecessor(writeNode->getPredecessors().at(0),pos);

                        //update stream window
                        writeNode->getPredecessors().at(0)->setStreamWindow(
                                readNode->getStreamWindow().first,
                                readNode->getStreamWindow().second);

                        llvm::errs() << "\nRSP\n";
                        for(DFGNode* rs : readSucc->getPredecessors()){
                            rs->getValue()->dump();
                        }

                        readSucc->unlinkPredecessor(readNode);
                        llvm::errs() << "\nRSP\n";
                        for(DFGNode* rs : readSucc->getPredecessors()){
                            rs->getValue()->dump();
                        }


                        if(writeNode->getStreamWindow().first != 0 &&
                           writeNode->getPredecessors().at(0)->getType() != NodeType::Offset){

                            DFGOffsetNode* offsetNode = nodeFactory->createDFGOffsetNode(writeNode);
                            DFGNode* wPred = writeNode->getPredecessors().at(0);

                            oxigen::insertNode(offsetNode,wPred,writeNode,true);
                            oxigen::transferSuccessors(wPred,offsetNode);
                        }

                        if(readNode->getStreamWindow().first != 0){
                            DFGOffsetNode* offsetNode = nodeFactory->createDFGOffsetNode(readNode);
                            DFGNode* wPred = writeNode->getPredecessors().at(0);

                            oxigen::insertNode(offsetNode,wPred,readSucc,true);
                        }

                        j = 0;
                    }
                }
            }
        }
    }

    std::vector<DFG*> indipendentGraphs;
    std::vector<DFG*> reverseGraphs(dfgs.size());
    std::reverse_copy(std::begin(dfgs),std::end(dfgs),std::begin(reverseGraphs));

    for(DFG* dfg : dfgs)
        dfg->resetFlags(dfg->getEndNode());

    for(DFG* dfg : reverseGraphs){

        if(!dfg->getEndNode()->getFlag())
            indipendentGraphs.push_back(dfg);

        dfg->setDFGFlags();
        }

    dfgs = indipendentGraphs;

    for(DFG* ind_graph : indipendentGraphs){
        ind_graph->fuseIdenticalNodes();
        ind_graph->resetFlags(ind_graph->getEndNode());
    }

    return indipendentGraphs;
}
