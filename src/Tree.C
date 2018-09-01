#define Tree_cxx
#include "Tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLine.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
void Tree::Loop()
{
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
    }
}

void Tree::VisualisationAllChannels(Int_t nEv)
{

    if (fChain == 0) return;

    TCanvas *vis = new TCanvas("vis","CpFM",5,5,600,600);

    vis->Divide(2,(Constants::nCh+1)/2);
    fChain->GetEntry(nEv);
    Double_t t[Constants::nPnt], amp[Constants::nPnt];
    for(Int_t j = 0; j < Constants::nCh; j++)
    {
        vis->cd(j+1);
        for (Int_t i = 0; i < Constants::nPnt; i++)
        {
            t[i] = Constants::dTime*i;
            amp[i] = Amplitude[j][i];
        }

        TGraph *gr = new TGraph(Constants::nPnt,t,amp);

        TString title = "WaveForm CH"; title += j;
        gr->SetTitle(title.Data());
        gr->GetXaxis()->SetTitle("Time / ns");
        gr->GetYaxis()->SetTitle("Amplitude / V");
        gr->Draw("APL");
    }
    vis->SaveAs("VisualAllCh.root");
}

void Tree::VisualisationOnlyOneChannel(Int_t nEv,Int_t nChannel)
{
    if (fChain == 0) return;

    fChain->GetEntry(nEv);

    TCanvas *viss = new TCanvas("viss","CpFM",1000,0,600,600);

    Double_t t[Constants::nPnt], amp[Constants::nPnt];
    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        t[i] = Constants::dTime*i;
        amp[i] = (-1)*Amplitude[nChannel][i];
    }
    Double_t max_ampl;
    Double_t min_ampl;
    Double_t mean_value_20p;
    Double_t time_max_ampl;
    Double_t time_min_ampl;
    Double_t time_level;
    Double_t time_cf;
    Double_t width_at_level;
    Double_t rise_time;
    Double_t fall_time;
    Int_t num_peaks = 0;
    Double_t max_ampl_per_peak[Constants::nPeakMax];
    Double_t time_max_ampl_per_peak[Constants::nPeakMax];

    GetMean(nChannel, mean_value_20p);
    GetMaxAmpl(amp, max_ampl, time_max_ampl);
    GetMinAmpl(amp, min_ampl, time_min_ampl);
    GetTimeAtLevel(amp, Constants::Level[nChannel], time_max_ampl, time_level);
    GetWidth(amp, Constants::Level[nChannel],time_max_ampl,width_at_level);
    GetTimeCF(amp, Constants::CF[nChannel],max_ampl,time_max_ampl,time_cf);
    GetRiseTime(amp, max_ampl,time_max_ampl,rise_time);
    GetFallTime(amp, max_ampl,time_max_ampl,fall_time);
    GetTrueNumPeaks(amp, Constants::Level[nChannel], num_peaks);

    if(num_peaks > 0)
    {
        GetMaxAmplPerPeak(amp, Constants::Level[nChannel], max_ampl_per_peak, time_max_ampl_per_peak);
    }

    TGraph *gr = new TGraph(Constants::nPnt,t,amp);
    gr->SetMarkerStyle(21);
    gr->SetLineWidth(2);
    gr->GetXaxis()->SetTitle("time / ns");
    gr->GetYaxis()->SetTitle("Amplitude / V");
    gr->Draw("APL");

    TLine *line1 = new TLine(t[0],mean_value_20p,t[Constants::nPnt-1],mean_value_20p);
    line1->SetLineWidth(2);
    line1->SetLineStyle(1);
    line1->SetLineColor(kBlue);
    line1->Draw("same");

    TLine *line2 = new TLine(t[0],max_ampl,t[Constants::nPnt-1],max_ampl);
    line2->SetLineWidth(2);
    line2->SetLineStyle(2);
    line2->SetLineColor(kRed);
    line2->Draw("same");

    TLine *line3 = new TLine(t[0],min_ampl,t[Constants::nPnt-1],min_ampl);
    line3->SetLineWidth(2);
    line3->SetLineStyle(2);
    line3->SetLineColor(kMagenta);
    line3->Draw("same");

    TLine *line4 = new TLine(time_level,min_ampl,time_level,max_ampl);
    line4->SetLineWidth(2);
    line4->SetLineStyle(2);
    line4->SetLineColor(kCyan);
    line4->Draw("same");

    TLine *line5 = new TLine(t[0],Constants::Level[nChannel],t[Constants::nPnt-1],Constants::Level[nChannel]);
    line5->SetLineWidth(2);
    line5->SetLineStyle(2);
    line5->SetLineColor(kYellow);
    line5->Draw("same");

    TLine *line6 = new TLine(time_level,Constants::Level[nChannel],time_level+width_at_level,Constants::Level[nChannel]);
    line6->SetLineWidth(2);
    line6->SetLineStyle(1);
    line6->SetLineColor(kRed);
    line6->Draw("same");

    TLine *line7 = new TLine(time_cf,min_ampl,time_cf,max_ampl);
    line7->SetLineWidth(2);
    line7->SetLineStyle(2);
    line7->SetLineColor(kOrange);
    line7->Draw("same");

    TLine *line8 = new TLine(time_max_ampl-Constants::charge_wind_left,min_ampl,time_max_ampl-Constants::charge_wind_left,max_ampl);
    line8->SetLineWidth(2);
    line8->SetLineStyle(2);
    line8->SetLineColor(kViolet);
    line8->Draw("same");

    TLine *line9 = new TLine(time_max_ampl+Constants::charge_wind_right,min_ampl,time_max_ampl+Constants::charge_wind_right,max_ampl);
    line9->SetLineWidth(2);
    line9->SetLineStyle(2);
    line9->SetLineColor(kViolet);
    line9->Draw("same");

    TLine *line10 = new TLine(t[0],max_ampl*0.1,t[Constants::nPnt-1],max_ampl*0.1);
    line10->SetLineWidth(2);
    line10->SetLineStyle(2);
    line10->SetLineColor(kGreen);
    line10->Draw("same");

    TLine *line11 = new TLine(t[0],max_ampl*0.9,t[Constants::nPnt-1],max_ampl*0.9);
    line11->SetLineWidth(2);
    line11->SetLineStyle(2);
    line11->SetLineColor(kGreen);
    line11->Draw("same");

    Double_t qw1 = 0, x1, x2, y1, y2, k, b, y3;
    Double_t i = time_max_ampl/Constants::dTime;

    for (Int_t t = i; t > 0; t--)
    {
        if (amp[t] < 0.9*max_ampl)
        {
            x1 = t*Constants::dTime + Constants::dTime;
            x2 = t*Constants::dTime;
            y1 = amp[t+1];
            y2 = amp[t];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = 0.9*max_ampl;
            qw1 = (y3-b)/k;
            break;
        }
    }

    TLine *line12 = new TLine(qw1,max_ampl*0.9,qw1-rise_time,max_ampl*0.1);
    line12->SetLineWidth(2);
    line12->SetLineStyle(1);
    line12->SetLineColor(kGreen);
    line12->Draw("same");

    for (Int_t t = i; t < Constants::nPnt; t++)
    {
        if (amp[t] < 0.9*max_ampl)
        {
            x1 = t*Constants::dTime - Constants::dTime;
            x2 = t*Constants::dTime;
            y1 = amp[t-1];
            y2 = amp[t];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = 0.9*max_ampl;
            qw1 = (y3-b)/k;
            break;
        }
    }

    TLine *line13 = new TLine(qw1,max_ampl*0.9,qw1+fall_time,max_ampl*0.1);
    line13->SetLineWidth(2);
    line13->SetLineStyle(1);
    line13->SetLineColor(kTeal);
    line13->Draw("same");

    if(num_peaks > 0)
    {
        TLine *line14[num_peaks];
        for(Int_t k = 0; k < num_peaks; k++)
        {
            line14[k] = new TLine(time_max_ampl_per_peak[k],min_ampl,time_max_ampl_per_peak[k],max_ampl);
            line14[k]->SetLineWidth(2);
            line14[k]->SetLineStyle(2);
            line14[k]->SetLineColor(kRed);
            line14[k]->Draw("same");
        }
    }

    viss->SaveAs("VisualOneCh.root");
}

