//root
#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"

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
#include <assert.h>

#include "include/Constants.hh"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [1] - A path to the .dat files."<<endl;
        cout<<"--> [2] - A name of the input .txt filelist."<<endl;
        cout<<"--> [3] - A name of the output .root file."<<endl;
        cout<<endl;
        return -1;
    }

    TFile *file = new TFile(argv[3],"recreate");
    TTree *tree = new TTree("Tree","A Root Tree");

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
    // Per peak
    Double_t max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_level_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t width_at_level_per_peak[Constants::nCh][Constants::nPeakMax];

    TString tdc_ss = "tdc/D";
    TString untime_ss = "untime/D";
    TString max_ampl_ss = "max_ampl[";
    TString min_ampl_ss = "min_ampl[";
    TString mean_value_ss = "mean_value_20p[";
    TString time_max_ampl_ss = "time_max_ampl[";
    TString time_min_ampl_ss = "time_min_ampl[";
    TString time_level_ss = "time_level[";
    TString time_cf_ss = "time_cf[";
    TString rise_time_ss = "rise_time[";
    TString fall_time_ss = "fall_time[";
    TString charge_ss = "charge[";
    TString width_at_level_ss = "width_at_level[";
    TString num_peaks_ss = "num_peaks[";
    TString num_peaks_true_ss = "num_peaks_true[";

    TString max_ampl_per_peak_ss = "max_ampl_per_peak[";
    TString time_max_ampl_per_peak_ss = "time_max_ampl_per_peak[";
    TString time_level_per_peak_ss = "time_level_per_peak[";
    TString width_at_level_per_peak_ss = "width_at_level_per_peak[";

    max_ampl_ss += Constants::nCh;
    min_ampl_ss += Constants::nCh;
    mean_value_ss += Constants::nCh;
    time_max_ampl_ss += Constants::nCh;
    time_min_ampl_ss += Constants::nCh;
    time_level_ss += Constants::nCh;
    time_cf_ss += Constants::nCh;
    rise_time_ss += Constants::nCh;
    fall_time_ss += Constants::nCh;
    charge_ss += Constants::nCh;
    width_at_level_ss += Constants::nCh;
    num_peaks_ss += Constants::nCh;
    num_peaks_true_ss += Constants::nCh;

    max_ampl_per_peak_ss += Constants::nCh;
    time_max_ampl_per_peak_ss += Constants::nCh;
    time_level_per_peak_ss += Constants::nCh;
    width_at_level_per_peak_ss += Constants::nCh;

    max_ampl_per_peak_ss += "][";
    time_max_ampl_per_peak_ss += "][";
    time_level_per_peak_ss += "][";
    width_at_level_per_peak_ss += "][";

    max_ampl_per_peak_ss += Constants::nPeakMax;
    time_max_ampl_per_peak_ss += Constants::nPeakMax;
    time_level_per_peak_ss += Constants::nPeakMax;
    width_at_level_per_peak_ss += Constants::nPeakMax;

    mean_value_ss +="]/D";
    max_ampl_ss +="]/D";
    min_ampl_ss +="]/D";
    time_max_ampl_ss +="]/D";
    time_min_ampl_ss +="]/D";
    time_level_ss +="]/D";
    time_cf_ss +="]/D";
    rise_time_ss +="]/D";
    fall_time_ss +="]/D";
    charge_ss +="]/D";
    width_at_level_ss +="]/D";
    num_peaks_ss +="]/I";
    num_peaks_true_ss +="]/I";

    max_ampl_per_peak_ss +="]/D";
    time_max_ampl_per_peak_ss +="]/D";
    time_level_per_peak_ss +="]/D";
    width_at_level_per_peak_ss +="]/D";

    tree->Branch("UnixTime",    &untime,        untime_ss.Data());
    tree->Branch("TDC",         &tdc,           tdc_ss.Data());

    tree->Branch("MaxAmp", max_ampl, max_ampl_ss.Data());
    tree->Branch("MinAmp", min_ampl, min_ampl_ss.Data());
    tree->Branch("TimeMaxAmp", time_max_ampl, time_max_ampl_ss.Data());
    tree->Branch("TimeMinAmp", time_min_ampl, time_min_ampl_ss.Data());
    tree->Branch("TimeLevel", time_level, time_level_ss.Data());
    tree->Branch("WidthAtTheLevel", width_at_level, width_at_level_ss.Data());
    tree->Branch("MeanValue20Points", mean_value_20p, mean_value_ss.Data());
    tree->Branch("TimeCF", time_cf, time_cf_ss.Data());
    tree->Branch("RiseTime", rise_time, rise_time_ss.Data());
    tree->Branch("FallTime", fall_time, fall_time_ss.Data());
    tree->Branch("Charge", charge, charge_ss.Data());
    tree->Branch("NumPeaks", num_peaks, num_peaks_ss.Data());
    tree->Branch("NumPeaksTrue", num_peaks_true, num_peaks_true_ss.Data());

    tree->Branch("MaxAmpPerPeak", max_ampl_per_peak, max_ampl_per_peak_ss.Data());
    tree->Branch("TimeMaxAmpPerPeak", time_max_ampl_per_peak, time_max_ampl_per_peak_ss.Data());
    tree->Branch("TimeLevelPerPeak", time_level_per_peak, time_level_per_peak_ss.Data());
    tree->Branch("WidthAtTheLevelPerPeak", width_at_level_per_peak, width_at_level_per_peak_ss.Data());

    for (Int_t i = 0; i < Constants::nCh; i++)
    {
        max_ampl[i] = -999;
        min_ampl[i] = -999;
        time_max_ampl[i] = -999;
        time_min_ampl[i] = -999;
        width_at_level[i] = -999;
        time_level[i] = -999;
        time_cf[i] = -999;
        mean_value_20p[i] = -999;
        rise_time[i] = -999;
        fall_time[i] = -999;
        charge[i] = -999;
        num_peaks[i] = -999;
        num_peaks_true[i] = -999;

        for(Int_t j = 0; j < Constants::nPeakMax; j++)
        {
            max_ampl_per_peak[i][j] = -999;
            time_max_ampl_per_peak[i][j] = -999;
            width_at_level_per_peak[i][j] = -999;
            time_level_per_peak[i][j] = -999;
        }
    }

    Int_t chid;
    string word;
    ifstream fp(argv[2]);
    string NameOfTheFile;
    Double_t LeadingEdgeTime = 0, TrailingEdgeTime = 0;
    while(fp>>NameOfTheFile)
    {
        TString inputFileName = argv[1]; inputFileName += NameOfTheFile;
        ifstream txt(inputFileName.Data());
        cout<<"Reading the file: "<<inputFileName.Data()<<endl;
        while (txt>>word)
        {
            if(word == "Event")
            {
                txt>>word; txt>>word;
                txt>>word;
                txt>>untime;            //UnixTime
                txt>>word; txt>>word;   //Timestamp
                txt>>word; txt>>word;
                txt>>word;
                txt>>tdc;               //TDC
                txt>>word;

                for(Int_t i = 0; i < Constants::nCh; i++)
                {
                    txt>>chid;                                  //ChannelNb
                    if(chid != i) {cout<<"--> ERROR: Wrong format of the input data!"<<endl; assert(0);}
                    txt>>word;                                  //ChannelName
                    txt>>word;                                  //EventID
                    txt>>mean_value_20p[chid];                  //MeasuredBaseline[Volts]
                    txt>>max_ampl[chid];                        //Amplitude[Volts]
                    max_ampl[chid] = (-1)*max_ampl[chid];
                    txt>>time_max_ampl[chid];                   //PeakTime[ns]
                    txt>>charge[chid];                          //Charge[pC]
                    charge[chid] = (-1)*charge[chid];
                    txt>>LeadingEdgeTime;                       //LeadingEdgeTime[ns]
                    txt>>TrailingEdgeTime;                      //TrailingEdgeTime[ns]
                    width_at_level[chid] = LeadingEdgeTime - TrailingEdgeTime;
                    time_level[chid] = TrailingEdgeTime;
                    time_cf[chid] = TrailingEdgeTime;
                    txt>>num_peaks[chid];                       //Peaks[count]
                }
            }
            else continue;
            tree->Fill();
        }
    }
    file->Write();
    file->Close();

    return 0;
}
