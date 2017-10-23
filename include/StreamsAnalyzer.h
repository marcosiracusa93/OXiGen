#ifndef STREMS_ANALYZER_H
#define STREMS_ANALYZER_H

#include "llvm-c/Core.h"
#include "llvm/IR/Function.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"
#include "AnalysisManager.h"
#include <set>

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
        std::vector<llvm::SCEV*> inputOffsets;
        std::vector<llvm::SCEV*> outputOffsets;
		
	public:


        IOStreams(std::vector<llvm::Value*> inStr,std::vector<llvm::Value*> outStr,
                  std::vector<llvm::SCEV*> inOfs = std::vector<llvm::SCEV*>(), std::vector<llvm::SCEV*> outOfs = std::vector<llvm::SCEV*>()) :
            inputStreams(inStr),
            outputStreams(outStr),
            inputOffsets(inOfs),
            outputOffsets(outOfs) {}
    
		//getter methods for this struct
    
		std::vector<llvm::Value*> getInputStreams(){ return this->inputStreams; }
    
		std::vector<llvm::Value*> getOutputStreams(){ return this->outputStreams; }

        std::vector<llvm::SCEV*> getInputOffsets(){ return this->inputOffsets; }

        std::vector<llvm::SCEV*> getOutputOffsets(){ return this->outputOffsets; }

		std::vector<std::pair<llvm::Value*,llvm::SCEV*>> getUniqueOutPairs(){

			std::pair<llvm::Value*,llvm::SCEV*> valOffsetPair;
			std::set<std::pair<llvm::Value*,llvm::SCEV*>> pairSet;

			for(int i = 0; i < outputStreams.size() && i < outputOffsets.size(); i++){
				valOffsetPair = std::pair(outputStreams.at(i),outputOffsets.at(i));
				pairSet.insert(valOffsetPair);
			}
			std::vector<std::pair<llvm::Value*,llvm::SCEV*>> pairsVector;
			for(std::pair<llvm::Value*,llvm::SCEV*> pair : pairSet){
				pairsVector.push_back(pair);
			}

			return pairsVector;
		}

		std::vector<std::pair<llvm::Value*,llvm::SCEV*>> getUniqueInPairs(){

			std::pair<llvm::Value*,llvm::SCEV*> valOffsetPair;
			std::set<std::pair<llvm::Value*,llvm::SCEV*>> pairSet;

			for(int i = 0; i < inputStreams.size() && i < inputOffsets.size(); i++){
				valOffsetPair = std::pair(inputStreams.at(i),inputOffsets.at(i));
				pairSet.insert(valOffsetPair);
			}
			std::vector<std::pair<llvm::Value*,llvm::SCEV*>> pairsVector;
			for(std::pair<llvm::Value*,llvm::SCEV*> pair : pairSet){
				pairsVector.push_back(pair);
			}

			return pairsVector;
		}
	};

	/**
	* @class StreamsAnalyzer
	* @author 
	* @date 26/07/17
	* @file StreamsAnalyzer.h
	* @brief 
	*/
	class StreamsAnalyzer : public ProcessingComponent{

	public:

        void acceptExecutor(ProcessingScheduler* scheduler){
            scheduler->execute(this);
        }
        
		IOStreams* getExactIndvarIOStreams(llvm::Function* F, llvm::Loop* L);
    
		IOStreams* getConstantIndvarIOStreams(llvm::Function *F, llvm::ScalarEvolution *SE, llvm::Loop *L,
                                              LoopAnalysisResult *loopInfo);

		IOStreams* getNonLinearIndvarIOStreasms(llvm::Function* F, llvm::Loop* L){
			llvm::errs() << "Indvar access type not supported...\n";
            return nullptr;
		}
		
		IOStreams* getNoIndvarIOStreams(llvm::Function* F, llvm::Loop* L){
			llvm::errs() << "Indvar access type not supported...\n";
            return nullptr;
		}
        
    private:
        
        bool directlyUses(llvm::Value *userValue, llvm::Value* targetValue);

        bool isStored(llvm::Value* value);
	};

} // End OXiGen namespace

#endif