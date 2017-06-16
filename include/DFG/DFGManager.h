#ifndef DFGMANAGER_H
#define DFGMANAGER_H 

#include "DFG/Nodes.h"

namespace SimpleDFG{
    
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
        SequentialNamesManager namesManager;
        
        std::vector<DFG*> DFGs;
        DFG* finalDFG;
        
        
    public:
    
        DFGManager(std::vector<DFG*> DFGs){ this->DFGs = DFGs; }
        
        //void printDFGAsKernel(std::string kerelName);
    };
}

#endif