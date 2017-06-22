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
#include "OXiGen/OXiGenPass.h"
#include "DFG/DFGManager.h"

using namespace oxigen;
using namespace utils;

OXiGenPass* oxigen::createOXiGenWrapperPass(std::string functionName){
    return new OXiGenPass::OXiGenPass(functionName); 
}

OXiGenPass::OXiGenPass(std::string functionName) : FunctionPass(ID){ this->functionName = functionName; }

bool OXiGenPass::runOnFunction(Function &F) {
        
        std::cout << "Running test pass on a function" << std::endl;
        
        //get scalar evolution and loop analysis
        OXiGenPass::SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
        OXiGenPass::LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        
        //process every top level loop in the function
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

void OXiGenPass::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
    AU.addRequiredTransitive<LoopInfoWrapperPass>();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}

void OXiGenPass::indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F){
    
    //checks whether the loop has a known taken back trip count 
    if(SE->hasLoopInvariantBackedgeTakenCount(topLevelLoop))
    {
        //checks for the presence of subloops within this loop
        if(topLevelLoop->getSubLoops().size() == 0)
        {
            //retrieves the IO streams 
            IOStreams* IOs = getIOStreamDependences(topLevelLoop,F);
            
            errs() << "Input Streams: \n";
            
            for(Value* inStr : IOs->getInputStreams()) 
                inStr->dump(); 
                
            errs() << "Output streams: \n";
            
            for(Value* outStr : IOs->getOutputStreams())
                outStr->dump();
            
            //obtain a vector of DFGs involving the IO streams 
            std::vector<DFG*> dfgs = computeIOStreamBasedDFG(topLevelLoop,F,IOs);
            
            for(DFG* dfg : dfgs) dfg->printDFG();

            //manager used to process DFGs
            simple_dfg::DFGManager* dfgManager = new simple_dfg::DFGManager(dfgs);
            
            //print the resulting maxj code in the console
            dfgManager->printDFGAsKernel(functionName + std::string("Kernel"),functionName);
        }
        else
        {
            errs() << "Processing subloops... TODO\n";
        }
            
    }
    else
    {
        errs() << "No taken back trip count, terminating... \n";
        return;
    }
}
        
