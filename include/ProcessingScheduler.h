#ifndef PROCESSING_SCHEDULER_H
#define PROCESSING_SCHEDULER_H

#include <vector>
#include <string>

#include "llvm-c/Core.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/Value.h"

namespace oxigen{

    class DFGNode;
    static  std::vector<DFGNode*> globalNodesList;

	enum SchedulerType { Default = 1, Abstract = 0 };
    
    class FunctionAnalysisResult;
    struct IOStreams;
    class AnalysisManager;
    class StreamsAnalyzer;
    class DFGConstructor;
    class DFGLinker;
    class DFG;
	class LoopDependencyGraph;
    class SubloopHandler;
    class DFGTranslator;
	class DFGStreamsOverlapHandler;
	class LoopReplicationManager;
    class ProcessingComponent;
    
	class ProcessingScheduler{
        
        protected:
        
            std::vector<ProcessingComponent*> scheduledComponents;
			SchedulerType typeID;
			
        public:
        
            FunctionAnalysisResult* analysisResult;
			std::vector<IOStreams*> ioStreams; 
			std::vector<DFG*> dataflowGraph;
			std::vector<LoopDependencyGraph*> dependencyGraph;

			std::vector<std::string> kernelOptimizations;

			std::string kernelCode;
        
            void schedule(ProcessingComponent* processingComponent);
			void executeNextComponent();
            void executeComponentsQueue();
            
			virtual void execute(AnalysisManager* analysisManager);
			virtual void execute(StreamsAnalyzer* streamsAnalyzer);
			virtual void execute(DFGConstructor* dfgConstructor);
            virtual void execute(DFGLinker* dfgLinker);
			virtual void execute(DFGStreamsOverlapHandler* overlapHandler);
			virtual void execute(SubloopHandler* subloopHandler);
			virtual void execute(DFGTranslator* dfgTranslator);
			virtual void execute(LoopReplicationManager* loopReplicationManager);
            
            FunctionAnalysisResult* getAnalysisResult(){ return analysisResult; }
            std::vector<IOStreams*> getIOStreams() { return ioStreams; }
            std::vector<DFG*> getDFG(){ return dataflowGraph; }
            std::string getKernelCode(){ return kernelCode; }
			SchedulerType getType(){ return typeID; }
            
	};
	
	class DefaultScheduler : public ProcessingScheduler{

    protected:
        
        std::string functionName;
        llvm::Function* F;
        llvm::ScalarEvolution* SE;        
        llvm::LoopInfo* LI;
        llvm::SCEVAAResult* SEAA;
        
	public:
		DefaultScheduler(std::string functionName, llvm::Function* F,
												   llvm::ScalarEvolution* SE,
												   llvm::LoopInfo* LI,
												   llvm::SCEVAAResult* SEAA);

		void execute(AnalysisManager* analysisManager);
		void execute(StreamsAnalyzer* streamsAnalyzer);
		void execute(DFGConstructor* dfgConstructor);
		void execute(DFGLinker* dfgLinker);
		void execute(SubloopHandler* subloopHandler);
		void execute(DFGStreamsOverlapHandler* overlapHandler);
		void execute(DFGTranslator* dfgTranslator);
		void execute(LoopReplicationManager* loopReplicationManager);

		llvm::LoopInfo* getLoopInfo(){ return this->LI; }
            
	};


} // End OXiGen namespace

#endif