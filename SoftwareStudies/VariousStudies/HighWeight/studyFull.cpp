#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>




void test1(){
  TFile *f = new TFile("/hepstore/agroves/MyStudies/SoftwareStudies/ICmicStudies/RootFiles/ICmic.root","READ");///hepstore/agroves/mu3e_42/mu3e/run/normalweight.root
  TTree *tree = (TTree*)f->Get("vertex");
  TFile fileout("fullsim_chi.root","RECREATE");
 
  vector<double> *px1=0,*py1=0,*pz1=0;
  vector<double> *px2=0,*py2=0,*pz2=0;
  vector<double> *px3=0,*py3=0,*pz3=0;
  vector<int> *pid1=0,*pid2=0,*pid3=0;
  vector<double> *chi2=0;
  double weight;
  u_int nvert;
  tree->SetBranchAddress("nvert",&nvert);
  tree->SetBranchAddress("px1",&px1);
  tree->SetBranchAddress("px2",&px2);
  tree->SetBranchAddress("px3",&px3);
  tree->SetBranchAddress("py1",&py1);
  tree->SetBranchAddress("py2",&py2);
  tree->SetBranchAddress("py3",&py3);
  tree->SetBranchAddress("pz1",&pz1);
  tree->SetBranchAddress("pz2",&pz2);
  tree->SetBranchAddress("pz3",&pz3);
  // tree->SetBranchAddress("pid1",&pid1);
  // tree->SetBranchAddress("pid2",&pid2);
  // tree->SetBranchAddress("pid3",&pid3);
  tree->SetBranchAddress("chi2",&chi2);
  tree->SetBranchAddress("weight",&weight);


  TH1F *h_weight = new TH1F("h_weight", "Weight",1e4 ,0,13e9);
  TH1F *h_angleE1E2 = new TH1F("h_angleE1E2", "Angle 1",500 ,0,5);
  TH1F *h_angleE2E3 = new TH1F("h_angleE2E3", "Angle 2",500 ,0,5);
  TH1F *h_angleE1E3 = new TH1F("h_angleE1E3", "Angle 3",500 ,0,5);

  TH1F *h_Emumu3e = new TH1F("h_Emumu3e", "mu E mu", 1000,0,200);

  TH1F *h_massmu3e = new TH1F("h_massmu3e", "Mass mu3e", 1000,0,200);
  TH1F *h_tmommu3e = new TH1F("h_tmommu3e", "Absolute momentum mu3e", 1000,0,100);
  TH1F *h_Emu3e = new TH1F("h_Emu3e", "E mu3e", 1000,0,100);
  TH1F *h_muEmu3e = new TH1F("h_muEmu3e", "Emu mu3e", 1000,-100,100);

  TH1F *h_tmome1 = new TH1F("h_tmome1", "Absolute momentum e1", 1000,0,100);
  TH1F *h_tmome2 = new TH1F("h_tmome2", "Absolute momentum e2", 1000,0,100);
  TH1F *h_tmome3 = new TH1F("h_tmome3", "Absolute momentum e3", 1000,0,100);

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
    for( int i=0; i<(int)nvert ; i++){
      e1.SetPxPyPzE(px1->at(i),py1->at(i),pz1->at(i),TMath::Sqrt(emass*emass+(px1->at(i)*px1->at(i)+py1->at(i)*py1->at(i)+pz1->at(i)*pz1->at(i))));
      e2.SetPxPyPzE(px2->at(i),py2->at(i),pz2->at(i),TMath::Sqrt(emass*emass+(px2->at(i)*px2->at(i)+py2->at(i)*py2->at(i)+pz2->at(i)*pz2->at(i))));
      e3.SetPxPyPzE(px3->at(i),py3->at(i),pz3->at(i),TMath::Sqrt(emass*emass+(px3->at(i)*px3->at(i)+py3->at(i)*py3->at(i)+pz3->at(i)*pz3->at(i))));

      mu3e = e1+e2+e3;

      if (chi2->at(i) < 200 ){
	h_weight->Fill(weight);
    
	h_massmu3e->Fill(mu3e.M());
	h_tmommu3e->Fill(mu3e.P());
	h_Emu3e->Fill(mu3e.E());
	h_Emumu3e->Fill(mu3e.E()/mu3e.M());
	h_muEmu3e->Fill(mu3e.M()-mu3e.E());
      }
    }

    // h_tmome1 ->Fill(e1.P());
    // h_tmome2 ->Fill(e2.P());
    // h_tmome3->Fill(e3.P());
    // h_angleE1E2->Fill(e2p.Angle(e1p));
    // h_angleE1E3->Fill(e3p.Angle(e1p));
    // h_angleE2E3->Fill(e2p.Angle(e3p));



  }


  h_weight->Write();
  // h_angleE1E2->Write();
  // h_angleE2E3->Write();
  // h_angleE1E3->Write();
  h_muEmu3e->Write();
  h_massmu3e->Write();
  h_tmommu3e->Write();
  h_Emu3e->Write();
  h_Emumu3e->Write();
  // h_tmome1 ->Write();
  // h_tmome2 ->Write();
  // h_tmome3->Write();


  fileout.Close();

}