void Tree::GetNumEntries(Long64_t &nEntires)
{
    if (fChain == 0) return;

    nEntires = fChain->GetEntries();
}


void Tree::GetMean(Int_t nCh, Double_t &OutMean)
{
    Double_t sum = 0;
    Double_t n = 0;

    for (Int_t i = 0; i < 20; i++)
    {
        sum = sum + Amplitude[nCh][i];
        n++;
    }
    OutMean = sum/n;
}

void Tree::TransformAmplitude(Int_t nCh, Double_t *OutAmpl)
{
    for(Int_t i = 0; i < Constants::nPnt; i++)
    {
        OutAmpl[i] = (-1)*Amplitude[nCh][i];
    }
}

void Tree::GetMaxAmpl(Double_t *InAmpl, Double_t &OutAmpl, Double_t &OutTime)
{
    Double_t max = 0.0;
    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if (InAmpl[i] > max)
        {
            max = InAmpl[i];
            OutAmpl = max;
            OutTime = i*Constants::dTime;
        }
    }
}

void Tree::GetMinAmpl(Double_t *InAmpl, Double_t &OutAmpl, Double_t &OutTime)
{
    Double_t min = 999.0;
    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if (InAmpl[i] < min)
        {
            min = InAmpl[i];
            OutAmpl = min;
            OutTime = i*Constants::dTime;
        }
    }
}

