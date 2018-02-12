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
#include <llvm/Transforms/Utils/CodeExtractor.h>
#include <llvm/IR/Dominators.h>

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"

using namespace llvm;

namespace oxigen{
    /**
     * @class OXiGenPass
     * @author Francesco Peverelli, Marco Siracusa 
     * @file OXiGenPass.h
     * @brief OXiGen custom pass. Processes the llvm IR to produce a MaxJ Kernel.
     */
    class OXiGenPass : public FunctionPass{
    
        char ID = 0;
        int v_factor = 0;
        std::string functionName;   //name of the analyzed function
        std::string fileName;
        
    public:
        
        /**
         * @brief Constructor for the class. Initializes the functionName parameter. 
         * @param functionName - the name of the function which the pass needs to process. The name
         * to specify here is the name of the original function in the C implementation, which is
         * preserved by LLVM during the IR generation.
         */
        OXiGenPass(std::string functionName,std::string fileName,int v_factor = 0);
        
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
    
    };
    
    /**
     * @brief wrapper function to create a @{OXiGenPass}
     * @param functionName - the name of the function which the pass needs to process. The name
     * to specify here is the name of the original function in the C implementation, which is
     * preserved by LLVM during the IR generation
     * @return the @{OXiGenPass} object used to run the pass on a LLVM function
     */
    OXiGenPass* createOXiGenWrapperPass(std::string functionName,std::string fileName,int v_factor = 0);
}

#endif