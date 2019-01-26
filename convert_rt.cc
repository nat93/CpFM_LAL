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
    Int_t eventid;
    Double_t untime;
    Double_t tdc;
    Double_t rate[Constants::nCh];

    TString tdc_ss              = "tdc/D";
    TString untime_ss           = "untime/D";
    TString rate_ss             = "rate[";
    TString eventid_ss          = "eventid/I";

    rate_ss += Constants::nCh;
    rate_ss +="]/D";

    tree->Branch("UnixTime",    &untime,    untime_ss.Data());
    tree->Branch("TDC",         &tdc,       tdc_ss.Data());
    tree->Branch("EventID",     &eventid,   eventid_ss.Data());
    tree->Branch("Rate",        rate,       rate_ss.Data());

    string word;
    ifstream fp(argv[2]);
    string NameOfTheFile;
    eventid = -999;
    while(fp>>NameOfTheFile)
    {
        TString inputFileName = argv[1]; inputFileName += NameOfTheFile;
        ifstream txt(inputFileName.Data());
        if(txt.is_open())
            cout<<"Reading the file: "<<inputFileName<<endl;
        else
            cout<<"Cannot read the file: "<<inputFileName<<endl;

        while(txt>>word)
        {
            if(word == "Event")
            {
                txt>>eventid;           //EventID
                txt>>word; txt>>word;
                txt>>untime;            //UnixTime
                txt>>word; txt>>word;   //Timestamp
                txt>>word; txt>>word;
                txt>>word;
                txt>>tdc;               //TDC
                txt>>word;

                for(Int_t i = 0; i < Constants::nCh; i++)
                {
                    txt>>rate[i]; //Rate
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
