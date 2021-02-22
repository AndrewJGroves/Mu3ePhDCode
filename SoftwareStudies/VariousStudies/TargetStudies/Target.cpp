#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>


void test(){
  TFile *f = new TFile("/bundle/data/Mu3e/build_4.1/signal/vertex.root","READ");
  TTree *t1 = (TTree*)f->Get("vertex");

  TFile fileout("plots.root","RECREATE");
  u_int nvert;
  vector<double> *true_vx=0,*true_vy=0,*true_vz=0;
  vector<double> *vx=0,*vy=0,*vz=0;
  vector<int> *nhit1=0,*nhit2=0,*nhit3=0;

  t1->SetBranchAddress("true_vx",&true_vx);
  t1->SetBranchAddress("true_vy",&true_vy);
  t1->SetBranchAddress("true_vz",&true_vz);
  t1->SetBranchAddress("vx",&vx);
  t1->SetBranchAddress("vy",&vy);
  t1->SetBranchAddress("vz",&vz);
  t1->SetBranchAddress("nhit1",&nhit1);
  t1->SetBranchAddress("nhit2",&nhit2);
  t1->SetBranchAddress("nhit3",&nhit3);
  t1->SetBranchAddress("nvert", &nvert);   

  TH1F *target = new TH1F("target","target",120,-60,60);
  TH1F *xres = new TH1F("xres","xres",100,-2,2);
  TH1F *yres = new TH1F("yres","yres",100,-2,2);
  TH1F *zres = new TH1F("zres","zres",100,-2,2);
  TH1F *xres_3rec = new TH1F("xres_3rec","xres_3rec",100,-2,2);
  TH1F *yres_3rec = new TH1F("yres_3rec","yres_3rec",100,-2,2);
  TH1F *zres_3rec = new TH1F("zres_3rec","zres_3rec",100,-2,2);

  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    //if (i > 1e6) break;
    t1->GetEntry(i);

    for(int p=0; p<(int)nvert ; p++){
      target->Fill(true_vz->at(p));
      xres->Fill((vx->at(p))-(true_vx->at(p)));
      yres->Fill((vy->at(p))-(true_vy->at(p)));
      zres->Fill((vz->at(p))-(true_vz->at(p)));
      if(nhit1->at(p) >= 6 && nhit2->at(p) >= 6 && nhit3->at(p) >= 6){
	xres_3rec->Fill((vx->at(p))-(true_vx->at(p)));
	yres_3rec->Fill((vy->at(p))-(true_vy->at(p)));
	zres_3rec->Fill((vz->at(p))-(true_vz->at(p)));
      }

    }

  }

  xres->Write();
  yres->Write();
  zres->Write();
  xres_3rec->Write();
  yres_3rec->Write();
  zres_3rec->Write();
  target->Write();
  fileout.Close();


}
