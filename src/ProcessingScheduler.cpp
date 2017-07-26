
#include "ProcessingScheduler.h"
#include "AnalysisManager.h"
#include "DFGConstructor.h"
#include "DFGTranslator.h"
#include "StreamsAnalyzer.h"

using namespace oxigen;

DefaultScheduler::DefaultScheduler(){
    
}

void ProcessingScheduler:: schedule(ProcessingComponent &processingComponent){
    scheduledComponents.push_back(&processingComponent);
}

void ProcessingScheduler::executeNextComponent(){
    (*scheduledComponents.back()).visit(this);
}