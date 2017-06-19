
#include "DFG/DFGManager.h" 

using namespace simple_dfg;

std::vector<std::string> DFGManager::imports = {
    "com.maxeler.maxcompiler.v2.kernelcompiler.Kernel",
    "com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters",
    "com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar"
};

std::string DFGManager::kernelSignature = 
    std::string("class <kernelName> extends Kernel {\n\n")              +
    std::string("\t<kernelName>(KernelParameters parameters) {\n")    +
    std::string("\t\tsuper(parameters);\n\n");
    
std::string DFGManager::kernelSignatureClosing = std::string("\t}\n}\n");
    
MaxJInstructionPrinter::OpcodeMap MaxJInstructionPrinter::opcodeMap = {
    
    {"fadd"," + "},
    {"add", " + "},
    {"mul", " * "},
    {"fmul"," * "},
    {"fdiv", " / "},
    {"sdiv", " / "},
    {"udiv", " / "},
    
};

std::string SequentialNamesManager::generateNextName(){
    
    char oldNameFirst = nextName.front();
    std::string newGenName;
        
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
    std::string kernelSignatureTmpl = DFGManager::kernelSignature;
    
    kernelAsString.append(std::string("package ") + packageName + endl);
    kernelAsString.append("\n");
    
    for(std::string import : DFGManager::imports)
        kernelAsString.append(std::string("import ") + import + endl);
    
    kernelAsString.append("\n");
    
    std::string::size_type n = 0;
    
    while ( ( n = kernelSignatureTmpl.find(kernelNamePlaceholder,n)) 
        != std::string::npos )
    {
        kernelSignatureTmpl.replace( n, kernelNamePlaceholder.size(), kernelName );
        n += kernelName.size();
    }
    
    kernelAsString.append(kernelSignatureTmpl);
    
    DFGManager::assignNodeNames();
    
    std::vector<DFGReadNode*> readNodes = 
        DFGManager::finalDFG->getReadNodes(DFGManager::finalDFG->getEndNode());
    std::vector<DFGWriteNode*> writeNodes = 
        DFGManager::finalDFG->getWriteNodes(DFGManager::finalDFG->getEndNode());
    
    kernelAsString.append(DFGManager::maxjPrinter->getImputStreamsDeclarations(readNodes));
    
    kernelAsString.append(DFGManager::maxjPrinter->generateInstructionsString(DFGManager::finalDFG->getEndNode()));
    
    kernelAsString.append(DFGManager::maxjPrinter->getOutputStreamsDeclarations(writeNodes));
    
    kernelAsString.append(DFGManager::kernelSignatureClosing);
    
    return kernelAsString;
}
