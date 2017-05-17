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

int extractModuleFromFile(const string fileName){
        
    }

int main(int argc, char**argv) {
    
    //set directory to look for .ll files
    RESOURCES_DIR = argv[2];
    //set file to process. Must be a .ll file containing a llvm module
    const string fileName = argv[1];
    
    
    extractModuleFromFile(fileName);

    static LLVMContext context;
    Module* module = new Module("top", context);

    IRBuilder<> builder(context);

    module->dump();

    StringRef fileName = "/home/user/Documents/workspace/prova/resources/loop_1.ll";
    SMDiagnostic error;

    auto parsedModuleCont = parseAssemblyFile(fileName,error,context);

    Module* parsedModule = parsedModuleCont.get();

    ((Module*)parsedModule)->dump();


  return 0;
}