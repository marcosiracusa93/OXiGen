#ifndef STREMS_ANALYZER_H
#define STREMS_ANALYZER_H

#include "llvm-c/Core.h"
#include "llvm/IR/Function.h"

namespace oxigen{
	
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

	/**
	* @class StreamsAnalyzer
	* @author 
	* @date 26/07/17
	* @file StreamsAnalyzer.h
	* @brief 
	*/
	class StreamsAnalyzer{

	public:

		IOStreams getExactIndvarIOStreams(llvm::Function &F, llvm::Loop &L){
			//TODO: implement this stub class
		}
    
		IOStreams getLinearIndvarIOStreams(llvm::Function &F, llvm::Loop &L){
			//TODO: implement this stub class
		}

		IOStreams getNonLinearIndvarIOStreasms(llvm::Function &F, llvm::Loop &L){
			//TODO: implement this stub class
		}
		
		IOStreams getNoIndvarIOStreams(llvm::Function &F, llvm::Loop &L){
			//TODO: implement this stub class
		}
	};

} // End OXiGen namespace

#endif