void Tree::GetTimeAtLevel(Double_t *InAmpl, Double_t level, Double_t InTime, Double_t &OutTime)
{
    Double_t t = InTime/Constants::dTime;
    for (Int_t i = t; i > 0; i--)
    {
        if(InAmpl[i] < level)
        {
            Double_t x1 = i*Constants::dTime + Constants::dTime;
            Double_t x2 = i*Constants::dTime;
            Double_t y1 = InAmpl[i+1];
            Double_t y2 = InAmpl[i];
            Double_t k = (y1-y2)/(x1-x2);
            Double_t b = (y2*x1-y1*x2)/(x1-x2);
            Double_t y3 = level;
            OutTime = (y3-b)/k;
            break;
        }
    }
}

void Tree::GetWidth(Double_t *InAmpl, Double_t level, Double_t InTime, Double_t &OutWidth)
{
    Double_t w1 = 0, w2 = 0, x1, x2, y1, y2, k, b, y3;
    Double_t t = InTime/Constants::dTime;

    for (Int_t i = t; i > 0; i--)
    {
        if(InAmpl[i] < level)
        {
            x1 = i*Constants::dTime + Constants::dTime;
            x2 = i*Constants::dTime;
            y1 = InAmpl[i+1];
            y2 = InAmpl[i];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = level;
            w1 = (y3-b)/k;
            break;
        }
    }

    for (Int_t i = t; i < Constants::nPnt; i++)
    {
        if(InAmpl[i] < level)
        {
            x1 = i*Constants::dTime - Constants::dTime;
            x2 = i*Constants::dTime;
            y1 = InAmpl[i-1];
            y2 = InAmpl[i];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = level;
            w2 = (y3-b)/k;
            OutWidth = TMath::Abs(w2-w1);
            break;
        }
    }
}

void Tree::GetTimeCF(Double_t *InAmpl, Double_t cf, Double_t MaxAmpl, Double_t TimeMax, Double_t &OutTime)
{
    Double_t i = TimeMax/Constants::dTime;
    for (Int_t t = i; t > 0; t--)
    {
        if(InAmpl[t] < cf*MaxAmpl)
        {
            Double_t x1 = t*Constants::dTime + Constants::dTime;
            Double_t x2 = t*Constants::dTime;
            Double_t y1 = InAmpl[t+1];
            Double_t y2 = InAmpl[t];
            Double_t k = (y1-y2)/(x1-x2);
            Double_t b = (y2*x1-y1*x2)/(x1-x2);
            Double_t y3 = cf*MaxAmpl;
            OutTime = (y3-b)/k;
            break;
        }
    }
}

