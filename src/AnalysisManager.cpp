
#import "AnalysisManager.h"

using namespace oxigen;


FunctionAnalysisResult::FunctionAnalysisResult(std::vector<LoopAnalysisResult*> loopsInfo){
    
    this->loopsInfo = loopsInfo;
    
    maxNestingDepth = 0;
    
    for(LoopAnalysisResult* loopResult : loopsInfo){
        if(loopResult->getNestingDepth() > maxNestingDepth)
            maxNestingDepth = loopResult->getNestingDepth();
    }
}

FunctionAnalysisResult* AnalysisManager::analyzeFunction(llvm::Function* F, llvm::ScalarEvolution* SE,
                                            llvm::LoopInfo* LI){
                                                
    std::vector<LoopAnalysisResult*> loopAnalysisResults;
    
        for(llvm::Loop* loop : *LI){
            
            llvm::PHINode* indVar = loop->getCanonicalInductionVariable();
            int loopDepth = loop->getLoopDepth();
            int backedgeTakenCount = -1;

            if(indVar == nullptr){
                llvm::errs() << "\nCanonical induction variable not found, terminating...\n";
                exit(EXIT_FAILURE);
            }

            llvm::errs() << "Recursive trip count analysis not implemented...\n";
            
            if(SE->hasLoopInvariantBackedgeTakenCount(loop)){
                backedgeTakenCount = 1;
                llvm::errs() << "Backedge taken count calculation not implemented...\n";
            }

            std::vector<LoopTripCount*> subloopsTripCount;
            LoopTripCount* loopTripCount = new LoopTripCount(backedgeTakenCount,subloopsTripCount);
            
            llvm::errs() << "Exact indVar access attributed by default...\n";
            IndVarAccess accessType = IndVarAccess::Exact;
            
            loopAnalysisResults.push_back(
                new LoopAnalysisResult(indVar,accessType,loopTripCount,loopDepth));
        }
        
   return new FunctionAnalysisResult(loopAnalysisResults); 

}

