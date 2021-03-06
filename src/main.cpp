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

#include "llvm/Support/SourceMgr.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/AssemblyAnnotationWriter.h"
#include "llvm/IR/Dominators.h"

#include "OXiGenPass.h"
#include "OxigenGenVectorizedPass.h"
#include "OxigenVectorizationPass.h"
#include "OxigenVectorizationUnroll.h"

#include "AnalysisManager.h"
#include "DFGConstructor.h"

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

    char in;
    int v_factor = 0;
    std::cout << "Apply vectorization for kernel?(y/n)\n";
    std::cin >> in;

    module = (Module*)modPtr.get();

    legacy::FunctionPassManager* functionPassManager = new legacy::FunctionPassManager(module);

    ScalarEvolutionWrapperPass* scevPassRef = new ScalarEvolutionWrapperPass();
    LoopInfoWrapperPass* loopInfoPassRef = new LoopInfoWrapperPass();

    if(in == 'y') {
        //The pass manager is used to run the preliminary LLVM passes on the .ll file,
        //and the OXiGen custom pass

        std::cout << "Select vectorization factor\n";
        std::cin >> v_factor;

        functionPassManager->add(createPromoteMemoryToRegisterPass());          // -mem2reg
        functionPassManager->add(loopInfoPassRef);                              // -loops
        functionPassManager->add(scevPassRef);                                  // -scalar-evolution

        //run for generation of the vectorized function in the module
        functionPassManager->add(
                oxigen::createOxigenGenVectorizedPass(v_factor));     // creates the vectorized function signature
        functionPassManager->run(*module->getFunction(StringRef(functionName)));

        functionPassManager = new legacy::FunctionPassManager(module);

        //repeat analysis for the vectorized function
        functionPassManager->add(loopInfoPassRef);
        functionPassManager->add(scevPassRef);
        functionPassManager->add(oxigen::createOxigenVectorizationPass(v_factor));     // run function vectorization

        functionName = "vectorized_" + functionName;
        functionPassManager->run(*module->getFunction(StringRef(functionName)));

        functionPassManager = new legacy::FunctionPassManager(module);
    }

    functionPassManager->add(createPromoteMemoryToRegisterPass());

    functionPassManager->add(loopInfoPassRef);
    functionPassManager->add(scevPassRef);
    functionPassManager->add(createSCEVAAWrapperPass());
    //functionPassManager->add(oxigen::createOxigenVectorizationUnroll());
    functionPassManager->add(oxigen::createOXiGenWrapperPass(functionName,fileName,v_factor));// -OXiGen custom pass
    functionPassManager->run(*module->getFunction(StringRef(functionName)));
    
    return 0;
}