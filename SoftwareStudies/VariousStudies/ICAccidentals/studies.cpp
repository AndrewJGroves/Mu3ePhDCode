#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include "TRandom3.h"


void test(){
  TFile *f = new TFile("icmictruth.root","READ");
  TTree *t1 = (TTree*)f->Get("t1");

  TFile fileout("plots2020.root","RECREATE");

  double E_1michel,px_1michel,py_1michel,pz_1michel;
  double E_2michel,px_2michel,py_2michel,pz_2michel;
  double weight_1mic,weight_2mic;

  t1->SetBranchAddress("E_1michel",&E_1michel);
  t1->SetBranchAddress("px_1michel",&px_1michel);
  t1->SetBranchAddress("py_1michel",&py_1michel);
  t1->SetBranchAddress("pz_1michel",&pz_1michel);
  t1->SetBranchAddress("E_2michel",&E_2michel);
  t1->SetBranchAddress("px_2michel",&px_2michel);
  t1->SetBranchAddress("py_2michel",&py_2michel);
  t1->SetBranchAddress("pz_2michel",&pz_2michel);
  t1->SetBranchAddress("weight_1mic",&weight_1mic);
  t1->SetBranchAddress("weight_2mic",&weight_2mic);

  TH1F *mass1 = new TH1F("mass1","Mass 1 michel",100,75,120);
  TH1F *mom1 = new TH1F("mom1","Momentum 1 michel",100,0,11); 
  TH1F *mass2 = new TH1F("mass2","Mass 2 michel",100,75,120);
  TH1F *mom2 = new TH1F("mom2","Momentum 2 michel",100,0,11); 

  TH1F *mass1_mass95 = new TH1F("mass1_mass95","Mass 1 michel",100,95,110);
  TH1F *mom1_mass95 = new TH1F("mom1_mass95","Momentum 1 michel",100,0,11);
  TH1F *mass1_mom8 = new TH1F("mass1_mom8","Mass 1 michel",100,75,120); 
  TH1F *mom1_mom8 = new TH1F("mom1_mom8","Momentum 1 michel",100,0,11); 
  TH1F *mom1_mass95mom8 = new TH1F("mom1_mass95mom8","Momentum 1 michel",100,0,11); 
  TH1F *mass1_mass95mom8 = new TH1F("mass1_mass95mom8","Momentum 1 michel",100,95,110); 
  TH1F *mass1_mass95mom8L = new TH1F("mass1_mass95mom8L","Momentum 1 michel",100,95,103.5); 
  TH1F *mass1_mass95mom8M = new TH1F("mass1_mass95mom8M","Momentum 1 michel",100,103.5,115); 
  TH1F *mass1_mass95mom8H = new TH1F("mass1_mass95mom8H","Momentum 1 michel",100,115,200); 



  TH1F *mass2_mass95 = new TH1F("mass2_mass95","Mass 2 michel",100,95,110);
  TH1F *mom2_mass95 = new TH1F("mom2_mass95","Momentum 2 michel",100,0,11);
  TH1F *mass2_mom8 = new TH1F("mass2_mom8","Mass 2 michel",100,75,120); 
  TH1F *mom2_mom8 = new TH1F("mom2_mom8","Momentum 2 michel",100,0,11); 
  TH1F *mom2_mass95mom8 = new TH1F("mom2_mass95mom8","Momentum 2 michel",100,0,11); 
  TH1F *mass2_mass95mom8 = new TH1F("mass2_mass95mom8","Momentum 2 michel",100,95,110); 
  TH1F *mass2_mass95mom8L = new TH1F("mass2_mass95mom8L","Momentum 1 michel",100,95,103.5); 
  TH1F *mass2_mass95mom8M = new TH1F("mass2_mass95mom8M","Momentum 1 michel",100,103.5,115); 
  TH1F *mass2_mass95mom8H = new TH1F("mass2_mass95mom8H","Momentum 1 michel",100,115,200); 

  double mic1=0,mic2=0,mic1_mass95=0,mic1_mom8=0,mic2_mass95=0,mic2_mom8=0,mic1_mass95mom8=0,mic2_mass95mom8=0;
  double mic1SQ=0,mic2SQ=0,mic1_mass95SQ=0,mic1_mom8SQ=0,mic2_mass95SQ=0,mic2_mom8SQ=0,mic1_mass95mom8SQ=0,mic2_mass95mom8SQ=0;

  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000000 == 0) std::cout<<"Entry " << i << std::endl;
    if (i > 1000) break;
    t1->GetEntry(i);

    TRandom3 gen;
    gen.SetSeed(0);

    //TLorentzVector michel1(px_1michel+gen->Gaus(0,1),py_1michel+gen->Gaus(0,1),pz_1michel+gen->Gaus(0,1),E_1michel);
    //TLorentzVector michel2(px_2michel+gen->Gaus(0,1),py_2michel+gen->Gaus(0,1),pz_2michel+gen->Gaus(0,1),E_2michel);
    TLorentzVector michel1(px_1michel,py_1michel,pz_1michel,E_1michel);
    TLorentzVector michel2(px_2michel,py_2michel,pz_2michel,E_2michel);

    mic1 += weight_1mic;
    mic2 += weight_2mic;
    mic1SQ += (weight_1mic*weight_1mic);
    mic2SQ += (weight_2mic*weight_2mic);

    mass1->Fill(michel1.M(),weight_1mic);
    mom1->Fill(michel1.P(),weight_1mic);
    mass2->Fill(michel2.M(),weight_2mic);
    mom2->Fill(michel2.P(),weight_2mic);

    if(michel1.M() > 95){ 
      mass1_mass95->Fill(michel1.M(),weight_1mic); 
      mom1_mass95->Fill(michel1.P(),weight_1mic); 
      mic1_mass95 += weight_1mic;
      mic1_mass95SQ += (weight_1mic*weight_1mic);

    }
    if(michel1.P() < 8){
      mom1_mom8->Fill(michel1.P(),weight_1mic);
      mass1_mom8->Fill(michel1.M(),weight_1mic);
      mic1_mom8 += weight_1mic;
      mic1_mom8SQ += (weight_1mic*weight_1mic);
    }
    if(michel1.P() < 8 && michel1.M() > 95){
      mass1_mass95mom8->Fill(michel1.M(),weight_1mic); 
      mass1_mass95mom8L->Fill(michel1.M(),weight_1mic); 
      mass1_mass95mom8M->Fill(michel1.M(),weight_1mic); 
      mass1_mass95mom8H->Fill(michel1.M(),weight_1mic); 
      mom1_mass95mom8->Fill(michel1.P()); 
      mic1_mass95mom8 += weight_1mic;
      mic1_mass95mom8SQ += (weight_1mic*weight_1mic);
    }
    

    if(michel2.M() > 95){
      mass2_mass95->Fill(michel2.M(),weight_2mic);
      mom2_mass95->Fill(michel2.P(),weight_2mic);
      mic2_mass95 += weight_2mic;
      mic2_mass95SQ += (weight_2mic*weight_2mic);
    }
    if(michel2.P() < 8){
      mass2_mom8->Fill(michel2.M(),weight_2mic);
      mom2_mom8->Fill(michel2.P(),weight_2mic);
      mic2_mom8 += weight_2mic;
      mic2_mom8SQ += (weight_2mic*weight_2mic);
    }  
    if(michel2.P() < 8 && michel2.M() > 95){
      mass2_mass95mom8->Fill(michel2.M(),weight_2mic); 
      mass2_mass95mom8L->Fill(michel2.M(),weight_2mic); 
      mass2_mass95mom8M->Fill(michel2.M(),weight_2mic); 
      mass2_mass95mom8H->Fill(michel2.M(),weight_2mic); 
      mom2_mass95mom8->Fill(michel2.P()); 
      mic2_mass95mom8 += weight_2mic;
      mic2_mass95mom8SQ += (weight_2mic*weight_2mic);
    }

  }

  printf("Weight of michel 1 2 IC %37e +- %5e \n",mic1,TMath::Sqrt(mic1SQ));
  printf("After cuts \n");
  printf("Mass of > 95 MeV %43.3f +- %5f %10.3f  \n",mic1_mass95,mic1_mass95SQ,mic1_mass95/mic1);
  printf("Absolute Momentum of > 8 MeV/c %29.3f +- %5f %10.3f \n",mic1_mom8,mic1_mom8SQ,mic1_mom8/mic1);
  printf("Mass of > 95 MeV and Absolute Momentum of > 8 MeV/c  %3e +- %5e %10.3f\n",mic1_mass95mom8,TMath::Sqrt(mic1_mass95mom8SQ),mic1_mass95mom8/mic1);
  printf("----------------------------------------------------------------- \n");
  printf("Weight of michel 2 1 IC %37e +- %5e \n",mic2,TMath::Sqrt(mic2SQ));
  printf("After cuts \n");
  printf("Mass of > 95 MeV %43.3f +- %5f %10.3f  \n",mic2_mass95,mic2_mass95SQ,mic2_mass95/mic2);
  printf("Absolute Momentum of > 8 MeV/c %29.3f +- %5f %10.3f \n",mic2_mom8,mic2_mom8SQ,mic2_mom8/mic2);
  printf("Mass of > 95 MeV and Absolute Momentum of > 8 MeV/c  %3e +- %5e %10.3f\n",mic2_mass95mom8,TMath::Sqrt(mic2_mass95mom8SQ),mic2_mass95mom8/mic2);









  mass1->Write();
  mom1->Write();
  mass1_mass95->Write();
  mom1_mass95->Write();
  mom1_mom8->Write();
  mass1_mom8->Write();
  mass1_mass95mom8->Write();
  mass1_mass95mom8H->Write();
  mass1_mass95mom8L->Write();
  mass1_mass95mom8M->Write();
  mom1_mass95mom8->Write();

  mass2->Write();
  mom2->Write();
  mass2_mass95->Write();
  mom2_mass95->Write();
  mom2_mom8->Write();
  mass2_mom8->Write();
  mass2_mass95mom8->Write();
  mass2_mass95mom8H->Write();
  mass2_mass95mom8M->Write();
  mass2_mass95mom8L->Write();
  mom2_mass95mom8->Write();
  fileout.Close();


}
