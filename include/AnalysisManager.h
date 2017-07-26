
#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include "ProcessingScheduler.h"

namespace oxigen {

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
            
            LoopTripCount(int tripCount, std::vector<LoopTripCount*> subloopsTripCount){
                this->tripCount = tripCount;
                this->subloopsTripCount = subloopsTripCount;
            }
                
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
        
            FunctionAnalysisResult(llvm::PHINode* indVar, IndVarAccess accessType,
                                    std::vector<LoopTripCount*> outerLoopsTripCount, int maxNestingDepth){
                this->indVar = indVar;
                this->accessType = accessType;
                this->outerLoopsTripCount = outerLoopsTripCount;
                this->maxNestingDepth = maxNestingDepth;
            }
            
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
        
    private:
        int stubAttr;
        //TODO: implement this stub class
    public:
    
        int get(){return stubAttr;}
        void set(int i){this->stubAttr = i;}
    }; 

    class AnalysisManager : public ProcessingComponent{
                
        public:
            
            FunctionAnalysisResult* analyzeFunction(llvm::Function &F){
                llvm::errs() << "Function analysis not implemented\n";
                return nullptr;
            }
            
    };

} // End OXiGen namespace

#endif