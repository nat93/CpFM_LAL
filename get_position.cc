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
    if(argc < 5)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [1] - A name of the input .root file with position."<<endl;
        cout<<"--> [2] - Beginning time Unix Time for position."<<endl;
        cout<<"--> [3] - A name of the input .root file with parameters."<<endl;
        cout<<"--> [4] - A name of the output .root file with position."<<endl;
        cout<<endl;
        return -1;
    }

    Float_t tqcd_51991_lvdt;
    Int_t time;
    Double_t untime;

    TChain *fChain1 = new TChain("tree");
    TChain *fChain2 = new TChain("Tree");
    fChain1->Add(argv[1]);
    fChain2->Add(argv[3]);

    fChain1->SetBranchAddress("tqcd_51991_lvdt", &tqcd_51991_lvdt);
    fChain1->SetBranchAddress("t", &time);
    fChain2->SetBranchAddress("UnixTime", &untime);

    Double_t nEntries1 = fChain1->GetEntries();
    cout<<"The number of Entries:  "<<nEntries1<<endl;
    Double_t nEntries2 = fChain2->GetEntries();
    cout<<"The number of Entries:  "<<nEntries2<<endl;

    TFile *file = new TFile(argv[4],"recreate");
	TTree *tree = new TTree("Tree","A Root Tree");

	Double_t position;
    Double_t time_00_00 = atof(argv[2]);

	TString position_ss = "position/D";
    TString untime_ss = "untime/D";
	
	tree->Branch("MotorPosition", &position, position_ss.Data());
    tree->Branch("UnixTime", &untime, untime_ss.Data());

    Int_t eventID1 = 0;
    Int_t eventID2 = 0;
    Int_t div = 0.05*nEntries2;
    fChain1->GetEntry(eventID1);
    Double_t old_time = time*1000000.0 + time_00_00;
    Double_t new_time = time*1000000.0 + time_00_00;
    Double_t old_pos = tqcd_51991_lvdt;
    Double_t new_pos = tqcd_51991_lvdt;

    cout<<"Please wait ..."<<endl;

    while(eventID2 < nEntries2)
    {
        fChain2->GetEntry(eventID2);

        if(untime > old_time)
        {
            break;
        }

        position = old_pos;
        eventID2++;

        if (eventID2%div == 0)
        {
            cout<<"--> "<<100.0*eventID2/nEntries2<<" % "<<endl;
        }

        tree->Fill();
    }
    eventID1++;

    while(eventID1 < nEntries1)
	{		
        fChain1->GetEntry(eventID1);
        new_time = time*1000000.0 + time_00_00;
        new_pos = tqcd_51991_lvdt;

        while(eventID2 < nEntries2)
        {
            fChain2->GetEntry(eventID2);            

            if(untime <= new_time)
            {
                if(new_time - old_time != 0)
                    position = ((new_pos - old_pos)/(new_time - old_time))*untime + (old_pos - old_time*(new_pos - old_pos)/(new_time - old_time));
                else
                    position = new_pos;
            }
            else
            {
                break;
            }

            if (eventID2%div == 0)
            {
                cout<<"--> "<<100.0*eventID2/nEntries2<<" % "<<endl;
            }
            eventID2++;
            tree->Fill();
        }

        old_time = new_time;
        old_pos = new_pos;
        eventID1++;
    }
    while(eventID2 < nEntries2)
    {
        fChain2->GetEntry(eventID2);

        position = old_pos;
        eventID2++;

        if (eventID2%div == 0)
        {
            cout<<"--> "<<100.0*eventID2/nEntries2<<" % "<<endl;
        }

        tree->Fill();
    }
    //rintf("counter=%10.d untime=%20.f  new_time=%20.f  old_time=%20.f\n",counter,untime,new_time,old_time);
	file->Write();
	file->Close();

    delete fChain1->GetCurrentFile();
    delete fChain2->GetCurrentFile();
}
