#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <string>


int countTracks(int n, int i, int type1,int type2,int type3){
  int f1 = 10*i;
  int f2 = 10*i + 9;
  int counter_case=0;
  if (type1 >= f1 && type1 <= f2) counter_case += 1;
  if (type2 >= f1 && type2 <= f2) counter_case += 1;
  if (type3 >= f1 && type3 <= f2) counter_case += 1;
  return counter_case;
}

int getTrack(int nv, int type1,int type2,int type3){
  int count_mic = countTracks(nv,1,type1,type2,type3);
  int count_rad = countTracks(nv,2,type1,type2,type3);
  int count_int = countTracks(nv, 3,type1,type2,type3);
  int count_pho = countTracks(nv,4,type1,type2,type3);
  int count_bhab = countTracks(nv,5,type1,type2,type3);
  int count_brem = countTracks(nv,6,type1,type2,type3);
  int count_posAnn = countTracks(nv,7,type1,type2,type3);
  int count_comp = countTracks(nv,8,type1,type2,type3);
  int count_sig = countTracks(nv,9,type1,type2,type3);
  // if(count_pho == 2){
  //   std::cout<<"mi "<<count_mic<<std::endl;
  //   std::cout<<"ph "<<count_pho<<std::endl;
  // }
  if (count_sig == 3) return 1; 
  if (count_mic == 3) return 2;
  if (count_int == 3) return 3; 
  if (count_pho == 3) return 4;
  if (count_bhab == 3) return 5; 
  if (count_brem == 3) return 6;
  if (count_posAnn == 3) return 7; 
  if (count_comp == 3) return 8;
  if (count_int == 1 && count_mic == 2) return 9;
  if (count_int == 2 && count_mic == 1) return 10;
  //if (count_pho >=1) return 11;
  if (count_brem >=1) return 12;
  if (count_posAnn >=1) return 13;
  if (count_comp >=1) return 14;
  if (count_rad ==3) return 15;
  if (count_pho == 2 && count_mic == 1) return 16;
  if (count_pho == 2 && count_rad == 1) return 17;

  return 18;
}

void SkimTree(TString InName, TString OutName,TString SEED){
  TFile *f = new TFile(InName,"READ");
  TTree *t1 = (TTree*)f->Get("vertex");
 
  const auto n =t1->GetEntries();
 
  // Create a new file + a clone of old tree in new file
  TFile newfile(OutName, "recreate");
  TTree *testing =t1->CloneTree(0);

  UInt_t nvert;
  vector<double> *chi2=0;
  vector<int> *type1=0,*type2=0,*type3=0;
  Double_t weight;

  t1->SetBranchAddress("chi2",&chi2);
  t1->SetBranchAddress("type1",&type1);
  t1->SetBranchAddress("type2",&type2);
  t1->SetBranchAddress("type3",&type3);
  t1->SetBranchAddress("nvert", &nvert);  
  t1->SetBranchAddress("weight", &weight);   
 
  TH1F *h_chi2 = new TH1F("h_chi2", "Chi2", 1000,0,100);
  TH1F *h_weight = new TH1F("h_weight", "Weight", 100000,0,100e9);


  unsigned long long int nframesweight1 = 0;
  long double weightsum = 0;
  long double weightsumcor = 0;
  long double weightsum2 = 0;
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    t1->GetEntry(i);
    if(weight==1.0) nframesweight1++;
    double y = weight - weightsumcor;
    double t = weightsum + y;
    weightsumcor = (t-weightsum) -y;
    weightsum= t;
    weightsum2 += (weight*weight);

    for(int nv=0; nv<(int)nvert ; nv++){ 
      h_chi2->Fill((*chi2)[nv],weight);
      h_weight->Fill(weight);
      int trackType = getTrack(nv,type1->at(nv),type2->at(nv),type3->at(nv));
      if(chi2->at(nv) < 30 && trackType == 1) testing->Fill();
    }
  }

  ofstream myfile;
  //TString SE = std::string(1,SEED);
  //int b_size = sizeof(SEED) / sizeof(char); 
  //string SE = convertToString(SEED, b_size); 

 TString weFile = "WeightSum_"+SEED;
TString weiFile=weFile+".txt";
 myfile.open(weiFile);
  myfile << weightsum;
  myfile.close();
  //std::cout<<weightsum<<std::endl;
  //weightsum
  //weightsum2
  //h_weight->Write();
  //h_chi2->Write();
  //testing->Print();
  newfile.Write();
 
}
