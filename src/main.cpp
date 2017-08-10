/** --------------------- main.cpp ---------------------------- //
 *
 * Main class for the OXiGen tool. 
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

#include "llvm/Support/SourceMgr.h"
#include "llvm/AsmParser/Parser.h"

#include "OXiGenPass.h"

#include "AnalysisManager.h"
#include "DFGConstructor.h"
#include "DFGTranslator.h"
#include "ProcessingScheduler.h"
#include "StreamsAnalyzer.h"

using namespace llvm;

//Directory used to access .ll files to process
std::string RESOURCES_DIR; 
//Directory used to store the processed files
std::string OUTPUT_DIR;

/**
 * @brief Entry point of the program. Two arguments must be passed. 
 * @param argc 
 * @param argv [1]: name of a .ll file, argv [2]: directory where [1] is located,
 *        argv [3]: name of the function to process. Must correspond to the name of a
 *        function to translate present in the C implementation in the file from which
 *        the .ll file was generated.
 * @return 0 on success, -1 on failure
 */
int main(int argc, char**argv) {
	    
    static LLVMContext context;             // LLVMContext variable
    SMDiagnostic error;                     // error message
    Module* module;                         // module to process
    
    StringRef filePathRef;                  // StringRef for the file to process
    std::string fileName;                   // file to process, must be a .ll file containing a llvm module
    std::string filePath;                   // full path for the file to process
    std::string functionName;               // name of the function to process
    
    ::RESOURCES_DIR = argv[2];              // set directory to look for .ll files
    fileName = argv[1];                     // set name of the file to process
    functionName = argv[3];                 // set the name of the function to process
    
    filePath = ::RESOURCES_DIR + fileName;  // set full path
    filePathRef = filePath;                 // set a StringRef for the full path 
    
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
    
    //check if llvm::parseAssemblyFile has returned a pointer to a llvm::Module
    if(modPtr == NULL){
        std::cout << "Null pointer returned from parsing, abort\n" << filePath << std::endl;
        return -1;
    }
    
    module = (Module*)modPtr.get();

    legacy::FunctionPassManager* functionPassManager = new legacy::FunctionPassManager(module);
    
    ScalarEvolutionWrapperPass* scevPassRef = new ScalarEvolutionWrapperPass();
    LoopInfoWrapperPass* loopInfoPassRef = new LoopInfoWrapperPass();

    //The pass manager is used to run the preliminary LLVM passes on the .ll file,
    //and the OXiGen custom pass
    
    functionPassManager->add(createPromoteMemoryToRegisterPass());          // -mem2reg
    functionPassManager->add(loopInfoPassRef);                              // -loops
    functionPassManager->add(scevPassRef);                                  // -scalar-evolution
    functionPassManager->add(oxigen::createOXiGenWrapperPass(functionName));// -OXiGen custom pass
    
    //the scheduled passes are run on the specified function
    functionPassManager->run(*module->getFunction(StringRef(functionName)));
    
    return 0;
}