#include "TFile.h"
#include "TH1F.h"
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
  std::vector<double> run;
  std::vector<double> layer0MeanX, layer0RMSX, layer0MeanY, layer0RMSY, layer0MeanXerr, layer0MeanYerr, layer0RMSXerr, layer0RMSYerr;
  std::vector<double> layer1MeanX, layer1RMSX, layer1MeanY, layer1RMSY, layer1MeanXerr, layer1MeanYerr, layer1RMSXerr, layer1RMSYerr;
  std::vector<double> layer2MeanX, layer2RMSX, layer2MeanY, layer2RMSY, layer2MeanXerr, layer2MeanYerr, layer2RMSXerr, layer2RMSYerr;
  std::vector<double> layer3MeanX, layer3RMSX, layer3MeanY, layer3RMSY, layer3MeanXerr, layer3MeanYerr, layer3RMSXerr, layer3RMSYerr;


  int mupix = 9;
  TString MuPix;
  TString matchR = "400";
  TString HP;

  //TString dirc = "/hepstore/agroves/testbeam/201910/analysis/analysis_00";
  //TString dirc2 = "_dut-01_searchWindow-0"+matchR+"_timeCut-0020_HP-REMOVAL-"+HP+".root";

  int xmeanRange[] ={0,0};
  int ymeanRange[] ={0,0};
  int xRMSRange[] ={0,0};
  int yRMSRange[] ={0,0};
  std::vector<int> start;
  if (mupix == 8){
  HP = "OFF";
  MuPix="8";
  std::vector<int> start1 = {
    2029,
    2041,
    2051,
    2059,
    2067,
    2075,
    2083,
    2091,
    2099,
    2107};
  start.insert(start.begin(),start1.begin(),start1.end());
  }
    
 if (mupix == 9){
  HP = "ON";
  MuPix="9";

  std::vector<int> start2 = {
2164,
			    2171,
			    2178,
			    2186,
			    2194,
			    2201,
			    2208,
			    2215,
			    2232,
			    2243,
			    2254,
			    2263,
			    2270,
			    2277,
			    2285,
			    2292,
//2299,
			    2309,
			    2319,
			    2326,
			    2333,
			    2340,
			    2347,
			    2355,
			    2362,
			    2373,
			    2383,
			    2390,
			    2397,
			    2404,
			    2414,
			    2421,
			    2428,
			    2438,
			    2448,
			    2454,
			    2461,
			    2468,
			    2475,
			    2482};
  start.insert(start.begin(),start2.begin(),start2.end());

 }
 std::vector<int> end;
  if (mupix == 8){
  std::vector<int> end1 = {2039
,2049,2058,
			  2065,
			  2074,
			  2082,
			  2090,
			  2097, 2106,2114
};
  end.insert(end.begin(),end1.begin(),end1.end());
  }

  if (mupix == 9){
  std::vector<int> end2 = {
			  2169,
			   2177,
			   2185,
			   2193,
			   2200,
			   2207,
			   2214,
			  2221,
			  2242,
			  2253,
			  2262,
			  2269,
			  2276,
			  2284,
			  2291,
			  2298,
		  //2308,
			  2318,
			  2325,
			  2332,
			  2339,
			  2346,
			  2354,
			  2361,
			  2372,
			  2382,
			  2389,
			  2396,
			  2403,
			  2413,
			  2420,
			  2427,
			  2437,
			  2447,
			  2453,
			  2460,
			  2467,
			  2474,
			  2481,
  2488};
  end.insert(end.begin(),end2.begin(),end2.end());
  }

  TString dirc = "/hepstore/agroves/testbeam/201910/analysis/analysis_PSI_2019_10_00";
  TString dirc2 = "_dut-01_searchWindow-0"+matchR+"_timeCut-0100_HP-REMOVAL-OFF_new.root";
  int ignor[] = {2170,2177,2284};
  for(int i=0; i<(int)start.size(); i++){
    // if( ignor[0] == i) continue;
    // if( ignor[1] == i) continue;
    // if( ignor[2] == i) continue;

    TString st; st.Form("%d",start[i]); 
    TString en; en.Form("%d",end[i]); 
    TFile *f = new TFile(dirc+st+"-00"+en+dirc2);

    TH1F * layer0X = (TH1F*)f->Get("AlignmentHistograms/biased_residuals_0/res_X_0");
    layer0X->GetXaxis()->SetTitle("x residual plane 0 / #mum");
    layer0X->GetYaxis()->SetTitle("Entries");
    TH1F * layer0Y = (TH1F*)f->Get("AlignmentHistograms/biased_residuals_0/res_Y_0");
    layer0Y->GetXaxis()->SetTitle("y residual plane 0 / #mum");
    layer0Y->GetYaxis()->SetTitle("Entries");
    TH1F * layer1X = (TH1F*)f->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_X_1");
    layer1X->GetXaxis()->SetTitle("x residual plane 1 / #mum");
    layer1X->GetYaxis()->SetTitle("Entries");
    TH1F * layer1Y = (TH1F*)f->Get("AlignmentHistograms/unbiased_residuals_DUT_1/res_Y_1");
    layer1Y->GetXaxis()->SetTitle("y residual plane 1 / #mum");
    layer1Y->GetYaxis()->SetTitle("Entries");
    TH1F * layer2X = (TH1F*)f->Get("AlignmentHistograms/biased_residuals_2/res_X_2");
    layer2X->GetXaxis()->SetTitle("x residual plane 2 / #mum");
    layer2X->GetYaxis()->SetTitle("Entries");
    TH1F * layer2Y = (TH1F*)f->Get("AlignmentHistograms/biased_residuals_2/res_Y_2");
    layer2Y->GetXaxis()->SetTitle("y residual plane 2 / #mum");
    layer2Y->GetYaxis()->SetTitle("Entries");
    TH1F * layer3X = (TH1F*)f->Get("AlignmentHistograms/biased_residuals_3/res_X_3");
    layer3X->GetXaxis()->SetTitle("x residual plane 3 / #mum");
    layer3X->GetYaxis()->SetTitle("Entries");
    TH1F * layer3Y = (TH1F*)f->Get("AlignmentHistograms/biased_residuals_3/res_Y_3");
    layer3Y->GetXaxis()->SetTitle("y residual plane 3 / #mum");
    layer3Y->GetYaxis()->SetTitle("Entries");

    
            
    TF1  * Fitlayer0X = new TF1("Fitlayer0X","gaus",-500,500);
    TF1  * Fitlayer0Y = new TF1("Fitlayer0Y","gaus",-500,500);
    TF1  * Fitlayer1X = new TF1("Fitlayer1X","gaus",-500,500);
    TF1  * Fitlayer1Y = new TF1("Fitlayer1Y","gaus",-500,500);
    TF1  * Fitlayer2X = new TF1("Fitlayer2X","gaus",-500,500);
    TF1  * Fitlayer2Y = new TF1("Fitlayer2Y","gaus",-500,500);
    TF1  * Fitlayer3X = new TF1("Fitlayer3X","gaus",-500,500);
    TF1  * Fitlayer3Y = new TF1("Fitlayer3Y","gaus",-500,500);

    layer0X->Fit("Fitlayer0X");
    TCanvas *cr1 = new TCanvas();
    layer0X->Draw();
    //cr1->Print("./Plots/ResidualRun/"+st+"-"+en+"_0X.png");
     layer0Y->Fit("Fitlayer0Y");
    TCanvas *cr2 = new TCanvas();
    layer0Y->Draw();
    //cr2->Print("./Plots/ResidualRun/"+st+"-"+en+"_0Y.png");
     layer1X->Fit("Fitlayer1X");
    TCanvas *cr3 = new TCanvas();
    layer1X->Draw();
    layer1X->Draw("E1,same");
    //cr3->Print("./Plots/ResidualRun/"+st+"-"+en+"_1X.png");
     layer1Y->Fit("Fitlayer1Y");
    TCanvas *cr4 = new TCanvas();
    layer1Y->Draw();
    layer1Y->Draw("E1,same");
    //cr4->Print("./Plots/ResidualRun/"+st+"-"+en+"_1Y.png");
     layer2X->Fit("Fitlayer2X");
    TCanvas *cr5 = new TCanvas();
    layer2X->Draw();
    //cr5->Print("./Plots/ResidualRun/"+st+"-"+en+"_2X.png");
     layer2Y->Fit("Fitlayer2Y");
    TCanvas *cr6 = new TCanvas();
    layer2Y->Draw();
    //cr6->Print("./Plots/ResidualRun/"+st+"-"+en+"_2Y.png");
     layer3X->Fit("Fitlayer3X");
    TCanvas *cr7 = new TCanvas();
    layer3X->Draw();
    //cr7->Print("./Plots/ResidualRun/"+st+"-"+en+"_3X.png");
     layer3Y->Fit("Fitlayer3Y");
    TCanvas *cr8 = new TCanvas();
    layer3Y->Draw();
    //cr8->Print("./Plots/ResidualRun/"+st+"-"+en+"_3Y.png");

    layer0MeanX.push_back(Fitlayer0X->GetParameter(1));
    layer0MeanXerr.push_back(Fitlayer0X->GetParError(1));
    layer0MeanY.push_back(Fitlayer0Y->GetParameter(1));
    layer0MeanYerr.push_back(Fitlayer0Y->GetParError(1));
    layer1MeanX.push_back(Fitlayer1X->GetParameter(1));
    layer1MeanXerr.push_back(Fitlayer1X->GetParError(1));
    layer1MeanY.push_back(Fitlayer1Y->GetParameter(1));
    layer1MeanYerr.push_back(Fitlayer1Y->GetParError(1));
    layer2MeanX.push_back(Fitlayer2X->GetParameter(1));
    layer2MeanXerr.push_back(Fitlayer2X->GetParError(1));
    layer2MeanY.push_back(Fitlayer2Y->GetParameter(1));
    layer2MeanYerr.push_back(Fitlayer2Y->GetParError(1));
    layer3MeanX.push_back(Fitlayer3X->GetParameter(1));
    layer3MeanXerr.push_back(Fitlayer3X->GetParError(1));
    layer3MeanY.push_back(Fitlayer3Y->GetParameter(1));
    layer3MeanYerr.push_back(Fitlayer3Y->GetParError(1));


    layer0RMSX.push_back(layer0X->GetRMS());
    layer0RMSY.push_back(layer0Y->GetRMS());
    layer0RMSXerr.push_back(layer0X->GetRMSError());
    layer0RMSYerr.push_back(layer0Y->GetRMSError());
    layer1RMSX.push_back(layer1X->GetRMS());
    layer1RMSY.push_back(layer1Y->GetRMS());
    layer1RMSXerr.push_back(layer1X->GetRMSError());
    layer1RMSYerr.push_back(layer1Y->GetRMSError());
    layer2RMSX.push_back(layer2X->GetRMS());
    layer2RMSY.push_back(layer2Y->GetRMS());
    layer2RMSXerr.push_back(layer2X->GetRMSError());
    layer2RMSYerr.push_back(layer2Y->GetRMSError());
    layer3RMSX.push_back(layer3X->GetRMS());
    layer3RMSY.push_back(layer3Y->GetRMS());
    layer3RMSXerr.push_back(layer3X->GetRMSError());
    layer3RMSYerr.push_back(layer3Y->GetRMSError());

    run.push_back(start[i]);

  }
  
  int n=run.size();


  Double_t runN[n], runXerr[n], layer0MeanX1[n], layer0RMSX1[n], layer0MeanY1[n], layer0RMSY1[n], layer0MeanXerr1[n], layer0MeanYerr1[n], layer0RMSXerr1[n], layer0RMSYerr1[n], layer1MeanX1[n], layer1RMSX1[n], layer1MeanY1[n], layer1RMSY1[n], layer1MeanXerr1[n], layer1MeanYerr1[n], layer1RMSXerr1[n], layer1RMSYerr1[n];
  Double_t layer2MeanX1[n], layer2RMSX1[n], layer2MeanY1[n], layer2RMSY1[n], layer2MeanXerr1[n], layer2MeanYerr1[n], layer2RMSXerr1[n], layer2RMSYerr1[n], layer3MeanX1[n], layer3RMSX1[n], layer3MeanY1[n], layer3RMSY1[n], layer3MeanXerr1[n], layer3MeanYerr1[n], layer3RMSXerr1[n], layer3RMSYerr1[n];
  for( int i = 0; i<n ; i++){
    runN[i]=run[i];
    runXerr[i]=0;
    layer0MeanX1[i]=layer0MeanX[i];
    layer0MeanY1[i]=layer0MeanY[i];
    layer0MeanXerr1[i]=layer0MeanXerr[i];
    layer0MeanYerr1[i]=layer0MeanYerr[i];
    layer0RMSX1[i]=layer0RMSX[i];
    layer0RMSY1[i]=layer0RMSY[i];
    layer0RMSXerr1[i]=layer0RMSXerr[i];
    layer0RMSYerr1[i]=layer0RMSYerr[i];

    layer1MeanX1[i]=layer1MeanX[i];
    layer1MeanY1[i]=layer1MeanY[i];
    layer1MeanXerr1[i]=layer1MeanXerr[i];
    layer1MeanYerr1[i]=layer1MeanYerr[i];
    layer1RMSX1[i]=layer1RMSX[i];
    layer1RMSY1[i]=layer1RMSY[i];
    layer1RMSXerr1[i]=layer1RMSXerr[i];
    layer1RMSYerr1[i]=layer1RMSYerr[i];

    layer2MeanX1[i]=layer2MeanX[i];
    layer2MeanY1[i]=layer2MeanY[i];
    layer2MeanXerr1[i]=layer2MeanXerr[i];
    layer2MeanYerr1[i]=layer2MeanYerr[i];
    layer2RMSX1[i]=layer2RMSX[i];
    layer2RMSY1[i]=layer2RMSY[i];
    layer2RMSXerr1[i]=layer2RMSXerr[i];
    layer2RMSYerr1[i]=layer2RMSYerr[i];

    layer3MeanX1[i]=layer3MeanX[i];
    layer3MeanY1[i]=layer3MeanY[i];
    layer3MeanXerr1[i]=layer3MeanXerr[i];
    layer3MeanYerr1[i]=layer3MeanYerr[i];
    layer3RMSX1[i]=layer3RMSX[i];
    layer3RMSY1[i]=layer3RMSY[i];
    layer3RMSXerr1[i]=layer3RMSXerr[i];
    layer3RMSYerr1[i]=layer3RMSYerr[i];
  }


  TCanvas *cxmean = new TCanvas("cxmean","cxmean",700, 500);
  cxmean->SetGrid();
  TLegend *leg1 = new TLegend(0.7,0.70,0.95,0.94);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);  
  TGraphErrors * layer0Xmean = new TGraphErrors(n,runN,layer0MeanX1,runXerr,layer0MeanXerr1);
  layer0Xmean->SetMarkerStyle(21);
  layer0Xmean->SetMarkerColor(1);
  layer0Xmean->SetDrawOption("AP");
  TGraphErrors * layer1Xmean = new TGraphErrors(n,runN,layer1MeanX1,runXerr,layer1MeanXerr1);
  layer1Xmean->SetMarkerStyle(22);
  layer1Xmean->SetMarkerColor(2);
  layer1Xmean->SetDrawOption("AP");
  TGraphErrors * layer2Xmean = new TGraphErrors(n,runN,layer2MeanX1,runXerr,layer2MeanXerr1);
  layer2Xmean->SetMarkerStyle(23);
  layer2Xmean->SetMarkerColor(3);
  layer2Xmean->SetDrawOption("AP");
  TGraphErrors * layer3Xmean = new TGraphErrors(n,runN,layer3MeanX1,runXerr,layer3MeanXerr1);
  layer3Xmean->SetMarkerStyle(24);
  layer3Xmean->SetMarkerColor(4);
  layer3Xmean->SetDrawOption("AP");


  TMultiGraph * xmean = new TMultiGraph("xmean","xmean");
  xmean->Add(layer0Xmean);
  xmean->Add(layer1Xmean);
  xmean->Add(layer2Xmean);
  xmean->Add(layer3Xmean);
  if( xmeanRange[0]!=0 || xmeanRange[1]!=0) xmean->GetYaxis()->SetRangeUser(xmeanRange[0],xmeanRange[1]);
  xmean->GetXaxis()->SetTitle("run");
  xmean->GetYaxis()->SetTitle("mean x residual / #mum");
  leg1->AddEntry(layer0Xmean,"Layer 0", "P");
  leg1->AddEntry(layer1Xmean,"Layer 1", "P");
  leg1->AddEntry(layer2Xmean,"Layer 2", "P");
  leg1->AddEntry(layer3Xmean,"Layer 3", "P");
  xmean->Draw("AP");
  leg1->Draw();
  cxmean->Print("./Plots/xmean"+MuPix+"_"+matchR+".png");

  TCanvas *cymean = new TCanvas("cymean","cymean",700, 500);
  cymean->SetGrid();
  TLegend *leg2 = new TLegend(0.7,0.7,0.95,0.94);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);  
  TGraphErrors * layer0Ymean = new TGraphErrors(n,runN,layer0MeanY1,runXerr,layer0MeanYerr1);
  layer0Ymean->SetMarkerStyle(21);
  layer0Ymean->SetMarkerColor(1);
  layer0Ymean->SetDrawOption("AP");
  TGraphErrors * layer1Ymean = new TGraphErrors(n,runN,layer1MeanY1,runXerr,layer1MeanYerr1);
  layer1Ymean->SetMarkerStyle(22);
  layer1Ymean->SetMarkerColor(2);
  layer1Ymean->SetDrawOption("AP");
  TGraphErrors * layer2Ymean = new TGraphErrors(n,runN,layer2MeanY1,runXerr,layer2MeanYerr1);
  layer2Ymean->SetMarkerStyle(23);
  layer2Ymean->SetMarkerColor(3);
  layer2Ymean->SetDrawOption("AP");
  TGraphErrors * layer3Ymean = new TGraphErrors(n,runN,layer3MeanY1,runXerr,layer3MeanYerr1);
  layer3Ymean->SetMarkerStyle(24);
  layer3Ymean->SetMarkerColor(4);
  layer3Ymean->SetDrawOption("AP");

  TMultiGraph * ymean = new TMultiGraph("ymean","ymean");
  ymean->Add(layer0Ymean);
  ymean->Add(layer1Ymean);
  ymean->Add(layer2Ymean);
  ymean->Add(layer3Ymean);
  if( ymeanRange[0]!=0 || ymeanRange[1]!=0) ymean->GetYaxis()->SetRangeUser(ymeanRange[0],ymeanRange[1]);
  leg2->AddEntry(layer0Ymean,"Layer 0", "P");
  leg2->AddEntry(layer1Ymean,"Layer 1", "P");
  leg2->AddEntry(layer2Ymean,"Layer 2", "P");
  leg2->AddEntry(layer3Ymean,"Layer 3", "P");
  ymean->GetXaxis()->SetTitle("run");
  ymean->GetYaxis()->SetTitle("mean y residual / #mum");
  ymean->Draw("AP");
  leg2->Draw();
  cymean->Print("./Plots/ymean"+MuPix+"_"+matchR+".png");



  TCanvas *cxRMS = new TCanvas("cxRMS","cxRMS",700, 500);
  cxRMS->SetGrid();
  TLegend *leg3 = new TLegend(0.7,0.7,0.95,0.94);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);  
  TGraphErrors * layer0XRMS = new TGraphErrors(n,runN,layer0RMSX1,runXerr,layer0RMSXerr1);
  layer0XRMS->SetMarkerStyle(21);
  layer0XRMS->SetMarkerColor(1);
  layer0XRMS->SetDrawOption("AP");
  TGraphErrors * layer1XRMS = new TGraphErrors(n,runN,layer1RMSX1,runXerr,layer1RMSXerr1);
  layer1XRMS->SetMarkerStyle(22);
  layer1XRMS->SetMarkerColor(2);
  layer1XRMS->SetDrawOption("AP");
  TGraphErrors * layer2XRMS = new TGraphErrors(n,runN,layer2RMSX1,runXerr,layer2RMSXerr1);
  layer2XRMS->SetMarkerStyle(23);
  layer2XRMS->SetMarkerColor(3);
  layer2XRMS->SetDrawOption("AP");
  TGraphErrors * layer3XRMS = new TGraphErrors(n,runN,layer3RMSX1,runXerr,layer3RMSXerr1);
  layer3XRMS->SetMarkerStyle(24);
  layer3XRMS->SetMarkerColor(4);
  layer3XRMS->SetDrawOption("AP");

  TMultiGraph * xRMS = new TMultiGraph("xRMS","xRMS");
  xRMS->Add(layer0XRMS);
  xRMS->Add(layer1XRMS);
  xRMS->Add(layer2XRMS);
  xRMS->Add(layer3XRMS);
  if( xRMSRange[0]!=0 || xRMSRange[1]!=0) xRMS->GetYaxis()->SetRangeUser(xRMSRange[0],xRMSRange[1]);
  xRMS->GetXaxis()->SetTitle("run");
  xRMS->GetYaxis()->SetTitle("RMS x residual / #mum");
  leg3->AddEntry(layer0XRMS,"Layer 0", "P");
  leg3->AddEntry(layer1XRMS,"Layer 1", "P");
  leg3->AddEntry(layer2XRMS,"Layer 2", "P");
  leg3->AddEntry(layer3XRMS,"Layer 3", "P");
  xRMS->Draw("AP");
  leg3->Draw();
  cxRMS->Print("./Plots/xRMS"+MuPix+"_"+matchR+".png");

  TCanvas *cyRMS = new TCanvas("cyRMS","cyRMS",700, 500);
  cyRMS->SetGrid();
  TLegend *leg4 = new TLegend(0.7,0.7,0.95,0.94);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);  
  TGraphErrors * layer0YRMS = new TGraphErrors(n,runN,layer0RMSY1,runXerr,layer0RMSYerr1);
  layer0YRMS->SetMarkerStyle(21);
  layer0YRMS->SetMarkerColor(1);
  layer0YRMS->SetDrawOption("AP");
  TGraphErrors * layer1YRMS = new TGraphErrors(n,runN,layer1RMSY1,runXerr,layer1RMSYerr1);
  layer1YRMS->SetMarkerStyle(22);
  layer1YRMS->SetMarkerColor(2);
  layer1YRMS->SetDrawOption("AP");
  TGraphErrors * layer2YRMS = new TGraphErrors(n,runN,layer2RMSY1,runXerr,layer2RMSYerr1);
  layer2YRMS->SetMarkerStyle(23);
  layer2YRMS->SetMarkerColor(3);
  layer2YRMS->SetDrawOption("AP");
  TGraphErrors * layer3YRMS = new TGraphErrors(n,runN,layer3RMSY1,runXerr,layer3RMSYerr1);
  layer3YRMS->SetMarkerStyle(24);
  layer3YRMS->SetMarkerColor(4);
  layer3YRMS->SetDrawOption("AP");

  TMultiGraph * yRMS = new TMultiGraph("yRMS","yRMS");
  yRMS->Add(layer0YRMS);
  yRMS->Add(layer1YRMS);
  yRMS->Add(layer2YRMS);
  yRMS->Add(layer3YRMS);
  if( yRMSRange[0]!=0 || yRMSRange[1]!=0) yRMS->GetYaxis()->SetRangeUser(yRMSRange[0],yRMSRange[1]);
  leg4->AddEntry(layer0YRMS,"Layer 0", "P");
  leg4->AddEntry(layer1YRMS,"Layer 1", "P");
  leg4->AddEntry(layer2YRMS,"Layer 2", "P");
  leg4->AddEntry(layer3YRMS,"Layer 3", "P");
  yRMS->GetXaxis()->SetTitle("run");
  yRMS->GetYaxis()->SetTitle("RMS y residual / #mum");
  yRMS->Draw("AP");
  leg4->Draw();
  cyRMS->Print("./Plots/yRMS"+MuPix+"_"+matchR+".png");

}
