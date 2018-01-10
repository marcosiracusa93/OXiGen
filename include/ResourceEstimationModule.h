
#ifndef OXIGEN_RESOURCEESTIMATIONMODULE_H
#define OXIGEN_RESOURCEESTIMATIONMODULE_H

#include "DFGConstructor.h"
#include "LoopReplicationManager.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen {

    typedef std::pair<unsigned,int> InstrDescriptor;
    typedef std::map<InstrDescriptor,int> OperationsUseMap;
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
        Ncdf = -13
    };

    class OperationCount{

    private:

        OperationsUseMap operationsMap;

    public:

        OperationCount(DFG* dfg,LoopDependencyGraph* dependencyGraph,llvm::Function* F);

        OperationsUseMap getOperationsUseMap();
        void printOperationsCount();

    private:

        void countOperationsInNodeVector(std::vector<DFGNode*> nodes,
                                         LoopDependencyGraph* dependencyGraph,
                                         llvm::Function* F, int multiplier = 1);

        void countOperationsForLoop(DFGLoopNode* loopNode,LoopDependencyGraph* dependencyGraph,
                                    llvm::Function* F,int currentMultiplier = 1);

    };

    class ResourceEstimator : public ProcessingComponent{

    private:

        llvm::Function* F;

    public:

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
