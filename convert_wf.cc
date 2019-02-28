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

    TString amplitude_ss    = "amplitude[";
    TString untime_ss       = "untime/D";
    TString eventid_ss      = "eventid/I";
    TString tdc_ss          = "tdc/D";
    TString baseline_ss     = "baseline[";
    TString peak_ss         = "peak[";
    TString peaktime_ss     = "peaktime[";
    TString charge_ss       = "charge[";
    TString risingtime_ss   = "risingtime[";
    TString fallingtime_ss  = "fallingtime[";
    TString peaknum_ss      = "peaknum[";

    amplitude_ss += Constants::nCh;
    amplitude_ss += "][";
    amplitude_ss += Constants::nPnt;
    amplitude_ss +="]/D";
    baseline_ss += Constants::nCh;
    baseline_ss += "]/D";
    peak_ss += Constants::nCh;
    peak_ss += "]/D";
    peaktime_ss += Constants::nCh;
    peaktime_ss += "]/D";
    charge_ss += Constants::nCh;
    charge_ss += "]/D";
    risingtime_ss += Constants::nCh;
    risingtime_ss += "]/D";
    fallingtime_ss += Constants::nCh;
    fallingtime_ss += "]/D";
    peaknum_ss += Constants::nCh;
    peaknum_ss += "]/D";

    string word;
    Int_t chid, pntid, eventid, chid_id = 0;
    Double_t amplitude[Constants::nCh][Constants::nPnt], untime, tdc, baseline[Constants::nCh], peak[Constants::nCh],
            peaktime[Constants::nCh], charge[Constants::nCh], risingtime[Constants::nCh], fallingtime[Constants::nCh],
            peaknum[Constants::nCh];

    tree->Branch("Amplitude",   amplitude,      amplitude_ss.Data());
    tree->Branch("UnixTime",    &untime,        untime_ss.Data());
    tree->Branch("EventID",     &eventid,       eventid_ss.Data());
    tree->Branch("TDC",         &tdc,           tdc_ss.Data());
    tree->Branch("BaseLine",    baseline,       baseline_ss.Data());
    tree->Branch("Peak",        peak,           peak_ss.Data());
    tree->Branch("PeakTime",    peaktime,       peaktime_ss.Data());
    tree->Branch("Charge",      charge,         charge_ss.Data());
    tree->Branch("RisingTime",  risingtime,     risingtime_ss.Data());
    tree->Branch("FallingTime", fallingtime,    fallingtime_ss.Data());
    tree->Branch("PeakNum",     peaknum,        peaknum_ss.Data());

    ifstream fp(argv[2]);
    string NameOfTheFile;
    while(fp>>NameOfTheFile)
    {
        TString inputFileName = argv[1]; inputFileName += NameOfTheFile;
        ifstream txt(inputFileName.Data());
        cout<<"Reading the file: "<<inputFileName.Data()<<endl;
        while (txt>>word)
        {
            if(word == "Event")
            {
                chid_id = 0;
                txt>>eventid;
                txt>>word; txt>>word;
                txt>>untime;
                txt>>word; txt>>word;
                txt>>word; txt>>word; txt>>word;
                txt>>tdc;

//                cout<<"--> EventID: "<<eventid<<" | UnixTime: "<<untime<<" | TDC: "<<tdc<<endl;

                while(txt>>word)
                {
                    if(word=="CH:")
                    {
                        txt>>chid; chid = chid_id; chid_id++;
                        txt>>word; txt>>word;
                        txt>>word; txt>>word;
                        txt>>word; txt>>baseline[chid];
                        txt>>word; txt>>peak[chid];
                        txt>>word; txt>>peaktime[chid];
                        txt>>word; txt>>charge[chid];
                        txt>>word; txt>>risingtime[chid];
                        txt>>word; txt>>fallingtime[chid];
                        txt>>word; txt>>peaknum[chid];

                        /*cout<<"---->> CH: "<<chid<<" | BaseLine: "<<baseline[chid]<<" | Peak: "<<peak[chid]
                           <<" | PeakTime: "<<peaktime[chid]<<" | Charge: "<<charge[chid]<<" | RisingTime: "<<risingtime[chid]
                          <<" | FallingTime: "<<fallingtime[chid]<<" | PeakNum: "<<peaknum[chid]<<endl;*/

                        for(pntid = 0; pntid < Constants::nPnt; pntid++)
                        {
                            txt>>amplitude[chid][pntid];
                        }

                        if(chid >= Constants::nCh - 1) break;
                    }
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



