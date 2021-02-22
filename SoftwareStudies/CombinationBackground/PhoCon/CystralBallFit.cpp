#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include "TMath.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1F.h"
#include <algorithm>
#include "TF1.h"
#include "TMatrixD.h"

#include <set> 
#include <random>
#include <algorithm>
#include <string> 

Double_t DSCB(double_t *x, double_t *par){

    Double_t mean = par[1];
    Double_t sigma = par[2];
    Double_t absAlpha1 = abs(par[3]);
    Double_t n1 = par[4];
    Double_t absAlpha2= abs(par[5]);
    Double_t n2 = par[6];

    Double_t A1 = TMath::Power((n1/absAlpha1),n1)*std::exp(-0.5*absAlpha1*absAlpha1);
    Double_t B1 = n1/absAlpha1 - absAlpha1;

    Double_t A2 = TMath::Power((n2/absAlpha2),n2)*std::exp(-0.5*absAlpha2*absAlpha2);
    Double_t B2 = n2/absAlpha2 - absAlpha2;

    Double_t z = (x[0] - mean)/sigma;

    if (z >= -par[3]){
      return (par[0]*A1*TMath::Power(B1+z,-n1));
    }
    if (z <= -par[5]){
      return (par[0]*A2*TMath::Power(B2-z,-n2));
    }else{
      return (par[0]*std::exp(-0.5*z*z));
    }
}

void CystralBallFit(){
  //gROOT->SetStyle("ATLAS");
  gStyle->SetOptStat(0);


  double Ntarget = 1e15;    
  double timming = 0.01;
  //ic_acceptance = 0.62577 
  double mic_acceptance = 0.461745;
  double Scale = Ntarget * 4.6e-6 * mic_acceptance * timming; 
  std::cout<<Scale<<std::endl;
  TCanvas *c = new TCanvas();
  TFile *f = new TFile("/hepstore/agroves/backup/SoftwareStudies/TDRSensitity/CombinationBackground/PhoCon/RootFiles/PhoConShort.root","READ");
  TH1F *mass=(TH1F*)f->Get("h_massLongPho");
  mass->SetFillColor(kRed-9);
  std::string str = std::to_string (mass->GetXaxis()->GetBinWidth(2));
  str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
  TString yaxis = "Events / "+str+"  [MeV/c^{2}]";
  mass->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  mass->GetYaxis()->SetTitle(yaxis);
  mass->SetTitle("");
  double under8=mass->Integral(mass->GetXaxis()->FindBin(103),mass->GetXaxis()->FindBin(110));
  double all1=mass->Integral(0,99999);
  Double_t errunder8;
  Double_t errall;
  mass->IntegralAndError(mass->GetXaxis()->FindBin(103),mass->GetXaxis()->FindBin(110),errunder8);
  mass->IntegralAndError(0,99999,errall);
  double err1=under8/all1*TMath::Sqrt((errunder8/under8)*(errunder8/under8)+(errall/all1)*(errall/all1));
  std::cout<<"Usins graph "<<under8/all1<<" pm "<<err1<<std::endl;
  std::cout<<" "<<std::endl;



  TF1 *fi1 = new TF1("fi1", "pol3", 80,120);
  //TF1 *fi1 = new TF1("fi1", DSCB, 0,120,7);
   // fi1->SetParNames("constant","mean","sigma","alpha1","n1","alpha2","n2");
   // fi1->SetParameters(180,mass->GetMean(),mass->GetRMS(),-4,-3,3,6);
  fi1->SetLineColor(kBlack);
  mass->Rebin(10);

  mass->GetXaxis()->SetRangeUser(0,130);
  mass->Fit("fi1","R");
  mass->SetMarkerStyle(1);
  mass->SetFillColor(kRed-9);
  mass->DrawCopy("HIST");
  mass->SetFillColor(kBlue);
  mass->SetFillStyle(3345);
  mass->DrawCopy("E2,same");
  mass->SetFillColor(kRed-9);
  mass->SetFillStyle(1001);
  gPad->SetLogy(1);
  c->Print("../Figures/PhoCon40/MassPho_log.png");

  double all = fi1->Integral(0,150);
  double sel = fi1->Integral(103,110);
  double eff = fi1->Integral(103,110)/mass->Integral();
  Double_t allerr;
  mass->IntegralAndError(0,99999,allerr);
  Double_t selerr =fi1->IntegralError(103.5,115);
  Double_t efferr = eff * TMath::Sqrt((allerr/all)*(allerr/all)+(selerr/sel)*(selerr/sel));


  //std::cout<<mass->Integral()<<std::endl;
  //std::cout<<fi1->Integral(0,115)<<std::endl;
  //std::cout<<fi1->Integral(103.5,115)<<std::endl;
  std::cout<<"Effeincy for mass range "<<eff<<" +- "<<efferr<<std::endl;
  //std::cout<<fi1->Integral(103.5,115)/fi1->Integral(0,2000000)<<std::endl;
  // mass->Fit("fi1");
  // fi1->Draw("same");

}
