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
#include "TMath.h"
#include "TF1.h"
#include "TLine.h"
#include "TMultiGraph.h"
#include "TPaveText.h"

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

int plotHisto()
{
/*
    TFile* file = new TFile("./root_files/output5.root");
    file->ls();

    TProfile* profile_nparticles_vs_motor_position1_ampl_cut = (TProfile*)file->Get("profile_nparticles_vs_motor_position[1]_ampl_calculated_cut");
    TProfile* profile_nparticles_vs_motor_position2_ampl_cut = (TProfile*)file->Get("profile_nparticles_vs_motor_position[2]_ampl_calculated_cut");
    TProfile* profile_nparticles_vs_motor_position1_charge_cut = (TProfile*)file->Get("profile_nparticles_vs_motor_position[1]_charge_calculated_cut");
    TProfile* profile_nparticles_vs_motor_position2_charge_cut = (TProfile*)file->Get("profile_nparticles_vs_motor_position[2]_charge_calculated_cut");

    profile_nparticles_vs_motor_position1_ampl_cut->Rebin(10);
    profile_nparticles_vs_motor_position2_ampl_cut->Rebin(10);
    profile_nparticles_vs_motor_position1_charge_cut->Rebin(10);
    profile_nparticles_vs_motor_position2_charge_cut->Rebin(10);

    Int_t n1 = profile_nparticles_vs_motor_position1_ampl_cut->GetNbinsX();
    Int_t n2 = profile_nparticles_vs_motor_position2_ampl_cut->GetNbinsX();
    Int_t n3 = profile_nparticles_vs_motor_position1_charge_cut->GetNbinsX();
    Int_t n4 = profile_nparticles_vs_motor_position2_charge_cut->GetNbinsX();
    const Int_t nBinX1 = n1;
    const Int_t nBinX2 = n2;
    const Int_t nBinX3 = n3;
    const Int_t nBinX4 = n4;

    Double_t x_profile_nparticles_vs_motor_position1_ampl_cut[nBinX1];
    Double_t err_x_profile_nparticles_vs_motor_position1_ampl_cut[nBinX1];
    Double_t y_profile_nparticles_vs_motor_position1_ampl_cut[nBinX1];
    Double_t err_y_profile_nparticles_vs_motor_position1_ampl_cut[nBinX1];

    Double_t x_profile_nparticles_vs_motor_position2_ampl_cut[nBinX2];
    Double_t err_x_profile_nparticles_vs_motor_position2_ampl_cut[nBinX2];
    Double_t y_profile_nparticles_vs_motor_position2_ampl_cut[nBinX2];
    Double_t err_y_profile_nparticles_vs_motor_position2_ampl_cut[nBinX2];

    Double_t x_profile_nparticles_vs_motor_position1_charge_cut[nBinX3];
    Double_t err_x_profile_nparticles_vs_motor_position1_charge_cut[nBinX3];
    Double_t y_profile_nparticles_vs_motor_position1_charge_cut[nBinX3];
    Double_t err_y_profile_nparticles_vs_motor_position1_charge_cut[nBinX3];

    Double_t x_profile_nparticles_vs_motor_position2_charge_cut[nBinX4];
    Double_t err_x_profile_nparticles_vs_motor_position2_charge_cut[nBinX4];
    Double_t y_profile_nparticles_vs_motor_position2_charge_cut[nBinX4];
    Double_t err_y_profile_nparticles_vs_motor_position2_charge_cut[nBinX4];

    Double_t  Ap_CpFM_calculated1 = 0.00102998;
    Double_t  Ap_CpFM_calculated2 = 0.00358228;
    Double_t  errAp_CpFM_calculated1 = 0.000206283/profile_nparticles_vs_motor_position1_ampl_cut->GetEffectiveEntries();
    Double_t  errAp_CpFM_calculated2 = 0.000137642/profile_nparticles_vs_motor_position2_ampl_cut->GetEffectiveEntries();

    Double_t  Qp_CpFM_calculated1 = 25.9039;
    Double_t  Qp_CpFM_calculated2 = 118.81;
    Double_t  errQp_CpFM_calculated1 = 4.94504/profile_nparticles_vs_motor_position1_charge_cut->GetEffectiveEntries();
    Double_t  errQp_CpFM_calculated2 = 7.74099/profile_nparticles_vs_motor_position2_charge_cut->GetEffectiveEntries();

    Double_t shiftValue = 6.0;

    for(Int_t i = 0; i < nBinX1; i++)
    {
        x_profile_nparticles_vs_motor_position1_ampl_cut[i] = profile_nparticles_vs_motor_position1_ampl_cut->GetBinCenter(i);
        err_x_profile_nparticles_vs_motor_position1_ampl_cut[i] = profile_nparticles_vs_motor_position1_ampl_cut->GetBinWidth(i);
        y_profile_nparticles_vs_motor_position1_ampl_cut[i] = profile_nparticles_vs_motor_position1_ampl_cut->GetBinContent(i);
        err_y_profile_nparticles_vs_motor_position1_ampl_cut[i] = TMath::Sqrt(TMath::Power(profile_nparticles_vs_motor_position1_ampl_cut->GetBinError(i),2)
                                                                              + TMath::Power((errAp_CpFM_calculated1/Ap_CpFM_calculated1)*(profile_nparticles_vs_motor_position1_ampl_cut->GetBinContent(i)),2));
    }
    for(Int_t i = 0; i < nBinX2; i++)
    {
        x_profile_nparticles_vs_motor_position2_ampl_cut[i] = profile_nparticles_vs_motor_position2_ampl_cut->GetBinCenter(i) - shiftValue;
        err_x_profile_nparticles_vs_motor_position2_ampl_cut[i] = profile_nparticles_vs_motor_position2_ampl_cut->GetBinWidth(i);
        y_profile_nparticles_vs_motor_position2_ampl_cut[i] = profile_nparticles_vs_motor_position2_ampl_cut->GetBinContent(i);
        err_y_profile_nparticles_vs_motor_position2_ampl_cut[i] = TMath::Sqrt(TMath::Power(profile_nparticles_vs_motor_position2_ampl_cut->GetBinError(i),2)
                                                                              + TMath::Power((errAp_CpFM_calculated2/Ap_CpFM_calculated2)*(profile_nparticles_vs_motor_position2_ampl_cut->GetBinContent(i)),2));
    }

    for(Int_t i = 0; i < nBinX3; i++)
    {
        x_profile_nparticles_vs_motor_position1_charge_cut[i] = profile_nparticles_vs_motor_position1_charge_cut->GetBinCenter(i);
        err_x_profile_nparticles_vs_motor_position1_charge_cut[i] = profile_nparticles_vs_motor_position1_charge_cut->GetBinWidth(i);
        y_profile_nparticles_vs_motor_position1_charge_cut[i] = profile_nparticles_vs_motor_position1_charge_cut->GetBinContent(i);
        err_y_profile_nparticles_vs_motor_position1_charge_cut[i] = TMath::Sqrt(TMath::Power(profile_nparticles_vs_motor_position1_charge_cut->GetBinError(i),2)
                                                                              + TMath::Power((errQp_CpFM_calculated1/Qp_CpFM_calculated1)*(profile_nparticles_vs_motor_position1_charge_cut->GetBinContent(i)),2));
    }
    for(Int_t i = 0; i < nBinX4; i++)
    {
        x_profile_nparticles_vs_motor_position2_charge_cut[i] = profile_nparticles_vs_motor_position2_charge_cut->GetBinCenter(i) - shiftValue;
        err_x_profile_nparticles_vs_motor_position2_charge_cut[i] = profile_nparticles_vs_motor_position2_charge_cut->GetBinWidth(i);
        y_profile_nparticles_vs_motor_position2_charge_cut[i] = profile_nparticles_vs_motor_position2_charge_cut->GetBinContent(i);
        err_y_profile_nparticles_vs_motor_position2_charge_cut[i] = TMath::Sqrt(TMath::Power(profile_nparticles_vs_motor_position2_charge_cut->GetBinError(i),2)
                                                                              + TMath::Power((errQp_CpFM_calculated2/Qp_CpFM_calculated2)*(profile_nparticles_vs_motor_position2_charge_cut->GetBinContent(i)),2));
    }

    TGraphErrors* gr_profile_nparticles_vs_motor_position1_ampl = new TGraphErrors(nBinX1,x_profile_nparticles_vs_motor_position1_ampl_cut,y_profile_nparticles_vs_motor_position1_ampl_cut,err_x_profile_nparticles_vs_motor_position1_ampl_cut,err_y_profile_nparticles_vs_motor_position1_ampl_cut);
    TGraphErrors* gr_profile_nparticles_vs_motor_position2_ampl = new TGraphErrors(nBinX2,x_profile_nparticles_vs_motor_position2_ampl_cut,y_profile_nparticles_vs_motor_position2_ampl_cut,err_x_profile_nparticles_vs_motor_position2_ampl_cut,err_y_profile_nparticles_vs_motor_position2_ampl_cut);

    TGraphErrors* gr_profile_nparticles_vs_motor_position1_charge = new TGraphErrors(nBinX3,x_profile_nparticles_vs_motor_position1_charge_cut,y_profile_nparticles_vs_motor_position1_charge_cut,err_x_profile_nparticles_vs_motor_position1_charge_cut,err_y_profile_nparticles_vs_motor_position1_charge_cut);
    TGraphErrors* gr_profile_nparticles_vs_motor_position2_charge = new TGraphErrors(nBinX4,x_profile_nparticles_vs_motor_position2_charge_cut,y_profile_nparticles_vs_motor_position2_charge_cut,err_x_profile_nparticles_vs_motor_position2_charge_cut,err_y_profile_nparticles_vs_motor_position2_charge_cut);


    gr_profile_nparticles_vs_motor_position1_ampl->SetLineColor(kBlue);
    gr_profile_nparticles_vs_motor_position1_ampl->SetLineStyle(1);
    gr_profile_nparticles_vs_motor_position1_ampl->SetLineWidth(2);
    gr_profile_nparticles_vs_motor_position1_ampl->SetMarkerStyle(20);
    gr_profile_nparticles_vs_motor_position1_ampl->SetTitle("CpFM1 (from Amplitude)");
    gr_profile_nparticles_vs_motor_position1_ampl->SetFillColor(0);

    gr_profile_nparticles_vs_motor_position2_ampl->SetLineColor(kRed);
    gr_profile_nparticles_vs_motor_position2_ampl->SetLineStyle(1);
    gr_profile_nparticles_vs_motor_position2_ampl->SetLineWidth(2);
    gr_profile_nparticles_vs_motor_position2_ampl->SetMarkerStyle(21);
    gr_profile_nparticles_vs_motor_position2_ampl->SetTitle("CpFM2 (from Amplitude)");
    gr_profile_nparticles_vs_motor_position2_ampl->SetFillColor(0);

    gr_profile_nparticles_vs_motor_position1_charge->SetLineColor(kBlue);
    gr_profile_nparticles_vs_motor_position1_charge->SetLineStyle(1);
    gr_profile_nparticles_vs_motor_position1_charge->SetLineWidth(2);
    gr_profile_nparticles_vs_motor_position1_charge->SetMarkerStyle(20);
    gr_profile_nparticles_vs_motor_position1_charge->SetTitle("CpFM1 (from Charge)");
    gr_profile_nparticles_vs_motor_position1_charge->SetFillColor(0);

    gr_profile_nparticles_vs_motor_position2_charge->SetLineColor(kRed);
    gr_profile_nparticles_vs_motor_position2_charge->SetLineStyle(1);
    gr_profile_nparticles_vs_motor_position2_charge->SetLineWidth(2);
    gr_profile_nparticles_vs_motor_position2_charge->SetMarkerStyle(21);
    gr_profile_nparticles_vs_motor_position2_charge->SetTitle("CpFM2 (from Charge)");
    gr_profile_nparticles_vs_motor_position2_charge->SetFillColor(0);

    TMultiGraph* mg1 = new TMultiGraph();

    mg1->Add(gr_profile_nparticles_vs_motor_position1_ampl);
    mg1->Add(gr_profile_nparticles_vs_motor_position2_ampl);
    mg1->SetMaximum(170);
    mg1->SetMinimum(-5);

    TMultiGraph* mg2 = new TMultiGraph();

    mg2->Add(gr_profile_nparticles_vs_motor_position1_charge);
    mg2->Add(gr_profile_nparticles_vs_motor_position2_charge);
    mg2->SetMaximum(160);
    mg2->SetMinimum(-5);

    TCanvas* c1 = new TCanvas();
    c1->cd();
    mg1->Draw("APL");
    c1->BuildLegend();

    TCanvas* c2 = new TCanvas();
    c2->cd();
    mg2->Draw("APL");
    c2->BuildLegend();
*/
/*
    TFile* file = new TFile("output5_parking.root");
    file->ls();

    //---------------------------- AMPLITUDE -----------------------------------------------------------//
    TH2D* histo1 = (TH2D*)file->Get("max_ampl[1]");
    TH2D* histo1_cut = (TH2D*)file->Get("max_ampl[1]_cut");
    TH2D* histo2 = (TH2D*)file->Get("max_ampl[2]");
    TH2D* histo2_cut = (TH2D*)file->Get("max_ampl[2]_cut");

    histo1->SetLineColor(kBlue);
    histo1->SetLineWidth(2);

    histo1_cut->SetLineColor(kBlack);
    histo1_cut->SetLineWidth(2);

    histo2->SetLineColor(kBlue);
    histo2->SetLineWidth(2);

    histo2_cut->SetLineColor(kBlack);
    histo2_cut->SetLineWidth(2);

    histo1->Rebin(2);
    histo1_cut->Rebin(2);
    histo2->Rebin(2);
    histo2_cut->Rebin(2);

    TCanvas* c1 = new TCanvas();
    c1->cd();
    histo1->Draw();
    histo1_cut->Draw("same");

    Double_t par1[3];
    TF1 *g1 = new TF1("g1","gaus",0.001,0.006);
    g1->SetLineColor(kGreen);
    histo1->Fit(g1,"NR");
    g1->GetParameters(&par1[0]);
    TF1 *f_g1 = new TF1("f_g1","gaus",histo1->GetBinLowEdge(0),histo1->GetBinWidth(histo1->GetNbinsX())*histo1->GetNbinsX());
    f_g1->SetParameters(par1[0],par1[1],par1[2]);
    f_g1->SetLineColor(kGreen);
    f_g1->Draw("same");

    TH1D* histo1_nozeros = new TH1D("histo1_nozeros","histo1_nozeros",histo1->GetNbinsX(),histo1->GetBinLowEdge(0),histo1->GetBinWidth(histo1->GetNbinsX())*histo1->GetNbinsX());
    for(Int_t i = 0; i < histo1->GetNbinsX(); i++)
    {
        histo1_nozeros->SetBinContent(i,histo1->GetBinContent(i)-par1[0]*TMath::Gaus(histo1->GetBinCenter(i),par1[1],par1[2]));
    }

    histo1_nozeros->SetLineColor(kMagenta);
    histo1_nozeros->SetLineWidth(2);
    histo1_nozeros->Draw("same");

    TH1D *histo1_zeros = new TH1D("histo1_zeros","histo1_zeros",histo1->GetNbinsX(),0,2);
    TH1D *histo1_final = new TH1D("histo1_final","histo1_final",histo1->GetNbinsX(),0,2);
    histo1_zeros->FillRandom("f_g1",208343);

    for(Int_t i = 0; i < histo1->GetNbinsX(); i++)
    {
        histo1_final->SetBinContent(i,histo1_nozeros->GetBinContent(i) + histo1_zeros->GetBinContent(i));
    }

    histo1_final->SetLineWidth(2);
    histo1_final->SetLineColor(kRed);
    histo1_final->Draw("same");

    TCanvas* c2 = new TCanvas();
    c2->cd();
    histo2->Draw();
    histo2_cut->Draw("same");

    Double_t par2[3];
    TF1 *g2 = new TF1("g2","gaus",0.001,0.006);
    g2->SetLineColor(kGreen);
    histo2->Fit(g2,"NR");
    g2->GetParameters(&par2[0]);
    TF1 *f_g2 = new TF1("f_g2","gaus",histo2->GetBinLowEdge(0),histo2->GetBinWidth(histo2->GetNbinsX())*histo2->GetNbinsX());
    f_g2->SetParameters(par2[0],par2[1],par2[2]);
    f_g2->SetLineColor(kGreen);
    f_g2->Draw("same");

    TH1D* histo2_nozeros = new TH1D("histo2_nozeros","histo2_nozeros",histo2->GetNbinsX(),histo2->GetBinLowEdge(0),histo2->GetBinWidth(histo2->GetNbinsX())*histo2->GetNbinsX());
    for(Int_t i = 0; i < histo2->GetNbinsX(); i++)
    {
        histo2_nozeros->SetBinContent(i,histo2->GetBinContent(i)-par2[0]*TMath::Gaus(histo2->GetBinCenter(i),par2[1],par2[2]));
    }

    histo2_nozeros->SetLineColor(kMagenta);
    histo2_nozeros->SetLineWidth(2);
    histo2_nozeros->Draw("same");

    TH1D *histo2_zeros = new TH1D("histo2_zeros","histo2_zeros",histo2->GetNbinsX(),0,2);
    TH1D *histo2_final = new TH1D("histo2_final","histo2_final",histo2->GetNbinsX(),0,2);
    histo2_zeros->FillRandom("f_g2",73935);

    for(Int_t i = 0; i < histo2->GetNbinsX(); i++)
    {
        histo2_final->SetBinContent(i,histo2_nozeros->GetBinContent(i) + histo2_zeros->GetBinContent(i));
    }

    histo2_final->SetLineWidth(2);
    histo2_final->SetLineColor(kRed);
    histo2_final->Draw("same");

    cout<<" For Amplitude:"<<endl;
    cout<<" Amean(CpFM1) = "<<histo1_final->GetMean()<<endl;
    cout<<" Amean(CpFM2) = "<<histo2_final->GetMean()<<endl;

    //---------------------------- CHARGE -----------------------------------------------------------//
    TH2D* histo3 = (TH2D*)file->Get("charge[1]");
    TH2D* histo3_cut = (TH2D*)file->Get("charge[1]_cut");
    TH2D* histo4 = (TH2D*)file->Get("charge[2]");
    TH2D* histo4_cut = (TH2D*)file->Get("charge[2]_cut");

    histo3->SetLineColor(kBlue);
    histo3->SetLineWidth(2);

    histo3_cut->SetLineColor(kBlack);
    histo3_cut->SetLineWidth(2);

    histo4->SetLineColor(kBlue);
    histo4->SetLineWidth(2);

    histo4_cut->SetLineColor(kBlack);
    histo4_cut->SetLineWidth(2);

    histo3->Rebin(2);
    histo3_cut->Rebin(2);
    histo4->Rebin(2);
    histo4_cut->Rebin(2);

    TCanvas* c3 = new TCanvas();
    c3->cd();
    histo3->Draw();
    histo3_cut->Draw("same");

    Double_t par3[3];
    TF1 *g3 = new TF1("g3","gaus",-200,200);
    g3->SetLineColor(kGreen);
    histo3->Fit(g3,"NR");
    g3->GetParameters(&par3[0]);
    TF1 *f_g3 = new TF1("f_g3","gaus",histo3->GetBinLowEdge(0),histo3->GetBinWidth(histo3->GetNbinsX())*histo3->GetNbinsX());
    f_g3->SetParameters(par3[0],par3[1],par3[2]);
    f_g3->SetLineColor(kGreen);
    f_g3->Draw("same");

    TH1D *histo3_zeros = new TH1D("histo3_zeros","histo3_zeros",histo3->GetNbinsX(),-1000,4000);
    TH1D *histo3_final = new TH1D("histo3_final","histo3_final",histo3->GetNbinsX(),-1000,4000);
    histo3_zeros->FillRandom("f_g3",208343);

    for(Int_t i = 0; i < histo3->GetNbinsX(); i++)
    {
        histo3_final->SetBinContent(i,histo3_cut->GetBinContent(i) + histo3_zeros->GetBinContent(i));
    }

    histo3_final->SetLineWidth(2);
    histo3_final->SetLineColor(kRed);
    histo3_final->Draw("same");

    TCanvas* c4 = new TCanvas();
    c4->cd();
    histo4->Draw();
    histo4_cut->Draw("same");

    Double_t par4[3];
    TF1 *g4 = new TF1("g4","gaus",-200,200);
    g4->SetLineColor(kGreen);
    histo4->Fit(g4,"NR");
    g4->GetParameters(&par4[0]);
    TF1 *f_g4 = new TF1("f_g4","gaus",histo4->GetBinLowEdge(0),histo4->GetBinWidth(histo4->GetNbinsX())*histo4->GetNbinsX());
    f_g4->SetParameters(par4[0],par4[1],par4[2]);
    f_g4->SetLineColor(kGreen);
    f_g4->Draw("same");

    TH1D *histo4_zeros = new TH1D("histo4_zeros","histo4_zeros",histo4->GetNbinsX(),-1000,4000);
    TH1D *histo4_final = new TH1D("histo4_final","histo4_final",histo4->GetNbinsX(),-1000,4000);
    histo4_zeros->FillRandom("f_g4",73935);

    for(Int_t i = 0; i < histo4->GetNbinsX(); i++)
    {
        histo4_final->SetBinContent(i,histo4_cut->GetBinContent(i) + histo4_zeros->GetBinContent(i));
    }

    histo4_final->SetLineWidth(2);
    histo4_final->SetLineColor(kRed);
    histo4_final->Draw("same");

    cout<<" For Charge:"<<endl;
    cout<<" Qmean(CpFM1) = "<<histo3_final->GetMean()<<endl;
    cout<<" Qmean(CpFM2) = "<<histo4_final->GetMean()<<endl;
*/

/*
    TFile* file = new TFile("output5.root");
    file->ls();

    TProfile* profile_nParticles_vs_time1_ampl_expected = (TProfile*)file->Get("profile_nParticles_vs_time[1]_ampl_expected");
    TProfile* profile_nParticles_vs_time2_ampl_expected = (TProfile*)file->Get("profile_nParticles_vs_time[2]_ampl_expected");
    TProfile* profile_nParticles_vs_time1_charge_expected = (TProfile*)file->Get("profile_nParticles_vs_time[1]_charge_expected");
    TProfile* profile_nParticles_vs_time2_charge_expected = (TProfile*)file->Get("profile_nParticles_vs_time[2]_charge_expected");

    TProfile* profile_nParticles_vs_time1_ampl_calculated = (TProfile*)file->Get("profile_nParticles_vs_time[1]_ampl_calculated");
    TProfile* profile_nParticles_vs_time2_ampl_calculated = (TProfile*)file->Get("profile_nParticles_vs_time[2]_ampl_calculated");
    TProfile* profile_nParticles_vs_time1_charge_calculated = (TProfile*)file->Get("profile_nParticles_vs_time[1]_charge_calculated");
    TProfile* profile_nParticles_vs_time2_charge_calculated = (TProfile*)file->Get("profile_nParticles_vs_time[2]_charge_calculated");

    const Int_t n = 200;
    Double_t x_profile_nParticles_vs_time1_ampl_expected[n];
    Double_t y_profile_nParticles_vs_time1_ampl_expected[n];
    Double_t x_profile_nParticles_vs_time2_ampl_expected[n];
    Double_t y_profile_nParticles_vs_time2_ampl_expected[n];
    Double_t x_profile_nParticles_vs_time1_charge_expected[n];
    Double_t y_profile_nParticles_vs_time1_charge_expected[n];
    Double_t x_profile_nParticles_vs_time2_charge_expected[n];
    Double_t y_profile_nParticles_vs_time2_charge_expected[n];

    Double_t x_profile_nParticles_vs_time1_ampl_calculated[n];
    Double_t y_profile_nParticles_vs_time1_ampl_calculated[n];
    Double_t x_profile_nParticles_vs_time2_ampl_calculated[n];
    Double_t y_profile_nParticles_vs_time2_ampl_calculated[n];
    Double_t x_profile_nParticles_vs_time1_charge_calculated[n];
    Double_t y_profile_nParticles_vs_time1_charge_calculated[n];
    Double_t x_profile_nParticles_vs_time2_charge_calculated[n];
    Double_t y_profile_nParticles_vs_time2_charge_calculated[n];

    for(Int_t i = 0; i < n; i++)
    {
	x_profile_nParticles_vs_time1_ampl_expected[i] = profile_nParticles_vs_time1_ampl_expected->GetBinCenter(i);
	y_profile_nParticles_vs_time1_ampl_expected[i] = profile_nParticles_vs_time1_ampl_expected->GetBinContent(i);
	x_profile_nParticles_vs_time2_ampl_expected[i] = profile_nParticles_vs_time2_ampl_expected->GetBinCenter(i);
	y_profile_nParticles_vs_time2_ampl_expected[i] = profile_nParticles_vs_time2_ampl_expected->GetBinContent(i);
	x_profile_nParticles_vs_time1_charge_expected[i] = profile_nParticles_vs_time1_charge_expected->GetBinCenter(i);
	y_profile_nParticles_vs_time1_charge_expected[i] = profile_nParticles_vs_time1_charge_expected->GetBinContent(i);
	x_profile_nParticles_vs_time2_charge_expected[i] = profile_nParticles_vs_time2_charge_expected->GetBinCenter(i);
	y_profile_nParticles_vs_time2_charge_expected[i] = profile_nParticles_vs_time2_charge_expected->GetBinContent(i);

	x_profile_nParticles_vs_time1_ampl_calculated[i] = profile_nParticles_vs_time1_ampl_calculated->GetBinCenter(i);
	y_profile_nParticles_vs_time1_ampl_calculated[i] = profile_nParticles_vs_time1_ampl_calculated->GetBinContent(i);
	x_profile_nParticles_vs_time2_ampl_calculated[i] = profile_nParticles_vs_time2_ampl_calculated->GetBinCenter(i);
	y_profile_nParticles_vs_time2_ampl_calculated[i] = profile_nParticles_vs_time2_ampl_calculated->GetBinContent(i);
	x_profile_nParticles_vs_time1_charge_calculated[i] = profile_nParticles_vs_time1_charge_calculated->GetBinCenter(i);
	y_profile_nParticles_vs_time1_charge_calculated[i] = profile_nParticles_vs_time1_charge_calculated->GetBinContent(i);
	x_profile_nParticles_vs_time2_charge_calculated[i] = profile_nParticles_vs_time2_charge_calculated->GetBinCenter(i);
	y_profile_nParticles_vs_time2_charge_calculated[i] = profile_nParticles_vs_time2_charge_calculated->GetBinContent(i);
    }

    TGraph* gr_profile_nParticles_vs_time1_ampl_expected = new TGraph(n,x_profile_nParticles_vs_time1_ampl_expected,y_profile_nParticles_vs_time1_ampl_expected);
    TGraph* gr_profile_nParticles_vs_time2_ampl_expected = new TGraph(n,x_profile_nParticles_vs_time2_ampl_expected,y_profile_nParticles_vs_time2_ampl_expected);
    TGraph* gr_profile_nParticles_vs_time1_charge_expected = new TGraph(n,x_profile_nParticles_vs_time1_charge_expected,y_profile_nParticles_vs_time1_charge_expected);
    TGraph* gr_profile_nParticles_vs_time2_charge_expected = new TGraph(n,x_profile_nParticles_vs_time2_charge_expected,y_profile_nParticles_vs_time2_charge_expected);
    TGraph* gr_profile_nParticles_vs_time1_ampl_calculated = new TGraph(n,x_profile_nParticles_vs_time1_ampl_calculated,y_profile_nParticles_vs_time1_ampl_calculated);
    TGraph* gr_profile_nParticles_vs_time2_ampl_calculated = new TGraph(n,x_profile_nParticles_vs_time2_ampl_calculated,y_profile_nParticles_vs_time2_ampl_calculated);
    TGraph* gr_profile_nParticles_vs_time1_charge_calculated = new TGraph(n,x_profile_nParticles_vs_time1_charge_calculated,y_profile_nParticles_vs_time1_charge_calculated);
    TGraph* gr_profile_nParticles_vs_time2_charge_calculated = new TGraph(n,x_profile_nParticles_vs_time2_charge_calculated,y_profile_nParticles_vs_time2_charge_calculated);


    gr_profile_nParticles_vs_time1_ampl_expected->SetLineColor(kBlue);
    gr_profile_nParticles_vs_time1_ampl_expected->SetLineStyle(2);
    gr_profile_nParticles_vs_time1_ampl_expected->SetLineWidth(2);
    gr_profile_nParticles_vs_time1_ampl_expected->SetTitle("CpFM1 (amplitude) expected");
    gr_profile_nParticles_vs_time1_ampl_expected->SetFillColor(0);

    gr_profile_nParticles_vs_time2_ampl_expected->SetLineColor(kRed);
    gr_profile_nParticles_vs_time2_ampl_expected->SetLineStyle(2);
    gr_profile_nParticles_vs_time2_ampl_expected->SetLineWidth(2);
    gr_profile_nParticles_vs_time2_ampl_expected->SetTitle("CpFM2 (amplitude) expected");
    gr_profile_nParticles_vs_time2_ampl_expected->SetFillColor(0);

    gr_profile_nParticles_vs_time1_charge_expected->SetLineColor(kGreen);
    gr_profile_nParticles_vs_time1_charge_expected->SetLineStyle(2);
    gr_profile_nParticles_vs_time1_charge_expected->SetLineWidth(2);
    gr_profile_nParticles_vs_time1_charge_expected->SetTitle("CpFM1 (charge) expected");
    gr_profile_nParticles_vs_time1_charge_expected->SetFillColor(0);

    gr_profile_nParticles_vs_time2_charge_expected->SetLineColor(kMagenta);
    gr_profile_nParticles_vs_time2_charge_expected->SetLineStyle(2);
    gr_profile_nParticles_vs_time2_charge_expected->SetLineWidth(2);
    gr_profile_nParticles_vs_time2_charge_expected->SetTitle("CpFM2 (charge) expected");
    gr_profile_nParticles_vs_time2_charge_expected->SetFillColor(0);

    gr_profile_nParticles_vs_time1_ampl_calculated->SetLineColor(kBlue);
    gr_profile_nParticles_vs_time1_ampl_calculated->SetLineStyle(1);
    gr_profile_nParticles_vs_time1_ampl_calculated->SetLineWidth(2);
    gr_profile_nParticles_vs_time1_ampl_calculated->SetTitle("CpFM1 (amplitude) calculated");
    gr_profile_nParticles_vs_time1_ampl_calculated->SetFillColor(0);

    gr_profile_nParticles_vs_time2_ampl_calculated->SetLineColor(kRed);
    gr_profile_nParticles_vs_time2_ampl_calculated->SetLineStyle(1);
    gr_profile_nParticles_vs_time2_ampl_calculated->SetLineWidth(2);
    gr_profile_nParticles_vs_time2_ampl_calculated->SetTitle("CpFM2 (amplitude) calculated");
    gr_profile_nParticles_vs_time2_ampl_calculated->SetFillColor(0);

    gr_profile_nParticles_vs_time1_charge_calculated->SetLineColor(kGreen);
    gr_profile_nParticles_vs_time1_charge_calculated->SetLineStyle(1);
    gr_profile_nParticles_vs_time1_charge_calculated->SetLineWidth(2);
    gr_profile_nParticles_vs_time1_charge_calculated->SetTitle("CpFM1 (charge) calculated");
    gr_profile_nParticles_vs_time1_charge_calculated->SetFillColor(0);

    gr_profile_nParticles_vs_time2_charge_calculated->SetLineColor(kMagenta);
    gr_profile_nParticles_vs_time2_charge_calculated->SetLineStyle(1);
    gr_profile_nParticles_vs_time2_charge_calculated->SetLineWidth(2);
    gr_profile_nParticles_vs_time2_charge_calculated->SetTitle("CpFM2 (charge) calculated");
    gr_profile_nParticles_vs_time2_charge_calculated->SetFillColor(0);

    TMultiGraph* mg1 = new TMultiGraph();
    TMultiGraph* mg2 = new TMultiGraph();
    TMultiGraph* mg3 = new TMultiGraph();

    mg1->Add(gr_profile_nParticles_vs_time1_ampl_expected);
    mg1->Add(gr_profile_nParticles_vs_time2_ampl_expected);
    mg1->Add(gr_profile_nParticles_vs_time1_charge_expected);
    mg1->Add(gr_profile_nParticles_vs_time2_charge_expected);
    mg1->Add(gr_profile_nParticles_vs_time1_ampl_calculated);
    mg1->Add(gr_profile_nParticles_vs_time2_ampl_calculated);
    mg1->Add(gr_profile_nParticles_vs_time1_charge_calculated);
    mg1->Add(gr_profile_nParticles_vs_time2_charge_calculated);
    mg1->SetMaximum(70);
    mg1->SetMinimum(-5);

    mg2->Add(gr_profile_nParticles_vs_time1_ampl_calculated);
    mg2->Add(gr_profile_nParticles_vs_time2_ampl_calculated);
    mg2->SetMaximum(70);
    mg2->SetMinimum(-5);

    mg3->Add(gr_profile_nParticles_vs_time1_charge_calculated);
    mg3->Add(gr_profile_nParticles_vs_time2_charge_calculated);
    mg3->SetMaximum(70);
    mg3->SetMinimum(-5);


    TCanvas* c1 = new TCanvas();
    c1->cd();
    mg1->Draw("APL");
    c1->BuildLegend();

    TCanvas* c2 = new TCanvas();
    c2->cd();
    mg2->Draw("APL");
    c2->BuildLegend();

    TCanvas* c3 = new TCanvas();
    c3->cd();
    mg3->Draw("APL");
    c3->BuildLegend();

    TH1D* histo1 = (TH1D*)file->Get("max_ampl[1]");
    TH1D* histo2 = (TH1D*)file->Get("max_ampl[2]");
    TH1D* histo3 = (TH1D*)file->Get("charge[1]");
    TH1D* histo4 = (TH1D*)file->Get("charge[2]");

    Double_t Ap1 = 1.03e-3;Double_t errAp1 = 0.21e-3;
    Double_t Ap2 = 3.58e-3;Double_t errAp2 = 0.14e-3;
    Double_t Qp1 = 25.90;Double_t errQp1 = 4.95;
    Double_t Qp2 = 118.81;Double_t errQp2 = 7.74;

    cout<<"max_ampl[1]mean="<<histo1->GetMean()<<" +/- "<<histo1->GetMeanError()<<" V"<<endl;
    cout<<"max_ampl[2]mean="<<histo2->GetMean()<<" +/- "<<histo2->GetMeanError()<<" V"<<endl;
    cout<<"charge[1]mean="<<histo3->GetMean()<<" +/- "<<histo3->GetMeanError()<<" pC"<<endl;
    cout<<"charge[2]mean="<<histo4->GetMean()<<" +/- "<<histo4->GetMeanError()<<" pC"<<endl;

    cout<<"nparticles_ampl[1]mean="<<histo1->GetMean()/Ap1<<" +/- "<<TMath::Sqrt(TMath::Power(histo1->GetMeanError()/Ap1,2) + TMath::Power(errAp1*histo1->GetMean()/(Ap1*Ap1),2))<<endl;
    cout<<"nparticles_ampl[2]mean="<<histo2->GetMean()/Ap2<<" +/- "<<TMath::Sqrt(TMath::Power(histo2->GetMeanError()/Ap2,2) + TMath::Power(errAp2*histo2->GetMean()/(Ap2*Ap2),2))<<endl;
    cout<<"nparticles_charge[1]mean="<<histo3->GetMean()/Qp1<<" +/- "<<TMath::Sqrt(TMath::Power(histo3->GetMeanError()/Qp1,2) + TMath::Power(errQp1*histo3->GetMean()/(Qp1*Qp1),2))<<endl;
    cout<<"nparticles_charge[2]mean="<<histo4->GetMean()/Qp2<<" +/- "<<TMath::Sqrt(TMath::Power(histo4->GetMeanError()/Qp2,2) + TMath::Power(errQp2*histo4->GetMean()/(Qp2*Qp2),2))<<endl;

    histo1->SetLineColor(kBlue);
    histo1->SetLineStyle(1);
    histo1->SetLineWidth(2);
    histo1->SetFillColor(0);

    histo2->SetLineColor(kRed);
    histo2->SetLineStyle(1);
    histo2->SetLineWidth(2);
    histo2->SetFillColor(0);

    histo1->Rebin(5);
    histo2->Rebin(5);

    TCanvas* c4 = new TCanvas();
    c4->cd();
    histo1->Draw();
    histo2->Draw("same");

    histo3->SetLineColor(kGreen);
    histo3->SetLineStyle(1);
    histo3->SetLineWidth(2);
    histo3->SetFillColor(0);

    histo4->SetLineColor(kMagenta);
    histo4->SetLineStyle(1);
    histo4->SetLineWidth(2);
    histo4->SetFillColor(0);

    histo3->Rebin(2);
    histo4->Rebin(2);

    TCanvas* c5 = new TCanvas();
    c5->cd();
    histo3->Draw();
    histo4->Draw("same");
*/

/*
Double_t Gp1 = 5.63e6;
Double_t Gp2 = 5.73e6;
Double_t Gi1 = 2.33e5;
Double_t Gi2 = 2.90e5;
Double_t K = 1.4873e-4;
Double_t Qi1 = 7208;Double_t errQi1 = 1376;
Double_t Qi2 = 33060;Double_t errQi2 = 2154;
Double_t Ai1 = 0.2866;Double_t errAi1 = 0.0574;
Double_t Ai2 = 0.9968;Double_t errAi2 = 0.0383;
Double_t Qp1, Qp2, Ap1, Ap2;
Double_t errQp1, errQp2, errAp1, errAp2;
Qp1 = (Gp1/Gi1)*Qi1*K;
Qp2 = (Gp1/Gi1)*Qi2*K;
Ap1 = (Gp1/Gi1)*Ai1*K;
Ap2 = (Gp1/Gi1)*Ai2*K;
errQp1 = (Gp1/Gi1)*errQi1*K;
errQp2 = (Gp1/Gi1)*errQi2*K;
errAp1 = (Gp1/Gi1)*errAi1*K;
errAp2 = (Gp1/Gi1)*errAi2*K; 
cout<<"Qp1 = "<<Qp1<<" +/- "<<errQp1<<endl;
cout<<"Qp2 = "<<Qp2<<" +/- "<<errQp2<<endl;
cout<<"Ap1 = "<<Ap1<<" +/- "<<errAp1<<endl;
cout<<"Ap2 = "<<Ap2<<" +/- "<<errAp2<<endl;

Double_t Ape1 = 15.51e-3;Double_t errApe1 = 9.55e-3;
Double_t Ape2 = 16.41e-3;Double_t errApe2 = 8.31e-3;
Double_t eff1_amplitude, eff2_amplitude, erreff1_amplitude, erreff2_amplitude;
eff1_amplitude = Ap1/Ape1;
eff2_amplitude = Ap2/Ape2;
erreff1_amplitude = TMath::Sqrt(TMath::Power(errAp1/Ape1,2) + TMath::Power(Ap1*errApe1/(Ape1*Ape1),2));
erreff2_amplitude = TMath::Sqrt(TMath::Power(errAp2/Ape2,2) + TMath::Power(Ap2*errApe2/(Ape2*Ape2),2));
cout<<"eff1_amplitude(amplitude) = "<<eff1_amplitude<<" +/- "<<erreff1_amplitude<<endl;
cout<<"eff2_amplitude(amplitude) = "<<eff2_amplitude<<" +/- "<<erreff2_amplitude<<endl;

Double_t Qpe1 = 237.5;Double_t errQpe1 = 136.5;
Double_t Qpe2 = 219.6;Double_t errQpe2 = 115.4;
Double_t eff1_charge, eff2_charge, erreff1_charge, erreff2_charge;
eff1_charge = Qp1/Qpe1;
eff2_charge = Qp2/Qpe2;
erreff1_charge = TMath::Sqrt(TMath::Power(errQp1/Qpe1,2) + TMath::Power(Qp1*errQpe1/(Qpe1*Qpe1),2));
erreff2_charge = TMath::Sqrt(TMath::Power(errQp2/Qpe2,2) + TMath::Power(Qp2*errQpe2/(Qpe2*Qpe2),2));
cout<<"eff1_charge(amplitude) = "<<eff1_charge<<" +/- "<<erreff1_charge<<endl;
cout<<"eff2_charge(amplitude) = "<<eff2_charge<<" +/- "<<erreff2_charge<<endl;

//---------------------------- BCTDC -----------------------------------------------------------//

    TChain *fChain = new TChain("tree");
    fChain->Add("2016_10_18_sps_full.root");
    const Int_t nEvents = fChain->GetEntries();
    Float_t bctdc4;
    Int_t time;
    Double_t y[nEvents], x[nEvents];

    Long64_t time1 = (1476807480000000 - 1476741600000000)/1000000;
    Long64_t time2 = (1476810000000000 - 1476741600000000)/1000000;
    Long64_t time1_cut = (1476809260000000 - 1476741600000000)/1000000;
    Long64_t time2_cut = (1476809710000000 - 1476741600000000)/1000000;

    fChain->SetBranchAddress("bctdc4", &bctdc4);
    fChain->SetBranchAddress("t", &time);

    cout<<endl<<endl;
    cout<<"File: '"<<fChain->GetFile()->GetName()<<"' was opened."<<endl;
    cout<<"Number of events is: "<<nEvents<<endl;

    TCanvas* c5 = new TCanvas();
    c5->cd();
    TH2D* bctdc4_vs_t = new TH2D("bctdc4_vs_t","BCTDC4 vs Time",1000,0,170000,1000,0,14e10);

    for(Int_t i = 0; i < nEvents; i++)
    {
        fChain->GetEntry(i);
        bctdc4_vs_t->Fill(time,bctdc4);
        y[i] = bctdc4;
        x[i] = time;
    }

    bctdc4_vs_t->Draw();

    TCanvas* c6 = new TCanvas();
    c6->cd();
    TGraph* gr5 = new TGraph(nEvents,x,y);
    gr5->SetLineColor(kBlue);
    gr5->SetMarkerColor(kRed);
    gr5->SetMarkerSize(3);
    gr5->Draw("APL");

    TLine *line1 = new TLine(time1,0,time1,14e10);
    line1->SetLineWidth(2);
    line1->SetLineStyle(1);
    line1->SetLineColor(kGreen);
    line1->Draw("same");

    TLine *line2 = new TLine(time2,0,time2,14e10);
    line2->SetLineWidth(2);
    line2->SetLineStyle(1);
    line2->SetLineColor(kGreen);
    line2->Draw("same");

    TLine *line3 = new TLine(time1_cut,0,time1_cut,14e10);
    line3->SetLineWidth(2);
    line3->SetLineStyle(2);
    line3->SetLineColor(kYellow);
    line3->Draw("same");

    TLine *line4 = new TLine(time2_cut,0,time2_cut,14e10);
    line4->SetLineWidth(2);
    line4->SetLineStyle(2);
    line4->SetLineColor(kYellow);
    line4->Draw("same");

    Double_t par5[4];
    Double_t err_par5[4];
    TF1* fit_func = new TF1("fit_func","[0]+[1]*x+[2]*x*x+[3]*x*x*x",time1,time2_cut);
    fit_func->SetParameters(1e13,1e8,-1e4,1);
    fit_func->SetParNames("p0","p1","p2","p3");
    gr5->Fit(fit_func,"NR");
    fit_func->GetParameters(&par5[0]);
    err_par5[0] = fit_func->GetParError(0);
    err_par5[1] = fit_func->GetParError(1);
    err_par5[2] = fit_func->GetParError(2);
    err_par5[3] = fit_func->GetParError(3);

    fit_func->SetParameters(par5[0],par5[1],par5[2],par5[3]);
    fit_func->SetLineColor(kMagenta);
    fit_func->Draw("same");

    cout<<endl<<endl;

    Double_t N1 = par5[0]+par5[1]*time1+par5[2]*time1*time1+par5[3]*time1*time1*time1;
    Double_t errN1 = TMath::Sqrt(TMath::Power(err_par5[0],2)+TMath::Power(err_par5[1]*time1,2)+TMath::Power(err_par5[2]*time1*time1,2)+TMath::Power(err_par5[3]*time1*time1*time1,2));
    Double_t N2 = par5[0]+par5[1]*time2_cut+par5[2]*time2_cut*time2_cut+par5[3]*time2_cut*time2_cut*time2_cut;
    Double_t errN2 = TMath::Sqrt(TMath::Power(err_par5[0],2)+TMath::Power(err_par5[1]*time2_cut,2)+TMath::Power(err_par5[2]*time2_cut*time2_cut,2)+TMath::Power(err_par5[3]*time2_cut*time2_cut*time2_cut,2));

    cout<<"N1 = N(t1 = "<<time1<<" sec) = "<<N1<<" +/- "<<errN1<<endl;
    cout<<"N2 = N(t2 = "<<time2_cut<<" sec) = "<<N2<<" +/- "<<errN2<<endl;

    cout<<"|(N2 - N1)/(t2 - t1)| = "<<TMath::Abs((N2 - N1)/(time2_cut - time1))<<" +/- "<<TMath::Sqrt(TMath::Power(errN2,2)+TMath::Power(errN1,2))/(time2_cut - time1)<<endl;

    cout<<endl;
    cout<<"Losses = "<<TMath::Abs((N2 - N1)/(time2_cut - time1))/43000<<" +/- "<<TMath::Sqrt(TMath::Power(errN2,2)+TMath::Power(errN1,2))/((time2_cut - time1)*43000)<<endl;
*/

    TFile* file = new TFile("./root_files/output5.root");

    TH2D* histo1 = (TH2D*)file->Get("nparticles[1]_ampl_cut");
    TH2D* histo2 = (TH2D*)file->Get("nparticles[2]_ampl_cut");
    TH2D* histo3 = (TH2D*)file->Get("nparticles[1]_charge_cut");
    TH2D* histo4 = (TH2D*)file->Get("nparticles[2]_charge_cut");

    histo1->SetLineColor(kBlue);
    histo1->SetLineWidth(2);

    histo3->SetLineColor(kRed);
    histo3->SetLineWidth(2);

    histo2->SetLineColor(kBlue);
    histo2->SetLineWidth(2);

    histo4->SetLineColor(kRed);
    histo4->SetLineWidth(2);

    histo1->Rebin(10);
    histo2->Rebin(10);
    histo3->Rebin(10);
    histo4->Rebin(10);
/*
    TCanvas* c1 = new TCanvas();
    c1->cd();
    histo3->Draw();
    histo1->Draw("same");

    cout<<"histo1 ("<<histo1->GetEntries()<<") = "<<histo1->GetMean()<<" +/- "<<histo1->GetMeanError()<<endl;
    cout<<"histo3 ("<<histo3->GetEntries()<<") = "<<histo3->GetMean()<<" +/- "<<histo3->GetMeanError()<<endl;

    TCanvas* c2 = new TCanvas();
    c2->cd();
    histo4->Draw();
    histo2->Draw("same");

    cout<<"histo2 ("<<histo2->GetEntries()<<") = "<<histo2->GetMean()<<" +/- "<<histo2->GetMeanError()<<endl;
    cout<<"histo4 ("<<histo4->GetEntries()<<") = "<<histo4->GetMean()<<" +/- "<<histo4->GetMeanError()<<endl;


    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);

    TCanvas* c3 = new TCanvas();
    c3->cd();
    histo2->Draw();
    histo1->Draw("same");

    cout<<"histo1="<<histo1->GetMean()<<" +/- "<<histo1->GetMeanError()<<endl;
    cout<<"histo2="<<histo2->GetMean()<<" +/- "<<histo2->GetMeanError()<<endl;
*/

    cout<<endl<<"##############################"<<endl;
    Double_t Histo_Mean_1 = histo1->GetMean();
    Double_t errHisto_Mean_1 = histo1->GetMeanError();
    Double_t Histo_Mean_2 = histo2->GetMean();
    Double_t errHisto_Mean_2 = histo2->GetMeanError();

    cout<<"histo1 = "<<Histo_Mean_1<<" +/- "<<errHisto_Mean_1<<endl;
    cout<<"histo2 = "<<Histo_Mean_2<<" +/- "<<errHisto_Mean_2<<endl;
    cout<<"##############################"<<endl<<endl;

    TCanvas* c4 = new TCanvas();
    c4->cd();
    Double_t norm1 = histo1->GetEntries();
    histo1->Scale(1/norm1);
/*
    // Poisson function
    TF1 *pois1 = new TF1("pois","[0]*TMath::Poisson(x,[1])",0,100);
    pois1->SetLineColor(kRed);
    pois1->SetParameters(histo1->GetMaximum(), histo1->GetMean());
    pois1->SetParNames("Constant","Mean");
    histo1->Fit("pois", "R+");
*/
    // Landau function
    TF1 *land1 = new TF1("land","[0]*TMath::Landau(x,[1],[2])",0,100);
    land1->SetLineColor(kGreen);
    land1->SetParameters(histo1->GetMaximum(), histo1->GetMean(), histo1->GetRMS());
    land1->SetParNames("Constant","MPV","Sigma");
    histo1->Fit("land", "R+");
    gStyle->SetOptFit(1);

    histo1->SetAxisRange(0.0, 100.0, "X");
    histo1->SetAxisRange(0.0, 0.07, "Y");
    histo1->Draw();

    TCanvas* c5 = new TCanvas();
    c5->cd();
    Double_t norm2 = histo2->GetEntries();
    histo2->Scale(1/norm2);
/*
    // Poisson function
    TF1 *pois2 = new TF1("pois","[0]*TMath::Poisson(x,[1])",0,100);
    pois2->SetLineColor(kRed);
    pois2->SetParameters(histo2->GetMaximum(), histo2->GetMean());
    pois2->SetParNames("Constant","Mean");
    histo2->Fit("pois", "R+");
*/
    // Landau function
    TF1 *land2 = new TF1("land","[0]*TMath::Landau(x,[1],[2])",0,100);
    land2->SetLineColor(kGreen);
    land2->SetParameters(histo2->GetMaximum(), histo2->GetMean(), histo2->GetRMS());
    land2->SetParNames("Constant","MPV","Sigma");
    histo2->Fit("land", "R+");
    gStyle->SetOptFit(1);

    histo2->SetAxisRange(0.0, 100.0, "X");
    histo2->SetAxisRange(0.0, 0.07, "Y");
    histo2->Draw();

/*
    TFile* file = new TFile("./root_files/output5_parking.root");
    file->ls();
    TH2D* histo1 = (TH2D*)file->Get("charge[2]");
    TH2D* histo2 = (TH2D*)file->Get("charge[2]_cut");

    histo1->SetLineColor(kBlue);
    histo1->SetLineWidth(2);

    histo2->SetLineColor(kRed);
    histo2->SetLineWidth(2);

    histo1->Rebin(10);
    histo2->Rebin(10);

    TCanvas* c3 = new TCanvas();
    c3->cd();
    histo1->Draw();
    histo2->Draw("same");*/
/*
    TFile* file1 = new TFile("./root_files/output3.root");
    TFile* file2 = new TFile("./root_files/output3_del.root");

    TH1D* histo1 = (TH1D*)file1->Get("charge[1]_cut");
    TH1D* histo2 = (TH1D*)file1->Get("charge[2]_cut");
    TH1D* histo3 = (TH1D*)file2->Get("charge[1]_cut");
    TH1D* histo4 = (TH1D*)file2->Get("charge[2]_cut");

    histo1->SetLineColor(kBlue);
    histo1->SetLineWidth(2);

    histo3->SetLineColor(kRed);
    histo3->SetLineWidth(2);

    histo2->SetLineColor(kBlue);
    histo2->SetLineWidth(2);

    histo4->SetLineColor(kRed);
    histo4->SetLineWidth(2);

    histo1->Rebin(10);
    histo2->Rebin(10);
    histo3->Rebin(10);
    histo4->Rebin(10);

    TCanvas* c1 = new TCanvas();
    c1->cd();
    histo3->Draw();
    histo1->Draw("same");

    cout<<"histo1 ("<<histo1->GetEntries()<<") = "<<histo1->GetMean()<<" +/- "<<histo1->GetMeanError()<<endl;
    cout<<"histo3 ("<<histo3->GetEntries()<<") = "<<histo3->GetMean()<<" +/- "<<histo3->GetMeanError()<<endl;

    TCanvas* c2 = new TCanvas();
    c2->cd();
    histo4->Draw();
    histo2->Draw("same");

    cout<<"histo2 ("<<histo2->GetEntries()<<") = "<<histo2->GetMean()<<" +/- "<<histo2->GetMeanError()<<endl;
    cout<<"histo4 ("<<histo4->GetEntries()<<") = "<<histo4->GetMean()<<" +/- "<<histo4->GetMeanError()<<endl;
*/
}
