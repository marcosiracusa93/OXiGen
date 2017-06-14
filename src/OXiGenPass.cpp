
using namespace llvm;
using namespace OXiGen;
using namespace SimpleDFG;

#include "OXiGen/OXiGenPass.h"

///Processes a loop which has a canonical induction variable
void TestPass::indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F){
    
    if(SE->hasLoopInvariantBackedgeTakenCount(topLevelLoop)){
        
        errs() << "Processing with taken back trip count...\n"; 
        
        if(topLevelLoop->getSubLoops().size() == 0){
            
            errs() << "Processing innermost loop...\n";
            
            IOStreams* IOs = getIOStreamDependences(topLevelLoop,F);
            
            errs() << "Input Streams: \n";
            
            for(Value* inStr : IOs->getInputStreams()) 
                inStr->dump(); 
                
            errs() << "Output streams: \n";
            
            for(Value* outStr : IOs->getOutputStreams())
                outStr->dump();
            
            std::vector<DFG*> dfgs = computeIOStreamBasedDFG(topLevelLoop,F,IOs);
            
            for(DFG* dfg : dfgs){
                dfg->printDFG(); 
            }
            
        }else{
            errs() << "Processing subloops... TODO\n";
        }
            
    }else
        errs() << "No taken back trip count, terminating... \n";
        return;
}