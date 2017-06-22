/** --------------------- OXiGenPass.h ---------------------------- //
 * 
 * This file contains the declaration of the OXiGenPass class.
 * 
 * OXiGen pass is a llvm::FunctionPass which generates a translation
 * of the function as a .maxj kernel suitable to be compiled through
 * the MaxCompiler toolchain
 * 
 * @author Francesco Peverelli, Marco Siracusa
 */

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
     * @class OXiGenPass
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
         * @brief Constructor for the class. Initializes the functionName parameter. 
         * @param functionName - the name of the function which the pass needs to process. The name
         * to specify here is the name of the original function in the C implementation, which is
         * preserved by LLVM during the IR generation.
         */
        OXiGenPass(std::string functionName);
        
        /**
         * @brief methods which processes the llvm function to produce the MaxJ code
         * @param F an llvm::Function to be processed
         * @return false - the function is not modified 
         */
        bool runOnFunction(Function &F) override;
        
        /**
         * @brief specifies the required llvm passes for this pass. The required llvm
         * passes are: llvm::LoopInfoWrapperPass and llvm::ScalarEvolutionWrapperPass
         * @param AU - see llvm::FunctionPass documentation
         */
        void getAnalysisUsage(AnalysisUsage &AU) const override;
        
    private:
    
        /**
         * @brief processes a loop which has a canonical induction variable. Uses the
         * results of the llvm -scalar-evolution pass to check whether the loop has a
         * taken back trip count, and checks whether the loop contains any subloops.
         * Depending on the conditions met, this method processes the llvm::Function
         * and produces a MaxJ kernel implementation.
         * 
         * @param topLevelLoop - one of the outermost loops in the fuction
         * @param F - the llvm::Function to be processed
         */
        void indVarBasedLoopProcessing(Loop* topLevelLoop, Function &F);
        
        /**
         * @brief Returns a utils::IOStream object which contains the llvm::Value objects
         *        representing the input and output streams for the DFG.
         *        If the llvm::Value is stored, it is classified as output stream,
         *        if it appears in the function arguments, it is classified as input stream
         * 
         * @param topLevelLoop - one of the outermost loops in the fuction
         * @param F - the llvm::Function to be processed
         * @return returns a pointer to a IOStreams object containing the values of the streams 
         *         used in the loop 
         */
        utils::IOStreams* getIOStreamDependences(Loop* topLevelLoop, Function &F);
        
        /**
         * @brief Takes a llvm::Loop, its parent llvm::Function and a utils::IOStreams object
         *        to create a vector of DataFlow Graphs with an output stream as their base
         * 
         * @param topLevelLoop - one of the outermost loops in the fuction
         * @param F - the llvm::Function to be processed
         * @param IOs - the IOStream object containing the llvm::Value(s) considered input and
         *        output streams for the function
         * @return a std::vector<DFG*> containing all the DFGs which end with a store linked to an
         *         output stream
         */
        std::vector<DFG*> computeIOStreamBasedDFG(Loop* topLevelLoop,Function &F,utils::IOStreams* IOs);

        /**
         * @brief Uses a base node to construct a DFG using the LLVM user/uses infrastructure.
         *        The function calls itself again on each DFGNode it adds to the graph
         * 
         * @param node - the DFGNode acting as the parent node for this instance of the
         *        function call
         * @param loop - loop containing the processed instructions
         * @param IOs - the IOStream object containing the llvm::Value(s) considered input and
         *        output streams for the function
         */
        void populateDFG(DFGNode* node,Loop* loop, utils::IOStreams* IOs);
        
        /**
         * @brief Wrapper function used to initialize a new DFG object, which
         *        is then popuated through the oxigen::populateDFG() function
         * 
         * @param baseNode - the base node of the DFG object 
         * @param loop - loop containing the processed instructions
         * @param IOs - the IOStream object containing the llvm::Value(s) considered input and
         *        output streams for the function
         * @return a pointer to a DFG object, representing a populated DFG
         */
        DFG* computeDFGFromBase(DFGWriteNode* baseNode, Loop* loop, utils::IOStreams* IOs);
        
        /**
         * @brief Utiity function used to get an llvm::Instruction pointer from
         *        a llvm::Value, given its supposed opcode name as a string
         * 
         * @param value - the llvm::Value which will be returned as an instruction
         * @param opcodeName - a std::string representing the opcode in llvm of an
         *        instruction
         * @return if the llvm::Value passed as a parameter was a llvm::Instruction
         *         and its opcode corresponds to the std::string passed as a parameter,
         *         a llvm::Instruction pointer to the llvm::Value passed as a parameter
         *         is returned. In any other case, a null pointer is returned
         */
        Instruction* getInstrFromOperand(Value* value, std::string opcodeName);
        
        /**
         * @brief Utility function used to bypass a getelementptr instruction
         *        before a store (seen as a DFGWriteNode in a DFG). 
         *        The DFGWriteNode is linked to the predecessor of the 
         *        getelementptr instruction. WARNING: no checks are performed
         *        regarding the identity of the instructions contained in the
         *        DFGNodes. This function should only be used when there is a 
         *        store preceded by a getelementptr in the llvm IR
         * 
         * @param storeNode - a DFGWriteNode containing a store instruction
         * @return the DFGNode preceding the getelementptr instruction
         */
        DFGNode* shortcutSoreGetelementPtr(DFGWriteNode* storeNode);
        
        /**
         * @brief Checks whether the instruction passed as a parameter has
         *        as argument a llvm::Instuction corresponding to a 'sext'
         *        operation used on the loop's canonical induction variable
         * 
         * @param instr - the instruction on which the check is performed
         * @param loop - the loop which has the canonical induction variable
         *        over which the check is performed
         * @return true if the check is successful, false otherwise
         */
        bool hasSextOnIndvar(Instruction* instr,Loop* loop);
        
        /**
         * @brief Checks whether the first llvm::Value uses the second
         *        llvm::Value as an operand. The first llvm::Value is 
         *        cast as a llvm::Instruction to perform the check.
         *        This check has nothing to do with the user/uses
         *        LLVM infrastructure
         * 
         * @param userValue - value which supposedly uses the target value
         * @param targetValue - the value which is supposedly used as operand
         * @return true if the use relation is verified, false otherwise
         */
        bool directlyUses(Value *userValue, Value* targetValue);
        
        /**
         * @brief Checks whether the llvm::Value is used by a store llvm::Instruction
         * @param value - value on which the check is performed
         * @return true if the llvm::Value is used by a store llvm::Instruction,
         *         false otherwise
         */
        bool isStored(Value* value);
    };
    
    /**
     * @brief wrapper function to create a @{OXiGenPass}
     * @param functionName - the name of the function which the pass needs to process. The name
     * to specify here is the name of the original function in the C implementation, which is
     * preserved by LLVM during the IR generation
     * @return the @{OXiGenPass} object used to run the pass on a LLVM function
     */
    OXiGenPass* createOXiGenWrapperPass(std::string functionName);
}

#endif