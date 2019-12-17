
#import "DFGTranslator.h"

using namespace oxigen;

//default imports for the maxj kernel
std::vector<std::string> MaxJInstructionPrinter::imports = {
    "com.maxeler.maxcompiler.v2.kernelcompiler.Kernel",
    "com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters",
    "com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar"
};

//default kernel signature
std::string MaxJInstructionPrinter::kernelSignature = 
    std::string("class <kernelName> extends Kernel {\n\n")            +
    std::string("\t<kernelName>(KernelParameters parameters) {\n")    +
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
    {"fptosi","int"},
    {"sitrunc","int"}
    
};

MaxJInstructionPrinter::OpcodeMap MaxJInstructionPrinter::funcLibMap = {

        {"ceil","KernelMath"},
        {"abs","KernelMath"},
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
        {"Ncdf", "FunctionHart"}
};

MaxJInstructionPrinter::ImportMap MaxJInstructionPrinter::libImports = {
        {"KernelMath",std::pair<bool,std::string>(
                false,"com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.KernelMath")},
        {"FunctionHart",std::pair<bool,std::string>(
                false,"com.maxeler.maxblox.funceval.FunctionHart")},
        {"DFEVector",std::pair<bool,std::string>(
                false,"com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVector"
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
    std::vector<DFGReadNode*> tmp;

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
        //TODO : check correctness
        auto inputStream = inputNode->getReadingStream();
        llvm::Type* inputStreamType = inputStream.first->getType()->getPointerElementType();
        std::string nodeName = inputNode->getName();
        
        if(inputStreamType->isFloatingPointTy())
        {
            int size = inputStreamType->getPrimitiveSizeInBits();
            int mantissa = inputStreamType->getFPMantissaWidth();
            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.input(\"") + nodeName + 
                        std::string("\", dfeFloat(") + std::to_string(size-mantissa) +
                        std::string(", ") + std::to_string(mantissa) + std::string("));\n");
            
            declarations.append(decl);
        }
        if(inputStreamType->isIntegerTy())
        {
            int bitWidth = inputStreamType->getIntegerBitWidth();
            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.input(\"") + nodeName + 
                        std::string("\", dfeInt(") + std::to_string(bitWidth) + 
                        std::string("));\n");
                        
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
    std::vector<DFGWriteNode*> tmp;

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
            int size = outputStreamType->getPrimitiveSizeInBits();
            int mantissa = outputStreamType->getFPMantissaWidth();
            
            std::string decl = std::string("\t\tio.output(\"") + nodeName + 
                        std::string("\", ") + resultName + std::string(", dfeFloat(") + 
                        std::to_string(size-mantissa) + std::string(", ") +
                        std::to_string(mantissa) + std::string("));\n");
                        
            declarations.append(decl);
        }
        if(outputStreamType->isIntegerTy())
        {
            int bitWidth = outputStreamType->getIntegerBitWidth();
            
            std::string decl = std::string("\t\tio.output(\"") + nodeName + 
                        std::string("\", ") + resultName + std::string(", dfeInt(") + 
                        std::to_string(bitWidth) + std::string("));\n");
                        
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
            int size = argType->getPrimitiveSizeInBits();
            int mantissa = argType->getFPMantissaWidth();
            
            std::string decl = std::string("\t\tDFEVar ") + nodeName +
                        std::string(" = io.scalarInput(\"") + nodeName + 
                        std::string("\", dfeFloat(") + std::to_string(size-mantissa) +
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

    int iterations = loopNode->getTripCount();

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

    for(auto el = loopIndexes.begin(); el != loopIndexes.end();++el){
        llvm::errs() << "index: " + el->second << "\n";
    }

    std::string forHeader = std::string("\n"+nestingTabs+"\tfor(int "+l_idx+" = 0; "+l_idx+" < " +
                                        std::to_string(iterations)+"; "+l_idx+" += 1){\n");
    std::string forClosure = std::string(nestingTabs+"\t}\n");

    std::vector<DFG*> dfgs = loopNode->getIndipendentLoopGraphs();

    std::string loopBody = "";

    for(DFG* dfg : dfgs) {

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGNode*> sortedNodes;

        dfg->resetFlags(endNode);

        llvm::errs() << "\nLOOP GRAPH\n";
        dfg->printDFG();

        dfg->resetFlags(endNode);

        sortedNodes = dfg->orderNodesWithFunc(F);

        //append instructions
        loopBody.append(generateInstructionsString(sortedNodes));

        loopBody.append("\n");

    }
    nestingTabs = "";

    return std::string(loopHeadDeclarations +forHeader+loopBody+forClosure);
}

bool MaxJInstructionPrinter::isNestedVectorWrite(DFGNode *node) {

    if(node->getLoopDepth() < 2)
        return false;

    for(DFGNode* s : node->getSuccessors()){
        if(llvm::StoreInst* store = llvm::dyn_cast<llvm::StoreInst>(s->getValue())){
            if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(store->getPointerOperand())) {
                if (llvm::dyn_cast<llvm::AllocaInst>(gep->getPointerOperand()))
                    return true;
            }
        }
    }
    return false;
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

std::string MaxJInstructionPrinter::appendInstruction(DFGNode* node){

    std::string currentInstr = "";
    std::string varType = "DFEVar ";
    std::string assignmentType = " = ";
    std::string varName = node->getName();

    node->setIsDeclared();

    llvm::errs() << "node: ";
    node->getValue()->dump();
    llvm::errs() << "Node type: " << node->getType() << "\n";

    if(isNestedVectorWrite(node) && translationMode == MaxLoopTranslationMode::JavaLoop){

        llvm::AllocaInst* basePtr = getVectorBasePointer(node);
        DFGLoopNode* loopNode = node->getLoop();
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
            int size = loopNode->getTripCount();

            if(dataType->isIntegerTy()){

                baseType = "dfeInt(" + std::to_string(bitWidth) + ")," + std::to_string(size) + ")";

            }else if(dataType->isFloatingPointTy()){

                int mantissa = dataType->getFPMantissaWidth();
                baseType = "dfeFloat(" + std::to_string(bitWidth-mantissa) + "," + std::to_string(mantissa) +
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

    for(DFGNode* pred : node->getCrossScopePredecessors()){
        if(isNestedVectorWrite(pred) && translationMode == MaxLoopTranslationMode::JavaLoop){
            pred->setName(pred->getName() + "[" + currentLoopIndex + "]");
        }
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

        for(DFGNode* pred : node->getCrossScopePredecessors()){
            llvm::PHINode* phi = (llvm::PHINode*)node->getValue();
            pred->getValue()->dump();
            phi->getIncomingValue(0)->dump();
            if(pred->getValue() == phi->getIncomingValue(0))
                initPred = pred;
        }
        if(initPred == nullptr){
            llvm::errs() << "ERROR: init pred not found in translation\n";
            exit(EXIT_FAILURE);
        }

        loopHeadDeclarations.append("\t\t"+ varType + varName +
                                    assignmentType + initPred->getName() + ";\n");

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
                int destTypeSize = castInst->getDestTy()->getScalarSizeInBits();
                int split_1 = 8;
                int split_2 = destTypeSize - split_1;
                std::string castTarget = node->getCrossScopePredecessors().at(0)->getName();

                if(opcode == std::string("float")){

                    currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                                   assignmentType + castTarget +
                                   std::string(".cast(dfeFloat(") + std::to_string(split_1)+
                                   std::string(",") + std::to_string(split_2) +
                                   std::string("));\n");
                }

                if(opcode == std::string("int")){

                    currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                                   assignmentType + castTarget +
                                   std::string(".cast(dfeInt(") + std::to_string(destTypeSize) +
                                   std::string("));\n");
                }

            }else if(llvm::CallInst* callInstr = llvm::dyn_cast<llvm::CallInst>(instr)){

                std::string funcName = callInstr->getCalledFunction()->getName();
                std::string funcLib = MaxJInstructionPrinter::funcLibMap[funcName];
                std::vector<std::string> funcArgs = std::vector<std::string>();

                for(DFGNode* pred : node->getCrossScopePredecessors()){
                    funcArgs.push_back(pred->getName());
                }

                std::string argsSig = "(";

                for(std::string arg : funcArgs){
                    argsSig.append(arg + std::string(","));
                }

                argsSig.pop_back();
                argsSig.append(")");

                if(funcLib.length() == 0 || funcLib == std::string("Unknown")){
                    llvm::errs() << "ERROR: unknown function was called, terminating...\n";
                    exit(EXIT_FAILURE);
                }

                libImports[funcLib].first = true;
                llvm::errs() << libImports[funcLib].first;

                currentInstr = nestingTabs + std::string("\t\t"+ varType) + varName +
                               assignmentType + funcLib + std::string(".") +
                               funcName + argsSig + std::string(";\n");

            } else if (llvm::ICmpInst* iCmp = llvm::dyn_cast<llvm::ICmpInst>(instr)){

                std::string condOpCode = MaxJInstructionPrinter::cmpPredMap[iCmp->getPredicate()];
                std::string firstTerm = "NOT_FOUND";
                std::string secondTerm = "NOT_FOUND";

                for(DFGNode* pred : node->getCrossScopePredecessors()){
                    if(pred->getValue() == iCmp->getOperand(0)){
                        firstTerm = pred->getName();
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
                        trueAlt = pred->getName();
                    }else if(pred->getValue() == selInstr->getFalseValue()){
                        falseAlt = pred->getName();
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

                std::reverse(predecessors.begin(), predecessors.end());

                for (DFGNode *pred : predecessors) {
                    currentInstr.append(pred->getName());
                    currentInstr.append(opcode);
                }

                currentInstr = currentInstr.substr(0, currentInstr.size() - opcode.size());
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
    return currentInstr;
}

//DFGTranslator methods implementation

void DFGTranslator::printDFGAsKernel(std::vector<DFG*> dfg, std::string kernelName, std::string packageName){
    
        DFGTranslator::dfgs = dfg;
        std::string kernelString = generateKernelString(kernelName,packageName);
        llvm::errs() << kernelString;
}

void DFGTranslator::assignNodeNames(){
    
    SequentialNamesManager* namesManager = new SequentialNamesManager();

    for(DFG* dfg : dfgs){

        int nodesCount = dfg->getNodesCount();
        std::vector<std::string> nodeNames;

        for(int i = 0; i < nodesCount; i++)
            nodeNames.push_back(namesManager->getNewName());

        dfg->setNameVector(nodeNames,dfg->getEndNode());

    }
}

std::string DFGTranslator::generateKernelString(std::string kernelName,std::string packageName){

    std::string kernelAsString = "\n";
    std::string endl = std::string(";\n");
    std::string kernelNamePlaceholder = "<kernelName>";
    std::string kernelSignatureTmpl = MaxJInstructionPrinter::kernelSignature;
    
    MaxJInstructionPrinter* maxjPrinter = new MaxJInstructionPrinter(SE,F);
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

        //append instructions
        kernelBody.append(maxjPrinter->generateInstructionsString(sortedNodes));

        kernelBody.append("\n");

    }

    //append output declarations
    kernelBody.append(maxjPrinter->getOutputStreamsDeclarations(writeNodes));
    
    //append kernel signature closing
    kernelBody.append(MaxJInstructionPrinter::kernelSignatureClosing);

    for(auto libImport : MaxJInstructionPrinter::libImports){
        if(libImport.second.first == true)
            kernelAsString.append(std::string("import ") + libImport.second.second + endl);
    }

    kernelAsString.append("\n");

    kernelAsString.append(kernelBody);
    
    return kernelAsString;
}