
#import "DFGTranslator.h"

using namespace oxigen;

//default imports for the maxj kernel
std::vector<std::string> MaxJInstructionPrinter::imports = {
    "com.maxeler.maxcompiler.v2.kernelcompiler.Kernel",
    "com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters",
    "com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar"
};

//default kernel signature
std::string MaxJInstructionPrinter::kernelSignature_1 =
    std::string("class <kernelName> extends Kernel {\n\n");

std::string MaxJInstructionPrinter::kernelSignature_2 = std::string("\t<kernelName>(KernelParameters parameters) {\n")    +
    std::string("\t\tsuper(parameters);\n\n");
   
//default kernel signature closing 
std::string MaxJInstructionPrinter::kernelSignatureClosing = std::string("\t}\n}\n");
    
//opcode map for the MaxJInstructionPrinter, {LLVM opcode, maxj operaion}
MaxJInstructionPrinter::OpcodeMap MaxJInstructionPrinter::opcodeMap = {
    
    {"fadd"," + "},
    {"add", " + "},
    {"fsub"," - "},
    {"sub"," - "},
    {"mul", " * "},
    {"fmul"," * "},
    {"fdiv", " / "},
    {"sdiv", " / "},
    {"udiv", " / "},
    {"sitofp", "float"},
    {"fpext","float"},
    {"fptrunc","float"},
    {"sext","int"},
    {"zext","int"},
    {"fptosi","int"},
    {"fptoui","int"},
    {"sitrunc","int"}
    
};

MaxJInstructionPrinter::OpcodeMap MaxJInstructionPrinter::funcLibMap = {

        {"ceil","KernelMath"},
        {"abs","KernelMath"},
        {"fabs","KernelMath"},
        {"floor","KernelMath"},
        {"sqrt","KernelMath"},
        {"log2","KernelMath"},
        {"log","KernelMath"},
        {"sin","KernelMath"},
        {"cos","KernelMath"},
        {"pow2","KernelMath"},
        {"exp","KernelMath"},
        {"min","KernelMath"},
        {"max","KernelMath"},
        {"fmin","KernelMath"},
        {"fmax","KernelMath"},
        {"Ncdf", "OXiGen"}
};

MaxJInstructionPrinter::ImportMap MaxJInstructionPrinter::libImports = {

        {"KernelMath",std::pair<bool,std::string>(
                false,"com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.KernelMath")},
        {"OXigen",std::pair<bool,std::string>(
                false,"")},
        {"Reductions",std::pair<bool,std::string>(
                false,"com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.Reductions"
        )},
        {"DFEVector",std::pair<bool,std::string>(
                false,"com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVector;\nimport com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVectorType"
        )}
};

MaxJInstructionPrinter::CmpPredMap MaxJInstructionPrinter::cmpPredMap = {

        {32," === "},
        {33," !== "},
        {34," > "},
        {35," >= "},
        {36," < "},
        {37," <= "},
        {38," > "},
        {39," >="},
        {40," < "},
        {41," <= "}

};

//SequentialNamesManager methods implementation

std::string SequentialNamesManager::getNewName(){
    std::string newName = SequentialNamesManager::nextName;
    SequentialNamesManager::varNames.push_back(newName);
    SequentialNamesManager::nextName = generateNextName();
    return newName;
}

std::string SequentialNamesManager::generateNextName(){
    
    char oldNameFirst = SequentialNamesManager::nextName.front();
    std::string newGenName;
        
    //generates names starting from "a","b"..."aa","ab"...
    if(oldNameFirst != 'z')
    {
        char newFirst = oldNameFirst + 1;
        newGenName = SequentialNamesManager::nextName.substr(1, SequentialNamesManager::nextName.size());
        newGenName.insert(0,1,newFirst);
    }
    else
    {
        newGenName = SequentialNamesManager::nextName;
        int flipCount = 0;
        
        while(flipCount != newGenName.size()){
            if(newGenName.at(flipCount) == 'z')
            {
                newGenName.replace(flipCount,1,1,'a');
                flipCount++;
            }
            else
            {
                newGenName.replace(flipCount,1,1,newGenName.at(flipCount)+1);
                break;
            }
        }
        if(flipCount == newGenName.size() && newGenName.at(flipCount-1) == 'a')
            newGenName.push_back('a');
    }
    
    return newGenName;
}

//MaxJInstructionPrinter methods implementation

std::string MaxJInstructionPrinter::getInputStreamsDeclarations(std::vector<DFGReadNode*> inputs){
    
    std::string declarations;
    std::string inputEnable = "";
    std::vector<DFGReadNode*> tmp;

    if(std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING)
                    != kernelOptimizations.end()){
        inputEnable = ",tileCounter.eq(0)";
    }

    for(auto it_r = inputs.rbegin(); it_r != inputs.rend(); ++it_r){

        tmp.push_back(*it_r);

        for(DFGReadNode* n : tmp){
            if(n->getReadingStream().first == (*it_r)->getReadingStream().first && n != (*it_r)){
                (*it_r)->setName(n->getName());
                tmp.pop_back();
            }
        }
    }

    inputs = tmp;

    for(DFGReadNode* inputNode : inputs)
    {
        inputNode->setGlobalDelay(0);
        auto inputStream = inputNode->getReadingStream();
        llvm::Type* inputStreamType = inputStream.first->getType()->getPointerElementType();
        std::string nodeName = inputNode->getName();
        
        if(inputStreamType->isFloatingPointTy())
        {
            int exp;
            int mantissa;

            if(inputStreamType->isDoubleTy()){
                mantissa = DOUBLE_MANTISSA;
                exp = DOUBLE_EXP;
            }else{
                mantissa = FLOAT_MANTISSA;
                exp = FLOAT_EXP;
            }

            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.input(\"") + nodeName + 
                        std::string("\", dfeFloat(") + std::to_string(exp) +
                        std::string(", ") + std::to_string(mantissa) + std::string(")") + inputEnable +
                        std::string(");\n");
            
            declarations.append(decl);
        }
        if(inputStreamType->isIntegerTy())
        {
            int bitWidth = inputStreamType->getIntegerBitWidth();
            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.input(\"") + nodeName + 
                        std::string("\", dfeInt(") + std::to_string(bitWidth) +
                        std::string(")") + inputEnable + std::string(");\n");
                        
            declarations.append(decl);
        }
    }
    
    return declarations;
}

