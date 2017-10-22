
#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen {

    /**
     */
    enum class IndVarAccess { Exact = 1, Linear = 2, NonLinear = 3, Constant = 4, Undefined = 0 };

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
     * @class LoopAnalysisResult
     * @author 
     * @date 27/07/17
     * @file AnalysisManager.h
     * @brief 
     */
    class LoopAnalysisResult{
        
        private:
            
            llvm::PHINode* indVar;
            IndVarAccess accessType;
            LoopTripCount* loopTripCount;
            int nestingDepth;
            
        public:
        
            LoopAnalysisResult(llvm::PHINode* indVar, IndVarAccess accessType,
                                    LoopTripCount* loopTripCount, int nestingDepth){
                this->indVar = indVar;
                this->accessType = accessType;
                this->loopTripCount = loopTripCount;
                this->nestingDepth = nestingDepth;
            }
            
            llvm::PHINode* getIndVar(){
                return indVar;
            }
            
            IndVarAccess getAccessType(){
                return accessType;
            }
            
            LoopTripCount* getLoopTripCount(){
                return loopTripCount;
            }
            
            int getNestingDepth(){
                return nestingDepth;
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
            
            std::vector<LoopAnalysisResult*> loopsInfo;
            int maxNestingDepth;
        
        public:
    
            FunctionAnalysisResult(std::vector<LoopAnalysisResult*> loopsInfo);
            
            LoopAnalysisResult* getLoopInfo(int index){
                return loopsInfo.at(index);
            }
            
            int getMaxNestingDepth(){
                return maxNestingDepth;
            }
    };

    class DFGAnalysisResult{
        //TODO: implement this stub class
    };


    class AnalysisManager : public ProcessingComponent{
                
        public:

            FunctionAnalysisResult* analyzeFunction(llvm::Function* F, llvm::ScalarEvolution* SE,
                                                        llvm::LoopInfo* LI);
                                                        
            void acceptExecutor(ProcessingScheduler* processingScheduler){
                processingScheduler->execute(this);
            }

        private:

            IndVarAccess identifyAccessType(llvm::Function* F, llvm::ScalarEvolution* SE,llvm::Loop* loop);
            
    };

} // End OXiGen namespace

#endif