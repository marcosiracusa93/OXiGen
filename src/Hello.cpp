

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct Hello : public ModulePass {
  static char ID;
  Hello() : ModulePass(ID) {}

  bool runOnModule(Module &F) override {
    errs() << "Hello: ";
    return false;
  }
}; // end of struct Hello
}  // end of anonymous namespace

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);


