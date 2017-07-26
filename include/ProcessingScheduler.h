#ifndef PROCESSING_SCHEDULER_H
#define PROCESSING_SCHEDULER_H

#include "llvm-c/Core.h"

namespace oxigen{
	
	class DefaultScheduler{
		public:
			DefaultScheduler{}
	};
		
	class ProcessingScheduler{
		private:
			std::vector<ProcessComponent&> scheduledComponents;
	};	
	
} // End OXiGen namespace
#endif