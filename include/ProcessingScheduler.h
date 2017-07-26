#ifndef PROCESSING_SCHEDULER_H
#define PROCESSING_SCHEDULER_H

#include <vector>
#include <string>

#include "llvm-c/Core.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Value.h"

namespace oxigen{
    
    class FunctionAnalysisResult;
    struct IOStreams;
    class AnalysisManager;
    class StreamsAnalyzer;
    class DFGConstructor;
    class DFG;
    class SubloopHandler;
    class DFGTranslator;
    
    class ProcessingComponent;
	
	class DefaultScheduler{
		public:
			DefaultScheduler();
	};
	
	class ProcessingScheduler{
        
        private:
        
			std::vector<ProcessingComponent*> scheduledComponents;
			FunctionAnalysisResult* analysisResult;
			IOStreams* ioStreams; 
			DFG* dataflowGraph;
			std::string kernelCode;
			
		public:
			ProcessingScheduler();
			void schedule(ProcessingComponent &processingComponent);
			void executeNextComponent();
			void execute(AnalysisManager &analysisManager);
			void execute(StreamsAnalyzer &streamAnalyzer);
			void execute(DFGConstructor &DFGConstructor);
			void execute(SubloopHandler &subloopHandler);
			void execute(DFGTranslator &DFGTranslator);
            
	};	
    
    class ProcessingComponent{
        public:
            void visit(ProcessingScheduler* scheduler){
                llvm::errs() << "Generic visit\n";
            }
    };
	
} // End OXiGen namespace

#endif