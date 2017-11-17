
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

IndVarAccess AnalysisManager::identifyAccessType(llvm::Function *F, llvm::ScalarEvolution *SE, llvm::Loop *L) {

    IndVarAccess accessType = IndVarAccess::Exact;
    llvm::errs() << "Exact indVar access attributed by default...\n";

    //iterate basic blocks of the loop body
    for (llvm::BasicBlock *BB : L->blocks()) {
        if (BB != L->getHeader() &&
            BB != L->getLoopLatch()) {
            for (llvm::Instruction &instr : BB->getInstList()) {

                if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(&instr)){
                    for(auto idx = gep->idx_begin(); idx != gep->idx_end(); ++idx){

                        bool isOffset = true;

                        if(llvm::Instruction* inst = llvm::dyn_cast<llvm::Instruction>(*idx)){
                            if((inst->isCast() && inst->getOperand(0) == L->getCanonicalInductionVariable())
                                    || L->getCanonicalInductionVariable() == *idx)
                                isOffset = false;
                        }else if(llvm::Constant* c = llvm::dyn_cast<llvm::Constant>(*idx)){
                            isOffset = !(c->isZeroValue());
                        }
                        if(isOffset){
                            idx->get()->dump();
                            const llvm::SCEV* scev_access = SE->getSCEV(*idx);

                            if(const llvm::SCEVAddRecExpr* addRec = llvm::dyn_cast<llvm::SCEVAddRecExpr>(scev_access)){
                                if(addRec->getStepRecurrence(*SE)->isOne()){

                                    const llvm::SCEV* start = addRec->getStart();

                                    if(llvm::dyn_cast<llvm::SCEVConstant>(start)){
                                        llvm::errs() << "Attributed constant access... ";
                                        accessType = IndVarAccess::Constant;
                                    } else{
                                        llvm::errs() << "Non constant access... ";
                                        exit(EXIT_FAILURE);
                                    }
                                } else{
                                    llvm::errs() << "Non constant access... ";
                                    exit(EXIT_FAILURE);
                                }
                            }else{
                                llvm::errs() << "Non add-rec based access... ";
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }

        }
    }

    return accessType;
}

FunctionAnalysisResult* AnalysisManager::analyzeFunction(llvm::Function* F, llvm::ScalarEvolution* SE,
                                            llvm::LoopInfo* LI){
                                                
    std::vector<LoopAnalysisResult*> loopAnalysisResults;
    
        for(llvm::Loop* loop : *LI){
            
            llvm::PHINode* indVar = loop->getCanonicalInductionVariable();
            int loopDepth = loop->getLoopDepth();
            int backedgeTakenCount = -1;

            IndVarAccess accessType = identifyAccessType(F,SE,loop);

            if(indVar == nullptr){
                llvm::errs() << "\nCanonical induction variable not found...\n";

                for(auto it = loop->getHeader()->begin(); it != loop->getHeader()->end(); ++it){

                    if (llvm::BranchInst* br = llvm::dyn_cast<llvm::BranchInst>(it)){

                        llvm::Value* cond = br->getCondition();

                        if(llvm::CmpInst* cmp = llvm::dyn_cast<llvm::CmpInst>(cond)){
                            llvm::Value* exitPred_1 = cmp->getOperand(0);

                            if(llvm::PHINode* exitPhi = llvm::dyn_cast<llvm::PHINode>(exitPred_1)){
                                indVar = exitPhi;

                                const llvm::SCEV* phi_scev = SE->getSCEV(exitPhi);

                                if(const llvm::SCEVAddRecExpr* add_rec = llvm::dyn_cast<llvm::SCEVAddRecExpr>(phi_scev)){
                                    if(add_rec->getStart()->getSCEVType() == llvm::SCEVTypes::scConstant &&
                                            accessType == IndVarAccess::Exact)
                                        accessType = IndVarAccess::Constant;
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
                const llvm::SCEV* back_edge_count_scev = SE->getBackedgeTakenCount(loop);

                if(back_edge_count_scev->getSCEVType() == llvm::SCEVTypes::scConstant){

                    const llvm::SCEVConstant *const_offset_scev = (llvm::SCEVConstant *)back_edge_count_scev;
                    llvm::ConstantInt* intOfs = const_offset_scev->getValue();
                    backedgeTakenCount = intOfs->getSExtValue();

                    llvm::errs() << "Backedge taken count is " << backedgeTakenCount << " for ";
                    indVar->dump();
                }
            }else{
                llvm::errs() << "Backedge taken count could not be computed for ";
                indVar->dump();
            }

            std::vector<LoopTripCount*> subloopsTripCount;
            LoopTripCount* loopTripCount = new LoopTripCount(backedgeTakenCount,subloopsTripCount);
            
            loopAnalysisResults.push_back(
                new LoopAnalysisResult(indVar,accessType,loopTripCount,loopDepth));
        }
    llvm::errs() << "Analysis phase terminated..\n";

    return new FunctionAnalysisResult(loopAnalysisResults);

}

