#ifndef PROCESSING_SCHEDULER_H
#define PROCESSING_SCHEDULER_H

#include "llvm-c/Core.h"

namespace oxigen{
	
	class ProcessComponents{
	};
	
	class DefaultScheduler{
		public:
			DefaultScheduler();
	};
		
	class ProcessingScheduler{
		private:
			std::vector<ProcessComponent&> scheduledComponents;
			AnalysisResult analysisResult;
			IOStreams* ioStreams; 
			DFG* dataflowGraph;
			std::string kernelCode;
			
		public:
			ProcessingScheduler();
			schedule(ProcessComponent &processComponent);
			executeNextComponent();
			execute(AnalysisManager &analysisManager);
			execute(StreamAnalyzer &streamAnalyzer);
			execute(DFGConstructor &DFGConstructor);
			execute(SubloopHandler &subloopHandler);
			execute(DFGTranslator &DFGTranslator);
	};	
	
} // End OXiGen namespace
#endif