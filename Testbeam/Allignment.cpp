#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TRint.h"
#include "TStyle.h"
#include "TROOT.h"
#include <iostream>
#include <vector>

void plotPro(TH2D* hist,TString NAME,bool slice,int SliNum,TString SliceName,TString yaxis,int x0, int x1){
  //gROOT->SetStyle("ATLAS");
  // if(slice){
  //   TCanvas *c2 = new TCanvas();
  //   TLatex latex;
  //   latex.SetTextSize(0.05);
  //   TH1D * po = hist->ProjectionY("test",SliNum,SliNum);
  //   TF1  * Fit = new TF1("Fit","gaus",-500,500);
  //   //po->Fit("Fit");
  //   //double mean = Fit->GetParameter(1);
  //  //double std = Fit->GetParameter(2);
  //   //latex.DrawLatex(800,120,Form("Mean = %3.3f",mean));
  //   //latex.DrawLatex(1000,110,Form("#sigma = %0.3f",std));
  //   po->Draw();
  //   c2->Print("/hepstore/agroves/MyStudies/Testbeam/Plots/Allignment/"+SliceName+""+SliNum+".png");
  // }
  // else{
  gStyle->SetOptStat(0);
  TProfile *Pro = hist->ProfileX("te",0,1000);
  Pro->GetYaxis()->SetTitle(yaxis);
  if( x1 > 0){
    Pro->GetXaxis()->SetRangeUser(x0,x1);}
    TCanvas *c1 = new TCanvas();
    Pro->Draw();
    c1->Print("/hepstore/agroves/MyStudies/Testbeam/Plots/Allignment/"+NAME+".png");
   
}

void Plotting2D(TH2D* hist,TString NAME){
  gROOT->SetStyle("ATLAS");
  TCanvas *c3 = new TCanvas();
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetYaxis()->SetRangeUser(-1000,1000);
    gStyle->SetPalette(kViridis);
  hist->Draw("COLZ");
  c3->Print("/hepstore/agroves/MyStudies/Testbeam/Plots/Allignment/"+NAME+".png");
}

void PlottingRes(TH1F* histx, TH1F* histy, TString NAMEX, TString NAMEY, int MuPix){
  gROOT->SetStyle("ATLAS");
  TLatex latex;
  latex.SetTextSize(0.05);
  TCanvas *c3 = new TCanvas();
  TF1  * Fitx = new TF1("Fitx","gaus",-500,500);
  histx->Fit("Fitx");
  TF1  * Fity = new TF1("Fity","gaus",-500,500);
  histy->Fit("Fity");
  double meanx = Fitx->GetParameter(1);
  double stdx = Fitx->GetParameter(2);
  double meany = Fity->GetParameter(1);
  double stdy = Fity->GetParameter(2);
  histx->GetXaxis()->SetRangeUser(-1500,1500);
  histx->GetYaxis()->SetTitleOffset(1.4);
  histy->GetXaxis()->SetRangeUser(-1500,1500);
  histy->GetYaxis()->SetTitleOffset(1.4);
  histx->Draw();
  if( MuPix == 9){
    latex.DrawLatex(600,35000,Form("Mean = %3.3f",meanx));  //x positons
    latex.DrawLatex(700,32000,Form("#sigma = %0.3f",stdx));}
  if(MuPix == 89){
    latex.DrawLatex(400,2800e3,Form("Mean = %3.3f #mum",meanx));  //x positions for MuPix8
    latex.DrawLatex(600,2500e3,Form("#sigma = %0.3f #mum",stdx));}
  if(MuPix == 8){
    latex.DrawLatex(400,2800e3,Form("Mean = %3.3f #mum",meanx));  //x positions for MuPix8
    latex.DrawLatex(600,2500e3,Form("#sigma = %0.3f #mum",stdx));}
  c3->Print("/hepstore/agroves/MyStudies/Testbeam/Plots/Allignment/"+NAMEX+".png");
  TCanvas *c4 = new TCanvas();
  histy->Draw();
  if( MuPix == 9){
    latex.DrawLatex(600,42000,Form("Mean = %3.3f",meany));  //y positions
    latex.DrawLatex(700,38500,Form("#sigma = %0.3f",stdy));}
  if(MuPix == 89){
    latex.DrawLatex(400,3200e3,Form("Mean = %3.3f #mum",meany));  //y positions for MuPix8
    latex.DrawLatex(600,2900e3,Form("#sigma = %0.3f #mum",stdy));}
  if(MuPix == 8){
    latex.DrawLatex(400,3200e3,Form("Mean = %3.3f #mum",meany));  //y positions for MuPix8
    latex.DrawLatex(600,2900e3,Form("#sigma = %0.3f #mum",stdy));}
  c4->Print("/hepstore/agroves/MyStudies/Testbeam/Plots/Allignment/"+NAMEY+".png");
}

