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
#include "TGraphErrors.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TMultiGraph.h"
#include "TCanvas.h"

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

void function_1();
void function_2();
void function_3();
void function_4();
void function_5();
void function_6();
void function_7();
void function_8();
void function_9();
void function_10();

Double_t fitf(Double_t *x,Double_t *par);
Int_t getNphotonDetect(Double_t polishingQuality, Int_t *reflectionNum, Double_t *Wavelength, Int_t Nhits);
Bool_t isPhotonDetected(Double_t polishingQuality, Int_t reflectionNum, Double_t Wavelength);
void GetPointGraph(TGraphErrors* gr, Double_t x, Double_t ex, Double_t &y, Double_t &ey);
inline bool exists_test(const std::string& name);

TRandom3* _rnd = new TRandom3();

Int_t main(Int_t argc, char *argv[])
{
    if(argc != 2)
    {
        cout<<endl;
        cout<<"--> 1 >> function_1() -- parking position"<<endl;
        cout<<"--> 2 >> function_2() -- linear scan"<<endl;
        cout<<"--> 3 >> function_3() -- number of particles along the linear scan"<<endl;
        cout<<"--> 4 >> function_4() -- H8 linear scan"<<endl;
        cout<<"--> 5 >> function_5() -- angular scan"<<endl;
        cout<<"--> 6 >> function_6() - to plot ratio for 100% of polishing"<<endl;
        cout<<"--> 7 >> function_7() - to plot ratio for dif% of polishing"<<endl;
        cout<<"--> 8 >> function_8() - to find the exp sim match (polish)"<<endl;
        cout<<"--> 9 >> function_9() - to plot ratio for dif% of polishing and width"<<endl;
        cout<<"--> 10 >> function_10() - to find the exp sim match (polish + width)"<<endl;
        cout<<endl;
        return -1;
    }

    switch ( atoi(argv[1]) )
    {
    case 1:
      function_1();
      break;
    case 2:
      function_2();
      break;
    case 3:
      function_3();
      break;
    case 4:
      function_4();
      break;
    case 5:
      function_5();
      break;
    case 6:
      function_6();
      break;
    case 7:
      function_7();
      break;
    case 8:
      function_8();
      break;
    case 9:
      function_9();
      break;
    case 10:
      function_10();
      break;
    default:
      cout<<"--> Nothing to do =)"<<endl;
      break;
    }

    return 0;
}

