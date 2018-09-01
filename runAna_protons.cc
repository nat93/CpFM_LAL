//root
#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TProfile.h"
#include "TCanvas.h"
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

const Double_t  rate_time   = 1000000; // mksec
const Int_t     runID       = 1;
const Int_t     prob_npeaks = 5;
// 60% expected
const Double_t  Ap_CpFM_expected[]   = {1,9.306e-3,9.846e-3};
const Double_t  Qp_CpFM_expected[]   = {1,142.5,131.76};
// calculated
const Double_t  Ap_CpFM_calculated[]   = {1,1.03e-3,3.58e-3};
const Double_t  Qp_CpFM_calculated[]   = {1,25.9,118.8};

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [1] - A name of the input .root file with WvF parameters."<<endl;
        cout<<"--> [2] - A name of the output file with histograms."<<endl;
        cout<<"--> [3] - A name of the input .root file with motor position."<<endl;
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
    Double_t position;
    Int_t num_peaks[Constants::nCh];
    Int_t num_peaks_true[Constants::nCh];
    // Per peak
    Double_t max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_level_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t width_at_level_per_peak[Constants::nCh][Constants::nPeakMax];

    TChain *fChain1 = new TChain("Tree");
    TChain *fChain2 = new TChain("Tree");
    fChain1->Add(argv[1]);
    fChain2->Add(argv[3]);

    fChain1->SetBranchAddress("UnixTime", &untime);
    fChain1->SetBranchAddress("TDC", &tdc);
    fChain1->SetBranchAddress("MaxAmp", max_ampl);
    fChain1->SetBranchAddress("MinAmp", min_ampl);
    fChain1->SetBranchAddress("TimeMaxAmp", time_max_ampl);
    fChain1->SetBranchAddress("TimeMinAmp", time_min_ampl);
    fChain1->SetBranchAddress("TimeLevel", time_level);
    fChain1->SetBranchAddress("WidthAtTheLevel", width_at_level);
    fChain1->SetBranchAddress("MeanValue20Points", mean_value_20p);
    fChain1->SetBranchAddress("TimeCF", time_cf);
    fChain1->SetBranchAddress("RiseTime", rise_time);
    fChain1->SetBranchAddress("FallTime", fall_time);
    fChain1->SetBranchAddress("Charge", charge);
    fChain1->SetBranchAddress("NumPeaks", num_peaks);
    fChain1->SetBranchAddress("NumPeaksTrue", num_peaks_true);

    fChain1->SetBranchAddress("MaxAmpPerPeak", max_ampl_per_peak);
    fChain1->SetBranchAddress("TimeMaxAmpPerPeak", time_max_ampl_per_peak);
    fChain1->SetBranchAddress("TimeLevelPerPeak", time_level_per_peak);
    fChain1->SetBranchAddress("WidthAtTheLevelPerPeak", width_at_level_per_peak);

    fChain2->SetBranchAddress("MotorPosition", &position);

    Long64_t minUnixTime_cut, maxUnixTime_cut, minUnixTime_run, maxUnixTime_run;

    switch(runID)
    {
    case 0:
    {
        // Angular scan (crystal 4) 14:47 - 15:00
        minUnixTime_run = 1476794820000000;
        maxUnixTime_run = 1476795600000000;
        minUnixTime_cut = 1476794820000000;
        maxUnixTime_cut = 1476795600000000;
        break;
    }
    case 1:
    {
        // Linear scan (crystal 4) 18:18 - 19:00
        minUnixTime_run = 1476807480000000;
        maxUnixTime_run = 1476810000000000;
        minUnixTime_cut = 1476809260000000;
        maxUnixTime_cut = 1476809710000000;
        break;
    }
    case 2:
    {
        // Linear scan (crystal 1) 21:49 - 22:12
        minUnixTime_run = 1476820140000000;
        maxUnixTime_run = 1476821520000000;
        minUnixTime_cut = 1476820140000000;
        maxUnixTime_cut = 1476821520000000;
        break;
    }
    case 3:
    {
        // Angular scan (crystal 1) 22:24 - 22:37
        minUnixTime_run = 1476822240000000;
        maxUnixTime_run = 1476823020000000;
        minUnixTime_cut = 1476822240000000;
        maxUnixTime_cut = 1476823020000000;
        break;
    }
    case 4:
    {
        // Angular scan (crystal 1) 22:39 - 22:55
        minUnixTime_run = 1476823140000000;
        maxUnixTime_run = 1476824100000000;
        minUnixTime_cut = 1476823140000000;
        maxUnixTime_cut = 1476824100000000;
        break;
    }
    case 5:
    {
        // Linear scan (crystal 1) 23:04 - 23:32
        minUnixTime_run = 1476824640000000;
        maxUnixTime_run = 1476826320000000;
        minUnixTime_cut = 1476824640000000;
        maxUnixTime_cut = 1476826320000000;
        break;
    }
    case 6:
    {
        // Angular scan (crystal 1) 23:35 - 23:53
        minUnixTime_run = 1476826500000000;
        maxUnixTime_run = 1476827580000000;
        minUnixTime_cut = 1476826500000000;
        maxUnixTime_cut = 1476827580000000;
        break;
    }
    case 7:
    {
        // Angular scan (crystal 1) 23:54 - 00:08
        minUnixTime_run = 1476827640000000;
        maxUnixTime_run = 1476828480000000;
        minUnixTime_cut = 1476827640000000;
        maxUnixTime_cut = 1476828480000000;
        break;
    }
    case 8:
    {
        // Linear scan (crystal 1) 00:16 - 00:37
        minUnixTime_run = 1476828960000000;
        maxUnixTime_run = 1476830220000000;
        minUnixTime_cut = 1476828960000000;
        maxUnixTime_cut = 1476830220000000;
        break;
    }
    case 9:
    {
        // Linear scan (crystal 4) 06:39 - 07:13
        minUnixTime_run = 1476851940000000;
        maxUnixTime_run = 1476853980000000;
        minUnixTime_cut = 1476851940000000;
        maxUnixTime_cut = 1476853980000000;
        break;
    }
    case 10:
    {
        // Linear scan (crystal 4) 07:20 - 07:43
        minUnixTime_run = 1476854400000000;
        maxUnixTime_run = 1476855780000000;
        minUnixTime_cut = 1476854400000000;
        maxUnixTime_cut = 1476855780000000;
        break;
    }
    case 11:
    {
        // Angular scan (crystal 4) 07:49 - 07:58
        minUnixTime_run = 1476856140000000;
        maxUnixTime_run = 1476856680000000;
        minUnixTime_cut = 1476856140000000;
        maxUnixTime_cut = 1476856680000000;
        break;
    }
    case 12:
    {
        // Parking position 11:10 - 14:20
        minUnixTime_run = 1476781800000000;
        maxUnixTime_run = 1476793200000000;
        minUnixTime_cut = 1476781800000000;
        maxUnixTime_cut = 1476793200000000;
        break;
    }
    default:
    {
        // All MD
        minUnixTime_run = 1476746592585121;
        maxUnixTime_run = 1476901193794074;
        minUnixTime_cut = 1476746592585121;
        maxUnixTime_cut = 1476901193794074;
        break;
    }
    }

    cout<<"File "<<argv[1]<<" was opened."<<endl;
    cout<<"File "<<argv[3]<<" was opened."<<endl;
    Double_t nEntries = fChain1->GetEntries();
    Double_t nEntries2 = fChain2->GetEntries();
    if(nEntries != nEntries2)
    {
        cout<<"ERROR:: Different numbers of entries: "<<nEntries<<" != "<<nEntries2<<endl;
        assert(0);
    }
    cout<<"The number of Entries:  "<<nEntries<<endl;

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------//
    // WITHOUT CUTS
    TH1D* h1 = new TH1D("max_ampl[0]","Maximum Amplitude of WF CH0",10000,0.0,2.0);
    TH1D* h2 = new TH1D("max_ampl[1]","Maximum Amplitude of WF CH1",10000,0.0,2.0);
    TH1D* h3 = new TH1D("max_ampl[2]","Maximum Amplitude of WF CH2",10000,0.0,2.0);

    TH1D* h4 = new TH1D("time_level[0]","Time at level of WF CH0",10000,-1100.0,400.0);
    TH1D* h5 = new TH1D("time_cf[1]","CF time of max. peak CH1",10000,-1100.0,400.0);
    TH1D* h6 = new TH1D("time_cf[2]","CF time of max. peak CH2",10000,-1100.0,400.0);

    TH1D* h7 = new TH1D("dtime[0]-[1]","Delta (time level of WF) CH0 - (cf time of max. peak) CH1",8000,-400.0,400.0);
    TH1D* h8 = new TH1D("dtime[0]-[2]","Delta (time level of WF) CH0 - (cf time of max. peak) CH2",8000,-400.0,400.0);
    TH1D* h9 = new TH1D("dtime[1]-[2]","Delta (cf time of max. peak) CH1 - (cf time of max. peak) CH2",8000,-400.0,400.0);

    TH1D* h10 = new TH1D("num_peaks[0]","Number of the peaks CH0",1000,0,100);
    TH1D* h11 = new TH1D("num_peaks[1]","Number of the peaks CH1",1000,0,100);
    TH1D* h12 = new TH1D("num_peaks[2]","Number of the peaks CH2",1000,0,100);

    TH1D* h13 = new TH1D("duntime","Delta unix time between events",1000000,0.0,1000000);

    TH1D* h14 = new TH1D("rate[0]","Rate CH0",10000,0.0,200.0);
    TH1D* h15 = new TH1D("rate[1]","Rate CH1",10000,0.0,200.0);
    TH1D* h16 = new TH1D("rate[2]","Rate CH2",10000,0.0,200.0);

    TH2D* h17 = new TH2D("rate_vs_time[0]","Rate vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,1000,0,200);
    TH2D* h18 = new TH2D("rate_vs_time[1]","Rate vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,1000,0,200);
    TH2D* h19 = new TH2D("rate_vs_time[2]","Rate vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,1000,0,200);

    TH2D* h20 = new TH2D("max_ampl_vs_time_level[0]","Maximum Amplitude of WF vs Time at level of WF CH0",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h21 = new TH2D("max_ampl_vs_time_cf[1]","Maximum Amplitude of WF vs CF time of max. peak CH1",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h22 = new TH2D("max_ampl_vs_time_cf[2]","Maximum Amplitude of WF vs CF time of max. peak CH2",4000,0.0,400.0,2000,0.0,2.0);

    TH2D* h23 = new TH2D("max_ampl_vs_time[0]","Maximum Amplitude of WF vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,2000,0.0,2.0);
    TH2D* h24 = new TH2D("max_ampl_vs_time[1]","Maximum Amplitude of WF vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,2000,0.0,2.0);
    TH2D* h25 = new TH2D("max_ampl_vs_time[2]","Maximum Amplitude of WF vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,2000,0.0,2.0);

    TH2D* h26 = new TH2D("num_peaks_vs_time[0]","Number of the peaks vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,2000,0,1000);
    TH2D* h27 = new TH2D("num_peaks_vs_time[1]","Number of the peaks vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,2000,0,1000);
    TH2D* h28 = new TH2D("num_peaks_vs_time[2]","Number of the peaks vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,2000,0,1000);

    TH2D* h29 = new TH2D("max_ampl[1]_vs_dtime[0]-[1]","Maximum Amplitude of WF CH1 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH1",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h30 = new TH2D("max_ampl[2]_vs_dtime[0]-[2]","Maximum Amplitude of WF CH2 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH2",8000,-400.0,400.0,2000,0.0,2.0);

    TH1* h33 = new TH1D("time_level_per_peak[0]","Time at level (per peak) CH0",10000,0,400);
    TH1* h34 = new TH1D("time_level_per_peak[1]","Time at level (per peak) CH1",10000,0,400);
    TH1* h35 = new TH1D("time_level_per_peak[2]","Time at level (per peak) CH2",10000,0,400);

    TH1* h36 = new TH1D("time_level[0] - time_level_per_peak[0]","Time at level of WF CH0 - Time at level (per peak) CH0",10000,0,400);
    TH1* h37 = new TH1D("time_level[0] - time_level_per_peak[1]","Time at level of WF CH0 - Time at level (per peak) CH1",10000,0,400);
    TH1* h38 = new TH1D("time_level[0] - time_level_per_peak[2]","Time at level of WF CH0 - Time at level (per peak) CH2",10000,0,400);

    TH2D* h39 = new TH2D("max_ampl_per_peak[0]_vs_time_level[0]-time_level_per_peak[0]","Maximum Amplitude (per peak) CH0 vs Time at level of WF CH0 - Time at level (per peak) CH0",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h40 = new TH2D("max_ampl_per_peak[1]_vs_time_level[0]-time_level_per_peak[1]","Maximum Amplitude (per peak) CH1 vs Time at level of WF CH0 - Time at level (per peak) CH1",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h41 = new TH2D("max_ampl_per_peak[2]_vs_time_level[0]-time_level_per_peak[2]","Maximum Amplitude (per peak) CH2 vs Time at level of WF CH0 - Time at level (per peak) CH2",8000,-400.0,400.0,2000,0.0,2.0);

    TH2D* h42 = new TH2D("max_ampl_vs_motor_position[0]","Maximum Amplitude of WF vs Motor Position CH0",2000,-100.0,100.0,2000,0.0,2.0);
    TH2D* h43 = new TH2D("max_ampl_vs_motor_position[1]","Maximum Amplitude of WF vs Motor Position CH1",2000,-100.0,100.0,2000,0.0,2.0);
    TH2D* h44 = new TH2D("max_ampl_vs_motor_position[2]","Maximum Amplitude of WF vs Motor Position CH2",2000,-100.0,100.0,2000,0.0,2.0);

    TH2D* h45 = new TH2D("motor_position_vs_time_full","Motor Position vs Full Time",10000,1476746592585121,1476901193794074,2000,-100.0,100.0);

    TH2D* h46[prob_npeaks];
    TH2D* h47[prob_npeaks];
    TH2D* h48[prob_npeaks];
    for(Int_t k = 0; k < prob_npeaks; k++)
    {
        TString title1 = "prob_"; title1 += k; title1 += "_vs_time[0]";
        TString title2 = "prob_"; title2 += k; title2 += "_vs_time[1]";
        TString title3 = "prob_"; title3 += k; title3 += "_vs_time[2]";
        h46[k] = new TH2D(title1.Data(),"Probability vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,1000,0,1);
        h47[k] = new TH2D(title2.Data(),"Probability vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,1000,0,1);
        h48[k] = new TH2D(title3.Data(),"Probability vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,1000,0,1);
    }

    TH2D* h49 = new TH2D("max_ampl[2]_vs_max_ampl[1]","Maximum Amplitude of WF CH2 vs Maximum Amplidute of WF CH1",5000,-0.5,2.0,5000,-0.5,2.0);
    h49->GetXaxis()->SetTitle("MaxAmpl[1]");
    h49->GetYaxis()->SetTitle("MaxAmpl[2]");

    TH1D* h50 = new TH1D("num_peaks_true[0]","Number of the peaks (true) CH0",1000,0,100);
    TH1D* h51 = new TH1D("num_peaks_true[1]","Number of the peaks (true) CH1",1000,0,100);
    TH1D* h52 = new TH1D("num_peaks_true[2]","Number of the peaks (true) CH2",1000,0,100);

    TH1D* h53 = new TH1D("ntruen[0]","N_true/N_total peaks CH0",220,-1.1,1.1);
    TH1D* h54 = new TH1D("ntruen[1]","N_true/N_total peaks CH1",220,-1.1,1.1);
    TH1D* h55 = new TH1D("ntruen[2]","N_true/N_total peaks CH2",220,-1.1,1.1);

    TH1D* h59 = new TH1D("time_max[0]","Time at maximum of WF CH0",10000,-1100.0,400.0);
    TH1D* h60 = new TH1D("time_max[1]","Time at maximum of WF CH1",10000,-1100.0,400.0);
    TH1D* h61 = new TH1D("time_max[2]","Time at maximum of WF CH2",10000,-1100.0,400.0);

    TH1D* h62 = new TH1D("dtime_max[0]-[1]","Delta (time max of WF) CH0 - (time max of WF) CH1",8000,-400.0,400.0);
    TH1D* h63 = new TH1D("dtime_max[0]-[2]","Delta (time max of WF) CH0 - (time max of WF) CH2",8000,-400.0,400.0);
    TH1D* h64 = new TH1D("dtime_max[1]-[2]","Delta (time max of WF) CH1 - (time max of WF) CH2",8000,-400.0,400.0);

    TH2D* h65 = new TH2D("max_ampl_vs_time_max[0]","Maximum Amplitude of WF vs Time of MaxAmpl. of WF CH0",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h66 = new TH2D("max_ampl_vs_time_max[1]","Maximum Amplitude of WF vs Time of MaxAmpl. of WF CH1",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h67 = new TH2D("max_ampl_vs_time_max[2]","Maximum Amplitude of WF vs Time of MaxAmpl. of WF CH2",4000,0.0,400.0,2000,0.0,2.0);

    TH2D* h68 = new TH2D("max_ampl[1]_vs_dtime_max[0]-[1]","Maximum Amplitude of WF CH1 vs Delta (time of maxampl. of WF) CH0 - (time of maxampl. of WF) CH1",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h69 = new TH2D("max_ampl[2]_vs_dtime_max[0]-[2]","Maximum Amplitude of WF CH2 vs Delta (time of maxampl. of WF) CH0 - (time of maxampl. of WF) CH2",8000,-400.0,400.0,2000,0.0,2.0);

    TH2D* h70 = new TH2D("motor_position_vs_untime","Motor Position vs Unix Time",200,minUnixTime_run,maxUnixTime_run,2200,-10.0,100.0);

    TH1D* h71 = new TH1D("charge[0]","Charge of max. peak CH0",10000,50000,70000.0);
    TH1D* h72 = new TH1D("charge[1]","Charge of max. peak CH1",41000,-1000.0,40000.0);
    TH1D* h73 = new TH1D("charge[2]","Charge of max. peak CH2",41000,-1000.0,40000.0);

    TH2D* h74 = new TH2D("charge_max_ampl[0]","Charge of max. peak vs Maximum Amplitude of WF CH0",2000,0.0,2.0,2000,50000,70000.0);
    TH2D* h75 = new TH2D("charge_max_ampl[1]","Charge of max. peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,2000,-1000.0,100000.0);
    TH2D* h76 = new TH2D("charge_max_ampl[2]","Charge of max. peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,2000,-1000.0,100000.0);

    TH2D* h77 = new TH2D("nparticles_vs_motor_position[1]_ampl","Number of Particles vs Motor Position CH1 (from amplitude)",2000,-100.0,100.0,2000,0.0,1000.0);
    TH2D* h78 = new TH2D("nparticles_vs_motor_position[2]_ampl","Number of Particles vs Motor Position CH2 (from amplitude)",2000,-100.0,100.0,2000,0.0,1000.0);

    TH1D* h79 = new TH1D("nparticles[1]_ampl","Number of Particles (from Amplitude) CH1",10000,0.0,1000.0);
    TH1D* h80 = new TH1D("nparticles[2]_ampl","Number of Particles (from Amplitude) CH2",10000,0.0,1000.0);
    TH1D* h81 = new TH1D("nparticles[1]_charge","Number of Particles (from Charge) CH1",10000,0.0,1000.0);
    TH1D* h82 = new TH1D("nparticles[2]_charge","Number of Particles (from Charge) CH2",10000,0.0,1000.0);

    TH2D* h83 = new TH2D("max_ampl_per_peak_vs_max_ampl[1]","Max. Amplitude per peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,2000,-0.5,2.0);
    TH2D* h84 = new TH2D("max_ampl_per_peak_vs_max_ampl[2]","Max. Amplitude per peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,2000,-0.5,2.0);

    TH2D* h85 = new TH2D("dtime_per_peak_vs_max_ampl[1]","Delat Time per peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,6400,-320.0,320.0);
    TH2D* h86 = new TH2D("dtime_per_peak_vs_max_ampl[2]","Delat Time per peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,6400,-320.0,320.0);

    TH2D* h87 = new TH2D("dtime_per_peak_vs_dtime[1]","Delat Time per peak vs Delta Time CH1",6400,-320.0,320.0,6400,-320.0,320.0);
    TH2D* h88 = new TH2D("dtime_per_peak_vs_dtime[2]","Delat Time per peak vs Delat Time CH2",6400,-320.0,320.0,6400,-320.0,320.0);

    TH1D* h89 = new TH1D("width_at_level[0]","Width at level CH0",6400,-320.0,320.0);
    TH1D* h90 = new TH1D("width_at_level[1]","Width at level CH1",6400,-320.0,320.0);
    TH1D* h91 = new TH1D("width_at_level[2]","Width at level CH2",6400,-320.0,320.0);

    TH2D* h92 = new TH2D("width_at_level_vs_max_ampl[0]","Width at level vs Maximum Amplitude of WF CH0",2000,0.0,2.0,6400,-320.0,320.0);
    TH2D* h93 = new TH2D("width_at_level_vs_max_ampl[1]","Width at level vs Maximum Amplitude of WF CH1",2000,0.0,2.0,6400,-320.0,320.0);
    TH2D* h94 = new TH2D("width_at_level_vs_max_ampl[2]","Width at level vs Maximum Amplitude of WF CH2",2000,0.0,2.0,6400,-320.0,320.0);

    TH2D* h95 = new TH2D("width_at_level_vs_charge[0]","Width at level vs Charge of max. peak CH0",2000,-1000.0,100000.0,6400,-320.0,320.0);
    TH2D* h96 = new TH2D("width_at_level_vs_charge[1]","Width at level vs Charge of max. peak CH1",2000,-1000.0,100000.0,6400,-320.0,320.0);
    TH2D* h97 = new TH2D("width_at_level_vs_charge[2]","Width at level vs Charge of max. peak CH2",2000,-1000.0,100000.0,6400,-320.0,320.0);

    TProfile* prof1 = new TProfile("profile_max_ampl_vs_time[0]","Profile: Maximum Amplitude of WF vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0.0,2.0);
    TProfile* prof2 = new TProfile("profile_max_ampl_vs_time[1]","Profile: Maximum Amplitude of WF vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0.0,2.0);
    TProfile* prof3 = new TProfile("profile_max_ampl_vs_time[2]","Profile: Maximum Amplitude of WF vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0.0,2.0);

    TProfile* prof4 = new TProfile("profile_rate_vs_time[0]","Profile: Rate vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof5 = new TProfile("profile_rate_vs_time[1]","Profile: Rate vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof6 = new TProfile("profile_rate_vs_time[2]","Profile: Rate vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0,200);

    TProfile* prof7 = new TProfile("profile_num_peaks_vs_time[0]","Profile: Number of the peaks vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0,1000);
    TProfile* prof8 = new TProfile("profile_num_peaks_vs_time[1]","Profile: Number of the peaks vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0,1000);
    TProfile* prof9 = new TProfile("profile_num_peaks_vs_time[2]","Profile: Number of the peaks vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0,1000);

    TProfile* prof10 = new TProfile("profile_max_ampl_per_peak_vs_peakid[0]","Maximum Amplitude (per peak) vs peak ID CH0",60,-10,50,0.0,2.0);
    TProfile* prof11 = new TProfile("profile_max_ampl_per_peak_vs_peakid[1]","Maximum Amplitude (per peak) vs peak ID CH1",60,-10,50,0.0,2.0);
    TProfile* prof12 = new TProfile("profile_max_ampl_per_peak_vs_peakid[2]","Maximum Amplitude (per peak) vs peak ID CH2",60,-10,50,0.0,2.0);

    TProfile* prof13 = new TProfile("profile_time_level_per_peak_vs_peakid[0]","Arrival time (per peak) vs peak ID CH0",60,-10,50,0.0,400.0);
    TProfile* prof14 = new TProfile("profile_time_level_per_peak_vs_peakid[1]","Arrival time (per peak) vs peak ID CH1",60,-10,50,0.0,400.0);
    TProfile* prof15 = new TProfile("profile_time_level_per_peak_vs_peakid[2]","Arrival time (per peak) vs peak ID CH2",60,-10,50,0.0,400.0);

    TProfile* prof16 = new TProfile("profile_max_ampl_per_peak_vs_time_level_per_peak[0]","Maximum Amplitude (per peak) vs Arrival time (per peak) CH0",4000,0.0,400.0,0.0,2.0);
    TProfile* prof17 = new TProfile("profile_max_ampl_per_peak_vs_time_level_per_peak[1]","Maximum Amplitude (per peak) vs Arrival time (per peak) CH1",4000,0.0,400.0,0.0,2.0);
    TProfile* prof18 = new TProfile("profile_max_ampl_per_peak_vs_time_level_per_peak[2]","Maximum Amplitude (per peak) vs Arrival time (per peak) CH2",4000,0.0,400.0,0.0,2.0);

    TProfile* prof19 = new TProfile("profile_max_ampl[1]_vs_dtime[0]-[1]","Profile: Maximum Amplitude of WF CH1 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH1",8000,-400.0,400.0,0.0,2.0);
    TProfile* prof20 = new TProfile("profile_max_ampl[2]_vs_dtime[0]-[2]","Profile: Maximum Amplitude of WF CH2 vs Delta (time level of WF) CH0 - (cf time of max. peaks) CH2",8000,-400.0,400.0,0.0,2.0);

    TProfile* prof21 = new TProfile("profile_max_ampl[2]_vs_max_ampl[1]","Profile: Maximum Amplitude of WF CH2 vs Maximum Amplidute of WF CH1",5000,-0.5,2.0,-0.5,2.0);
    prof21->GetXaxis()->SetTitle("MaxAmpl[1]");
    prof21->GetYaxis()->SetTitle("MaxAmpl[2]");

    TProfile* prof22 = new TProfile("profile_max_ampl[1]_vs_dtime_max[0]-[1]","Profile: Maximum Amplitude of WF CH1 vs Delta (time of maxampl. of max. peak) CH0 - (time of maxampl. of max. peak) CH1",8000,-400.0,400.0,0.0,2.0);
    TProfile* prof23 = new TProfile("profile_max_ampl[2]_vs_dtime_max[0]-[2]","Profile: Maximum Amplitude of WF CH2 vs Delta (time of maxampl. of max. peak) CH0 - (time of maxampl. of max. peak) CH2",8000,-400.0,400.0,0.0,2.0);

    TProfile* prof24 = new TProfile("profile_rate_true_vs_time[0]","Profile: Rate_true vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof25 = new TProfile("profile_rate_true_vs_time[1]","Profile: Rate_true vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof26 = new TProfile("profile_rate_true_vs_time[2]","Profile: Rate_true vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0,200);

    TProfile* prof27 = new TProfile("profile_charge_max_ampl[0]","Profile: Charge of max. peak vs Maximum Amplitude of WF CH0",2000,0.0,2.0,50000,70000);
    TProfile* prof28 = new TProfile("profile_charge_max_ampl[1]","Profile: Charge of max. peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,-1000.0,100000.0);
    TProfile* prof29 = new TProfile("profile_charge_max_ampl[2]","Profile: Charge of max. peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,-1000.0,100000.0);

    TProfile* prof30 = new TProfile("profile_nParticles_vs_time[1]_ampl_expected","Profile: Number of particles vs Unix Time CH1 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof31 = new TProfile("profile_nParticles_vs_time[2]_ampl_expected","Profile: Number of particles vs Unix Time CH2 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof32 = new TProfile("profile_nParticles_vs_time[1]_charge_expected","Profile: Number of particles vs Unix Time CH1 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof33 = new TProfile("profile_nParticles_vs_time[2]_charge_expected","Profile: Number of particles vs Unix Time CH2 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);

    TProfile* prof34 = new TProfile("profile_nParticles_vs_time[1]_ampl_calculated","Profile: Number of particles vs Unix Time CH1 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof35 = new TProfile("profile_nParticles_vs_time[2]_ampl_calculated","Profile: Number of particles vs Unix Time CH2 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof36 = new TProfile("profile_nParticles_vs_time[1]_charge_calculated","Profile: Number of particles vs Unix Time CH1 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof37 = new TProfile("profile_nParticles_vs_time[2]_charge_calculated","Profile: Number of particles vs Unix Time CH2 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);

    TProfile* prof38 = new TProfile("profile_nparticles_vs_motor_position[1]_ampl_calculated","Profile: Number of Particles vs Motor Position CH1 (from Amplitude)",10000,0.0,100.0,0.0,1000.0);
    TProfile* prof39 = new TProfile("profile_nparticles_vs_motor_position[2]_ampl_calculated","Profile: Number of Particles vs Motor Position CH2 (from Amplitude)",10000,0.0,100.0,0.0,1000.0);
    TProfile* prof40 = new TProfile("profile_nparticles_vs_motor_position[1]_charge_calculated","Profile: Number of Particles vs Motor Position CH1 (from Charge)",10000,0.0,100.0,0.0,1000.0);
    TProfile* prof41 = new TProfile("profile_nparticles_vs_motor_position[2]_charge_calculated","Profile: Number of Particles vs Motor Position CH2 (from Chareg)",10000,0.0,100.0,0.0,1000.0);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------//
    // WITH CUTS
    TH1D* h1_cut = new TH1D("max_ampl[0]_cut","Maximum Amplitude of WF CH0",10000,0.0,2.0);
    TH1D* h2_cut = new TH1D("max_ampl[1]_cut","Maximum Amplitude of WF CH1",10000,0.0,2.0);
    TH1D* h3_cut = new TH1D("max_ampl[2]_cut","Maximum Amplitude of WF CH2",10000,0.0,2.0);

    TH1D* h4_cut = new TH1D("time_level[0]_cut","Time at level of WF CH0",10000,-1100.0,400.0);
    TH1D* h5_cut = new TH1D("time_cf[1]_cut","CF time of max. peak CH1",10000,-1100.0,400.0);
    TH1D* h6_cut = new TH1D("time_cf[2]_cut","CF time of max. peak CH2",10000,-1100.0,400.0);

    TH1D* h7_cut = new TH1D("dtime[0]-[1]_cut","Delta (time level of WF) CH0 - (cf time of max. peak) CH1",8000,-400.0,400.0);
    TH1D* h8_cut = new TH1D("dtime[0]-[2]_cut","Delta (time level of WF) CH0 - (cf time of max. peak) CH2",8000,-400.0,400.0);
    TH1D* h9_cut = new TH1D("dtime[1]-[2]_cut","Delta (cf time of max. peak) CH1 - (cf time of max. peak) CH2",8000,-400.0,400.0);

    TH1D* h10_cut = new TH1D("num_peaks[0]_cut","Number of the peaks CH0",1000,0,100);
    TH1D* h11_cut = new TH1D("num_peaks[1]_cut","Number of the peaks CH1",1000,0,100);
    TH1D* h12_cut = new TH1D("num_peaks[2]_cut","Number of the peaks CH2",1000,0,100);

    TH1D* h13_cut = new TH1D("duntime_cut","Delta unix time between events",1000000,0.0,1000000);

    TH1D* h14_cut = new TH1D("rate[0]_cut","Rate CH0",10000,0.0,200.0);
    TH1D* h15_cut = new TH1D("rate[1]_cut","Rate CH1",10000,0.0,200.0);
    TH1D* h16_cut = new TH1D("rate[2]_cut","Rate CH2",10000,0.0,200.0);

    TH2D* h17_cut = new TH2D("rate_vs_time[0]_cut","Rate vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,1000,0,200);
    TH2D* h18_cut = new TH2D("rate_vs_time[1]_cut","Rate vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,1000,0,200);
    TH2D* h19_cut = new TH2D("rate_vs_time[2]_cut","Rate vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,1000,0,200);

    TH2D* h20_cut = new TH2D("max_ampl_vs_time_level[0]_cut","Maximum Amplitude of WF vs Time at level of WF CH0",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h21_cut = new TH2D("max_ampl_vs_time_cf[1]_cut","Maximum Amplitude of WF vs CF time  of max. peak CH1",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h22_cut = new TH2D("max_ampl_vs_time_cf[2]_cut","Maximum Amplitude of WF vs CF time  of max. peak CH2",4000,0.0,400.0,2000,0.0,2.0);

    TH2D* h23_cut = new TH2D("max_ampl_vs_time[0]_cut","Maximum Amplitude of WF vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,2000,0.0,2.0);
    TH2D* h24_cut = new TH2D("max_ampl_vs_time[1]_cut","Maximum Amplitude of WF vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,2000,0.0,2.0);
    TH2D* h25_cut = new TH2D("max_ampl_vs_time[2]_cut","Maximum Amplitude of WF vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,2000,0.0,2.0);

    TH2D* h26_cut = new TH2D("num_peaks_vs_time[0]_cut","Number of the peaks vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,2000,0,1000);
    TH2D* h27_cut = new TH2D("num_peaks_vs_time[1]_cut","Number of the peaks vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,2000,0,1000);
    TH2D* h28_cut = new TH2D("num_peaks_vs_time[2]_cut","Number of the peaks vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,2000,0,1000);

    TH2D* h29_cut = new TH2D("max_ampl[1]_vs_dtime[0]-[1]_cut","Maximum Amplitude of WF CH1 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH1",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h30_cut = new TH2D("max_ampl[2]_vs_dtime[0]-[2]_cut","Maximum Amplitude of WF CH2 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH2",8000,-400.0,400.0,2000,0.0,2.0);

    TH1* h33_cut = new TH1D("time_level_per_peak[0]_cut","Time at level (per peak) CH0",10000,0,400);
    TH1* h34_cut = new TH1D("time_level_per_peak[1]_cut","Time at level (per peak) CH1",10000,0,400);
    TH1* h35_cut = new TH1D("time_level_per_peak[2]_cut","Time at level (per peak) CH2",10000,0,400);

    TH1* h36_cut = new TH1D("time_level[0] - time_level_per_peak[0]_cut","Time at level of WF CH0 - Time at level (per peak) CH0",10000,0,400);
    TH1* h37_cut = new TH1D("time_level[0] - time_level_per_peak[1]_cut","Time at level of WF CH0 - Time at level (per peak) CH1",10000,0,400);
    TH1* h38_cut = new TH1D("time_level[0] - time_level_per_peak[2]_cut","Time at level of WF CH0 - Time at level (per peak) CH2",10000,0,400);

    TH2D* h39_cut = new TH2D("max_ampl_per_peak[0]_vs_time_level[0]-time_level_per_peak[0]_cut","Maximum Amplitude (per peak) CH0 vs Time at level of WF CH0 - Time at level (per peak) CH0",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h40_cut = new TH2D("max_ampl_per_peak[1]_vs_time_level[0]-time_level_per_peak[1]_cut","Maximum Amplitude (per peak) CH1 vs Time at level of WF CH0 - Time at level (per peak) CH1",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h41_cut = new TH2D("max_ampl_per_peak[2]_vs_time_level[0]-time_level_per_peak[2]_cut","Maximum Amplitude (per peak) CH2 vs Time at level of WF CH0 - Time at level (per peak) CH2",8000,-400.0,400.0,2000,0.0,2.0);

    TH2D* h42_cut = new TH2D("max_ampl_vs_motor_position[0]_cut","Maximum Amplitude of WF vs Motor Position CH0",2000,-100.0,100.0,2000,0.0,2.0);
    TH2D* h43_cut = new TH2D("max_ampl_vs_motor_position[1]_cut","Maximum Amplitude of WF vs Motor Position CH1",2000,-100.0,100.0,2000,0.0,2.0);
    TH2D* h44_cut = new TH2D("max_ampl_vs_motor_position[2]_cut","Maximum Amplitude of WF vs Motor Position CH2",2000,-100.0,100.0,2000,0.0,2.0);

    TH2D* h46_cut[prob_npeaks];
    TH2D* h47_cut[prob_npeaks];
    TH2D* h48_cut[prob_npeaks];
    for(Int_t k = 0; k < prob_npeaks; k++)
    {
        TString title1 = "prob_"; title1 += k; title1 += "_vs_time[0]_cut";
        TString title2 = "prob_"; title2 += k; title2 += "_vs_time[1]_cut";
        TString title3 = "prob_"; title3 += k; title3 += "_vs_time[2]_cut";
        h46_cut[k] = new TH2D(title1.Data(),"Probability vs Time CH0",10000,minUnixTime_run,maxUnixTime_run,1000,0,1);
        h47_cut[k] = new TH2D(title2.Data(),"Probability vs Time CH1",10000,minUnixTime_run,maxUnixTime_run,1000,0,1);
        h48_cut[k] = new TH2D(title3.Data(),"Probability vs Time CH2",10000,minUnixTime_run,maxUnixTime_run,1000,0,1);
    }

    TH2D* h49_cut = new TH2D("max_ampl[2]_vs_max_ampl[1]_cut","Maximum Amplitude of WF CH2 vs Maximum Amplidute of WF CH1",5000,-0.5,2.0,5000,-0.5,2.0);
    h49_cut->GetXaxis()->SetTitle("MaxAmpl[1]");
    h49_cut->GetYaxis()->SetTitle("MaxAmpl[2]");

    TH1D* h50_cut = new TH1D("num_peaks_true[0]_cut","Number of the peaks (true) CH0",1000,0,100);
    TH1D* h51_cut = new TH1D("num_peaks_true[1]_cut","Number of the peaks (true) CH1",1000,0,100);
    TH1D* h52_cut = new TH1D("num_peaks_true[2]_cut","Number of the peaks (true) CH2",1000,0,100);

    TH1D* h53_cut = new TH1D("ntruen[0]_cut","N_true/N_total peaks CH0",220,-1.1,1.1);
    TH1D* h54_cut = new TH1D("ntruen[1]_cut","N_true/N_total peaks CH1",220,-1.1,1.1);
    TH1D* h55_cut = new TH1D("ntruen[2]_cut","N_true/N_total peaks CH2",220,-1.1,1.1);

    TH1D* h59_cut = new TH1D("time_max[0]_cut","Time at maximum CH0",10000,-1100.0,400.0);
    TH1D* h60_cut = new TH1D("time_max[1]_cut","Time at maximum CH1",10000,-1100.0,400.0);
    TH1D* h61_cut = new TH1D("time_max[2]_cut","Time at maximum CH2",10000,-1100.0,400.0);

    TH1D* h62_cut = new TH1D("dtime_max[0]-[1]_cut","Delta (time max of WF) CH0 - (time max of WF) CH1",8000,-400.0,400.0);
    TH1D* h63_cut = new TH1D("dtime_max[0]-[2]_cut","Delta (time max of WF) CH0 - (time max of WF) CH2",8000,-400.0,400.0);
    TH1D* h64_cut = new TH1D("dtime_max[1]-[2]_cut","Delta (time max of WF) CH1 - (time max of WF) CH2",8000,-400.0,400.0);

    TH2D* h65_cut = new TH2D("max_ampl_vs_time_max[0]_cut","Maximum Amplitude of WF vs Time of MaxAmpl. of WF CH0",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h66_cut = new TH2D("max_ampl_vs_time_max[1]_cut","Maximum Amplitude of WF vs Time of MaxAmpl. of WF CH1",4000,0.0,400.0,2000,0.0,2.0);
    TH2D* h67_cut = new TH2D("max_ampl_vs_time_max[2]_cut","Maximum Amplitude of WF vs Time of MaxAmpl. of WF CH2",4000,0.0,400.0,2000,0.0,2.0);

    TH2D* h68_cut = new TH2D("max_ampl[1]_vs_dtime_max[0]-[1]_cut","Maximum Amplitude of WF CH1 vs Delta (time of maxampl. of WF) CH0 - (time of maxampl. of WF) CH1",8000,-400.0,400.0,2000,0.0,2.0);
    TH2D* h69_cut = new TH2D("max_ampl[2]_vs_dtime_max[0]-[2]_cut","Maximum Amplitude of WF CH2 vs Delta (time of maxampl. of WF) CH0 - (time of maxampl. of WF) CH2",8000,-400.0,400.0,2000,0.0,2.0);

    TH2D* h70_cut = new TH2D("motor_position_vs_untime_cut","Motor Position vs Unix Time",200,minUnixTime_run,maxUnixTime_run,2200,-10.0,100.0);

    TH1D* h71_cut = new TH1D("charge[0]_cut","Charge of max. peak CH0",10000,50000,70000.0);
    TH1D* h72_cut = new TH1D("charge[1]_cut","Charge of max. peak CH1",41000,-1000.0,40000.0);
    TH1D* h73_cut = new TH1D("charge[2]_cut","Charge of max. peak CH2",41000,-1000.0,40000.0);

    TH2D* h74_cut = new TH2D("charge_max_ampl[0]_cut","Charge of max. peak vs Maximum Amplitude of WF CH0",2000,0.0,2.0,2000,50000,70000.0);
    TH2D* h75_cut = new TH2D("charge_max_ampl[1]_cut","Charge of max. peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,2000,-1000.0,100000.0);
    TH2D* h76_cut = new TH2D("charge_max_ampl[2]_cut","Charge of max. peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,2000,-1000.0,100000.0);

    TH2D* h77_cut = new TH2D("nparticles_vs_motor_position[1]_ampl_cut","Number of Particles vs Motor Position CH1 (from amplitude)",2000,-100.0,100.0,2000,0.0,1000.0);
    TH2D* h78_cut = new TH2D("nparticles_vs_motor_position[2]_ampl_cut","Number of Particles vs Motor Position CH2 (from amplitude)",2000,-100.0,100.0,2000,0.0,1000.0);

    TH1D* h79_cut = new TH1D("nparticles[1]_ampl_cut","Number of Particles (from Amplitude) CH1",10000,0.0,1000.0);
    TH1D* h80_cut = new TH1D("nparticles[2]_ampl_cut","Number of Particles (from Amplitude) CH2",10000,0.0,1000.0);
    TH1D* h81_cut = new TH1D("nparticles[1]_charge_cut","Number of Particles (from Charge) CH1",10000,0.0,1000.0);
    TH1D* h82_cut = new TH1D("nparticles[2]_charge_cut","Number of Particles (from Charge) CH2",10000,0.0,1000.0);

    TH2D* h83_cut = new TH2D("max_ampl_per_peak_vs_max_ampl[1]_cut","Max. Amplitude per peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,2000,-0.5,2.0);
    TH2D* h84_cut = new TH2D("max_ampl_per_peak_vs_max_ampl[2]_cut","Max. Amplitude per peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,2000,-0.5,2.0);

    TH2D* h85_cut = new TH2D("dtime_per_peak_vs_max_ampl[1]_cut","Delat Time per peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,6400,-320.0,320.0);
    TH2D* h86_cut = new TH2D("dtime_per_peak_vs_max_ampl[2]_cut","Delat Time per peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,6400,-320.0,320.0);

    TH2D* h87_cut = new TH2D("dtime_per_peak_vs_dtime[1]_cut","Delat Time per peak vs Delta Time CH1",6400,-320.0,320.0,6400,-320.0,320.0);
    TH2D* h88_cut = new TH2D("dtime_per_peak_vs_dtime[2]_cut","Delat Time per peak vs Delat Time CH2",6400,-320.0,320.0,6400,-320.0,320.0);

    TH1D* h89_cut = new TH1D("width_at_level[0]_cut","Width at level CH0",6400,-320.0,320.0);
    TH1D* h90_cut = new TH1D("width_at_level[1]_cut","Width at level CH1",6400,-320.0,320.0);
    TH1D* h91_cut = new TH1D("width_at_level[2]_cut","Width at level CH2",6400,-320.0,320.0);

    TH2D* h92_cut = new TH2D("width_at_level_vs_max_ampl[0]_cut","Width at level vs Maximum Amplitude of WF CH0",2000,0.0,2.0,6400,-320.0,320.0);
    TH2D* h93_cut = new TH2D("width_at_level_vs_max_ampl[1]_cut","Width at level vs Maximum Amplitude of WF CH1",2000,0.0,2.0,6400,-320.0,320.0);
    TH2D* h94_cut = new TH2D("width_at_level_vs_max_ampl[2]_cut","Width at level vs Maximum Amplitude of WF CH2",2000,0.0,2.0,6400,-320.0,320.0);

    TH2D* h95_cut = new TH2D("width_at_level_vs_charge[0]_cut","Width at level vs Charge of max. peak CH0",2000,-1000.0,100000.0,6400,-320.0,320.0);
    TH2D* h96_cut = new TH2D("width_at_level_vs_charge[1]_cut","Width at level vs Charge of max. peak CH1",2000,-1000.0,100000.0,6400,-320.0,320.0);
    TH2D* h97_cut = new TH2D("width_at_level_vs_charge[2]_cut","Width at level vs Charge of max. peak CH2",2000,-1000.0,100000.0,6400,-320.0,320.0);

    TProfile* prof1_cut = new TProfile("profile_max_ampl_vs_time[0]_cut","Profile: Maximum Amplitude of WF vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0.0,2.0);
    TProfile* prof2_cut = new TProfile("profile_max_ampl_vs_time[1]_cut","Profile: Maximum Amplitude of WF vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0.0,2.0);
    TProfile* prof3_cut = new TProfile("profile_max_ampl_vs_time[2]_cut","Profile: Maximum Amplitude of WF vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0.0,2.0);

    TProfile* prof4_cut = new TProfile("profile_rate_vs_time[0]_cut","Profile: Rate vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof5_cut = new TProfile("profile_rate_vs_time[1]_cut","Profile: Rate vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof6_cut = new TProfile("profile_rate_vs_time[2]_cut","Profile: Rate vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0,200);

    TProfile* prof7_cut = new TProfile("profile_num_peaks_vs_time[0]_cut","Profile: Number of the peaks vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0,1000);
    TProfile* prof8_cut = new TProfile("profile_num_peaks_vs_time[1]_cut","Profile: Number of the peaks vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0,1000);
    TProfile* prof9_cut = new TProfile("profile_num_peaks_vs_time[2]_cut","Profile: Number of the peaks vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0,1000);

    TProfile* prof10_cut = new TProfile("profile_max_ampl_per_peak_vs_peakid[0]_cut","Maximum Amplitude (per peak) vs peak ID CH0",60,-10,50,0.0,2.0);
    TProfile* prof11_cut = new TProfile("profile_max_ampl_per_peak_vs_peakid[1]_cut","Maximum Amplitude (per peak) vs peak ID CH1",60,-10,50,0.0,2.0);
    TProfile* prof12_cut = new TProfile("profile_max_ampl_per_peak_vs_peakid[2]_cut","Maximum Amplitude (per peak) vs peak ID CH2",60,-10,50,0.0,2.0);

    TProfile* prof13_cut = new TProfile("profile_time_level_per_peak_vs_peakid[0]_cut","Arrival time (per peak) vs peak ID CH0",60,-10,50,0.0,400.0);
    TProfile* prof14_cut = new TProfile("profile_time_level_per_peak_vs_peakid[1]_cut","Arrival time (per peak) vs peak ID CH1",60,-10,50,0.0,400.0);
    TProfile* prof15_cut = new TProfile("profile_time_level_per_peak_vs_peakid[2]_cut","Arrival time (per peak) vs peak ID CH2",60,-10,50,0.0,400.0);

    TProfile* prof16_cut = new TProfile("profile_max_ampl_per_peak_vs_time_level_per_peak[0]_cut","Maximum Amplitude (per peak) vs Arrival time (per peak) CH0",4000,0.0,400.0,0.0,2.0);
    TProfile* prof17_cut = new TProfile("profile_max_ampl_per_peak_vs_time_level_per_peak[1]_cut","Maximum Amplitude (per peak) vs Arrival time (per peak) CH1",4000,0.0,400.0,0.0,2.0);
    TProfile* prof18_cut = new TProfile("profile_max_ampl_per_peak_vs_time_level_per_peak[2]_cut","Maximum Amplitude (per peak) vs Arrival time (per peak) CH2",4000,0.0,400.0,0.0,2.0);

    TProfile* prof19_cut = new TProfile("profile_max_ampl[1]_vs_dtime[0]-[1]_cut","Profile: Maximum Amplitude of WF CH1 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH1",8000,-400.0,400.0,0.0,2.0);
    TProfile* prof20_cut = new TProfile("profile_max_ampl[2]_vs_dtime[0]-[2]_cut","Profile: Maximum Amplitude of WF CH2 vs Delta (time level of WF) CH0 - (cf time of max. peak) CH2",8000,-400.0,400.0,0.0,2.0);

    TProfile* prof21_cut = new TProfile("profile_max_ampl[2]_vs_max_ampl[1]_cut","Profile: Maximum Amplitude of WF CH2 vs Maximum Amplidute of WF CH1",5000,-0.5,2.0,-0.5,2.0);
    prof21_cut->GetXaxis()->SetTitle("MaxAmpl[1]");
    prof21_cut->GetYaxis()->SetTitle("MaxAmpl[2]");

    TProfile* prof22_cut = new TProfile("profile_max_ampl[1]_vs_dtime_max[0]-[1]_cut","Profile: Maximum Amplitude of WF CH1 vs Delta (time of maxampl. of max. peak) CH0 - (time of maxampl. of max. peak) CH1",8000,-400.0,400.0,0.0,2.0);
    TProfile* prof23_cut = new TProfile("profile_max_ampl[2]_vs_dtime_max[0]-[2]_cut","Profile: Maximum Amplitude of WF CH2 vs Delta (time of maxampl. of max. peak) CH0 - (time of maxampl. of max. peak) CH2",8000,-400.0,400.0,0.0,2.0);

    TProfile* prof24_cut = new TProfile("profile_rate_true_vs_time[0]_cut","Profile: Rate_true vs Time CH0",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof25_cut = new TProfile("profile_rate_true_vs_time[1]_cut","Profile: Rate_true vs Time CH1",200,minUnixTime_run,maxUnixTime_run,0,200);
    TProfile* prof26_cut = new TProfile("profile_rate_true_vs_time[2]_cut","Profile: Rate_true vs Time CH2",200,minUnixTime_run,maxUnixTime_run,0,200);

    TProfile* prof27_cut = new TProfile("profile_charge_max_ampl[0]_cut","Profile: Charge of max. peak vs Maximum Amplitude of WF CH0",2000,0.0,2.0,50000.0,70000.0);
    TProfile* prof28_cut = new TProfile("profile_charge_max_ampl[1]_cut","Profile: Charge of max. peak vs Maximum Amplitude of WF CH1",2000,-0.5,2.0,-1000.0,100000.0);
    TProfile* prof29_cut = new TProfile("profile_charge_max_ampl[2]_cut","Profile: Charge of max. peak vs Maximum Amplitude of WF CH2",2000,-0.5,2.0,-1000.0,100000.0);

    TProfile* prof30_cut = new TProfile("profile_nParticles_vs_time[1]_ampl_expected_cut","Profile: Number of particles vs Unix Time CH1 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof31_cut = new TProfile("profile_nParticles_vs_time[2]_ampl_expected_cut","Profile: Number of particles vs Unix Time CH2 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof32_cut = new TProfile("profile_nParticles_vs_time[1]_charge_expected_cut","Profile: Number of particles vs Unix Time CH1 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof33_cut = new TProfile("profile_nParticles_vs_time[2]_charge_expected_cut","Profile: Number of particles vs Unix Time CH2 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);

    TProfile* prof34_cut = new TProfile("profile_nParticles_vs_time[1]_ampl_calculated_cut","Profile: Number of particles vs Unix Time CH1 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof35_cut = new TProfile("profile_nParticles_vs_time[2]_ampl_calculated_cut","Profile: Number of particles vs Unix Time CH2 (from Amplitude)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof36_cut = new TProfile("profile_nParticles_vs_time[1]_charge_calculated_cut","Profile: Number of particles vs Unix Time CH1 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);
    TProfile* prof37_cut = new TProfile("profile_nParticles_vs_time[2]_charge_calculated_cut","Profile: Number of particles vs Unix Time CH2 (from Charge)",200,minUnixTime_run,maxUnixTime_run,-100,2000);

    TProfile* prof38_cut = new TProfile("profile_nparticles_vs_motor_position[1]_ampl_calculated_cut","Profile: Number of Particles vs Motor Position CH1 (from Amplitude)",10000,0.0,100.0,0.0,1000.0);
    TProfile* prof39_cut = new TProfile("profile_nparticles_vs_motor_position[2]_ampl_calculated_cut","Profile: Number of Particles vs Motor Position CH2 (from Amplitude)",10000,0.0,100.0,0.0,1000.0);
    TProfile* prof40_cut = new TProfile("profile_nparticles_vs_motor_position[1]_charge_calculated_cut","Profile: Number of Particles vs Motor Position CH1 (from Charge)",10000,0.0,100.0,0.0,1000.0);
    TProfile* prof41_cut = new TProfile("profile_nparticles_vs_motor_position[2]_charge_calculated_cut","Profile: Number of Particles vs Motor Position CH2 (from Chareg)",10000,0.0,100.0,0.0,1000.0);

    Int_t rate[Constants::nCh] = {};
    Int_t rate_true[Constants::nCh] = {};
    Long64_t oldval = 0, newval = 0;    
    Double_t start_untime = 0, stop_untime = 0;
    Int_t divider[Constants::nCh] = {};
    Int_t prob[Constants::nCh][5];
    Int_t nEventsSelected = 0;

    Int_t rate_cut[Constants::nCh] = {};
    Int_t rate_true_cut[Constants::nCh] = {};
    Long64_t oldval_cut = 0, newval_cut = 0;
    Double_t start_untime_cut[Constants::nCh] = {}, stop_untime_cut[Constants::nCh] = {};
    Int_t divider_cut[Constants::nCh] = {};
    Int_t prob_cut[Constants::nCh][5];
    Int_t nEventsSelected_cut[Constants::nCh+1] = {};

    const Int_t NbinsProb = 100;
    Int_t Ncpfm1Prob[NbinsProb] = {};
    Int_t Ncpfm2Prob[NbinsProb] = {};
    Double_t CpFM1Probability[NbinsProb] = {};
    Double_t errCpFM1Probability[NbinsProb] = {};

    fChain1->GetEntry(0);
    start_untime = untime;
    for(Int_t i = 0; i < Constants::nCh; i++)
    {        
        start_untime_cut[i] = untime;
        for(Int_t j = 0; j < prob_npeaks; j++)
        {
            prob[i][j] = 0;
            prob_cut[i][j] = 0;
        }
    }

    oldval = untime;
    oldval_cut = untime;

    Double_t AstepProb = 0.020;
    Int_t nEventsOnPosition1_ampl_cut = 0;
    Int_t nEventsOnPosition2_ampl_cut = 0;
    Double_t AmaxCpFM1[NbinsProb] = {};
    Double_t AmaxCpFM2[NbinsProb] = {};
    Double_t errAmaxCpFM1[NbinsProb] = {};
    Double_t errAmaxCpFM2[NbinsProb] = {};
    Int_t NafterpulsesAmplCpFM1[NbinsProb] = {};
    Int_t NafterpulsesAmplCpFM2[NbinsProb] = {};

    Int_t Ntrig = 0;
    Int_t Ncpfm_ampl_1 = 0;
    Int_t Ncpfm_ampl_2 = 0;
    Int_t Ncpfm_charge_1 = 0;
    Int_t Ncpfm_charge_2 = 0;

    for(Int_t eventID = 0; eventID < nEntries; eventID++)
    {
        fChain1->GetEntry(eventID);
        fChain2->GetEntry(eventID);

        h45->Fill(untime,position);

        Int_t div = 0.05*nEntries;
        if (eventID%div == 0)
        {
            cout<<"--> "<<100.0*eventID/nEntries<<" % "<<endl;
        }
        //if(untime < minUnixTime_run || untime > maxUnixTime_run) continue;
        if(untime < minUnixTime_run || untime > maxUnixTime_run) continue;
        //-------------------------------------------------------------------------------------------------------------------------------------//
        // WITHOUT CUTS

        newval = untime;
        h13->Fill(newval - oldval);
        oldval = newval;

        h1->Fill(max_ampl[0]);
        h2->Fill(max_ampl[1]);
        h3->Fill(max_ampl[2]);

        h4->Fill(time_level[0]);
        h5->Fill(time_cf[1]);
        h6->Fill(time_cf[2]);

        h7->Fill(time_level[0]-time_cf[1]);
        h8->Fill(time_level[0]-time_cf[2]);
        h9->Fill(time_cf[1]-time_cf[2]);

        h10->Fill(num_peaks[0]);
        h11->Fill(num_peaks[1]);
        h12->Fill(num_peaks[2]);

        stop_untime = untime;
        for(Int_t nChID = 0; nChID < Constants::nCh; nChID++)
        {
            if(max_ampl[nChID] >= Constants::Level[nChID])
            {
                rate[nChID] += num_peaks[nChID];
                rate_true[nChID] += num_peaks_true[nChID];
            }
            for(Int_t k = 0; k < prob_npeaks; k++)
            {
                if(num_peaks[nChID] == k)
                {
                    prob[nChID][k]++;
                }
            }
            divider[nChID]++;
        }

        if(stop_untime - start_untime > rate_time)
        {
            h14->Fill(1000000.0*rate[0]/(stop_untime - start_untime));
            h15->Fill(1000000.0*rate[1]/(stop_untime - start_untime));
            h16->Fill(1000000.0*rate[2]/(stop_untime - start_untime));

            h17->Fill(untime,1000000.0*rate[0]/(stop_untime - start_untime));
            h18->Fill(untime,1000000.0*rate[1]/(stop_untime - start_untime));
            h19->Fill(untime,1000000.0*rate[2]/(stop_untime - start_untime));

            prof4->Fill(untime,1000000.0*rate[0]/(stop_untime - start_untime),1);
            prof5->Fill(untime,1000000.0*rate[1]/(stop_untime - start_untime),1);
            prof6->Fill(untime,1000000.0*rate[2]/(stop_untime - start_untime),1);

            prof24->Fill(untime,1000000.0*rate_true[0]/(stop_untime - start_untime),1);
            prof25->Fill(untime,1000000.0*rate_true[1]/(stop_untime - start_untime),1);
            prof26->Fill(untime,1000000.0*rate_true[2]/(stop_untime - start_untime),1);

            for(Int_t k = 0; k < 5; k++)
            {
                h46[k]->Fill(untime,(double)prob[0][k]/divider[0]);
                h47[k]->Fill(untime,(double)prob[1][k]/divider[1]);
                h48[k]->Fill(untime,(double)prob[2][k]/divider[2]);
            }

            for(Int_t nChID = 0; nChID < Constants::nCh; nChID++)
            {
                rate[nChID] = 0;
                rate_true[nChID] = 0;
                for(Int_t j = 0; j < prob_npeaks; j++)
                {
                    prob[nChID][j] = 0;
                }
                divider[nChID] = 0;
            }
            start_untime = stop_untime;
        }

        h20->Fill(time_level[0],max_ampl[0]);
        h21->Fill(time_cf[1],max_ampl[1]);
        h22->Fill(time_cf[2],max_ampl[2]);

        h23->Fill(untime,max_ampl[0]);
        h24->Fill(untime,max_ampl[1]);
        h25->Fill(untime,max_ampl[2]);

        prof1->Fill(untime,max_ampl[0],1);
        prof2->Fill(untime,max_ampl[1],1);
        prof3->Fill(untime,max_ampl[2],1);

        h26->Fill(untime,num_peaks[0]);
        h27->Fill(untime,num_peaks[1]);
        h28->Fill(untime,num_peaks[2]);

        prof7->Fill(untime,num_peaks[0],1);
        prof8->Fill(untime,num_peaks[1],1);
        prof9->Fill(untime,num_peaks[2],1);

        h29->Fill(time_level[0]-time_cf[1],max_ampl[1]);
        h30->Fill(time_level[0]-time_cf[2],max_ampl[2]);

        prof19->Fill(time_level[0]-time_cf[1],max_ampl[1],1);
        prof20->Fill(time_level[0]-time_cf[2],max_ampl[2],1);

        h42->Fill(position,max_ampl[0]);
        h43->Fill(position,max_ampl[1]);
        h44->Fill(position,max_ampl[2]);

        h49->Fill(max_ampl[1],max_ampl[2]);
        prof21->Fill(max_ampl[1],max_ampl[2],1);

        h50->Fill(num_peaks_true[0]);
        h51->Fill(num_peaks_true[1]);
        h52->Fill(num_peaks_true[2]);

        h53->Fill((double)num_peaks_true[0]/num_peaks[0]);
        h54->Fill((double)num_peaks_true[1]/num_peaks[1]);
        h55->Fill((double)num_peaks_true[2]/num_peaks[2]);

        h59->Fill(time_max_ampl[0]);
        h60->Fill(time_max_ampl[1]);
        h61->Fill(time_max_ampl[2]);

        h62->Fill(time_max_ampl[0]-time_max_ampl[1]);
        h63->Fill(time_max_ampl[0]-time_max_ampl[2]);
        h64->Fill(time_max_ampl[1]-time_max_ampl[2]);

        h65->Fill(time_max_ampl[0],max_ampl[0]);
        h66->Fill(time_max_ampl[1],max_ampl[1]);
        h67->Fill(time_max_ampl[2],max_ampl[2]);

        h68->Fill(time_max_ampl[0]-time_max_ampl[1],max_ampl[1]);
        h69->Fill(time_max_ampl[0]-time_max_ampl[2],max_ampl[2]);

        prof22->Fill(time_max_ampl[0]-time_max_ampl[1],max_ampl[1],1);
        prof23->Fill(time_max_ampl[0]-time_max_ampl[2],max_ampl[2],1);

        h70->Fill(untime,position);

        h71->Fill(charge[0]);
        h72->Fill(charge[1]);
        h73->Fill(charge[2]);

        h74->Fill(max_ampl[0],charge[0]);
        h75->Fill(max_ampl[1],charge[1]);
        h76->Fill(max_ampl[2],charge[2]);

        for(Int_t i = 0; i < num_peaks_true[1]; i++)
        {
            //if(max_ampl_per_peak[1][i] == max_ampl[1]) continue;
            h83->Fill(max_ampl[1],max_ampl_per_peak[1][i]);
            h85->Fill(max_ampl[1],time_level[0]-time_level_per_peak[1][i]);
            h87->Fill(time_level[0]-time_cf[1],time_level[0]-time_level_per_peak[1][i]);
        }
        for(Int_t i = 0; i < num_peaks_true[1]; i++)
        {
            //if(max_ampl_per_peak[2][i] == max_ampl[2]) continue;
            h84->Fill(max_ampl[2],max_ampl_per_peak[2][i]);
            h86->Fill(max_ampl[2],time_level[0]-time_level_per_peak[2][i]);
            h88->Fill(time_level[0]-time_cf[2],time_level[0]-time_level_per_peak[2][i]);
        }

        h89->Fill(width_at_level[0]);
        h90->Fill(width_at_level[1]);
        h91->Fill(width_at_level[2]);

        h92->Fill(max_ampl[0],width_at_level[0]);
        h93->Fill(max_ampl[1],width_at_level[1]);
        h94->Fill(max_ampl[2],width_at_level[2]);

        h95->Fill(charge[0],width_at_level[0]);
        h96->Fill(charge[1],width_at_level[1]);
        h97->Fill(charge[2],width_at_level[2]);

        prof27->Fill(max_ampl[0],charge[0],1);
        prof28->Fill(max_ampl[1],charge[1],1);
        prof29->Fill(max_ampl[2],charge[2],1);        

        prof30->Fill(untime,max_ampl[1]/Ap_CpFM_expected[1],1);
        prof31->Fill(untime,max_ampl[2]/Ap_CpFM_expected[2],1);
        prof32->Fill(untime,charge[1]/Qp_CpFM_expected[1],1);
        prof33->Fill(untime,charge[2]/Qp_CpFM_expected[2],1); 


        prof34->Fill(untime,max_ampl[1]/Ap_CpFM_calculated[1],1);
        prof35->Fill(untime,max_ampl[2]/Ap_CpFM_calculated[2],1);
        prof36->Fill(untime,charge[1]/Qp_CpFM_calculated[1],1);
        prof37->Fill(untime,charge[2]/Qp_CpFM_calculated[2],1);       

        h77->Fill(position,max_ampl[1]/Ap_CpFM_calculated[1]);
        h78->Fill(position,max_ampl[2]/Ap_CpFM_calculated[2]);

        prof38->Fill(position,max_ampl[1]/Ap_CpFM_calculated[1],1);
        prof39->Fill(position,max_ampl[2]/Ap_CpFM_calculated[2],1);
        prof40->Fill(position,charge[1]/Qp_CpFM_calculated[1],1);
        prof41->Fill(position,charge[2]/Qp_CpFM_calculated[2],1);       

        if(position > Constants::posMinLim && position < Constants::posMaxLim)
        {
            h79->Fill(max_ampl[1]/Ap_CpFM_calculated[1]);
            h81->Fill(charge[1]/Qp_CpFM_calculated[1]);
        }
        if(position > Constants::posMinLim+6.0 && position < Constants::posMaxLim+6.0)
        {
            h80->Fill(max_ampl[2]/Ap_CpFM_calculated[2]);
            h82->Fill(charge[2]/Qp_CpFM_calculated[2]);
        }

        for(Int_t peakID = 0; peakID < num_peaks[0]; peakID++)
        {
            prof10->Fill(peakID,max_ampl_per_peak[0][peakID],1);
            prof13->Fill(peakID,time_level_per_peak[0][peakID],1);
            prof16->Fill(time_level_per_peak[0][peakID],max_ampl_per_peak[0][peakID],1);

            h33->Fill(time_level_per_peak[0][peakID]);
            h36->Fill(time_level[0] - time_level_per_peak[0][peakID]);
            h39->Fill(time_level[0] - time_level_per_peak[0][peakID],max_ampl_per_peak[0][peakID]);
        }

        for(Int_t peakID = 0; peakID < num_peaks[1]; peakID++)
        {
            prof11->Fill(peakID,max_ampl_per_peak[1][peakID],1);
            prof14->Fill(peakID,time_level_per_peak[1][peakID],1);
            prof17->Fill(time_level_per_peak[1][peakID],max_ampl_per_peak[1][peakID],1);

            h34->Fill(time_level_per_peak[1][peakID]);
            h37->Fill(time_level[0] - time_level_per_peak[1][peakID]);
            h40->Fill(time_level[0] - time_level_per_peak[1][peakID],max_ampl_per_peak[1][peakID]);
        }

        for(Int_t peakID = 0; peakID < num_peaks[2]; peakID++)
        {
            prof12->Fill(peakID,max_ampl_per_peak[2][peakID],1);
            prof15->Fill(peakID,time_level_per_peak[2][peakID],1);
            prof18->Fill(time_level_per_peak[2][peakID],max_ampl_per_peak[2][peakID],1);

            h35->Fill(time_level_per_peak[2][peakID]);
            h38->Fill(time_level[0] - time_level_per_peak[2][peakID]);
            h41->Fill(time_level[0] - time_level_per_peak[2][peakID],max_ampl_per_peak[2][peakID]);
        }

        nEventsSelected++;

        //-------------------------------------------------------------------------------------------------------------------------------------//
        // WITH CUTS

        if(untime < minUnixTime_run || untime > maxUnixTime_run) continue;

        newval_cut = untime;
        h13_cut->Fill(newval_cut - oldval_cut);
        oldval_cut = newval_cut;

        //TRIGGER CHANNEL
        if(max_ampl[0] > Constants::Level[0])
        {
            h1_cut->Fill(max_ampl[0]);
            h4_cut->Fill(time_level[0]);
            h10_cut->Fill(num_peaks[0]);
            h20_cut->Fill(time_level[0],max_ampl[0]);
            h23_cut->Fill(untime,max_ampl[0]);
            prof1_cut->Fill(untime,max_ampl[0],1);
            h26_cut->Fill(untime,num_peaks[0]);
            prof7_cut->Fill(untime,num_peaks[0],1);
            h42_cut->Fill(position,max_ampl[0]);
            h50_cut->Fill(num_peaks_true[0]);
            h53_cut->Fill((double)num_peaks_true[0]/num_peaks[0]);
            h59_cut->Fill(time_max_ampl[0]);
            h65_cut->Fill(time_max_ampl[0],max_ampl[0]);
            h71_cut->Fill(charge[0]);
            h74_cut->Fill(max_ampl[0],charge[0]);
            prof27_cut->Fill(max_ampl[0],charge[0],1);
            h89_cut->Fill(width_at_level[0]);
            h92_cut->Fill(max_ampl[0],width_at_level[0]);
            h95_cut->Fill(charge[0],width_at_level[0]);

            if(position > Constants::posMinLim && position < Constants::posMaxLim)
            {
                Ntrig++;
            }

            for(Int_t peakID = 0; peakID < num_peaks[0]; peakID++)
            {
                prof10_cut->Fill(peakID,max_ampl_per_peak[0][peakID],1);
                prof13_cut->Fill(peakID,time_level_per_peak[0][peakID],1);
                prof16_cut->Fill(time_level_per_peak[0][peakID],max_ampl_per_peak[0][peakID],1);

                h33_cut->Fill(time_level_per_peak[0][peakID]);
                h36_cut->Fill(time_level[0] - time_level_per_peak[0][peakID]);
                h39_cut->Fill(time_level[0] - time_level_per_peak[0][peakID],max_ampl_per_peak[0][peakID]);
            }
            stop_untime_cut[0] = untime;
            if(max_ampl[0] >= Constants::Level[0])
            {
                rate_cut[0] += num_peaks[0];
                rate_true_cut[0] += num_peaks_true[0];
            }
            for(Int_t k = 0; k < prob_npeaks; k++)
            {
                if(num_peaks[0] == k)
                {
                    prob_cut[0][k]++;
                }
            }
            divider_cut[0]++;
            if(stop_untime_cut[0] - start_untime_cut[0] > rate_time)
            {
                h14_cut->Fill(1000000.0*rate_cut[0]/(stop_untime_cut[0] - start_untime_cut[0]));
                h17_cut->Fill(untime,1000000.0*rate_cut[0]/(stop_untime_cut[0] - start_untime_cut[0]));
                prof4_cut->Fill(untime,1000000.0*rate_cut[0]/(stop_untime_cut[0] - start_untime_cut[0]),1);
                prof24_cut->Fill(untime,1000000.0*rate_true_cut[0]/(stop_untime_cut[0] - start_untime_cut[0]),1);

                for(Int_t k = 0; k < 5; k++)
                {
                    h46_cut[k]->Fill(untime,(double)prob_cut[0][k]/divider_cut[0]);
                }
                rate_cut[0] = 0;
                rate_true_cut[0] = 0;
                for(Int_t j = 0; j < prob_npeaks; j++)
                {
                    prob[0][j] = 0;
                }
                divider[0] = 0;
                start_untime_cut[0] = stop_untime_cut[0];
            }
            nEventsSelected_cut[0]++;
        }

        //CpFM1 CHANNEL
        if(charge[1] > Constants::ChargeLevel[1])
        {
            if((time_level[0] - time_cf[1]) > 108.0 && (time_level[0] - time_cf[1]) < 112.0)
            {
                h72_cut->Fill(charge[1]);
                prof32_cut->Fill(untime,charge[1]/Qp_CpFM_expected[1],1);
                prof36_cut->Fill(untime,charge[1]/Qp_CpFM_calculated[1],1);
                prof40_cut->Fill(position,charge[1]/Qp_CpFM_calculated[1],1);

                if(position > Constants::posMinLim && position < Constants::posMaxLim)
                {
                    h81_cut->Fill(charge[1]/Qp_CpFM_calculated[1]);
                    Ncpfm_charge_1++;
                }
            }
        }
        if(max_ampl[1] > Constants::Level[1])
        {
            if((time_level[0] - time_cf[1]) > 108.0 && (time_level[0] - time_cf[1]) < 112.0)
            {
                h2_cut->Fill(max_ampl[1]);
                h5_cut->Fill(time_cf[1]);
                h7_cut->Fill(time_level[0]-time_cf[1]);
                h11_cut->Fill(num_peaks[1]);
                h21_cut->Fill(time_cf[1],max_ampl[1]);
                h24_cut->Fill(untime,max_ampl[1]);
                prof2_cut->Fill(untime,max_ampl[1],1);
                h27_cut->Fill(untime,num_peaks[1]);
                prof8_cut->Fill(untime,num_peaks[1],1);
                h29_cut->Fill(time_level[0]-time_cf[1],max_ampl[1]);
                prof19_cut->Fill(time_level[0]-time_cf[1],max_ampl[1],1);
                h43_cut->Fill(position,max_ampl[1]);
                h51_cut->Fill(num_peaks_true[1]);
                h54_cut->Fill((double)num_peaks_true[1]/num_peaks[1]);
                h60_cut->Fill(time_max_ampl[1]);
                h62_cut->Fill(time_max_ampl[0]-time_max_ampl[1]);
                h66_cut->Fill(time_max_ampl[1],max_ampl[1]);
                h68_cut->Fill(time_max_ampl[0]-time_max_ampl[1],max_ampl[1]);
                prof22_cut->Fill(time_max_ampl[0]-time_max_ampl[1],max_ampl[1],1);                
                h75_cut->Fill(max_ampl[1],charge[1]);
                prof28_cut->Fill(max_ampl[1],charge[1],1);                
                prof30_cut->Fill(untime,max_ampl[1]/Ap_CpFM_expected[1],1);
                prof34_cut->Fill(untime,max_ampl[1]/Ap_CpFM_calculated[1],1);                
                h77_cut->Fill(position,max_ampl[1]/Ap_CpFM_calculated[1]);
                prof38_cut->Fill(position,max_ampl[1]/Ap_CpFM_calculated[1],1);

                if(position > Constants::posMinLim && position < Constants::posMaxLim)
                {
                    h79_cut->Fill(max_ampl[1]/Ap_CpFM_calculated[1]);

                    Int_t index = max_ampl[1]/AstepProb+0.5;
                    AmaxCpFM1[index] = index*AstepProb;
                    nEventsOnPosition1_ampl_cut++;
                    if(num_peaks_true[1] > 1) NafterpulsesAmplCpFM1[index]++;
                    for(Int_t i = 0; i < num_peaks_true[1]; i++)
                    {
                        if(max_ampl_per_peak[1][i] == max_ampl[1]) continue;
                        h83_cut->Fill(max_ampl[1],max_ampl_per_peak[1][i]);
                        h85_cut->Fill(max_ampl[1],time_level[0]-time_level_per_peak[1][i]);
                        h87_cut->Fill(time_level[0]-time_cf[1],time_level[0]-time_level_per_peak[1][i]);
                    }
                    h90_cut->Fill(width_at_level[1]);
                    h93_cut->Fill(max_ampl[1],width_at_level[1]);
                    h96_cut->Fill(charge[1],width_at_level[1]);
                    Ncpfm_ampl_1++;
                }

                for(Int_t peakID = 0; peakID < num_peaks[1]; peakID++)
                {
                    prof11_cut->Fill(peakID,max_ampl_per_peak[1][peakID],1);
                    prof14_cut->Fill(peakID,time_level_per_peak[1][peakID],1);
                    prof17_cut->Fill(time_level_per_peak[1][peakID],max_ampl_per_peak[1][peakID],1);

                    h34_cut->Fill(time_level_per_peak[1][peakID]);
                    h37_cut->Fill(time_level[0] - time_level_per_peak[1][peakID]);
                    h40_cut->Fill(time_level[0] - time_level_per_peak[1][peakID],max_ampl_per_peak[1][peakID]);
                }
                stop_untime_cut[1] = untime;
                if(max_ampl[1] >= Constants::Level[1])
                {
                    rate_cut[1] += num_peaks[1];
                    rate_true_cut[1] += num_peaks_true[1];
                }
                for(Int_t k = 0; k < prob_npeaks; k++)
                {
                    if(num_peaks[1] == k)
                    {
                        prob_cut[1][k]++;
                    }
                }
                divider_cut[1]++;
                if(stop_untime_cut[1] - start_untime_cut[1] > rate_time)
                {
                    h15_cut->Fill(1000000.0*rate_cut[1]/(stop_untime_cut[1] - start_untime_cut[1]));
                    h18_cut->Fill(untime,1000000.0*rate_cut[1]/(stop_untime_cut[1] - start_untime_cut[1]));
                    prof5_cut->Fill(untime,1000000.0*rate_cut[1]/(stop_untime_cut[1] - start_untime_cut[1]),1);
                    prof25_cut->Fill(untime,1000000.0*rate_true_cut[1]/(stop_untime_cut[1] - start_untime_cut[1]),1);

                    for(Int_t k = 0; k < 5; k++)
                    {
                        h47_cut[k]->Fill(untime,(double)prob[1][k]/divider[1]);
                    }
                    rate_cut[1] = 0;
                    rate_true_cut[1] = 0;
                    for(Int_t j = 0; j < prob_npeaks; j++)
                    {
                        prob[1][j] = 0;
                    }
                    divider[1] = 0;
                    start_untime_cut[1] = stop_untime_cut[1];
                }
                nEventsSelected_cut[1]++;
            }
        }

        //CpFM2 CHANNEL
        if(charge[2] > Constants::ChargeLevel[2])
        {
            if((time_level[0] - time_cf[2]) > 109.0 && (time_level[0] - time_cf[2]) < 113.0)
            {
                h73_cut->Fill(charge[2]);
                prof33_cut->Fill(untime,charge[2]/Qp_CpFM_expected[2],1);
                prof37_cut->Fill(untime,charge[2]/Qp_CpFM_calculated[2],1);
                prof41_cut->Fill(position,charge[2]/Qp_CpFM_calculated[2],1);
                if(position > Constants::posMinLim+6.0 && position < Constants::posMaxLim+6.0)
                {
                    h82_cut->Fill(charge[2]/Qp_CpFM_calculated[2]);
                    Ncpfm_charge_2++;
                }
            }
        }
        if(max_ampl[2] > Constants::Level[2])
        {
            if((time_level[0] - time_cf[2]) > 109.0 && (time_level[0] - time_cf[2]) < 113.0)
            {
                h3_cut->Fill(max_ampl[2]);
                h6_cut->Fill(time_cf[2]);
                h8_cut->Fill(time_level[0]-time_cf[2]);
                h12_cut->Fill(num_peaks[2]);
                h22_cut->Fill(time_cf[2],max_ampl[2]);
                h25_cut->Fill(untime,max_ampl[2]);
                prof3_cut->Fill(untime,max_ampl[2],1);
                h28_cut->Fill(untime,num_peaks[2]);
                prof9_cut->Fill(untime,num_peaks[2],1);
                h30_cut->Fill(time_level[0]-time_cf[2],max_ampl[2]);
                prof20_cut->Fill(time_level[0]-time_cf[2],max_ampl[2],1);
                h44_cut->Fill(position,max_ampl[2]);
                h52_cut->Fill(num_peaks_true[2]);
                h55_cut->Fill((double)num_peaks_true[2]/num_peaks[2]);
                h61_cut->Fill(time_max_ampl[2]);
                h63_cut->Fill(time_max_ampl[0]-time_max_ampl[2]);
                h67_cut->Fill(time_max_ampl[2],max_ampl[2]);
                h69_cut->Fill(time_max_ampl[0]-time_max_ampl[2],max_ampl[2]);
                prof23_cut->Fill(time_max_ampl[0]-time_max_ampl[2],max_ampl[2],1);                
                h76_cut->Fill(max_ampl[2],charge[2]);
                prof29_cut->Fill(max_ampl[2],charge[2],1);
                prof31_cut->Fill(untime,max_ampl[2]/Ap_CpFM_expected[2],1);
                prof35_cut->Fill(untime,max_ampl[2]/Ap_CpFM_calculated[2],1);                
                h78_cut->Fill(position,max_ampl[2]/Ap_CpFM_calculated[2]);
                prof39_cut->Fill(position,max_ampl[2]/Ap_CpFM_calculated[2],1);

                if(position > Constants::posMinLim+6.0 && position < Constants::posMaxLim+6.0)
                {
                    h80_cut->Fill(max_ampl[2]/Ap_CpFM_calculated[2]);

                    Int_t index = max_ampl[2]/AstepProb+0.5;
                    AmaxCpFM2[index] = index*AstepProb;
                    nEventsOnPosition2_ampl_cut++;
                    if(num_peaks_true[2] > 1) NafterpulsesAmplCpFM2[index]++;
                    for(Int_t i = 0; i < num_peaks_true[1]; i++)
                    {
                        if(max_ampl_per_peak[2][i] == max_ampl[2]) continue;
                        h84_cut->Fill(max_ampl[2],max_ampl_per_peak[2][i]);
                        h86_cut->Fill(max_ampl[2],time_level[0]-time_level_per_peak[2][i]);
                        h88_cut->Fill(time_level[0]-time_cf[2],time_level[0]-time_level_per_peak[2][i]);
                    }
                    h91_cut->Fill(width_at_level[2]);
                    h94_cut->Fill(max_ampl[2],width_at_level[2]);
                    h97_cut->Fill(charge[2],width_at_level[2]);
                    Ncpfm_ampl_2++;

                    index = max_ampl[2]/AstepProb+0.5;
                    Ncpfm2Prob[index]++;
                    if(max_ampl[1] > Constants::Level[1])
                    {
                        if((time_level[0] - time_cf[1]) > 108.0 && (time_level[0] - time_cf[1]) < 112.0)
                        {
                            Ncpfm1Prob[index]++;
                        }
                    }
                }

                for(Int_t peakID = 0; peakID < num_peaks[2]; peakID++)
                {
                    prof12_cut->Fill(peakID,max_ampl_per_peak[2][peakID],1);
                    prof15_cut->Fill(peakID,time_level_per_peak[2][peakID],1);
                    prof18_cut->Fill(time_level_per_peak[2][peakID],max_ampl_per_peak[2][peakID],1);

                    h35_cut->Fill(time_level_per_peak[2][peakID]);
                    h38_cut->Fill(time_level[0] - time_level_per_peak[2][peakID]);
                    h41_cut->Fill(time_level[0] - time_level_per_peak[2][peakID],max_ampl_per_peak[2][peakID]);
                }
                stop_untime_cut[2] = untime;
                if(max_ampl[2] >= Constants::Level[2])
                {
                    rate_cut[2] += num_peaks[2];
                    rate_true_cut[2] += num_peaks_true[2];
                }
                for(Int_t k = 0; k < prob_npeaks; k++)
                {
                    if(num_peaks[2] == k)
                    {
                        prob_cut[2][k]++;
                    }
                }
                divider_cut[2]++;
                if(stop_untime_cut[2] - start_untime_cut[2] > rate_time)
                {
                    h16_cut->Fill(1000000.0*rate_cut[2]/(stop_untime_cut[2] - start_untime_cut[2]));
                    h19_cut->Fill(untime,1000000.0*rate_cut[2]/(stop_untime_cut[2] - start_untime_cut[2]));
                    prof6_cut->Fill(untime,1000000.0*rate_cut[2]/(stop_untime_cut[2] - start_untime_cut[2]),1);
                    prof26_cut->Fill(untime,1000000.0*rate_true_cut[2]/(stop_untime_cut[2] - start_untime_cut[2]),1);

                    for(Int_t k = 0; k < 5; k++)
                    {
                        h48_cut[k]->Fill(untime,(double)prob[2][k]/divider[2]);
                    }
                    rate_cut[2] = 0;
                    rate_true_cut[2] = 0;
                    for(Int_t j = 0; j < prob_npeaks; j++)
                    {
                        prob[2][j] = 0;
                    }
                    divider[2] = 0;
                    start_untime_cut[2] = stop_untime_cut[2];
                }
                nEventsSelected_cut[2]++;
            }
        }

        //CpFM1 & CpFM2 CHANNELS
        if(max_ampl[1] > Constants::Level[1] && max_ampl[2] > Constants::Level[2])
        {
            if((time_level[0] - time_cf[1]) > 108.0 && (time_level[0] - time_cf[1]) < 112.0)
            {
                if((time_level[0] - time_cf[2]) > 109.0 && (time_level[0] - time_cf[2]) < 113.0)
                {
                    h9_cut->Fill(time_cf[1]-time_cf[2]);
                    h49_cut->Fill(max_ampl[1],max_ampl[2]);
                    h64_cut->Fill(time_max_ampl[1]-time_max_ampl[2]);
                    prof21_cut->Fill(max_ampl[1],max_ampl[2],1);
                    nEventsSelected_cut[3]++;
                }
            }
        }
        h70_cut->Fill(untime,position);
    }

    Double_t AmplitudeCpFM2[NbinsProb] = {};
    Double_t errAmplitudeCpFM2[NbinsProb] = {};
    for(Int_t i = 0; i < NbinsProb; i++)
    {
        AmplitudeCpFM2[i] = i*AstepProb;
        errAmplitudeCpFM2[i] = AstepProb;
        if(Ncpfm2Prob[i] != 0)
        {
            CpFM1Probability[i] = 100.0*Ncpfm1Prob[i]/Ncpfm2Prob[i];
            errCpFM1Probability[i] = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(Ncpfm1Prob[i])/Ncpfm2Prob[i],2) + TMath::Power(TMath::Sqrt(Ncpfm1Prob[i]*TMath::Sqrt(Ncpfm2Prob[i]))/TMath::Power(Ncpfm2Prob[i],2),2));
        }
    }

    Double_t ProbabilityAfterPulsesCpFM1_ampl[NbinsProb] = {};
    Double_t errProbabilityAfterPulsesCpFM1_ampl[NbinsProb] = {};
    Double_t ProbabilityAfterPulsesCpFM2_ampl[NbinsProb] = {};
    Double_t errProbabilityAfterPulsesCpFM2_ampl[NbinsProb] = {};
    for(Int_t i = 0; i < NbinsProb; i++)
    {
        errAmaxCpFM1[i] = AstepProb;
        errAmaxCpFM2[i] = AstepProb;

        ProbabilityAfterPulsesCpFM1_ampl[i] = 100.0*NafterpulsesAmplCpFM1[i]/nEventsOnPosition1_ampl_cut;
        errProbabilityAfterPulsesCpFM1_ampl[i] = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(NafterpulsesAmplCpFM1[i])/nEventsOnPosition1_ampl_cut,2) + TMath::Power(TMath::Sqrt(nEventsOnPosition1_ampl_cut)*NafterpulsesAmplCpFM1[i]/(nEventsOnPosition1_ampl_cut*nEventsOnPosition1_ampl_cut),2));
        ProbabilityAfterPulsesCpFM2_ampl[i] = 100.0*NafterpulsesAmplCpFM2[i]/nEventsOnPosition2_ampl_cut;
        errProbabilityAfterPulsesCpFM2_ampl[i] = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(NafterpulsesAmplCpFM2[i])/nEventsOnPosition2_ampl_cut,2) + TMath::Power(TMath::Sqrt(nEventsOnPosition2_ampl_cut)*NafterpulsesAmplCpFM2[i]/(nEventsOnPosition2_ampl_cut*nEventsOnPosition2_ampl_cut),2));
    }

    Double_t Eff_ampl_1 = 100.0*Ncpfm_ampl_1/Ntrig;
    Double_t errEff_ampl_1 = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(Ncpfm_ampl_1)/Ntrig,2) + TMath::Power(TMath::Sqrt(Ntrig)*Ncpfm_ampl_1/(Ntrig*Ntrig),2));
    Double_t Eff_ampl_2 = 100.0*Ncpfm_ampl_2/Ntrig;
    Double_t errEff_ampl_2 = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(Ncpfm_ampl_2)/Ntrig,2) + TMath::Power(TMath::Sqrt(Ntrig)*Ncpfm_ampl_2/(Ntrig*Ntrig),2));
    Double_t Eff_charge_1 = 100.0*Ncpfm_charge_1/Ntrig;
    Double_t errEff_charge_1 = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(Ncpfm_charge_1)/Ntrig,2) + TMath::Power(TMath::Sqrt(Ntrig)*Ncpfm_charge_1/(Ntrig*Ntrig),2));
    Double_t Eff_charge_2 = 100.0*Ncpfm_charge_2/Ntrig;
    Double_t errEff_charge_2 = 100.0*TMath::Sqrt(TMath::Power(TMath::Sqrt(Ncpfm_charge_2)/Ntrig,2) + TMath::Power(TMath::Sqrt(Ntrig)*Ncpfm_charge_2/(Ntrig*Ntrig),2));

    cout<<"Efficiency CpFM1 (from Amplitude) = "<<Eff_ampl_1<<" +/- "<<errEff_ampl_1<<" %"<<endl;
    cout<<"Efficiency CpFM2 (from Amplitude) = "<<Eff_ampl_2<<" +/- "<<errEff_ampl_2<<" %"<<endl;
    cout<<"Efficiency CpFM1 (from Charge) = "<<Eff_charge_1<<" +/- "<<errEff_charge_1<<" %"<<endl;
    cout<<"Efficiency CpFM2 (from Charge) = "<<Eff_charge_2<<" +/- "<<errEff_charge_2<<" %"<<endl;

    cout<<"--> Selected: "<<100.0*nEventsSelected/nEntries<<" %"<<endl;
    cout<<"--> Selected: "<<100.0*nEventsSelected_cut[0]/nEntries<<" % (CH0,with cuts)"<<endl;
    cout<<"--> Selected: "<<100.0*nEventsSelected_cut[1]/nEntries<<" % (CH1,with cuts)"<<endl;
    cout<<"--> Selected: "<<100.0*nEventsSelected_cut[2]/nEntries<<" % (CH2,with cuts)"<<endl;
    cout<<"--> Selected: "<<100.0*nEventsSelected_cut[3]/nEntries<<" % (CH1+2,with cuts)"<<endl;

    TFile* file = new TFile(argv[2],"recreate");
    file->cd();

    TCanvas* canva1 = new TCanvas("canva1","Probability of CpFM1 triggering as a function of CpFM2 amplitude",800,800);
    canva1->cd();
    TGraphErrors* gr1 = new TGraphErrors(NbinsProb,AmplitudeCpFM2,CpFM1Probability,errAmplitudeCpFM2,errCpFM1Probability);
    gr1->SetLineWidth(2);
    gr1->SetLineColor(kBlue);
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(1);
    gr1->SetMarkerColor(kRed);
    gr1->GetXaxis()->SetTitle("Max. Amplitude CpFM2, V");
    gr1->GetYaxis()->SetTitle("Probability, %");
    gr1->Draw("APL");
    canva1->Write();

    TCanvas* canva2 = new TCanvas("canva2","Probability of Afterpulses vs Amplitude on CpFM1",800,800);
    canva2->cd();
    TGraphErrors* gr2 = new TGraphErrors(NbinsProb,AmaxCpFM1,ProbabilityAfterPulsesCpFM1_ampl,errAmaxCpFM1,errProbabilityAfterPulsesCpFM1_ampl);
    gr2->SetMarkerStyle(20);
    gr2->SetMarkerSize(1);
    gr2->SetMarkerColor(kBlue);
    gr2->GetXaxis()->SetTitle("Max. Amplitude CpFM1, V");
    gr2->GetYaxis()->SetTitle("Probability, %");
    gr2->Draw("AP");
    canva2->Write();

    TCanvas* canva4 = new TCanvas("canva4","Probability of Afterpulses vs Amplitude on CpFM2",800,800);
    canva4->cd();
    TGraphErrors* gr4 = new TGraphErrors(NbinsProb,AmaxCpFM2,ProbabilityAfterPulsesCpFM2_ampl,errAmaxCpFM2,errProbabilityAfterPulsesCpFM2_ampl);
    gr4->SetMarkerStyle(20);
    gr4->SetMarkerSize(1);
    gr4->SetMarkerColor(kBlue);
    gr4->GetXaxis()->SetTitle("Max. Amplitude CpFM2, V");
    gr4->GetYaxis()->SetTitle("Probability, %");
    gr4->Draw("AP");
    canva4->Write();
    //------------------------------------------------//
    // WITHOUT CUTS
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    h5->Write();
    h6->Write();
    h7->Write();
    h8->Write();
    h9->Write();
    h10->Write();
    h11->Write();
    h12->Write();
    h13->Write();
    h14->Write();
    h15->Write();
    h16->Write();
    h17->Write();
    h18->Write();
    h19->Write();
    h20->Write();
    h21->Write();
    h22->Write();
    h23->Write();
    h24->Write();
    h25->Write();    
    h26->Write();
    h27->Write();
    h28->Write();    
    h29->Write();
    h30->Write();    
    h33->Write();
    h34->Write();
    h35->Write();
    h36->Write();
    h37->Write();
    h38->Write();
    h39->Write();
    h40->Write();
    h41->Write();
    h42->Write();
    h43->Write();
    h44->Write();
    h45->Write();

    for(Int_t k = 0; k < prob_npeaks; k++)
    {
        h46[k]->Write();
        h47[k]->Write();
        h48[k]->Write();
    }

    h49->Write();
    h50->Write();
    h51->Write();
    h52->Write();
    h53->Write();
    h54->Write();
    h55->Write();
    h59->Write();
    h60->Write();
    h61->Write();
    h62->Write();
    h63->Write();
    h64->Write();
    h65->Write();
    h66->Write();
    h67->Write();
    h68->Write();
    h69->Write();
    h70->Write();
    h71->Write();
    h72->Write();
    h73->Write();
    h74->Write();
    h75->Write();
    h76->Write();
    h77->Write();
    h78->Write();
    h79->Write();
    h80->Write();
    h81->Write();
    h82->Write();
    h83->Write();
    h84->Write();
    h85->Write();
    h86->Write();
    h87->Write();
    h88->Write();
    h89->Write();
    h90->Write();
    h91->Write();
    h92->Write();
    h93->Write();
    h94->Write();
    h95->Write();
    h96->Write();
    h97->Write();
    
    prof1->Write();
    prof2->Write();
    prof3->Write();
    prof4->Write();
    prof5->Write();
    prof6->Write();
    prof7->Write();
    prof8->Write();
    prof9->Write();
    prof10->Write();
    prof11->Write();
    prof12->Write();
    prof13->Write();
    prof14->Write();
    prof15->Write();
    prof16->Write();
    prof17->Write();
    prof18->Write();
    prof19->Write();
    prof20->Write();
    prof21->Write();
    prof22->Write();
    prof23->Write();
    prof24->Write();
    prof25->Write();
    prof26->Write();
    prof27->Write();
    prof28->Write();
    prof29->Write();
    prof30->Write();
    prof31->Write();
    prof32->Write();
    prof33->Write();
    prof34->Write();
    prof35->Write();
    prof36->Write();
    prof37->Write();
    prof38->Write();
    prof39->Write();
    prof40->Write();
    prof41->Write();

    //------------------------------------------------//
    // WITH CUTS
    h1_cut->Write();
    h2_cut->Write();
    h3_cut->Write();
    h4_cut->Write();
    h5_cut->Write();
    h6_cut->Write();
    h7_cut->Write();
    h8_cut->Write();
    h9_cut->Write();
    h10_cut->Write();
    h11_cut->Write();
    h12_cut->Write();
    h13_cut->Write();
    h14_cut->Write();
    h15_cut->Write();
    h16_cut->Write();
    h17_cut->Write();
    h18_cut->Write();
    h19_cut->Write();
    h20_cut->Write();
    h21_cut->Write();
    h22_cut->Write();
    h23_cut->Write();
    h24_cut->Write();
    h25_cut->Write();
    h26_cut->Write();
    h27_cut->Write();
    h28_cut->Write();
    h29_cut->Write();
    h30_cut->Write();
    h33_cut->Write();
    h34_cut->Write();
    h35_cut->Write();
    h36_cut->Write();
    h37_cut->Write();
    h38_cut->Write();
    h39_cut->Write();
    h40_cut->Write();
    h41_cut->Write();
    h42_cut->Write();
    h43_cut->Write();
    h44_cut->Write();

    for(Int_t k = 0; k < prob_npeaks; k++)
    {
        h46_cut[k]->Write();
        h47_cut[k]->Write();
        h48_cut[k]->Write();
    }

    h49_cut->Write();
    h50_cut->Write();
    h51_cut->Write();
    h52_cut->Write();
    h53_cut->Write();
    h54_cut->Write();
    h55_cut->Write();
    h59_cut->Write();
    h60_cut->Write();
    h61_cut->Write();
    h62_cut->Write();
    h63_cut->Write();
    h64_cut->Write();
    h65_cut->Write();
    h66_cut->Write();
    h67_cut->Write();
    h68_cut->Write();
    h69_cut->Write();
    h70_cut->Write();
    h71_cut->Write();
    h72_cut->Write();
    h73_cut->Write();
    h74_cut->Write();
    h75_cut->Write();
    h76_cut->Write();
    h77_cut->Write();
    h78_cut->Write();
    h79_cut->Write();
    h80_cut->Write();
    h81_cut->Write();
    h82_cut->Write();
    h83_cut->Write();
    h84_cut->Write();
    h85_cut->Write();
    h86_cut->Write();
    h87_cut->Write();
    h88_cut->Write();
    h89_cut->Write();
    h90_cut->Write();
    h91_cut->Write();
    h92_cut->Write();
    h93_cut->Write();
    h94_cut->Write();
    h95_cut->Write();
    h96_cut->Write();
    h97_cut->Write();

    prof1_cut->Write();
    prof2_cut->Write();
    prof3_cut->Write();
    prof4_cut->Write();
    prof5_cut->Write();
    prof6_cut->Write();
    prof7_cut->Write();
    prof8_cut->Write();
    prof9_cut->Write();
    prof10_cut->Write();
    prof11_cut->Write();
    prof12_cut->Write();
    prof13_cut->Write();
    prof14_cut->Write();
    prof15_cut->Write();
    prof16_cut->Write();
    prof17_cut->Write();
    prof18_cut->Write();
    prof19_cut->Write();
    prof20_cut->Write();
    prof21_cut->Write();
    prof22_cut->Write();
    prof23_cut->Write();
    prof24_cut->Write();
    prof25_cut->Write();
    prof26_cut->Write();
    prof27_cut->Write();
    prof28_cut->Write();
    prof29_cut->Write();
    prof30_cut->Write();
    prof31_cut->Write();
    prof32_cut->Write();
    prof33_cut->Write();
    prof34_cut->Write();
    prof35_cut->Write();
    prof36_cut->Write();
    prof37_cut->Write();
    prof38_cut->Write();
    prof39_cut->Write();
    prof40_cut->Write();
    prof41_cut->Write();

    file->Write();

    return 0;
}