std::string MaxJInstructionPrinter::getConstantOutputOffsetsDeclarations(std::vector<DFGOffsetWriteNode*> offsetWrites){

    SequentialNamesManager* offsetsNamesManager = new SequentialNamesManager();
    std::vector<std::string> offsetsNames;
    std::string offsetsStreamsDeclarations = "";

    for(int i = 0; i < offsetWrites.size(); i++){
        offsetsNames.push_back(offsetsNamesManager->getNewName());
    }

    for(DFGOffsetWriteNode* n : offsetWrites) {

        if(llvm::dyn_cast<llvm::AllocaInst>(n->getWritingStream().first))
            break;

        std::string sourceName = n->getPredecessors().front()->getName();
        n->getPredecessors().front()->setName(std::string("w_off_") + offsetsNames.back());
        offsetsNames.pop_back();
        std::string ofsStreamName = n->getPredecessors().front()->getName();

        const llvm::SCEV *offset_scev = n->getWritingStream().second;

        if(offset_scev->getSCEVType() == llvm::SCEVTypes::scConstant) {
            const llvm::SCEVConstant *const_offset_scev = (llvm::SCEVConstant *) offset_scev;

            llvm::ConstantInt* intOfs = const_offset_scev->getValue();

            int offset = 0;

            offset = intOfs->getSExtValue();

            int reversed_offset = -offset;

            std::string offsetDeclaration = std::string("\t\tDFEVar ") + ofsStreamName +
                                            std::string(" = stream.offset(") + sourceName +
                                            std::string(", ") + std::to_string(reversed_offset) +
                                            std::string(");\n");

            offsetsStreamsDeclarations.append(offsetDeclaration);

        }else{
            llvm::errs() << "Non-constant offset not supported...";
            exit(EXIT_FAILURE);
        }
    }
    return offsetsStreamsDeclarations;
}

std::string MaxJInstructionPrinter::getConstantInputOffsetsDeclarations(std::vector<DFGOffsetReadNode*> offsetReads){

    SequentialNamesManager* offsetsNamesManager = new SequentialNamesManager();
    std::vector<std::string> offsetsNames;
    std::string offsetsStreamsDeclarations = "";

    for(int i = 0; i < offsetReads.size(); i++){
        offsetsNames.push_back(offsetsNamesManager->getNewName());
    }

    for(DFGOffsetReadNode* n : offsetReads){

        llvm::errs() << "\nNODE:\n";    n->printNode();

        std::string sourceName = n->getName();
        n->setName(std::string("r_off_") + offsetsNames.back());
        offsetsNames.pop_back();
        std::string ofsStreamName = n->getName();

        const llvm::SCEV* offset_scev = n->getReadingStream().second;

        if(offset_scev->getSCEVType() == llvm::SCEVTypes::scConstant) {
            const llvm::SCEVConstant *const_offset_scev = (llvm::SCEVConstant *) offset_scev;

            llvm::ConstantInt* intOfs = const_offset_scev->getValue();

            int offset = 0;

            offset = intOfs->getSExtValue();

            std::string offsetDeclaration = std::string("\t\tDFEVar ") + ofsStreamName +
                                            std::string(" = stream.offset(") + sourceName +
                                            std::string(", ") + std::to_string(offset) +
                                            std::string(");\n");

            offsetsStreamsDeclarations.append(offsetDeclaration);

        }else{
            llvm::errs() << "Non-constant offset not supported...";
            exit(EXIT_FAILURE);
        }
    }

    return offsetsStreamsDeclarations;
}

std::string MaxJInstructionPrinter::getOutputStreamsDeclarations(std::vector<DFGWriteNode*> outputs){
    
    std::string declarations;
    std::string outputEnable = "";
    std::vector<DFGWriteNode*> tmp;

    if(std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING)
       != kernelOptimizations.end()){

        int delay = MaxJInstructionPrinter::dependencyGraph->getFinalDelay();

        outputEnable = ",tileCounter.eq(" + std::to_string(delay) + " % tilingFactor)";
    }

    for(auto it_r = outputs.rbegin(); it_r != outputs.rend(); ++it_r){

        tmp.push_back(*it_r);

        for(DFGWriteNode* n : tmp){
            if(n->getWritingStream() == (*it_r)->getWritingStream() && n != (*it_r)){
                (*it_r)->setName(n->getName());
                tmp.pop_back();
            }
        }
    }

    outputs = tmp;
    
    for(DFGWriteNode* outputNode :outputs)
    {
        auto outputStream = outputNode->getWritingStream();
        llvm::Type* outputStreamType = outputStream.first->getType()->getPointerElementType();
        std::string nodeName = outputNode->getName();
        std::string resultName = "NOT_FOUND";

        llvm::errs() << "\nOUTPUT PREDS\n";

        std::vector<DFGNode*> predecessors = outputNode->getCrossScopePredecessors();

        for(DFGNode* pred : predecessors){
            pred->getValue()->dump();
            if(!oxigen::isComposite(pred->getType())){
                resultName = pred->getName();
            }
        }
        
        if(outputStreamType->isFloatingPointTy())
        {
            int exp;
            int mantissa;

            if(outputStreamType->isDoubleTy()){
                mantissa = DOUBLE_MANTISSA;
                exp = DOUBLE_EXP;
            }else{
                mantissa = FLOAT_MANTISSA;
                exp = FLOAT_EXP;
            }
            
            std::string decl = std::string("\t\tio.output(\"") + nodeName + 
                        std::string("\", ") + resultName + std::string(", dfeFloat(") + 
                        std::to_string(exp) + std::string(", ") +
                        std::to_string(mantissa) + std::string(")") + outputEnable +
                        std::string(");\n");
                        
            declarations.append(decl);
        }
        if(outputStreamType->isIntegerTy())
        {
            int bitWidth = outputStreamType->getIntegerBitWidth();
            
            std::string decl = std::string("\t\tio.output(\"") + nodeName + 
                        std::string("\", ") + resultName + std::string(", dfeInt(") + 
                        std::to_string(bitWidth) + std::string(")") + outputEnable +
                        std::string(");\n");
                        
            declarations.append(decl);
        }
        
    }
    
    return declarations;
}

