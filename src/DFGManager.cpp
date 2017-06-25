/** --------------------- DFGManager.cpp ---------------------------- //
 *
 * Contains the implementation of the methods declared in DFGManager.h
 */

#include "DFG/DFGManager.h" 

using namespace simple_dfg;

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

std::string SequentialNamesManager::generateNextName(){
    
    char oldNameFirst = nextName.front();
    std::string newGenName;
        
    //generates names starting from "a","b"..."aa","ab"...
    if(oldNameFirst != 'z')
    {
        char newFirst = oldNameFirst + 1;
        newGenName = nextName.substr(1, nextName.size());
        newGenName.insert(0,1,newFirst);
    }
    else
    {
        newGenName = nextName;
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

bool SequentialNamesManager::isPresent(std::string varName){ 
    
    for(std::string var : varNames){
        if(var == varName)
            return true;
    }
    return false; 
} 

//MaxJInstructionPrinter methods implementation

std::string MaxJInstructionPrinter::getImputStreamsDeclarations(std::vector<DFGReadNode*> inputs){

    std::string declarations;
    
    for(DFGReadNode* inputNode : inputs)
    {
        Value* inputStream = inputNode->getReadingStream();
        Type* inputStreamType = inputStream->getType()->getPointerElementType();
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

std:: string MaxJInstructionPrinter::getScalarInputsDeclarations(std::vector<DFGNode*> scalarInputs){
    
    std::string declarations;
    
    for(DFGNode* n : scalarInputs)
    {
        Type* argType = n->getValue()->getType();
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

std::string MaxJInstructionPrinter::getOutputStreamsDeclarations(std::vector<DFGWriteNode*> outputs){
    
    std::string declarations;
    
    for(DFGWriteNode* outputNode :outputs)
    {
        Value* outputStream = outputNode->getWritingStream();
        Type* outputStreamType = outputStream->getType()->getPointerElementType();
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

std::string MaxJInstructionPrinter::generateInstructionsString(DFGNode* node){
    
    std::string instructionsString;
    
    std::string currentInstr = "";
    
    if(Instruction* instr = dyn_cast<Instruction>(node->getValue()))
    {
        if(instr->getOpcodeName() != std::string("load") &&
            instr->getOpcodeName() != std::string("store"))
        {
            std::string opcode = MaxJInstructionPrinter::opcodeMap[instr->getOpcodeName()];
            
            currentInstr = std::string("\t\tDFEVar ") + node->getName() +
                std::string(" = ");
            
            for(DFGNode* pred : node->getPredecessors())
            {
                currentInstr.append(pred->getName());
                currentInstr.append(opcode);
            }
            currentInstr = currentInstr.substr(0,currentInstr.size()-opcode.size());
            currentInstr.append(";\n");
        }
    }
    
    for(DFGNode* pred : node->getPredecessors())
    {
        instructionsString.append(generateInstructionsString(pred));
    }
    
    return instructionsString.append(currentInstr);
}

//DFGManager methods implementation

void DFGManager::printDFGAsKernel(std::string kernelName, std::string packageName){
    
    if(DFGs.size() == 1)
    {
        finalDFG = DFGs.front();
        std::string kernelString = DFGManager::generateKernelString(kernelName,packageName);
        errs() << kernelString;
        return;
    }
    else
    {
        errs() << "DFG arrangement not yet supported...\n";
        return;
    }
}

void DFGManager::assignNodeNames(){
        
    int nodesCount = DFGManager::finalDFG->getNodesCount();
    
    std::vector<std::string> nodeNames;
    
    for(int i = 0; i < nodesCount; i++)
    {
        nodeNames.push_back(DFGManager::namesManager->getNewName());
    }
    
    DFGManager::finalDFG->setNameVector(nodeNames,DFGManager::finalDFG->getEndNode());
}

std::string DFGManager::generateKernelString(std::string kernelName,std::string packageName){
    
    std::string kernelAsString = "\n";
    std::string endl = std::string(";\n");
    std::string kernelNamePlaceholder = "<kernelName>";
    std::string kernelSignatureTmpl = MaxJInstructionPrinter::kernelSignature;
    
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
    DFGManager::assignNodeNames();
    
    std::vector<DFGReadNode*> readNodes = 
        DFGManager::finalDFG->getUniqueReadNodes(DFGManager::finalDFG->getEndNode());
    
    std::vector<DFGWriteNode*> writeNodes = 
        DFGManager::finalDFG->getWriteNodes(DFGManager::finalDFG->getEndNode());
    
    std::vector<DFGNode*> argNodes = DFGManager::finalDFG->getScalarArguments(DFGManager::finalDFG->getEndNode());
    
    //append input declarations
    kernelAsString.append(DFGManager::maxjPrinter->getImputStreamsDeclarations(readNodes));
    
    kernelAsString.append(DFGManager::maxjPrinter->getScalarInputsDeclarations(argNodes));
    
    //append instructions
    kernelAsString.append(DFGManager::maxjPrinter->generateInstructionsString(DFGManager::finalDFG->getEndNode()));
    
    //append output declarations
    kernelAsString.append(DFGManager::maxjPrinter->getOutputStreamsDeclarations(writeNodes));
    
    //append kernel signature closing
    kernelAsString.append(MaxJInstructionPrinter::kernelSignatureClosing);
    
    return kernelAsString;
}

