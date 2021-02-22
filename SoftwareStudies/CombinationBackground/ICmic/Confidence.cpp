#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <vector>

std::vector<int> getTrackType(int nv){
  int trlong = 0, trshort = 0, long3 =0, long2 =0, long1 =0, long0=0;
  if (nhit1->at(nv) <= 4) trshort += 1;
  else trlong += 1;
  if (nhit2->at(nv) <= 4) trshort += 1;
  else trlong += 1;
  if (nhit3->at(nv) <= 4) trshort += 1;
  else trlong += 1;
  if ((trlong + trshort) == 3  ) long0 += 1;
  if (trlong >0) long1 += 1;
  if (trlong >1) long2 += 1;
  if (trlong >2) long3 += 1;
  std::vector<int> type;
  type.push_back(long0);
  type.push_back(long1);
  type.push_back(long2);
  type.push_back(long3);
  return type;
}


void VertexAnalysis(){
  TFile *f = new TFile("/hepstore/agroves/MyStudies/SoftwareStudies/ICmicStudies/RootFiles/ICmic.root","READ");
  TTree *t1 = (TTree*)f->Get("t1");
  TFile fileout("../RootFiles/Confidence.root","RECREATE");

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
  double emass = 0.51099895;

  vector<double> *tv_1=0,*tv_2=0,*tv_3=0;
  vector<double> *tv_mc1=0,*tv_mc2=0,*tv_mc3=0;
  vector<double> *t0_fb1=0,*t0_fb2=0,*t0_fb3=0;
  vector<double> *t0_mc1=0,*t0_mc2=0,*t0_mc3=0;
  vector<double> *t0_tl1=0,*t0_tl2=0,*t0_tl3=0;

  t1->SetBranchAddress("tv_1",&tv_1);
  t1->SetBranchAddress("tv_2",&tv_2);
  t1->SetBranchAddress("tv_3",&tv_3);
  t1->SetBranchAddress("tv_mc1",&tv_mc1);
  t1->SetBranchAddress("tv_mc2",&tv_mc2);
  t1->SetBranchAddress("tv_mc3",&tv_mc3);
  t1->SetBranchAddress("t0_fb1",&t0_fb1);
  t1->SetBranchAddress("t0_fb2",&t0_fb2);
  t1->SetBranchAddress("t0_fb3",&t0_fb3);
  t1->SetBranchAddress("t0_tl1",&t0_tl1);
  t1->SetBranchAddress("t0_tl2",&t0_tl2);
  t1->SetBranchAddress("t0_tl3",&t0_tl3);
  t1->SetBranchAddress("t0_mc1",&t0_mc1);
  t1->SetBranchAddress("t0_mc2",&t0_mc2);
  t1->SetBranchAddress("t0_mc3",&t0_mc3);
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
  t1->SetBranchAddress("true_cx1",&true_cx1);
  t1->SetBranchAddress("true_cy1",&true_cy1);
  t1->SetBranchAddress("true_cz1",&true_cz1);
  t1->SetBranchAddress("true_cx2",&true_cx2);
  t1->SetBranchAddress("true_cy2",&true_cy2);
  t1->SetBranchAddress("true_cz2",&true_cz2);
  t1->SetBranchAddress("true_cx3",&true_cx3);
  t1->SetBranchAddress("true_cy3",&true_cy3);
  t1->SetBranchAddress("true_cz3",&true_cz3);
  t1->SetBranchAddress("targetdist",&targetdist);
  t1->SetBranchAddress("r1",&r1);
  t1->SetBranchAddress("r2",&r2);
  t1->SetBranchAddress("r3",&r3);
  t1->SetBranchAddress("rerr21",&rerr21);
  t1->SetBranchAddress("rerr22",&rerr22);
  t1->SetBranchAddress("rerr23",&rerr23);

  TH1F *h_weight = new TH1F("h_weight", "Weight", 200,0,6e6);


  double weightSum=0, weightSum2=0;

  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    t1->GetEntry(i);
    
    for (int nv=0; nv<(int)nvert;nv++){
      std::vector<int> numTrack( getTrackType(nv) );
      if (numTrack[3] == 1) {
	weightSum += weight;
	weightSum2 += weight*weight;



      }


    }



  }





    



  fileout.Close();
}
