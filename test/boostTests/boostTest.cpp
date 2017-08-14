
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

using namespace boost;
using namespace llvm;

Module* acquireModule() {
    
    int status = -1;
	    
    static LLVMContext context;             // LLVMContext variable
    SMDiagnostic error;                     // error message
    Module* module = nullptr;                         // module to process
    
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
    
    module = (Module*)modPtr.get();
    
    return module;
}

int constructDFGFromModule(){
    
    Module* module = acquireModule();
    
    Function* F = module->getFunction(StringRef("gravitational_force"));
    
   /*for( BasicBlock &BB : F.getBasicBlockList())
        for( Instruction &instr : BB.getInstList()){
            if(instr)
        }*/
            
    return 0;
    
}

TEST_CASE("Execution", "[constructDFG]"){
    REQUIRE( acquireModule() != nullptr );
}