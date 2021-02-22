#include "TRandom3.h"
#include "TH1D.h"
#include "TMath.h"
#include "TFile.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include <iostream>

void test(){
  double me = 0.511;
  double pol=0.95;
  double EMAX=53;
  double pmax = 52.7;
  TRandom3 generator;

  double EMASS = 0.511;
  double EMMU = 105.66;
  TH1F *h_pt = new TH1F("h_pt","h_pt",1000,0,60);
  TH1F *h_p = new TH1F("h_p","h_p",1000,0,60);
  TH1F *h_E = new TH1F("h_E","h_E",1000,0,60);
  TH1F *h_theta = new TH1F("h_costheta","h_costheta",500,-1.2,1.2);

  long long int n=10000000;


  double weightT=0;
  double count1=0;
  double count2=0;

  TFile fileout("output.root", "recreate");


  double michel_rho   = 0.75; //Standard Model Michel rho
  double michel_delta = 0.75; //Standard Model Michel delta
  double michel_xsi   = 1.00; //Standard Model Michel xsi
  double michel_eta   = 0.00; //Standard Model eta
   
  double rndm, x, ctheta;
  double FG; 
  double FG_max = 2.00;
   
  double W_mue  = (EMMU*EMMU+EMASS*EMASS)/(2.*EMMU);
  double x0     =           EMASS/W_mue;
   
  double x0_squared = x0*x0;


  for(long long int i = 0; i < n; i++){
       
    // Sample the positron energy by sampling from F
     
    x = x0 + generator.Rndm()*(1.-x0);
   
     
    ctheta = 2.*generator.Rndm()-1.;
    double energy = x * W_mue;
    double phi = TMath::Pi() * generator.Rndm();
      
    // calculate daughter momentum
    double daughtermomentum[3];
   
    double p = std::sqrt(energy*energy - EMASS*EMASS);
   
    double stheta = std::sqrt(1.-ctheta*ctheta);
    double cphi = std::cos(phi);
    double sphi = std::sin(phi);
   
    //Coordinates of the decay positron with respect to the muon spin
   
    double px = stheta*cphi;
    double py = stheta*sphi;
    double pz = ctheta;
    TLorentzVector michelpositron(px, py, pz, energy);

    double x1=energy/EMAX;
    double weight = x1*x1*((3-2*x1) + 0.95*ctheta*(1-2*x1));
    weightT+=weight;
    if(fabs(py/pz)<0.8) count1 += weight;
    //if(TMath::Cos(michelpositron.Theta()) > -0.8 && TMath::Cos(michelpositron.Theta()) < 0.8) count1 += weight;
    //if(michelpositron.E() > 10) count1 += weight;
    if(michelpositron.Pt() > 10) count2 += weight;

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
  std::cout<<"Weight total "<<weightT<<std::endl;
  std::cout<<"Angle and Energy "<<count1<<" Fraction "<<count1/weightT<<std::endl;
  std::cout<<"Pt "<<count2<<" Fraction "<<count2/weightT<<std::endl;
}
