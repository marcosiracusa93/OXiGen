
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

using namespace boost;
using namespace llvm;

static std::string functionName = "gravitational_force";

ScalarEvolution const* SE;
LoopInfo* LI;

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
    
    //module = (Module*)modPtr.get();
    
    return modPtr;
}

int preprocessModule(std::unique_ptr<Module> const &modPtr){
    
    Module* module = (Module*)modPtr.get();

    legacy::FunctionPassManager* functionPassManager = new legacy::FunctionPassManager(module);
    
    ScalarEvolutionWrapperPass* scevPassRef = new ScalarEvolutionWrapperPass();
    LoopInfoWrapperPass* loopInfoPassRef = new LoopInfoWrapperPass();

    //The pass manager is used to run the preliminary LLVM passes on the .ll file,
    //and the OXiGen custom pass
    
    functionPassManager->add(createPromoteMemoryToRegisterPass());          // -mem2reg
    functionPassManager->add(loopInfoPassRef);                              // -loops
    functionPassManager->add(scevPassRef);                                  // -scalar-evolution
    
    functionPassManager->run(*module->getFunction(StringRef(functionName)));
    ScalarEvolution const &se = scevPassRef->getSE();
    
    

    SE = &se;
    LI = &(loopInfoPassRef->getLoopInfo());
    
    return 1;
}


int constructDFGFromModule(){
    
    std::unique_ptr<Module> modPtr = acquireModule();
    
    //Function* F = module->getFunction(StringRef(functionName));
    
   /*for( BasicBlock &BB : F.getBasicBlockList())
        for( Instruction &instr : BB.getInstList()){
            if(instr)
        }*/
            
    return 0;
    
}

TEST_CASE("Execution", "[constructDFG]"){
    
    std::unique_ptr<Module> modPtr;
    
    modPtr = acquireModule();
    
    REQUIRE( modPtr != nullptr );
    REQUIRE( preprocessModule(modPtr) != -1 );
    REQUIRE( SE != nullptr); 
    REQUIRE( LI != nullptr);
    
    Module* module = (Module*)modPtr.get();
    module->dump();
    
    
}