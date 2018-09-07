#define HcalPfgStudies_cxx
#include "HcalPfgStudies.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TList.h>
#include <TSystemFile.h>
#include <TCollection.h>
#include <TSystemDirectory.h>
#include <TString.h>


#include <time.h>
int main(int argc, char* argv[])
{

  if (argc < 3)
  {
    std::cerr << "Sorry, what you input is invalid! Please see the instruction below:" << std::endl;
    std::cerr << "The first argument is the path where your root files store, don't include slash in the end" << std::endl;
    std::cerr << "The second argument is the TTree path in your root file, like: directory/tree" << std::endl;
    std::cerr << "The third argument is the number of files you want to run. 0 for all files." << std::endl;
    return -1;
  }
  //clock module to collect time information
  time_t startTime,endTime;
  startTime = time(NULL);
  //Take arguments
  //
  
  std::string file_path = argv[1];
  std::string file_path_d = file_path + "/";
  std::string tree_path = argv[2];
  std::string num_s = argv[3];
  int num_file = std::stoi(num_s);

  std::string file_ext = ".root";

  TSystemDirectory dir(file_path.c_str(),file_path.c_str());
  TList *files = dir.GetListOfFiles();
  if (!files)
  {
    std::cerr << "Error: your path is not legal or no root files exist under the path!" << std::endl;
    return -1;
  }

  std::cout << "Going to the directory: " << file_path << std::endl;

  TSystemFile *file;
  TString fname;
  std::string fname_s;
  TIter next(files);
  
  TChain *ch = new TChain(tree_path.c_str());
  int num=0;
  while ( (file = (TSystemFile*)next()) != NULL )
  {
    fname = file->GetName();
    fname_s = file->GetName();
    if(!file->IsDirectory() && fname.EndsWith(file_ext.c_str()))
    {
      std::string filename = file_path_d + fname_s;

      ch->Add(filename.c_str()); 
      std::cout << "Added the file: " << filename <<std::endl;  

      num++;

      if(num_file != 0 && num >= num_file)
      {
        break;
      }
    }
    else//skip if it is a directory or not root file
    {
      continue;
    }
  }
  delete files;

  std::cout << "Successfully added " << num << " files, now processing..." << std::endl;

  HcalPfgStudies t(ch);
  t.Loop();

  endTime = time(NULL);
  std::cout << "Summary: " << std::endl \
  << "Has successfully run " << num << "file." << std::endl \
  << "Totally used: " << (double)(endTime - startTime)/60.0 << " mins" <<std::endl; 

  return 0;

}
///////////////////////////LOOP FUNCTION STARTS HERE**********************************************************************
void HcalPfgStudies::Loop()
{
//   In a ROOT session, you can do:
//      root> .L HcalPfgStudies.C
//      root> HcalPfgStudies t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  
  time_t currtime = time(NULL);
  tm* p = localtime(&currtime);
  char outputname[100] = "";
  sprintf(outputname,"hcal_histogram-%02d:%02d:%02d.root",p->tm_hour,p->tm_min,p->tm_sec);


  // total number of entries Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nentries = fChain->GetEntries();

  int flag = nentries/100 < 500 ? 0 : 1;
  int processed_events = 0;
  
//  unsigned int secs_min = nentries/12;
//  unsigned int secs_max = nentries/11;

//  std::cout << "The estimation time to run is between: " << secs_min/60.0 << " mins and " << secs_max/60.0 << " mins.-----------------------------" << std::endl;
  
  time_t startTime,endTime;
  startTime = time(NULL);
  // map TS to histogram
  //std::map<int,TH1D*> qie11_adc;
  //std::map<int,TH1D*> qie11_tdc;
  
  std::map<int,TH1D*> qie10_adc;
  std::map<int,TH1D*> qie10_tdc;
  std::map<int,TH1D*> qie10_charge;
  
  std::map<int,TH1D*> hf_tdc_adc;

  // dual anode correlcations - same iEta, iPhi for depths 1,3 and 2,4
  
  // pedestal subtractions?
  
  // charge asymmetry

  // hf pulse shape; charge vs. ts or adc vs. ts -- by iEta and depth
  std::map<std::vector<int>,TH1D*> qie10_charge_pulse_shapes;
  std::map<std::vector<int>,TProfile*> qie10_average_charge_pulse_shapes;
  std::map<std::vector<int>,TProfile*> qie10_average_charge_pulse_shapes_ped_sub;
  
  // charge fraction in iEta vs. iPhi for each depth
  // std::map<int,TProfile2D*> qie10_charge_fraction_TS0;
  std::map<int,TProfile2D*> qie10_charge_fraction_TS2;
  std::map<int,TProfile2D*> qie10_tdc_iphi_vs_ieta; 
  // charge fraction in depth vs. iEta
  // TProfile2D *qie10_charge_fraction_TS0_depth_vs_ieta = new TProfile2D("qie10_charge_fraction_TS0_depth_vs_ieta","",85,-42.5,42.5,4,0.5,4.5);
  TProfile2D *qie10_charge_fraction_TS2_depth_vs_ieta = new TProfile2D("qie10_charge_fraction_TS2_depth_vs_ieta","",85,-42.5,42.5,4,0.5,4.5);
  TProfile2D *qie10_charge_fraction_TS2_depth_vs_ieta_higher_charge_cut = new TProfile2D("qie10_charge_fraction_TS2_depth_vs_ieta_higher_charge_cut","",85,-42.5,42.5,4,0.5,4.5);
  
  // charge fraction vs. ts for each depth
  // std::map<int,TH2D*> qie10_charge_fraction_TS0_vs_ts1;
  std::map<int,TProfile*> qie10_charge_fraction_TS2_vs_ts1;
  
  // charge fraction vs. tdc for each depth
  // std::map<int,TH2D*> qie10_charge_fraction_TS0_vs_tdc;
  std::map<int,TProfile*> qie10_charge_fraction_TS2_vs_tdc;
  std::map<int,TProfile*> qie10_charge_fraction_TS2_vs_tdc_charge_cut;
  
  std::map<int,TH1D*> hf_capId_frequency;
  
  int power = 1;
  
  // capID each TS
  
  // capID for SOI
  
  std::map<std::vector<int>,TH2D*> hf_ieta_tdc_for_depth;
  
  //std::map<std::vector<int>, TH2D*> hf_tdc_adc_for_ieta_depth;
  
  // std::map<std::vector<int>, TH1D*> hf_channel_timing;
  // std::map<std::vector<int>, TH1D*> hf_channel_timing_cut;
  
  TH1D *hf_timing_all_channels_adc_0  =  new TH1D("hf_timing_all_channels_adc_0","",150,0,75);
  TH1D *hf_timing_all_channels_adc_30 =  new TH1D("hf_timing_all_channels_adc_30","",150,0,75);
  TH1D *hf_timing_all_channels_adc_40 =  new TH1D("hf_timing_all_channels_adc_40","",150,0,75);
  
  TH1D *hf_capID_SOI_check = new TH1D("hf_capID_SOI_check","",4,0,4);
  
  // TH2D *depth1 =  new TH2D("depth1","",85,-42.5,42.5,72,0.5,72.5);
  // TH2D *hf_ieta_tdc = new TH2D("hf_ieta_tdc","",85,-42.5,42.5,65,0,65); // Fill(x,y)
  
  // TFile file_out("hcal_histograms.root","RECREATE");
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    //if ( (jentry + 1) % 100 == 0 ) std::cout << "Processing event " << jentry + 1 << "/" << nentries << std::endl;
//    if (jentry+1 == std::pow(2,power)) {
//    std::cout << "Processing event " << jentry+1 << "/" << nentries << std::endl;
//      power++;
//    }

//    for (int index = 1; index < 10; index++)
//    {
//      if ( (jentry+1)*index == nentries )
//    }
    

    float job_percent = (jentry+1)*100/nentries;
    if ( (int)job_percent == 100 )
    {
      std::cout << "***********************************Job complete!************************************************" << std::endl;
    }
    else if ( (flag == 1) && (jentry + 1) % 500 == 0 )//valid when events number is big
    {
      std::cout << "Processing event " << jentry+1 << "/" << nentries << ". Have completed:  " << (int)job_percent << "% of the task..." << std::endl;
//          std::cout << "Test information: QIE10DigiLETDC[0][1]= " << QIE10DigiLETDC->at(0).at(1) << std::endl;
    }
    if( (int)job_percent == power )
    {
      endTime = clock();
      float elapsed = (float)(endTime - startTime)/60.0;
      if ( flag == 0 )
        std::cout << "Processing event " << jentry+1 << "/" << nentries << ". Have completed:  " << (int)job_percent << "% of the task..." << std::endl;
      
      std::cout << "Has elapsed: " << elapsed << " mins. " << "Estimated time remaining is: " << elapsed * (100/job_percent - 1) << " mins----------------------------------------------------" << std::endl;
      power++;
      power %= 100;
    }


//    }
    // Fill 5849
    
    // Fill 5849 isolated bunch
//    if (bx != 3490) continue;
    
    // note: some invalid TDC values observed in runs 297218, 297219, and 297224
//    if (run != 297229 && run != 297228 && run != 297227 && run != 297225 && run != 297224 && run != 297219 && run != 297218 && run != 297215 && run != 297211) continue;
    
    // bad HF DCS bits for these LS
//    if (run == 297219 &&
//	(
//	  (ls >= 81 && ls <= 84) || (ls >= 282 && ls <= 287) || (ls >= 580 && ls <= 584) ||
//	  (ls >= 917 && ls <= 920) || (ls >= 1430 && ls <= 1435) || (ls >= 2005 && ls <= 2009)
//	  )
//     ) continue;
//  if (run == 297224 && ls >= 20 && ls <= 23) continue;
    
    processed_events++;
    
    
    //if (run == 296641 && ls < 4) continue;
    
    //cout << "run " << run << ", ls " << ls << ", evn " << event << ", bx " << bx << ", orbit " << orbit << endl;
    
    /*
      for (int ch = 0; ch < QIE11DigiIEta->size(); ++ch) {
      // cout << "QIE11 channel " << "(" << QIE11DigiIEta->at(ch) << ", " << QIE11DigiIPhi->at(ch) << ", " << QIE11DigiDepth->at(ch) << ")" << endl;
      for (int ts = 0; ts < QIE11DigiCapID->at(ch).size(); ++ts) {
      // cout << "TS" << ts;
      // cout << ": ADC = " << QIE11DigiADC->at(ch).at(ts) << ", TDC = " <<  QIE11DigiTDC->at(ch).at(ts) << endl;
      
      if (qie11_adc.find(ts) == qie11_adc.end())
      qie11_adc[ts] = new TH1D(Form("qie11_ADC_all_channels_ts_%d",ts),"",300,0,300);
      
      if (qie11_tdc.find(ts) == qie11_tdc.end())
      qie11_tdc[ts] = new TH1D(Form("qie11_TDC_all_channels_ts_%d",ts),"",80,0,80);
      
      qie11_adc[ts]->Fill(QIE11DigiADC->at(ch).at(ts));
      qie11_tdc[ts]->Fill(QIE11DigiTDC->at(ch).at(ts));
      
      }
      }
    */
    
    for (unsigned int ch = 0; ch < QIE10DigiIEta->size(); ++ch) {
      //cout << "QIE10 channel " << "(" << QIE10DigiIEta->at(ch) << ", " << QIE10DigiIPhi->at(ch) << ", " << QIE10DigiDepth->at(ch) << ")" << endl;
      
      if (QIE10DigiFC->at(ch).at(0) < 0) QIE10DigiFC->at(ch).at(0) = 0.0;

      double ts2_charge_fraction_num = QIE10DigiFC->at(ch).at(2)-QIE10DigiFC->at(ch).at(0); // TS2
      double ts2_charge_fraction_denom = QIE10DigiFC->at(ch).at(1)-QIE10DigiFC->at(ch).at(0); // TS1
      
      if (ts2_charge_fraction_num < 0.0) ts2_charge_fraction_num = 0.0;
      if (ts2_charge_fraction_denom < 0.0) ts2_charge_fraction_denom = 0.0;

      // TS2/TS1
      double ts2_charge_fraction = (ts2_charge_fraction_denom != 0.0) ? ts2_charge_fraction_num/ts2_charge_fraction_denom : 0.0;
      
      // charge fraction TS0/TS1 (TS1 = SOI). iPhi vs. iEta for each depth.
      // if (qie10_charge_fraction_TS0.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS0.end()) {
      // 	qie10_charge_fraction_TS0[QIE10DigiDepth->at(ch)] = new TProfile2D(Form("qie10_charge_fraction_TS0_depth_%d",QIE10DigiDepth->at(ch)),"",85,-42.5,42.5,72,0.5,72.5);
      // }
      // if (QIE10DigiADC->at(ch).at(0) > 20. && QIE10DigiADC->at(ch).at(1) > 20.)
      // 	qie10_charge_fraction_TS0[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiFC->at(ch).at(0)/QIE10DigiFC->at(ch).at(1));
      
      // charge fraction TS2/TS1 (TS1 = SOI). iPhi vs. iEta for each depth.
      if (qie10_charge_fraction_TS2.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS2.end()) {
	qie10_charge_fraction_TS2[QIE10DigiDepth->at(ch)] = new TProfile2D(Form("qie10_charge_fraction_TS2_depth_%d",QIE10DigiDepth->at(ch)),"",85,-42.5,42.5,72,0.5,72.5);
      }
      // using (QIE10DigiFC->at(ch).at(1) > 90., not ts2_charge_fraction_denom > 90.
      if (QIE10DigiFC->at(ch).at(1) > 90.) qie10_charge_fraction_TS2[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),ts2_charge_fraction);
     
      if (qie10_tdc_iphi_vs_ieta.find(QIE10DigiDepth->at(ch)) == qie10_tdc_iphi_vs_ieta.end())
      {
        qie10_tdc_iphi_vs_ieta[QIE10DigiDepth->at(ch)] = new TProfile2D(Form("qie10_tdc_depth_%d",QIE10DigiDepth->at(ch)),"",85,-42.5,42.5,72,0.5,72.5);
      }
      if (QIE10DigiFC->at(ch).at(1) > 90.) qie10_tdc_iphi_vs_ieta[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiLETDC->at(ch).at(1));
      
      // charge fraction TS0/TS1 in depth vs. iEta
      // if (QIE10DigiADC->at(ch).at(0) > 20. && QIE10DigiADC->at(ch).at(1) > 20.) {
      // qie10_charge_fraction_TS0_depth_vs_ieta->Fill(QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch),QIE10DigiFC->at(ch).at(0)/QIE10DigiFC->at(ch).at(1));
      // cout << "TS0 " << QIE10DigiADC->at(ch).at(0) << " TS1 " << QIE10DigiADC->at(ch).at(1) << " TS2 " << QIE10DigiADC->at(ch).at(2) << endl;
      // cout << "TS0/TS1 " << QIE10DigiFC->at(ch).at(0)/QIE10DigiFC->at(ch).at(1) << endl;
      // }

      // charge fraction TS2/TS1 in depth vs. iEta
      if (QIE10DigiFC->at(ch).at(1) > 90.) qie10_charge_fraction_TS2_depth_vs_ieta->Fill(QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch),ts2_charge_fraction);
      if (QIE10DigiFC->at(ch).at(1) > 200.) qie10_charge_fraction_TS2_depth_vs_ieta_higher_charge_cut->Fill(QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch),ts2_charge_fraction);
      // cout << "TS0 " << QIE10DigiADC->at(ch).at(0) << " TS1 " << QIE10DigiADC->at(ch).at(1) << " TS2 " << QIE10DigiADC->at(ch).at(2) << endl;
      // cout << "TS2/TS1 " << QIE10DigiFC->at(ch).at(2)/QIE10DigiFC->at(ch).at(1) << endl;
      
      
      // charge fraction vs. TS1 charge
      // if (qie10_charge_fraction_TS0_vs_ts1.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS0_vs_ts1.end()) {
      // 	qie10_charge_fraction_TS0_vs_ts1[QIE10DigiDepth->at(ch)] = new TH2D(Form("qie10_charge_fraction_TS0_vs_ts1_depth_%d",QIE10DigiDepth->at(ch)),"",300,0,3000,100,0,1);
      // }
      // if (QIE10DigiADC->at(ch).at(0) > 20. && QIE10DigiADC->at(ch).at(1) > 20.)
      // 	qie10_charge_fraction_TS0_vs_ts1[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiFC->at(ch).at(1),QIE10DigiFC->at(ch).at(0)/QIE10DigiFC->at(ch).at(1));

      if (qie10_charge_fraction_TS2_vs_ts1.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS2_vs_ts1.end()) {
	qie10_charge_fraction_TS2_vs_ts1[QIE10DigiDepth->at(ch)] = new TProfile(Form("qie10_charge_fraction_TS2_vs_ts1_depth_%d",QIE10DigiDepth->at(ch)),"",300,0,3000);
      }
      qie10_charge_fraction_TS2_vs_ts1[QIE10DigiDepth->at(ch)]->Fill(ts2_charge_fraction_denom,ts2_charge_fraction);
	
      // // charge fraction vs. TS1 TDC
      // if (qie10_charge_fraction_TS0_vs_tdc.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS0_vs_tdc.end()) {
      // 	qie10_charge_fraction_TS0_vs_tdc[QIE10DigiDepth->at(ch)] = new TH2D(Form("qie10_charge_fraction_TS0_vs_tdc_depth_%d",QIE10DigiDepth->at(ch)),"",50,0,50,100,0,1);
      // }
      // if (QIE10DigiLETDC->at(ch).at(1) < 60. && QIE10DigiADC->at(ch).at(0) > 20. && QIE10DigiADC->at(ch).at(1) > 20.)
      // 	qie10_charge_fraction_TS0_vs_tdc[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiLETDC->at(ch).at(1),QIE10DigiFC->at(ch).at(0)/QIE10DigiFC->at(ch).at(1));
	
      if (qie10_charge_fraction_TS2_vs_tdc.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS2_vs_tdc.end()) {
	qie10_charge_fraction_TS2_vs_tdc[QIE10DigiDepth->at(ch)] = new TProfile(Form("qie10_charge_fraction_TS2_vs_tdc_depth_%d",QIE10DigiDepth->at(ch)),"",65,0,65);
      }
      // if (QIE10DigiLETDC->at(ch).at(1) < 60.)
      qie10_charge_fraction_TS2_vs_tdc[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiLETDC->at(ch).at(1),ts2_charge_fraction);


      if (qie10_charge_fraction_TS2_vs_tdc_charge_cut.find(QIE10DigiDepth->at(ch)) == qie10_charge_fraction_TS2_vs_tdc_charge_cut.end()) {
	qie10_charge_fraction_TS2_vs_tdc_charge_cut[QIE10DigiDepth->at(ch)] = new TProfile(Form("qie10_charge_fraction_TS2_vs_tdc_depth_%d_charge_cut",QIE10DigiDepth->at(ch)),"",65,0,65);
      }
      if (QIE10DigiFC->at(ch).at(1) > 90.)
	qie10_charge_fraction_TS2_vs_tdc_charge_cut[QIE10DigiDepth->at(ch)]->Fill(QIE10DigiLETDC->at(ch).at(1),ts2_charge_fraction);
      
      
      for (unsigned int ts = 0; ts < QIE10DigiCapID->at(ch).size(); ++ts) {
	//cout << "TS" << ts << endl;
	//cout << ": ADC = " << QIE10DigiADC->at(ch).at(ts) << ", TDC = " <<  QIE10DigiLETDC->at(ch).at(ts) << endl;
	
	double ped_sub_charge = QIE10DigiFC->at(ch).at(ts)-QIE10DigiFC->at(ch).at(0);
	if (ped_sub_charge < 0.0) ped_sub_charge = 0.0;
	
	// ADC pedestal cut
	//if (QIE10DigiADC->at(ch).at(1) < 20.) continue;

	//cout << "TS0 " << QIE10DigiADC->at(ch).at(0) << " TS1 " << QIE10DigiADC->at(ch).at(1) << " TS2 " << QIE10DigiADC->at(ch).at(2) << endl;
	  
	//if (QIE10DigiADC->at(ch).at(0) > 20. && QIE10DigiADC->at(ch).at(1)) cout << "hi" <<endl;
	  
	// ADC all channels each TS
	if (qie10_adc.find(ts) == qie10_adc.end()) {
	  qie10_adc[ts] = new TH1D(Form("qie10_ADC_all_channels_ts_%d",ts),"",300,0,300);
	}
	qie10_adc[ts]->Fill(QIE10DigiADC->at(ch).at(ts));
	  
	// TDC all channels each TS
	if (qie10_tdc.find(ts) == qie10_tdc.end()) {
	  qie10_tdc[ts] = new TH1D(Form("qie10_TDC_all_channels_ts_%d",ts),"",80,0,80);
	}
	qie10_tdc[ts]->Fill(QIE10DigiLETDC->at(ch).at(ts));
	  
	// Charge all channels each TS
	if (qie10_charge.find(ts) == qie10_charge.end()) {
	  qie10_charge[ts] = new TH1D(Form("qie10_charge_all_channels_ts_%d",ts),"",300,0,3000);
	}
	qie10_charge[ts]->Fill(QIE10DigiFC->at(ch).at(ts));
	  
	if (hf_capId_frequency.find(ts) == hf_capId_frequency.end()) {
	  hf_capId_frequency[ts] = new TH1D(Form("hf_capId_frequency_all_channels_ts_%d",ts),"",4,0,4);
	}
	hf_capId_frequency[ts]->Fill(QIE10DigiCapID->at(ch).at(ts));
	  
	// charge pulse shapes for each iEta and depth
	std::vector<int> ieta_depth = {QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch)};
	if (qie10_charge_pulse_shapes.find(ieta_depth) == qie10_charge_pulse_shapes.end()) {
	  qie10_charge_pulse_shapes[ieta_depth] = new TH1D(Form("hf_charge_pulse_shape_ieta_%d_depth_%d",QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch)),"",QIE10DigiCapID->at(ch).size(),0,QIE10DigiCapID->at(ch).size());
	}
	if (QIE10DigiFC->at(ch).at(1) > 90.) qie10_charge_pulse_shapes[ieta_depth]->Fill(ts,ped_sub_charge);
	
	if (qie10_average_charge_pulse_shapes.find(ieta_depth) == qie10_average_charge_pulse_shapes.end()) {
	  qie10_average_charge_pulse_shapes[ieta_depth] = new TProfile(Form("hf_average_charge_pulse_shape_ieta_%d_depth_%d",QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch)),"",QIE10DigiCapID->at(ch).size(),0,QIE10DigiCapID->at(ch).size());
	}
	if (QIE10DigiFC->at(ch).at(1) > 90.) qie10_average_charge_pulse_shapes[ieta_depth]->Fill(ts,QIE10DigiFC->at(ch).at(ts));

	// assume TS0 is only pedestal (may be some charge leakage here however. different capIDs have different ped)
	if (qie10_average_charge_pulse_shapes_ped_sub.find(ieta_depth) == qie10_average_charge_pulse_shapes_ped_sub.end()) {
	  qie10_average_charge_pulse_shapes_ped_sub[ieta_depth] = new TProfile(
	    Form("hf_average_charge_pulse_shape_ped_sub_ieta_%d_depth_%d",QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch)),"",QIE10DigiCapID->at(ch).size(),0,QIE10DigiCapID->at(ch).size()
	    );
	}
	if (QIE10DigiFC->at(ch).at(1) > 90.) qie10_average_charge_pulse_shapes_ped_sub[ieta_depth]->Fill(ts,ped_sub_charge);
	  
	// TDC vs. iEta all channels for each depth and each TS
	std::vector<int> ts_depth = {(int)ts,QIE10DigiDepth->at(ch)};
	if (hf_ieta_tdc_for_depth.find(ts_depth) == hf_ieta_tdc_for_depth.end()) {
	  hf_ieta_tdc_for_depth[ts_depth] = new TH2D(Form("hf_ieta_tdc_depth_%d_ts_%d",QIE10DigiDepth->at(ch),ts),"",85,-42.5,42.5,65,0,65); // Fill(x,y)
	}
	hf_ieta_tdc_for_depth[ts_depth]->Fill(QIE10DigiIEta->at(ch),QIE10DigiLETDC->at(ch).at(ts));
	  
	if (QIE10DigiLETDC->at(ch).at(ts) > 49 && QIE10DigiLETDC->at(ch).at(ts) < 61) {
	  std::cout << "Invalid TDC!" << std::endl;
	  std::cout << "run " << run << ", ls " << ls << ", evn " << event << ", bx " << bx << ", orbit " << orbit << std::endl;
	  std::cout << "QIE10 channel " << "(" << QIE10DigiIEta->at(ch) << ", " << QIE10DigiIPhi->at(ch) << ", " << QIE10DigiDepth->at(ch) << ")" << std::endl;
	  std::cout << "TS" << ts << std::endl;
	  std::cout << "ADC = " << QIE10DigiADC->at(ch).at(ts) << ", TDC = " <<  QIE10DigiLETDC->at(ch).at(ts) << std::endl;
	}
	  
	// SOI
	if (ts == 1) {
	  int capId_check = (QIE10DigiCapID->at(ch).at(ts) - bx) % 4;
	  //cout << "capId " << QIE10DigiCapID->at(ch).at(ts) << ", bx " << bx << ", check " << capId_check << endl;
	  hf_capID_SOI_check->Fill(capId_check);
	}
	  
	// TDC vs. iEta all channels for each iEta, each depth, and each TS
	// std::vector<int> ts_ieta_depth = {ts,QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch)};
	// cout << ts_ieta_depth[0] << ", " << ts_ieta_depth[1] << ", " << ts_ieta_depth[2] << endl;
	// if (hf_tdc_adc_for_ieta_depth.find(ts_ieta_depth) == hf_tdc_adc_for_ieta_depth.end()) {
	// hf_tdc_adc_for_ieta_depth[ts_ieta_depth] = new TH2D(Form("hf_adc_vs_tdc_ieta_%d_depth_%d_ts_%d",QIE10DigiIEta->at(ch),QIE10DigiDepth->at(ch),ts),"",65,0,65,300,0,300); // Fill(x,y)
	// }
	// hf_tdc_adc_for_ieta_depth[ts_ieta_depth]->Fill(QIE10DigiLETDC->at(ch).at(ts),QIE10DigiADC->at(ch).at(ts));
	  
	// HF timing for each channel (all TS)
	// std::vector<int> channel = {QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiDepth->at(ch)};
	// cout << channel[0] << ", " << channel[1] << ", " << channel[2] << endl;
	// if (hf_channel_timing.find(channel) == hf_channel_timing.end()) {
	//   hf_channel_timing[channel] = new TH1D(Form("hf_timing_iEta_%d_iPhi_%d_depth_%d",QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiDepth->at(ch)),"",150,0,75);
	// }
	// if (hf_channel_timing_cut.find(channel) == hf_channel_timing_cut.end()) {
	//   hf_channel_timing_cut[channel] = new TH1D(Form("hf_timing_cut_iEta_%d_iPhi_%d_depth_%d",QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiDepth->at(ch)),"",150,0,75);
	// }
	  
	if (QIE10DigiLETDC->at(ch).at(ts) < 60.) {
	  double timing = QIE10DigiLETDC->at(ch).at(ts) / 2. + 25. * ts;  
	  // hf_channel_timing[channel]->Fill(timing);
	  hf_timing_all_channels_adc_0->Fill(timing);
	  // if (QIE10DigiADC->at(ch).at(ts) > 30.) hf_channel_timing_cut[channel]->Fill(timing);
	  if (QIE10DigiADC->at(ch).at(ts) > 30.) hf_timing_all_channels_adc_30->Fill(timing);
	  if (QIE10DigiADC->at(ch).at(ts) > 40.) hf_timing_all_channels_adc_40->Fill(timing);
	}
      }
    }
    
    if (jentry == nentries-1) {
      // noZS in HF, but ZS in other regions
      std::cout << std::endl;
      std::cout << "Total QIE10 (HF) channels: " << QIE10DigiIEta->size() << ", each with " << QIE10DigiCapID->at(0).size() << " TS" << std::endl;
      std::cout << "\tExpected 3456 channels; missing " << 3456-QIE10DigiIEta->size() << " channels" << std::endl;
      /*
	cout << "Total QIE11 (HEP17) channels: " << QIE11DigiIEta->size() << ", each with " << QIE11DigiCapID->at(0).size() << " TS" << endl;
	cout << "\tExpected 184 channels; missing " << 184-QIE11DigiIEta->size() << " channels" << endl;
	cout << "Total HBHE (no HEP17) channels: " << HBHEDigiIEta->size() << ", each with " << HBHEDigiCapID->at(0).size() << " TS" << endl;
	cout << "\tExpected 5112 channels, missing " << 5112-HBHEDigiIEta->size() << " channels" << endl;
	cout << "Total HO channels: " << HODigiIEta->size() << ", each with " << HODigiCapID->at(0).size() << " TS" << endl;
	cout << "\tExpected 2160 channels, missing " << 2160-HODigiIEta->size() << " channels" << endl;
      */
      std::cout << std::endl;
    }
    
  } // end for loop over nentries

  std::cout << "Processed events: " << processed_events << std::endl;
 
  TFile file_out(outputname,"RECREATE");
