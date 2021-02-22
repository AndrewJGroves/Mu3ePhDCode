#include "TFile.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void comb2(){
  

  bool ICmic = true;

  double nmuon = 1e15;

  TString outname = "2DplotICmic.png";


  TFile * SigFile = new TFile("./Signal/RootFiles/signal.root","READ");
  TFile * ICFile     = new TFile("./IC/RootFiles/IC.root","READ");
  TFile * ICmicFile     = new TFile("./CombinationBackground/ICmic/RootFiles/ICmic.root","READ");


  double timingeff = 0.9;

  double ic_sel_fraction = 3.094575e-06;
  double ic_BR = 3.4e-5;
  double ICscale = nmuon*1000 * ic_BR * timingeff * ic_sel_fraction * 0.011396 ;
    
  double ICmicEff = 3.660731949e-9;
  double ICmicScale = nmuon * ic_BR * ICmicEff  * 0.01 * 0.62577  *  0.461745;


  TH2F * hsig = (TH2F*)SigFile->Get("h_PmMass");
  TH2F * hic  = (TH2F*)ICFile->Get("h_PmMass");
  TH2F * hb  = (TH2F*)ICmicFile->Get("h_PmMass");

  
  hic->Scale(1./hic->Integral());
  hic->Scale(ICscale);
  std::cout<<"IC "<<ICscale<<std::endl;
  hb->Scale(1./hb->Integral());
  hb->Scale(ICmicScale);
  std::cout<<"ICmic "<<ICmicScale<<std::endl;
  hsig->Scale(1./hsig->Integral());

  std::vector<double> bc;
  for(int i=1; i <= hsig->GetNbinsX(); i++){
    for(int j=1; j <= hsig->GetNbinsY(); j++){
      bc.push_back(hsig->GetBinContent(i,j));
    }
  }

  double levels[4] = {0,0,0,0};

  
  std::sort(bc.begin(), bc.end());
  double sum =0;
  for(int i=bc.size()-1; i >= 0; i --){
    sum += bc[i];
    if(sum > 0.50 && levels[3]==0){
      levels[3] = bc[i];
    }
    if(sum > 0.80 && levels[2]==0){
      levels[2] = bc[i];
    }
    if(sum > 0.9 && levels[1]==0){
      levels[1] = bc[i];
    }
    if(sum > 0.95 && levels[0]==0){
      levels[0] = bc[i];
    }
  }
  cout << sum << endl;
  

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TCanvas * c = new TCanvas("Mu3e","Mu3e",800,600);
  c->SetFrameLineColor(0);
 
  c->SetBottomMargin(0.15);
  c->SetLeftMargin(0.15);

  //cout << hic->GetMaximum() << endl;
  
  hic->GetXaxis()->SetRangeUser(95.5,110);
  hic->GetYaxis()->SetRangeUser(0,12);
  cout << hic->GetMaximum() << endl;
  hic->SetMarkerColor(2);
  hic->SetMarkerStyle(1);
  hic->SetMarkerSize(0.01);
  //hic->Draw("scat=1");

  if(ICmic){
  hb->SetMarkerColor(4);
  hb->SetMarkerStyle(20);
  hb->SetMarkerSize(0.4);
  hb->Draw("scat=1");
  }
  hsig->SetContour(4,levels);
  hsig->Draw("CONT3SAME");

  TLatex * t50 = new TLatex(105,1,"50%");
  t50->SetTextFont(42);
  t50->SetTextSize(0.03);
  t50->Draw();

  TLatex * t80 = new TLatex(105,2.3,"80%");
  t80->SetTextFont(42);
  t80->SetTextSize(0.03);
  t80->Draw();

  TLatex * t90 = new TLatex(104.7,3.1,"90%");
  t90->SetTextFont(42);
  t90->SetTextSize(0.03);
  t90->Draw();

  TLatex * t95 = new TLatex(104.5,3.8,"95%");
  t95->SetTextFont(42);
  t95->SetTextSize(0.03);
  t95->Draw();

  TLatex * tic = new TLatex(105,11,"#it{#mu} #rightarrow #it{eee#nu#bar{#nu}}");
  tic->SetTextFont(42);
  tic->SetTextColor(2);
  tic->Draw();

  TLatex * tic2 = new TLatex(105,10.3,"1 dot: 1 event per 10^{18} #it{#mu} stops");
  tic2->SetTextFont(42);
  tic2->SetTextColor(2);
  tic2->SetTextSize(0.04);
  tic2->Draw();
  if(ICmic){
  TLatex * tb = new TLatex(105,9,"Michel + #it{#mu} #rightarrow #it{eee#nu#bar{#nu}}");
  tb->SetTextFont(42);
  tb->SetTextColor(4);
  tb->Draw();

  TLatex * tb2 = new TLatex(105,8.3,"1 dot: 1 event per 10^{15} #it{#mu} stops");
  tb2->SetTextFont(42);
  tb2->SetTextColor(4);
  tb2->SetTextSize(0.04);
  tb2->Draw();
  }
  TLatex * ts = new TLatex(106.5,4,"#it{#mu} #rightarrow #it{eee}");
  ts->SetTextFont(42);
  ts->Draw();

  TLatex * ptitle = new TLatex();
  ptitle->SetTextFont(42);
  ptitle->DrawLatexNDC(0.3,0.95,"Mu3e Phase I Simulation");
  
  c->Print(outname);
}
