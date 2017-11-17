
#ifndef OXIGEN_DFGSTREAMSOVERLAPHANDLER_H
#define OXIGEN_DFGSTREAMSOVERLAPHANDLER_H

#include "llvm/Support/raw_ostream.h"
#include "StreamsAnalyzer.h"
#include "AnalysisManager.h"
#include "DFGConstructor.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"

namespace oxigen{

    class DFGStreamsOverlapHandler : public ProcessingComponent{

    protected:

        ProcessingScheduler* scheduler;

    public:

        void acceptExecutor(ProcessingScheduler* scheduler){
            this->scheduler = scheduler;
            scheduler->execute(this);
        }

        void computeFallbackWrites(DFG* dfg);

    private:

        void insertForwardMuxNodes(DFGNode* startingNode);

        DFGNode* getFallbackPredecessor(DFGNode* n);
    };
}

#endif //OXIGEN_DFGSTREAMSOVERLAPHANDLER_H