std::string MaxJInstructionPrinter::getScalarInputsDeclarations(std::vector<DFGNode*> scalarInputs){
    
    std::string declarations;

    std::vector<DFGNode*> tmp;

    for(auto it_r = scalarInputs.rbegin(); it_r != scalarInputs.rend(); ++it_r){

        tmp.push_back(*it_r);

        for(DFGNode* n : tmp){
            if(n->getValue() == (*it_r)->getValue() && n != (*it_r)){
                (*it_r)->setName(n->getName());
                tmp.pop_back();
            }
        }
    }

    scalarInputs = tmp;
    
    for(DFGNode* n : scalarInputs)
    {
        llvm::Type* argType = n->getValue()->getType();
        std::string nodeName = n->getName();
        
        if(argType->isFloatingPointTy())
        {
            int exp;
            int mantissa;

            if(argType->isDoubleTy()){
                mantissa = DOUBLE_MANTISSA;
                exp = DOUBLE_EXP;
            }else{
                mantissa = FLOAT_MANTISSA;
                exp = FLOAT_EXP;
            }
            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.scalarInput(\"") + nodeName + 
                        std::string("\", dfeFloat(") + std::to_string(exp) +
                        std::string(", ") + std::to_string(mantissa) + std::string("));\n");
                        
            declarations.append(decl);
        }
        if(argType->isIntegerTy())
        {
            int bitWidth = argType->getIntegerBitWidth();
            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.scalarInput(\"") + nodeName + 
                        std::string("\", dfeInt(") + std::to_string(bitWidth) + 
                        std::string("));\n");
                        
            declarations.append(decl);
        }
    }
    return declarations;
}

std::string MaxJInstructionPrinter::generateInstructionsString(std::vector<DFGNode*> sortedNodes){
    
    std::string instructionsString = "";
    
    for(DFGNode* n : sortedNodes)
    {
        instructionsString = instructionsString.append(appendInstruction(n));
    }

    return instructionsString;

}

std::string MaxJInstructionPrinter::translateAsJavaLoop(DFGLoopNode* loopNode){

    SequentialNamesManager* loopNamesManager = new SequentialNamesManager();
    loopHeadDeclarations = "";
    LoopGraphNode* dependencyGraphNode = MaxJInstructionPrinter::dependencyGraph->getNodeForLoop(loopNode);

    for(DFGNode* endNode : loopNode->getEndNodes()){
        DFG* dfg = new DFG(endNode);
        dfg->resetFlags(endNode);

        int nodesCount = dfg->getNodesCount();
        std::vector<std::string> nodeNames;

        for(int i = 0; i < nodesCount; i++)
            nodeNames.push_back(std::string("l_")+loopNode->getName()+loopNamesManager->getNewName());

        dfg->setNameVector(nodeNames,dfg->getEndNode());
    }

    for(DFGNode* outInnerNode : loopNode->getOutPortInnerNodes()){
        DFG* dfg = new DFG(outInnerNode);
        dfg->resetFlags(outInnerNode);

        int nodesCount = dfg->getNodesCount();
        std::vector<std::string> nodeNames;

        for(int i = 0; i < nodesCount; i++)
            nodeNames.push_back(std::string("l_")+loopNode->getName()+loopNamesManager->getNewName());

        dfg->setNameVector(nodeNames,dfg->getEndNode());
    }

    int iterations;
    int tilingFactor = dependencyGraphNode->getTilingFactor();

    if(!tilingFactor) {
        iterations = loopNode->getTripCount();
    }else{
        iterations = dependencyGraphNode->getReplication();
    }
    if(iterations < 0){
        llvm::errs() << "ERROR: trip count is not constant\n";
        exit(EXIT_FAILURE);
    }

    std::string loopNestingTabs = "";
    for(int i = 0; i < loopNode->getLoopDepth(); i++){
        loopNestingTabs.append("\t");
    }

    nestingTabs = loopNestingTabs;

    std::string l_idx = loopNode->getName() + std::string("_idx");

    loopIndexes[loopNode] = l_idx;
    currentLoopIndex = l_idx;

    if(dependencyGraphNode->getLoopType() == LoopType::Accumul &&
       std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING)
       != kernelOptimizations.end()) {

        iterations = loopNode->getTripCount();
    }

    std::string forHeader = std::string("\n"+nestingTabs+"\tfor(int "+l_idx+" = 0; "+l_idx+" < " +
                                        std::to_string(iterations)+"; "+l_idx+" += 1){\n");
    std::string forClosure = std::string(nestingTabs+"\t}\n");

    if(dependencyGraphNode->getLoopType() == LoopType::Accumul &&
       std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING)
       != kernelOptimizations.end()){

        std::string accumul_idx = currentLoopIndex + "_r";

        forHeader.append("\n" + nestingTabs + "\t\tint tile_n = " + currentLoopIndex + " / " +
                         std::to_string(dependencyGraphNode->getReplication()) + ";\n" + nestingTabs + "\t\tint " + accumul_idx + " = " +
                         currentLoopIndex + " % " + std::to_string(dependencyGraphNode->getReplication()) + ";\n\n");

        loopIndexes[loopNode] = accumul_idx;
        currentLoopIndex = accumul_idx;
    }

    std::vector<DFG*> dfgs = loopNode->getIndipendentLoopGraphs();

    std::string loopBody = "";

    for(DFG* dfg : dfgs) {

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGNode*> sortedNodes;

        dfg->resetFlags(endNode);

        sortedNodes = dfg->orderNodesWithFunc(F);

        //append instructions
        loopBody.append(generateInstructionsString(sortedNodes));
        loopBody.append("\n");

    }
    nestingTabs = "";

    std::string closingDeclarations = "";

    if(dependencyGraphNode->getLoopType() == LoopType::Accumul &&
            std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING)
            != kernelOptimizations.end()){

        int tilingFactor = dependencyGraphNode->getTilingFactor();

        for(DFGNode* n : loopNode->getOutPortInnerNodes()){
            if(n->getType() == NodeType::AccumulNode){

                libImports["Reductions"].first = true;
                int tilingDelay = dependencyGraphNode->getTilingDelay();


                closingDeclarations.append(nestingTabs + "\t\tDFEVar " +  n->getName() + "_hold"
                 " = " + "Reductions.streamHold(" + n->getName() + ", tileCounter.eq(" +
                std::to_string(( tilingDelay + tilingFactor -1) % tilingFactor) + "));\n");
                n->setName(n->getName() + "_hold");
            }

        }

        MaxJInstructionPrinter::currentGlobalDelay = currentGlobalDelay + tilingFactor - 1;
    }

    return std::string(loopHeadDeclarations +forHeader+loopBody+forClosure + closingDeclarations);
}

