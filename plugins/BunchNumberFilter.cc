#ifndef HcalTupleMaker_BunchNumberFilter_h
#define HcalTupleMaker_BunchNumberFilter_h

#include "HCALPFG/HcalTupleMaker/interface/HcalTupleFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Common/interface/EventBase.h"

#include "/afs/cern.ch/user/y/yuanc/jsoncpp/dist/jsoncpp.cpp"
#include "/afs/cern.ch/user/y/yuanc/jsoncpp/dist/json/json.h"
#include "/afs/cern.ch/user/y/yuanc/jsoncpp/dist/json/json-forwards.h"

#include <fstream>
#include <iostream> 
#include <string>
class BunchNumberFilter : public HcalTupleFilter {
  public:
      explicit BunchNumberFilter(const edm::ParameterSet&);
      ~BunchNumberFilter();

  private:    
      virtual void compute(edm::Event&, const edm::EventSetup&) override;
      //virtual void getCustomParameter(const edm::ParameterSet&) override;

      std::vector< unsigned int > selectedBXs;
      std::string bunch_crossing;
      

};

BunchNumberFilter::BunchNumberFilter(const edm::ParameterSet& iConfig) : HcalTupleFilter(iConfig) {
  
  reverse_ = iConfig.getParameter < bool > ("reverseDecision");
  //selectedBXs = iConfig.getUntrackedParameter < std::vector < unsigned int > > ("selectedBXs");
  bunch_crossing = iConfig.getUntrackedParameter < std::string > ("bunch_crossing");

};

BunchNumberFilter::~BunchNumberFilter(){};

void BunchNumberFilter::compute(edm::Event& iEvent, const edm::EventSetup&){

  Json::Reader reader;
  Json::Value root;

  std::ifstream in(bunch_crossing, std::ifstream::in);
  if( !in.is_open() ){
    std::cout << "Error opening file\t" << bunch_crossing;
    return;
  }
  if( !reader.parse(in,root) )
  {
    std::cout << "Error reading file\t" << bunch_crossing;
    return;
  }
  reader.parse(in,root);

  edm::EventBase const & eventbase = iEvent;
  int bx = (unsigned int)eventbase.bunchCrossing();
  int run = (unsigned int)eventbase.id().run();
  result_ = false;
  std::vector< unsigned int>::iterator it;
  //if (std::find( selectedBXs.begin() , selectedBXs.end() , bx ) != selectedBXs.end() ) {
  //  result_ = true;
  //};

  if( !root[std::to_string(run)].empty() ){
    for(unsigned int i=0;i<root[std::to_string(run)].size();i++ ){
      if(  bx == root[std::to_string(run)][i].asInt() ){
        result_ = true;
        break;
      }
    }
  }

};

DEFINE_FWK_MODULE( BunchNumberFilter );

#endif
