#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TRint.h"
#include "TROOT.h"
#include <iostream>
#include <vector>

void test(){
  std::cout<<"#################################################"<<std::endl;
  std::cout<<"             IF SEG VIOLATION OCCURES            "<<std::endl;
  std::cout<<"               ROOT VERSION IS WRONG             "<<std::endl;
  std::cout<<"#################################################"<<std::endl;

  
  gROOT->SetStyle("ATLAS");


  TString match = "900";

    //TFile *f = new TFile(dirc+st+"-00"+en+dirc2);
    TFile *f = new TFile("/hepstore/agroves/testbeam/201910/analysis/analysis_PSI_2019_10_002164-002190_dut-01_searchWindow-0"+match+"_timeCut-0100_HP-REMOVAL-OFF_new.root");

    // TH1F * Chi2 = (TH1F*)f->Get("TrackHistograms/chisquare_ndf");
    // Chi2->GetXaxis()->SetTitle("#chi^{2}/ndf");
    // Chi2->GetYaxis()->SetTitle("Entries");
    // //Chi2->GetYaxis()->SetRangeUser();
    // Chi2->GetYaxis()->SetTitleOffset(1.2);
    // Chi2->GetXaxis()->SetRangeUser(0,50);
    // TCanvas *chiCan = new TCanvas();
    // Chi2->SetMarkerStyle(1);
    // Chi2->SetFillColor(kRed-4);
    // Chi2->DrawCopy("HIST");
    // Chi2->SetFillColor(kBlue);
    // Chi2->SetFillStyle(3345);
    // Chi2->DrawCopy("E2,same");
    // Chi2->SetFillColor(kRed-4);
    // Chi2->SetFillStyle(1001);
    // chiCan->Print("./Plots/TrackHist/Chi2/chi2_"+match+".png");


    // TH2F * TrackMap = (TH2F*)f->Get("MatchingHistograms_DUT_1/matching/absolute_matching_dist");
    // TrackMap->GetXaxis()->SetTitle("absolute distance / #mum");
    // TrackMap->GetYaxis()->SetTitle("Entries");
    // //TrackMap->GetYaxis()->SetRangeUser(0,50);
    // TrackMap->GetYaxis()->SetTitleOffset(1.5);
    // //TrackMap->GetXaxis()->SetRangeUser(0,12100);
    // TCanvas *TrackMapCan = new TCanvas();
    // TrackMap->SetMarkerStyle(1);
    // TrackMap->SetFillColor(kRed-4);
    // TrackMap->DrawCopy("HIST");
    // TrackMap->SetFillColor(kBlue);
    // TrackMap->SetFillStyle(3345);
    // TrackMap->DrawCopy("E2,same");
    // TrackMap->SetFillColor(kRed-4);
    // TrackMap->SetFillStyle(1001);
    // TrackMapCan->Print("./Plots/TrackHist/MatchingDist/AbsoMat_"+match+".png");


    TH2D * effmap = (TH2D*)f->Get("MatchingHistograms_DUT_1/efficiency/efficiency_map");
    //TrackMap->GetXaxis()->SetTitle("absolute distance / #mu mcol");
    //TrackMap->GetYaxis()->SetTitle("Entries");
    //TrackMap->GetYaxis()->SetRangeUser(0,50);
    //TrackMap->GetYaxis()->SetTitleOffset(1.5);
    //TrackMap->GetXaxis()->SetRangeUser(0,12100);
    //TrackMap->GetXaxis()->SetRangeUser(0,12100);    
    gStyle->SetPalette(kViridis);
    gStyle->SetPadRightMargin( 20 );
    TCanvas *effmapCan = new TCanvas();
effmap->SetTitle("My histo;My X axis;My Y axis;My Z axix");
//effmap->GetZaxis()->SetTitle("Efficiency");
effmap->SetStats(0);
    effmap->Draw("COLZ");
    effmapCan->Print("./Plots/TrackHist/MatchingDist/EffMap_"+match+".png");


    // TH1D * eff = (TH1D*)f->Get("MatchingHistograms_DUT_1/efficiency/eff_matching_dist");
    // //TrackMap->GetXaxis()->SetTitle("absolute distance / #mu mcol");
    // //TrackMap->GetYaxis()->SetTitle("Entries");
    // //TrackMap->GetXaxis()->SetRangeUser(0,500);
    // //TrackMap->GetYaxis()->SetTitleOffset(1.5);
    // //TrackMap->GetXaxis()->SetRangeUser(0,12100);
    // //eff->Scale(1/eff->Integral());
    // //TAxis* a=eff->GetYaxis();
    // //a->ChangeLabel(6,-1,-1,-1,-1,-1,"#pi/2");
    // TCanvas *effCan = new TCanvas();
    // eff->Draw();
    // effCan->Print("./Plots/TrackHist/MatchingDist/EffMathc_"+match+".png");

    //}
}
