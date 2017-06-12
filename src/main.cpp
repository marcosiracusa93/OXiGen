/**
 * Main class for the project.
 * @author Francesco Peverelli, Marco Siracusa
 */
 
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <list>
#include <algorithm>

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm-c/Core.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/Dominators.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace{
    
    struct IOStreams{
    
    private:
        
        std::vector<Value*> inputStreams;
        std::vector<Value*> outputStreams;
        
    public:
    
        IOStreams(std::vector<Value*> inStr, std::vector<Value*> outStr) {
            
            this->inputStreams = inStr;
            this->outputStreams = outStr;
        }
        
        std::vector<Value*> getInputStreams(){
            return this->inputStreams;
        }
        
        std::vector<Value*> getOutputStreams(){
            return this->outputStreams;
        }
    
    };
    
    class DFGNode{
    
    private:
        Value* node;
        std::vector<DFGNode*> predecessors;
        DFGNode* successor;
        
    public:
        DFGNode(Value* value){
            this->node = value;
        } 
        
        Value* getValue(){ return node; }

        std::vector<DFGNode*> getPredecessors(){ return predecessors; }
        
        DFGNode* getSuccessor(){ return successor; }
        
        void linkPredecessor(DFGNode* pred){
            predecessors.push_back(pred);
            pred->setSuccessor(this);
        }
        
        void setSuccessor(DFGNode* succ){ successor = succ; }
        
        void printNode(){
            
            errs() << "Node \n";
            node->dump();
            errs() << "\nPredecessors\n";
            
            for(DFGNode* predecessor : predecessors){
                predecessor->getValue()->dump();
            }
        }
        
    };
    
    class DFGWriteNode : public DFGNode {
    
    private:
        
        Value* writingStream;
        
    public:
        
        DFGWriteNode(Value* value, IOStreams* loopStreams) : DFGNode(value) {
            
            for(Value* stream : loopStreams->getOutputStreams()){
                if(Instruction* instr = dyn_cast<Instruction>(value))
                    if(instr->getOperand(1) == stream){

                        writingStream = stream;
                        errs() << "WriteStream found\n";
                    }   
            }
        }
        
        Value* getWritingStream(){ return writingStream; }
    };
    
    class DFGReadNode : public DFGNode {
    
    private:
        
        Value* sourceStream;
        
    public:
        
        DFGReadNode(Value* value, IOStreams* loopStreams) : DFGNode(value) {
            
            for(Value* stream : loopStreams->getInputStreams()){
                if(Instruction* instr = dyn_cast<Instruction>(value))
                    if(instr->getOperand(1) == stream){
                        
                        sourceStream = stream;
                        errs() << "SourceStream found\n";
                    }
            }
        }
        
        Value* getReadingStream(){ return sourceStream; }
    };
        
    class DFG{
    
    private:
        DFGNode* endNode;
        
    public:
        DFG(DFGNode* initNode){ this->endNode = initNode; }
        
        DFGNode* getEndNode(){ return endNode; }
        
        void printDFG(DFGNode* startingNode){
            
            startingNode->printNode();
         
            for(DFGNode* pred : startingNode->getPredecessors())
                printDFG(pred);
        }
        
        void printDFG(){
            
            endNode->printNode();
         
            for(DFGNode* pred : endNode->getPredecessors())
                printDFG(pred);
        }
        
        };

    class TestPass : public FunctionPass{
    
    static char ID;
    ScalarEvolution* SE;
    LoopInfo* LI;
        
    public:
        TestPass() : FunctionPass(ID){}
        
        bool runOnFunction(Function &F){
                
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
        
        void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesAll();
            AU.addRequiredTransitive<LoopInfoWrapperPass>();
            AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
        }
        
    private:
    
        ///Processes a loop which has a canonical induction variable
        void indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F){
            
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
        IOStreams* getIOStreamDependences(Loop* topLevelLoop, Function &F){
            
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
        
        std::vector<DFG*> computeIOStreamBasedDFG(Loop* topLevelLoop,Function &F,IOStreams* IOs){
            
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
        
        DFG* computeDFGFromBase(DFGNode* baseNode){
                
            DFG* graph = new DFG(baseNode);
            
            return graph;
        }
        
        ///Checks if 'dependentValue' uses 'targetValue' directly
        ///At present, uses through 'sext' instructions are considered direct 
        bool directlyUses(Value *dependentValue, Value* targetValue){
            
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
        bool isStored(Value* value){

            for(User* user : value->users()){
                if(Instruction* userAsInstr = dyn_cast<Instruction>(user)) 
                    if(userAsInstr->getOpcodeName() == std::string("store") &&
                        user->getOperand(1) == value)
                        return true;
            }

            return false;
        }
    };
    
    char TestPass::ID = 0;
    
    TestPass* createTestWrapperPass(){
        return new TestPass();
        }
}

//Directory used to access .ll files to process
std::string RESOURCES_DIR; 
//Directory used to store the processed files
std::string OUTPUT_DIR;

/**
 * @brief Entry point of the program. Two arguments must be passed. 
 * @param argc 
 * @param argv [1]: name of a .ll file, [2]: directory where [1] is located
 * @return 0 on success, -1 on failure
 */
int main(int argc, char**argv) {
	    
    static LLVMContext context;         	// LLVMContext variable
    SMDiagnostic error;                 	// error message
    Module* module;                     	// module to process
    
    StringRef filePathRef;              	// StringRef for the file to process
    std::string fileName;               	// file to process, must be a .ll file containing a llvm module
    std::string filePath;               	// full path for the file to process
    
    ::RESOURCES_DIR = argv[2];          	// set directory to look for .ll files
    fileName = argv[1];                 	// set name of the file to process
    
    filePath = ::RESOURCES_DIR + fileName; 	// set full path
    filePathRef = filePath;                	// set a StringRef for the full path
    
    try{
        //try to open the file to process
        std::fstream file;
        file.open(filePath);
        file.close();
        
    }catch(const std::exception &e){
        std::cout << "Failed to open " + filePath;
        return -1;
    }
    
    //parse a llvm::Module from the .ll file 
    auto modPtr = parseAssemblyFile(filePathRef,error,context);
    
    if(modPtr == NULL){
        std::cout << "Null pointer returned from parsing, abort\n" << filePath << std::endl;
        return -1;
    }
    
    module = (Module*)modPtr.get();

    legacy::FunctionPassManager* functionPassManager = new legacy::FunctionPassManager(module);
    
    ScalarEvolutionWrapperPass* scevPassRef = new ScalarEvolutionWrapperPass();
    LoopInfoWrapperPass* loopInfoPassRef = new LoopInfoWrapperPass();
	
	functionPassManager->add(createBasicAAWrapperPass());			// -basicaa
	functionPassManager->add(createAAResultsWrapperPass());			// -aa
	functionPassManager->add(createPromoteMemoryToRegisterPass());	// -mem2reg
    functionPassManager->add(loopInfoPassRef);                       // -loops
	functionPassManager->add(scevPassRef);			                // -scalar-evolution
	functionPassManager->add(createTestWrapperPass());
	functionPassManager->run(*module->getFunction(StringRef("loop")));
	
    return 0;
}