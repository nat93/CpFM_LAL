// For calibration with ion beam data analysis using waveform analysis results

//root
#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TProfile.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

#include "include/Constants.hh"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [1] - A name of the input .root file with WvF parameters."<<endl;
        cout<<"--> [2] - A name of the output file with histograms."<<endl;
        cout<<endl;
        return -1;
    }

    // Common
    Double_t untime;
    Double_t tdc;
    Double_t max_ampl[Constants::nCh];
    Double_t min_ampl[Constants::nCh];
    Double_t mean_value_20p[Constants::nCh];
    Double_t time_max_ampl[Constants::nCh];
    Double_t time_min_ampl[Constants::nCh];
    Double_t time_level[Constants::nCh];
    Double_t time_cf[Constants::nCh];
    Double_t rise_time[Constants::nCh];
    Double_t fall_time[Constants::nCh];
    Double_t charge[Constants::nCh];
    Double_t width_at_level[Constants::nCh];
    Int_t num_peaks[Constants::nCh];
    Int_t num_peaks_true[Constants::nCh];
    Int_t eventid;
    // Per peak
    Double_t max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_level_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t width_at_level_per_peak[Constants::nCh][Constants::nPeakMax];

    TChain *fChain1 = new TChain("Tree");
    fChain1->Add(argv[1]);

    fChain1->SetBranchAddress("UnixTime",               &untime);
    fChain1->SetBranchAddress("TDC",                    &tdc);
    fChain1->SetBranchAddress("EventID",                &eventid);
    fChain1->SetBranchAddress("MaxAmp",                 max_ampl);
    fChain1->SetBranchAddress("MinAmp",                 min_ampl);
    fChain1->SetBranchAddress("TimeMaxAmp",             time_max_ampl);
    fChain1->SetBranchAddress("TimeMinAmp",             time_min_ampl);
    fChain1->SetBranchAddress("TimeLevel",              time_level);
    fChain1->SetBranchAddress("WidthAtTimeCF",          width_at_level);
    fChain1->SetBranchAddress("MeanValue20Points",      mean_value_20p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    fChain1->SetBranchAddress("MaxAmpPerPeak",          max_ampl_per_peak);
    fChain1->SetBranchAddress("TimeMaxAmpPerPeak",      time_max_ampl_per_peak);
    fChain1->SetBranchAddress("TimeLevelPerPeak",       time_level_per_peak);
    fChain1->SetBranchAddress("WidthAtTimeCFPerPeak",   width_at_level_per_peak);

    Long64_t minUnixTime_run = 1479948000000000;//24 November 2016 01:40:00
    Long64_t maxUnixTime_run = 1479957600000000;//24 November 2016 04:20:00

    cout<<"--> Input file: "<<argv[1]<<endl;
    Double_t nEntries = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//
    TH1D* h_1 = new TH1D("h_1","max_ampl CH[0]",2000,0,2.0);
    TH1D* h_2 = new TH1D("h_2","max_ampl CH[1]",2000,0,2.0);
    TH1D* h_3 = new TH1D("h_3","max_ampl CH[2]",2000,0,2.0);
    TH1D* h_4 = new TH1D("h_4","charge CH[0]",5000,0,50.0);
    TH1D* h_5 = new TH1D("h_5","charge CH[1]",5000,0,50.0);
    TH1D* h_6 = new TH1D("h_6","charge CH[2]",5000,0,50.0);
    TH2D* h_7 = new TH2D("h_7","charge vs max_ampl CH[1]",2000,0,2.0,5000,0,50.0);
    TH2D* h_8 = new TH2D("h_8","charge vs max_ampl CH[2]",2000,0,2.0,5000,0,50.0);
    TH1D* h_9 = new TH1D("h_9","charge CH[1] (cut)",5000,0,50.0);
    TH1D* h_10 = new TH1D("h_10","charge CH[2] (cut)",5000,0,50.0);
    TH2D* h_11 = new TH2D("h_11","charge vs max_ampl CH[1] (cut)",2000,0,2.0,5000,0,50.0);
    TH2D* h_12 = new TH2D("h_12","charge vs max_ampl CH[2] (cut)",2000,0,2.0,5000,0,50.0);
    TH2D* h_13 = new TH2D("h_13","max_ampl CH[1] vs max_ampl CH[2]",2000,0,2.0,2000,0,2.0);
    TH2D* h_14 = new TH2D("h_14","charge CH[1] vs charge CH[2]",5000,0,50.0,5000,0,50.0);
    //--------------------------------------------------------------------------//

    for(Int_t eventID = 0; eventID < nEntries; eventID++)
    {
        fChain1->GetEntry(eventID);

        for(Int_t i = 0; i < Constants::nCh; i++)
        {
            charge[i]   = charge[i] - mean_value_20p[i]*Constants::dTime*Constants::nPnt;
            max_ampl[i] = max_ampl[i] - mean_value_20p[i];
        }

        if(eventID%1000 == 0)
        {
            printf("\r--> Working: %3.1f %%",100*(Double_t)eventID/nEntries);
            fflush(stdout);
        }
        if(untime < minUnixTime_run || untime > maxUnixTime_run) continue;
        //-------------------------------------------------------------------------------------------------------------------------------------//

        h_1->Fill(max_ampl[0]);
        h_4->Fill(charge[0]);

        if(max_ampl[0] > Constants::Level[0]) // check trigger channel
        {
            h_2->Fill(max_ampl[1]);
            h_3->Fill(max_ampl[2]);
            h_5->Fill(charge[1]);
            h_6->Fill(charge[2]);
            h_7->Fill(max_ampl[1],charge[1]);
            h_8->Fill(max_ampl[2],charge[2]);

            if(max_ampl[1] < 0.4)
            {
                h_9->Fill(charge[1]);
                h_11->Fill(max_ampl[1],charge[1]);
            }

            if(max_ampl[2] < 1.2)
            {
                h_10->Fill(charge[2]);
                h_12->Fill(max_ampl[2],charge[2]);
            }

            h_13->Fill(max_ampl[2],max_ampl[1]);
            h_14->Fill(charge[2],charge[1]);
        }
    }
    cout<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- WRITE -----------------------------------//
    //--------------------------------------------------------------------------//
    cout<<"--> Output file: "<<argv[2]<<endl;
    TFile* file = new TFile(argv[2],"recreate");

    h_1->Write();
    h_2->Write();
    h_3->Write();
    h_4->Write();
    h_5->Write();
    h_6->Write();
    h_7->Write();
    h_8->Write();
    h_9->Write();
    h_10->Write();
    h_11->Write();
    h_12->Write();
    h_13->Write();
    h_14->Write();

    file->Write();
    //--------------------------------------------------------------------------//

    return 0;
}

