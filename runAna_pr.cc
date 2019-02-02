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

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout<<endl;
        cout<<"--> 1 >> function_1() -- parking position (18 Oct 2016 12:50:00 - 18 Oct 2016 14:25:00)"<<endl;
        cout<<"--> 2 >> function_2() -- linear scan (18 Oct 2016 18:11:30 - 18 Oct 2016 18:53:30)"<<endl;
        cout<<"--> 3 >> function_3() -- number of particles along the linear scan (18 Oct 2016 18:11:30 - 18 Oct 2016 18:53:30)"<<endl;
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
    default:
      cout<<"--> Nothing to do =)"<<endl;
      break;
    }

    return 0;
}

void function_1()
{
    TString input_file_name     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_10_18.root";
    TString output_file_name    = "./output/output_function_1.root";

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
    fChain1->SetBranchAddress("MeanValue20Points",      mean_value_20p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    // Linear Scan
    Long64_t minUnixTime_run = 1476787800000000;
    Long64_t maxUnixTime_run = 1476793500000000;

    cout<<"--> Input file: "<<input_file_name<<endl;
    Double_t nEntries = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//
    TH1D* h_1 = new TH1D("h_1","max_ampl CH[0]",2500,-0.5,2.0);
    TH1D* h_2 = new TH1D("h_2","max_ampl CH[1]",2500,-0.5,2.0);
    TH1D* h_3 = new TH1D("h_3","max_ampl CH[2]",2500,-0.5,2.0);
    TH1D* h_4 = new TH1D("h_4","charge CH[0]",5000,0,50.0);
    TH1D* h_5 = new TH1D("h_5","charge CH[1]",5000,0,50.0);
    TH1D* h_6 = new TH1D("h_6","charge CH[2]",5000,0,50.0);
    TH2D* h_7 = new TH2D("h_7","charge vs max_ampl CH[1]",2000,0,2.0,5000,0,50.0);
    TH2D* h_8 = new TH2D("h_8","charge vs max_ampl CH[2]",2000,0,2.0,5000,0,50.0);
    TH1D* h_9 = new TH1D("h_9","charge CH[1] (cut)",200000,-1000,1000.0);
    TH1D* h_10 = new TH1D("h_10","charge CH[2] (cut)",200000,-1000,1000.0);
    TH2D* h_11 = new TH2D("h_11","charge vs max_ampl CH[1] (cut)",2000,0,2.0,5000,0,50.0);
    TH2D* h_12 = new TH2D("h_12","charge vs max_ampl CH[2] (cut)",2000,0,2.0,5000,0,50.0);
    TH2D* h_13 = new TH2D("h_13","max_ampl CH[1] vs max_ampl CH[2]",2000,0,2.0,2000,0,2.0);
    TH2D* h_14 = new TH2D("h_14","charge CH[1] vs charge CH[2]",5000,0,50.0,5000,0,50.0);
    TH1D* h_15 = new TH1D("h_15","max_ampl CH[1] (cut)",2500,-0.5,2.0);
    TH1D* h_16 = new TH1D("h_16","max_ampl CH[2] (cut)",2500,-0.5,2.0);
    TH1D* h_17 = new TH1D("h_17","max_ampl CH[1] (cut2)",2500,-0.5,2.0);
    TH1D* h_18 = new TH1D("h_18","max_ampl CH[2] (cut2)",2500,-0.5,2.0);
    //--------------------------------------------------------------------------//

    for(Int_t eventID = 0; eventID < nEntries; eventID++)
    {
        fChain1->GetEntry(eventID);

        for(Int_t i = 0; i < Constants::nCh; i++)
        {
            charge[i]   = charge[i]*Constants::pCtoAu - mean_value_20p[i]*Constants::ChargeLength;
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

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_2()
{
    TString input_file_meas     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_10_18.root";
    TString input_file_rate     = "/media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_rt_2016_10_18.root";
    TString input_file_motor    = "cpfm_linear_scan_1.root";
    TString output_file_name    = "./output/output_function_2.root";

    // Measurements
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
    fChain1->SetBranchAddress("MeanValue20Points",      mean_value_20p);
    fChain1->SetBranchAddress("TimeCF",                 time_cf);
    fChain1->SetBranchAddress("RiseTime",               rise_time);
    fChain1->SetBranchAddress("FallTime",               fall_time);
    fChain1->SetBranchAddress("Charge",                 charge);
    fChain1->SetBranchAddress("NumPeaks",               num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue",           num_peaks_true);

    // Rate
    Int_t eventid_rate;
    Double_t untime_rate;
    Double_t tdc_rate;
    Double_t rate[Constants::nCh];

    TChain *fChain2 = new TChain("Tree");
    fChain2->Add(input_file_rate);

    fChain2->SetBranchAddress("UnixTime",    &untime_rate);
    fChain2->SetBranchAddress("TDC",         &tdc_rate);
    fChain2->SetBranchAddress("EventID",     &eventid_rate);
    fChain2->SetBranchAddress("Rate",        rate);

    // Motor
    Double_t position;
    Double_t untime_motor;

    TChain *fChain3 = new TChain("Tree");
    fChain3->Add(input_file_motor);

    fChain3->SetBranchAddress("MotorPosition",  &position);
    fChain3->SetBranchAddress("UnixTime",       &untime_motor);

    // Linear Scan
    Long64_t minUnixTime_run = 1476807090;
    Long64_t maxUnixTime_run = 1476809610;

    cout<<"--> Input file with measurements: "<<input_file_meas<<endl;
    Double_t nEntries_1 = fChain1->GetEntries();
    cout<<"--> nEntries: "<<nEntries_1<<endl;

    cout<<"--> Input file with rate: "<<input_file_rate<<endl;
    Double_t nEntries_2 = fChain2->GetEntries();
    cout<<"--> nEntries: "<<nEntries_2<<endl;

    cout<<"--> Input file with motor: "<<input_file_motor<<endl;
    Double_t nEntries_3 = fChain3->GetEntries();
    cout<<"--> nEntries: "<<nEntries_3<<endl;

    //--------------------------------------------------------------------------//
    //-------------------------------- HISTOS ----------------------------------//
    //--------------------------------------------------------------------------//
    TH1D* h_1 = new TH1D("h_1","max_ampl CH[0]",2500,-0.5,2.0);
    TH1D* h_2 = new TH1D("h_2","max_ampl CH[1]",2500,-0.5,2.0);
    TH1D* h_3 = new TH1D("h_3","max_ampl CH[2]",2500,-0.5,2.0);
    TH1D* h_4 = new TH1D("h_4","charge CH[0]",5000,0,50.0);
    TH1D* h_5 = new TH1D("h_5","charge CH[1]",5000,0,50.0);
    TH1D* h_6 = new TH1D("h_6","charge CH[2]",5000,0,50.0);
    TH2D* h_7 = new TH2D("h_7","charge vs max_ampl CH[1]",2000,0,2.0,5000,0,50.0);
    TH2D* h_8 = new TH2D("h_8","charge vs max_ampl CH[2]",2000,0,2.0,5000,0,50.0);
    TH1D* h_9 = new TH1D("h_9","charge CH[1] (cut)",200000,-1000,1000.0);
    TH1D* h_10 = new TH1D("h_10","charge CH[2] (cut)",200000,-1000,1000.0);
    TH2D* h_11 = new TH2D("h_11","charge vs max_ampl CH[1] (cut)",2000,0,2.0,5000,0,50.0);
    TH2D* h_12 = new TH2D("h_12","charge vs max_ampl CH[2] (cut)",2000,0,2.0,5000,0,50.0);
    TH2D* h_13 = new TH2D("h_13","max_ampl CH[1] vs max_ampl CH[2]",2000,0,2.0,2000,0,2.0);
    TH2D* h_14 = new TH2D("h_14","charge CH[1] vs charge CH[2]",5000,0,50.0,5000,0,50.0);
    TH1D* h_15 = new TH1D("h_15","max_ampl CH[1] (cut)",2500,-0.5,2.0);
    TH1D* h_16 = new TH1D("h_16","max_ampl CH[2] (cut)",2500,-0.5,2.0);
    TH1D* h_17 = new TH1D("h_17","max_ampl CH[1] (cut2)",2500,-0.5,2.0);
    TH1D* h_18 = new TH1D("h_18","max_ampl CH[2] (cut2)",2500,-0.5,2.0);
    //--------------------------------------------------------------------------//
    TH2D* hh_1 = new TH2D("hh_1","Amplitude vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,2500,-0.5,2.0);
    TH2D* hh_2 = new TH2D("hh_2","Amplitude vs UnixTime CH[1]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,2500,-0.5,2.0);
    TH2D* hh_3 = new TH2D("hh_3","Amplitude vs UnixTime CH[2]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,2500,-0.5,2.0);
    TH2D* hh_4 = new TH2D("hh_4","Charge vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,6000,-10,50.0);
    TH2D* hh_5 = new TH2D("hh_5","Charge vs UnixTime CH[1]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,6000,-10,50.0);
    TH2D* hh_6 = new TH2D("hh_6","Charge vs UnixTime CH[2]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,6000,-10,50.0);
    TH2D* hh_7 = new TH2D("hh_7","Rate vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,1000,0,1e3);
    TH2D* hh_8 = new TH2D("hh_8","Rate vs UnixTime CH[1]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,10000,0,1e7);
    TH2D* hh_9 = new TH2D("hh_9","Rate vs UnixTime CH[2]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,10000,0,1e7);
    TH2D* hh_10 = new TH2D("hh_10","Position vs UnixTime CH[0]",(maxUnixTime_run-minUnixTime_run),minUnixTime_run,maxUnixTime_run,10000,0,100);

    TH2D* hh_11 = new TH2D("hh_11","Amplitude vs Position CH[0]",10000,0,100,2500,-0.5,2.0);
    TH2D* hh_12 = new TH2D("hh_12","Amplitude vs Position CH[1]",10000,0,100,2500,-0.5,2.0);
    TH2D* hh_13 = new TH2D("hh_13","Amplitude vs Position CH[2]",10000,0,100,2500,-0.5,2.0);
    TH2D* hh_14 = new TH2D("hh_14","Charge vs Position CH[0]",10000,0,100,6000,-10,50.0);
    TH2D* hh_15 = new TH2D("hh_15","Charge vs Position CH[1]",10000,0,100,6000,-10,50.0);
    TH2D* hh_16 = new TH2D("hh_16","Charge vs Position CH[2]",10000,0,100,6000,-10,50.0);
    TH2D* hh_17 = new TH2D("hh_17","Rate vs Position CH[0]",10000,0,100,1000,0,1e3);
    TH2D* hh_18 = new TH2D("hh_18","Rate vs Position CH[1]",10000,0,100,10000,0,1e7);
    TH2D* hh_19 = new TH2D("hh_19","Rate vs Position CH[2]",10000,0,100,10000,0,1e7);

    TProfile* hprof_1  = new TProfile("hprof_1","Profile of Amplitude vs Position CH[0]",10000,0,100,-0.5,2.0);
    TProfile* hprof_2  = new TProfile("hprof_2","Profile of Amplitude vs Position CH[1]",10000,0,100,-0.5,2.0);
    TProfile* hprof_3  = new TProfile("hprof_3","Profile of Amplitude vs Position CH[2]",10000,0,100,-0.5,2.0);
    TProfile* hprof_4  = new TProfile("hprof_4","Profile of Charge vs Position CH[0]",10000,0,100,-10,50.0);
    TProfile* hprof_5  = new TProfile("hprof_5","Profile of Charge vs Position CH[1]",10000,0,100,-10,50.0);
    TProfile* hprof_6  = new TProfile("hprof_6","Profile of Charge vs Position CH[2]",10000,0,100,-10,50.0);
    TProfile* hprof_7  = new TProfile("hprof_7","Profile of Rate vs Position CH[0]",10000,0,100,0,1e3);
    TProfile* hprof_8  = new TProfile("hprof_8","Profile of Rate vs Position CH[1]",10000,0,100,0,1e7);
    TProfile* hprof_9  = new TProfile("hprof_9","Profile of Rate vs Position CH[2]",10000,0,100,0,1e7);

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
    if(nEntries_1 != nEntries_2)
    {
        cout<<endl;
        cout<<"--> Different number of Entries: nEntries_1 != nEntries_2 !!!!"<<endl;
        cout<<endl;
        assert(0);
    }

    Int_t starting_event = 2331786-100;
    for(Int_t eventID = starting_event; eventID < nEntries_1; eventID++)
    {
        fChain1->GetEntry(eventID);
        fChain2->GetEntry(eventID);

        for(Int_t i = 0; i < Constants::nCh; i++)
        {
            charge[i]   = charge[i]*Constants::pCtoAu - mean_value_20p[i]*Constants::ChargeLength;
            max_ampl[i] = max_ampl[i] - mean_value_20p[i];
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

        if(eventid != eventid_rate)
        {
            cout<<endl;
            cout<<"--> Different EventID: eventid != eventid_rate !!!!"<<endl;
            cout<<endl;
            assert(0);
        }

        hh_1->Fill(untime,max_ampl[0]);
        hh_2->Fill(untime,max_ampl[1]);
        hh_3->Fill(untime,max_ampl[2]);
        hh_4->Fill(untime,charge[0]);
        hh_5->Fill(untime,charge[1]);
        hh_6->Fill(untime,charge[2]);
        hh_7->Fill(untime,rate[0]);
        hh_8->Fill(untime,rate[1]);
        hh_9->Fill(untime,rate[2]);

        Double_t position = gr_0->Eval(untime);

        hh_11->Fill(position,max_ampl[0]);
        hh_12->Fill(position,max_ampl[1]);
        hh_13->Fill(position,max_ampl[2]);
        hh_14->Fill(position,charge[0]);
        hh_15->Fill(position,charge[1]);
        hh_16->Fill(position,charge[2]);
        hh_17->Fill(position,rate[0]);
        hh_18->Fill(position,rate[1]);
        hh_19->Fill(position,rate[2]);

        hprof_1->Fill(position,max_ampl[0]);
        hprof_2->Fill(position,max_ampl[1]);
        hprof_3->Fill(position,max_ampl[2]);
        hprof_4->Fill(position,charge[0]);
        hprof_5->Fill(position,charge[1]);
        hprof_6->Fill(position,charge[2]);
        hprof_7->Fill(position,rate[0]);
        hprof_8->Fill(position,rate[1]);
        hprof_9->Fill(position,rate[2]);

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

    hh_1->Write();
    hh_2->Write();
    hh_3->Write();
    hh_4->Write();
    hh_5->Write();
    hh_6->Write();
    hh_7->Write();
    hh_8->Write();
    hh_9->Write();
    hh_10->Write();
    hh_11->Write();
    hh_12->Write();
    hh_13->Write();
    hh_14->Write();
    hh_15->Write();
    hh_16->Write();
    hh_17->Write();
    hh_18->Write();
    hh_19->Write();

    hprof_1->Write();
    hprof_2->Write();
    hprof_3->Write();
    hprof_4->Write();
    hprof_5->Write();
    hprof_6->Write();
    hprof_7->Write();
    hprof_8->Write();
    hprof_9->Write();

    file->Write();
    //--------------------------------------------------------------------------//
}

void function_3()
{
    TString input_file_meas     = "./output/output_function_2.root";
    TString output_file_name    = "./output/output_function_3.root";

    const Double_t ampl_cpfm1_pro       = 0.990e-3;
    const Double_t ampl_cpfm1_pro_err   = 0.001e-3;
    const Double_t ampl_cpfm2_pro       = 2.909e-3;
    const Double_t ampl_cpfm2_pro_err   = 0.001e-3;

    const Double_t char_cpfm1_pro       = 0.005;
    const Double_t char_cpfm1_pro_err   = 3.6e-6;
    const Double_t char_cpfm2_pro       = 0.019;
    const Double_t char_cpfm2_pro_err   = 5.9e-6;

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

    TH1D* h_1 = new TH1D("h_1",hprof_1->GetTitle(),10000,0,100);
    TH1D* h_2 = new TH1D("h_2",hprof_2->GetTitle(),10000,0,100);
    TH1D* h_3 = new TH1D("h_3",hprof_3->GetTitle(),10000,0,100);
    TH1D* h_4 = new TH1D("h_4",hprof_4->GetTitle(),10000,0,100);
    TH1D* h_5 = new TH1D("h_5",hprof_5->GetTitle(),10000,0,100);
    TH1D* h_6 = new TH1D("h_6",hprof_6->GetTitle(),10000,0,100);

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
