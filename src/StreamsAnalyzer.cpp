
#include "StreamsAnalyzer.h"

using namespace oxigen;

//StreamsAnalyzer methods implementation

IOStreams* StreamsAnalyzer::getExactIndvarIOStreams(llvm::Function* F, llvm::Loop* L,llvm::ScalarEvolution *SE){

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
                            if(&arg == instr.getOperand(0)){
                                inputStreams.push_back(instr.getOperand(0));
                            }
                        }
                    }
            }
        }
    }
    
    IOStreams* IOs = new IOStreams(inputStreams,outputStreams,SE);

    IOs->makeOutPairsUnique();

    IOs->printStreams();

    return IOs;
}

IOStreams* StreamsAnalyzer::getConstantIndvarIOStreams(llvm::Function *F, llvm::ScalarEvolution *SE, llvm::Loop *L,
                                                       LoopAnalysisResult *loopInfo) {

    llvm::errs() << "Checking for IO streams dependences... \n";

    llvm::PHINode* indVar = loopInfo->getIndVar();
    llvm::errs() << "PHI: "; indVar->dump();

    std::vector<llvm::Value *> inputStreams;
    std::vector<llvm::Value *> outputStreams;
    std::vector<const llvm::SCEV*> inOffsets;
    std::vector<const llvm::SCEV*> outOffsets;

    //iterate basic blocks of the loop body
    for(llvm::BasicBlock *BB : L->blocks()){
        if(BB != L->getHeader() &&
           BB != L->getLoopLatch()){

            //for each getelementptr, check if uses an IO stream
            for(llvm::Instruction &instr : BB->getInstList()){
                if(llvm::GetElementPtrInst* gep = llvm::dyn_cast<llvm::GetElementPtrInst>(&instr)){

                    //if the base pointer used by the getelementptr is stored, it is considered an output stream
                    for (llvm::Argument &arg : F->args()) {
                        if (&arg == instr.getOperand(0) && isStored(&instr)) {

                            outputStreams.push_back(instr.getOperand(0));

                            if (directlyUses(&instr, indVar)) {
                                outOffsets.push_back(nullptr);
                            } else {

                                //Store offset as llvm::SCEV*
                                llvm::Value* index = *(gep->idx_begin());

                                if(const llvm::SCEVAddRecExpr* scev_index = llvm::dyn_cast<const llvm::SCEVAddRecExpr>(SE->getSCEV(index))){
                                    const llvm::SCEV* scev_offset = scev_index->getStart();
                                    outOffsets.push_back(scev_offset);
                                }else{
                                    llvm::errs() << "Unable to compute offset...";
                                    outOffsets.push_back(nullptr);
                                }
                            }
                        }
                    }
                    //if the element pointed by the getelementptr is present in the function arguments
                    //it is considered an input stream
                    for (llvm::Argument &arg : F->args()) {
                        if (&arg == instr.getOperand(0)) {
                            inputStreams.push_back(instr.getOperand(0));

                            if (directlyUses(&instr, indVar) || isStored(&instr)) {
                                inOffsets.push_back(nullptr);
                            }else{

                                //Store offset as llvm::SCEV*
                                llvm::Value* index = *(gep->idx_begin());

                                if(const llvm::SCEVAddRecExpr* scev_index = llvm::dyn_cast<const llvm::SCEVAddRecExpr>(SE->getSCEV(index))){
                                    const llvm::SCEV* scev_offset = scev_index->getStart();
                                    inOffsets.push_back(scev_offset);
                                }else{
                                    llvm::errs() << "Unable to compute offset...";
                                    outOffsets.push_back(nullptr);
                                }
                            }

                        }
                    }
                }
            }
        }
    }

    IOStreams* IOs = new IOStreams(inputStreams,outputStreams,SE,inOffsets,outOffsets);

    IOs->printStreams();

    return IOs;
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