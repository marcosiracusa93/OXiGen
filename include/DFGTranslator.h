#ifndef DFGTRANSLATOR_H
#define DFGTRANSLATOR_H

#include "DFGConstructor.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen{

/**
     * @class SequentialNamesManager
     * @author Francesco Peverelli, Marco Siracusa
     * 
     * @brief This class manages the automatic variable names generation
     *        used in the conversion from the simple_dfg::DFG to the final
     *        maxj code. Contains a std::vector of std::string representing
     *        the names generated so far, and a std::string representing 
     *        the next name to be returned when a new name is requested
     */
    class SequentialNamesManager{
        
    private:
        std::vector<std::string> varNames;
        std::string nextName;
    
    public:
        
        /**
         * @brief Constructor for the class, initializes the nextName
         *        attribute to "a".
         */
       SequentialNamesManager(){ this->nextName = std::string("a"); }
        
        /**
         * @brief This method offers a way to obtain a unique new name from
         *        this manager. Upon calling this method, the nextName 
         *        attribute is returned as the new name, and another name
         *        is generated to replace it. The returned name is also
         *        pushed into the std::vector of names in current use.
         * 
         * @return the new name as a std::string
         */
        std::string getNewName();
        
        /**
         * @brief Checks if the std::string passed as a parameters is identical to
         *        one of the variable names currently in use by this manager.
         * @param varName - the string against which the check is performed
         * 
         * @return true if the string is present in the currently used names
         */
        bool isPresent(std::string varName){
    
            for(std::string var : varNames){
                if(var == varName)
                    return true;
            }
            return false; 
        }
            
    private:
        
        /**
         * @brief Private method used to generate a new unique variable name.
         * 
         * @return the newly generated name as a std::string
         */
        std::string generateNextName();
    };
    
    /**
     * @class MaxJInstructionPrinter
     * @author Francesco Peverelli, Marco Siracusa
     * 
     * @brief This class provides the methods and attributes used to present the
     *        simple_dfg::DFG as a maxj kernel. It contains a mapping of the LLVM
     *        opcodes into the correspondins maxj operations, a set of default
     *        imports for the kernel and a default kernel signature.
     */
    class MaxJInstructionPrinter{
        
    private:
        typedef std::map<std::string,std::string> OpcodeMap;
        typedef std::map<std::string,std::pair<bool,std::string>> ImportMap;
        typedef std::map<int,std::string> CmpPredMap;
        static OpcodeMap opcodeMap;
        static OpcodeMap funcLibMap;
        static CmpPredMap cmpPredMap;
        llvm::ScalarEvolution* SE;
        llvm::Function* F;
        
    public:
    
        static std::vector<std::string> imports;
        static ImportMap libImports;
        static std::string kernelSignature;
        static std::string kernelSignatureClosing;
        std::string nestingTabs;
        std::string loopHeadDeclarations;
        
        MaxJInstructionPrinter(llvm::ScalarEvolution* SE,llvm::Function* F){
            this->SE = SE;
            this->F = F;
            this->nestingTabs = "";
        }
        
        /**
         * @param inputs - a std::vector of DFGReadNode pointers, corresponding to
         *        the kernel's input streams.
         * @return a std::string containing the input streams declarations for the
         *         maxj kernel.
         */
        std::string getInputStreamsDeclarations(std::vector<DFGReadNode*> inputs);
        
        /**
         * @param outputs - a std::vector of DFGWriteNode pointers, corresponding to
         *        the kernel's output streams.
         * @return a std::string containing the output streams declarations for the
         *         maxj kernel.
         */
        std::string getOutputStreamsDeclarations(std::vector<DFGWriteNode*> outputs);
        
        /**
         * @param scalarInputs - a std::vector of DFGNode pointers, corresponding to
         *        the kernel's scalar inputs.
         * @return a std::string containing the scalar inputs declarations for the
         *         maxj kernel.
         */
        std::string getScalarInputsDeclarations(std::vector<DFGNode*> scalarInputs);

        std::string getConstantInputOffsetsDeclarations(std::vector<DFGOffsetReadNode*> offsetReads);

        std::string getConstantOutputOffsetsDeclarations(std::vector<DFGOffsetWriteNode*> offsetWrites);
        
        /**
         * @brief This method traverses the graph from a parent node and
         *        converts all the basic arithmetic operations into
         *        a std::string and concatenates them. The resulting 
         *        string is a series of computations on the DFEVar
         *        of the maxj kernel.
         * @param node - the starting point for the method
         * 
         * @return a std::string containing a series of maxj arithmetic instructions
         */
        std::string generateInstructionsString(std::vector<DFGNode*> sortedNodes);
        
        std::string appendInstruction(DFGNode* node);

        std::string getTmpStoreInstructionString(DFGNode* node);

        std::string translateAsJavaLoop(DFGLoopNode* loopNode);

        void fixAccumulNodeNaming(DFGAccNode *n, DFGLoopNode *loopNode,
                                  SequentialNamesManager* nm,std::string loopPrefix);
    };

    /**
     * @class DFGTranslator
     * @author 
     * @date 26/07/17
     * @file DFGTranslator.h
     * @brief 
     */
    class DFGTranslator : public ProcessingComponent{

        private:

            llvm::Function* F;
        
        public:

            DFGTranslator(llvm::ScalarEvolution* SE,llvm::Function* F){
                this->SE = SE;
                this->F = F;
            }
        
            void acceptExecutor(ProcessingScheduler* scheduler){
                scheduler->execute(this);
            }
            
            void printDFGAsKernel(std::vector<DFG*> dfg, std::string kernelName, std::string packageName);
            
        protected:
            
            std::vector<DFG*> dfgs;
            llvm::ScalarEvolution* SE;
            
        private:
        
            void assignNodeNames();
            
            std::string generateKernelString(std::string kernelName,std::string packageName);
    };
} // End OXiGen namespace

#endif