void Tree::GetRiseTime(Double_t *InAmpl, Double_t MaxAmpl, Double_t InTime, Double_t &OutTime)
{
    Double_t qw1 = 0, qw2 = 0, x1, x2, y1, y2, k, b, y3;
    Double_t i = InTime/Constants::dTime;

    for (Int_t t = i; t > 0; t--)
    {
        if (InAmpl[t] < 0.9*MaxAmpl)
        {
            x1 = t*Constants::dTime + Constants::dTime;
            x2 = t*Constants::dTime;
            y1 = InAmpl[t+1];
            y2 = InAmpl[t];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = 0.9*MaxAmpl;
            qw1 = (y3-b)/k;

            while(InAmpl[t] > 0.1*MaxAmpl)
            {
                t--;
            }

            x1 = t*Constants::dTime + Constants::dTime;
            x2 = t*Constants::dTime;
            y1 = InAmpl[t+1];
            y2 = InAmpl[t];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = 0.1*MaxAmpl;
            qw2 = (y3-b)/k;
            OutTime = TMath::Abs(qw1-qw2);
            break;
        }
    }
}

void Tree::GetFallTime(Double_t *InAmpl, Double_t MaxAmpl, Double_t InTime, Double_t &OutTime)
{
    Double_t qw1 = 0, qw2 = 0, x1, x2, y1, y2, k, b, y3;
    Double_t i = InTime/Constants::dTime;

    for (Int_t t = i; t < Constants::nPnt; t++)
    {
        if (InAmpl[t] < 0.9*MaxAmpl)
        {
            x1 = t*Constants::dTime - Constants::dTime;
            x2 = t*Constants::dTime;
            y1 = InAmpl[t-1];
            y2 = InAmpl[t];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = 0.9*MaxAmpl;
            qw1 = (y3-b)/k;

            while(InAmpl[t] > 0.1*MaxAmpl)
            {
                t++;
            }

            x1 = t*Constants::dTime - Constants::dTime;
            x2 = t*Constants::dTime;
            y1 = InAmpl[t-1];
            y2 = InAmpl[t];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = 0.1*MaxAmpl;
            qw2 = (y3-b)/k;
            OutTime = TMath::Abs(qw1-qw2);
            break;
        }
    }
}

void Tree::GetCharge(Double_t *InAmpl, Double_t InTime, Double_t &Charge)
{
    Charge = 0;
    for(Int_t i = 0; i < Constants::nPnt; i++)
    {
        if(i*Constants::dTime > (InTime - Constants::charge_wind_left) && i*Constants::dTime < (InTime + Constants::charge_wind_right))
        {
            Charge += (InAmpl[i]*Constants::dTime)*Constants::nVsTopC;
        }
    }
}

void Tree::GetNumPeaks(Double_t *InAmpl, Double_t level, Int_t &num_peaks)
{
    num_peaks = 0;

    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if(InAmpl[i] > level)
        {
            num_peaks++;
            while(InAmpl[i] > level)
            {
                i++;
            }
            i--;
        }
    }
}

void Tree::GetTrueNumPeaks(Double_t *InAmpl, Double_t level, Int_t &num_peaks)
{
    num_peaks = 0;
    Double_t time = 0;

    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if(InAmpl[i] > level && num_peaks == 0)
        {
            time = i*Constants::dTime;
            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                i++;
            }
            i--;
            num_peaks++;
        }
        if(InAmpl[i] > level && num_peaks > 0 && i*Constants::dTime > time + Constants::separTime)
        {
            time = i*Constants::dTime;
            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                i++;
            }
            i--;
            num_peaks++;
        }
    }
}

