
#ifndef PROCESSING_COMPONENT_H
#define PROCESSING_COMPONENT_H

#include "ProcessingScheduler.h"

namespace oxigen{
    
    class ProcessingComponent{
        
        public:
        
            virtual void acceptExecutor(ProcessingScheduler* scheduler) = 0;
    };
    
}   // End OXiGen namespace


#endif