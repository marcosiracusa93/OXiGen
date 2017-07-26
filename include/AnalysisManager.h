
#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include "llvm-c/Core.h"

/**
 */
enum class IndVarAccess { Exact, Linear, NonLinear, Undefined };

/**
 * @class LoopTripCount
 * @author 
 * @date 26/07/17
 * @file AnalysisManager.h
 * @brief 
 */
class LoopTripCount{
    
    private:

        int tripCount;
        std::vector<LoopTripCount*> subloopsTripCount;
        
    public:
        
        int getTripCount(){
            return tripCount;
        }
        
        std::vector<LoopTripCount*> getSubloopsTripCount(){
            return subloopsTripCount;
        }
    
};

/**
 * @class FunctionAnalysisResult
 * @author 
 * @date 26/07/17
 * @file AnalysisManager.h
 * @brief 
 */
class FunctionAnalysisResult{
        
    private:
        
        llvm::PHINode* indVar;
        IndVarAccess accessType;
        std::vector<LoopTripCount*> outerLoopsTripCount;
        int maxNestingDepth;

    public:
        
        llvm::PHINode* getIndVar(){
            return indVar;
        }
        
        IndVarAccess getAccessType(){
            return accessType;
        }
        
        std::vector<LoopTripCount*> getOuterLoopsTripCount(){
            return outerLoopsTripCount;
        }
        
        int getMaxNestingDepth(){
            return maxNestingDepth;
        }
};

class LoopAnalysisResult{
    //TODO: implement this stub class
};

class DFGAnalysisResult{
    //TODO: implement this stub class
}; 

#endif