//  TFile file_out("hcal_histogram.root","RECREATE");
  
  /*
  for (std::map<int,TH1D*>::iterator it = qie11_adc.begin() ; it != qie11_adc.end(); ++it)
  it->second->Write();
  for (std::map<int,TH1D*>::iterator it = qie11_tdc.begin() ; it != qie11_tdc.end(); ++it)
  it->second->Write();
  */

  
  for (std::map<int,TH1D*>::iterator it = qie10_adc.begin() ; it != qie10_adc.end(); ++it)
    it->second->Write();
  for (std::map<int,TH1D*>::iterator it = qie10_tdc.begin() ; it != qie10_tdc.end(); ++it)
    it->second->Write();

  for (std::map<int,TH1D*>::iterator it = qie10_charge.begin() ; it != qie10_charge.end(); ++it)
    it->second->Write();
  
  for (std::map<int,TH1D*>::iterator it = hf_capId_frequency.begin() ; it != hf_capId_frequency.end(); ++it)
    it->second->Write();

  for (std::map<std::vector<int>,TH1D*>::iterator it = qie10_charge_pulse_shapes.begin() ; it != qie10_charge_pulse_shapes.end(); ++it)
    it->second->Write();
  for (std::map<std::vector<int>,TProfile*>::iterator it = qie10_average_charge_pulse_shapes.begin() ; it != qie10_average_charge_pulse_shapes.end(); ++it)
    it->second->Write();
  for (std::map<std::vector<int>,TProfile*>::iterator it = qie10_average_charge_pulse_shapes_ped_sub.begin() ; it != qie10_average_charge_pulse_shapes_ped_sub.end(); ++it)
    it->second->Write();
  
  for (std::map<std::vector<int>,TH2D*>::iterator it = hf_ieta_tdc_for_depth.begin() ; it != hf_ieta_tdc_for_depth.end(); ++it)
    it->second->Write();

  //for (std::map<int,TProfile2D*>::iterator it = qie10_charge_fraction_TS0.begin() ; it != qie10_charge_fraction_TS0.end(); ++it)
  //it->second->Write();

  for (std::map<int,TProfile2D*>::iterator it = qie10_charge_fraction_TS2.begin() ; it != qie10_charge_fraction_TS2.end(); ++it)
    it->second->Write();

  //qie10_charge_fraction_TS0_depth_vs_ieta->Write();
  qie10_charge_fraction_TS2_depth_vs_ieta->Write();
  qie10_charge_fraction_TS2_depth_vs_ieta_higher_charge_cut->Write();

  //for (std::map<int,TH2D*>::iterator it = qie10_charge_fraction_TS0_vs_tdc.begin() ; it != qie10_charge_fraction_TS0_vs_tdc.end(); ++it)
  //it->second->Write();
  for (std::map<int,TProfile*>::iterator it = qie10_charge_fraction_TS2_vs_tdc.begin() ; it != qie10_charge_fraction_TS2_vs_tdc.end(); ++it)
    it->second->Write();
  for (std::map<int,TProfile*>::iterator it = qie10_charge_fraction_TS2_vs_tdc_charge_cut.begin() ; it != qie10_charge_fraction_TS2_vs_tdc_charge_cut.end(); ++it)
    it->second->Write();

  for (std::map<int,TProfile2D*>::iterator it = qie10_tdc_iphi_vs_ieta.begin() ; it != qie10_tdc_iphi_vs_ieta.end(); ++it)
    it->second->Write();
  
  //for (std::map<int,TH2D*>::iterator it = qie10_charge_fraction_TS0_vs_ts1.begin() ; it != qie10_charge_fraction_TS0_vs_ts1.end(); ++it)
  //it->second->Write();
  for (std::map<int,TProfile*>::iterator it = qie10_charge_fraction_TS2_vs_ts1.begin() ; it != qie10_charge_fraction_TS2_vs_ts1.end(); ++it)
    it->second->Write();
  
  //for (std::map<std::vector<int>,TH2D*>::iterator it = hf_tdc_adc_for_ieta_depth.begin() ; it != hf_tdc_adc_for_ieta_depth.end(); ++it)
  //it->second->Write();
  
  // for (std::map<std::vector<int>,TH1D*>::iterator it = hf_channel_timing.begin() ; it != hf_channel_timing.end(); ++it)
  //   it->second->Write();
  // for (std::map<std::vector<int>,TH1D*>::iterator it = hf_channel_timing_cut.begin() ; it != hf_channel_timing_cut.end(); ++it)
  //   it->second->Write();
  
  hf_timing_all_channels_adc_0->Write();
  hf_timing_all_channels_adc_30->Write();
  hf_timing_all_channels_adc_40->Write();

  hf_capID_SOI_check->Write();
  
//  file_out.ls();
  file_out.Close();
  
  std::cout << "Histograms dumped into: " << outputname << std::endl;
} // end Loop()
