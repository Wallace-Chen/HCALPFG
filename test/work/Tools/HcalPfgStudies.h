//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 26 03:37:36 2017 by ROOT version 6.08/05
// from TTree tree/
// found on file: root://cmseos.fnal.gov//store/user/abuccill/hcal-analysis/hf_phase_settings_2017/hcal_pfg_MinimumBias_Run2017A-v1_RAW_fill_5698_merged.root
//////////////////////////////////////////////////////////

#ifndef HcalPfgStudies_h
#define HcalPfgStudies_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TProfile.h>
#include <TProfile2D.h>

#include <string>
#include <vector>
#include <iostream>
// Header file for the classes stored in the TTree if any.
//#include "vector"
//#include "vector"
//#include "vector"

class HcalPfgStudies {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   std::vector<std::vector<double> > *QIE10DigiFC;
   std::vector<int>     *QIE10DigiDepth;
   std::vector<int>     *QIE10DigiFlags;
   std::vector<int>     *QIE10DigiIEta;
   std::vector<int>     *QIE10DigiIPhi;
   std::vector<int>     *QIE10DigiLinkError;
   std::vector<int>     *QIE10DigiRawID;
   std::vector<int>     *QIE10DigiSubdet;
   std::vector<std::vector<int> > *QIE10DigiADC;
   std::vector<std::vector<int> > *QIE10DigiCapID;
   std::vector<std::vector<int> > *QIE10DigiLETDC;
   std::vector<std::vector<int> > *QIE10DigiOK;
   std::vector<std::vector<int> > *QIE10DigiSOI;
   std::vector<std::vector<int> > *QIE10DigiTETDC;
   UInt_t          bx;
   UInt_t          event;
   UInt_t          ls;
   UInt_t          orbit;
   UInt_t          run;

   // List of branches
   TBranch        *b_QIE10DigiFC;   //!
   TBranch        *b_QIE10DigiDepth;   //!
   TBranch        *b_QIE10DigiFlags;   //!
   TBranch        *b_QIE10DigiIEta;   //!
   TBranch        *b_QIE10DigiIPhi;   //!
   TBranch        *b_QIE10DigiLinkError;   //!
   TBranch        *b_QIE10DigiRawID;   //!
   TBranch        *b_QIE10DigiSubdet;   //!
   TBranch        *b_QIE10DigiADC;   //!
   TBranch        *b_QIE10DigiCapID;   //!
   TBranch        *b_QIE10DigiLETDC;   //!
   TBranch        *b_QIE10DigiOK;   //!
   TBranch        *b_QIE10DigiSOI;   //!
   TBranch        *b_QIE10DigiTETDC;   //!
   TBranch        *b_bx;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ls;   //!
   TBranch        *b_orbit;   //!
   TBranch        *b_run;   //!

   HcalPfgStudies(TTree *tree=0);
   virtual ~HcalPfgStudies();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HcalPfgStudies_cxx
HcalPfgStudies::HcalPfgStudies(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://cmseos.fnal.gov//store/user/abuccill/hcal-analysis/hf_phase_settings_2017/hcal_pfg_MinimumBias_Run2017A-v1_RAW_fill_5698_merged.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://cmseos.fnal.gov//store/user/abuccill/hcal-analysis/hf_phase_settings_2017/hcal_pfg_MinimumBias_Run2017A-v1_RAW_fill_5698_merged.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("root://cmseos.fnal.gov//store/user/abuccill/hcal-analysis/hf_phase_settings_2017/hcal_pfg_MinimumBias_Run2017A-v1_RAW_fill_5698_merged.root:/hcalTupleTree");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

HcalPfgStudies::~HcalPfgStudies()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HcalPfgStudies::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HcalPfgStudies::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HcalPfgStudies::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   QIE10DigiFC = 0;
   QIE10DigiDepth = 0;
   QIE10DigiFlags = 0;
   QIE10DigiIEta = 0;
   QIE10DigiIPhi = 0;
   QIE10DigiLinkError = 0;
   QIE10DigiRawID = 0;
   QIE10DigiSubdet = 0;
   QIE10DigiADC = 0;
   QIE10DigiCapID = 0;
   QIE10DigiLETDC = 0;
   QIE10DigiOK = 0;
   QIE10DigiSOI = 0;
   QIE10DigiTETDC = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("QIE10DigiFC", &QIE10DigiFC, &b_QIE10DigiFC);
   fChain->SetBranchAddress("QIE10DigiDepth", &QIE10DigiDepth, &b_QIE10DigiDepth);
   fChain->SetBranchAddress("QIE10DigiFlags", &QIE10DigiFlags, &b_QIE10DigiFlags);
   fChain->SetBranchAddress("QIE10DigiIEta", &QIE10DigiIEta, &b_QIE10DigiIEta);
   fChain->SetBranchAddress("QIE10DigiIPhi", &QIE10DigiIPhi, &b_QIE10DigiIPhi);
   fChain->SetBranchAddress("QIE10DigiLinkError", &QIE10DigiLinkError, &b_QIE10DigiLinkError);
   fChain->SetBranchAddress("QIE10DigiRawID", &QIE10DigiRawID, &b_QIE10DigiRawID);
   fChain->SetBranchAddress("QIE10DigiSubdet", &QIE10DigiSubdet, &b_QIE10DigiSubdet);
   fChain->SetBranchAddress("QIE10DigiADC", &QIE10DigiADC, &b_QIE10DigiADC);
   fChain->SetBranchAddress("QIE10DigiCapID", &QIE10DigiCapID, &b_QIE10DigiCapID);
   fChain->SetBranchAddress("QIE10DigiLETDC", &QIE10DigiLETDC, &b_QIE10DigiLETDC);
   fChain->SetBranchAddress("QIE10DigiOK", &QIE10DigiOK, &b_QIE10DigiOK);
   fChain->SetBranchAddress("QIE10DigiSOI", &QIE10DigiSOI, &b_QIE10DigiSOI);
   fChain->SetBranchAddress("QIE10DigiTETDC", &QIE10DigiTETDC, &b_QIE10DigiTETDC);
   fChain->SetBranchAddress("bx", &bx, &b_bx);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ls", &ls, &b_ls);
   fChain->SetBranchAddress("orbit", &orbit, &b_orbit);
   fChain->SetBranchAddress("run", &run, &b_run);
   Notify();
}

Bool_t HcalPfgStudies::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HcalPfgStudies::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HcalPfgStudies::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HcalPfgStudies_cxx
