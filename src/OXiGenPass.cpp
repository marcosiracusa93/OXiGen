/** --------------------- OXiGenPass.cpp ---------------------------- //
 *
 *  Implementation of the OXiGen llvm::FunctionPass as part of the LLVM
 *  pass infarastructure. This pass processes the LLVM IR to generate
 *  the source files for the supported HLS tools. See OXiGenPass.h
 * 
 *  @author Francesco Peverelli, Marco Siracusa
 *  @see OXiGenPass.h
 */

#include <vector>
#include <iostream>
#include <llvm/IR/Dominators.h>

#include "OXiGenPass.h"
#include "ProcessingScheduler.h"

using namespace oxigen;

OXiGenPass* oxigen::createOXiGenWrapperPass(std::string functionName){
    return new OXiGenPass(functionName);
}

OXiGenPass::OXiGenPass(std::string functionName) : FunctionPass(ID){ this->functionName = functionName; }

bool OXiGenPass::runOnFunction(Function &F) {
        
        std::cout << "Running test pass on a function" << std::endl;

        //get scalar evolution and loop analysis
        ScalarEvolution* SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
        LoopInfo* LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        SCEVAAResult* SEAA = &getAnalysis<SCEVAAWrapperPass>().getResult();

        DefaultScheduler* scheduler = new DefaultScheduler(functionName, &F, SE ,LI, SEAA);
        scheduler->executeComponentsQueue();

        return false;
}

void OXiGenPass::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
    AU.addRequiredTransitive<SCEVAAWrapperPass>();
}

