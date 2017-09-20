
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

    for(DFGReadNode* inputNode : inputs)
    {
        llvm::Value* inputStream = inputNode->getReadingStream();
        llvm::Type* inputStreamType = inputStream->getType()->getPointerElementType();
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

std::string MaxJInstructionPrinter::getOutputStreamsDeclarations(std::vector<DFGWriteNode*> outputs){
    
    std::string declarations;
    
    for(DFGWriteNode* outputNode :outputs)
    {
        llvm::Value* outputStream = outputNode->getWritingStream();
        llvm::Type* outputStreamType = outputStream->getType()->getPointerElementType();
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
                
            std::reverse(node->getPredecessors().begin(),node->getPredecessors().end());
            
            for(DFGNode* pred : node->getPredecessors())
            {
                currentInstr.append(pred->getName());
                currentInstr.append(opcode);
            }
            currentInstr = currentInstr.substr(0,currentInstr.size()-opcode.size());
            currentInstr.append(";\n");
        }
    }

    return currentInstr;
}

//DFGTranslator methods implementation

void DFGTranslator::printDFGAsKernel(DFG* dfg, std::string kernelName, std::string packageName){
    
        DFGTranslator::dfg = dfg;
        std::string kernelString = generateKernelString(kernelName,packageName);
        llvm::errs() << kernelString;
}

void DFGTranslator::assignNodeNames(){
    
    int nodesCount = dfg->getNodesCount();

    SequentialNamesManager* namesManager = new SequentialNamesManager();

    std::vector<std::string> nodeNames;
    
    for(int i = 0; i < nodesCount; i++)
    {
        nodeNames.push_back(namesManager->getNewName());
    }
    
    dfg->setNameVector(nodeNames,dfg->getEndNode());
}

std::string DFGTranslator::generateKernelString(std::string kernelName,std::string packageName){

    std::string kernelAsString = "\n";
    std::string endl = std::string(";\n");
    std::string kernelNamePlaceholder = "<kernelName>";
    std::string kernelSignatureTmpl = MaxJInstructionPrinter::kernelSignature;
    
    MaxJInstructionPrinter* maxjPrinter = new MaxJInstructionPrinter();
    
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
    
    DFGNode* endNode = dfg->getEndNode();
    
    std::vector<DFGReadNode*> readNodes = 
        dfg->getUniqueReadNodes(endNode);
    
    std::vector<DFGWriteNode*> writeNodes =
        dfg->getUniqueWriteNodes(endNode);
    
    std::vector<DFGNode*> sortedNodes(dfg->getNodesCount());

    std::vector<DFGNode*> argNodes = dfg->getUniqueScalarArguments(endNode);
    
    //append input declarations
    kernelAsString.append(maxjPrinter->getInputStreamsDeclarations(readNodes));
    
    kernelAsString.append(maxjPrinter->getScalarInputsDeclarations(argNodes));
    
    int startingPos = 0;
    
    dfg->resetFlags(endNode);
 
    dfg->orderNodes(endNode,startingPos,sortedNodes);
    
    //append instructions
    kernelAsString.append(maxjPrinter->generateInstructionsString(sortedNodes));
    
    //append output declarations
    kernelAsString.append(maxjPrinter->getOutputStreamsDeclarations(writeNodes));
    
    //append kernel signature closing
    kernelAsString.append(MaxJInstructionPrinter::kernelSignatureClosing);
    
    return kernelAsString;
}