void function_1()
{
    //=======================================//
    // 2016_10_18
    // Parking Position --> (18 Oct 2016 12:50:00 - 18 Oct 2016 14:25:00)
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_10_18.root";
    // Linear Scan
//    Long64_t minUnixTime_run = 1476787800000000;
//    Long64_t maxUnixTime_run = 1476793500000000;
    //=======================================//

    //=======================================//
    // 2018_09_17
    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_09_17.root";
    // Fixed Position in Single CH
    //== PMT HV 700 V ==//
//    Long64_t minUnixTime_run = 1537188840000000;
//    Long64_t maxUnixTime_run = 1537189800000000;
    //== PMT HV 750 V ==//
//    Long64_t minUnixTime_run = 1537204800000000;
//    Long64_t maxUnixTime_run = 1537205400000000;
    //== PMT HV 800 V ==//
//    Long64_t minUnixTime_run = 1537187340000000;
//    Long64_t maxUnixTime_run = 1537188060000000;
    //== PMT HV 900 V ==//
    Long64_t minUnixTime_run = 1537188300000000;
    Long64_t maxUnixTime_run = 1537188780000000;
    // Parking Position
//    Long64_t minUnixTime_run = 1537190700000000;
//    Long64_t maxUnixTime_run = 1537191900000000;
    //=======================================//

    //=======================================//
    // 2017_05_30
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_05_30.root";
    // Parking Position
//    Long64_t minUnixTime_run = 1496151420000000;
//    Long64_t maxUnixTime_run = 1496153220000000;
    //=======================================//

    //=======================================//
    // 2017_09_18
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_09_18.root";
    // Parking Position
//    Long64_t minUnixTime_run = 1505715000000000;
//    Long64_t maxUnixTime_run = 1505718000000000;
    // LHC coll scan
//    Long64_t minUnixTime_run = 1505768040000000;
//    Long64_t maxUnixTime_run = 1505768700000000;
    //=======================================//

    TString output_file_name    = "./output/output_function_1.root";

    // Common
    Double_t untime;
    Double_t tdc;
    Double_t max_ampl[Constants::nCh];
    Double_t min_ampl[Constants::nCh];
    Double_t mean_value_16p[Constants::nCh];
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

    TChain *fChain1 = new TChain("Tree");
    fChain1->Add(input_file_name);

    fChain1->SetBranchAddress("UnixTime",               &untime);
    fChain1->SetBranchAddress("TDC",                    &tdc);
    fChain1->SetBranchAddress("EventID",                &eventid);
    fChain1->SetBranchAddress("MaxAmp",                 max_ampl);
    fChain1->SetBranchAddress("MinAmp",                 min_ampl);
    fChain1->SetBranchAddress("TimeMaxAmp",             time_max_ampl);
    fChain1->SetBranchAddress("TimeMinAmp",             time_min_ampl);
    fChain1->SetBranchAddress("TimeLevel",              time_level);
    fChain1->SetBranchAddress("WidthAtTimeCF",          width_at_level);
    fChain1->SetBranchAddress("MeanValue16Points",      mean_value_16p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    cout<<"--> Input file: "<<input_file_name<<endl;
    Double_t nEntries = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//
    TH1D* h_1 = new TH1D("h_1","max_ampl CH[0]",3000,-0.5,2.5);
    TH1D* h_2 = new TH1D("h_2","max_ampl CH[1]",3000,-0.5,2.5);
    TH1D* h_3 = new TH1D("h_3","max_ampl CH[2]",3000,-0.5,2.5);
    TH1D* h_4 = new TH1D("h_4","charge CH[0]",6000,-10,50.0);
    TH1D* h_5 = new TH1D("h_5","charge CH[1]",6000,-10,50.0);
    TH1D* h_6 = new TH1D("h_6","charge CH[2]",6000,-10,50.0);
    TH2D* h_7 = new TH2D("h_7","charge vs max_ampl CH[1]",3000,-0.5,2.5,6000,-10,50.0);
    TH2D* h_8 = new TH2D("h_8","charge vs max_ampl CH[2]",3000,-0.5,2.5,6000,-10,50.0);
    TH1D* h_9 = new TH1D("h_9","charge CH[1] (cut)",200000,-1000,1000.0);
    TH1D* h_10 = new TH1D("h_10","charge CH[2] (cut)",200000,-1000,1000.0);
    TH2D* h_11 = new TH2D("h_11","charge vs max_ampl CH[1] (cut)",3000,-0.5,2.5,6000,-10,50.0);
    TH2D* h_12 = new TH2D("h_12","charge vs max_ampl CH[2] (cut)",3000,-0.5,2.5,6000,-10,50.0);
    TH2D* h_13 = new TH2D("h_13","max_ampl CH[1] vs max_ampl CH[2]",3000,-0.5,2.5,3000,-0.5,2.5);
    TH2D* h_14 = new TH2D("h_14","charge CH[1] vs charge CH[2]",6000,-10,50.0,6000,-10,50.0);
    TH1D* h_15 = new TH1D("h_15","max_ampl CH[1] (cut)",3000,-0.5,2.5);
    TH1D* h_16 = new TH1D("h_16","max_ampl CH[2] (cut)",3000,-0.5,2.5);
    TH1D* h_17 = new TH1D("h_17","max_ampl CH[1] (cut2)",3000,-0.5,2.5);
    TH1D* h_18 = new TH1D("h_18","max_ampl CH[2] (cut2)",3000,-0.5,2.5);
    TH1D* h_19 = new TH1D("h_19","num max_ampl CH[1]",1010000,-10,1000);
    TH1D* h_20 = new TH1D("h_20","num charge CH[1]",1010000,-10,1000);
    //--------------------------------------------------------------------------//

    const Double_t ampl_cpfm1_pro       = 18.294e-3;
    const Double_t char_cpfm1_pro       = 0.149;

    for(Int_t eventID = 0; eventID < nEntries; eventID++)
    {
        fChain1->GetEntry(eventID);

        for(Int_t i = 0; i < Constants::nCh; i++)
        {
            charge[i]   = charge[i]*Constants::pCtoAu;
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

            if(max_ampl[1] > 6.0e-3)
            {
                h_9->Fill(charge[1]);
                h_11->Fill(max_ampl[1],charge[1]);
                h_15->Fill(max_ampl[1]);
                h_19->Fill(max_ampl[1]/ampl_cpfm1_pro);
                h_20->Fill(charge[1]/char_cpfm1_pro);
            }            

            if(max_ampl[2] > 6.0e-3)
            {
                h_10->Fill(charge[2]);
                h_12->Fill(max_ampl[2],charge[2]);
                h_16->Fill(max_ampl[2]);
            }

            h_13->Fill(max_ampl[2],max_ampl[1]);
            h_14->Fill(charge[2],charge[1]);

            if(charge[1] < 2.6+5.0*0.12)
            {
                h_17->Fill(max_ampl[1]);
            }

            if(charge[2] < 0.0495+3.0*0.0252)
            {
                h_18->Fill(max_ampl[2]);
            }
        }
    }
    cout<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- WRITE -----------------------------------//
    //--------------------------------------------------------------------------//
    cout<<"--> Output file: "<<output_file_name<<endl;
    TFile* file = new TFile(output_file_name,"recreate");

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
    h_15->Write();
    h_16->Write();
    h_17->Write();
    h_18->Write();
    h_19->Write();
    h_20->Write();

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_2()
{
    TString output_file_name    = "./output/output_function_2.root";

    //=============================================================//
    // Linear Scan
    // 2016_10_18
//    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_10_18.root";
//    TString input_file_rate     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_rt_2016_10_18.root";
//    TString input_file_motor    = "cpfm_linear_scan_1.root";
//    Long64_t minUnixTime_run = 1476807090;
//    Long64_t maxUnixTime_run = 1476809610;

//    const Double_t ampl_cpfm1_pro       = 0.990e-3;
//    const Double_t ampl_cpfm2_pro       = 2.910e-3;
//    const Double_t char_cpfm1_pro       = 0.005;
//    const Double_t char_cpfm2_pro       = 0.018;
    //=============================================================//
    // Linear Scan Single CH
    // 2018_09_17
    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_09_17.root";
    TString input_file_motor    = "cpfm_linear_scan_2018_09_17.root";
    Long64_t minUnixTime_run = 1537188300;
    Long64_t maxUnixTime_run = 1537188622;

    const Double_t ampl_cpfm1_pro       = 77.8e-3;
    const Double_t ampl_cpfm2_pro       = 77.8e-3;
    const Double_t char_cpfm1_pro       = 0.407;
    const Double_t char_cpfm2_pro       = 0.407;
    const Double_t linear_speed         = 0.1; // [mm/s]
    //=============================================================//
    // Linear Scan Double_t CH
    // 2018_09_17
//    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_09_17.root";
//    TString input_file_motor    = "cpfm_linear_scan_2018_09_17_dch.root";
//    Long64_t minUnixTime_run = 1537246666;
//    Long64_t maxUnixTime_run = 1537247388;

//    const Double_t ampl_cpfm1_pro       = 19.2e-3;
//    const Double_t ampl_cpfm2_pro       = 19.2e-3;
//    const Double_t char_cpfm1_pro       = 0.114;
//    const Double_t char_cpfm2_pro       = 0.114;
//    const Double_t linear_speed         = 0.1; // [mm/s]
    //=============================================================//
    // Linear Scan Double_t CH
    // 2018_11_07
//    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_11_07.root";
//    TString input_file_motor    = "cpfm_linear_scan_2018_11_07_dch.root";
//    Long64_t minUnixTime_run = 1541599153;
//    Long64_t maxUnixTime_run = 1541599616;

//    const Double_t ampl_cpfm1_pro       = 19.2e-3;
//    const Double_t ampl_cpfm2_pro       = 19.2e-3;
//    const Double_t char_cpfm1_pro       = 0.114;
//    const Double_t char_cpfm2_pro       = 0.114;
//    const Double_t linear_speed         = 0.1; // [mm/s]
    //=============================================================//

    // Measurements
    Double_t untime;
    Double_t tdc;
    Double_t max_ampl[Constants::nCh];
    Double_t min_ampl[Constants::nCh];
    Double_t mean_value_16p[Constants::nCh];
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

    TChain *fChain1 = new TChain("Tree");
    fChain1->Add(input_file_meas);

    fChain1->SetBranchAddress("UnixTime",               &untime);
    fChain1->SetBranchAddress("TDC",                    &tdc);
    fChain1->SetBranchAddress("EventID",                &eventid);
    fChain1->SetBranchAddress("MaxAmp",                 max_ampl);
    fChain1->SetBranchAddress("MinAmp",                 min_ampl);
    fChain1->SetBranchAddress("TimeMaxAmp",             time_max_ampl);
    fChain1->SetBranchAddress("TimeMinAmp",             time_min_ampl);
    fChain1->SetBranchAddress("TimeLevel",              time_level);
    fChain1->SetBranchAddress("WidthAtTimeCF",          width_at_level);
    fChain1->SetBranchAddress("MeanValue16Points",      mean_value_16p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    // Rate
//    Int_t eventid_rate;
//    Double_t untime_rate;
//    Double_t tdc_rate;
//    Double_t rate[Constants::nCh];

//    TChain *fChain2 = new TChain("Tree");
//    fChain2->Add(input_file_rate);

//    fChain2->SetBranchAddress("UnixTime",    &untime_rate);
//    fChain2->SetBranchAddress("TDC",         &tdc_rate);
//    fChain2->SetBranchAddress("EventID",     &eventid_rate);
//    fChain2->SetBranchAddress("Rate",        rate);

    // Motor
    Double_t position;
    Double_t untime_motor;

    TChain *fChain3 = new TChain("Tree");
    fChain3->Add(input_file_motor);

    fChain3->SetBranchAddress("MotorPosition",  &position);
    fChain3->SetBranchAddress("UnixTime",       &untime_motor);

    cout<<"--> Input file with measurements: "<<input_file_meas<<endl;
    Double_t nEntries_1 = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries_1<<endl;

//    cout<<"--> Input file with rate: "<<input_file_rate<<endl;
//    Double_t nEntries_2 = fChain2->GetEntries();
//    cout<<"--> nEntries: "<<nEntries_2<<endl;

    cout<<"--> Input file with motor: "<<input_file_motor<<endl;
    Double_t nEntries_3 = fChain3->GetEntries();
    cout<<"--> nEntries: "<<nEntries_3<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//
    TH1D* h_1 = new TH1D("h_1","max_ampl CH[0]",3000,-0.5,2.5);
    TH1D* h_2 = new TH1D("h_2","max_ampl CH[1]",3000,-0.5,2.5);
    TH1D* h_3 = new TH1D("h_3","max_ampl CH[2]",3000,-0.5,2.5);
    TH1D* h_4 = new TH1D("h_4","charge CH[0]",6000,-10,50.0);
    TH1D* h_5 = new TH1D("h_5","charge CH[1]",6000,-10,50.0);
    TH1D* h_6 = new TH1D("h_6","charge CH[2]",6000,-10,50.0);
    TH2D* h_7 = new TH2D("h_7","charge vs max_ampl CH[1]",3000,-0.5,2.5,6000,-10,50.0);
    TH2D* h_8 = new TH2D("h_8","charge vs max_ampl CH[2]",3000,-0.5,2.5,6000,-10,50.0);
    TH1D* h_9 = new TH1D("h_9","charge CH[1] (cut)",200000,-1000,1000.0);
    TH1D* h_10 = new TH1D("h_10","charge CH[2] (cut)",200000,-1000,1000.0);
    TH2D* h_11 = new TH2D("h_11","charge vs max_ampl CH[1] (cut)",3000,-0.5,2.5,6000,-10,50.0);
    TH2D* h_12 = new TH2D("h_12","charge vs max_ampl CH[2] (cut)",3000,-0.5,2.5,6000,-10,50.0);
    TH2D* h_13 = new TH2D("h_13","max_ampl CH[1] vs max_ampl CH[2]",3000,-0.5,2.5,3000,-0.5,2.5);
    TH2D* h_14 = new TH2D("h_14","charge CH[1] vs charge CH[2]",6000,-10,50.0,6000,-10,50.0);
    TH1D* h_15 = new TH1D("h_15","max_ampl CH[1] (cut)",3000,-0.5,2.5);
    TH1D* h_16 = new TH1D("h_16","max_ampl CH[2] (cut)",3000,-0.5,2.5);
    TH1D* h_17 = new TH1D("h_17","max_ampl CH[1] (cut2)",3000,-0.5,2.5);
    TH1D* h_18 = new TH1D("h_18","max_ampl CH[2] (cut2)",3000,-0.5,2.5);
    //--------------------------------------------------------------------------//
    TH2D* hh_1 = new TH2D("hh_1","Amplitude vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,3000,-0.5,2.5);
    TH2D* hh_2 = new TH2D("hh_2","Amplitude vs UnixTime CH[1]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,3000,-0.5,2.5);
    TH2D* hh_3 = new TH2D("hh_3","Amplitude vs UnixTime CH[2]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,3000,-0.5,2.5);
    TH2D* hh_4 = new TH2D("hh_4","Charge vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,6000,-10,500.0);
    TH2D* hh_5 = new TH2D("hh_5","Charge vs UnixTime CH[1]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,6000,-10,500.0);
    TH2D* hh_6 = new TH2D("hh_6","Charge vs UnixTime CH[2]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,6000,-10,500.0);
//    TH2D* hh_7 = new TH2D("hh_7","Rate vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,1000,0,1e3);
//    TH2D* hh_8 = new TH2D("hh_8","Rate vs UnixTime CH[1]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,10000,0,1e7);
//    TH2D* hh_9 = new TH2D("hh_9","Rate vs UnixTime CH[2]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,10000,0,1e7);
    TH2D* hh_10 = new TH2D("hh_10","Position vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,10000,0,100);

    TH2D* hh_11 = new TH2D("hh_11","Amplitude vs Position CH[0]",10000,0,100,3000,-0.5,2.5);
    TH2D* hh_12 = new TH2D("hh_12","Amplitude vs Position CH[1]",10000,0,100,3000,-0.5,2.5);
    TH2D* hh_13 = new TH2D("hh_13","Amplitude vs Position CH[2]",10000,0,100,3000,-0.5,2.5);
    TH2D* hh_14 = new TH2D("hh_14","Charge vs Position CH[0]",10000,0,100,6000,-10,50.0);
    TH2D* hh_15 = new TH2D("hh_15","Charge vs Position CH[1]",10000,0,100,6000,-10,50.0);
    TH2D* hh_16 = new TH2D("hh_16","Charge vs Position CH[2]",10000,0,100,6000,-10,50.0);
//    TH2D* hh_17 = new TH2D("hh_17","Rate vs Position CH[0]",10000,0,100,1000,0,1e3);
//    TH2D* hh_18 = new TH2D("hh_18","Rate vs Position CH[1]",10000,0,100,10000,0,1e7);
//    TH2D* hh_19 = new TH2D("hh_19","Rate vs Position CH[2]",10000,0,100,10000,0,1e7);

    TProfile* hprof_1  = new TProfile("hprof_1","Profile of Amplitude vs Position CH[0]",100/linear_speed,0,100,-0.5,2.5);
    TProfile* hprof_2  = new TProfile("hprof_2","Profile of Amplitude vs Position CH[1]",100/linear_speed,0,100,-0.5,2.5);
    TProfile* hprof_3  = new TProfile("hprof_3","Profile of Amplitude vs Position CH[2]",100/linear_speed,0,100,-0.5,2.5);
    TProfile* hprof_4  = new TProfile("hprof_4","Profile of Charge vs Position CH[0]",100/linear_speed,0,100,-10,500.0);
    TProfile* hprof_5  = new TProfile("hprof_5","Profile of Charge vs Position CH[1]",100/linear_speed,0,100,-10,500.0);
    TProfile* hprof_6  = new TProfile("hprof_6","Profile of Charge vs Position CH[2]",100/linear_speed,0,100,-10,500.0);
//    TProfile* hprof_7  = new TProfile("hprof_7","Profile of Rate vs Position CH[0]",10000,0,100,0,1e3);
//    TProfile* hprof_8  = new TProfile("hprof_8","Profile of Rate vs Position CH[1]",10000,0,100,0,1e7);
//    TProfile* hprof_9  = new TProfile("hprof_9","Profile of Rate vs Position CH[2]",10000,0,100,0,1e7);

    TH1D* h_19 = new TH1D("h_19","max_ampl CH[1] (70-72cm)",3000,-0.5,2.5);
    TH1D* h_20 = new TH1D("h_20","max_ampl CH[2] (75-77cm)",3000,-0.5,2.5);
    TH1D* h_21 = new TH1D("h_21","num max_ampl CH[1] (70-72cm & cut)",1010,-10,1000);
    TH1D* h_22 = new TH1D("h_22","num max_ampl CH[2] (75-77cm & cut)",1010,-10,1000);
    TH1D* h_23 = new TH1D("h_23","num charge CH[1] (70-72cm & cut)",1010,-10,1000);
    TH1D* h_24 = new TH1D("h_24","num charge CH[2] (75-77cm & cut)",1010,-10,1000);

    TGraphErrors* gr_0 = new TGraphErrors();
    gr_0->SetName("gr_0");
    gr_0->SetTitle("Position");
    Int_t gr_0_iter = 0;

    //--------------------------------------------------------------------------//

    // MOTOR
    for(Int_t eventID = 0; eventID < nEntries_3; eventID++)
    {
        fChain3->GetEntry(eventID);
        untime_motor = untime_motor/1000000.0;

        if(eventID%1 == 0)
        {
            printf("\r--> Working Motor: %3.1f %%",100*(Double_t)eventID/nEntries_3);
            fflush(stdout);
        }
        if(untime_motor < minUnixTime_run || untime_motor > maxUnixTime_run) continue;
        //-------------------------------------------------------------------------------------------------------------------------------------//

        hh_10->Fill(untime_motor,position);
        gr_0->SetPoint(gr_0_iter,untime_motor,position);
        gr_0->SetPointError(gr_0_iter,1.0/TMath::Sqrt(12.0),0.001);
        gr_0_iter++;
    }
    cout<<endl;

    // RATE & MEASUREMENTS
//    if(nEntries_1 != nEntries_2)
//    {
//        cout<<endl;
//        cout<<"--> Different number of Entries: nEntries_1 != nEntries_2 !!!!"<<endl;
//        cout<<endl;
//        assert(0);
//    }

    Int_t starting_event = 0; // (18 Oct 2016 18:11:30 - 18 Oct 2016 18:53:30) --> 2331786-100;
    for(Int_t eventID = starting_event; eventID < nEntries_1; eventID++)
    {
        fChain1->GetEntry(eventID);
//        fChain2->GetEntry(eventID);

        for(Int_t i = 0; i < Constants::nCh; i++)
        {
            charge[i]   = charge[i]*Constants::pCtoAu;
        }
        untime = untime/1000000.0;

        if(eventID%1000 == 0)
        {
            printf("\r--> Working Measurements: %3.1f %%",100*(Double_t)eventID/nEntries_1);
            fflush(stdout);
        }
        if(untime < minUnixTime_run || untime > maxUnixTime_run) continue;
//        cout<<endl<<"--> Starting EventID = "<<eventID<<endl;
        //-------------------------------------------------------------------------------------------------------------------------------------//

//        if(eventid != eventid_rate)
//        {
//            cout<<endl;
//            cout<<"--> Different EventID: eventid != eventid_rate !!!!"<<endl;
//            cout<<endl;
//            assert(0);
//        }

        hh_1->Fill(untime,max_ampl[0]);
        hh_2->Fill(untime,max_ampl[1]);
        hh_3->Fill(untime,max_ampl[2]);
        hh_4->Fill(untime,charge[0]);
        hh_5->Fill(untime,charge[1]);
        hh_6->Fill(untime,charge[2]);
//        hh_7->Fill(untime,rate[0]);
//        hh_8->Fill(untime,rate[1]);
//        hh_9->Fill(untime,rate[2]);

        Double_t position = gr_0->Eval(untime);

        hh_11->Fill(position,max_ampl[0]);
        hh_12->Fill(position,max_ampl[1]);
        hh_13->Fill(position,max_ampl[2]);
        hh_14->Fill(position,charge[0]);
        hh_15->Fill(position,charge[1]);
        hh_16->Fill(position,charge[2]);
//        hh_17->Fill(position,rate[0]);
//        hh_18->Fill(position,rate[1]);
//        hh_19->Fill(position,rate[2]);

        hprof_1->Fill(position,max_ampl[0]);
        hprof_2->Fill(position,max_ampl[1]);
        hprof_3->Fill(position,max_ampl[2]);
        hprof_4->Fill(position,charge[0]);
        hprof_5->Fill(position,charge[1]);
        hprof_6->Fill(position,charge[2]);
//        hprof_7->Fill(position,rate[0]);
//        hprof_8->Fill(position,rate[1]);
//        hprof_9->Fill(position,rate[2]);

        //-------------------------------------------------------------------------------------------------------------------------------------//
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

            if(max_ampl[1] > 6.0e-3)
            {
                h_9->Fill(charge[1]);
                h_11->Fill(max_ampl[1],charge[1]);
                h_15->Fill(max_ampl[1]);
            }

            if(max_ampl[2] > 6.0e-3)
            {
                h_10->Fill(charge[2]);
                h_12->Fill(max_ampl[2],charge[2]);
                h_16->Fill(max_ampl[2]);
            }

            h_13->Fill(max_ampl[2],max_ampl[1]);
            h_14->Fill(charge[2],charge[1]);

            if(charge[1] < 0.0395+3.0*0.0247)
            {
                h_17->Fill(max_ampl[1]);
            }

            if(charge[2] < 0.0495+3.0*0.0252)
            {
                h_18->Fill(max_ampl[2]);
            }

            if(position > 70.0 && position < 72.0)
            {
                h_19->Fill(max_ampl[1]);
                if(max_ampl[1] > 6.0e-3)
                {
                    h_21->Fill(max_ampl[1]/ampl_cpfm1_pro);
                    h_23->Fill(charge[1]/char_cpfm1_pro);
                }
            }
            if(position > 75.0 && position < 77.0)
            {
                h_20->Fill(max_ampl[2]);
                if(max_ampl[2] > 6.0e-3)
                {
                    h_22->Fill(max_ampl[2]/ampl_cpfm2_pro);
                    h_24->Fill(charge[2]/char_cpfm2_pro);
                }
            }
        }
    }
    cout<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- WRITE -----------------------------------//
    //--------------------------------------------------------------------------//
    cout<<"--> Output file: "<<output_file_name<<endl;
    TFile* file = new TFile(output_file_name,"recreate");

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
    h_15->Write();
    h_16->Write();
    h_17->Write();
    h_18->Write();
    h_19->Write();
    h_20->Write();
    h_21->Write();
    h_22->Write();
    h_23->Write();
    h_24->Write();

    hh_1->Write();
    hh_2->Write();
    hh_3->Write();
    hh_4->Write();
    hh_5->Write();
    hh_6->Write();
//    hh_7->Write();
//    hh_8->Write();
//    hh_9->Write();
    hh_10->Write();
    hh_11->Write();
    hh_12->Write();
    hh_13->Write();
    hh_14->Write();
    hh_15->Write();
    hh_16->Write();
//    hh_17->Write();
//    hh_18->Write();
//    hh_19->Write();

    hprof_1->Write();
    hprof_2->Write();
    hprof_3->Write();
    hprof_4->Write();
    hprof_5->Write();
    hprof_6->Write();
//    hprof_7->Write();
//    hprof_8->Write();
//    hprof_9->Write();

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_3()
{
    TString input_file_meas     = "./output/output_function_2.root";
    TString output_file_name    = "./output/output_function_3.root";

    //===========================================================================//
    // Linear scan 2016_10_18 (18 Oct 2016 18:11:30 - 18 Oct 2016 18:53:30)
//    const Double_t ampl_cpfm1_pro       = 0.990e-3;
//    const Double_t ampl_cpfm1_pro_err   = 0.001e-3;
//    const Double_t ampl_cpfm2_pro       = 2.910e-3;
//    const Double_t ampl_cpfm2_pro_err   = 0.001e-3;

//    const Double_t char_cpfm1_pro       = 0.005;
//    const Double_t char_cpfm1_pro_err   = 3.6e-6;
//    const Double_t char_cpfm2_pro       = 0.018;
//    const Double_t char_cpfm2_pro_err   = 5.9e-6;

    //===========================================================================//
    // Linear scan single CH 2018_09_17
    const Double_t ampl_cpfm1_pro       = 77.8e-3;
    const Double_t ampl_cpfm1_pro_err   = 0.1e-3;
    const Double_t ampl_cpfm2_pro       = 77.8e-3;
    const Double_t ampl_cpfm2_pro_err   = 0.1e-3;

    const Double_t char_cpfm1_pro       = 0.407;
    const Double_t char_cpfm1_pro_err   = 0.004;
    const Double_t char_cpfm2_pro       = 0.407;
    const Double_t char_cpfm2_pro_err   = 0.004;
    const Double_t linear_speed         = 0.1; // [mm/s]
    //===========================================================================//
    // Linear scan Double_t CH 2018_09_17
//    const Double_t ampl_cpfm1_pro       = 19.2e-3;
//    const Double_t ampl_cpfm1_pro_err   = 0.4e-3;
//    const Double_t ampl_cpfm2_pro       = 19.2e-3;
//    const Double_t ampl_cpfm2_pro_err   = 0.4e-3;

//    const Double_t char_cpfm1_pro       = 0.114;
//    const Double_t char_cpfm1_pro_err   = 0.002;
//    const Double_t char_cpfm2_pro       = 0.114;
//    const Double_t char_cpfm2_pro_err   = 0.002;
//    const Double_t linear_speed         = 0.1; // [mm/s]
    //===========================================================================//
    // Linear scan Double_t CH 2018_11_07
//    const Double_t ampl_cpfm1_pro       = 19.2e-3;
//    const Double_t ampl_cpfm1_pro_err   = 0.4e-3;
//    const Double_t ampl_cpfm2_pro       = 19.2e-3;
//    const Double_t ampl_cpfm2_pro_err   = 0.4e-3;

//    const Double_t char_cpfm1_pro       = 0.114;
//    const Double_t char_cpfm1_pro_err   = 0.002;
//    const Double_t char_cpfm2_pro       = 0.114;
//    const Double_t char_cpfm2_pro_err   = 0.002;
//    const Double_t linear_speed         = 0.1; // [mm/s]
    //===========================================================================//

    const Double_t sps_rate             = 43000.0; // [Hz]

    TFile *_file_input = TFile::Open(input_file_meas.Data());

    TProfile* hprof_1  = (TProfile*)_file_input->Get("hprof_1");
    TProfile* hprof_2  = (TProfile*)_file_input->Get("hprof_2");
    TProfile* hprof_3  = (TProfile*)_file_input->Get("hprof_3");
    TProfile* hprof_4  = (TProfile*)_file_input->Get("hprof_4");
    TProfile* hprof_5  = (TProfile*)_file_input->Get("hprof_5");
    TProfile* hprof_6  = (TProfile*)_file_input->Get("hprof_6");
//    TProfile* hprof_7  = (TProfile*)_file_input->Get("hprof_7");
//    TProfile* hprof_8  = (TProfile*)_file_input->Get("hprof_8");
//    TProfile* hprof_9  = (TProfile*)_file_input->Get("hprof_9");

    TH1D* h_1 = new TH1D("h_1",hprof_1->GetTitle(),100/linear_speed,0,100);
    TH1D* h_2 = new TH1D("h_2",hprof_2->GetTitle(),100/linear_speed,0,100);
    TH1D* h_3 = new TH1D("h_3",hprof_3->GetTitle(),100/linear_speed,0,100);
    TH1D* h_4 = new TH1D("h_4",hprof_4->GetTitle(),100/linear_speed,0,100);
    TH1D* h_5 = new TH1D("h_5",hprof_5->GetTitle(),100/linear_speed,0,100);
    TH1D* h_6 = new TH1D("h_6",hprof_6->GetTitle(),100/linear_speed,0,100);

    for(Int_t i = 1; i <= hprof_1->GetNbinsX(); i++)
    {
        /*h_1->SetBinContent(i,hprof_1->GetBinContent(i)*hprof_7->GetBinContent(i));
        h_2->SetBinContent(i,hprof_2->GetBinContent(i)*hprof_8->GetBinContent(i)/ampl_cpfm1_pro);
        h_3->SetBinContent(i,hprof_3->GetBinContent(i)*hprof_9->GetBinContent(i)/ampl_cpfm2_pro);
        h_4->SetBinContent(i,hprof_4->GetBinContent(i)*hprof_7->GetBinContent(i));
        h_5->SetBinContent(i,hprof_5->GetBinContent(i)*hprof_8->GetBinContent(i)/char_cpfm1_pro);
        h_6->SetBinContent(i,hprof_6->GetBinContent(i)*hprof_9->GetBinContent(i)/char_cpfm2_pro);

        h_1->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_1->GetBinError(i)*hprof_7->GetBinContent(i),2)+
                                       TMath::Power(hprof_1->GetBinContent(i)*hprof_7->GetBinError(i),2)));
        h_2->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_2->GetBinError(i)*hprof_8->GetBinContent(i)/ampl_cpfm1_pro,2)+
                                       TMath::Power(hprof_2->GetBinContent(i)*hprof_8->GetBinError(i)/ampl_cpfm1_pro,2)+
                                       TMath::Power(hprof_2->GetBinContent(i)*hprof_8->GetBinContent(i)*ampl_cpfm1_pro_err/(ampl_cpfm1_pro*ampl_cpfm1_pro),2)));
        h_3->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_3->GetBinError(i)*hprof_9->GetBinContent(i)/ampl_cpfm2_pro,2)+
                                       TMath::Power(hprof_3->GetBinContent(i)*hprof_9->GetBinError(i)/ampl_cpfm2_pro,2)+
                                       TMath::Power(hprof_3->GetBinContent(i)*hprof_9->GetBinContent(i)*ampl_cpfm2_pro_err/(ampl_cpfm2_pro*ampl_cpfm2_pro),2)));
        h_4->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_4->GetBinError(i)*hprof_7->GetBinContent(i),2)+
                                       TMath::Power(hprof_4->GetBinContent(i)*hprof_7->GetBinError(i),2)));
        h_5->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_5->GetBinError(i)*hprof_8->GetBinContent(i)/char_cpfm1_pro,2)+
                                       TMath::Power(hprof_5->GetBinContent(i)*hprof_8->GetBinError(i)/char_cpfm1_pro,2)+
                                       TMath::Power(hprof_5->GetBinContent(i)*hprof_8->GetBinContent(i)*char_cpfm1_pro_err/(char_cpfm1_pro*char_cpfm1_pro),2)));
        h_6->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_6->GetBinError(i)*hprof_9->GetBinContent(i)/char_cpfm2_pro,2)+
                                       TMath::Power(hprof_6->GetBinContent(i)*hprof_9->GetBinError(i)/char_cpfm2_pro,2)+
                                       TMath::Power(hprof_6->GetBinContent(i)*hprof_9->GetBinContent(i)*char_cpfm2_pro_err/(char_cpfm2_pro*char_cpfm2_pro),2)));*/
        h_1->SetBinContent(i,hprof_1->GetBinContent(i)*sps_rate);
        h_2->SetBinContent(i,hprof_2->GetBinContent(i)*sps_rate/ampl_cpfm1_pro);
        h_3->SetBinContent(i,hprof_3->GetBinContent(i)*sps_rate/ampl_cpfm2_pro);
        h_4->SetBinContent(i,hprof_4->GetBinContent(i)*sps_rate);
        h_5->SetBinContent(i,hprof_5->GetBinContent(i)*sps_rate/char_cpfm1_pro);
        h_6->SetBinContent(i,hprof_6->GetBinContent(i)*sps_rate/char_cpfm2_pro);

        h_1->SetBinError(i,hprof_1->GetBinError(i)*sps_rate);
        h_2->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_2->GetBinError(i)*sps_rate/ampl_cpfm1_pro,2)+
                                       TMath::Power(hprof_2->GetBinContent(i)*sps_rate*ampl_cpfm1_pro_err/(ampl_cpfm1_pro*ampl_cpfm1_pro),2)));
        h_3->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_3->GetBinError(i)*sps_rate/ampl_cpfm2_pro,2)+
                                       TMath::Power(hprof_3->GetBinContent(i)*sps_rate*ampl_cpfm2_pro_err/(ampl_cpfm2_pro*ampl_cpfm2_pro),2)));
        h_4->SetBinError(i,hprof_4->GetBinError(i)*sps_rate);
        h_5->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_5->GetBinError(i)*sps_rate/char_cpfm1_pro,2)+
                                       TMath::Power(hprof_5->GetBinContent(i)*sps_rate*char_cpfm1_pro_err/(char_cpfm1_pro*char_cpfm1_pro),2)));
        h_6->SetBinError(i,TMath::Sqrt(TMath::Power(hprof_6->GetBinError(i)*sps_rate/char_cpfm2_pro,2)+
                                       TMath::Power(hprof_6->GetBinContent(i)*sps_rate*char_cpfm2_pro_err/(char_cpfm2_pro*char_cpfm2_pro),2)));

    }

    //--------------------------------------------------------------------------//
    //-------------------------------- WRITE -----------------------------------//
    //--------------------------------------------------------------------------//
    cout<<"--> Output file: "<<output_file_name<<endl;
    TFile* _file_output = new TFile(output_file_name,"recreate");

    hprof_1->Write();
    h_1->Write();
    h_2->Write();
    h_3->Write();
    h_4->Write();
    h_5->Write();
    h_6->Write();

    _file_output->Write();
    //--------------------------------------------------------------------------//
}

void function_4()
{
    //=======================================//
    // 2017_10_20
    //=======================================//    
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20.root";    // pyramid2     149 --> -15, HV 1050
//    Double_t pos_ini            = -15.0;
//    Double_t pos_fin            = 140.0;
    //=======================================//
    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20_v2.root";   // pyramid2 v2  -15 --> 140, HV 1050
    Double_t pos_ini            =   0.0;
    Double_t pos_fin            = 69+15;
    //=======================================//
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20_2.root";  // pyramid1     -5  --> 140, HV ?900
//    Double_t pos_ini            =  -5.0;
//    Double_t pos_fin            = 140.0;
    //=======================================//
    //=======================================//
    TString output_file_name    = "./output/output_function_4.root";

    // Common
    Double_t untime;
    Double_t tdc;
    Double_t max_ampl[Constants::nCh];
    Double_t min_ampl[Constants::nCh];
    Double_t mean_value_16p[Constants::nCh];
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

    TChain *fChain1 = new TChain("Tree");
    fChain1->Add(input_file_name);

    fChain1->SetBranchAddress("UnixTime",               &untime);
    fChain1->SetBranchAddress("TDC",                    &tdc);
    fChain1->SetBranchAddress("EventID",                &eventid);
    fChain1->SetBranchAddress("MaxAmp",                 max_ampl);
    fChain1->SetBranchAddress("MinAmp",                 min_ampl);
    fChain1->SetBranchAddress("TimeMaxAmp",             time_max_ampl);
    fChain1->SetBranchAddress("TimeMinAmp",             time_min_ampl);
    fChain1->SetBranchAddress("TimeLevel",              time_level);
    fChain1->SetBranchAddress("WidthAtTimeCF",          width_at_level);
    fChain1->SetBranchAddress("MeanValue16Points",      mean_value_16p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    cout<<"--> Input file: "<<input_file_name<<endl;
    Double_t nEntries = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//

    fChain1->GetEntry(0);
    Int_t time_ini      = untime/1000.0;
    Int_t tdc_ini       = (tdc*16*Constants::dTime)/1000000000.0;
    Int_t evnt_ini      = eventid;

    printf("--> time_ini = %20.d\n",time_ini);
    printf("--> tdc_ini = %20.d\n",tdc_ini);
    printf("--> pos_ini = %20.f\n",pos_ini);

    fChain1->GetEntry(nEntries-1);
    Int_t time_fin      = untime/1000.0;
    Int_t tdc_fin       = (tdc*16*Constants::dTime)/1000000000.0;
    Int_t evnt_fin      = eventid;

    printf("--> time_fin = %20.d\n",time_fin);
    printf("--> tdc_fin = %20.d\n",tdc_fin);
    printf("--> pos_fin = %20.f\n",pos_fin);

    TH2D* h_31 = new TH2D("h_31","max_ampl CH[0] vs max_ampl CH[1]",3000,-0.5,2.5,3000,-0.5,2.5);

    TH1D* h_1   = new TH1D("h_1","max_ampl CH[0] (T1+T2)",3000,-0.5,2.5);
    TH1D* h_2   = new TH1D("h_2","max_ampl CH[1] (T1+T2)",3000,-0.5,2.5);
    TH1D* h_3   = new TH1D("h_3","max_ampl CH[2] (T1+T2)",3000,-0.5,2.5);
    TH2D* h_4   = new TH2D("h_4","max_ampl vs untime CH[0] (T1+T2)",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TH2D* h_5   = new TH2D("h_5","max_ampl vs untime CH[1] (T1+T2)",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TH2D* h_6   = new TH2D("h_6","max_ampl vs untime CH[2] (T1+T2)",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TH2D* h_14  = new TH2D("h_14","max_ampl vs tdc CH[0] (T1+T2)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_15  = new TH2D("h_15","max_ampl vs tdc CH[1] (T1+T2)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_24  = new TH2D("h_24","max_ampl vs eventid CH[0] (T1+T2)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TH2D* h_25  = new TH2D("h_25","max_ampl vs eventid CH[1] (T1+T2)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TH1D* h_9   = new TH1D("h_9","charge CH[0] (T1+T2)",1000,0,10);
    TH1D* h_10  = new TH1D("h_10","charge CH[1] (T1+T2)",1000,0,10);
    TH1D* h_11  = new TH1D("h_11","charge CH[2] (T1+T2)",1000,0,10);
    TH2D* h_16  = new TH2D("h_16","max_ampl vs tdc CH[2] (T1+T2)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_26  = new TH2D("h_26","max_ampl vs eventid CH[2] (T1+T2)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);

    TH2D* h_7       = new TH2D("h_7","max_ampl vs untime CH[2] (T1+T2+CpFM)",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TH2D* h_12      = new TH2D("h_12","charge vs untime CH[2] (T1+T2+CpFM)",(time_fin-time_ini),time_ini,time_fin,1000,0,10);
    TH2D* h_17      = new TH2D("h_17","max_ampl vs tdc CH[2] (T1+T2+CpFM)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_19      = new TH2D("h_19","charge vs tdc CH[2] (T1+T2+CpFM)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,1000,0,10);
    TH2D* h_27      = new TH2D("h_27","max_ampl vs eventid CH[2] (T1+T2+CpFM)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TH2D* h_29      = new TH2D("h_29","charge vs eventid CH[2] (T1+T2+CpFM)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,1000,0,10);
    TProfile* h_8   = new TProfile("h_8","profile max_ampl vs untime CH[2] (T1+T2+CpFM)",(time_fin-time_ini),time_ini,time_fin,-0.5,2.5);
    TProfile* h_13  = new TProfile("h_13","profile charge vs untime CH[2] (T1+T2+CpFM)",(time_fin-time_ini),time_ini,time_fin,0,10);
    TProfile* h_18  = new TProfile("h_18","profile max_ampl vs tdc CH[2] (T1+T2+CpFM)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,-0.5,2.5);
    TProfile* h_20  = new TProfile("h_20","profile charge vs tdc CH[2] (T1+T2+CpFM)",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,-0.5,2.5);
    TProfile* h_28  = new TProfile("h_28","profile max_ampl vs eventid CH[2] (T1+T2+CpFM)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,-0.5,2.5);
    TProfile* h_30  = new TProfile("h_30","profile charge vs eventid CH[2] (T1+T2+CpFM)",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,0,10);
    TProfile* h_32   = new TProfile("h_32","profile max_ampl vs position CH[2] (T1+T2+CpFM)",80000,-400,400,-0.5,2.5);

    //--------------------------------------------------------------------------//

    for(Int_t eventID = 0; eventID < nEntries; eventID++)
    {
        fChain1->GetEntry(eventID);

        if(eventID%1000 == 0)
        {
            printf("\r--> Working: %3.1f %%",100*(Double_t)eventID/nEntries);
            fflush(stdout);
        }

        //-------------------------------------------------------------------------------------------------------------------------------------//

        h_31->Fill(max_ampl[1],max_ampl[0]);

        if(max_ampl[0] < 0.10 || max_ampl[0] > 0.20) continue;
        if(max_ampl[1] < 0.02 || max_ampl[1] > 0.12) continue;

        h_1->Fill(max_ampl[0]);
        h_2->Fill(max_ampl[1]);
        h_3->Fill(max_ampl[2]);

        h_4->Fill(untime/1000.0,max_ampl[0]);
        h_5->Fill(untime/1000.0,max_ampl[1]);
        h_6->Fill(untime/1000.0,max_ampl[2]);

        h_9->Fill(charge[0]);
        h_10->Fill(charge[1]);
        h_11->Fill(charge[2]);

        h_14->Fill((tdc*16*Constants::dTime)/1000000000.0,max_ampl[0]);
        h_15->Fill((tdc*16*Constants::dTime)/1000000000.0,max_ampl[1]);
        h_16->Fill((tdc*16*Constants::dTime)/1000000000.0,max_ampl[2]);

        h_24->Fill(eventid,max_ampl[0]);
        h_25->Fill(eventid,max_ampl[1]);
        h_26->Fill(eventid,max_ampl[2]);

        if(max_ampl[2] > 1.20) continue;

        h_7->Fill(untime/1000.0,max_ampl[2]);
        h_8->Fill(untime/1000.0,max_ampl[2]);
        h_12->Fill(untime/1000.0,charge[2]);
        h_13->Fill(untime/1000.0,charge[2]);

        h_17->Fill((tdc*16*Constants::dTime)/1000000000.0,max_ampl[2]);
        h_18->Fill((tdc*16*Constants::dTime)/1000000000.0,max_ampl[2]);
        h_19->Fill((tdc*16*Constants::dTime)/1000000000.0,charge[2]);
        h_20->Fill((tdc*16*Constants::dTime)/1000000000.0,charge[2]);

        h_27->Fill(eventid,max_ampl[2]);
        h_28->Fill(eventid,max_ampl[2]);
        h_29->Fill(eventid,charge[2]);
        h_30->Fill(eventid,charge[2]);

        Double_t a = (pos_fin - pos_ini)/(time_fin - time_ini);
        Double_t b = pos_fin - a*time_fin;
        h_32->Fill((-1)*(a*untime/1000.0 + b),max_ampl[2]);
    }
    cout<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- WRITE -----------------------------------//
    //--------------------------------------------------------------------------//
    cout<<"--> Output file: "<<output_file_name<<endl;
    TFile* file = new TFile(output_file_name,"recreate");

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
    h_15->Write();
    h_16->Write();
    h_17->Write();
    h_18->Write();
    h_19->Write();
    h_20->Write();
    h_24->Write();
    h_25->Write();
    h_26->Write();
    h_27->Write();
    h_28->Write();
    h_29->Write();
    h_30->Write();
    h_31->Write();
    h_32->Write();

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_5()
{
    TString output_file_name    = "./output/output_function_5.root";

    //=============================================================//
    // Angular Scan Single CH
    // 2017_12_12
//    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_12_12.root";
//    TString input_file_motor    = "crystal4_angularscan_2017_12_12.root";
//    TString input_file_blm      = "blm_crystal4_angularscan_2017_12_12.root";
//    Long64_t minUnixTime_run    = 1513133528;
//    Long64_t maxUnixTime_run    = 1513134093;
//    Int_t starting_event        = 24739937 - 10;
//    Double_t blm_norm           = 2000.0;
//    Int_t angLimMin             = 1000;
//    Int_t angLimMax             = 2000;
//    Int_t angBins               = 3000;
    //=============================================================//
    // Angular Scan Single CH
    // 2018_06_18
    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_06_18.root";
    TString input_file_motor    = "crystal1_angularscan_2018_06_18.root";
    TString input_file_blm      = "blm_crystal1_angularscan_2018_06_18.root";
    Long64_t minUnixTime_run    = 1529341636;
    Long64_t maxUnixTime_run    = 1529342007;
    Int_t starting_event        = 0;
    Double_t blm_norm           = 2000.0;
    Int_t angLimMin             = 1000;
    Int_t angLimMax             = 2000;
    Int_t angBins               = 3000;
    //=============================================================//

    // Measurements
    Double_t untime;
    Double_t tdc;
    Double_t max_ampl[Constants::nCh];
    Double_t min_ampl[Constants::nCh];
    Double_t mean_value_16p[Constants::nCh];
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

    TChain *fChain1 = new TChain("Tree");
    fChain1->Add(input_file_meas);

    fChain1->SetBranchAddress("UnixTime",               &untime);
    fChain1->SetBranchAddress("TDC",                    &tdc);
    fChain1->SetBranchAddress("EventID",                &eventid);
    fChain1->SetBranchAddress("MaxAmp",                 max_ampl);
    fChain1->SetBranchAddress("MinAmp",                 min_ampl);
    fChain1->SetBranchAddress("TimeMaxAmp",             time_max_ampl);
    fChain1->SetBranchAddress("TimeMinAmp",             time_min_ampl);
    fChain1->SetBranchAddress("TimeLevel",              time_level);
    fChain1->SetBranchAddress("WidthAtTimeCF",          width_at_level);
    fChain1->SetBranchAddress("MeanValue16Points",      mean_value_16p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    // BLM
    Double_t blm;
    Double_t untime_blm;

    TChain *fChain2 = new TChain("Tree");
    fChain2->Add(input_file_blm);

    fChain2->SetBranchAddress("MotorPosition",  &blm);
    fChain2->SetBranchAddress("UnixTime",       &untime_blm);

    // Motor
    Double_t angle;
    Double_t untime_motor;

    TChain *fChain3 = new TChain("Tree");
    fChain3->Add(input_file_motor);

    fChain3->SetBranchAddress("MotorPosition",  &angle);
    fChain3->SetBranchAddress("UnixTime",       &untime_motor);

    cout<<"--> Input file with measurements: "<<input_file_meas<<endl;
    Double_t nEntries_1 = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries_1<<endl;

    cout<<"--> Input file with blm: "<<input_file_blm<<endl;
    Double_t nEntries_2 = fChain2->GetEntries();
    cout<<"--> nEntries: "<<nEntries_2<<endl;

    cout<<"--> Input file with motor: "<<input_file_motor<<endl;
    Double_t nEntries_3 = fChain3->GetEntries();
    cout<<"--> nEntries: "<<nEntries_3<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//

    TH2D* hh_10 = new TH2D("hh_10","CrystalAngle vs UnixTime",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,angBins,angLimMin,angLimMax);
    TH2D* hh_11 = new TH2D("hh_11","Amplitude vs Angle CH[0]",angBins,angLimMin,angLimMax,3000,-0.5,2.5);
    TH2D* hh_12 = new TH2D("hh_12","Amplitude vs Angle CH[1]",angBins,angLimMin,angLimMax,3000,-0.5,2.5);
    TH2D* hh_13 = new TH2D("hh_13","Amplitude vs Angle CH[2]",angBins,angLimMin,angLimMax,3000,-0.5,2.5);
    TH2D* hh_14 = new TH2D("hh_14","BLM vs Angle",angBins,angLimMin,angLimMax,3000,-1,2);

    TProfile* hprof_1  = new TProfile("hprof_1","Profile of Amplitude vs Angle CH[0]",angBins/10,angLimMin,angLimMax,-1,2);
    TProfile* hprof_2  = new TProfile("hprof_2","Profile of Amplitude vs Angle CH[1]",angBins/10,angLimMin,angLimMax,-1,2);
    TProfile* hprof_3  = new TProfile("hprof_3","Profile of Amplitude vs Angle CH[2]",angBins/10,angLimMin,angLimMax,-1,2);
    TProfile* hprof_4  = new TProfile("hprof_4","Profile of BLM vs Angle",angBins/10,angLimMin,angLimMax,-1,2);

    TGraphErrors* gr_0 = new TGraphErrors();
    gr_0->SetName("gr_0");
    gr_0->SetTitle("Angle");
    Int_t gr_0_iter = 0;

    //--------------------------------------------------------------------------//

    // MOTOR
    for(Int_t eventID = 0; eventID < nEntries_3; eventID++)
    {
        fChain3->GetEntry(eventID);
        untime_motor = untime_motor/1000000.0;

        if(eventID%1 == 0)
        {
            printf("\r--> Working Motor: %3.1f %%",100*(Double_t)eventID/nEntries_3);
            fflush(stdout);
        }

        if(untime_motor < minUnixTime_run || untime_motor > maxUnixTime_run) continue;
        //-------------------------------------------------------------------------------------------------------------------------------------//

        angle = TMath::Abs(angle);

        hh_10->Fill(untime_motor,angle);
        gr_0->SetPoint(gr_0_iter,untime_motor,angle);
        gr_0->SetPointError(gr_0_iter,0.001,0.1);
        gr_0_iter++;
    }
    cout<<endl;

    // MEASUREMENTS

    for(Int_t eventID = starting_event; eventID < nEntries_1; eventID++)
    {
        fChain1->GetEntry(eventID);

        untime = untime/1000000.0;

        if(eventID%1000 == 0)
        {
            printf("\r--> Working Measurements: %3.1f %%",100*(Double_t)eventID/nEntries_1);
            fflush(stdout);
        }
        if(untime < minUnixTime_run || untime > maxUnixTime_run) continue;
//        cout<<"--> starting_event = "<<eventID<<endl; break;
        //-------------------------------------------------------------------------------------------------------------------------------------//

        Double_t angle_temp = gr_0->Eval(untime);

        hh_11->Fill(angle_temp,max_ampl[0]);
        hh_12->Fill(angle_temp,max_ampl[1]);
        hh_13->Fill(angle_temp,max_ampl[2]);

        hprof_1->Fill(angle_temp,max_ampl[0]);
        hprof_2->Fill(angle_temp,max_ampl[1]);
        hprof_3->Fill(angle_temp,max_ampl[2]);
    }
    cout<<endl;

    // BLM
    for(Int_t eventID = 0; eventID < nEntries_2; eventID++)
    {
        fChain2->GetEntry(eventID);

        untime_blm = untime_blm/1000000.0;

        if(eventID%1000 == 0)
        {
            printf("\r--> Working BLM: %3.1f %%",100*(Double_t)eventID/nEntries_2);
            fflush(stdout);
        }
        if(untime_blm < minUnixTime_run || untime_blm > maxUnixTime_run) continue;
        //-------------------------------------------------------------------------------------------------------------------------------------//

        Double_t angle_temp = gr_0->Eval(untime_blm);

        hh_14->Fill(angle_temp,blm/blm_norm);

        hprof_4->Fill(angle_temp,blm/blm_norm);
    }
    cout<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- WRITE -----------------------------------//
    //--------------------------------------------------------------------------//
    cout<<"--> Output file: "<<output_file_name<<endl;
    TFile* file = new TFile(output_file_name,"recreate");

    hh_10->Write();
    hh_11->Write();
    hh_12->Write();
    hh_13->Write();
    hh_14->Write();

    hprof_1->Write();
    hprof_2->Write();
    hprof_3->Write();
    hprof_4->Write();

    gr_0->Write();

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_6()
{
    const Int_t nPhotMax  = 20000;
    const Int_t nFiles    = 80+5;
    Double_t pos[nFiles];

    Int_t _nEntries,_Nhits,_NTotPhot,_nPhot, _reflectionNum[nPhotMax];
    Double_t _Wavelength[nPhotMax];

    TH1D* h_nhits[nFiles];
    TH1D* h_ntotph[nFiles];
    TString f_name, h_name;
    Double_t _MomDirZ[nPhotMax],_PosX[nPhotMax];

    TGraphErrors* gr_nhits = new TGraphErrors();
    gr_nhits->SetName("gr_nhits");
    TGraphErrors* gr_ntotph = new TGraphErrors();
    gr_ntotph->SetName("gr_ntotph");
    TGraphErrors* gr_nratio = new TGraphErrors();
    gr_nratio->SetName("gr_nratio");

    TH2D* h_1 = new TH2D("h_1","MomDirZ vs primPosZ",400,0,400,1800,0,180);
    TH2D* h_2 = new TH2D("h_2","MomDirZ vs PosX",3000,-15,15,1800,0,180);
    TH2D* h_3 = new TH2D("h_3","PosX vs primPosZ",400,0,400,3000,-15,15);
    TH2D* h_4 = new TH2D("h_4","reflectionNum vs primPosZ",400,0,400,1000,0,1000);
    TH2D* h_5 = new TH2D("h_5","reflectionNum vs PosX",3000,-15,15,1000,0,1000);
    TH2D* h_6 = new TH2D("h_6","reflectionNum vs MomDirZ",1800,0,180,1000,0,1000);

    for(Int_t i = 0; i < nFiles; i++)
    {
        if(i <= 4)
        {
            pos[i] = i*1;
        }
        else
        {
            pos[i] = (i - 4)*5;
        }

        f_name = "/media/andrii/F492773C92770302/CpfmDataSim/buildPos2/out_";
        f_name += (int)pos[i];
        f_name += ".root";

        cout<<"--> FileName: "<<f_name<<endl;

        TChain* _tree = new TChain("T");
        _tree->Add(f_name.Data());
        _tree->SetBranchAddress("nPhot",            &_nPhot);
        _tree->SetBranchAddress("Nhits",            &_Nhits);
        _tree->SetBranchAddress("NTotPhot",         &_NTotPhot);
        _tree->SetBranchAddress("MomDirZ",          _MomDirZ);
        _tree->SetBranchAddress("PosX",             _PosX);
        _tree->SetBranchAddress("reflectionNum",    _reflectionNum);
        _tree->SetBranchAddress("Wavelength",       _Wavelength);

        _nEntries = _tree->GetEntries();
        cout<<"--> nEntries = "<<_nEntries<<endl;

        h_name = "h_nhits_";
        h_name += (int)pos[i];
        h_name += "mm";
        h_nhits[i] = new TH1D(h_name.Data(),h_name.Data(),100000,0,100000);

        h_name = "h_ntotph_";
        h_name += (int)pos[i];
        h_name += "mm";
        h_ntotph[i] = new TH1D(h_name.Data(),h_name.Data(),100000,0,100000);

        for(Int_t iEntry = 0; iEntry < _nEntries; iEntry++)
        {
            _tree->GetEntry(iEntry);

            h_nhits[i]->Fill(getNphotonDetect(1,_reflectionNum,_Wavelength,_Nhits));
            h_ntotph[i]->Fill(_NTotPhot);

            for(Int_t iPhot = 0; iPhot < _nPhot; iPhot++)
            {
                if(isPhotonDetected(1,_reflectionNum[iPhot],_Wavelength[iPhot]))
                {
                    if(1)//pos[i] != 1 && pos[i] != 2 && pos[i] != 3 && pos[i] != 4)
                    {
                        h_1->Fill(pos[i],_MomDirZ[iPhot]);
                        h_2->Fill(_PosX[iPhot],_MomDirZ[iPhot]);
                        h_3->Fill(pos[i],_PosX[iPhot]);
                        h_4->Fill(pos[i],_reflectionNum[iPhot]);
                        h_5->Fill(_PosX[i],_reflectionNum[iPhot]);
                        h_6->Fill(_MomDirZ[i],_reflectionNum[iPhot]);
                    }
                }
            }
        }

        _tree->Delete();

        gr_nhits->SetPoint(gr_nhits->GetN(),pos[i],h_nhits[i]->GetMean());
        gr_nhits->SetPointError(gr_nhits->GetN()-1,0.0,h_nhits[i]->GetMeanError());

        gr_ntotph->SetPoint(gr_ntotph->GetN(),pos[i],h_ntotph[i]->GetMean());
        gr_ntotph->SetPointError(gr_ntotph->GetN()-1,0.0,h_ntotph[i]->GetMeanError());

        gr_nratio->SetPoint(gr_nratio->GetN(),pos[i],h_nhits[i]->GetMean()/h_ntotph[i]->GetMean());
        gr_nratio->SetPointError(gr_nratio->GetN()-1,0.0,TMath::Sqrt(TMath::Power(h_nhits[i]->GetMeanError()/h_ntotph[i]->GetMean(),2) +
                                                                     TMath::Power(h_nhits[i]->GetMean()*h_ntotph[i]->GetMeanError()/(h_ntotph[i]->GetMean()*h_ntotph[i]->GetMean()),2)));
    }
    cout<<endl<<endl;

    TFile* file_output = new TFile("./output/output_function_6.root","RECREATE");

    for(Int_t i = 0; i < nFiles; i++)
    {
        h_nhits[i]->Write();
        h_ntotph[i]->Write();
    }
    gr_nhits->Write();
    gr_ntotph->Write();
    gr_nratio->Write();

    h_1->Write();
    h_2->Write();
    h_3->Write();
    h_4->Write();
    h_5->Write();
    h_6->Write();

    cout<<"--> Output filename: "<<file_output->GetName()<<endl;
    file_output->Close();
}

void function_7()
{
    const Int_t nPolish   = 21;
    const Int_t nPhotMax  = 20000;
    const Int_t nFiles    = 79+5;
    Double_t polish[nPolish];
    Double_t pos[nFiles];

    Int_t _nEntries,_Nhits,_NTotPhot,_nPhot, _reflectionNum[nPhotMax];
    Double_t _Wavelength[nPhotMax];

    TH1D* h_nhits[nFiles][nPolish];
    TH1D* h_ntotph[nFiles][nPolish];
    TString f_name, h_name;
    Double_t _MomDirZ[nPhotMax],_PosX[nPhotMax];

    TGraphErrors* gr_nhits[nPolish];
    TGraphErrors* gr_ntotph[nPolish];
    TGraphErrors* gr_nratio[nPolish];

    TString grName;
    for(Int_t polishID = 0; polishID < nPolish; polishID++)
    {
        gr_nhits[polishID] = new TGraphErrors();
        grName = "gr_nhits_";
        grName += polishID;
        gr_nhits[polishID]->SetName(grName.Data());

        gr_ntotph[polishID] = new TGraphErrors();
        grName = "gr_ntotph_";
        grName += polishID;
        gr_ntotph[polishID]->SetName(grName.Data());

        gr_nratio[polishID] = new TGraphErrors();
        grName = "gr_nratio_";
        grName += polishID;
        gr_nratio[polishID]->SetName(grName.Data());

        polish[polishID] = 0.900 + 0.005*polishID;
    }

    for(Int_t fileID = 0; fileID < nFiles; fileID++)
    {
        _rnd->SetSeed(time(NULL));

        if(fileID <= 4)
        {
            pos[fileID] = fileID*1;
        }
        else
        {
            pos[fileID] = (fileID - 4)*5;
        }

        f_name = "/media/andrii/F492773C92770302/CpfmDataSim/buildPos2/out_";
        f_name += (int)pos[fileID];
        f_name += ".root";

        cout<<endl<<"--> FileName: "<<f_name<<endl;

    TChain* _tree = new TChain("T");
    _tree->Add(f_name.Data());
        _tree->SetBranchAddress("nPhot",            &_nPhot);
        _tree->SetBranchAddress("Nhits",            &_Nhits);
        _tree->SetBranchAddress("NTotPhot",         &_NTotPhot);
        _tree->SetBranchAddress("MomDirZ",          _MomDirZ);
        _tree->SetBranchAddress("PosX",             _PosX);
        _tree->SetBranchAddress("reflectionNum",    _reflectionNum);
        _tree->SetBranchAddress("Wavelength",       _Wavelength);

        _nEntries = _tree->GetEntries();
        cout<<"--> nEntries = "<<_nEntries<<endl;

        for(Int_t polishID = 0; polishID < nPolish; polishID++)
        {
            printf("\r----->> Polishing: %1.3f",polish[polishID]);
            fflush(stdout);

            h_name = "h_nhits_";
            h_name += (int)pos[fileID];
            h_name += "mm_";
            h_name += (int)(polish[polishID]*1000);
            h_nhits[fileID][polishID] = new TH1D(h_name.Data(),h_name.Data(),100000,0,100000);

            h_name = "h_ntotph_";
            h_name += (int)pos[fileID];
            h_name += "mm_";
            h_name += (int)(polish[polishID]*1000);
            h_ntotph[fileID][polishID] = new TH1D(h_name.Data(),h_name.Data(),100000,0,100000);

            for(Int_t iEntry = 0; iEntry < _nEntries; iEntry++)
            {
                _tree->GetEntry(iEntry);

                h_nhits[fileID][polishID]->Fill(getNphotonDetect(polish[polishID],_reflectionNum,_Wavelength,_Nhits));
                h_ntotph[fileID][polishID]->Fill(_NTotPhot);
            }

            gr_nhits[polishID]->SetPoint(gr_nhits[polishID]->GetN(),pos[fileID],h_nhits[fileID][polishID]->GetMean());
            gr_nhits[polishID]->SetPointError(gr_nhits[polishID]->GetN()-1,0.0,h_nhits[fileID][polishID]->GetMeanError());

            gr_ntotph[polishID]->SetPoint(gr_ntotph[polishID]->GetN(),pos[fileID],h_ntotph[fileID][polishID]->GetMean());
            gr_ntotph[polishID]->SetPointError(gr_ntotph[polishID]->GetN()-1,0.0,h_ntotph[fileID][polishID]->GetMeanError());

            gr_nratio[polishID]->SetPoint(gr_nratio[polishID]->GetN(),pos[fileID],h_nhits[fileID][polishID]->GetMean()/h_ntotph[fileID][polishID]->GetMean());
            gr_nratio[polishID]->SetPointError(gr_nratio[polishID]->GetN()-1,0.0,TMath::Sqrt(TMath::Power(h_nhits[fileID][polishID]->GetMeanError()/h_ntotph[fileID][polishID]->GetMean(),2) +
                                                                         TMath::Power(h_nhits[fileID][polishID]->GetMean()*h_ntotph[fileID][polishID]->GetMeanError()/(h_ntotph[fileID][polishID]->GetMean()*h_ntotph[fileID][polishID]->GetMean()),2)));

        }

        _tree->Delete();
    }

    TFile* file_output = new TFile("./output/output_function_7.root","RECREATE");

    for(Int_t i = 0; i < nFiles; i++)
    {
        for(Int_t j = 0; j < nPolish; j++)
        {
            h_nhits[i][j]->Write();
            h_ntotph[i][j]->Write();
        }
    }

    for(Int_t j = 0; j < nPolish; j++)
    {
        gr_nhits[j]->Write();
        gr_ntotph[j]->Write();
        gr_nratio[j]->Write();
    }

    cout<<"--> Output filename: "<<file_output->GetName()<<endl;
    file_output->Close();

}

void function_8()
{
    const Int_t nPolish   = 21;

    TFile* _file1 = TFile::Open("./output/output_function_7.root");
    TFile* _file2 = TFile::Open("./output/output_function_4.root");
    cout<<endl;

    if(_file1->IsOpen())
        cout<<"--> The input file ''"<<_file1->GetName()<<"'' has been successfully opened."<<endl;
    else
        cout<<"--> Cannot open the inout file ''"<<_file1->GetName()<<"''"<<endl;
    cout<<endl;

    if(_file2->IsOpen())
        cout<<"--> The input file ''"<<_file2->GetName()<<"'' has been successfully opened."<<endl;
    else
        cout<<"--> Cannot open the inout file ''"<<_file2->GetName()<<"''"<<endl;
    cout<<endl;

    TProfile* prof_data = (TProfile*)_file2->Get("h_32");
    cout<<"--> prof_data BIN: "<<prof_data->GetBinWidth(1)<<endl;
    prof_data->Rebin(100);
    cout<<"--> prof_data BIN: "<<prof_data->GetBinWidth(1)<<endl;

    //=================================================//
    // NORMALIZATION RANGE
    //=================================================//
    Double_t pointAfterZeroIni = 3;
    Double_t pointAfterZeroFin = 9;
    //=================================================//

    TCanvas* c_profdata = new TCanvas("c_profdata","c_profdata");
    c_profdata->cd();
    prof_data->Draw();

    TF1* fit_1 = new TF1("fit_1",fitf,-58,-48,4);
    fit_1->SetParameter(0,0.30);
    fit_1->SetParameter(1,-53.5);
    fit_1->SetParameter(2,0.07);
    fit_1->SetParameter(3,0.40);
    fit_1->SetLineColor(kRed);
    prof_data->Fit(fit_1,"R+");
    cout<<"--> Chi2/ndf ERF = "<<fit_1->GetChisquare()<<"/"<<fit_1->GetNDF()<<endl;
    Double_t par_1[4], errpar_1[4];
    fit_1->GetParameters(&par_1[0]);
    errpar_1[0] = fit_1->GetParError(0);
    errpar_1[1] = fit_1->GetParError(1);
    errpar_1[2] = fit_1->GetParError(2);
    errpar_1[3] = fit_1->GetParError(3);

    //=================================================//
    // NORMALIZATION I
    //=================================================//
    TF1* fit_2 = new TF1("fit_2","pol0",par_1[1]+pointAfterZeroIni,par_1[1]+pointAfterZeroFin);
    fit_2->SetLineColor(kGreen);
    prof_data->Fit(fit_2,"R+");
    cout<<"--> Chi2/ndf POL0 = "<<fit_2->GetChisquare()<<"/"<<fit_2->GetNDF()<<endl;
    Double_t par_2[1], errpar_2[1];
    fit_2->GetParameters(&par_2[0]);
    errpar_2[0] = fit_2->GetParError(0);
    //=================================================//
    // NORMALIZATION II
    //=================================================//
//    par_2[0] = prof_data->GetBinContent(prof_data->FindFirstBinAbove(prof_data->GetMaximum()*0.9,1)     + 3);
//    errpar_2[0] = prof_data->GetBinError(prof_data->FindFirstBinAbove(prof_data->GetMaximum()*0.9,1)    + 3);
    //=================================================//

    TGraphErrors* gr_data = new TGraphErrors();
    gr_data->SetName("gr_data");
    gr_data->SetMarkerStyle(21);
    gr_data->SetMarkerSize(0.5);

    for(Int_t i = 1; i <= prof_data->GetNbinsX(); i++)
    {
        gr_data->SetPoint(gr_data->GetN(),prof_data->GetBinCenter(i)-par_1[1],prof_data->GetBinContent(i)/par_2[0]);
        gr_data->SetPointError(gr_data->GetN()-1,TMath::Sqrt(
                                   TMath::Power(prof_data->GetBinWidth(i)/TMath::Sqrt(12.0),2) +
                                   TMath::Power(errpar_1[1],2)
                                   ),TMath::Sqrt(
                    TMath::Power(prof_data->GetBinError(i)/par_2[0],2) +
                    TMath::Power(prof_data->GetBinContent(i)*errpar_2[0]/(par_2[0]*par_2[0]),2)
                    ));
    }

    TCanvas* c_data = new TCanvas("c_data","c_data");
    c_data->cd();
    gr_data->Draw("AP");

    TF1* fit_3 = new TF1("fit_3","pol0",pointAfterZeroIni,pointAfterZeroFin);
    Double_t par_3[1], errpar_3[1];
    TGraphErrors* gr_nhits[nPolish];
    TMultiGraph* mg_nhits   = new TMultiGraph();

    Double_t nhits_x, nhits_y;
    TString grName;

    for(Int_t polishID = 0; polishID < nPolish; polishID++)
    {
        grName = "gr_nhits_";
        grName += polishID;
        gr_nhits[polishID] = (TGraphErrors*)_file1->Get(grName.Data());

        //=================================================//
        // NORMALIZATION I
        //=================================================//
        gr_nhits[polishID]->Fit(fit_3,"R0Q");
        fit_3->GetParameters(&par_3[0]);
        errpar_3[0] = fit_3->GetParError(0);
        //=================================================//
        // NORMALIZATION II
        //=================================================//
//        gr_nhits[polishID]->GetPoint(4,nhits_x,par_3[0]);
//        errpar_3[0] = gr_nhits[polishID]->GetErrorY(4);
        //=================================================//

        for(Int_t i = 0; i < gr_nhits[polishID]->GetN(); i++)
        {
            gr_nhits[polishID]->GetPoint(i,nhits_x,nhits_y);
            gr_nhits[polishID]->SetPoint(i,nhits_x,nhits_y/par_3[0]);

            gr_nhits[polishID]->SetPointError(i,gr_nhits[polishID]->GetErrorX(i),
                                              TMath::Sqrt(TMath::Power(gr_nhits[polishID]->GetErrorY(i)/par_3[0],2) +
                                              TMath::Power(nhits_y*errpar_3[0]/(par_3[0]*par_3[0]),2)));
        }

        grName.Form("P = %.3f",0.900 + 0.005*polishID);
        gr_nhits[polishID]->SetName(grName.Data());
        gr_nhits[polishID]->SetFillColor(0);
        gr_nhits[polishID]->SetLineColor(polishID + 1);

        if(1)//900 + 5*polishID == 965)
        {
            mg_nhits->Add(gr_nhits[polishID]);
        }
    }

    TH2D* h_chi2_1 = new TH2D("h_chi2_1","#Chi^{2}",50,0,50,nPolish,0.900,1.005);
    TH1D* h_chi2_2 = new TH1D("h_chi2_2","#Sigma #Chi^{2}",nPolish,0.900,1.005);
    Double_t xx,exx,y1,y2,ey1,ey2,polish_temp, chi2, chi2_tot[nPolish] = {};

    for(Int_t j = 0; j < gr_data->GetN(); j++)
    {
        gr_data->GetPoint(j,xx,y1);
        exx = gr_data->GetErrorX(j);
        ey1 = gr_data->GetErrorY(j);

        if(xx < 0 || xx > 50) continue;

        for(Int_t polishID = 0; polishID < nPolish; polishID++)
        {
            polish_temp = 0.900 + 0.005*polishID;

            GetPointGraph(gr_nhits[polishID],xx,exx,y2,ey2);
            chi2 = TMath::Power(y2 - y1,2)/(ey2*ey2 + ey1*ey1);
            chi2_tot[polishID] += chi2;

            h_chi2_1->Fill(xx,polish_temp,chi2);
        }
    }

    for(Int_t polishID = 0; polishID < nPolish; polishID++)
    {
        polish_temp = 0.900 + 0.005*polishID;
        h_chi2_2->Fill(polish_temp,chi2_tot[polishID]);
    }

    TCanvas* c_nhits = new TCanvas("c_nhits","c_nhits");
    c_nhits->cd();
    mg_nhits->Draw("APL");
    c_nhits->BuildLegend();

    TCanvas* c_nhits_data = new TCanvas("c_nhits_data","c_nhits_data");
    c_nhits_data->cd();
    mg_nhits->Draw("APL");
    gr_data->Draw("Psame");
    c_nhits_data->BuildLegend();

    TFile* file_output = new TFile("./output/output_function_8.root","RECREATE");

    c_profdata->Write();
    c_data->Write();
    c_nhits->Write();
    c_nhits_data->Write();
    h_chi2_1->Write();
    h_chi2_2->Write();

    cout<<"--> Output filename: "<<file_output->GetName()<<endl;
    file_output->Close();
}

void function_9()
{
    const Int_t nPolish   = 21;
    const Int_t nWidth    = 21;
    const Int_t nPhotMax  = 20000;
    const Int_t nPosition = 80+5;
    Double_t polish[nPolish];
    Double_t width[nPolish];
    Double_t pos[nPosition];

    Int_t _nEntries,_Nhits,_NTotPhot,_nPhot, _reflectionNum[nPhotMax];
    Double_t _Wavelength[nPhotMax];

    TH1D* h_nhits[nPosition][nPolish][nWidth];
    TH1D* h_ntotph[nPosition][nPolish][nWidth];
    TString f_name, h_name;
    Double_t _MomDirZ[nPhotMax],_PosX[nPhotMax];

    TGraphErrors* gr_nhits[nPolish][nWidth];
    TGraphErrors* gr_ntotph[nPolish][nWidth];
    TGraphErrors* gr_nratio[nPolish][nWidth];

    TString grName;
    for(Int_t polishID = 0; polishID < nPolish; polishID++)
    {
        for(Int_t widthID = 0; widthID < nWidth; widthID++)
        {
            gr_nhits[polishID][widthID] = new TGraphErrors();
            grName = "gr_nhits_";
            grName += polishID;
            grName += "_";
            grName += widthID;
            gr_nhits[polishID][widthID]->SetName(grName.Data());

            gr_ntotph[polishID][widthID] = new TGraphErrors();
            grName = "gr_ntotph_";
            grName += polishID;
            grName += "_";
            grName += widthID;
            gr_ntotph[polishID][widthID]->SetName(grName.Data());

            gr_nratio[polishID][widthID] = new TGraphErrors();
            grName = "gr_nratio_";
            grName += polishID;
            grName += "_";
            grName += widthID;
            gr_nratio[polishID][widthID]->SetName(grName.Data());

            width[widthID] = 0.05*widthID;
        }
        polish[polishID] = 0.900 + 0.005*polishID;
    }

    for(Int_t posID = 0; posID < nPosition; posID++)
    {
        for(Int_t widthID = 0; widthID < nWidth; widthID++)
        {
            _rnd->SetSeed(time(NULL));

            if(posID <= 4)
            {
                pos[posID] = posID*1;
            }
            else
            {
                pos[posID] = (posID - 4)*5;
            }

            f_name.Form("/home/gred/home2/dataSimH8/out_%.0f_%1.1f.root",pos[posID],width[widthID]);
            if(!exists_test(f_name.Data()))
                f_name.Form("/home/gred/home2/dataSimH8/out_%.0f_%1.2f.root",pos[posID],width[widthID]);

            cout<<endl<<"--> FileName: "<<f_name<<endl;

            TChain* _tree = new TChain("T");
            _tree->Add(f_name.Data());
            _tree->SetBranchAddress("nPhot",            &_nPhot);
            _tree->SetBranchAddress("Nhits",            &_Nhits);
            _tree->SetBranchAddress("NTotPhot",         &_NTotPhot);
            _tree->SetBranchAddress("MomDirZ",          _MomDirZ);
            _tree->SetBranchAddress("PosX",             _PosX);
            _tree->SetBranchAddress("reflectionNum",    _reflectionNum);
            _tree->SetBranchAddress("Wavelength",       _Wavelength);

            _nEntries = _tree->GetEntries();
            cout<<"--> nEntries = "<<_nEntries<<endl;

            for(Int_t polishID = 0; polishID < nPolish; polishID++)
            {
                printf("\r----->> Polishing: %1.3f",polish[polishID]);
                fflush(stdout);

                h_name = "h_nhits_";
                h_name += (int)pos[posID];
                h_name += "_";
                h_name += (int)(polish[polishID]*1000);
                h_name += "_";
                h_name += (int)(width[widthID]*100);
                h_nhits[posID][polishID][widthID] = new TH1D(h_name.Data(),h_name.Data(),100000,0,100000);

                h_name = "h_ntotph_";
                h_name += (int)pos[posID];
                h_name += "_";
                h_name += (int)(polish[polishID]*1000);
                h_name += "_";
                h_name += (int)(width[widthID]*100);
                h_ntotph[posID][polishID][widthID] = new TH1D(h_name.Data(),h_name.Data(),100000,0,100000);

                for(Int_t iEntry = 0; iEntry < _nEntries; iEntry++)
                {
                    _tree->GetEntry(iEntry);

                    h_nhits[posID][polishID][widthID]->Fill(getNphotonDetect(polish[polishID],_reflectionNum,_Wavelength,_Nhits));
                    h_ntotph[posID][polishID][widthID]->Fill(_NTotPhot);
                }

                gr_nhits[polishID][widthID]->SetPoint(gr_nhits[polishID][widthID]->GetN(),pos[posID],h_nhits[posID][polishID][widthID]->GetMean());
                gr_nhits[polishID][widthID]->SetPointError(gr_nhits[polishID][widthID]->GetN()-1,0.0,h_nhits[posID][polishID][widthID]->GetMeanError());

                gr_ntotph[polishID][widthID]->SetPoint(gr_ntotph[polishID][widthID]->GetN(),pos[posID],h_ntotph[posID][polishID][widthID]->GetMean());
                gr_ntotph[polishID][widthID]->SetPointError(gr_ntotph[polishID][widthID]->GetN()-1,0.0,h_ntotph[posID][polishID][widthID]->GetMeanError());

                gr_nratio[polishID][widthID]->SetPoint(gr_nratio[polishID][widthID]->GetN(),pos[posID],h_nhits[posID][polishID][widthID]->GetMean()/h_ntotph[posID][polishID][widthID]->GetMean());
                gr_nratio[polishID][widthID]->SetPointError(gr_nratio[polishID][widthID]->GetN()-1,0.0,TMath::Sqrt(TMath::Power(h_nhits[posID][polishID][widthID]->GetMeanError()/h_ntotph[posID][polishID][widthID]->GetMean(),2) +
                                                                                                                   TMath::Power(h_nhits[posID][polishID][widthID]->GetMean()*h_ntotph[posID][polishID][widthID]->GetMeanError()/(h_ntotph[posID][polishID][widthID]->GetMean()*h_ntotph[posID][polishID][widthID]->GetMean()),2)));
            }

            _tree->Delete();
        }
    }

    TFile* file_output = new TFile("./output/output_function_9.root","RECREATE");

    for(Int_t i = 0; i < nPosition; i++)
    {
        for(Int_t j = 0; j < nPolish; j++)
        {
            for(Int_t k = 0; k < nWidth; k++)
            {
                h_nhits[i][j][k]->Write();
                h_ntotph[i][j][k]->Write();
            }
        }
    }

    for(Int_t j = 0; j < nPolish; j++)
    {
        for(Int_t k = 0; k < nWidth; k++)
        {
            gr_nhits[j][k]->Write();
            gr_ntotph[j][k]->Write();
            gr_nratio[j][k]->Write();
        }
    }

    cout<<"--> Output filename: "<<file_output->GetName()<<endl;
    file_output->Close();

}

void function_10()
{
    const Int_t nPolish   = 21;
    const Int_t nWidth    = 21;

    TFile* _file1 = TFile::Open("./output/output_function_9.root");
    TFile* _file2 = TFile::Open("./output/output_function_4.root");
    cout<<endl;

    if(_file1->IsOpen())
        cout<<"--> The input file ''"<<_file1->GetName()<<"'' has been successfully opened."<<endl;
    else
        cout<<"--> Cannot open the inout file ''"<<_file1->GetName()<<"''"<<endl;
    cout<<endl;

    if(_file2->IsOpen())
        cout<<"--> The input file ''"<<_file2->GetName()<<"'' has been successfully opened."<<endl;
    else
        cout<<"--> Cannot open the inout file ''"<<_file2->GetName()<<"''"<<endl;
    cout<<endl;

    TProfile* prof_data = (TProfile*)_file2->Get("h_32");
    cout<<"--> prof_data BIN: "<<prof_data->GetBinWidth(1)<<endl;
    prof_data->Rebin(100);
    cout<<"--> prof_data BIN: "<<prof_data->GetBinWidth(1)<<endl;

    //=================================================//
    // NORMALIZATION RANGE
    //=================================================//
    Double_t pointAfterZeroIni = 3;
    Double_t pointAfterZeroFin = 9;
    //=================================================//

    TCanvas* c_profdata = new TCanvas("c_profdata","c_profdata");
    c_profdata->cd();
    prof_data->Draw();

    TF1* fit_1 = new TF1("fit_1",fitf,-58,-48,4);
    fit_1->SetParameter(0,0.30);
    fit_1->SetParameter(1,-53.5);
    fit_1->SetParameter(2,0.07);
    fit_1->SetParameter(3,0.40);
    fit_1->SetLineColor(kRed);
    prof_data->Fit(fit_1,"R+");
    cout<<"--> Chi2/ndf ERF = "<<fit_1->GetChisquare()<<"/"<<fit_1->GetNDF()<<endl;
    Double_t par_1[4], errpar_1[4];
    fit_1->GetParameters(&par_1[0]);
    errpar_1[0] = fit_1->GetParError(0);
    errpar_1[1] = fit_1->GetParError(1);
    errpar_1[2] = fit_1->GetParError(2);
    errpar_1[3] = fit_1->GetParError(3);

    //=================================================//
    // NORMALIZATION I
    //=================================================//
    TF1* fit_2 = new TF1("fit_2","pol0",par_1[1]+pointAfterZeroIni,par_1[1]+pointAfterZeroFin);
    fit_2->SetLineColor(kGreen);
    prof_data->Fit(fit_2,"R+");
    cout<<"--> Chi2/ndf POL0 = "<<fit_2->GetChisquare()<<"/"<<fit_2->GetNDF()<<endl;
    Double_t par_2[1], errpar_2[1];
    fit_2->GetParameters(&par_2[0]);
    errpar_2[0] = fit_2->GetParError(0);
    //=================================================//
    // NORMALIZATION II
    //=================================================//
//    par_2[0] = prof_data->GetBinContent(prof_data->FindFirstBinAbove(prof_data->GetMaximum()*0.9,1)     + 3);
//    errpar_2[0] = prof_data->GetBinError(prof_data->FindFirstBinAbove(prof_data->GetMaximum()*0.9,1)    + 3);
    //=================================================//

    TGraphErrors* gr_data = new TGraphErrors();
    gr_data->SetName("gr_data");
    gr_data->SetMarkerStyle(21);
    gr_data->SetMarkerSize(0.5);
    gr_data->SetFillColor(0);

    for(Int_t i = 1; i <= prof_data->GetNbinsX(); i++)
    {
        gr_data->SetPoint(gr_data->GetN(),prof_data->GetBinCenter(i)-par_1[1],prof_data->GetBinContent(i)/par_2[0]);
        gr_data->SetPointError(gr_data->GetN()-1,TMath::Sqrt(
                                   TMath::Power(prof_data->GetBinWidth(i)/TMath::Sqrt(12.0),2) +
                                   TMath::Power(errpar_1[1],2)
                                   ),TMath::Sqrt(
                    TMath::Power(prof_data->GetBinError(i)/par_2[0],2) +
                    TMath::Power(prof_data->GetBinContent(i)*errpar_2[0]/(par_2[0]*par_2[0]),2)
                    ));
    }

    TCanvas* c_data = new TCanvas("c_data","c_data");
    c_data->cd();
    gr_data->Draw("AP");

    TF1* fit_3 = new TF1("fit_3","pol0",pointAfterZeroIni,pointAfterZeroFin);
    Double_t par_3[1], errpar_3[1];
    TGraphErrors* gr_nhits[nPolish*nWidth];
    TGraphErrors* gr_nhits_notnorm[nPolish*nWidth];
    TMultiGraph* mg_nhits   = new TMultiGraph();

    Double_t nhits_x, nhits_y;
    TString grName;
    Int_t grID = 0;
    Int_t grID_0, grID_1, grID_2, grID_3;

    for(Int_t polishID = 0; polishID < nPolish; polishID++)
    {
        for(Int_t widthID = 0; widthID < nWidth; widthID++)
        {
            grName = "gr_nhits_";
            grName += polishID;
            grName += "_";
            grName += widthID;
            gr_nhits[grID] = (TGraphErrors*)_file1->Get(grName.Data());
            gr_nhits_notnorm[grID] = (TGraphErrors*)_file1->Get(grName.Data());

            //=================================================//
            // NORMALIZATION I
            //=================================================//
            gr_nhits[grID]->Fit(fit_3,"R0Q");
            fit_3->GetParameters(&par_3[0]);
            errpar_3[0] = fit_3->GetParError(0);
            //=================================================//
            // NORMALIZATION II
            //=================================================//
    //        gr_nhits[grID]->GetPoint(4,nhits_x,par_3[0]);
    //        errpar_3[0] = gr_nhits[grID]->GetErrorY(4);
            //=================================================//

            for(Int_t i = 0; i < gr_nhits[polishID]->GetN(); i++)
            {
                gr_nhits[grID]->GetPoint(i,nhits_x,nhits_y);

                gr_nhits_notnorm[grID]->SetPoint(i,nhits_x,nhits_y);
                gr_nhits[grID]->SetPoint(i,nhits_x,nhits_y/par_3[0]);

                gr_nhits_notnorm[grID]->SetPointError(i,gr_nhits[grID]->GetErrorX(i),gr_nhits[grID]->GetErrorY(i));
                gr_nhits[grID]->SetPointError(i,gr_nhits[grID]->GetErrorX(i),
                                                  TMath::Sqrt(TMath::Power(gr_nhits[grID]->GetErrorY(i)/par_3[0],2) +
                                                  TMath::Power(nhits_y*errpar_3[0]/(par_3[0]*par_3[0]),2)));                
            }

            gr_nhits[grID]->SetName(grName.Data());
            grName += "_notnorm";
            gr_nhits_notnorm[grID]->SetName(grName.Data());
            grName.Form("P = %.3f | W = %.2f",0.900 + 0.005*polishID,0.05*widthID);
            gr_nhits[grID]->SetTitle(grName.Data());
            gr_nhits_notnorm[grID]->SetTitle(grName.Data());
            gr_nhits[grID]->SetFillColor(0);
            gr_nhits[grID]->SetLineColor(grID + 1);

            mg_nhits->Add(gr_nhits[grID]);

            if(polishID == 0 && widthID == 0)
            {
                grID_0 = grID;
                cout<<endl<<"----> polishID == 0 && widthID == 0: "<<grID_0<<endl;
            }

            if(polishID == nPolish-1 && widthID == 0)
            {
                grID_1 = grID;
                cout<<endl<<"----> polishID == nPolish-1 && widthID == 0: "<<grID_1<<endl;
            }

            if(polishID == 0 && widthID == nWidth-1)
            {
                grID_2 = grID;
                cout<<endl<<"----> polishID == 0 && widthID == nWidth-1: "<<grID_2<<endl;
            }

            if(polishID == nPolish-1 && widthID == nWidth-1)
            {
                grID_3 = grID;
                cout<<endl<<"----> polishID == nPolish-1 && widthID == nWidth-1: "<<grID_3<<endl;
            }

            grID++;
        }
    }

    TH2D* h_chi2 = new TH2D("h_chi2","#Chi^{2} vs polish vs width",nWidth,0,0.118785,nPolish,90.0,100.5);
    Double_t xx,exx,y1,y2,ey1,ey2,polish_temp, width_temp, chi2_temp, area_temp;

    Double_t** chi2_tot = new Double_t*[nPolish];
    for(Int_t i = 0; i < nPolish; i++)
    {
        chi2_tot[i] = new Double_t[nWidth];
        for(Int_t j = 0; j < nWidth; j++)
        {
            chi2_tot[i][j] = 0;
        }
    }

    for(Int_t j = 0; j < gr_data->GetN(); j++)
    {
        grID = 0;

        gr_data->GetPoint(j,xx,y1);
        exx = gr_data->GetErrorX(j);
        ey1 = gr_data->GetErrorY(j);

        if(xx < 0 || xx > 50) continue;

        for(Int_t polishID = 0; polishID < nPolish; polishID++)
        {
            for(Int_t widthID = 0; widthID < nWidth; widthID++)
            {
                GetPointGraph(gr_nhits[grID],xx,exx,y2,ey2);
                chi2_temp = TMath::Power(y2 - y1,2)/(ey2*ey2 + ey1*ey1);
                chi2_tot[polishID][widthID] += chi2_temp;
                grID++;
            }
        }
    }

    Double_t angl   = 1.0; // [deg]
    Double_t a      = 10.0; // [mm]
    Double_t L      = 391.7; // [mm]
    Double_t b      = a + 2.0*TMath::Tan(angl*TMath::Pi()/180.0)*L;
    Double_t aa     = a*TMath::Sqrt(2.0);
    Double_t bb     = b*TMath::Sqrt(2.0);
    Double_t x      = (bb - aa)/2.0;
    Double_t LL     = TMath::Sqrt(x*x + L*L);
    Double_t h      = TMath::Sqrt(LL*LL - (b - a)*(b - a)/4.0);
    Double_t S      = (a + b)*h/2.0;

    Double_t min_chi2               =  999;
    Double_t min_chi2_polish        = -999;
    Double_t min_chi2_width         = -999;
    Double_t min_chi2_fractionarea  = -999;
    Int_t min_chi2_grID          = -999;

    grID = 0;

    cout<<endl<<"--> Area <--"<<endl;
    for(Int_t polishID = 0; polishID < nPolish; polishID++)
    {
        for(Int_t widthID = 0; widthID < nWidth; widthID++)
        {
            polish_temp     = 90.0 + 0.5*polishID;
            width_temp      = 0.05*widthID;
            area_temp       = width_temp*LL*TMath::Sin((90.0 - angl)*TMath::Pi()/180.0);
            h_chi2->Fill(2.0*area_temp/S,polish_temp,chi2_tot[polishID][widthID]);

            if(chi2_tot[polishID][widthID] < min_chi2)
            {
                min_chi2                = chi2_tot[polishID][widthID];
                min_chi2_polish         = polish_temp;
                min_chi2_width          = width_temp;
                min_chi2_fractionarea   = 2.0*area_temp/S;
                min_chi2_grID           = grID;
            }

            if(polishID == 0 && widthID == 0)
            {
                cout<<endl<<"----> polishID == 0 && widthID == 0: "<<2.0*area_temp/S<<endl;
                cout<<gr_nhits_notnorm[grID]->GetName()<<endl;
            }

            if(polishID == nPolish-1 && widthID == 0)
            {
                cout<<endl<<"----> polishID == nPolish-1 && widthID == 0: "<<2.0*area_temp/S<<endl;
                cout<<gr_nhits_notnorm[grID]->GetName()<<endl;
            }

            if(polishID == 0 && widthID == nWidth-1)
            {
                cout<<endl<<"----> polishID == 0 && widthID == nWidth-1: "<<2.0*area_temp/S<<endl;
                cout<<gr_nhits_notnorm[grID]->GetName()<<endl;
            }

            if(polishID == nPolish-1 && widthID == nWidth-1)
            {
                cout<<endl<<"----> polishID == nPolish-1 && widthID == nWidth-1: "<<2.0*area_temp/S<<endl;
                cout<<gr_nhits_notnorm[grID]->GetName()<<endl;
            }

            grID++;
        }
    }
    cout<<endl<<"h_chi2->GetXaxis()->GetBinWidth(1) = "<<h_chi2->GetXaxis()->GetBinWidth(1)<<
          endl<<"h_chi2->GetYaxis()->GetBinWidth(1) = "<<h_chi2->GetYaxis()->GetBinWidth(1)<<
          endl<<endl;

    cout<<endl<<"--> min_chi2 = "<<min_chi2<<endl;
    cout<<"--> min_chi2_polish = "<<min_chi2_polish<<endl;
    cout<<"--> min_chi2_width = "<<min_chi2_width<<endl;
    cout<<"--> min_chi2_fractionarea = "<<min_chi2_fractionarea<<endl;
    cout<<"--> min_chi2_grID = "<<min_chi2_grID<<endl<<endl;

    for(Int_t i = 0; i < nPolish; i++)
    {
        delete [] chi2_tot[i];
    }
    delete [] chi2_tot;

    TCanvas* c_nhits = new TCanvas("c_nhits","c_nhits");
    c_nhits->cd();
    mg_nhits->Draw("APL");
    c_nhits->BuildLegend();

    TCanvas* c_nhits_data = new TCanvas("c_nhits_data","c_nhits_data");
    c_nhits_data->cd();
    mg_nhits->Draw("APL");
    gr_data->Draw("Psame");
    c_nhits_data->BuildLegend();

    TCanvas* c_nhits_data_min = new TCanvas("c_nhits_data_min","c_nhits_data_min");
    c_nhits_data_min->cd();
    gr_nhits[min_chi2_grID]->SetLineColor(kRed);
    gr_nhits[min_chi2_grID]->Draw("APL");
    gr_data->Draw("Psame");
    c_nhits_data_min->BuildLegend();

    TFile* file_output = new TFile("./output/output_function_10.root","RECREATE");

    c_profdata->Write();
    c_data->Write();
    c_nhits->Write();
    c_nhits_data->Write();
    h_chi2->Write();
    c_nhits_data_min->Write();
    gr_nhits[min_chi2_grID]->Write();
    gr_data->Write();
    gr_nhits[grID_0]->Write();
    gr_nhits[grID_1]->Write();
    gr_nhits[grID_2]->Write();
    gr_nhits[grID_3]->Write();
    gr_nhits_notnorm[grID_0]->Write();
    gr_nhits_notnorm[grID_1]->Write();
    gr_nhits_notnorm[grID_2]->Write();
    gr_nhits_notnorm[grID_3]->Write();

    cout<<"--> Output filename: "<<file_output->GetName()<<endl;
    file_output->Close();
}

Int_t getNphotonDetect(Double_t polishingQuality, Int_t *reflectionNum, Double_t *Wavelength, Int_t Nhits)
{
    // Bialkali photocathode (Normalized)
    Double_t opticalPhotonWavelength[33] = {299.746185,309.898468,321.065979,330.203033,339.340088,349.492371,358.629456,369.796967,378.934021,
                                           390.101532,400.253815,407.360413,416.497467,428.680206,436.802032,450.000000,458.121826,469.289337,
                                            478.426392,489.593903,498.730957,508.883240,521.065979,529.187805,540.355347,550.507629,560.659912,
                                            569.796936,578.934021,590.101501,599.238586,609.390869,1000.0};

    Double_t opticalPhotonQuantumEff[33] = {0.352165,0.442561,0.502825,0.548023,0.653481,0.713745,0.789076,0.84934,0.92467,1.0,1.0,
                                                1.0,1.0,1.0,1.0,0.984934,0.92467,0.804142,0.698679,0.623353,0.548023,0.442561,0.337099,0.291901,
                                                0.216571,0.216571,0.186439,0.156311,0.126179,0.0809804,0.0508484,0.0357823,0};

    Int_t _nPhotons = 0;

    for(Int_t j = 0; j < Nhits; j++)
    {
        Int_t i;
        for(i = 0; i < 33;i++)
        {
            if(Wavelength[j] < opticalPhotonWavelength[i]) {break;}
        }

        Double_t probability1 = opticalPhotonQuantumEff[i-1] + (opticalPhotonQuantumEff[i] - opticalPhotonQuantumEff[i-1])*
                (Wavelength[j] - opticalPhotonWavelength[i-1])/(opticalPhotonWavelength[i] - opticalPhotonWavelength[i-1]);

        Double_t probability2 = TMath::Power(polishingQuality,reflectionNum[j]);

        if(_rnd->Uniform(0,1) <= probability1*probability2) {_nPhotons++;}
    }

    return _nPhotons;
}

Bool_t isPhotonDetected(Double_t polishingQuality, Int_t reflectionNum, Double_t Wavelength)
{
    // Bialkali photocathode (Normalized)
    Double_t opticalPhotonWavelength[33] = {299.746185,309.898468,321.065979,330.203033,339.340088,349.492371,358.629456,369.796967,378.934021,
                                           390.101532,400.253815,407.360413,416.497467,428.680206,436.802032,450.000000,458.121826,469.289337,
                                            478.426392,489.593903,498.730957,508.883240,521.065979,529.187805,540.355347,550.507629,560.659912,
                                            569.796936,578.934021,590.101501,599.238586,609.390869,1000.0};

    Double_t opticalPhotonQuantumEff[33] = {0.352165,0.442561,0.502825,0.548023,0.653481,0.713745,0.789076,0.84934,0.92467,1.0,1.0,
                                                1.0,1.0,1.0,1.0,0.984934,0.92467,0.804142,0.698679,0.623353,0.548023,0.442561,0.337099,0.291901,
                                                0.216571,0.216571,0.186439,0.156311,0.126179,0.0809804,0.0508484,0.0357823,0};

    Int_t i;
    for(i = 0; i < 33;i++)
    {
        if(Wavelength < opticalPhotonWavelength[i]) {break;}
    }

    Double_t probability1 = opticalPhotonQuantumEff[i-1] + (opticalPhotonQuantumEff[i] - opticalPhotonQuantumEff[i-1])*
            (Wavelength - opticalPhotonWavelength[i-1])/(opticalPhotonWavelength[i] - opticalPhotonWavelength[i-1]);

    Double_t probability2 = TMath::Power(polishingQuality,reflectionNum);

    if(_rnd->Uniform(0,1) <= probability1*probability2) {return kTRUE;}

    return kFALSE;
}

Double_t fitf(Double_t *x,Double_t *par)
{
    Double_t arg = 0;
    if (par[2]!=0) arg = (x[0] - par[1])/(par[2]*TMath::Sqrt(2.0));
    Double_t fitval = par[0]*TMath::Erf(arg) + par[3];
    return fitval;
}

void GetPointGraph(TGraphErrors* gr, Double_t x, Double_t ex, Double_t &y, Double_t &ey)
{
    Int_t i = -1;
    Double_t x_tmp, y_tmp;
    for(i = 0; i < gr->GetN(); i++)
    {
        gr->GetPoint(i,x_tmp,y_tmp);
        if(x_tmp > x) break;
    }
    Double_t x1,y1,x2,y2;
    Double_t ex1,ey1,ex2,ey2;
    gr->GetPoint(i-1,x1,y1);
    ex1 = gr->GetErrorX(i-1);
    ey1 = gr->GetErrorY(i-1);
    gr->GetPoint(i,x2,y2);
    ex2 = gr->GetErrorX(i);
    ey2 = gr->GetErrorY(i);

    Double_t a = (y2-y1)/(x2-x1);
    Double_t ea = TMath::Sqrt( TMath::Power(ey2/(x2-x1),2) +
                               TMath::Power(ey1/(x2-x1),2) +
                               TMath::Power((y2-y1)*ex2/((x2-x1)*(x2-x1)),2) +
                               TMath::Power((y2-y1)*ex1/((x2-x1)*(x2-x1)),2) );
    Double_t b = y2 - a*x2;
    Double_t eb = TMath::Sqrt( TMath::Power(ey2,2) +
                               TMath::Power(ea*x2,2) +
                               TMath::Power(a*ex2,2) );

    y = a*x+b;
    ey = TMath::Sqrt( TMath::Power(ea*x,2) +
                      TMath::Power(a*ex,2) +
                      TMath::Power(eb,2) );

}

inline bool exists_test(const std::string& name)
{
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}
