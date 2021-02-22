#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include "TMath.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include <algorithm>
#include "TF1.h"
#include <set> 
#include <random>
#include <algorithm>
#include "TCanvas.h"
#include "TPaveText.h"
#include "TH1.h"
#include "TF1.h"
#include "Math/GoFTest.h"
#include "Math/Functor.h"
#include "TRandom3.h"
#include "Math/DistFunc.h"
Double_t lognormal(double* x, double_t* par){
  double x0 = par[0];
  double s = par[1];
  double m = par[2];
  if ((x[0]-x0) <= 0) {
    return 0.0;
  } else {
    double tmp = (std::log((x[0]-x0)) - m)/s;
    return 1.0 / ((x[0]-x0) * std::fabs(s) * std::sqrt(2 * M_PI)) * std::exp(-(tmp * tmp) /2);
  }
}

void Momentum(){
  //gROOT->SetStyle("ATLAS");
  //gStyle->SetOptStat(0);
  TFile *f = new TFile("/hepstore/agroves/backup/SoftwareStudies/TDRSensitity/CombinationBackground/PhoCon/RootFiles/PhoCon.root","READ");
  // TTree *t1 = (TTree*)f->Get("t1");
  // vector<double> *px1=0,*py1=0,*pz1=0;
  // vector<double> *px2=0,*py2=0,*pz2=0;
  // vector<double> *px3=0,*py3=0,*pz3=0;
  // vector<double> *chi2=0,*targetdist=0;
  // t1->SetBranchAddress("chi2",&chi2);
  // t1->SetBranchAddress("targetdist",&targetdist);
  // t1->SetBranchAddress("px1",&px1);
  // t1->SetBranchAddress("py1",&py1);
  // t1->SetBranchAddress("pz1",&pz1);
  // t1->SetBranchAddress("px2",&px2);
  // t1->SetBranchAddress("py2",&py2);
  // t1->SetBranchAddress("pz2",&pz2);
  // t1->SetBranchAddress("px3",&px3);
  // t1->SetBranchAddress("py3",&py3);
  // t1->SetBranchAddress("pz3",&pz3);

  //TH1F *tmom = new TH1F("h_tmom", "Absolute momentum", 1000,0,100);


  // Long64_T n = t1->GetEntries();
  // std::cout<<"Number of entries "<< n << std::endl;
  // for( Long64_t i=0 ; i<n ; i++){
  //   t1->GetEntry(i);
  //   for(int nv =0; nv<(int)px1->size() ; nv++){
  //     if(chi2->at(nv) > 15) continue;
  //     if (abs(targetdist->at(nv)) > 1){ continue; }
  //     TLorentzVector el1;
  //     TLorentzVector el2;
  //     TLorentzVector el3;
  //     TLorentzVector mu;
  //     el1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))+0.511*0.511);
  //     el2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))+0.511*0.511);
  //     el3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))+0.511*0.511);
  //     mu=el1+el2+el3;
  //     //tmom->Fill(mu.P());
  //   }
  // }





  TH1F* tmom=(TH1F*)f->Get("h_tmomLong");
  tmom->SetFillColor(kYellow);
  tmom->GetXaxis()->SetTitle("Momentum [MeV/c]");
  tmom->GetYaxis()->SetTitle("Number of Vertices");
  //tmom->Rebin(20);
  tmom->SetMarkerStyle(1);
  tmom->SetFillColor(kYellow);
  //tmom->DrawCopy("HIST");
  tmom->SetFillColor(kBlue);
  tmom->SetFillStyle(3345);
  //tmom->DrawCopy("E2,same");
  tmom->SetFillColor(kYellow);
  tmom->SetFillStyle(1001);



  double under8=tmom->Integral(0,tmom->GetXaxis()->FindBin(4));
  double all=tmom->Integral(0,99999);
  Double_t errunder8;
  Double_t errall;
  tmom->IntegralAndError(0,tmom->GetXaxis()->FindBin(4),errunder8);
  tmom->IntegralAndError(0,99999,errall);
  double err1=under8/all*TMath::Sqrt((errunder8/under8)*(errunder8/under8)+(errall/all)*(errall/all));
  std::cout<<"Usins graph "<<under8/all<<" pm "<<err1<<std::endl;
  std::cout<<" "<<std::endl;


  int num = 15;
  vector<int> bin;
  Double_t binUp[num];
  Double_t binUperr[num];

  //std::cout<<binUperr<<std::endl;
  Double_t Int[num];
  Double_t IntErr[num];
  Double_t err;
  binUp[num-15]=0;
  binUp[num-14]=0;
  binUp[num-13]=0;
  binUp[num-12]=0;
  binUp[num-11]=0;
  binUp[num-10]=0;
  binUp[num-9]=0;
  binUp[num-8]=0;
  binUp[num-7]=0;
  binUp[num-6]=0;
  binUp[num-5]=0;
  binUp[num-4]=0;
  binUp[num-3]=0;
  binUp[num-2]=0;
  binUp[num-1]=0;


  Int[num-15]=(double)(tmom->Integral(0,100))/(double)(tmom->Integral());
  binUp[num-15]=(tmom->GetBinLowEdge(101));
  tmom->IntegralAndError(0,100,err);
  IntErr[num-15]=(double)(tmom->Integral(0,100))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,100)))*(err/(double)(tmom->Integral(0,100)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;


  Int[num-14]=(double)(tmom->Integral(0,125))/(double)(tmom->Integral());
  binUp[num-14]=(tmom->GetBinLowEdge(126));
  tmom->IntegralAndError(0,125,err);
  IntErr[num-14]=(double)(tmom->Integral(0,125))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,125)))*(err/(double)(tmom->Integral(0,125)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-13]=(double)(tmom->Integral(0,150))/(double)(tmom->Integral());
  binUp[num-13]=(tmom->GetBinLowEdge(151));
  tmom->IntegralAndError(0,150,err);
  IntErr[num-13]=(double)(tmom->Integral(0,150))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,150)))*(err/(double)(tmom->Integral(0,150)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-12]=(double)(tmom->Integral(0,175))/(double)(tmom->Integral());
  binUp[num-12]=(tmom->GetBinLowEdge(176));
  tmom->IntegralAndError(0,150,err);
  IntErr[num-12]=(double)(tmom->Integral(0,150))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,150)))*(err/(double)(tmom->Integral(0,150)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-11]=(double)(tmom->Integral(0,200))/(double)(tmom->Integral());
  binUp[num-11]=(tmom->GetBinLowEdge(201));
  tmom->IntegralAndError(0,200,err);
  IntErr[num-11]=(double)(tmom->Integral(0,200))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,200)))*(err/(double)(tmom->Integral(0,200)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-10]=(double)(tmom->Integral(0,225))/(double)(tmom->Integral());
  binUp[num-10]=(tmom->GetBinLowEdge(226));
  tmom->IntegralAndError(0,225,err);
  IntErr[num-10]=(double)(tmom->Integral(0,225))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,225)))*(err/(double)(tmom->Integral(0,225)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-9]=(double)(tmom->Integral(0,250))/(double)(tmom->Integral());
  binUp[num-9]=(tmom->GetBinLowEdge(251));
  tmom->IntegralAndError(0,250,err);
  IntErr[num-9]=(double)(tmom->Integral(0,250))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,250)))*(err/(double)(tmom->Integral(0,250)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-8]=(double)(tmom->Integral(0,275))/(double)(tmom->Integral());
  binUp[num-8]=(tmom->GetBinLowEdge(276));
  tmom->IntegralAndError(0,275,err);
  IntErr[num-8]=(double)(tmom->Integral(0,275))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,275)))*(err/(double)(tmom->Integral(0,275)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-7]=(double)(tmom->Integral(0,300))/(double)(tmom->Integral());
  binUp[num-7]=(tmom->GetBinLowEdge(301));
  tmom->IntegralAndError(0,300,err);
  IntErr[num-7]=(double)(tmom->Integral(0,300))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,300)))*(err/(double)(tmom->Integral(0,300)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-6]=(double)(tmom->Integral(0,325))/(double)(tmom->Integral());
  binUp[num-6]=(tmom->GetBinLowEdge(326));
  tmom->IntegralAndError(0,325,err);
  IntErr[num-6]=(double)(tmom->Integral(0,325))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,325)))*(err/(double)(tmom->Integral(0,325)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-5]=(double)(tmom->Integral(0,350))/(double)(tmom->Integral());
  binUp[num-5]=tmom->GetBinLowEdge(351);
  tmom->IntegralAndError(0,350,err);
  IntErr[num-5]=(double)(tmom->Integral(0,350))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,350)))*(err/(double)(tmom->Integral(0,350)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  ///std::cout<<err<<std::endl;

  Int[num-4]=(tmom->Integral(0,400)/tmom->Integral());
  binUp[num-4]=(tmom->GetBinLowEdge(401));
  tmom->IntegralAndError(0,400,err);
  IntErr[num-4]=(double)(tmom->Integral(0,400))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,400)))*(err/(double)(tmom->Integral(0,400)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-3]=(tmom->Integral(0,450)/tmom->Integral());
  binUp[num-3]=(tmom->GetBinLowEdge(451));
  tmom->IntegralAndError(0,450,err);
  IntErr[num-3]=(double)(tmom->Integral(0,450))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,450)))*(err/(double)(tmom->Integral(0,450)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-2]=(tmom->Integral(0,500)/tmom->Integral());
  binUp[num-2]=(tmom->GetBinLowEdge(501));
  tmom->IntegralAndError(0,500,err);
  IntErr[num-2]=(double)(tmom->Integral(0,500))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,500))*(err/(double)(tmom->Integral(0,500)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral()))));
  err=0;
  //std::cout<<err<<std::endl;

  Int[num-1]=(tmom->Integral(0,550)/tmom->Integral());
  binUp[num-1]=(tmom->GetBinLowEdge(551));
  tmom->IntegralAndError(0,550,err);
  IntErr[num-1]=(double)(tmom->Integral(0,550))/(double)(tmom->Integral())*TMath::Sqrt((err/(double)(tmom->Integral(0,550)))*(err/(double)(tmom->Integral(0,550)))+(errall/(double)(tmom->Integral()))*(errall/(double)(tmom->Integral())));
  err=0;
  //std::cout<<err<<std::endl;

  // for(int i =0; i<num;i++){
  //   std::cout<<Int[i]<<" "<<binUp[i]<<std::endl;
  // }
  TCanvas *c1 = new TCanvas();
  TGraphErrors* gr = new TGraphErrors(num,binUp,Int,binUperr,IntErr);

  TEfficiency* pEff = new TEfficiency("eff","my efficiency;x;#epsilon",1,0,100);
  //pEff->SetStatisticOption(TEfficiency::kFWilson);
  pEff->Draw("AP");
  // bool pass;
  // std::cout<<"Number of entries "<< n << std::endl;
  // for( Long64_t i=0 ; i<n ; i++){
  //   t1->GetEntry(i);
  //   for(int nv =0; nv<(int)px1->size() ; nv++){
  //     if(chi2->at(nv) > 30) continue;
  //     if (abs(targetdist->at(nv)) > 3){ continue; }

  //     TLorentzVector el1;
  //     TLorentzVector el2;
  //     TLorentzVector el3;
  //     TLorentzVector mu;
  //     el1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))+0.511*0.511);
  //     el2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))+0.511*0.511);
  //     el3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))+0.511*0.511);
  //     mu=el1+el2+el3;
  //     //std::cout<<mu.M()<<std::endl;
  //     pass =  true;
  //     pEff->Fill(pass,mu.P());
  //   }
  // }


  // pEff->SetStatisticOption(TEfficiency::kFCP);
  // std::cout<<"ClopperPearson "<<pEff->GetEfficiency(1)<<" "<<pEff->GetEfficiencyErrorLow(1)<<" "<<pEff->GetEfficiencyErrorUp(1)<<std::endl;
  // pEff->SetStatisticOption(TEfficiency::kFNormal);
  // std::cout<<"Normal "<<pEff->GetEfficiency(1)<<" "<<pEff->GetEfficiencyErrorLow(1)<<" "<<pEff->GetEfficiencyErrorUp(1)<<std::endl;
  // pEff->SetStatisticOption(TEfficiency::kFWilson);
  // std::cout<<"Wilson "<<pEff->GetEfficiency(1)<<" "<<pEff->GetEfficiencyErrorLow(1)<<" "<<pEff->GetEfficiencyErrorUp(1)<<std::endl;
  // pEff->SetStatisticOption(TEfficiency::kFAC);
  // std::cout<<"AgrestiCoull "<<pEff->GetEfficiency(1)<<" "<<pEff->GetEfficiencyErrorLow(1)<<" "<<pEff->GetEfficiencyErrorUp(1)<<std::endl;
  // pEff->SetStatisticOption(TEfficiency::kFFC);
  // std::cout<<"FeldmanCousins "<<pEff->GetEfficiency(1)<<" "<<pEff->GetEfficiencyErrorLow(1)<<" "<<pEff->GetEfficiencyErrorUp(1)<<std::endl;
  // pEff->SetStatisticOption(TEfficiency::kBJeffrey);
  // std::cout<<"Jeffrey "<<pEff->GetEfficiency(1)<<" "<<pEff->GetEfficiencyErrorLow(1)<<" "<<pEff->GetEfficiencyErrorUp(1)<<std::endl;
  // std::cout<<" "<<std::endl;


  TF1 *fi1 = new TF1("fi1", "expo", 0,15);
  gr->Fit(fi1,"R");
  // TF1 *fi2 = new TF1("fi2", "pol3", 2,35);
  //gr->Fit(fi2,"R");
  gr->SetTitle("");
  gr->GetXaxis()->SetTitle("Momentum [MeV]");
  gr->GetYaxis()->SetTitle("Efficiency");
  gr->Draw("A*");
  std::cout<<"Value from fit "<<fi1->Integral(0,4)<<" "<<fi1->IntegralError(0,4)<<std::endl;
  gPad->SetLogy(1);
  c1->Print("../Figures/PhoCon40/mompho_log.png");

}

