#include "TMath.h"
#include "TH3F.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>


void test1(){
  TFile *f = new TFile("/hepstore/agroves/mu3e_42/mu3e/run/data/IC.root","READ");
  TTree *t1 = (TTree*)f->Get("vertex");

  TFile fileout("plots.root","RECREATE");
  u_int nvert;
  vector<double> *true_vx=0,*true_vy=0,*true_vz=0;
  vector<double> *vx=0,*vy=0,*vz=0;

  t1->SetBranchAddress("nvert", &nvert);   
  t1->SetBranchAddress("true_vx",&true_vx);
  t1->SetBranchAddress("true_vy",&true_vy);
  t1->SetBranchAddress("true_vz",&true_vz);
  t1->SetBranchAddress("vx",&vx);
  t1->SetBranchAddress("vy",&vy);
  t1->SetBranchAddress("vz",&vz);


  TH3F *tar = new TH3F("tar","tar",40,-20,20,40,-20,20,100,-50,50);
  TH1F *target = new TH1F("target","target",200,-100,100);



  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    t1->GetEntry(i);

    for(int p=0; p<(int)nvert ; p++){
      target->Fill(vx->at(p));
      tar->Fill(vx->at(p),vy->at(p),vz->at(p));
    }

  }
  target->Write();
  tar->Write();
  fileout.Close();
} 
