#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>


void test1(){
  TFile *f = new TFile("/hepstore/agroves/mu3e_42/mu3e/run/data/boom.root","READ");
  TTree *t1 = (TTree*)f->Get("vertex");

  TFile fileout("plots.root","RECREATE");
  u_int nvert;
  vector<double> *true_vx=0,*true_vy=0,*true_vz=0;
  vector<double> *type1=0,*type2=0,*type3=0;
  vector<double> *vx=0,*vy=0,*vz=0;
  vector<int> *nhit1=0,*nhit2=0,*nhit3=0;

  t1->SetBranchAddress("true_vx",&true_vx);
  t1->SetBranchAddress("true_vy",&true_vy);
  t1->SetBranchAddress("true_vz",&true_vz);
  t1->SetBranchAddress("type1",&type1);
  t1->SetBranchAddress("type2",&type2);
  t1->SetBranchAddress("type3",&type3);
  t1->SetBranchAddress("vx",&vx);
  t1->SetBranchAddress("vy",&vy);
  t1->SetBranchAddress("vz",&vz);
  t1->SetBranchAddress("nhit1",&nhit1);
  t1->SetBranchAddress("nhit2",&nhit2);
  t1->SetBranchAddress("nhit3",&nhit3);
  t1->SetBranchAddress("nvert", &nvert);   

  int count_IC=0;
  int count_ICmic = 0;
  int count2 = 0;

  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    t1->GetEntry(i);

    count2 += (int)nvert;
    for(int p=0; p<(int)nvert ; p++){
      if (type1->at(p) == 31 && type2->at(p) == 31 && type3 ->at(p) == 32) count_IC += 1; 
      if ((type1->at(p) == 11 && type2->at(p) == 31 && type3 ->at(p) == 32) || (type1->at(p) == 31 && type2->at(p) == 11 && type3 ->at(p) == 32)){
	count_ICmic += 1;
	//if (true_vx->at(p) < 1000 || true_vy->at(p) < 1000 || true_vz->at(p) <1000){
	//count1 += 1;
	  //std::cout<<"true v "<< true_vx->at(p) << true_vy->at(p) << true_vz->at(p) << std::endl;
	  //std::cout<<"type "<< type1->at(p) << type2->at(p) << type3->at(p) << std::endl;

	}
      }
    }
  
  std::cout<<count2<<std::endl;
  std::cout<<"Total IC "<<count_IC<<std::endl;
  std::cout<<"Total IC mic "<<count_ICmic<<std::endl;

}
