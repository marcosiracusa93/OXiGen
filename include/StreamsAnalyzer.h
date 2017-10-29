#ifndef STREMS_ANALYZER_H
#define STREMS_ANALYZER_H

#include "llvm-c/Core.h"
#include "llvm/IR/Function.h"
#include "ProcessingScheduler.h"
#include "ProcessingComponent.h"
#include "AnalysisManager.h"
#include <set>

namespace oxigen{

    typedef std::pair<llvm::Value*,const llvm::SCEV*> StreamPair;
	
	/**
	* @class IOStreams
	* @brief This struct contains two std::vector of llvm::Value pointers.
	*        It is used to store the references to the values identifying input
	*        and output streams. It only provides two simple getter methods
	*/
	struct IOStreams{

	private:
    
		std::vector<StreamPair> inputStreams;
		std::vector<StreamPair> outputStreams;
        llvm::ScalarEvolution* SE;
		
	public:


        IOStreams(std::vector<llvm::Value*> inStr,std::vector<llvm::Value*> outStr,
                  llvm::ScalarEvolution* SE,
                  std::vector<const llvm::SCEV*> inOfs = std::vector<const llvm::SCEV*>(),
                  std::vector<const llvm::SCEV*> outOfs = std::vector<const llvm::SCEV*>()){

            this->SE = SE;

            if(inOfs.size() == 0){
                for(int i = 0; i < inStr.size(); i++){
                    inOfs.push_back(nullptr);
                }
            }

            if(outOfs.size() == 0){
                for(int i = 0; i < outStr.size(); i++){
                    outOfs.push_back(nullptr);
                }
            }

            inputStreams = std::vector<StreamPair>();

            for(int i = 0; i < inStr.size(); i++){
                StreamPair p = StreamPair(inStr.at(i),inOfs.at(i));
                inputStreams.push_back(p);
            }

            outputStreams = std::vector<StreamPair>();

            for(int i = 0; i < outStr.size(); i++){
                StreamPair p = StreamPair(outStr.at(i),outOfs.at(i));
                outputStreams.push_back(p);
            }
        }
    
		//getter methods for this struct
    
		std::vector<StreamPair> getInputStreams(){ return this->inputStreams; }
    
		std::vector<StreamPair> getOutputStreams(){ return this->outputStreams; }

        StreamPair getInStreamFromGEP(llvm::GetElementPtrInst* gep){

            const llvm::SCEV* idx = SE->getSCEV(*(gep->idx_begin()));

            const llvm::SCEVAddRecExpr* addRec = llvm::dyn_cast<llvm::SCEVAddRecExpr>(idx);

            if(addRec == nullptr){
                llvm::errs() << "Non AddRec index, terminating...";
                exit(EXIT_FAILURE);
            }

            const llvm::SCEV* scev_offset = addRec->getStart();
            llvm::Value* ptr = gep->getPointerOperand();

            for(StreamPair p : inputStreams){
                if(p.first == ptr && p.second == scev_offset )
                    return p;
            }

            return StreamPair(nullptr, nullptr);
        }

        void printStreams(){

            llvm::errs() << "\nIO STREAMS\n";

            llvm::errs() << "Inputs: \n";
            for(StreamPair p : inputStreams){
                llvm::errs() << "\tStream: ";
                p.first->dump();
                llvm::errs() << "\tOffset: ";
                if(p.second != nullptr)
                    p.second->dump();
                else
                    llvm::errs() << " 0\n";
            }

            llvm::errs() << "Outputs: \n";
            for(StreamPair p : outputStreams){
                llvm::errs() << "\tStream: ";
                p.first->dump();
                llvm::errs() << "\tOffset: ";
                if(p.second != nullptr)
                    p.second->dump();
                else
                    llvm::errs() << " 0\n";
            }
        }

		void makeOutPairsUnique(){

            std::set<StreamPair> pairsSet;

			for(StreamPair p : outputStreams){
                pairsSet.insert(p);
            }

            std::vector<StreamPair> uniquePairs = std::vector<StreamPair>();

            for(StreamPair up : pairsSet){
                uniquePairs.push_back(up);
            }

            outputStreams = uniquePairs;

			return;
		}

        void makeInPairsUnique(){

            std::set<StreamPair> pairsSet;

            for(StreamPair p : inputStreams){
                pairsSet.insert(p);
            }

            std::vector<StreamPair> uniquePairs = std::vector<StreamPair>();

            for(StreamPair up : pairsSet){
                uniquePairs.push_back(up);
            }

            inputStreams = uniquePairs;

            return;
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
        
		IOStreams* getExactIndvarIOStreams(llvm::Function* F, llvm::Loop* L,llvm::ScalarEvolution *SE);
    
		IOStreams* getConstantIndvarIOStreams(llvm::Function *F, llvm::ScalarEvolution *SE, llvm::Loop *L,
                                              LoopAnalysisResult *loopInfo);

		IOStreams* getNonLinearIndvarIOStreasms(llvm::Function* F, llvm::Loop* L,llvm::ScalarEvolution *SE){
			llvm::errs() << "Indvar access type not supported...\n";
            return nullptr;
		}
		
		IOStreams* getNoIndvarIOStreams(llvm::Function* F, llvm::Loop* L,llvm::ScalarEvolution *SE){
			llvm::errs() << "Indvar access type not supported...\n";
            return nullptr;
		}
        
    private:
        
        bool directlyUses(llvm::Value *userValue, llvm::Value* targetValue);

        bool isStored(llvm::Value* value);
	};

} // End OXiGen namespace

#endif