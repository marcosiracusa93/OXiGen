
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
            intOfs->dump();

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
        std::string resultName = outputNode->getPredecessors().front()->getName();
        
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

/*std::string MaxJInstructionPrinter::getTmpStoreInstructionString(DFGNode* node){

    std::string instructionString = "";

    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(node->getValue()))
    {
        if(instr->getOpcodeName() != std::string("load") &&
           instr->getOpcodeName() != std::string("store")) {



            llvm::Instruction *instr = (llvm::Instruction *) node->getValue();

            std::string opcode = MaxJInstructionPrinter::opcodeMap[instr->getOpcodeName()];

            instructionString.append(std::string("\t\tDFEVar ") + node->getName() +
                                     std::string(" = "));

            instructionString = instructionString.substr(0, instructionString.size() - opcode.size());
            instructionString.append(";\n");

            for (DFGNode* succ : node->getSuccessors()) {
                if (llvm::dyn_cast<llvm::StoreInst>(succ->getValue())) {

                    storeOffset = succ->getStreamWindow().first;
                    int effectiveStoreOffset = -minDelay + storeOffset;
                    std::string newNodeName = node->getName() + std::string("_outoffs");

                    std::string storeOffsetInstruction = "";

                    if (effectiveStoreOffset != 0) {

                        storeOffsetInstruction.append(
                                std::string("\t\tDFEVar ") + newNodeName +
                                std::string(" = stream.offset(") + node->getName() +
                                std::string(", ") + std::to_string(effectiveStoreOffset) +
                                std::string(");\n"));
                        node->setName(newNodeName);
                        instructionString.append(storeOffsetInstruction);
                    }



                    ///IF STORE HAS OFFSET -> COMPUTE VALIDITY
                    ///                    -> GET PREVIOUS STORE
                    ///                    -> CREATE TERNARY INSTRUCTION
                }
            }
        }
    }

    return instructionString;
}*/

std::string MaxJInstructionPrinter::appendInstruction(DFGNode* node){
    
    std::string currentInstr = "";
    
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(node->getValue()))
    {
        if(instr->getOpcodeName() != std::string("load") &&
            instr->getOpcodeName() != std::string("store"))
        {

            std::string opcode = MaxJInstructionPrinter::opcodeMap[instr->getOpcodeName()];

            currentInstr = std::string("\t\tDFEVar ") + node->getName() +
                           std::string(" = ");

            std::reverse(node->getPredecessors().begin(), node->getPredecessors().end());

            for (DFGNode *pred : node->getPredecessors()) {
                currentInstr.append(pred->getName());
                currentInstr.append(opcode);
            }
            currentInstr = currentInstr.substr(0, currentInstr.size() - opcode.size());
            currentInstr.append(";\n");

        }

    }else if(node->getType() == NodeType::Offset) {

        DFGOffsetNode *offsetNode = (DFGOffsetNode *) node;

        std::string ofsStreamName = offsetNode->getName();
        std::string sourceName = offsetNode->getPredecessors().at(0)->getName();
        int offset = offsetNode->getOffsetAsInt();

        std::string offsetDeclaration = std::string("\t\tDFEVar ") + ofsStreamName +
                                        std::string(" = stream.offset(") + sourceName +
                                        std::string(", ") + std::to_string(offset) +
                                        std::string(");\n");
        currentInstr.append(offsetDeclaration);
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
    
    MaxJInstructionPrinter* maxjPrinter = new MaxJInstructionPrinter(SE);
    
    //append pakage
    kernelAsString.append(std::string("package ") + packageName + endl);
    kernelAsString.append("\n");
    
    //append imports
    for(std::string import : MaxJInstructionPrinter::imports)
        kernelAsString.append(std::string("import ") + import + endl);
    
    kernelAsString.append("\n");
    
    std::string::size_type n = 0;
    
    //replace kernel name in kernel signature
    while ( ( n = kernelSignatureTmpl.find(kernelNamePlaceholder,n)) 
        != std::string::npos )
    {
        kernelSignatureTmpl.replace( n, kernelNamePlaceholder.size(), kernelName );
        n += kernelName.size();
    }
    
    //append kernel signature
    kernelAsString.append(kernelSignatureTmpl);
    
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
        std::vector<DFGNode*> aNodes = dfg->getUniqueScalarArguments(endNode);

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
    kernelAsString.append(maxjPrinter->getInputStreamsDeclarations(readNodes));

    kernelAsString.append(maxjPrinter->getScalarInputsDeclarations(argNodes));

    //kernelAsString.append(maxjPrinter->getConstantInputOffsetsDeclarations(offsetReadNodes));

    kernelAsString.append("\n");

    //print instructions
    for(DFG* dfg : dfgs) {

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGNode*> sortedNodes(dfg->getNodesCount());

        int startingPos = 0;

        dfg->resetFlags(endNode);

        dfg->orderNodes(endNode, startingPos, sortedNodes);

        //append instructions
        kernelAsString.append(maxjPrinter->generateInstructionsString(sortedNodes));

        kernelAsString.append("\n");

    }

    //kernelAsString.append(maxjPrinter->getConstantOutputOffsetsDeclarations(offsetWriteNodes));

    //append output declarations
    kernelAsString.append(maxjPrinter->getOutputStreamsDeclarations(writeNodes));
    
    //append kernel signature closing
    kernelAsString.append(MaxJInstructionPrinter::kernelSignatureClosing);
    
    return kernelAsString;
}