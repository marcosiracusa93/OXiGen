
#ifndef OXIGEN_RESOURCEESTIMATIONMODULE_H
#define OXIGEN_RESOURCEESTIMATIONMODULE_H

#include "DFGConstructor.h"
#include "LoopReplicationManager.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen {

    struct InstrDescriptor{
        unsigned first;
        int second;
        std::vector<bool> opIsConstant;

        InstrDescriptor(unsigned OP,int b_width,std::vector<bool> opIsConst){
            first = OP;
            second = b_width;
            opIsConstant = opIsConst;
        }
    };

    typedef std::map<InstrDescriptor*,int> OperationsUseMap;
    typedef std::map<unsigned,std::string> OpcodeToStringMap;
    typedef std::map<std::string,int> NameToLibFuncOpcodeMap;

    enum OXiGenFunctions{

        Unknown = 0,
        Ceil = -1,
        Abs = -2,
        Floor = -3,
        Sqrt = -4,
        Log2 = -5,
        Log = -6,
        Sin = -7,
        Cos = -8,
        Pow2 = -9,
        Exp = -10,
        Min = -11,
        Max = -12,
        Ncdf = -13,
        Fabs = -14,
        Fmin = -15
    };

    class OperationCount{

    private:

        std::map<DFGLoopNode*,OperationsUseMap* > operationsMaps;
        OperationsUseMap* outerOperationsMap;
        std::string function_name;
        std::string file_name;
        int v_factor = 0;
        int tiling_factor = 0;

    public:

        OperationCount(DFG* dfg,LoopDependencyGraph* dependencyGraph,llvm::Function* F,
                       std::string function_name,std::string file_name,int v_factor = 0,int tiling_factor = 0);


        void printOperationsCount();

    private:

        void countOperationsInNodeVector(std::vector<DFGNode*> nodes,
                                         LoopDependencyGraph* dependencyGraph,
                                         llvm::Function* F, int multiplier = 1,DFGLoopNode* loopNode = nullptr);

        void countOperationsForLoop(DFGLoopNode* loopNode,LoopDependencyGraph* dependencyGraph,
                                    llvm::Function* F,int currentMultiplier = 1);

    };

    class ResourceEstimator : public ProcessingComponent{

    private:

        llvm::Function* F;

    public:

        std::string function_name;
        std::string file_name;
        int v_factor = 0;
        int tiling_factor = 0;

        ResourceEstimator(llvm::Function* F){
            this->F = F;
        }

        void acceptExecutor(ProcessingScheduler* scheduler){
            scheduler->execute(this);
        }

        void countOperations(DFG* dfg, LoopDependencyGraph* dependencyGraph);
    };
}

#endif //OXIGEN_RESOURCEESTIMATIONMODULE_H
