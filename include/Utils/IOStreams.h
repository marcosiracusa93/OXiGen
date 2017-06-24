/** --------------------- IOStreams.h ---------------------------- //
 * 
 * This file contains the declaration of the IOStreams struct
 */

#ifndef IOSTREAMS_H
#define IOSTREAMS_H

#include "llvm-c/Core.h"
#include "llvm/IR/Function.h"

namespace utils{
    
    /**
     * @class IOStreams
     * @brief This struct contains two std::vector of llvm::Value pointers.
     *        It is used to store the references to the values identifying input
     *        and output streams. It only provides two simple getter methods
     */
    struct IOStreams{
    
    private:
        
        std::vector<llvm::Value*> inputStreams;
        std::vector<llvm::Value*> outputStreams;
        
    public:
        
        IOStreams(std::vector<llvm::Value*> inStr, std::vector<llvm::Value*> outStr) {
            this->inputStreams = inStr;
            this->outputStreams = outStr;
        }
        
        //getter methods for this struct
        
        std::vector<llvm::Value*> getInputStreams(){ return this->inputStreams; }
        
        std::vector<llvm::Value*> getOutputStreams(){ return this->outputStreams; }
    
    };
}

#endif
