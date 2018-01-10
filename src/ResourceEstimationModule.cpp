
#include "ResourceEstimationModule.h"

using namespace oxigen;

NameToLibFuncOpcodeMap nameToLibFuncOpcodeMap = {

        {"ceil",OXiGenFunctions::Ceil },
        {"abs",OXiGenFunctions::Abs },
        {"floor",OXiGenFunctions::Floor },
        {"cos",OXiGenFunctions::Cos },
        {"sin",OXiGenFunctions::Sin },
        {"exp",OXiGenFunctions::Exp },
        {"log",OXiGenFunctions::Log },
        {"log2",OXiGenFunctions::Log2 },
        {"max",OXiGenFunctions::Max },
        {"min",OXiGenFunctions::Min },
        {"pow2",OXiGenFunctions::Pow2 },
        {"sqrt",OXiGenFunctions ::Sqrt},
        {"Ncdf",OXiGenFunctions::Ncdf }
};

OpcodeToStringMap opcodeToStringMap = {

        {llvm::Instruction::BinaryOps::Add,"ADD"},
        {llvm::Instruction::BinaryOps::And,"AND"},
        {llvm::Instruction::BinaryOps::AShr,"ASHR"},
        {llvm::Instruction::BinaryOps::FAdd,"FADD"},
        {llvm::Instruction::BinaryOps::FDiv,"FDIV"},
        {llvm::Instruction::BinaryOps::FMul,"FMUL"},
        {llvm::Instruction::BinaryOps::FRem,"FREM"},
        {llvm::Instruction::BinaryOps::FSub,"FSUB"},
        {llvm::Instruction::BinaryOps::LShr,"LSHR"},
        {llvm::Instruction::BinaryOps::Mul,"MUL"},
        {llvm::Instruction::BinaryOps::Or,"OR"},
        {llvm::Instruction::BinaryOps::SDiv,"DIV"},
        {llvm::Instruction::BinaryOps::Shl,"SHL"},
        {llvm::Instruction::BinaryOps::SRem,"SREM"},
        {llvm::Instruction::BinaryOps::Sub,"SUB"},
        {llvm::Instruction::BinaryOps::UDiv,"DIV"},
        {llvm::Instruction::BinaryOps::URem,"UREM"},
        {llvm::Instruction::BinaryOps::Xor,"XOR"},
        {llvm::Instruction::CastOps::AddrSpaceCast,"ADDR_SPACE_CAST"},
        {llvm::Instruction::CastOps::BitCast,"BITCAST"},
        {llvm::Instruction::CastOps::FPExt,"FPEXT"},
        {llvm::Instruction::CastOps::FPToSI,"FPTOSI"},
        {llvm::Instruction::CastOps::FPToUI,"FPTOUI"},
        {llvm::Instruction::CastOps::FPTrunc,"FPTRUNC"},
        {llvm::Instruction::CastOps::SExt,"SEXT"},
        {llvm::Instruction::CastOps::IntToPtr,"INT_TO_PTR"},
        {llvm::Instruction::CastOps::PtrToInt,"PTR_TO_INT"},
        {llvm::Instruction::CastOps::SIToFP,"SITOFP"},
        {llvm::Instruction::CastOps::Trunc,"TRUNC"},
        {llvm::Instruction::CastOps::UIToFP,"UITOFP"},
        {llvm::Instruction::CastOps::ZExt,"ZEXT"},
        {llvm::Instruction::OtherOps::Call,"CALL"},
        {llvm::Instruction::OtherOps::FCmp,"FCMP"},
        {llvm::Instruction::OtherOps::ICmp,"ICMP"},
        {llvm::Instruction::OtherOps::PHI,"PHI"},
        {llvm::Instruction::OtherOps::Select,"SELECT"},
};

