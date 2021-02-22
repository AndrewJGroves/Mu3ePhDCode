#include "TGraph.h"
#include "TMath.h"
#include "TH1F.h"
#include <math.h>
#include <iostream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include <vector>
#include <string>
#include "TStyle.h"
#include "TROOT.h"


std::vector<double> SESgen(double i){
  double eff_3l=0.204719;
  double eff_all=0.379269;
  double ceff_3l=1.497921e-01;//1.137921e-01;
  double ceff_all= 0.286755;

  double SES_3l=1/(i*eff_3l);
  double SES_all=1/(i*eff_all);
  double cSES_3l=1/(i*ceff_3l);
  double cSES_all=1/(i*ceff_all);
  std::vector<double> lim;
  lim.push_back(SES_3l);
  lim.push_back(SES_all);
  lim.push_back(cSES_3l); //Important
  lim.push_back(cSES_all);

  return lim;   
}

std::vector<double> limit(double i,double lamda){
  std::vector<double> SES(SESgen(i));
  std::vector<double> lim;
  lim.push_back(lamda*SES[0]);
  lim.push_back(lamda*SES[1]);
  lim.push_back(lamda*SES[2]); //Important
  lim.push_back(lamda*SES[3]);

  return lim;   
}

void filler(TGraph *gr_90, TGraph *gr_95,TGraph *ses, std::string output, double xmin){
  TCanvas *c= new TCanvas();
  TLegend *legend = new TLegend(.55,.70,.85,.85);
  legend->AddEntry(gr_90,"90% confidence","l");
  legend->AddEntry(gr_95,"95% confidence","l");
  legend->AddEntry(ses,"SIS","l");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);  
  gr_90->SetLineColor(kRed);
  ses->SetLineColor(kGreen);
  gr_90->SetLineWidth(3);
  gr_90->GetXaxis()->SetTitle("N_{target}");
  gr_90->GetYaxis()->SetTitle("Limit");
  TLatex Tl;
  TArrow *myarrow = new TArrow();
  std::string s2 ("_log");
  if (output.find(s2) != std::string::npos) {
    gPad->SetLogy(1);
    gr_90->GetYaxis()->SetRangeUser(2E-15, 10E-13);

  }
  else{
    gPad->SetLogy(0);
    //gr_90->GetYaxis()->SetRangeUser(0, 5E-6);
  }
  gr_90->GetXaxis()->SetRangeUser(xmin+5E13, 4000E12);
  gr_90->Draw("AC");
  gr_95->Draw("C");
  ses->Draw("C");

  legend->Draw();
  if (output.find(s2) != std::string::npos) {
    TArrow *myarrow = new TArrow(2500E12,1.6E-14,2500E12,0,1,"|>");
    myarrow->SetArrowSize(0.03);
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.DrawLatexNDC(0.53,0.38,"Phase 1 target");
    myarrow->Draw(); 
  }
  else{
    TArrow *myarrow = new TArrow(2500E12,0.045E-12,2500E12,0,1,"|>");
    myarrow->SetArrowSize(0.03);
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.DrawLatexNDC(0.53,0.38,"Phase 1 target");
    myarrow->Draw();
  }
  const char * out = output.c_str();
  c->Print(out);
}

void filler2(TGraph *gr_90, TGraph *gr_95,TGraph *ses, std::string output, double xmin){
  TCanvas *c= new TCanvas();
  TLegend *legend = new TLegend(.65,.75,.95,.9);
  legend->AddEntry(gr_90,"90% confidence","l");
  legend->AddEntry(gr_95,"95% confidence","l");
  legend->AddEntry(ses,"SES","l");

  legend->SetFillStyle(0);
  legend->SetBorderSize(0);  
  gr_90->SetLineColor(kRed);
  ses->SetLineColor(kGreen);
  gr_90->SetLineWidth(3);
  gr_90->GetXaxis()->SetTitle("Days");
  gr_90->GetYaxis()->SetTitle("Limit");
  TLatex Tl;
  TArrow *myarrow = new TArrow();
  std::string s2 ("_log");
  if (output.find(s2) != std::string::npos) {
    gPad->SetLogy(1);
    gr_90->GetYaxis()->SetRangeUser(1E-15, 1E-11);
  }
  else{
    gPad->SetLogy(0);
    //gr_90->GetYaxis()->SetRangeUser(0, 5E-6);
  }
  gr_90->GetXaxis()->SetRangeUser(0, 400);
  gr_90->Draw("AC");
  gr_95->Draw("C");
  ses->Draw("C");
  legend->Draw();
  if (output.find(s2) != std::string::npos) {
    TArrow *myarrow = new TArrow(2500E12,30E-15,2500E12,0,1,"|>");
    myarrow->SetArrowSize(0.03);
    TLatex * text7 = new TLatex(205, 6E-13, "SINDRUM 1988");
    text7->SetTextFont(42);
    text7->SetTextColor(kBlue+3);
    text7->SetTextSize(0.05);
    text7->Draw();
    TLine * l2 = new TLine(0,1e-12,400,1e-12);
    l2->SetLineColor(kBlue+3);
    l2->SetLineStyle(2);
    l2->Draw();
    myarrow->Draw(); 
    TLine * l = new TLine(0,2e-15,400,2e-15);
    l->SetLineColor(2);
    l->SetLineStyle(2);
    l->Draw();
    TLatex * text1 = new TLatex(10, 2.5E-15, "2 #times 10^{-15}");
    text1->SetTextFont(42);
    text1->SetTextColor(2);
    text1->SetTextSize(0.05);
    text1->Draw();
  }
  else{
    TArrow *myarrow = new TArrow(2500E12,0.045E-12,2500E12,0,1,"|>");
    myarrow->SetArrowSize(0.03);
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.DrawLatexNDC(0.53,0.38,"Phase 1 target");
    myarrow->Draw();
  }
  const char * out = output.c_str();
  c->Print(out);
}

