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
#include "llvm/AsmParser/Parser.h"

using namespace std;
using namespace llvm;

//Directory used to access .ll files to process
string RESOURCES_DIR; 
//Directory used to store the processed files
string OUTPUT_DIR;

Module* extractModuleFromFile(StringRef *filePathRef,LLVMContext &context,SMDiagnostic &error){

    auto parsedModuleCont = parseAssemblyFile(*filePathRef,error,context);

    Module* parsedModule = parsedModuleCont.get();
    
    return parsedModule;
        
    }

int main(int argc, char**argv) {
    
    //set directory to look for .ll files
    ::RESOURCES_DIR = argv[2];
    //set file to process. Must be a .ll file containing a llvm module
    const string fileName = argv[1];
    
    //LLVMContext variable
    static LLVMContext context;
    //error message
    SMDiagnostic error;
    //module to process
    Module* module = NULL;
    
    const string filePath = ::RESOURCES_DIR + fileName;
    
    try{
        //try to open the file to process
        fstream file;
        file.open(filePath);
        file.close();
        
    }catch(const exception &e){
        cout << "Failed to open " + filePath;
        return -1;
    }
    
    StringRef *filePathRef = new StringRef(filePath);
    
    //get a llvm module from the specified file
    module = extractModuleFromFile(filePathRef,context,error);
    
    return 0;
}