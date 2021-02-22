#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TH2F.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <math.h> 

void test(){
  TFile *f = new TFile("/hepstore/agroves/dev/mu3e/run/data/run000020-reco.root","READ");
  TTree *t1 = (TTree*)f->Get("mc_tracks");

  TFile fileout("PlotsTest.root","RECREATE");
  TH1::SetDefaultSumw2();

  vector<double> *p=0,*pt=0;
  vector<int> *mid=0, *type=0;
  vector<double> *phi=0,*theta=0;

  t1->SetBranchAddress("p",&p);
  t1->SetBranchAddress("pt",&pt);
  t1->SetBranchAddress("mid",&mid);  
  t1->SetBranchAddress("type",&type);  
  t1->SetBranchAddress("phi",&phi);
  t1->SetBranchAddress("theta",&theta);


  TH1F *h_EP_true = new TH1F("h_EPt_true", "EPt true", 1000,0,200);
  TH1F *h_EP = new TH1F("h_EPt", "EPt", 1000,0,200);

  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    //if (i > 1e6) break;
    t1->GetEntry(i);

    TLorentzVector e1;
    TLorentzVector e2;
    TLorentzVector Pho;

    for(int nv=0; nv<(int)p->size() ; nv++){
      double eta = -log(tan(theta->at(nv)/2));
      if( type->at(nv) == 41){
	e1.SetPtEtaPhiM(pt->at(nv),eta,phi->at(nv),0.511);
      }
      if( type->at(nv) == 42){
	e2.SetPtEtaPhiM(pt->at(nv),eta,phi->at(nv),0.511);
      }
    }
    Pho=e1+e2;
    h_EP_true->Fill(Pho.P()); 
  }

  h_EP_true->Write(); 
  fileout.Close();


}