llvm::AllocaInst* MaxJInstructionPrinter::getVectorBasePointer(DFGNode *node) {

    llvm::AllocaInst* vectorBasePointer = nullptr;

    for(DFGNode* s : node->getSuccessors()){
        if(llvm::StoreInst* store = llvm::dyn_cast<llvm::StoreInst>(s->getValue())){
            if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(store->getPointerOperand())) {
                if (llvm::AllocaInst* alloca = llvm::dyn_cast<llvm::AllocaInst>(gep->getPointerOperand()))
                    vectorBasePointer = alloca;
            }
        }
    }
    return vectorBasePointer;
}

std::pair<std::string,std::vector<std::string>> MaxJInstructionPrinter::translateFunctionArguments(llvm::Function* F,

                                                               std::vector<std::string> funcArgs) {
    std::string funcName = F->getName();
    std::pair<std::string,std::vector<std::string>> returnSignature;

    if(funcName == std::string("fmin")){
        funcName = "min";
    }else if (funcName == std::string("fmax")){
        funcName = "max";
    }else if(funcName == std::string("fabs")){
        funcName = "abs";
    }else if(funcName == std::string("log")){
        llvm::Type *argType = (*(F->getArgumentList().begin())).getType();
        std::string argTypeStr;

        if(argType->isFloatingPointTy()){

            int exp;
            int mantissa;

            if(argType->isDoubleTy()){
                mantissa = DOUBLE_MANTISSA;
                exp = DOUBLE_EXP;
            }else{
                mantissa = FLOAT_MANTISSA;
                exp = FLOAT_EXP;
            }

            argTypeStr = std::string(" dfeFloat(") + std::to_string(exp) +
                               std::string(", ") + std::to_string(mantissa) + std::string(")");

        }
        if(argType->isIntegerTy())
        {
            int bitWidth = argType->getIntegerBitWidth();

            argTypeStr = std::string("dfeInt(") + std::to_string(bitWidth) +
                                     std::string("));\n");
        }
        funcArgs.push_back(argTypeStr);
    }

    returnSignature.second = funcArgs;
    returnSignature.first = funcName;
    return returnSignature;
}

std::string MaxJInstructionPrinter::getFullNameIfConstant(DFGNode* var) {

    if(llvm::ConstantFP* CFP = llvm::dyn_cast<llvm::ConstantFP>(var->getValue()))
    {
        if(CFP->getType()->isDoubleTy()) {
            double val = CFP->getValueAPF().convertToDouble();
            return "constant.var(dfeFloat(" + std::to_string(DOUBLE_EXP) + "," +
                    std::to_string(DOUBLE_MANTISSA) + ")," + std::to_string(val) + ")";
        }else{
            float val = CFP->getValueAPF().convertToFloat();
            return "constant.var(dfeFloat(" + std::to_string(FLOAT_EXP) + "," +
                   std::to_string(FLOAT_MANTISSA) + ")," + std::to_string(val) + ")";
        }
    }else if(llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(var->getValue()))
    {
        int val = CI->getSExtValue();
        int bitWidth = CI->getBitWidth();
        if(var->getType() == NodeType::Offset){
            return var->getName();
        }else{
            return "constant.var(dfeInt(" + std::to_string(bitWidth) + ")," + std::to_string(val) + ")";
        }
    }else{
        return var->getName();
    }
}

