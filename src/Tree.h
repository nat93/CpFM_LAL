//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 26 11:58:34 2016 by ROOT version 5.34/36
// from TTree Tree/A Root Tree
// found on file: output.root
//////////////////////////////////////////////////////////

#ifndef Tree_h
#define Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "include/Constants.hh"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <string>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        Amplitude[Constants::nCh][Constants::nPnt];
   Double_t        UnixTime;
   Int_t           EventID;
   Double_t        TDC;
   Double_t        BaseLine[Constants::nCh];
   Double_t        Peak[Constants::nCh];
   Double_t        PeakTime[Constants::nCh];
   Double_t        Charge[Constants::nCh];
   Double_t        RisingTime[Constants::nCh];
   Double_t        FallingTime[Constants::nCh];
   Double_t        PeakNum[Constants::nCh];

   // List of branches
   TBranch        *b_amplitude;   //!
   TBranch        *b_untime;   //!
   TBranch        *b_eventid;   //!
   TBranch        *b_tdc;   //!
   TBranch        *b_baseline;   //!
   TBranch        *b_peak;   //!
   TBranch        *b_peaktime;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_risingtime;   //!
   TBranch        *b_fallingtime;   //!
   TBranch        *b_peaknum;   //!

   Tree(TString nameOfTheFile);
   virtual ~Tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   //Common
   virtual void     VisualisationAllChannels(Int_t nEv);
   virtual void     VisualisationOnlyOneChannel(Int_t nEv,Int_t nChannel);
   virtual void     GetNumEntries(Long64_t &nEntires);
   virtual void     TransformAmplitude(Int_t nCh, Double_t *OutAmpl);
   virtual void     GetMean16(Double_t *InAmpl, Double_t &OutMean, Double_t *OutAmpl);
   virtual void     GetMaxAmpl(Double_t *InAmpl, Double_t &OutAmpl, Double_t &OutTime);
   virtual void     GetMinAmpl(Double_t *InAmpl, Double_t &OutAmpl, Double_t &OutTime);
   virtual void     GetTimeAtLevel(Double_t *InAmpl, Double_t level, Double_t InTime, Double_t &OutTime);
   virtual void     GetWidth(Double_t *InAmpl, Double_t level, Double_t InTime, Double_t &OutWidth);
   virtual void     GetTimeCF(Double_t *InAmpl, Double_t cf, Double_t MinAmpl, Double_t TimeMax, Double_t &OutTime);
   virtual void     GetRiseTime(Double_t *InAmpl, Double_t MaxAmpl, Double_t InTime, Double_t &OutTime);
   virtual void     GetFallTime(Double_t *InAmpl, Double_t MaxAmpl, Double_t InTime, Double_t &OutTime);
   virtual void     GetCharge(Double_t *InAmpl, Double_t InTime, Double_t &Charge);
   virtual void     GetNumPeaks(Double_t *InAmpl, Double_t level, Int_t &num_peaks);
   virtual void     GetTrueNumPeaks(Double_t *InAmpl, Double_t level, Int_t &num_peaks);

   // Per peak
   virtual void     GetMaxAmplPerPeak(Double_t *InAmpl, Double_t level, Double_t *OutAmpl, Double_t *OutTime);
   virtual void     GetTimeAtLevelPerPeak(Double_t *InAmpl, Double_t level, Double_t *OutTime);
   virtual void     GetWidthPerPeak(Double_t *InAmpl, Double_t level, Double_t *OutWidth);

};

#endif

#ifdef Tree_cxx
Tree::Tree(TString nameOfTheFile) : fChain(0)
{
    TTree *tree = 0;
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0)
    {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(nameOfTheFile.Data());
        if (!f || !f->IsOpen())
        {
            f = new TFile(nameOfTheFile.Data());
        }
        f->GetObject("Tree",tree);
    }
    Init(tree);
}

Tree::~Tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Tree::LoadTree(Long64_t entry)
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

void Tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Amplitude", Amplitude, &b_amplitude);
   fChain->SetBranchAddress("UnixTime", &UnixTime, &b_untime);
   fChain->SetBranchAddress("EventID", &EventID, &b_eventid);
   fChain->SetBranchAddress("TDC", &TDC, &b_tdc);
   fChain->SetBranchAddress("BaseLine", BaseLine, &b_baseline);
   fChain->SetBranchAddress("Peak", Peak, &b_peak);
   fChain->SetBranchAddress("PeakTime", PeakTime, &b_peaktime);
   fChain->SetBranchAddress("Charge", Charge, &b_charge);
   fChain->SetBranchAddress("RisingTime", RisingTime, &b_risingtime);
   fChain->SetBranchAddress("FallingTime", FallingTime, &b_fallingtime);
   fChain->SetBranchAddress("PeakNum", PeakNum, &b_peaknum);
   Notify();
}

Bool_t Tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Tree_cxx
