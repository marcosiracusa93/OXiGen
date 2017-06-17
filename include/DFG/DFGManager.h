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
    
    class DFGManager{
    
    private:
        SequentialNamesManager* namesManager;
        
        std::vector<DFG*> DFGs;
        DFG* finalDFG;
        
    public:
    
        typedef std::map<std::string,std::string> OpcodeMap;
        typedef std::map<std::string,std::string> TypesMap;
        
        static OpcodeMap opcodeMap;
        static TypesMap typesMap;
        static std::vector<std::string> imports;
        static std::string kernelSignature;
    
        DFGManager(std::vector<DFG*> DFGs){ 
            this->DFGs = DFGs;
            namesManager = new SequentialNamesManager();
        }
        
        void printDFGAsKernel(std::string kernelName, std::string packageName);
        
    private:
    
        std::string generateKernelString(std::string kernelName,std::string packageName);
        
        void assignNodeNames();
    };
}

#endif