//
// Created by user on 2/2/18.
//

#include "OxigenVectorizationUnroll.h"

using namespace oxigen;

OxigenVectorizationUnroll* oxigen::createOxigenVectorizationUnroll() {
    return new OxigenVectorizationUnroll();
}

bool OxigenVectorizationUnroll::runOnFunction(Function &F) {

    return true;
}

void OxigenVectorizationUnroll::getAnalysisUsage(AnalysisUsage &AU) const {

    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}
