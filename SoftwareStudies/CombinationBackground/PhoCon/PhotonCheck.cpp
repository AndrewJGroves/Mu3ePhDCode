#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>


void test(){
  TFile *f = new TFile("/hepstore/agroves/dev/mu3e/run/data/mu3e_run_000020.root","READ");
  TTree *t1 = (TTree*)f->Get("mu3e");

  TFile fileout("Plots20test.root","RECREATE");
  TH1::SetDefaultSumw2();

  int Ntrajectories;
  double weight;
  vector<double> *traj_px=0,*traj_py=0,*traj_pz=0;
  vector<double> *traj_type=0,*traj_mother=0,*traj_ID=0;
  vector<double> *traj_vx=0,*traj_vy=0,*traj_vz=0;

  t1->SetBranchAddress("traj_px",&traj_px);
  t1->SetBranchAddress("traj_pz",&traj_pz);
  t1->SetBranchAddress("traj_py",&traj_py);
  t1->SetBranchAddress("traj_vx",&traj_vx);
  t1->SetBranchAddress("traj_vz",&traj_vz);
  t1->SetBranchAddress("traj_vy",&traj_vy);
  t1->SetBranchAddress("traj_mother",&traj_mother);
  t1->SetBranchAddress("traj_ID",&traj_ID);
  t1->SetBranchAddress("traj_type",&traj_type);
  t1->SetBranchAddress("Ntrajectories", &Ntrajectories);
  t1->SetBranchAddress("weight", &weight);   


  double count20=0;
  double count41=0;

  TH1F *h_EP_true = new TH1F("h_EPt_true", "EPt true", 1000,0,200);
  TH1F *h_EP = new TH1F("h_EPt", "EPt", 1000,0,200);
  TH1F *h_EP_true2 = new TH1F("h_EPt_true2", "EPt true", 1000,0,200);
  TH1F *h_EP2 = new TH1F("h_EPt2", "EPt", 1000,0,200);
  double count = 0;
  double count40 = 0;
  TH1F *h_E = new TH1F("h_E", "E", 1000,0,200);
  TH1F *h_PhoTheta = new TH1F("h_PhoTheta", "PhoTheta", 100,-10,10);
  TH1F *h_PhoPhi = new TH1F("h_PhoPhi", "PhoPho", 100,-10,10);
  TH1F *h_ETheta = new TH1F("h_ETheta", "ETheta", 100,-10,10);
  TH1F *h_EPhi = new TH1F("h_EPhi", "EPho", 100,-10,10);
  TH1F *h_Reso = new TH1F("h_Reso", "Reso", 100,-10,10);

  TH1F *h_x = new TH1F("h_x", "x", 1000,-600,600);
  TH1F *h_y = new TH1F("h_y", "y", 1000,-600,600);
  TH1F *h_z = new TH1F("h_z", "z", 1000,-950,950);
  TH2F *h_rz= new TH2F("h_xyz", "xyz",1000,-950,950, 100000,0,600);

  TH2F *h_Pth= new TH2F("h_Pth", "Pth", 1000,0,200,100,-10,10);
  double counttar = 0;
  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    //if (i > 1e6) break;
    t1->GetEntry(i);

    TLorentzVector e1;
    TLorentzVector e2;
    TLorentzVector pho;
    TLorentzVector e;

    
    for(int nv=0;nv<Ntrajectories;nv++){
      double p = TMath::Sqrt(traj_px->at(nv)*traj_px->at(nv)+traj_py->at(nv)*traj_py->at(nv)+traj_pz->at(nv)*traj_pz->at(nv));
      if( traj_type->at(nv) == 21){   
	e.SetPxPyPzE(traj_px->at(nv),traj_py->at(nv),traj_pz->at(nv),TMath::Sqrt(traj_px->at(nv)*traj_px->at(nv)+traj_py->at(nv)*traj_py->at(nv)+traj_pz->at(nv)*traj_pz->at(nv))+0.511*0.511);
	h_E->Fill(p);
	h_ETheta->Fill(e.Theta());
	h_EPhi->Fill(e.Phi());
	count20+=1;
      }
      if(traj_type->at(nv) == 20){
	pho.SetPxPyPzE(traj_px->at(nv),traj_py->at(nv),traj_pz->at(nv),TMath::Sqrt(traj_px->at(nv)*traj_px->at(nv)+traj_py->at(nv)*traj_py->at(nv)+traj_pz->at(nv)*traj_pz->at(nv)));
	if( p >= 25)count += 1;
	if( p >= 40) count40 +=1;
	h_EP_true->Fill(p);
	h_PhoTheta->Fill(traj_py->at(nv)/traj_pz->at(nv));
	h_PhoPhi->Fill(pho.Phi());
    h_Pth->Fill(pho.P(),pho.Py()/pho.Pz());
      }
    }
    for(int nv=0;nv<Ntrajectories;nv++){
      int co = 0;
      if(traj_type->at(nv) == 41 ){
	count41+=1;
	double true_r = TMath::Sqrt( ((*traj_vx)[nv]*(*traj_vx)[nv])  + ((*traj_vy)[nv]*(*traj_vy)[nv]));
	if (true_r < 25 && abs(traj_vz->at(nv)) < 80) counttar+=1;
	h_x->Fill(traj_vx->at(nv));
	h_y->Fill(traj_vy->at(nv));
	h_z->Fill(traj_vz->at(nv));
	h_rz->Fill(traj_vz->at(nv),true_r);
	e1.SetPxPyPzE(traj_px->at(nv),traj_py->at(nv),traj_pz->at(nv),TMath::Sqrt(traj_px->at(nv)*traj_px->at(nv)+traj_py->at(nv)*traj_py->at(nv)+traj_pz->at(nv)*traj_pz->at(nv))+0.511*0.511);
	co+=1;
      }
      if(traj_type->at(nv) == 42 ){
	e2.SetPxPyPzE(traj_px->at(nv),traj_py->at(nv),traj_pz->at(nv),TMath::Sqrt(traj_px->at(nv)*traj_px->at(nv)+traj_py->at(nv)*traj_py->at(nv)+traj_pz->at(nv)*traj_pz->at(nv))+0.511*0.511);
      }
    }
    TLorentzVector Pho;
    Pho=e1+e2;
    h_EP->Fill(Pho.P());
    h_Reso->Fill(Pho.P()-pho.P());

  }
  std::cout<<"Radiative "<<count20<<" Electron con "<<count41<<std::endl;
 
  std::cout<<count<<" "<<count40<<" "<<count40/count<<std::endl;
  std::cout<<count<<" "<<counttar<<" "<<counttar/count<<std::endl;

  h_x->Write();
  h_y->Write();
  h_z->Write();
  h_rz->Write();
  h_EP_true->Write();
  h_EP->Write();
  h_EP_true2->Write();
  h_EP2->Write();
  h_E->Write();
  h_Reso->Write();
  h_Pth->Write();
  h_PhoTheta->Write();
  h_PhoPhi->Write();
  h_ETheta->Write();
  h_EPhi->Write();

  fileout.Close();


}
