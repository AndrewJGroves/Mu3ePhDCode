#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <vector>


void VertexAnalysis(){
  TFile *f = new TFile("/hepstore/agroves/MyStudies/SoftwareStudies/CombinationBackground/RootFiles/ICmic.root","READ");//test1.root","READ");
  TTree *t1 = (TTree*)f->Get("t1");
  //TFile fileout("../RootFiles/VertexPlots.root","RECREATE");

  double weight;
  int run,event,nvert;
  vector<int> *type1=0,*type2=0,*type3=0,*chi2=0;
  vector<double> *vx=0,*vy=0,*vz=0;
  vector<double> *nhit1=0,*nhit2=0,*nhit3=0;
  vector<double> *px1=0,*py1=0,*pz1=0;
  vector<double> *true_px1=0,*true_py1=0,*true_pz1=0;
  vector<double> *true_cx1=0,*true_cy1=0,*true_cz1=0;
  vector<double> *px2=0,*py2=0,*pz2=0;
  vector<double> *true_px2=0,*true_py2=0,*true_pz2=0;
  vector<double> *true_cx2=0,*true_cy2=0,*true_cz2=0;
  vector<double> *px3=0,*py3=0,*pz3=0;
  vector<double> *true_px3=0,*true_py3=0,*true_pz3=0;
  vector<double> *true_cx3=0,*true_cy3=0,*true_cz3=0;
  vector<double> *pxm=0,*pym=0,*pzm=0;
  vector<double> *mmass=0,*pm=0;
  vector<double> *targetdist=0,*true_targetdist=0,*guessdist=0,*cosalpha=0;
  vector<double> *nsharedhit1=0,*nsharedhit2=0,*nsharedhit3=0;
  vector<double> *nsharedseg1=0,*nsharedseg2=0,*nsharedseg3=0;
  vector<double> *r1=0,*r2=0,*r3=0;
  vector<double> *rerr21=0,*rerr22=0,*rerr23=0;
  TLorentzVector e1;
  TLorentzVector e2;
  TLorentzVector e3;
  TLorentzVector mu;

  double emass = 0.51099895;

  vector<double> *tv_1=0,*tv_2=0,*tv_3=0;
  vector<double> *tv_mc1=0,*tv_mc2=0,*tv_mc3=0;
  vector<double> *t0_fb1=0,*t0_fb2=0,*t0_fb3=0;
  vector<double> *t0_mc1=0,*t0_mc2=0,*t0_mc3=0;
  vector<double> *t0_tl1=0,*t0_tl2=0,*t0_tl3=0;

  t1->SetBranchAddress("nvert",&nvert);
  t1->SetBranchAddress("type1",&type1);
  t1->SetBranchAddress("type2",&type2);
  t1->SetBranchAddress("type3",&type3);
  t1->SetBranchAddress("vx",&vx);
  t1->SetBranchAddress("vy",&vy);
  t1->SetBranchAddress("vz",&vz);
  t1->SetBranchAddress("nhit1",&nhit1);
  t1->SetBranchAddress("nhit2",&nhit2);
  t1->SetBranchAddress("nhit3",&nhit3); 
  t1->SetBranchAddress("run",&run);
  t1->SetBranchAddress("event",&event);
  t1->SetBranchAddress("weight",&weight);
  t1->SetBranchAddress("chi2",&chi2);
  t1->SetBranchAddress("true_px1",&true_px1);
  t1->SetBranchAddress("true_py1",&true_py1);
  t1->SetBranchAddress("true_pz1",&true_pz1);
  t1->SetBranchAddress("true_px2",&true_px2);
  t1->SetBranchAddress("true_py2",&true_py2);
  t1->SetBranchAddress("true_pz2",&true_pz2);
  t1->SetBranchAddress("true_px3",&true_px3);
  t1->SetBranchAddress("true_py3",&true_py3);
  t1->SetBranchAddress("true_pz3",&true_pz3);
  t1->SetBranchAddress("px1",&px1);
  t1->SetBranchAddress("py1",&py1);
  t1->SetBranchAddress("pz1",&pz1);
  t1->SetBranchAddress("px2",&px2);
  t1->SetBranchAddress("py2",&py2);
  t1->SetBranchAddress("pz2",&pz2);
  t1->SetBranchAddress("px3",&px3);
  t1->SetBranchAddress("py3",&py3);
  t1->SetBranchAddress("pz3",&pz3);
  double weight2 =0;
  double weightsum=0;
  int count = 0 ;
  TRandom3 gen;
  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    t1->GetEntry(i);

    for( int nv=0; nv < (int)type1->size(); nv ++){
      e1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(emass*emass+(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))));
      e2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(emass*emass+(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))));
      e3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(emass*emass+(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))));
      mu=e1+e2+e3;

      if(mu.M() > 103 && mu.M() < 110){
	count += 1;
	std::cout<<"Mass "<<mu.M()<<" weight "<<weight<<std::endl;
	double x = weight*weight;
	weightsum += weight;
	weight2 += x;
      }




    }





  }
  std::cout<<count<<std::endl;
  double err = TMath::Sqrt(weight2);
  std::cout<<weightsum<<" "<<err<<std::endl;
  //fileout.Close();

}
