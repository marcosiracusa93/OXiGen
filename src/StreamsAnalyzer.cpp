
#include "StreamsAnalyzer.h"
#include <set>

using namespace oxigen;

//StreamsAnalyzer methods implementation

IOStreams* StreamsAnalyzer::getExactIndvarIOStreams(llvm::Function* F, llvm::Loop* L){

    llvm::errs() << "Checking for IO streams dependences... \n";
    
    std::vector<llvm::Value*> inputStreams;
    std::vector<llvm::Value*> outputStreams;
    
    //iterate basic blocks of the loop body
    for(llvm::BasicBlock *BB : L->blocks()){
        if(BB != L->getHeader() &&
            BB != L->getLoopLatch()){
            
            //for each getelementptr, check if uses an IO stream
            for(llvm::Instruction &instr : BB->getInstList()){
                if(instr.getOpcodeName() == std::string("getelementptr"))
                    if(directlyUses(&instr,L->getCanonicalInductionVariable())){
                        
                        //if the base pointer used by the getelementptr is stored, it is considered an output stream
                        for(llvm::Argument &arg : F->args()){
                            if(&arg == instr.getOperand(0) && isStored(&instr)){
                                outputStreams.push_back(instr.getOperand(0));
                            }
                        }
                        //if the element pointed by the getelementptr is present in the function arguments
                        //it is considered an input stream
                        for(llvm::Argument &arg : F->args()){
                            instr.getOperand(0)->dump();
                            if(&arg == instr.getOperand(0)){
                                inputStreams.push_back(instr.getOperand(0));
                            }
                        }
                    }       
            }
        }
    }
    
    std::set<llvm::Value*> uniqueOuts(outputStreams.begin(),outputStreams.end());
    outputStreams.assign(uniqueOuts.begin(),uniqueOuts.end());
    
    return new IOStreams(inputStreams,outputStreams);
}

bool StreamsAnalyzer::directlyUses(llvm::Value *userValue, llvm::Value* targetValue){
    
    if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(userValue))
        for(llvm::Use &operand : instr->operands()){

            if(operand.get() == targetValue){
                return true;
            }

            if(llvm::Instruction* instrAsOperand = llvm::dyn_cast<llvm::Instruction>(operand.get()))
                if(instrAsOperand != nullptr and
                    instrAsOperand->isCast()){
                    
                    return directlyUses(instrAsOperand,targetValue);
            }
        }
    return false;
}

bool StreamsAnalyzer::isStored(llvm::Value* value){

    for(llvm::User* user : value->users()){
        if(llvm::Instruction* userAsInstr = llvm::dyn_cast<llvm::Instruction>(user)) 
            if(userAsInstr->getOpcodeName() == std::string("store") &&
                user->getOperand(1) == value){
                return true;
                }
    }

    return false;
}