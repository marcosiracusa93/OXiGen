#ifndef PROCESSING_SCHEDULER_H
#define PROCESSING_SCHEDULER_H

#include <vector>
#include <string>

#include "llvm-c/Core.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/Value.h"

namespace oxigen{
    
    class FunctionAnalysisResult;
    struct IOStreams;
    class AnalysisManager;
    class StreamsAnalyzer;
    class DFGConstructor;
    class DFGLinker;
    class DFG;
    class SubloopHandler;
    class DFGTranslator;
    class ProcessingComponent;
    
	class ProcessingScheduler{
        
        protected:
        
            std::vector<ProcessingComponent*> scheduledComponents;
			
        public:
        
            FunctionAnalysisResult* analysisResult;
			std::vector<IOStreams*> ioStreams; 
			DFG* dataflowGraph;
			std::string kernelCode;
        
            void schedule(ProcessingComponent* processingComponent);
			void executeNextComponent();
            void executeComponentsQueue();
            
			virtual void execute(AnalysisManager* analysisManager);
			virtual void execute(StreamsAnalyzer* streamsAnalyzer);
			virtual void execute(DFGConstructor* dfgConstructor);
            virtual void execute(DFGLinker* dfgLinker);
			virtual void execute(SubloopHandler* subloopHandler);
			virtual void execute(DFGTranslator* dfgTranslator);
            
            FunctionAnalysisResult* getAnalysisResult(){ return analysisResult; }
            std::vector<IOStreams*> getIOStreams() { return ioStreams; }
            DFG* getDFG(){ return dataflowGraph; }
            std::string getKernelCode(){ return kernelCode; }
            
	};
	
	class DefaultScheduler : public ProcessingScheduler{
    private:
        
        std::string functionName;
        llvm::Function* F;
        llvm::ScalarEvolution* SE;        
        llvm::LoopInfo* LI;
        
		public:
			DefaultScheduler(std::string functionName, llvm::Function* F,
                                llvm::ScalarEvolution* SE, llvm::LoopInfo* LI);
                                
            void execute(AnalysisManager* analysisManager);
            void execute(StreamsAnalyzer* streamsAnalyzer);
            void execute(DFGConstructor* dfgConstructor);
            void execute(DFGLinker* dfgLinker);
            void execute(DFGTranslator* dfgTranslator);
            
	};
	
} // End OXiGen namespace

#endif