std::string MaxJInstructionPrinter::appendInstruction(DFGNode* node){

    std::string currentInstr = "";
    std::string varType = "DFEVar ";
    std::string assignmentType = " = ";
    std::string varName = node->getName();
    node->setGlobalDelay(MaxJInstructionPrinter::currentGlobalDelay);

    llvm::errs() << "\nNODE NAME: " << varName << "\n";

    std::map<std::string,std::string> vectorPredNamesMap = std::map<std::string,std::string>();

    for(DFGNode* pred : node->getCrossScopePredecessors()){

        if(pred->getType() == NodeType::ReadNode || pred->getType() == NodeType::OffsetRead){
            pred->setGlobalDelay(0);
        }

        std::string tmpName = "";

        if(isNestedVectorWrite(pred) && translationMode == MaxLoopTranslationMode::JavaLoop) {
            tmpName = pred->getName() + "[" + currentLoopIndex + "]";
        }else{
            tmpName = pred->getName();
        }

        if(std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING)
           != kernelOptimizations.end() && translationMode == MaxLoopTranslationMode::JavaLoop) {

            if(pred->getLoop() != nullptr && node->getLoop() != nullptr) {

                LoopGraphNode* predLoopNode =
                        MaxJInstructionPrinter::dependencyGraph->getNodeForLoop(pred->getLoop());
                LoopGraphNode* nodeLoopNode =
                        MaxJInstructionPrinter::dependencyGraph->getNodeForLoop(node->getLoop());

                for(auto succ : predLoopNode->getSuccessors()) {
                    if(succ->getLoopNode() == node->getLoop()) {
                        if (nodeLoopNode->getLoopType() == LoopType::Accumul &&
                            predLoopNode->getLoopType() == LoopType::Expansion) {

                            int tilingFactor = nodeLoopNode->getTilingFactor();

                            tmpName = "stream.offset(" + tmpName + "," +
                                      std::to_string(-(tilingFactor - 1)) + " + tile_n)";
                        }
                    }
                }
            }

            if(pred->getGlobalDelay() != node->getGlobalDelay() && pred->getType() != NodeType::AccumulNode){
                tmpName = "stream.offset(" + tmpName + "," +
                          std::to_string(pred->getGlobalDelay()-node->getGlobalDelay()) + ")";
            }
        }
        if(tmpName != pred->getName()){
            vectorPredNamesMap.insert(std::pair<std::string,std::string>(tmpName,pred->getName()));
            pred->setName(tmpName);
        }
    }

    node->setIsDeclared();

    if(oxigen::isNestedVectorWrite(node) && translationMode == MaxLoopTranslationMode::JavaLoop){

        llvm::AllocaInst* basePtr = getVectorBasePointer(node);
        DFGLoopNode* loopNode = node->getLoop();
        LoopGraphNode* loopDependencyGraphNode = MaxJInstructionPrinter::dependencyGraph->getNodeForLoop(loopNode);
        std::string vectorName;
        libImports["DFEVector"].first = true;

        if(!declaredNestedVectors.count(basePtr)) {

            llvm::Type* dataType;

            if(llvm::ArrayType* arrType = llvm::dyn_cast<llvm::ArrayType>(basePtr->getAllocatedType())){
                dataType = arrType->getElementType();
            }else{
                llvm::errs() << "ERROR: non array composite type not supported\n";
                exit(EXIT_FAILURE);
            }

            vectorName = node->getName();
            std::string decl = "\t\tDFEVector<DFEVar> " + vectorName + " = new DFEVectorType<DFEVar>(";
            std::string baseType;

            int bitWidth = dataType->getScalarSizeInBits();
            int tilingFactor = loopDependencyGraphNode->getTilingFactor();
            int size;

            if(!tilingFactor){
                size = loopNode->getTripCount();
            }else{
                size = loopDependencyGraphNode->getReplication();
            }

            if(dataType->isIntegerTy()){

                baseType = "dfeInt(" + std::to_string(bitWidth) + ")," + std::to_string(size) + ")";

            }else if(dataType->isFloatingPointTy()){

                int exp;
                int mantissa;

                if(dataType->isDoubleTy()){
                    mantissa = DOUBLE_MANTISSA;
                    exp = DOUBLE_EXP;
                }else{
                    mantissa = FLOAT_MANTISSA;
                    exp = FLOAT_EXP;
                }

                baseType = "dfeFloat(" + std::to_string(exp) + "," + std::to_string(mantissa) +
                           ")," + std::to_string(size) + ").newInstance(this)";
            }
            decl.append(baseType + ";\n");
            declaredNestedVectors[basePtr] = std::pair<std::string,std::string>(vectorName,decl);
            loopHeadDeclarations.append(decl);

        }else{
            vectorName = declaredNestedVectors[basePtr].first;
        }
        varType = "";
        varName = vectorName + "[" + currentLoopIndex + "]";
        node->setName(vectorName);
        assignmentType = " <== ";
    }

    if(node->getType() == NodeType::LoopNode){

        switch(translationMode){
            case MaxLoopTranslationMode::JavaLoop :
                currentInstr = translateAsJavaLoop((DFGLoopNode*)node);
                loopHeadDeclarations = "";
                break;
            case MaxLoopTranslationMode::AutoLoop :
                llvm::errs() << "ERROR: translation mode not supported\n";
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }

    } else if(node->getType() == NodeType::MuxNode){
        llvm::errs() << "Mux translation not yet supported, terminating...\n";
        exit(EXIT_FAILURE);

    } else if(node->getType() == NodeType::AccumulNode){

        DFGNode* initPred = nullptr;
        llvm::PHINode* phi = (llvm::PHINode*)node->getValue();

        for(DFGNode* pred : node->getCrossScopePredecessors()){
            pred->getValue()->dump();
            phi->getIncomingValue(0)->dump();
            if(pred->getValue() == phi->getIncomingValue(0))
                initPred = pred;
        }
        if(initPred == nullptr){
            llvm::errs() << "ERROR: init pred not found in translation\n";
            exit(EXIT_FAILURE);
        }

        std::string initVal = getFullNameIfConstant(initPred);

        DFGAccNode* accNode = (DFGAccNode*)node;

        if(accNode->getIsCounter()){

            if(std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING) != kernelOptimizations.end()) {
                DFGLoopNode *loopNode = node->getLoop();
                LoopGraphNode *loopDependencyGraphNode =
                        MaxJInstructionPrinter::dependencyGraph->getNodeForLoop(loopNode);

                currentInstr.append("\t\t"+ nestingTabs + varType + varName +
                                    assignmentType + "constant.var(dfeInt(32)," + currentLoopIndex + ")" +
                                    " + (tileCounter * " + std::to_string(loopDependencyGraphNode->getReplication()) + ").cast(dfeInt(32));\n");

            }else{
                currentInstr.append("\t\t"+ nestingTabs + varType + varName +
                                    assignmentType + "constant.var(dfeInt(32)," + currentLoopIndex + ")" + ";\n");
            }

        }else{
            loopHeadDeclarations.append("\t\t" + varType + varName +
                                        assignmentType + initVal + ";\n");
        }

        if(!llvm::dyn_cast<llvm::PHINode>(node->getValue())){
            llvm::errs() << "ERROR: non phi accumul not supported, terimating...\n";
            exit(EXIT_FAILURE);
        }

    } else if(node->getType() == NodeType::CounterNode){

        DFGCounterNode* counterNode = (DFGCounterNode*)node;
        int width = 32;//default counter width

        if(counterNode->getStart() == 0 && counterNode->getStep() == 1){
            //simple counter init
            currentInstr = "\t\t" + varType + varName +
                           std::string(" = control.count.simpleCounter(") +
                           std::to_string(width) + std::string(");\n");

        }else{

            std::string paramsDecl = nestingTabs + std::string("\t\tCount.Params ") + varName +
                                     std::string("_params = control.count.makeParams(") +
                                     std::to_string(width) + std::string(").withStart(") +
                                     std::to_string(counterNode->getStart()) +
                                     std::string(").withInc(") + std::to_string(counterNode->getStep()) +
                                     std::string(");\n");

            currentInstr = paramsDecl.append(nestingTabs + std::string("\t\t"+ varType) + varName +
                                             std::string(" = control.count.makeCounter(") +
                                             varName + std::string("_params);\n"));
        }


    } else if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(node->getValue())) {

        if(instr->getOpcodeName() != std::string("load") &&
            instr->getOpcodeName() != std::string("store"))
        {
            if(llvm::CastInst* castInst = llvm::dyn_cast<llvm::CastInst>(instr)){

                std::string opcode = MaxJInstructionPrinter::opcodeMap[instr->getOpcodeName()];
                llvm::Type* destType = castInst->getDestTy();

                std::string castTarget = node->getCrossScopePredecessors().at(0)->getName();

                if(opcode == std::string("float")){

                    int exp;
                    int mantissa;

                    if(destType->isDoubleTy()){
                        mantissa = DOUBLE_MANTISSA;
                        exp = DOUBLE_EXP;
                    }else{
                        mantissa = FLOAT_MANTISSA;
                        exp = FLOAT_EXP;
                    }

                    currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                                   assignmentType + castTarget +
                                   std::string(".cast(dfeFloat(") + std::to_string(exp)+
                                   std::string(",") + std::to_string(mantissa) +
                                   std::string("));\n");
                }

                if(opcode == std::string("int")){

                    int bitWidth = destType->getScalarSizeInBits();
                    currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                                   assignmentType + castTarget +
                                   std::string(".cast(dfeInt(") + std::to_string(bitWidth) +
                                   std::string("));\n");
                }

            }else if(llvm::CallInst* callInstr = llvm::dyn_cast<llvm::CallInst>(instr)){

                std::string funcName = callInstr->getCalledFunction()->getName();
                std::string funcLib = MaxJInstructionPrinter::funcLibMap[funcName];
                std::vector<std::string> funcArgs = std::vector<std::string>();

                for(DFGNode* pred : node->getCrossScopePredecessors()){
                    funcArgs.push_back(getFullNameIfConstant(pred));
                }

                std::pair<std::string,std::vector<std::string>> newSignature;

                newSignature = translateFunctionArguments(callInstr->getCalledFunction(),funcArgs);

                funcName = newSignature.first;
                std::vector<std::string> argsList = newSignature.second;
                std::string argsSig = "(";

                for(std::string arg : argsList){
                    argsSig.append(arg + std::string(","));
                }

                argsSig.pop_back();
                argsSig.append(")");

                if(funcLib.length() == 0 || funcLib == std::string("Unknown")){
                    llvm::errs() << "ERROR: unknown function was called, terminating...\n";
                    llvm::errs() << "INFO: signature --> " << newSignature.first << " <--\n";
                    for(auto arg : newSignature.second){
                        llvm::errs() << arg;
                    }
                    llvm::errs() << "\n";
                    exit(EXIT_FAILURE);
                }

                libImports[funcLib].first = true;
                llvm::errs() << libImports[funcLib].first;

                currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                               assignmentType + funcLib + std::string(".") +
                               funcName + argsSig + std::string(";\n");

                if(libImports["OXiGen"].first){
                    if(oxigenFunctions.count(funcName)){
                        oxigenFunctions[funcName].first = true;
                    }
                }

            } else if (llvm::ICmpInst* iCmp = llvm::dyn_cast<llvm::ICmpInst>(instr)){

                std::string condOpCode = MaxJInstructionPrinter::cmpPredMap[iCmp->getPredicate()];
                std::string firstTerm = "NOT_FOUND";
                std::string secondTerm = "NOT_FOUND";

                for(DFGNode* pred : node->getCrossScopePredecessors()){
                    if(pred->getValue() == iCmp->getOperand(0)){
                        firstTerm = getFullNameIfConstant(pred);
                    }else if(pred->getValue() == iCmp->getOperand(1)){
                        secondTerm = pred->getName();
                    }
                }

                currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                               assignmentType + firstTerm + condOpCode + secondTerm +
                               std::string(";\n");

            }else if(llvm::SelectInst* selInstr = llvm::dyn_cast<llvm::SelectInst>(instr)){

                std::string cond = "NOT_FOUND";
                std::string trueAlt = "NOT_FOUND";
                std::string falseAlt = "NOT_FOUND";

                for(DFGNode* pred : node->getCrossScopePredecessors()){
                    if(pred->getValue() == selInstr->getCondition()){
                        cond = pred->getName();
                    }else if(pred->getValue() == selInstr->getTrueValue()){
                        trueAlt = getFullNameIfConstant(pred);
                    }else if(pred->getValue() == selInstr->getFalseValue()){
                        falseAlt = getFullNameIfConstant(pred);
                    }
                }

                currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                               assignmentType + cond + std::string(" ? ") +
                               trueAlt + std::string(" : ") + falseAlt + std::string(";\n");

            }else{

                std::vector<DFGNode*> predecessors = node->getCrossScopePredecessors();
                std::string opcode = MaxJInstructionPrinter::opcodeMap[instr->getOpcodeName()];

                currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                               assignmentType;

                if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(node->getValue())){

                    std::string firstOperand = "";
                    std::string secondOperand = "";
                    bool existsUnmatchedOperand = false;

                    if(predecessors.size() == 2) {
                        for (DFGNode *pred : predecessors) {
                            if (pred->getValue() == instr->getOperand(0)) {
                                firstOperand = getFullNameIfConstant(pred);
                            } else if (pred->getValue() == instr->getOperand(1)) {
                                secondOperand = getFullNameIfConstant(pred);
                            }
                        }

                        for (DFGNode *pred : predecessors) {
                            if (getFullNameIfConstant(pred) != firstOperand && secondOperand.size() == 0) {
                                secondOperand = getFullNameIfConstant(pred);
                            } else if (getFullNameIfConstant(pred) != secondOperand && firstOperand.size() == 0) {
                                firstOperand = getFullNameIfConstant(pred);
                            }
                        }

                        if(firstOperand.size() == 0 || secondOperand.size() == 0){
                            existsUnmatchedOperand = true;
                        }


                        if(!existsUnmatchedOperand)
                            currentInstr.append(firstOperand + opcode + secondOperand);
                        else{
                            for (DFGNode *pred : predecessors) {
                                currentInstr.append(getFullNameIfConstant(pred));
                                currentInstr.append(opcode);
                            }

                            currentInstr = currentInstr.substr(0, currentInstr.size() - opcode.size());
                        }

                    }else if(predecessors.size() == 1){
                        firstOperand = getFullNameIfConstant(predecessors.at(0));
                        currentInstr.append(firstOperand + opcode + firstOperand);
                    }else{
                        llvm::errs() << "ERROR: Unexpected ternary instruction:\n";
                        node->getValue()->dump();
                        exit(EXIT_FAILURE);
                    }

                }else{

                    for (DFGNode *pred : predecessors) {
                        currentInstr.append(getFullNameIfConstant(pred));
                        currentInstr.append(opcode);
                    }

                    currentInstr = currentInstr.substr(0, currentInstr.size() - opcode.size());
                }
                currentInstr.append(";\n");
            }
        }

    }else if(node->getType() == NodeType::Offset) {

        DFGOffsetNode *offsetNode = (DFGOffsetNode *) node;

        std::string ofsStreamName = offsetNode->getName();
        std::string sourceName = offsetNode->getCrossScopePredecessors().at(0)->getName();
        int offset = offsetNode->getOffsetAsInt();

        std::string offsetDeclaration = nestingTabs + std::string("\t\t"+ varType) + ofsStreamName +
                                        std::string(" = stream.offset(") + sourceName +
                                        std::string(", ") + std::to_string(offset) +
                                        std::string(");\n");
        currentInstr.append(offsetDeclaration);
    }

    for(DFGNode* succ : node->getLoopCarriedSuccessors()){
        currentInstr.append(nestingTabs + "\t\t"+ succ->getName() + assignmentType + varName + ";\n");
    }

    for(DFGNode* pred : node->getCrossScopePredecessors()){
        if(vectorPredNamesMap[pred->getName()].size()){

            pred->setName(vectorPredNamesMap[pred->getName()]);
        }
    }

    return currentInstr;
}

