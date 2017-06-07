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
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace{

    class TestPass : public FunctionPass{
    
    static char ID;
        
    public:
        TestPass() : FunctionPass(ID){}
        
        bool runOnFunction(Function &F){
                
                std::cout << "Running test pass on a function" << std::endl;
                
                ScalarEvolution SE = getAnalysis<ScalarEvolutionWrapperPass>().getSE();
                
                return true;
        }
        
        void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesAll();
            AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
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
    
    ScalarEvolutionWrapperPass&& scevPass = ScalarEvolutionWrapperPass();
    ScalarEvolutionWrapperPass* scevPassRef = &scevPass;
	
	functionPassManager->add(createBasicAAWrapperPass());			// -basicaa
	functionPassManager->add(createAAResultsWrapperPass());			// -aa
	functionPassManager->add(createPromoteMemoryToRegisterPass());	// -mem2reg
	functionPassManager->add(scevPassRef);			// -scalar-evolution
	functionPassManager->add(createTestWrapperPass());
	functionPassManager->run(*module->getFunction(StringRef("main")));
	
    return 0;
}