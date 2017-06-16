
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"

#include "DFG/Nodes.h"

using namespace llvm;
using namespace SimpleDFG;

namespace OXiGen{
    
    class TestPass : public FunctionPass{
    
    char ID = 0;
    ScalarEvolution* SE;
    LoopInfo* LI;
        
    public:
        TestPass();
        
        bool runOnFunction(Function &F) override;
        
        void getAnalysisUsage(AnalysisUsage &AU) const override;
        
    private:
    
        ///Processes a loop which has a canonical induction variable
        void indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F);
        
        ///Returns an object containing the values of the streams used in the loop
        ///If they appear in the function arguments, they are classified as input streams
        ///If they are stored, they are classified as output streams
        Utils::IOStreams* getIOStreamDependences(Loop* topLevelLoop, Function &F);
        
        ///Given a Loop and a set of IO streams, returns a vector of Dataflow graphs constructed with the
        ///IOStreams as input-output nodes
        std::vector<DFG*> computeIOStreamBasedDFG(Loop* topLevelLoop,Function &F,Utils::IOStreams* IOs);
		
        ///Recursive function to construct a DFG from a base node
		void populateDFG(DFGNode* node,Loop* loop, Utils::IOStreams* IOs);
        
        ///Function called to begin a DFG construction using 'populateDFG'
        DFG* computeDFGFromBase(DFGWriteNode* baseNode, Loop* loop, Utils::IOStreams* IOs);
        
        Instruction* getInstrFromOperand(Value* value, std::string opcodeName);
        
        DFGNode* shortcutSoreGetelementPtr(DFGWriteNode* storeNode);
        
        bool hasSextOnIndvar(Instruction* instr,Loop* loop);
        ///Checks if 'dependentValue' uses 'targetValue' directly
        ///At present, uses through 'sext' instructions are considered direct 
        bool directlyUses(Value *dependentValue, Value* targetValue);
        
        ///Checks wether the value passed is used by a store instruction
        ///TODO: verify/implement recursive behavior
        bool isStored(Value* value);
    };
    
    TestPass* createTestWrapperPass();
}