//DFGTranslator methods implementation

void DFGTranslator::printDFGAsKernel(std::vector<DFG*> dfg,std::vector<LoopDependencyGraph*> dependencyGraph,
                                     std::string kernelName, std::string packageName){
    
        DFGTranslator::dfgs = dfg;
        DFGTranslator::dependencyGraph = dependencyGraph;
        std::string kernelString = generateKernelString(kernelName,packageName);
        llvm::errs() << kernelString;
}

void DFGTranslator::assignNodeNames(){
    
    SequentialNamesManager* namesManager = new SequentialNamesManager();

    for(DFG* dfg : dfgs){

        int nodesCount = dfg->getNodesCount();
        llvm::errs() << "DEBUG: nodes count: " << nodesCount << "\n";
        std::vector<std::string> nodeNames;

        for(int i = 0; i < nodesCount; i++)
            nodeNames.push_back(namesManager->getNewName());

        dfg->setNameVector(nodeNames,dfg->getEndNode());

    }
}

std::string DFGTranslator::generateKernelString(std::string kernelName,std::string packageName){

    llvm::errs() << "INFO: printing dfg as kernel\n";
    llvm::errs() << "INFO: active kernel optimizations:\n\n";

    for(auto opt : kernelOptimizations)
        llvm::errs() << opt << "\n";

    MaxJInstructionPrinter* maxjPrinter = new MaxJInstructionPrinter(SE,F);

    maxjPrinter->kernelOptimizations.insert(maxjPrinter->kernelOptimizations.begin(),
                                            kernelOptimizations.begin(),kernelOptimizations.end());

    //TODO: revise this structure
    if(std::find(kernelOptimizations.begin(),kernelOptimizations.end(),GLOBAL_TILING) != kernelOptimizations.end()){

        if(DFGTranslator::dependencyGraph.size() == 0){
            llvm::errs() << "ERROR: no dependency graph available\n";
            exit(EXIT_FAILURE);
        }else if(DFGTranslator::dependencyGraph.size() > 1){
            llvm::errs() << "WARNING: multiple indipendent dependency graph. Tiling factor must be applicable to all\n";
        }

        int tilingFactor = dependencyGraph.at(0)->getBeginLoopNodes().at(0)->getTilingFactor();

        maxjPrinter->globalVariables.append("\t\tpublic static final int tilingFactor = " +
            std::to_string(tilingFactor) + ";\n\n");
        maxjPrinter->globalDFEVars.append("\t\tDFEVar tileCounter = control.count.simpleCounter(32, tilingFactor);\n");
    }
    //TODO: end of structure

    llvm::errs() << "\n";

    std::string kernelAsString = "\n";
    std::string endl = std::string(";\n");
    std::string kernelNamePlaceholder = "<kernelName>";

    std::string kernelSignatureTmpl = MaxJInstructionPrinter::kernelSignature_1 +
                                      maxjPrinter->globalVariables              +
                                      MaxJInstructionPrinter::kernelSignature_2;

    maxjPrinter->translationMode = MaxLoopTranslationMode::JavaLoop;
    
    //append pakage
    kernelAsString.append(std::string("package ") + packageName + endl);
    kernelAsString.append("\n");
    
    //append imports
    for(std::string import : MaxJInstructionPrinter::imports)
        kernelAsString.append(std::string("import ") + import + endl);

    std::string kernelBody = "";

    std::string::size_type n = 0;
    
    //replace kernel name in kernel signature
    while ( ( n = kernelSignatureTmpl.find(kernelNamePlaceholder,n)) 
        != std::string::npos )
    {
        kernelSignatureTmpl.replace( n, kernelNamePlaceholder.size(), kernelName );
        n += kernelName.size();
    }

    //append kernel signature
    kernelBody.append(kernelSignatureTmpl);

    kernelBody.append(maxjPrinter->globalDFEVars);
    
    //identify inputs and outputs
    assignNodeNames();

    std::vector<DFGReadNode*> readNodes;
    std::vector<DFGWriteNode*> writeNodes;
    std::vector<DFGNode*> argNodes;
    std::vector<DFGOffsetReadNode*> offsetReadNodes;
    std::vector<DFGOffsetWriteNode*> offsetWriteNodes;

    for(DFG* dfg : dfgs){

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGReadNode*> rNodes = dfg->getUniqueReadNodes(endNode);
        std::vector<DFGWriteNode*> wNodes = dfg->getUniqueWriteNodes(endNode);
        std::vector<DFGNode*> aNodes = dfg->getUniqueScalarArguments(endNode,F);

        readNodes.insert(readNodes.end(),rNodes.begin(),rNodes.end());
        writeNodes.insert(writeNodes.end(),wNodes.begin(),wNodes.end());
        argNodes.insert(argNodes.end(),aNodes.begin(),aNodes.end());

        llvm::errs() << "\nINFO: DFG recieved by translator:\n";
        dfg->printDFG();
    }

    for(DFGReadNode* rn : readNodes){
        if(rn->getType() == NodeType::OffsetRead){
            offsetReadNodes.push_back((DFGOffsetReadNode*)rn);
        }
    }

    for(DFGWriteNode* wn : writeNodes){
        if(wn->getType() == NodeType::OffsetWrite){
            offsetWriteNodes.push_back((DFGOffsetWriteNode*)wn);
        }
    }


    //append input declarations
    kernelBody.append(maxjPrinter->getInputStreamsDeclarations(readNodes));

    kernelBody.append(maxjPrinter->getScalarInputsDeclarations(argNodes));

    kernelBody.append("\n");

    //print instructions

    int dfgIndex = 0;

    for(DFG* dfg : dfgs) {

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGNode*> sortedNodes;

        dfg->resetFlags(endNode);

        sortedNodes = dfg->orderNodesWithFunc(F);

        llvm::errs() << "\nSorted nodes:\n";

        for(DFGNode* n : sortedNodes){
            n->getValue()->dump();
        }

        llvm::errs() << "\nEnd sorted nodes\n";

        maxjPrinter->dependencyGraph = DFGTranslator::dependencyGraph.at(dfgIndex);
        dfgIndex++;

        //append instructions
        kernelBody.append(maxjPrinter->generateInstructionsString(sortedNodes));

        kernelBody.append("\n");

    }

    //append output declarations
    kernelBody.append(maxjPrinter->getOutputStreamsDeclarations(writeNodes));
    
    //append kernel signature closing
    kernelBody.append(MaxJInstructionPrinter::kernelSignatureClosing);

    if(MaxJInstructionPrinter::libImports["OXiGen"].first) {
        MaxJInstructionPrinter::libImports["KernelMath"].first = true;
        MaxJInstructionPrinter::libImports["OXiGen"].first = false;
    }

    for(auto libImport : MaxJInstructionPrinter::libImports){
        if(libImport.second.first && libImport.first != std::string("OXiGen"))
            kernelAsString.append(std::string("import ") + libImport.second.second + endl);
    }

    kernelAsString.append("\n");

    for(auto oxigenFunction : maxjPrinter->getOxigenFunctions()){
        if(oxigenFunction.second.first == true){
            kernelAsString.append(oxigenFunction.second.second);
            break;
        }
    }

    kernelAsString.append("\n");
    kernelAsString.append(kernelBody);
    
    return kernelAsString;
}