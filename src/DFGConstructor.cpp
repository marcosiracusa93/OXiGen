
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

            default:
                break;
        }
    else
    {
        setFlag(false);
    }
    
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

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
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

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
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

std::vector<DFGNode*> DFG::getScalarArguments(DFGNode* baseNode){
    
    int startingPos = 0;
    std::vector<DFGNode*> sortedNodes(getNodesCount());
    std::vector<DFGNode*> scalarArgs;
    
    resetFlags(baseNode);
    orderNodes(baseNode,startingPos,sortedNodes);
    
    for(DFGNode* n : sortedNodes)
    {
        if(llvm::dyn_cast<llvm::Argument>(n->getValue()))
        {
            scalarArgs.push_back(n);
        }
    }
    
    return scalarArgs;
}

std::vector<DFGNode*> DFG::getUniqueScalarArguments(DFGNode* baseNode){
    
    std::vector<DFGNode*> scalarArguments;
    std::vector<DFGNode*> uniqueScalarArguments;
    
    scalarArguments = getScalarArguments(baseNode);
    
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

int DFG::getNodesCount(){
    
    int count = 0;

    DFG::resetFlags(DFG::endNode);
    count = DFG::countChildren(DFG::endNode,count);

    return count;
}

void DFG::resetFlags(DFGNode* node){
    
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

    while(nodeToReset->getSuccessors().size() != 0){
        for(DFGNode* succ : nodeToReset->getSuccessors()){
            if(succ->getFlag()){
                nodeToReset = succ;
                break;
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
    
    setNames(nodeNames,node);

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
            double val = CFP->getValueAPF().convertToDouble();
            node->setName(std::to_string(val));
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

    while(nodeToSet->getSuccessors().size() != 0){
        for(DFGNode* succ : nodeToSet->getSuccessors()){
            if(!succ->getFlag()){
                nodeToSet = succ;
                break;
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

    printDFG(endNode);
}

void DFG::descendAndPrint(DFGNode* node){
    
    DFGNode* nodeToPrint = node;

    while(nodeToPrint->getSuccessors().size() != 0) {
        int considered_succ = nodeToPrint->getSuccessors().size();
        for (DFGNode* succ : nodeToPrint->getSuccessors())
            if (!succ->getFlag()) {
                nodeToPrint = succ;
                break;
            }
        if(considered_succ == nodeToPrint->getSuccessors().size())
            for(DFGNode* succ : nodeToPrint->getSuccessors())
                succ->setFlag(false);
    }
    if(nodeToPrint != node)
        printDFG(nodeToPrint);
            
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

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
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
            descendAndSet(node);

    for(DFGNode* pred : node->getPredecessors())
        if(!pred->getFlag())
            setFlags(pred);

    return;
}

void DFG::descendAndSet(DFGNode* node){

    DFGNode* startingNode = node;

    while(startingNode->getSuccessors().size() != 0)
        for(DFGNode* succ : startingNode->getSuccessors())
            if(!succ->getFlag()){
                startingNode = succ;
                break;
            }
    if(startingNode != node)
        setFlags(startingNode);
    else
        if(!startingNode->getFlag()){
            startingNode->setFlag(true);
        }

    return;
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
    
    if(computedDFGs.size() > 1){
        DFGConstructor::scheduler->schedule(new DFGLinker(computedDFGs));
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

                        DFGOffsetWriteNode *offsetNode = new DFGOffsetWriteNode(&instr, IOs, stream.second,loopTripCount);
                        computedDFGs.push_back(
                                computeDFGFromBase(offsetNode, IOs,loopTripCount,topLevelLoop));
                    } else {

                        computedDFGs.push_back(
                                computeDFGFromBase(new DFGWriteNode(&instr, IOs,loopTripCount), IOs,loopTripCount,topLevelLoop));
                    }
                }

                stream = storedOutputStream(store,IOs,SE);

                if (stream.first != nullptr) {
                    if(stream.second == nullptr)
                        computedDFGs.push_back(
                                computeDFGFromBase(new DFGWriteNode(&instr, IOs,loopTripCount),IOs,loopTripCount, topLevelLoop));
                    else{
                        DFGOffsetWriteNode* offsetNode = new DFGOffsetWriteNode(&instr,IOs,stream.second,loopTripCount);
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
                                computeDFGFromBase(new DFGWriteNode(&instr, IOs, accessIndex,accessIndex), IOs, accessIndex,
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

void DFGConstructor::populateDFG(DFGNode* node, IOStreams* IOs,int loopTripCount,llvm::Loop* loop){
    //TODO: check link predecessor calls
    llvm::Value* parentVal = node->getValue();

    if(llvm::Instruction* parentInstr = llvm::dyn_cast<llvm::Instruction>(parentVal)){

        if(parentInstr->getOpcodeName() == std::string("load"))
            return;

        for(llvm::Value* operandVal : parentInstr->operands()){

            if(loop != nullptr) {

                if (llvm::Instruction *operandAsInstr = llvm::dyn_cast<llvm::Instruction>(operandVal)) {
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
                            DFGReadNode *childNode = new DFGReadNode(operandVal, IOs, loopTripCount);
                            node->linkPredecessor(childNode);
                        } else {
                            llvm::errs() << "Getelemptr may be offset node: ";
                            getelemPtrInstr->dump();
                            llvm::GetElementPtrInst *gep = llvm::dyn_cast<llvm::GetElementPtrInst>(getelemPtrInstr);

                            StreamPair stream = StreamPair(nullptr, nullptr);

                            if (gep != nullptr)
                                stream = IOs->getInStreamFromGEP(gep);

                            if (stream.second != nullptr) {
                                llvm::errs() << "Creating offset read node...\n";
                                DFGOffsetReadNode *childNode = new DFGOffsetReadNode(operandVal, IOs, stream.second,
                                                                                     loopTripCount);
                                node->linkPredecessor(childNode);
                            } else {
                                llvm::errs() << "Node was without offset after all...\n";
                                DFGReadNode *childNode = new DFGReadNode(operandVal, IOs, loopTripCount);
                                node->linkPredecessor(childNode);
                            }

                        }

                    } else {
                        //Node initialization for a generic instruction

                        DFGNode *childNode = new DFGNode(operandVal);
                        node->linkPredecessor(childNode);
                        populateDFG(childNode, IOs, loopTripCount, loop);
                    }
                } else {
                    //Node initializaton for a generic llvm::Value which is not an
                    //instruction

                    if((!llvm::dyn_cast<llvm::Function>(operandVal))){
                        DFGNode *childNode = new DFGNode(operandVal);
                        node->linkPredecessor(childNode);
                    }else{
                        llvm::errs() << "INFO: function called found. Node ignored...\n";
                    }
                }
            }else{

                if(llvm::LoadInst* load = llvm::dyn_cast<llvm::LoadInst>(operandVal)){

                    if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(load->getPointerOperand())){

                        llvm::Value* gep_idx = *(gep->idx_end() - 1);

                        if(llvm::ConstantInt* const_idx = llvm::dyn_cast<llvm::ConstantInt>(gep_idx)){

                            int index = const_idx->getSExtValue();

                            if(index-loopTripCount == 0){
                                DFGReadNode *childNode = new DFGReadNode(
                                        operandVal, IOs, index-loopTripCount, index-loopTripCount);
                                node->linkPredecessor(childNode);
                            }else{
                                //Offset read....
                                DFGReadNode *childNode = new DFGReadNode(
                                        operandVal, IOs, index-loopTripCount, index-loopTripCount);
                                node->linkPredecessor(childNode);
                            }

                        }else{
                            llvm::errs() << "ERROR: non constant index in static DFG\n";
                            exit(EXIT_FAILURE);
                        }
                    }else{
                        llvm::errs() << "ERROR: unexpected load pointer operand in static DFG\n";
                        exit(EXIT_FAILURE);
                    }

                } else if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(operandVal)){

                    //Node initialization for a generic instruction
                    if (instr->getOpcodeName() == std::string("sext")) {
                        llvm::errs() << "INFO: attempting to insert sext in static DFG\n";
                        return;
                    }

                    DFGNode *childNode = new DFGNode(operandVal);
                    node->linkPredecessor(childNode);
                    populateDFG(childNode, IOs, loopTripCount, loop);

                } else {
                    //Node initializaton for a generic llvm::Value which is not an
                    //instruction
                    if((!llvm::dyn_cast<llvm::Function>(operandVal))){
                        DFGNode *childNode = new DFGNode(operandVal);
                        node->linkPredecessor(childNode);
                    }else{
                        llvm::errs() << "INFO: function called found. Node ignored...\n";
                    }
                }

            }
        }
    }
    else
    {
        llvm::errs() << "Non instr parent\n";
        return;
    }

}

DFG* DFGConstructor::computeDFGFromBase(DFGWriteNode* baseNode, IOStreams* IOs,int loopTripCount,llvm::Loop* loop){
        
    //intializes a new DFG object
    DFG* graph = new DFG(baseNode);
    //populates it from its base node
    populateDFG(shortcutSoreGetelementPtr(baseNode,IOs,loopTripCount),IOs,loopTripCount,loop);

    return graph;
}

std::vector<DFG*> DFGConstructor::computeStaticDFG(IOStreams* IOs,llvm::ScalarEvolution* SE,
                                                   llvm::LoopInfo* LI,llvm::Function* F,llvm::BasicBlock* start){

    std::vector<DFG*> dfgs = std::vector<DFG*>();
    bool atCurrentBlock = false;

    for(llvm::Function::iterator BB_it = F->begin(); BB_it != F->end(); ++BB_it){

        if(&(*BB_it) == start)
            atCurrentBlock = true;

        if(LI->getLoopDepth(&(*BB_it)) == 0 && atCurrentBlock){

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

DFGNode* DFGConstructor::shortcutSoreGetelementPtr(DFGWriteNode* storeNode,IOStreams* IOs,int loopTripCount){

    llvm::Instruction* storeInstr = (llvm::Instruction*) storeNode->getValue();

    DFGNode* startingNode;

    if(llvm::Instruction* cInstr = llvm::dyn_cast<llvm::Instruction>(storeInstr->getOperand(0))){
        if (cInstr->getOpcodeName() == std::string("load")) {
            startingNode = new DFGReadNode(cInstr, IOs,loopTripCount);
            storeNode->linkPredecessor(startingNode);
            return startingNode;
        }
        if (cInstr->getOpcodeName() == std::string("store")) {
            startingNode = new DFGWriteNode(cInstr, IOs,loopTripCount);
            storeNode->linkPredecessor(startingNode);
            return startingNode;
        }
    }

    startingNode = new DFGNode(storeInstr->getOperand(0));
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

void oxigen::insertNode(DFGNode* n,DFGNode* pred,DFGNode* succ,bool areConsecutive = false){

    if(areConsecutive){
        succ->insertPredecessor(pred,n);
    }else{
        succ->linkPredecessor(n);
        n->linkPredecessor(pred);
    }

}

void oxigen::transferSuccessors(DFGNode* currentParent,DFGNode* newParent){

    for(DFGNode* child : currentParent->getSuccessors()){
        if(child != newParent){
            child->changeParent(currentParent,newParent);
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

//DFGLinker methods implementation

std::vector<DFG*> DFGLinker::linkDFG(){

    DefaultScheduler* dScheduler = nullptr;

    if(scheduler->getType() == SchedulerType::Default)
        dScheduler = (DefaultScheduler*)scheduler;

    std::vector<DFGNode*>  nodesOrder;
    std::vector<DFGReadNode*> readNodes;
    std::vector<DFGWriteNode*> writeNodes;
    int baseSize = 0;
    
    for(DFG* dfg : DFGLinker::dfgs)
    {
        int graphSize = dfg->getNodesCount();
        DFGNode* base = dfg->getEndNode();
        std::vector<DFGReadNode*> rNodes;
        std::vector<DFGWriteNode*> wNodes;
        std::vector<DFGNode*> sortedNodes(graphSize);
        
        dfg->getWriteNodes(base,wNodes);
        dfg->getReadNodes(base,rNodes);
        
        dfg->resetFlags(dfg->getEndNode());

        dfg->orderNodes(dfg->getEndNode(),baseSize,sortedNodes,baseSize);
        
        nodesOrder.insert(nodesOrder.end(),sortedNodes.begin(),sortedNodes.end());

        baseSize += graphSize;
        
        readNodes.insert(readNodes.end(),rNodes.begin(),rNodes.end());
        writeNodes.insert(writeNodes.end(),wNodes.begin(),wNodes.end());
        
    }

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

                        DFGNode* readSucc = readNode->getSuccessors().at(0);   //assumes that reads have one successor

                        for(DFGNode* rSucc : readNode->getSuccessors())
                            if(llvm::Instruction* readSuccAsInstr = llvm::dyn_cast<llvm::Instruction>(rSucc->getValue()))
                                if(readSuccAsInstr->getOpcodeName() != std::string("store")){
                                    readSucc = rSucc;
                                    break;
                                }

                        std::vector<DFGNode*> &linkedNodes = readSucc->getPredecessors();

                        int pos = std::find(linkedNodes.begin(),linkedNodes.end(),readNode)-linkedNodes.begin();
                        readSucc->linkPredecessor(writeNode->getPredecessors().at(0),pos);

                        //update stream window
                        writeNode->getPredecessors().at(0)->setStreamWindow(
                                readNode->getStreamWindow().first,
                                readNode->getStreamWindow().second);

                        linkedNodes.erase(linkedNodes.begin() + pos+1);

                        if(writeNode->getStreamWindow().first != 0 &&
                           writeNode->getPredecessors().at(0)->getType() != NodeType::Offset){

                            DFGOffsetNode* offsetNode = new DFGOffsetNode(writeNode);
                            DFGNode* wPred = writeNode->getPredecessors().at(0);

                            oxigen::insertNode(offsetNode,wPred,writeNode,true);
                            oxigen::transferSuccessors(wPred,offsetNode);
                        }

                        if(readNode->getStreamWindow().first != 0){
                            DFGOffsetNode* offsetNode = new DFGOffsetNode(readNode);
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

    return indipendentGraphs;
}

void DFG::orderNodes(DFGNode* n, int &pos, std::vector<DFGNode*> &sorted,int baseSize){
    
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


