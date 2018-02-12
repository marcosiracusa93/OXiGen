
#include "ResourceEstimationModule.h"

#include <iostream>
#include <fstream>
#include <utility>
#include <memory>

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
        {"Ncdf",OXiGenFunctions::Ncdf },
        {"fabs",OXiGenFunctions ::Fabs},
        {"fmin",OXiGenFunctions ::Fmin}
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

    if(loopNode != nullptr) {
        loopNode->setOperationsMultiplier(multiplier);
        loopNode->getLoopID();
    }

    std::vector<DFG*> dfgs = loopNode->getIndipendentLoopGraphs();

    for(DFG* dfg : dfgs) {

        DFGNode *endNode = dfg->getEndNode();
        std::vector<DFGNode *> sortedNodes;

        dfg->resetFlags(endNode);

        sortedNodes = dfg->orderNodesWithFunc(F);

        countOperationsInNodeVector(sortedNodes,dependencyGraph,F,multiplier,loopNode);
    }
}

OperationCount::OperationCount(DFG *dfg, LoopDependencyGraph *dependencyGraph,llvm::Function* F,
                               std::string function_name,std::string file_name,
                                int v_factor, int tiling_factor) {

    this->file_name = file_name;
    this->function_name = function_name;
    this->tiling_factor = tiling_factor;
    this->v_factor = v_factor;
    this->outerOperationsMap = new OperationsUseMap();

    std::vector<DFGNode*> orderedNodes = dfg->orderNodesWithFunc(F);

    countOperationsInNodeVector(orderedNodes,dependencyGraph,F);
}

void OperationCount::countOperationsInNodeVector(std::vector<DFGNode*> nodes,
                                                 LoopDependencyGraph* dependencyGraph,
                                                 llvm::Function* F,int multiplier,DFGLoopNode* loopNode) {
    OperationsUseMap* operationsMap;

    if(loopNode == nullptr){
        operationsMap = outerOperationsMap;

    }else if(operationsMaps.count(loopNode)){
        operationsMap = operationsMaps[loopNode];
    }else{
        operationsMaps.insert(std::pair<DFGLoopNode*,OperationsUseMap*>(loopNode,new OperationsUseMap()));
        operationsMap = operationsMaps[loopNode];
    }

    for(DFGNode* n : nodes){

        if(n->getType() == NodeType::LoopNode){

            countOperationsForLoop((DFGLoopNode*)n,dependencyGraph,F,multiplier);

        }
        else if(n->getType() == NodeType::ReadNode || n->getType() == NodeType::OffsetRead ||
                n->getType() == NodeType::WriteNode || n->getType() == NodeType::OffsetWrite){

            llvm::errs() << "Skipping read/write node: ";
            n->getValue()->dump();
        }
        else if(llvm::Instruction* instr = llvm::dyn_cast<llvm::Instruction>(n->getValue())){

            std::vector<bool> opIsConst;
            for(int i = 0; i < instr->getNumOperands(); i++){
                if(llvm::dyn_cast<llvm::Constant>(instr->getOperand(i))){
                    opIsConst.push_back(true);
                }else{
                    opIsConst.push_back(false);
                }
            }

            InstrDescriptor* descriptor =
                    new InstrDescriptor(instr->getOpcode(),instr->getType()->getScalarSizeInBits(),opIsConst);

            llvm::errs() << "CURRENT OP: " << opcodeToStringMap[descriptor->first] << " " << descriptor->second << "\n";
            instr->dump();

            if(descriptor->first == llvm::Instruction::Call){
                std::string functionName = ((llvm::CallInst*)instr)->getCalledFunction()->getName();

                if(nameToLibFuncOpcodeMap.count(functionName))
                    descriptor->second = nameToLibFuncOpcodeMap[functionName];
                else{
                    descriptor->second = OXiGenFunctions::Unknown;
                    llvm::errs() << "F name: " << functionName << "\n";
                }
                llvm::errs() << "added as function\n";
            }

            if(operationsMap->count(descriptor)){
                (*operationsMap)[descriptor] += multiplier;
                llvm::errs() << "added as op, M = " << multiplier << "\n";
            }else{
                if(opcodeToStringMap.count(descriptor->first)){
                    operationsMap->insert(std::pair<InstrDescriptor*,int>(descriptor,multiplier));
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

    std::string fileName = file_name.substr(0,file_name.size()-3);

    if(v_factor){
        function_name.append("_v" + std::to_string(v_factor));
    }
    if(tiling_factor){
        function_name.append("_t" + std::to_string(tiling_factor));
    }

    std::string file_path = "../output/" + fileName + "_" + function_name + "_resources.txt";

    try{
        //try to open the file to process
        std::ofstream file(file_path);

        file << "operations_count_report\n";

        std::vector<std::pair<DFGLoopNode*,OperationsUseMap*>> mapsOrderedVector(operationsMaps.size()+1);
        mapsOrderedVector[0] = std::pair<DFGLoopNode*,OperationsUseMap*>(nullptr,outerOperationsMap);

        for(auto m : operationsMaps){
            mapsOrderedVector[m.first->getLoopID()] = m;
        }
        for(auto operationsMapPair : mapsOrderedVector) {

            OperationsUseMap *operationsMap = operationsMapPair.second;
            std::string loopID;
            int operationsMultiplier;

            if(operationsMapPair.first == nullptr) {
                loopID = "NONE";
                operationsMultiplier = 1;
            }else{
                loopID = std::to_string(operationsMapPair.first->getLoopID());
                operationsMultiplier = operationsMapPair.first->getOperationsMultiplier();
            }

            file << "\n\nLoop_ID: " << loopID << "\n";
            file << "Operations_multiplier: " << operationsMultiplier << "\n\n";

            for (auto operation : *operationsMap) {

                if (!opcodeToStringMap.count(operation.first->first)) {
                    file << "\tOperation name not mapped\n";
                } else {
                    file << "\tOperation_name: " << opcodeToStringMap[operation.first->first] << "\n";
                }

                if (operation.first->second <= 0) {

                    std::string functionName;

                    if (!operation.first->second) {
                        functionName = "unknown";
                    } else {
                        for (auto m_it = nameToLibFuncOpcodeMap.begin(); m_it != nameToLibFuncOpcodeMap.end(); ++m_it) {
                            if (m_it->second == operation.first->second) {
                                functionName = m_it->first;
                                break;
                            }
                        }
                    }
                    file << "\tFunction_name: " << functionName << "\n";

                } else {
                    file << "\tOperation_bitwidth: " << operation.first->second << "\n";
                }

                std::string op_is_const = "\tOperands: ";

                for (bool isConst : operation.first->opIsConstant)
                    if (isConst)
                        op_is_const.append("const ");
                    else
                        op_is_const.append("var ");

                op_is_const.pop_back();
                op_is_const.append("\n");

                file << op_is_const;
                file << "\tUses: " << operation.second << "\n\n";

            }

            file << "loop_end\n";
        }

        file << "report_end\n";
        file.close();

    }catch(const std::exception &e){
        std::cout << "Failed to open " + file_path;
        exit(EXIT_FAILURE);
    }
}

void ResourceEstimator::countOperations(DFG* dfg,LoopDependencyGraph* dependencyGraph) {

    llvm::errs() << "INFO: count operations\n";

    OperationCount* operationCount = new OperationCount(dfg,dependencyGraph,F,
                                                        function_name,file_name,v_factor,tiling_factor);
    operationCount->printOperationsCount();
}