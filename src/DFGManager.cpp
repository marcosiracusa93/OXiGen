
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
    std::string("\t\tsuper(parameters);\n");
    
DFGManager::OpcodeMap DFGManager::opcodeMap = {
    
    {"fadd"," + "},
    {"add"," + "},
    {"mul"," * "},
    {"fmul"," * "}
    
};

DFGManager::TypesMap DFGManager::typesMap = {
    
    {"fadd"," + "},
    {"add"," + "},
    {"mul"," * "},
    {"fmul"," * "}
    
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
    
    return kernelAsString;
}