IOStreams* OXiGenPass::getIOStreamDependences(Loop* topLevelLoop, Function &F){
    
    errs() << "Checking for IO streams dependences... \n";
    
    std::vector<Value*> inputStreams;
    std::vector<Value*> outputStreams;
    
    //iterate basic blocks of the loop body
    for(BasicBlock *BB : topLevelLoop->blocks()){
        if(BB != topLevelLoop->getHeader() &&
            BB != topLevelLoop->getLoopLatch()){
            
            //for each getelementptr, check if uses an IO stream
            for(Instruction &instr : BB->getInstList()){
                if(instr.getOpcodeName() == std::string("getelementptr"))
                    if(directlyUses(&instr,topLevelLoop->getCanonicalInductionVariable())){
                        
                        //if the base pointer used by the getelementptr is stored, it is considered an output stream
                        if(isStored(&instr))
                            outputStreams.push_back(instr.getOperand(0));
                        
                        //if the element pointed by the getelementptr is present in the function arguments
                        //it is considered an input stream
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

std::vector<DFG*> OXiGenPass::computeIOStreamBasedDFG(Loop* topLevelLoop,Function &F,IOStreams* IOs){
    
    std::vector<DFG*> computedDFGs;
    
    //iterates over the loop body instructions
    for(Value* outStream : IOs->getOutputStreams()){

        for(BasicBlock *BB : topLevelLoop->blocks()){
            if(BB != topLevelLoop->getHeader() &&
                BB != topLevelLoop->getLoopLatch()){
                
                for(Instruction &instr : BB->getInstList()){
                    
                    //if a store is found, and the store refers to an output stream,
                    //a DFG is computed with the store as its base, and it is added 
                    //to the DFG vector
                    if(instr.getOpcodeName() == std::string("store"))
                        if(Instruction* storeAddr = dyn_cast<Instruction>(instr.getOperand(1)))
                            if(storeAddr->getOperand(0) == outStream ){
                                
                                errs() << "Computing DFG\n";
                                computedDFGs.push_back(computeDFGFromBase(new DFGWriteNode(&instr,IOs),topLevelLoop, IOs));
                            }
                }
            }
        }
    }
    return computedDFGs;
}

void OXiGenPass::populateDFG(DFGNode* node,Loop* loop, IOStreams* IOs){
    
    Value* parentVal = node->getValue();

    if(Instruction* parentInstr = dyn_cast<Instruction>(parentVal)){
        
        for(Value* operandVal : parentInstr->operands()){
            
            if(Instruction* operandAsInstr = dyn_cast<Instruction>(operandVal))
            {
                //these checks identify a DFGReadNode which accesses a stream
                //through the exact value of the canonical induction variable
                //at any given iteration
                if(operandAsInstr->getOpcodeName() == std::string("load"))
                {
                    Instruction* getelemPtrInstr = getInstrFromOperand(
                        operandAsInstr->getOperand(0), std::string("getelementptr"));
                    
                    if(getelemPtrInstr != nullptr && (hasSextOnIndvar(getelemPtrInstr,loop) ||
                    getelemPtrInstr->getOperand(1) == loop->getCanonicalInductionVariable()))
                    {
                        DFGReadNode* childNode = new DFGReadNode(operandVal,IOs);
                        node->linkPredecessor(childNode);
                    }
                }
                else
                {
                    //Node initialization for a generic instruction
                    DFGNode* childNode = new DFGNode(operandVal);
                    node->linkPredecessor(childNode);
                        
                    populateDFG(childNode,loop,IOs);
                    
                }
            }
            else
            {
                //Node initializaton for a generic llvm::Value which is not an 
                //instruction
                DFGNode* childNode = new DFGNode(operandVal);
                node->linkPredecessor(childNode);
            }
        }
    }
    else
    {
        errs() << "Non instr parent\n";
        return;
    }
    
}

DFG* OXiGenPass::computeDFGFromBase(DFGWriteNode* baseNode,Loop* loop, IOStreams* IOs){
        
    //intializes a new DFG object 
    DFG* graph = new DFG(baseNode);
    //populates it from its base node
    populateDFG(shortcutSoreGetelementPtr(baseNode),loop,IOs);
    
    return graph;
}

Instruction* OXiGenPass::getInstrFromOperand(Value* value, std::string opcodeName){
        
    if(Instruction* instr = dyn_cast<Instruction>(value))
        if(instr->getOpcodeName() == opcodeName)
            return instr;
    return nullptr;
}

DFGNode* OXiGenPass::shortcutSoreGetelementPtr(DFGWriteNode* storeNode){
        
        Instruction* storeInstr = (Instruction*) storeNode->getValue();
        DFGNode* startingNode = new DFGNode(storeInstr->getOperand(0));
        
        storeNode->linkPredecessor(startingNode);
        return startingNode;
    }

bool OXiGenPass::hasSextOnIndvar(Instruction* instr,Loop* loop){
        
    for(Value* operand : instr->operands()){
        
        if(Instruction* childInstr = dyn_cast<Instruction>(operand)){
            if(childInstr->getOperand(0) == loop->getCanonicalInductionVariable() &&
                childInstr->getOpcodeName() == std::string("sext"))
                return true;
        }
    }
    return false;
}
         
bool OXiGenPass::directlyUses(Value *userValue, Value* targetValue){
    
    if(Instruction* instr = dyn_cast<Instruction>(userValue))
        for(Use &operand : instr->operands()){

            if(operand.get() == targetValue){
                return true;
            }

            if(Instruction* instrAsOperand = dyn_cast<Instruction>(operand.get()))
                if(instrAsOperand != nullptr and
                    instrAsOperand->getOpcodeName()== std::string("sext")){
                    
                    //propagate as direct use if the use is mediated by a 
                    //'sext' instruction
                    return directlyUses(instrAsOperand,targetValue);
            }
        }
    return false;
}

bool OXiGenPass::isStored(Value* value){

    for(User* user : value->users()){
        if(Instruction* userAsInstr = dyn_cast<Instruction>(user)) 
            if(userAsInstr->getOpcodeName() == std::string("store") &&
                user->getOperand(1) == value)
                return true;
    }

    return false;
}