#ifndef DFGTRANSLATOR_H
#define DFGTRANSLATOR_H

#include "DFGConstructor.h"
#include "LoopReplicationManager.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"
#include <fstream>

namespace oxigen{

    enum MaxLoopTranslationMode { JavaLoop = 0, AutoLoop = 1 };

    const std::string GLOBAL_TILING = "global_tiling";

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

        ImportMap oxigenFunctions;
        llvm::ScalarEvolution* SE;
        llvm::Function* F;

        std::string oxigenClassPath = "../resources/MaxJOXiGenFunctions.txt";
        
    public:
    
        static std::vector<std::string> imports;
        static ImportMap libImports;
        static std::string kernelSignature_1;
        static std::string kernelSignature_2;
        static std::string kernelSignatureClosing;

        std::vector<std::string> kernelOptimizations;
        LoopDependencyGraph* dependencyGraph;

        MaxLoopTranslationMode translationMode;

        int FLOAT_MANTISSA = 24;
        int FLOAT_EXP = 8;
        int DOUBLE_MANTISSA = 53;
        int DOUBLE_EXP = 11;
        int currentGlobalDelay;

        std::string globalVariables;
        std::string globalDFEVars;
        std::string nestingTabs;
        std::string loopHeadDeclarations;
        std::string currentLoopIndex;

        std::map<llvm::Value*,std::pair<std::string,std::string>> declaredNestedVectors;
        std::map<DFGLoopNode*,std::string> loopIndexes;

        MaxJInstructionPrinter(llvm::ScalarEvolution* SE,llvm::Function* F){
            this->SE = SE;
            this->F = F;
            this->nestingTabs = "";
            this->currentGlobalDelay = 0;

            std::string oxigenClass;
            std::ifstream file(oxigenClassPath.c_str());
            std::string temp;
            while(std::getline(file, temp)) {
                oxigenClass.append(temp+"\n");
            }

            oxigenFunctions.insert(
                    std::pair<std::string,std::pair<bool,std::string>>(
                            "Ncdf",std::pair<bool,std::string>(false,oxigenClass)));
        }

        ImportMap getOxigenFunctions(){ return oxigenFunctions; }
        
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

        std::string translateAsJavaLoop(DFGLoopNode* loopNode);

        llvm::AllocaInst* getVectorBasePointer(DFGNode* node);

        std::vector<std::string> translateFunctionArguments(llvm::Function* F,std::vector<std::string> funcArgs);

        std::string getFullNameIfConstant(DFGNode* var);
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
            
            void printDFGAsKernel(std::vector<DFG*> dfg,std::vector<LoopDependencyGraph*> dependencyGraph, std::string kernelName, std::string packageName);

            void setKernelOptimizations(std::vector<std::string> kernelOptimizations){
                this->kernelOptimizations = kernelOptimizations;
            }
        protected:
            
            std::vector<DFG*> dfgs;
            std::vector<LoopDependencyGraph*> dependencyGraph;
            std::vector<std::string> kernelOptimizations;
            llvm::ScalarEvolution* SE;
            
        private:
        
            void assignNodeNames();
            
            std::string generateKernelString(std::string kernelName,std::string packageName);

    };
} // End OXiGen namespace

#endif