//my
#include "include/Constants.hh"
#include "src/Tree.h"
//c++
#include <cstdlib>
#include <assert.h>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [1] - A name of the input .root file."<<endl;
        cout<<"--> [2] - A name of the output file with parameters."<<endl;
        cout<<endl;
        return -1;
    }

    cout<<"--> Input file:"<<argv[1]<<endl;
    cout<<"--> Output file:"<<argv[2]<<endl;

    Tree pointer(argv[1]);

    TFile *file = new TFile(argv[2],"recreate");
    TTree *tree = new TTree("Tree","A Root Tree");

    Double_t AmplitudeRaw[Constants::nPnt];
    Double_t Amplitude[Constants::nPnt];
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
    Double_t width_at_cft[Constants::nCh];
    Int_t num_peaks[Constants::nCh];
    Int_t num_peaks_true[Constants::nCh];
    Int_t eventid;
    // Per peak
    Double_t max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_max_ampl_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t time_level_per_peak[Constants::nCh][Constants::nPeakMax];
    Double_t width_at_cft_per_peak[Constants::nCh][Constants::nPeakMax];

    TString tdc_ss = "tdc/D";
    TString untime_ss = "untime/D";
    TString max_ampl_ss = "max_ampl[";
    TString min_ampl_ss = "min_ampl[";
    TString mean_value_ss = "mean_value_16p[";
    TString time_max_ampl_ss = "time_max_ampl[";
    TString time_min_ampl_ss = "time_min_ampl[";
    TString time_level_ss = "time_level[";
    TString time_cf_ss = "time_cf[";
    TString rise_time_ss = "rise_time[";
    TString fall_time_ss = "fall_time[";
    TString charge_ss = "charge[";
    TString width_at_cft_ss = "width_at_cft[";
    TString num_peaks_ss = "num_peaks[";
    TString num_peaks_true_ss = "num_peaks_true[";
    TString eventid_ss = "eventid/I";

    TString max_ampl_per_peak_ss = "max_ampl_per_peak[";
    TString time_max_ampl_per_peak_ss = "time_max_ampl_per_peak[";
    TString time_level_per_peak_ss = "time_level_per_peak[";
    TString width_at_cft_per_peak_ss = "width_at_cft_per_peak[";

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
    width_at_cft_ss += Constants::nCh;
    num_peaks_ss += Constants::nCh;
    num_peaks_true_ss += Constants::nCh;

    max_ampl_per_peak_ss += Constants::nCh;
    time_max_ampl_per_peak_ss += Constants::nCh;
    time_level_per_peak_ss += Constants::nCh;
    width_at_cft_per_peak_ss += Constants::nCh;

    max_ampl_per_peak_ss += "][";
    time_max_ampl_per_peak_ss += "][";
    time_level_per_peak_ss += "][";
    width_at_cft_per_peak_ss += "][";

    max_ampl_per_peak_ss += Constants::nPeakMax;
    time_max_ampl_per_peak_ss += Constants::nPeakMax;
    time_level_per_peak_ss += Constants::nPeakMax;
    width_at_cft_per_peak_ss += Constants::nPeakMax;

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
    width_at_cft_ss +="]/D";
    num_peaks_ss +="]/I";
    num_peaks_true_ss +="]/I";

    max_ampl_per_peak_ss +="]/D";
    time_max_ampl_per_peak_ss +="]/D";
    time_level_per_peak_ss +="]/D";
    width_at_cft_per_peak_ss +="]/D";

    tree->Branch("UnixTime",    &untime,        untime_ss.Data());
    tree->Branch("TDC",         &tdc,           tdc_ss.Data());

    tree->Branch("EventID", &eventid, eventid_ss.Data());
    tree->Branch("MaxAmp", max_ampl, max_ampl_ss.Data());
    tree->Branch("MinAmp", min_ampl, min_ampl_ss.Data());
    tree->Branch("TimeMaxAmp", time_max_ampl, time_max_ampl_ss.Data());
    tree->Branch("TimeMinAmp", time_min_ampl, time_min_ampl_ss.Data());
    tree->Branch("TimeLevel", time_level, time_level_ss.Data());
    tree->Branch("WidthAtTimeCF", width_at_cft, width_at_cft_ss.Data());
    tree->Branch("MeanValue16Points", mean_value_16p, mean_value_ss.Data());
    tree->Branch("TimeCF", time_cf, time_cf_ss.Data());
    tree->Branch("RiseTime", rise_time, rise_time_ss.Data());
    tree->Branch("FallTime", fall_time, fall_time_ss.Data());
    tree->Branch("Charge", charge, charge_ss.Data());
    tree->Branch("NumPeaks", num_peaks, num_peaks_ss.Data());
    tree->Branch("NumPeaksTrue", num_peaks_true, num_peaks_true_ss.Data());

    tree->Branch("MaxAmpPerPeak", max_ampl_per_peak, max_ampl_per_peak_ss.Data());
    tree->Branch("TimeMaxAmpPerPeak", time_max_ampl_per_peak, time_max_ampl_per_peak_ss.Data());
    tree->Branch("TimeLevelPerPeak", time_level_per_peak, time_level_per_peak_ss.Data());
    tree->Branch("WidthAtTimeCFPerPeak", width_at_cft_per_peak, width_at_cft_per_peak_ss.Data());

    for (Int_t i = 0; i < Constants::nCh; i++)
    {
        AmplitudeRaw[i]     = -999;
        Amplitude[i]        = -999;
        max_ampl[i]         = -999;
        min_ampl[i]         = -999;
        time_max_ampl[i]    = -999;
        time_min_ampl[i]    = -999;
        width_at_cft[i]     = -999;
        time_level[i]       = -999;
        time_cf[i]          = -999;
        mean_value_16p[i]   = -999;
        rise_time[i]        = -999;
        fall_time[i]        = -999;
        charge[i]           = -999;
        num_peaks[i]        = -999;
        num_peaks_true[i]   = -999;

        for(Int_t j = 0; j < Constants::nPeakMax; j++)
        {
            max_ampl_per_peak[i][j]         = -999;
            time_max_ampl_per_peak[i][j]    = -999;
            width_at_cft_per_peak[i][j]     = -999;
            time_level_per_peak[i][j]       = -999;
        }
    }

    Long64_t nEvents = 0;
    eventid = -999;
    pointer.GetNumEntries(nEvents);

    cout<<"--> nEvents = "<<nEvents<<endl;

    for(Int_t eventID_iter = 0; eventID_iter < nEvents; eventID_iter++)
    {
        pointer.fChain->GetEntry(eventID_iter);
        for(Int_t channelID = 0; channelID < Constants::nCh; channelID++)
        {
            // Common
            pointer.TransformAmplitude(channelID, AmplitudeRaw);
            pointer.GetMean16(AmplitudeRaw, mean_value_16p[channelID],Amplitude);
            pointer.GetMaxAmpl(Amplitude, max_ampl[channelID], time_max_ampl[channelID]);
            pointer.GetMinAmpl(Amplitude, min_ampl[channelID], time_min_ampl[channelID]);
            pointer.GetTimeAtLevel(Amplitude, Constants::Level[channelID], time_max_ampl[channelID], time_level[channelID]);
            pointer.GetWidth(Amplitude, Constants::CF[channelID]*max_ampl[channelID],time_max_ampl[channelID],width_at_cft[channelID]);
            pointer.GetTimeCF(Amplitude, Constants::CF[channelID],max_ampl[channelID],time_max_ampl[channelID],time_cf[channelID]);
            pointer.GetRiseTime(Amplitude, max_ampl[channelID],time_max_ampl[channelID],rise_time[channelID]);
            pointer.GetFallTime(Amplitude, max_ampl[channelID],time_max_ampl[channelID],fall_time[channelID]);
            pointer.GetCharge(Amplitude, time_max_ampl[channelID], charge[channelID]);
            pointer.GetNumPeaks(Amplitude, Constants::Level[channelID], num_peaks[channelID]);
            pointer.GetTrueNumPeaks(Amplitude, Constants::Level[channelID], num_peaks_true[channelID]);

            // Per peak
            if(num_peaks_true[channelID] > 0)
            {
                pointer.GetMaxAmplPerPeak(Amplitude, Constants::Level[channelID], max_ampl_per_peak[channelID], time_max_ampl_per_peak[channelID]);
                pointer.GetTimeAtLevelPerPeak(Amplitude, Constants::Level[channelID], time_level_per_peak[channelID]);
                pointer.GetWidthPerPeak(Amplitude, Constants::CF[channelID]*max_ampl[channelID],width_at_cft_per_peak[channelID]);
            }
        }
        untime = pointer.UnixTime;
        tdc = pointer.TDC;
        eventid = pointer.EventID;

        tree->Fill();

        for (Int_t i = 0; i < Constants::nCh; i++)
        {
            AmplitudeRaw[i]     = -999;
            Amplitude[i]        = -999;
            max_ampl[i]         = -999;
            min_ampl[i]         = -999;
            time_max_ampl[i]    = -999;
            time_min_ampl[i]    = -999;
            width_at_cft[i]     = -999;
            time_level[i]       = -999;
            time_cf[i]          = -999;
            mean_value_16p[i]   = -999;
            rise_time[i]        = -999;
            fall_time[i]        = -999;
            charge[i]           = -999;
            num_peaks[i]        = -999;
            num_peaks_true[i]   = -999;

            for(Int_t j = 0; j < Constants::nPeakMax; j++)
            {
                max_ampl_per_peak[i][j]         = -999;
                time_max_ampl_per_peak[i][j]    = -999;
                width_at_cft_per_peak[i][j]     = -999;
                time_level_per_peak[i][j]       = -999;
            }
        }
        eventid = -999;
        if(eventID_iter%1000 == 0)
        {
            printf("\r--> Working: %3.1f %%",100*(Double_t)eventID_iter/nEvents);
            fflush(stdout);
        }
    }
    cout<<endl;
    file->Write();
    file->Close();

    return 0;
}
