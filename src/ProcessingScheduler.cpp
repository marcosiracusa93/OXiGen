
#include <llvm/Analysis/DependenceAnalysis.h>
#include "ProcessingScheduler.h"
#include "AnalysisManager.h"
#include "DFGConstructor.h"
#include "DFGStreamsOverlapHandler.h"
#include "SubloopHandler.h"
#include "DFGTranslator.h"


using namespace oxigen;

std::vector<DFGNode*> globalNodesList = std::vector<DFGNode*>();

void ProcessingScheduler::schedule(ProcessingComponent* processingComponent){
    scheduledComponents.push_back(processingComponent);
}

DefaultScheduler::DefaultScheduler(std::string functionName, llvm::Function* F,
                                   llvm::ScalarEvolution* SE,
                                   llvm::LoopInfo* LI,
                                   llvm::SCEVAAResult* SEAA){

    this->functionName = functionName;
    this->F = F;
    this->SE = SE;
    this->LI = LI;
    this->SEAA = SEAA;
    this->typeID = SchedulerType::Default;

    AnalysisManager* am = new AnalysisManager();
    StreamsAnalyzer* sa = new StreamsAnalyzer();
    DFGConstructor* dfgc = new DFGConstructor(F);
    DFGStreamsOverlapHandler* ovHandler = new DFGStreamsOverlapHandler();
    SubloopHandler* subhdl = new SubloopHandler();
    DFGTranslator* dfgt = new DFGTranslator(SE,F);

    schedule(dfgt);
    schedule(subhdl);
    schedule(ovHandler);
    schedule(dfgc);
    schedule(sa);
    schedule(am);
}

void ProcessingScheduler::executeNextComponent(){
    (*scheduledComponents.back()).acceptExecutor(this);
    scheduledComponents.pop_back();
}

void ProcessingScheduler::executeComponentsQueue(){
    while(scheduledComponents.size() != 0)
        executeNextComponent();
}

void ProcessingScheduler::execute(AnalysisManager* analysisManager){
    llvm::errs() << "Analysis executing\n";

}

void ProcessingScheduler::execute(StreamsAnalyzer* streamsAnalyzer){
    llvm::errs() << "StreamsAnalyzer executing\n";
}

void ProcessingScheduler::execute(DFGConstructor* dfgConstructor){
    llvm::errs() << "DFGConstructor executing\n";
}

void ProcessingScheduler::execute(DFGLinker* dfgLinker){
    llvm::errs() << "DFGLinker executing\n";
}

void ProcessingScheduler::execute(SubloopHandler* subloopHandler){
    llvm::errs() << "SubloopHandler executing\n";
}

void ProcessingScheduler::execute(DFGStreamsOverlapHandler* overlapHandler){
    llvm::errs() << "DFGStreamsOverlapHandler executing\n";
}

void ProcessingScheduler::execute(DFGTranslator* dfgTranslator){
    llvm::errs() << "DFGTranslator executing\n";
}

void DefaultScheduler::execute(AnalysisManager* analysisManager){

    analysisResult = analysisManager->analyzeFunction(F, SE, LI);

}

void DefaultScheduler::execute(StreamsAnalyzer* streamsAnalyzer){
    llvm::errs() << "\nInitializing streams...\n";

    int infoIndex = 0;

    for(llvm::Loop* loop : *LI){

        LoopAnalysisResult* loopInfo = analysisResult->getLoopInfo(infoIndex);
        infoIndex++;

        IndVarAccess accessType = loopInfo->getAccessType();

        IOStreams* IOs;

        switch(accessType){
            case(IndVarAccess::Exact) :
                IOs = streamsAnalyzer->getExactIndvarIOStreams(F,loop,SE);
                break;
            case(IndVarAccess::Constant):
                IOs = streamsAnalyzer->getConstantIndvarIOStreams(F, SE, loop, loopInfo);
                break;
            case(IndVarAccess::NonLinear):
                IOs = streamsAnalyzer->getNonLinearIndvarIOStreasms(F,loop,SE);
                break;
            case(IndVarAccess::Undefined):
                IOs = streamsAnalyzer->getNoIndvarIOStreams(F,loop,SE);
                break;
            default:
                break;
        }

        ioStreams.push_back(IOs);

    }

}

