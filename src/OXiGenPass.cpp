
#include <vector>
#include <iostream>
#include "OXiGen/OXiGenPass.h"

using namespace OXiGen;
using namespace Utils;

TestPass* OXiGen::createTestWrapperPass(){ return new TestPass::TestPass(); }

TestPass::TestPass() : FunctionPass(ID){}

///TODO add some doc
bool TestPass::runOnFunction(Function &F) {
        
        std::cout << "Running test pass on a function" << std::endl;
        
        //get scalar evolution and loop analysis
        TestPass::SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
        TestPass::LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        
        //process every top level loops in the function
        for(Loop* const loop : *LI){
            
            PHINode* indVar = loop->getCanonicalInductionVariable();
            
            if(indVar != NULL)
                //if indVar is found, process the part of the loop which depends on it
                indVarBasedLoopProcessing(loop,F);
            else
                errs() << "No canonical induction variable found, terminating... \n";
                return false;
        }
        return false;
}

void TestPass::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}

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
        
///Returns an object containing the values of the streams used in the loop
///If they appear in the function arguments, they are classified as input streams
///If they are stored, they are classified as output streams
IOStreams* TestPass::getIOStreamDependences(Loop* topLevelLoop, Function &F){
    
    errs() << "Checking for IO streams dependences... \n";
    
    std::vector<Value*> inputStreams;
    std::vector<Value*> outputStreams;
    
    //Iterate basic blocks of the loop body
    for(BasicBlock *BB : topLevelLoop->blocks()){
        if(BB != topLevelLoop->getHeader() &&
            BB != topLevelLoop->getLoopLatch()){
            
            //for each getelementptr, check if uses an IO stream
            for(Instruction &instr : BB->getInstList()){
                if(instr.getOpcodeName() == std::string("getelementptr"))
                    if(directlyUses(&instr,topLevelLoop->getCanonicalInductionVariable())){

                        if(isStored(&instr))
                            outputStreams.push_back(instr.getOperand(0));
                            
                        for(Argument &arg : F.args()){
                            if(&arg == instr.getOperand(0)){
                                inputStreams.push_back(instr.getOperand(0));
                            }
                        }
                    }       
            }
        }
    }
    return new IOStreams(inputStreams,outputStreams);
}

///TODO add some doc
std::vector<DFG*> TestPass::computeIOStreamBasedDFG(Loop* topLevelLoop,Function &F,IOStreams* IOs){
    
    std::vector<DFG*> computedDFGs;
    
    for(Value* outStream : IOs->getOutputStreams()){

        for(BasicBlock *BB : topLevelLoop->blocks()){
            if(BB != topLevelLoop->getHeader() &&
                BB != topLevelLoop->getLoopLatch()){
                
                for(Instruction &instr : BB->getInstList()){
                    
                    if(instr.getOpcodeName() == std::string("store"))
                        if(Instruction* storeAddr = dyn_cast<Instruction>(instr.getOperand(1)))
                            if(storeAddr->getOperand(0) == outStream ){
                                
                                errs() << "Computing DFG\n";
                                computedDFGs.push_back(computeDFGFromBase(new DFGWriteNode(&instr,IOs)));
                            }
                }
            }
        }
    }
    return computedDFGs;
}

///TODO add some doc
void TestPass::populateDFG(DFGNode* node){
    if(Instruction* instr = dyn_cast<Instruction>(node->getValue()))
    {
        for(Value* operand : instr->operands())
        {
            DFGNode* prevNode = new DFGNode(operand);
            node->linkPredecessor(prevNode);
            populateDFG(prevNode);
        }	
    }
}

///TODO add some doc
DFG* TestPass::computeDFGFromBase(DFGNode* baseNode){
        
    DFG* graph = new DFG(baseNode);
    
    
    
    return graph;
}
        
///Checks if 'dependentValue' uses 'targetValue' directly
///At present, uses through 'sext' instructions are considered direct 
bool TestPass::directlyUses(Value *dependentValue, Value* targetValue){
    
    if(Instruction* instr = dyn_cast<Instruction>(dependentValue))
        for(Use &operand : instr->operands()){

            if(operand.get() == targetValue){
                return true;
            }

            if(Instruction* instrAsOperand = dyn_cast<Instruction>(operand.get()))
                if(instrAsOperand != nullptr and
                    instrAsOperand->getOpcodeName()== std::string("sext")){
                        
                    return directlyUses(instrAsOperand,targetValue);//propagate as direct use
            }
        }
        
    return false;
}

///Checks wether the value passed is used by a store instruction
///TODO: verify/implement recursive behavior
bool TestPass::isStored(Value* value){

    for(User* user : value->users()){
        if(Instruction* userAsInstr = dyn_cast<Instruction>(user)) 
            if(userAsInstr->getOpcodeName() == std::string("store") &&
                user->getOperand(1) == value)
                return true;
    }

    return false;
}