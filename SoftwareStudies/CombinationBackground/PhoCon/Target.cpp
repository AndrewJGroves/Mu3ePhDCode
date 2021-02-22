#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include "TMath.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TGraph.h"
#include <algorithm>
#include "TF1.h"
#include <set> 
#include <random>
#include <algorithm>
#include "TCanvas.h"
#include "TPaveText.h"
#include "TH1.h"
#include "TF1.h"
#include "Math/GoFTest.h"
#include "Math/Functor.h"
#include "TRandom3.h"
#include "Math/DistFunc.h"

void test(){
  //gROOT->SetStyle("ATLAS");
  //gStyle->SetOptStat(0);
  TFile *f = new TFile("/hepstore/agroves/MyStudies/SoftwareStudies/ICmicStudies/RootFiles/Rad.root","READ");
  TTree *t1 = (TTree*)f->Get("t1");
  vector<double> *vx=0,*vy=0,*vz=0;

  t1->SetBranchAddress("vx",&vx);
  t1->SetBranchAddress("vy",&vy);
  t1->SetBranchAddress("vz",&vz);
  TH3F *h_tar = new TH3F("h_zrRec", "z Vs r Rec", 100,-80,80,100,-25,25,100,-25,25);

  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    t1->GetEntry(i);
    for(int nv =0; nv<(int)vx->size() ; nv++){
      h_tar->Fill(vx->at(nv),vy->at(nv),vz->at(nv));
    }

  }
  h_tar->Draw("COLZ");
}