void OperationCount::countOperationsForLoop(DFGLoopNode *loopNode,
                                            LoopDependencyGraph *dependencyGraph,
                                            llvm::Function* F,int currentMultiplier) {

    LoopGraphNode* loopGraphNode = dependencyGraph->getNodeForLoop(loopNode);
    int multiplier;

    if(loopGraphNode != nullptr && loopGraphNode->getTilingFactor()){
        if(loopGraphNode->getLoopType() == LoopType::Accumul){
            multiplier = currentMultiplier*loopNode->getTripCount();
        }else if(loopGraphNode->getLoopType() == LoopType::Expansion){
            multiplier = currentMultiplier*loopGraphNode->getReplication();
        }else{
            multiplier = currentMultiplier*loopNode->getTripCount();
            llvm::errs() << "WARNING: unhandled loop type ";
            loopNode->getValue()->dump();
        }
    }else{
       multiplier = currentMultiplier*loopNode->getTripCount();
    }

    std::vector<DFG*> dfgs = loopNode->getIndipendentLoopGraphs();

    for(DFG* dfg : dfgs) {

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGNode *> sortedNodes;

        dfg->resetFlags(endNode);

        sortedNodes = dfg->orderNodesWithFunc(F);

        countOperationsInNodeVector(sortedNodes,dependencyGraph,F,multiplier);
    }
}

OperationCount::OperationCount(DFG *dfg, LoopDependencyGraph *dependencyGraph,llvm::Function* F) {

    std::vector<DFGNode*> orderedNodes = dfg->orderNodesWithFunc(F);

    countOperationsInNodeVector(orderedNodes,dependencyGraph,F);
}

void OperationCount::countOperationsInNodeVector(std::vector<DFGNode*> nodes,
                                                 LoopDependencyGraph* dependencyGraph,
                                                 llvm::Function* F,int multiplier) {

    for(DFGNode* n : nodes){

        if(n->getType() == NodeType::LoopNode){

            countOperationsForLoop((DFGLoopNode*)n,dependencyGraph,F,multiplier);

        }else if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(n->getValue())){

            InstrDescriptor descriptor = InstrDescriptor(instr->getOpcode(),instr->getType()->getScalarSizeInBits());

            llvm::errs() << "CURRENT OP: " << opcodeToStringMap[descriptor.first] << " " << descriptor.second << "\n";
            instr->dump();

            if(descriptor.first == llvm::Instruction::Call){
                std::string functionName = ((llvm::CallInst*)instr)->getCalledFunction()->getName();

                if(nameToLibFuncOpcodeMap.count(functionName))
                    descriptor.second = nameToLibFuncOpcodeMap[functionName];
                else{
                    descriptor.second = OXiGenFunctions::Unknown;
                }
                llvm::errs() << "added as function\n";
            }

            if(operationsMap.count(descriptor)){
                operationsMap[descriptor] += multiplier;
                llvm::errs() << "added as op, M = " << multiplier << "\n";
            }else{
                if(opcodeToStringMap.count(descriptor.first)){
                    operationsMap.insert(std::pair<InstrDescriptor,int>(descriptor,multiplier));
                    llvm::errs() << "added as new op\n";
                }else{
                    llvm::errs() << "INFO: operations count: unknown operation: ";
                    instr->dump();
                }
            }
        }else{
            llvm::errs() << "INFO: operations count: unhandled node: ";
            n->getValue()->dump();
        }
    }
}

void OperationCount::printOperationsCount() {

    llvm::errs() << "RESULT: operations count report\n\n";

    for(auto operation : operationsMap){

        if(!opcodeToStringMap.count(operation.first.first)){
            llvm::errs() << "\tOperation name not mapped\n";
        }else{
            llvm::errs() << "\tOperation name: " << opcodeToStringMap[operation.first.first] << "\n";
        }

        if(operation.first.second <= 0){

            std::string functionName;

            if(!operation.first.second){
                functionName = "unknown";
            }else{
                for(auto m_it = nameToLibFuncOpcodeMap.begin(); m_it != nameToLibFuncOpcodeMap.end(); ++m_it){
                    if(m_it->second == operation.first.second){
                        functionName = m_it->first;
                        break;
                    }
                }
            }
            llvm::errs() << "\tFunction name: " << functionName << "\n";

        }else{
            llvm::errs() << "\tOperation bitwidth: " << operation.first.second << "\n";
        }

        llvm::errs() << "\tUses: " << operation.second << "\n\n";
    }

    llvm::errs() << "RESULT: report end\n";
}

void ResourceEstimator::countOperations(DFG* dfg,LoopDependencyGraph* dependencyGraph) {

    llvm::errs() << "INFO: count operations\n";

    OperationCount* operationCount = new OperationCount(dfg,dependencyGraph,F);
    operationCount->printOperationsCount();
}