void sensitivity(){
gROOT->SetStyle("ATLAS");
  TGraph *ses_3l = new TGraph();
  TGraph *ses_all = new TGraph();
  TGraph *ses_cut3l = new TGraph();
  TGraph *ses_cutall = new TGraph();
  TGraph *nses_3l = new TGraph();
  TGraph *nses_all = new TGraph();
  TGraph *nses_cut3l = new TGraph();
  TGraph *nses_cutall = new TGraph();


  TGraph *g90_3l = new TGraph();
  TGraph *g90_all = new TGraph();
  TGraph *g90_cut3l = new TGraph();
  TGraph *g90_cutall = new TGraph();
  TGraph *g95_3l = new TGraph();
  TGraph *g95_all = new TGraph();
  TGraph *g95_cut3l = new TGraph();
  TGraph *g95_cutall = new TGraph();

  TGraph *dg90_3l = new TGraph();
  TGraph *dg90_all = new TGraph();
  TGraph *dg90_cut3l = new TGraph();
  TGraph *dg90_cutall = new TGraph();
  TGraph *dg95_3l = new TGraph();
  TGraph *dg95_all = new TGraph();
  TGraph *dg95_cut3l = new TGraph();
  TGraph *dg95_cutall = new TGraph();


  double lamda_90 = -std::log(0.1);
  double lamda_95 = -std::log(0.05);


  double phase1 = 1E8; //muons/s
  double phase1Day = phase1*86400;
  int j=1;
  // Limit as a function of days 
  for (double n=0.1 ; n<400 ; n=n+0.1){
    double rate=phase1Day*n;
    std::vector<double> ses( SESgen(rate) );
    std::vector<double> lim_90( limit(rate,lamda_90) );
    std::vector<double> lim_95( limit(rate,lamda_95) );
    dg90_3l->SetPoint(j,n,lim_90[0]);
    dg90_all->SetPoint(j,n,lim_90[1]);
    dg90_cut3l->SetPoint(j,n,lim_90[2]);//Important
    dg90_cutall->SetPoint(j,n,lim_90[3]);
    dg95_3l->SetPoint(j,n,lim_95[0]);
    dg95_all->SetPoint(j,n,lim_95[1]);
    dg95_cut3l->SetPoint(j,n,lim_95[2]);//Important
    dg95_cutall->SetPoint(j,n,lim_95[3]);
    ses_3l->SetPoint(j,n,ses[0]);
    ses_all->SetPoint(j,n,ses[1]);
    ses_cut3l->SetPoint(j,n,ses[2]);//Important
    ses_cutall->SetPoint(j,n,ses[3]);
    j++;
  }


  //Limit as a function of ntarget
  double high = 4E15;
  double stepl = 1E14;
  int k = 0;
  for( double i=0; i < high; i=i+stepl){
    if ( i == 0 ) continue;
    k++;
    std::vector<double> ses( SESgen(i) );
    std::vector<double> lim_90( limit(i,lamda_90) );
    std::vector<double> lim_95( limit(i,lamda_95) );
    g90_3l->SetPoint(k,i,lim_90[0]);
    g90_all->SetPoint(k,i,lim_90[1]);
    g90_cut3l->SetPoint(k,i,lim_90[2]);
    g90_cutall->SetPoint(k,i,lim_90[3]);
    g95_3l->SetPoint(k,i,lim_95[0]);
    g95_all->SetPoint(k,i,lim_95[1]);
    g95_cut3l->SetPoint(k,i,lim_95[2]);
    g95_cutall->SetPoint(k,i,lim_95[3]);
    nses_3l->SetPoint(k,i,ses[0]);
    nses_all->SetPoint(k,i,ses[1]);
    nses_cut3l->SetPoint(k,i,ses[2]);
    nses_cutall->SetPoint(k,i,ses[3]);
  }


  filler(g90_cut3l,g95_cut3l,nses_cut3l,std::string ("3lhitsCut_log.png"),stepl);
  filler2(dg90_cut3l,dg95_cut3l,ses_cut3l,std::string ("3ldaysCut_log.png"),0);
  //filler(g90_3l,g95_3l,std::string ("3lhits_log.png"),stepl);
  //filler2(dg90_3l,dg95_3l,std::string ("3ldays_log.png"),0);


}
