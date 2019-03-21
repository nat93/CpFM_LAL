//root
#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

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

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [0] - Script name"<<endl;
        cout<<"--> [1] - Input filename .dat"<<endl;
        cout<<"--> [2] - Output filename .root"<<endl;
        cout<<endl;
        assert(0);
    }

    TFile *file = new TFile(argv[2],"recreate");
    TTree *tree = new TTree("Tree","A Root Tree");

    Double_t position;
    Double_t untime;

    TString position_ss = "position/D";
    TString untime_ss = "untime/D";

    tree->Branch("MotorPosition", &position, position_ss.Data());
    tree->Branch("UnixTime", &untime, untime_ss.Data());

    cout<<"--> input file: "<<argv[1]<<endl;
    ifstream infile(argv[1]);

    while (infile>>untime)
    {
        infile>>position;
        untime *= 1e6;

        tree->Fill();
    }

	file->Write();
    file->Close();

    cout<<"--> output file: "<<argv[2]<<endl;
}
