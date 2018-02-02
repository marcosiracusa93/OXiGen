//
// Created by user on 2/2/18.
//

#include "OxigenVectorizationUnroll.h"

using namespace oxigen;

OxigenVectorizationUnroll* oxigen::createOxigenVectorizationUnroll() {
    return new OxigenVectorizationUnroll();
}

bool OxigenVectorizationUnroll::runOnFunction(Function &F) {

    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    DominatorTree DT;

    AssumptionCache* AC = new AssumptionCache(F);
    OptimizationRemarkEmitter* ORE = new OptimizationRemarkEmitter(&F);

    for(Loop* outerLoop : *LI){
        for(Loop* subLoop : outerLoop->getSubLoops()){

            int tripCount = 0;
            const SCEV* tripCountSCEV = SE->getBackedgeTakenCount(subLoop);

            if(tripCountSCEV->getSCEVType() == SCEVTypes::scConstant){
                SCEVConstant* c = (SCEVConstant*)tripCountSCEV;
                tripCount = c->getValue()->getSExtValue();
            }
            UnrollLoop(subLoop,tripCount,tripCount,true,false,false,false,false,tripCount,0,LI,SE,&DT,AC,ORE,true);
        }
    }

    F.dump();
    return true;
}

void OxigenVectorizationUnroll::getAnalysisUsage(AnalysisUsage &AU) const {

    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}
