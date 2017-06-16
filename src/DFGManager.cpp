
#include "DFG/DFGManager.h" 

using namespace SimpleDFG;

std::string SequentialNamesManager::generateNextName(){
    
    char oldNameLast = nextName.back();
    std::string newGenName;
        
    if(oldNameLast != 'z')
    {
        char newLast = oldNameLast + 1;
        newGenName = nextName.substr(0, nextName.size()-1);
        newGenName.append(1,newLast);
    }
    else
    {
        newGenName = nextName.append(1,'a');
    }
    
    return newGenName;
}

bool SequentialNamesManager::isPresent(std::string varName){ return true; } 