void Allignment(bool profile){
  //gStyle->SetOptStat(0);
  TFile *f8 = new TFile("analysis_001436-001436_dut-01_searchWindow-0400_timeCut-0020_HP-REMOVAL-OFF.root");
  TFile *f9 = new TFile("analysis_PSI_2019_10_002164-002184_dut-01_searchWindow-0900_timeCut-0100_HP-REMOVAL-OFF_new.root");

  if(profile){
    TH2D * resXvsposX9 = (TH2D*)f9->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_X_vs_pos_X_1");
    TH2D * resXvsposY9 = (TH2D*)f9->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_X_vs_pos_Y_1");
    TH2D * resYvsposX9 = (TH2D*)f9->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_Y_vs_pos_X_1");
    TH2D * resYvsposY9 = (TH2D*)f9->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_Y_vs_pos_Y_1");
    plotPro(resXvsposY9,"resXvsposYPro9",false,5,"resXvsposYSlice9","col residual",0,0);
    plotPro(resXvsposX9,"resXvsposXPro9",false,5,"resXvsposXSlice9","col residual",0,49);
    plotPro(resYvsposY9,"resYvsposYPro9",false,5,"resYvsposYSlice9","row residual",0,0);
    plotPro(resYvsposX9,"resYvsposXPro9",false,5,"resYvsposXSlice9","row residual",0,49);
    TH2D * resXvsposX = (TH2D*)f8->Get("alignment_dut_1/unbiased_residuals_1/res_X_vs_pos_X_1");
    TH2D * resXvsposY = (TH2D*)f8->Get("alignment_dut_1/unbiased_residuals_1/res_X_vs_pos_Y_1");
    TH2D * resYvsposX = (TH2D*)f8->Get("alignment_dut_1/unbiased_residuals_1/res_Y_vs_pos_X_1");
    TH2D * resYvsposY = (TH2D*)f8->Get("alignment_dut_1/unbiased_residuals_1/res_Y_vs_pos_Y_1");
    plotPro(resXvsposY,"resXvsposYPro8",false,5,"resXvsposYSlice8","col residual",0,0);
    plotPro(resXvsposX,"resXvsposXPro8",false,5,"resXvsposXSlice8","col residual",0,49);
    plotPro(resYvsposY,"resYvsposYPro8",false,5,"resYvsposYSlice8","row residual",0,0);
    plotPro(resYvsposX,"resYvsposXPro8",false,5,"resYvsposXSlice8","row residual",0,49);
  }
  else{
    TH1F * resx9 = (TH1F*)f9->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_X_1");
    TH1F * resy9 = (TH1F*)f9->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_Y_1");
    PlottingRes(resx9,resy9,"resx9","resy9",9);
    TH1F * resx89 = (TH1F*)f9->Get("AlignmentHistograms/biased_residuals_0/res_X_0");
    TH1F * resy89 = (TH1F*)f9->Get("AlignmentHistograms/biased_residuals_0/res_Y_0");
    PlottingRes(resx89,resy89,"resx89","resy89",89);
    TH1F * resx8 = (TH1F*)f9->Get("alignment_dut_1/unbiased_residuals_1/res_X_1");
    TH1F * resy8 = (TH1F*)f9->Get("alignment_dut_1/unbiased_residuals_1/res_Y_1");
    PlottingRes(resx8,resy8,"resx8","resy8",8);
  }

}
