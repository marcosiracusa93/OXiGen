
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "boost/graph/adjacency_list.hpp"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm-c/Core.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/SourceMgr.h"
#include "llvm/AsmParser/Parser.h"

int stubTestFunction(){ return 1; }

TEST_CASE("StreamAnalysysTests", "[isStoredTest]"){
    REQUIRE( stubTestFunction() == 1 );

}