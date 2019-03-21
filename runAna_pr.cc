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

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout<<endl;
        cout<<"--> 1 >> function_1() -- parking position"<<endl;
        cout<<"--> 2 >> function_2() -- linear scan"<<endl;
        cout<<"--> 3 >> function_3() -- number of particles along the linear scan"<<endl;
        cout<<"--> 4 >> function_4() -- H8 linear scan"<<endl;
        cout<<"--> 5 >> function_5() -- angular scan"<<endl;
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
    // Linear Scan Double CH
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
    // Linear Scan Double CH
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
    // Linear scan double CH 2018_09_17
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
    // Linear scan double CH 2018_11_07
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
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20.root";
//    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20_v2.root";
    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20_2.root";

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
    TH1D* h_1 = new TH1D("h_1","max_ampl CH[0]",3000,-0.5,2.5);
    TH1D* h_2 = new TH1D("h_2","max_ampl CH[1]",3000,-0.5,2.5);
    TH1D* h_3 = new TH1D("h_3","max_ampl CH[2]",3000,-0.5,2.5);

    fChain1->GetEntry(0);
    Int_t time_ini  = untime/1000.0;
    Int_t tdc_ini   = (tdc*16*Constants::dTime)/1000000000.0;
    Int_t evnt_ini  = eventid;
    printf("--> time_ini = %20.d\n",time_ini);
    printf("--> tdc_ini = %20.d\n",tdc_ini);
    fChain1->GetEntry(nEntries-1);
    Int_t time_fin = untime/1000.0;
    Int_t tdc_fin = (tdc*16*Constants::dTime)/1000000000.0;
    Int_t evnt_fin  = eventid;
    printf("--> time_fin = %20.d\n",time_fin);
    printf("--> tdc_fin = %20.d\n",tdc_fin);

    TH2D* h_4 = new TH2D("h_4","max_ampl vs untime CH[0]",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TH2D* h_5 = new TH2D("h_5","max_ampl vs untime CH[1]",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TH2D* h_6 = new TH2D("h_6","max_ampl vs untime CH[2]",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);

    TH2D* h_7 = new TH2D("h_7","max_ampl vs untime CH[2]",(time_fin-time_ini),time_ini,time_fin,3000,-0.5,2.5);
    TProfile* h_8 = new TProfile("h_8","profile max_ampl vs untime CH[2]",(time_fin-time_ini),time_ini,time_fin,-0.5,2.5);

    TH1D* h_9 = new TH1D("h_9","charge CH[0]",1000,0,10);
    TH1D* h_10 = new TH1D("h_10","charge CH[1]",1000,0,10);
    TH1D* h_11 = new TH1D("h_11","charge CH[2]",1000,0,10);
    TH2D* h_12 = new TH2D("h_12","charge vs untime CH[2]",(time_fin-time_ini),time_ini,time_fin,1000,0,10);
    TProfile* h_13 = new TProfile("h_13","profile charge vs untime CH[2]",(time_fin-time_ini),time_ini,time_fin,0,10);

    TH2D* h_14 = new TH2D("h_14","max_ampl vs tdc CH[0]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_15 = new TH2D("h_15","max_ampl vs tdc CH[1]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_16 = new TH2D("h_16","max_ampl vs tdc CH[2]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TH2D* h_17 = new TH2D("h_17","max_ampl vs tdc CH[2]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,3000,-0.5,2.5);
    TProfile* h_18 = new TProfile("h_18","profile max_ampl vs tdc CH[2]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,-0.5,2.5);
    TH2D* h_19 = new TH2D("h_19","charge vs tdc CH[2]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,1000,0,10);
    TProfile* h_20 = new TProfile("h_20","profile charge vs tdc CH[2]",(tdc_fin-tdc_ini),tdc_ini,tdc_fin,-0.5,2.5);

    TH2D* h_24 = new TH2D("h_24","max_ampl vs eventid CH[0]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TH2D* h_25 = new TH2D("h_25","max_ampl vs eventid CH[1]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TH2D* h_26 = new TH2D("h_26","max_ampl vs eventid CH[2]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TH2D* h_27 = new TH2D("h_27","max_ampl vs eventid CH[2]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,3000,-0.5,2.5);
    TProfile* h_28 = new TProfile("h_28","profile max_ampl vs eventid CH[2]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,-0.5,2.5);
    TH2D* h_29 = new TH2D("h_29","charge vs eventid CH[2]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,1000,0,10);
    TProfile* h_30 = new TProfile("h_30","profile charge vs eventid CH[2]",(evnt_fin-evnt_ini+1)/10,evnt_ini,evnt_fin,0,10);

    TH2D* h_31 = new TH2D("h_31","max_ampl CH[0] vs max_ampl CH[1]",3000,-0.5,2.5,3000,-0.5,2.5);
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
        if(max_ampl[2] < 0.01 || max_ampl[2] > 1.20) continue;

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

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_5()
{
    TString output_file_name    = "./output/output_function_2.root";

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
