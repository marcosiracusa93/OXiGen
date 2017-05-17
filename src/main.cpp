/**
 * Main class for the project.
 * @author Francesco Peverelli, Marco Siracusa
 */
 
#include <iostream>
#include <utility>
#include <memory>

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm-c/Core.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/AsmParser/Parser.h"

using namespace std;
using namespace llvm;

//Directory used to access .ll files to process
const string RESOURCES_DIR; 
//Directory used to store the processed files
const string OUTPUT_DIR;

Module* extractModuleFromFile(const string fileName){

    static LLVMContext context;
    SMDiagnostic error;

    auto parsedModuleCont = parseAssemblyFile(fileName,error,context);

    Module* parsedModule = parsedModuleCont.get();
    
    return parsedModule;
        
    }

int main(int argc, char**argv) {
    
    //set directory to look for .ll files
    //set file to process. Must be a .ll file containing a llvm module
    const string fileName = argv[1];
    
    Module* module = NULL;
    
    try{
        
    }catch(const exception &e){
        
    }
    
    //get a llvm module from the specified file
    module = extractModuleFromFile(fileName);


  return 0;
}