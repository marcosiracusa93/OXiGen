#include <iostream>
#include <utility>
#include <memory>

using namespace std;

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm-c/Core.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/AsmParser/Parser.h"

int setResourceDir(const string &resourceDir){
        
    }

using namespace llvm;

int main(int argc, char**argv) {

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