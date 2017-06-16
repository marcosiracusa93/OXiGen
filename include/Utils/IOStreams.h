#ifndef IOSTREAMS_H
#define IOSTREAMS_H

#include "llvm-c/Core.h"
#include "llvm/IR/Function.h"

namespace Utils{
    
    struct IOStreams{
    
    private:
        
        std::vector<llvm::Value*> inputStreams;
        std::vector<llvm::Value*> outputStreams;
        
    public:
    
        IOStreams(std::vector<llvm::Value*> inStr, std::vector<llvm::Value*> outStr) {
            this->inputStreams = inStr;
            this->outputStreams = outStr;
        }
        
        std::vector<llvm::Value*> getInputStreams(){ return this->inputStreams; }
        
        std::vector<llvm::Value*> getOutputStreams(){ return this->outputStreams; }
    
    };
}

#endif