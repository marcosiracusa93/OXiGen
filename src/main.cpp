/**
 * Main class for the project.
 * @author Francesco Peverelli, Marco Siracusa
 */
 
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>

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
                }
                return true;
        }
        
        void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesAll();
            AU.addRequiredTransitive<LoopInfoWrapperPass>();
            AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
        }
        
    private:
    
        void indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F){
            if(SE->hasLoopInvariantBackedgeTakenCount(topLevelLoop)){
                errs() << "Processing with tbtc\n";  
                
                if(hasIOStreamDependences(topLevelLoop,F))
                    //computeIOStreamBasedDFG(topLevelLoop,F);
                    errs() << "TODO: IO stream dependences check\n";
            }else
                errs() << "No taken back trip count, terminating... \n";
                return;
        }
        
        bool hasIOStreamDependences(Loop* topLevelLoop, Function &F){
            errs() << "Checking for IO streams dependences... \n";
            
            //compute list of possible IO streams
            // 1. fargs -> getelementptr
            // 2. stores <- getelementptr
            //      ==> indvar dependant getelementptr uses
            //          gets stored ? isOutput
            //          is in fargs ? isInput
            /*errs() << "Exit\n";
            topLevelLoop->getExitBlock()->dump();
            errs() << "Header\n";
            topLevelLoop->getHeader()->dump();
            errs() << "Unique Latch\n";
            topLevelLoop->getLoopLatch()->dump();
            errs() << "Preheader\n";
            topLevelLoop->getLoopPreheader()->dump();
            auto args = &(F.getArgumentList());*/
            
            for(BasicBlock *BB : topLevelLoop->blocks())
                    if(BB != topLevelLoop->getHeader() &&
                        BB != topLevelLoop->getLoopLatch()){
                        for(Instruction &instr : BB->getInstList()){
                            instr.dump();
                        }
                    }
                    
            return true;
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
    
    //errs() << "\n--------------------------------------\n\n";
    
    //module->dump();
	
    return 0;
}