#include "TRandom3.h"
#include "TH1D.h"
#include "TMath.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <iostream>

void test(){
  double me = 0.511;
  double pol=0.95;
  double EMAX=53.0;
  double pmax = 52.7;
  TRandom3 generator;


  TH1F *h_pt = new TH1F("h_pt","h_pt",1000,0,60);
  TH1F *h_p = new TH1F("h_p","h_p",1000,0,60);
  TH1F *h_E = new TH1F("h_E","h_E",1000,0,60);
  TH1F *h_theta = new TH1F("h_costheta","h_costheta",500,-1.2,1.2);

  long long int n=100000000;


  double weightT=0;
  double count1=0;
  double count2=0;
  double count3=0;

  TFile fileout("RootFiles/MichelAcceptance.root", "recreate");

  for(long long int i = 0; i < n; i++){
    double ang = generator.Rndm()*2*TMath::Pi();
    double cos = TMath::Cos(ang);
    double x1 = (generator.Rndm() * EMAX)/EMAX;
    double phi1 = generator.Rndm()*2*M_PI;
    double p1 = pmax*x1;
    double weight = x1*x1*((3-2*x1) + pol*cos*(1-2*x1));
    weightT += weight;
    double sin1 = sqrt(1-cos*cos);
    TLorentzVector michelpositron(p1*sin(phi1)*sin1, p1*TMath::Cos(phi1)*sin1, p1*cos, sqrt(p1*p1+me*me));

    if(TMath::Cos(michelpositron.Theta()) > -0.8 && TMath::Cos(michelpositron.Theta()) < 0.8) count1 += weight;
    if(michelpositron.E() > 10) count2 += weight;
    if(michelpositron.Pt() > 10) count3 += weight;

    h_E->Fill(michelpositron.E(),weight);
    h_theta->Fill(TMath::Cos(michelpositron.Theta()),weight);
    h_p->Fill(michelpositron.P(),weight);
    h_pt->Fill(michelpositron.Pt(),weight);
  }
  h_E->Write();
  h_pt->Write();
  h_p->Write();
  h_theta->Write();
  fileout.Close();
  
  double xmin = 10.0/53.0;
  double IntAngTop=TMath::Pi()-2*TMath::ACos(0.8);
  double IntAng=(2*IntAngTop)/(2*TMath::Pi());
  double IntEnergyTop=1.5-(xmin*xmin*xmin*(xmin+2))*0.5;
  double IntEnergy=IntEnergyTop/1.5;

  std::cout<<"Weight total "<<weightT<<std::endl;
  std::cout<<"Angle  "<<count1<<" Fraction "<<count1/weightT<<" Comparison to Theory "<<IntAng<<std::endl;
  std::cout<<"Energy  "<<count2<<" Fraction "<<count2/weightT<<" Comparison to Theory "<<IntEnergy<<std::endl;
  std::cout<<"Pt "<<count3<<" Fraction "<<count3/weightT<<std::endl;
  double total=count1/weightT*count2/weightT*count3/weightT;
  std::cout<<"Total Acceptance effiency "<<total<<std::endl;
}
