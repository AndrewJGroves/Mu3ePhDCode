#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>




void MainStudy(TString inname, TString outname){
  TFile *f = new TFile(inname,"READ");
  TTree *tree = (TTree*)f->Get("Results");
  TFile fileout(outname,"RECREATE");

  double px1, py1, pz1, px2, py2, pz2,px3, py3, pz3,px4, py4, pz4, px5, py5, pz5;  

  double WT;
  double mat;
  double weight;
  tree->SetBranchAddress("px1",&px1);
  tree->SetBranchAddress("px2",&px2);
  tree->SetBranchAddress("px3",&px3);
  tree->SetBranchAddress("px4",&px4);
  tree->SetBranchAddress("px5",&px5);
  tree->SetBranchAddress("py1",&py1);
  tree->SetBranchAddress("py2",&py2);
  tree->SetBranchAddress("py3",&py3);
  tree->SetBranchAddress("py4",&py4);
  tree->SetBranchAddress("py5",&py5);
  tree->SetBranchAddress("pz1",&pz1);
  tree->SetBranchAddress("pz2",&pz2);
  tree->SetBranchAddress("pz3",&pz3);
  tree->SetBranchAddress("pz4",&pz4);
  tree->SetBranchAddress("pz5",&pz5);
  tree->SetBranchAddress("WT",&WT);
  tree->SetBranchAddress("mat",&mat);
  tree->SetBranchAddress("weight",&weight);


  TH1F *h_weight = new TH1F("h_weight", "Weight",1e4 ,0,13e9);
  TH1F *h_mat = new TH1F("h_mat", "Mat",1000 ,0,0.001);

  TH1F *h_angleE1E2 = new TH1F("h_angleE1E2", "Angle 1",500 ,0,5);
  TH1F *h_angleE2E3 = new TH1F("h_angleE2E3", "Angle 2",500 ,0,5);
  TH1F *h_angleE1E3 = new TH1F("h_angleE1E3", "Angle 3",500 ,0,5);

  TH1F *h_massmu = new TH1F("h_massmu", "Mass mu", 1000,0,200);
  TH1F *h_tmommu = new TH1F("h_tmommu", "Absolute momentum mu", 1000,0,100);
  TH1F *h_Emu = new TH1F("h_Emu", "E mu", 1000,0,200);
  TH1F *h_Emumu3e = new TH1F("h_Emumu3e", "mu E mu", 100,0,1);

  TH1F *h_massmu3e = new TH1F("h_massmu3e", "Mass mu3e", 1000,0,200);
  TH1F *h_tmommu3e = new TH1F("h_tmommu3e", "Absolute momentum mu3e", 1000,0,100);
  TH1F *h_Emu3e = new TH1F("h_Emu3e", "E mu3e", 1000,0,100);
  TH1F *h_muEmu3e = new TH1F("h_muEmu3e", "Emu mu3e", 500,0,100);

  TH1F *h_tmome1 = new TH1F("h_tmome1", "Absolute momentum e1", 1000,0,100);
  TH1F *h_tmome2 = new TH1F("h_tmome2", "Absolute momentum e2", 1000,0,100);
  TH1F *h_tmome3 = new TH1F("h_tmome3", "Absolute momentum e3", 1000,0,100);
  TH1F *h_tmomnu1 = new TH1F("h_tmomnu1", "Absolute momentum nu1", 1000,0,100);
  TH1F *h_tmomnu2 = new TH1F("h_tmomnu2", "Absolute momentum nu2", 1000,0,100);


  Long64_t n = tree->GetEntries();
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    tree->GetEntry(i);

    TLorentzVector e1;
    TLorentzVector e2;
    TLorentzVector e3;
    TLorentzVector nu1;
    TLorentzVector nu2;
    TLorentzVector mu;
    TLorentzVector mu3e;

    double emass = 0.51099895;
    double mmass = 105.65837;

    e1.SetPxPyPzE(px1,py1,pz1,TMath::Sqrt(emass*emass+(px1*px1+py1*py1+pz1*pz1)));
    e2.SetPxPyPzE(px2,py2,pz2,TMath::Sqrt(emass*emass+(px2*px2+py2*py2+pz2*pz2)));
    e3.SetPxPyPzE(px3,py3,pz3,TMath::Sqrt(emass*emass+(px3*px3+py3*py3+pz3*pz3)));
    
    nu1.SetPxPyPzE(px4,py4,pz4,TMath::Sqrt((px4*px4+py4*py4+pz4*pz4)));
    nu2.SetPxPyPzE(px5,py5,pz5,TMath::Sqrt((px5*px5+py5*py5+pz5*pz5)));
    TVector3 e1p(px1, py1,pz1);
    TVector3 e2p(px2, py2,pz2);
    TVector3 e3p(px3, py3,pz3);
    mu = e1+e2+e3+nu1+nu2;
    mu3e = e1+e2+e3;


    h_weight->Fill(weight);
    h_mat->Fill(mat);
    h_massmu->Fill(mu.M());
    h_tmommu->Fill(mu.P());
    h_Emu->Fill(mu.E());
    
    h_massmu3e->Fill(mu3e.M());
    h_tmommu3e->Fill(mu3e.P());
    h_Emu3e->Fill(mu3e.E());
    h_Emumu3e->Fill((mu3e.E())/mmass);
    h_muEmu3e->Fill(mmass-(mu3e.E()));
    
    

    h_tmome1 ->Fill(e1.P());
    h_tmome2 ->Fill(e2.P());
    h_tmome3->Fill(e3.P());
    h_tmomnu1 ->Fill(nu1.P());
    h_tmomnu2->Fill(nu2.P());
    h_angleE1E2->Fill(e2p.Angle(e1p));
    h_angleE1E3->Fill(e3p.Angle(e1p));
    h_angleE2E3->Fill(e2p.Angle(e3p));



  }


  h_weight->Write();
  h_mat->Write();
  h_angleE1E2->Write();
  h_angleE2E3->Write();
  h_angleE1E3->Write();
  h_massmu->Write();
  h_tmommu->Write();
  h_Emu->Write();
  h_muEmu3e->Write();
  h_massmu3e->Write();
  h_tmommu3e->Write();
  h_Emu3e->Write();
  h_Emumu3e->Write();
  h_tmome1 ->Write();
  h_tmome2 ->Write();
  h_tmome3->Write();
  h_tmomnu1 ->Write();
  h_tmomnu2->Write();


  fileout.Close();

}
