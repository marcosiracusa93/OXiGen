
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

            llvm::errs() << "Exact indVar access attributed by default...\n";
            IndVarAccess accessType = IndVarAccess::Exact;

            if(indVar == nullptr){
                llvm::errs() << "\nCanonical induction variable not found...\n";

                for(auto it = loop->getHeader()->begin(); it != loop->getHeader()->end(); ++it){

                    if (llvm::BranchInst* br = llvm::dyn_cast<llvm::BranchInst>(it)){

                        llvm::Value* cond = br->getCondition();

                        if(llvm::CmpInst* cmp = llvm::dyn_cast<llvm::CmpInst>(cond)){
                            llvm::Value* exitPred_1 = cmp->getOperand(0);

                            if(llvm::PHINode* exitPhi = llvm::dyn_cast<llvm::PHINode>(exitPred_1)){
                                indVar = exitPhi;
                                const llvm::SCEV* indVar_scev = SE->getSCEV(indVar);
                                if(const llvm::SCEVAddRecExpr* add_rec = llvm::dyn_cast<llvm::SCEVAddRecExpr>(indVar_scev)){
                                    llvm::Value* start_value = &(*(SE->getSCEVValues(add_rec->getStart())->begin())->first);
                                    llvm::Value* inc_value = &(*(SE->getSCEVValues(add_rec->getStepRecurrence(*SE))->begin())->first);

                                    if(llvm::dyn_cast<llvm::Constant>(start_value) && llvm::dyn_cast<llvm::Constant>(inc_value)){
                                        accessType = IndVarAccess::Linear;
                                        llvm::errs() << "Linear access attributed to non canonical phinode...\n";
                                    }else{
                                        llvm::errs() << "Non linear access not supported...\n";
                                        llvm::errs() << "Increment: "; inc_value->dump();
                                        llvm::errs() << "Start: "; start_value->dump();
                                        exit(EXIT_FAILURE);
                                    }
                                }


                            }else{
                                llvm::errs() << "Non PHI cond pred...\n";
                                cmp->getOperand(0)->dump();
                                exit(EXIT_FAILURE);
                            }
                        }else{
                            cond->dump();
                            llvm::errs() << "Non Cmp condition...\n";
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }

            llvm::errs() << "Recursive trip count analysis not implemented...\n";
            
            if(SE->hasLoopInvariantBackedgeTakenCount(loop)){
                backedgeTakenCount = 1;
                llvm::errs() << "Backedge taken count calculation not implemented...\n";
            }

            std::vector<LoopTripCount*> subloopsTripCount;
            LoopTripCount* loopTripCount = new LoopTripCount(backedgeTakenCount,subloopsTripCount);
            
            loopAnalysisResults.push_back(
                new LoopAnalysisResult(indVar,accessType,loopTripCount,loopDepth));
        }
        
   return new FunctionAnalysisResult(loopAnalysisResults); 

}

