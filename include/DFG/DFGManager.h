/** ----------------------- DFGManager.h ----------------------------- //
 * 
 *  This file contains the declarations of the SequentialNamesManager,
 *  MaxJInstructionPrinter and DFGManager classes.
 *  These classes are used by the OXiGenPass to generate the final maxj
 *  kernel code from a simple_dfg::DFG.
 * 
 *  @author Francesco Peverelli, Marco Siracusa
 */

#ifndef DFGMANAGER_H
#define DFGMANAGER_H 

#include "DFG/Nodes.h"

namespace simple_dfg{
    
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
        std::string getNewName(){
            std::string newName = nextName;
            varNames.push_back(newName);
            nextName = generateNextName();
            return newName;
        }
        
        /**
         * @brief Checks if the std::string passed as a parameters is identical to
         *        one of the variable names currently in use by this manager.
         * @param varName - the string against which the check is performed
         * 
         * @return true if the string is present in the currently used names
         */
        bool isPresent(std::string varName);
            
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
        static OpcodeMap opcodeMap;
        
    public:
    
        static std::vector<std::string> imports;
        static std::string kernelSignature;
        static std::string kernelSignatureClosing;
        
        MaxJInstructionPrinter(){}
        
        /**
         * @param inputs - a std::vector of DFGReadNode pointers, corresponding to
         *        the kernel's input streams.
         * @return a std::string containing the input streams declarations for the
         *         maxj kernel.
         */
        std::string getImputStreamsDeclarations(std::vector<DFGReadNode*> inputs);
        
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
        std::string generateInstructionsString(DFGNode* node);
    };
    
    /**
     * @class DFGManager
     * @author Francesco Peverelli, Marco Siracusa
     * @brief This class uses a SequentialNamesManager and a MaxJInstructionPrinter to
     *        translate a DFG into a std::string representing a maxj kernel.
     *        It is also responsible for collecting and arranging different DFG fragments.
     */
    class DFGManager{
    
    private:
        SequentialNamesManager* namesManager;
        MaxJInstructionPrinter* maxjPrinter;
        
        std::vector<DFG*> DFGs;
        DFG* finalDFG;
        
    public:
    
        /**
         * @brief Constructor for the class. Initalizes the SequentialNamesManager
         *        and MaxJInstructionPrinter, as well as the DFGs vector.
         * @param DFGs - a std::vector of simple_dfg::DFG pointers, representing
         *        different fragments of the DFG of the function.
         */
        DFGManager(std::vector<DFG*> DFGs){ 
            this->DFGs = DFGs;
            namesManager = new SequentialNamesManager();
            maxjPrinter = new MaxJInstructionPrinter();
        }
        
        /**
         * @brief Method used to print the maxj kernel constructed by the class.
         * @param kernelName - the name of the maxj kernel to print
         * @param packageName - the name of the package of the kernel
         */
        void printDFGAsKernel(std::string kernelName, std::string packageName);
        
    private:
    
        /**
         * @brief Private method used to generate the std::string containing
         *        the maxj kernel code, based on the finalDFG attribute of
         *        this manager.
         * @param kernelName - the name of the maxj kernel to print
         * @param packageName - the name of the package of the kernel
         * @return a std::string containing the maxj kernel code
         */
        std::string generateKernelString(std::string kernelName,std::string packageName);
        
        /**
         * @brief Method used to assign unique names to the modes of
         *        the finalDFG of this manager
         */
        void assignNodeNames();
    };
}

#endif