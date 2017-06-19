#ifndef DFGMANAGER_H
#define DFGMANAGER_H 

#include "DFG/Nodes.h"

namespace simple_dfg{
    
    class SequentialNamesManager{
        
    private:
        std::vector<std::string> varNames;
        std::string nextName;
    
    public:
        SequentialNamesManager(){ this->nextName = std::string("a"); }
        
        std::string getNewName(){
            std::string newName = nextName;
            varNames.push_back(newName);
            nextName = generateNextName();
            return newName;
        }
        
        bool isPresent(std::string varName);
            
    private:
        std::string generateNextName();
    };
    
    class MaxJInstructionPrinter{
        
    private:
        typedef std::map<std::string,std::string> OpcodeMap;
        static OpcodeMap opcodeMap;
        
    public:
        MaxJInstructionPrinter(){}
        
        std::string getImputStreamsDeclarations(std::vector<DFGReadNode*> inputs);
        std::string getOutputStreamsDeclarations(std::vector<DFGWriteNode*> outputs);
        std::string generateInstructionsString(DFGNode* node);
    };
    
    class DFGManager{
    
    private:
        SequentialNamesManager* namesManager;
        MaxJInstructionPrinter* maxjPrinter;
        
        std::vector<DFG*> DFGs;
        DFG* finalDFG;
        
    public:
    
        static std::vector<std::string> imports;
        static std::string kernelSignature;
        static std::string kernelSignatureClosing;
    
        DFGManager(std::vector<DFG*> DFGs){ 
            this->DFGs = DFGs;
            namesManager = new SequentialNamesManager();
            maxjPrinter = new MaxJInstructionPrinter();
        }
        
        void printDFGAsKernel(std::string kernelName, std::string packageName);
        
    private:
    
        std::string generateKernelString(std::string kernelName,std::string packageName);
        
        void assignNodeNames(std::vector<DFGReadNode*> readNodes);
    };
}

#endif