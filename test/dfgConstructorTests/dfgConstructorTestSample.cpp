
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <list>
#include <algorithm>

#include "boost/graph/adjacency_list.hpp"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm-c/Core.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/SourceMgr.h"
#include "llvm/AsmParser/Parser.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Scalar.h"

#include "ProcessingScheduler.h"
#include "DFGConstructor.h"

using namespace boost;
using namespace llvm;

static std::string functionName = "gravitational_force";

legacy::FunctionPassManager* functionPassManager;

class DFGTestPass : public FunctionPass{
    
    char ID = 0;
    std::unique_ptr<oxigen::DFG> const dfg;
    
    
    public:
    
        DFGTestPass() : FunctionPass(ID){}
        
        bool runOnFunction(Function &F) override {
            
            ScalarEvolution* tmpSE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
            LoopInfo* tmpLI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            
            oxigen::DefaultScheduler* scheduler =
                            new oxigen::DefaultScheduler(functionName,&F,tmpSE,tmpLI);
            
            scheduler->executeNextComponent(); //analysis manager
            scheduler->executeNextComponent(); //streams analyzer
            scheduler->executeNextComponent(); //dfg constructor
            
            REQUIRE( scheduler->getDFG() != nullptr);
            
            return false;
        }
        
        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesAll();
            AU.addRequiredTransitive<LoopInfoWrapperPass>();
            AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
        }
    
    };

std::unique_ptr<Module> acquireModule() {
    
    int status = -1;
	    
    static LLVMContext context;             // LLVMContext variable
    SMDiagnostic error;                     // error message
    //Module* module = nullptr;                         // module to process
    
    std::string filePath = "./../../resources/grav.ll";
    StringRef filePathRef = filePath;                  // StringRef for the file to process                // set the name of the function to process

    try{
        //try to open the file to process
        std::fstream file;
        file.open(filePath);
        file.close();
        
    }catch(const std::exception &e){
        std::cout << "Failed to open " + filePath;
        return nullptr;
    }
    
    //parse a llvm::Module from the .ll file 
    auto modPtr = parseAssemblyFile(filePathRef,error,context);
    
    //check if llvm::parseAssemblyFile has returned a pointer to a llvm::Module
    if(modPtr == NULL){
        std::cout << "Null pointer returned from parsing, abort\n" << filePath << std::endl;
        return nullptr;
    }
    
    return modPtr;
}

int preprocessModule(std::unique_ptr<Module> const &modPtr){
    
    Module* module = (Module*)modPtr.get();

    functionPassManager = new legacy::FunctionPassManager(module);
    
    ScalarEvolutionWrapperPass* scevPassRef = new ScalarEvolutionWrapperPass();
    LoopInfoWrapperPass* loopInfoPassRef = new LoopInfoWrapperPass();

    //The pass manager is used to run the preliminary LLVM passes on the .ll file,
    
    functionPassManager->add(createPromoteMemoryToRegisterPass());          // -mem2reg
    functionPassManager->add(loopInfoPassRef);                              // -loops
    functionPassManager->add(scevPassRef);                                  // -scalar-evolution
    
    functionPassManager->run(*module->getFunction(StringRef(functionName)));
    
    return 1;
}

int constructDFG(std::unique_ptr<Module> const &modPtr){
    
    Module* module = (Module*)modPtr.get();

    functionPassManager = new legacy::FunctionPassManager(module);
    
    ScalarEvolutionWrapperPass* scevPassRef = new ScalarEvolutionWrapperPass();
    LoopInfoWrapperPass* loopInfoPassRef = new LoopInfoWrapperPass();
    DFGTestPass* dfgTestRef = new DFGTestPass();

    //The pass manager is used to run the preliminary LLVM passes on the .ll file,
    
    functionPassManager->add(createPromoteMemoryToRegisterPass());          // -mem2reg
    functionPassManager->add(loopInfoPassRef);                              // -loops
    functionPassManager->add(scevPassRef);                                  // -scalar-evolution
    functionPassManager->add(dfgTestRef);
    
    functionPassManager->run(*module->getFunction(StringRef(functionName)));
    
    return 1;
}


TEST_CASE("Execution", "[constructDFG]"){
    
    std::unique_ptr<Module> modPtr;
    
    modPtr = acquireModule();
    
    REQUIRE( modPtr != nullptr );
    REQUIRE( preprocessModule(modPtr) != -1 );
    
    constructDFG(modPtr);
    
}