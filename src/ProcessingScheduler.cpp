
#include "ProcessingScheduler.h"
#include "AnalysisManager.h"
#include "DFGConstructor.h"
#include "DFGTranslator.h"
#include "StreamsAnalyzer.h"

using namespace oxigen;

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
    
    AnalysisManager* am = new AnalysisManager();
    StreamsAnalyzer* sa = new StreamsAnalyzer();
    DFGConstructor* dfgc = new DFGConstructor();
    DFGTranslator* dfgt = new DFGTranslator();
    
    schedule(dfgt);
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

void ProcessingScheduler::execute(DFGTranslator* dfgTranslator){
    llvm::errs() << "DFGTranslator executing\n";
}

void DefaultScheduler::execute(AnalysisManager* analysisManager){
    
    analysisResult = analysisManager->analyzeFunction(F, SE, LI);
    
}

void DefaultScheduler::execute(StreamsAnalyzer* streamsAnalyzer){
    
    int infoIndex = 0;

    for(llvm::Loop* loop : *LI){
        
        LoopAnalysisResult* loopInfo = analysisResult->getLoopInfo(infoIndex);
        infoIndex++;
        
        IndVarAccess accessType = loopInfo->getAccessType();
        
        IOStreams* IOs;
        
        switch(accessType){
            case(IndVarAccess::Exact) :
                IOs = streamsAnalyzer->getExactIndvarIOStreams(F,loop);
                break;
            case(IndVarAccess::Linear):
                IOs = streamsAnalyzer->getLinearIndvarIOStreams(F,SE,loop,loopInfo);
                break;
            case(IndVarAccess::NonLinear):
                IOs = streamsAnalyzer->getNonLinearIndvarIOStreasms(F,loop);
                break;
            case(IndVarAccess::Undefined):
                IOs = streamsAnalyzer->getNoIndvarIOStreams(F,loop);
                break;
            default:
                break;
        }
        
        ioStreams.push_back(IOs);
        
    }
    
    for(IOStreams* IOs : ioStreams){
        std::vector<llvm::Value*> ins = IOs->getInputStreams();
        std::vector<llvm::Value*> outs = IOs->getOutputStreams();
        
        llvm::errs() << "Ins\n";
        for(llvm::Value* v : ins)
            v->dump();
        llvm::errs() << "Outs\n";
        for(llvm::Value* v : outs)
            v->dump();
    }
}

void DefaultScheduler::execute(DFGConstructor* dfgConstructor){
    
    int loopIndex = 0;
    std::vector<DFG*> dfgs;
    
    for(llvm::Loop* loop : *LI){
        std::vector<DFG*> graphs = dfgConstructor->computeIOStreamBasedDFG(
                                                     loop,F,ioStreams.at(loopIndex));

        dfgs.insert(dfgs.end(), graphs.begin(), graphs.end());
        loopIndex++;
    }

    if(dfgs.size() > 1){
        std::vector<DFG*> revDfgs(dfgs.size());
        std::reverse_copy(std::begin(dfgs),std::end(dfgs),std::begin(revDfgs));
        schedule(new DFGLinker(revDfgs));
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

void DefaultScheduler::execute(DFGTranslator* dfgTranslator){
    
    dfgTranslator->printDFGAsKernel(DefaultScheduler::dataflowGraph,functionName+"Kernel",functionName); 
}