void DefaultScheduler::execute(DFGConstructor* dfgConstructor){

    int loopIndex = 0;
    std::vector<DFG*> dfgs;
    llvm::BasicBlock* currentBlock = &(*(F->begin()));

    for(llvm::Loop* loop : *LI){

        std::vector<DFG*> loopGraphs;

        std::vector<DFG*> staticGraphs =  dfgConstructor->computeStaticDFG(
                ioStreams.at(loopIndex),SE,LI,F,currentBlock);

        std::vector<DFG*> graphs = dfgConstructor->computeIOStreamBasedDFG(
                loop,ioStreams.at(loopIndex),SE,loopIndex);

        std::vector<DFG*> revStatic(staticGraphs.size());
        std::reverse_copy(std::begin(staticGraphs),std::end(staticGraphs),std::begin(revStatic));

        loopGraphs.insert(loopGraphs.begin(),revStatic.begin(),revStatic.end());
        loopGraphs.insert(loopGraphs.begin(),graphs.begin(),graphs.end());

        currentBlock = loop->getExitBlock();
        loopIndex++;
        dfgs.insert(dfgs.begin(),loopGraphs.begin(),loopGraphs.end());
    }

    std::vector<DFG*> staticGraphs =  dfgConstructor->computeStaticDFG(
            ioStreams.at(loopIndex-1),SE,LI,F,currentBlock);

    std::vector<DFG*> revStatic(staticGraphs.size());
    std::reverse_copy(std::begin(staticGraphs),std::end(staticGraphs),std::begin(revStatic));

    dfgs.insert(dfgs.begin(),revStatic.begin(),revStatic.end());

    if(dfgs.size() > 1){
        std::vector<DFG*> revDfgs(dfgs.size());
        std::reverse_copy(std::begin(dfgs),std::end(dfgs),std::begin(revDfgs));
        schedule(new DFGLinker(revDfgs,F));
        executeNextComponent();

    }else{
        llvm::errs() << "DFG linkage skipped, assumed only one graph...\n";
        DefaultScheduler::dataflowGraph = dfgs;
    }

}

void DefaultScheduler::execute(DFGLinker* dfgl){

    DefaultScheduler::dataflowGraph = dfgl->linkDFG();

    if(dataflowGraph.size() > 1){
        std::vector<DFG*> tmp(dataflowGraph.size());
        std::reverse_copy(std::begin(dataflowGraph),std::end(dataflowGraph),std::begin(tmp));
        dataflowGraph = tmp;
    }
}

void DefaultScheduler::execute(SubloopHandler *subloopHandler) {

    llvm::errs() << "\nINFO: Executing default subloop handler\n";

    for(DFG* dfg : dataflowGraph) {
        dfg->fuseIdenticalNodes();
        llvm::errs() << "INFO: DFG after identical nodes fusion and cleanup:\n";
        dfg->printDFG();
        subloopHandler->extractSubloops(F,SE, LI, dfg);
        llvm::errs() << "INFO: DFG after subloop extraction: \n";
        dfg->printDFG();
    }

}

void DefaultScheduler::execute(DFGStreamsOverlapHandler *overlapHandler) {

    for(DFG* dfg : dataflowGraph){
        dfg->printDFG();
        llvm::errs() << "\nComputing initial r/w offsets for graph with base ";
        dfg->getEndNode()->getValue()->dump();
        overlapHandler->addFinalStoreOffsets(dfg);
        overlapHandler->addInitialReadsOffsets(dfg);

        //llvm::errs() << "\nCOMPUTING GLOBAL DELAY\n";
        //overlapHandler->computeGlobalDelay(dfg);
        //llvm::errs() << "\nOFFSET COMPUTATION TERMINATED\n";
        llvm::errs() << "WARNING: global delay computation temporary suspended\n";
    }


    overlapHandler->setDFGs(dataflowGraph);
    DefaultScheduler::dataflowGraph = overlapHandler->computeFallbackWrites();

    if(dataflowGraph.size() > 1){
        std::vector<DFG*> tmp(dataflowGraph.size());
        std::reverse_copy(std::begin(dataflowGraph),std::end(dataflowGraph),std::begin(tmp));
        dataflowGraph = tmp;
    }
}

void DefaultScheduler::execute(DFGTranslator* dfgTranslator){

    dfgTranslator->printDFGAsKernel(DefaultScheduler::dataflowGraph,functionName+"Kernel",functionName);
}