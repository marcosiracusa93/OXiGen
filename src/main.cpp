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

int main(int argc, char**argv) {
    
    static LLVMContext context;         //LLVMContext variable
    SMDiagnostic error;                 //error message
    Module* module;                     //module to process
    StringRef filePathRef;              //StringRef for the file to process
    
    ::RESOURCES_DIR = argv[2];          //set directory to look for .ll files
    const string fileName = argv[1];    //set file to process. Must be a .ll file containing a llvm module
    
    const string filePath = ::RESOURCES_DIR + fileName;
    filePathRef = filePath;
    
    try{
        //try to open the file to process
        fstream file;
        file.open(filePath);
        file.close();
        
    }catch(const exception &e){
        cout << "Failed to open " + filePath;
        return -1;
    }
    
    module = (Module*)parseAssemblyFile(filePathRef,error,context).get();

    module->dump();
    
    return 0;
}