void Tree::GetMaxAmplPerPeak(Double_t *InAmpl, Double_t level, Double_t *OutAmpl, Double_t *OutTime)
{
    Double_t max = 0.0;
    Int_t peakID = 0;
    Double_t t = 0;
    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if (InAmpl[i] > level && peakID == 0)
        {
            while(InAmpl[i] > level && i < Constants::nPnt)
            {                
                if (InAmpl[i] > max)
                {
                    max = InAmpl[i];
                    t = i*Constants::dTime;
                }
                i++;
            }
            i--;
            OutAmpl[peakID] = max;
            OutTime[peakID] = t;
            max = 0.0;
            peakID++;
        }
        if (InAmpl[i] > level && peakID > 0 && i*Constants::dTime > OutTime[peakID-1] + Constants::separTime)
        {
            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                if (InAmpl[i] > max)
                {
                    max = InAmpl[i];
                    t = i*Constants::dTime;
                }
                i++;
            }
            i--;
            OutAmpl[peakID] = max;
            OutTime[peakID] = t;
            max = 0.0;
            peakID++;
        }
    }
}

void Tree::GetTimeAtLevelPerPeak(Double_t *InAmpl, Double_t level, Double_t *OutTime)
{
    Int_t peakID = 0;
    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if(InAmpl[i] > level && peakID == 0)
        {
            Double_t x1 = i*Constants::dTime - Constants::dTime;
            Double_t x2 = i*Constants::dTime;
            Double_t y1 = InAmpl[i-1];
            Double_t y2 = InAmpl[i];
            Double_t k = (y1-y2)/(x1-x2);
            Double_t b = (y2*x1-y1*x2)/(x1-x2);
            Double_t y3 = level;
            OutTime[peakID] = (y3-b)/k;
            peakID++;

            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                i++;
            }
            i--;
        }
        if(InAmpl[i] > level && peakID > 0 && i*Constants::dTime > OutTime[peakID-1] + Constants::separTime)
        {
            Double_t x1 = i*Constants::dTime - Constants::dTime;
            Double_t x2 = i*Constants::dTime;
            Double_t y1 = InAmpl[i-1];
            Double_t y2 = InAmpl[i];
            Double_t k = (y1-y2)/(x1-x2);
            Double_t b = (y2*x1-y1*x2)/(x1-x2);
            Double_t y3 = level;
            OutTime[peakID] = (y3-b)/k;
            peakID++;

            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                i++;
            }
            i--;
        }
    }
}

void Tree::GetWidthPerPeak(Double_t *InAmpl, Double_t level, Double_t *OutWidth)
{
    Double_t w1 = 0, w2 = 0, x1, x2, y1, y2, k, b, y3;
    Int_t peakID = 0;
    Double_t time = 0;
    for (Int_t i = 0; i < Constants::nPnt; i++)
    {
        if(InAmpl[i] > level && peakID == 0)
        {
            time = i*Constants::dTime;
            x1 = i*Constants::dTime - Constants::dTime;
            x2 = i*Constants::dTime;
            y1 = InAmpl[i-1];
            y2 = InAmpl[i];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = level;
            w1 = (y3-b)/k;

            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                i++;
            }

            x1 = i*Constants::dTime - Constants::dTime;
            x2 = i*Constants::dTime;
            y1 = InAmpl[i-1];
            y2 = InAmpl[i];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = level;
            w2 = (y3-b)/k;
            OutWidth[peakID] = w2-w1;
            peakID++;
        }
        if(InAmpl[i] > level && peakID > 0 && i*Constants::dTime > time + Constants::separTime)
        {
            time = i*Constants::dTime;
            x1 = i*Constants::dTime - Constants::dTime;
            x2 = i*Constants::dTime;
            y1 = InAmpl[i-1];
            y2 = InAmpl[i];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = level;
            w1 = (y3-b)/k;

            while(InAmpl[i] > level && i < Constants::nPnt)
            {
                i++;
            }

            x1 = i*Constants::dTime - Constants::dTime;
            x2 = i*Constants::dTime;
            y1 = InAmpl[i-1];
            y2 = InAmpl[i];
            k = (y1-y2)/(x1-x2);
            b = (y2*x1-y1*x2)/(x1-x2);
            y3 = level;
            w2 = (y3-b)/k;
            OutWidth[peakID] = w2-w1;
            peakID++;
        }
    }
}
