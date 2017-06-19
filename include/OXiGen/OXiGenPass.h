#ifndef OXIGENPASS_H
#define OXIGENPASS_H

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
using namespace simple_dfg;

namespace oxigen{
    /**
     * @class TestPass
     * @author Francesco Peverelli, Marco Siracusa 
     * @file OXiGenPass.h
     * @brief OXiGen custom pass. Processes the llvm IR to produce a MaxJ Kernel.
     */
    class OXiGenPass : public FunctionPass{
    
    char ID = 0;
    ScalarEvolution* SE;        //result form the scalar evolution analysis pass
    LoopInfo* LI;               //result from the analysis on loops on the function
    std::string functionName;   //name of the analyzed function
        
    public:
        
        /**
         * @brief Construction for the pass 
         * @param functionName the name of the function to process
         */
        OXiGenPass(std::string functionName);
        
        /**
         * @brief methods which processes the llvm function to produce the MaxJ code
         * @param F an llvm::Function to be processed
         * @return false - the function is not modified 
         */
        bool runOnFunction(Function &F) override;
        
        /**
         * @brief specifies the required llvm passes for this pass 
         * @param AU
         */
        void getAnalysisUsage(AnalysisUsage &AU) const override;
        
    private:
    
        /**
         * @brief processes a loop which has a canonical induction variable
         * @param topLevelLoop one of the outermost loops in the fuction
         * @param F the llvm::Function to be processed
         */
        void indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F);
        
        
        ///If they appear in the function arguments, they are classified as input streams
        ///If they are stored, they are classified as output streams
        /**
         * @brief  
         * @param topLevelLoop
         * @param F
         * @return returns a pointer to a IOStreams object containing the values of the streams used in the loop 
         */
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
    
    OXiGenPass* createTestWrapperPass(std::string functionName);
}

#endif