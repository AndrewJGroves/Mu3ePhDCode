#define sigAna_cxx
#include "sigAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include "TMath.h"
#include "TTree.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom3.h"
#include "TPad.h"
#include <algorithm>
#include "TLorentzVector.h"
#include "TF1.h"
#include <iomanip>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <set> 
#include <random>
#include <algorithm>
#include "Math/SpecFunc.h"
#include "Math/DistFunc.h"
static inline double computeSquare (double x) { return x*x; }

struct VtxChi2{
  double chi2;
  int vert;
};

bool sortChi2(const VtxChi2 &lhs, const VtxChi2 &rhs){return lhs.chi2 < rhs.chi2;}

void sigAna::setOutputFileName(TString fin) {
  if (fin=="") { 
    _fileoutname="./output_def.root";
    std::cout << "Setting output file to default name " 
	      << _fileoutname << std::endl;
    return;
  } 
  std::cout << "Requested output file name to " << fin << std::endl;
  _fileoutname=fin;
}

std::vector<double> sigAna::circle(double px,double py,double verx, double very, double rad){
  double u [2] ={1.0,0.0};
  if (px != 0){ 
    double pyOpx = py/px;
    double norm = 1/sqrt(1+pyOpx*pyOpx);
    u[0] = -norm*pyOpx;
    u[1] =  norm;
  }
  double cen_x = verx + rad*u[0];
  double cen_y = very + rad*u[1];
  std::vector<double> cir;
  cir.push_back(cen_x);
  cir.push_back(cen_y);
  return cir;
}

bool sigAna::hasTrueVertexInAcceptance(){
  for (int n=0; n<(int)nvert;n++){
    double true_r = sqrt( ((*true_vx)[n]*(*true_vx)[n])  + ((*true_vy)[n]*(*true_vy)[n]));
    if (true_r < 20 && abs(true_vz->at(n)) < 50) return true;
  }
  return false;
}

bool sigAna::hasVertexInAcceptance(){
  vector<double> vx2(vx->size());
  vector<double> vy2(vy->size());
  vector<double> vza(vz->size());
  vector<double> v2(vx->size());
  vector<double> r(vy->size());
  std::transform(vx->begin(), vx->end(), vx2.begin(), computeSquare);
  std::transform(vy->begin(), vy->end(), vy2.begin(), computeSquare);
  std::transform(vy2.begin(), vy2.end(), vx2.begin(), v2.begin(), std::plus<double>());
  std::transform(v2.begin(), v2.end(), r.begin(),(double(*)(double)) sqrt);
  std::transform(vz->begin(), vz->end(), vza.begin(),static_cast<double (*)(double)>(&std::abs));
  auto it = std::find_if(r.begin(), r.end(), [](int i){return i < 20;});
  //std::cout<<*it<<endl;
  while (it != std::end(r)) {
    if(vza[std::distance(std::begin(r), it)] < 50) return true;
    it = std::find_if(std::next(it), std::end(r), [](int i){return i < 20;});
  }
  return false;
}

bool sigAna::hasPhoMic(int p){
  for (int n=0; n<(int)nvert;n++){
    int type1p = (*type1)[n];
    int type2p = (*type2)[n];
    int type3p = (*type3)[n];
    int ty = getTrack(n);
    //if (ty != 2 && ty !=17) std::cout<<ty<<std::endl;
    int sum = type1p+type2p+type3p;
    if(ty == 16){
      if(p==1){
	std::cout<<type1p<<" "<<px1->at(n)<<" "<<py1->at(n)<<" "<<pz1->at(n)<<std::endl;
	std::cout<<type2p<<" "<<px2->at(n)<<" "<<py2->at(n)<<" "<<pz2->at(n)<<std::endl;
	std::cout<<type3p<<" "<<px3->at(n)<<" "<<py3->at(n)<<" "<<pz3->at(n)<<std::endl;
	std::cout<<" "<<std::endl;
      }
      return true;
    }
  }
  return false;
}

bool sigAna::trackComparison(TVector3 p1,TVector3 p2,double r1,double r2){ 
  TVector3 v1(p1[0], p1[1],p1[2]);
  TVector3 v2(p2[0], p2[1],p2[2]);
  double angle = v2.Angle(v1);
  if (angle == 0) return false;
  if (r1*r2 > 0){ // same sign tracks
    if (angle < 0.14) return false; }
  if (r1*r2 < 0){ // opposite sign tracks
    if (angle > 3.0) return false; }
  return true;
}

bool sigAna::checkVertexConsistency(int n1){ 
  TVector3 v1((*px1)[n1],(*py1)[n1],(*pz1)[n1]);
  TVector3 v2((*px2)[n1],(*py2)[n1],(*pz2)[n1]);
  TVector3 v3((*px3)[n1],(*py3)[n1],(*pz3)[n1]);
  bool a= trackComparison(v1,v2,(*r1)[n1],  (*r2)[n1]);
  bool b= trackComparison(v1,v3,(*r1)[n1],  (*r3)[n1]);
  bool c= trackComparison(v2,v3,(*r2)[n1],  (*r3)[n1]);
  if (!a)  return false;
  if (!b) return false;    
  if (!c) return false;
  return true;
}

std::vector<int> sigAna::getTrackType(int nv){
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

int sigAna::getGoodTrack(int nv){
  int common =0;
  if (id1->at(nv) == 0 || id2->at(nv) == 0 || id3->at(nv) == 0){ common +=1; }
  if (id1->at(nv) == id2->at(nv) || id1->at(nv) == id3->at(nv) || id2->at(nv) == id3->at(nv)){ common += 1; }
  return common;
}

int sigAna::getNTracksCommon(int a [],int b []){
  int common_tracks=0;
  if (a[0] == b[0] || a[1] == b[1] || a[2] == b[2]){ common_tracks +=3; }
  return common_tracks;
}

bool sigAna::trackComparison2(TVector3 v1,TVector3 v2,double r1,double r2){
  TVector3 p1(v1[0], v1[1],v1[2]);
  TVector3 p2(v2[0], v2[1],v2[2]);
  double angle = p2.Angle(p1);
  if (angle == 0) return false;
  if (r1*r2 > 0 && abs(p1.Mag() - p2.Mag()) < 1){ // same sign tracks
    if (angle < 0.14){
      return true;
    }
  }
  if (r1*r2 < 0){ // opposite sign tracks
    if (angle > 3.0){
      return true; 
    }
  }
  return false;

}
int sigAna::VtxTrackComparison(int n1,int n2){
  int tid1[] = {(*id1)[n1],(*id2)[n1],(*id3)[n1]};
  int tid2[3]={};
  if (n2 !=n1) {
    tid2[0] = (*id1)[n2];
    tid2[1] = (*id2)[n2];
    tid2[2] = (*id3)[n2];
  }
  int common( getNTracksCommon(tid1,tid2) );
  if (common == 3) return common;
  return -1;
}

double sigAna::VtxDistance(int n1,int n2){
  //std::cout<<"1 "<<(*vx)[n1]<<" "<<(*vy)[n1]<<" "<<(*vz)[n1]<<std::endl;
  //std::cout<<"2 "<<(*vx)[n2]<<" "<<(*vy)[n2]<<" "<<(*vz)[n2]<<std::endl;
  double a = ((*vx)[n1] - (*vx)[n2])*((*vx)[n1] - (*vx)[n2]);
  double b = ((*vy)[n1] - (*vy)[n2])*((*vy)[n1] - (*vy)[n2]);
  double c = ((*vz)[n1] - (*vz)[n2])*((*vz)[n1] - (*vz)[n2]);
  double x = TMath::Sqrt(a+b+c);
  return x; 
}

int sigAna::countTracks(int n, int i){
  int f1 = 10*i;
  int f2 = 10*i + 9;
  int counter_case=0;
  if ((*type1)[n] >= f1 && (*type1)[n] <= f2) counter_case += 1;
  if ((*type2)[n] >= f1 && (*type2)[n] <= f2) counter_case += 1;
  if ((*type3)[n] >= f1 && (*type3)[n] <= f2) counter_case += 1;
  return counter_case;
}

int sigAna::getTrack(int nv){
  int count_mic = countTracks(nv,1);
  int count_rad = countTracks(nv,2);
  int count_int = countTracks(nv, 3);
  int count_pho = countTracks(nv,4);
  int count_bhab = countTracks(nv,5);
  int count_brem = countTracks(nv,6);
  int count_posAnn = countTracks(nv,7);
  int count_comp = countTracks(nv,8);
  int count_sig = countTracks(nv,9);
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

void sigAna::Loop(int cut)
{
  if (fChain == 0) return;
  TH1::SetDefaultSumw2();
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  //TFile fileout("/user/agroves/Software/MyStudies/Plots/RootFiles/icmic_15mill.root", "recreate");
  TFile fileout(_fileoutname, "recreate");

  //---------------------------counters 

  double emass = 0.51099895;

  double c_1vtx =0, c_trueVtxAccp = 0, c_VtxAccp = 0, c_sameTrack = 0, c_commonTracks = 0, c_vtxTovtx=0;
  double vtx1_c5[4] = {0}, vtx2_c5[4] = {0}, vtx3_c5[4] = {0};
  double totVtx_c5[3]={0};
  double c_chi2=0, c_tDis=0,c_pm=0, c_mass=0;
  double vtx1_c6[4] = {0}, vtx2_c6[4] = {0}, vtx3_c6[4] = {0};
  double totVtx_c6[3]={0};
  double vtx1_c7[4] = {0}, vtx2_c7[4] = {0}, vtx3_c7[4] = {0};
  double totVtx_c7[3]={0};
  double vtx1_c72 = 0 ;
  int combiR[16] = {0};
  int icmicR[16] = {0};
  int nframedev[16] ={0};

  unsigned long long int nframesweight1 = 0;
  long double weightsum = 0;
  long double weightsumcor = 0;
  long double weightsum2 = 0;
  double count_int=0;
  int count_mic=0, count_rad=0, count_pho=0, count_bhab=0,  count_brem=0, count_posAnn=0, count_comp=0,  count_sig=0;
  int int2mic1=0, int1mic2=0, pho1=0, brem1=0, posAnn1=0, comp1=0, other=0; 
  int tot_IC=0, tot_mic=0, tot_pho = 0, tot_com = 0 ;
  int ic_2=0;
  int countPhoMStart=0,countPhoM=0;
  int countDiffPho=0,countSamePho=0;
  int countPhoMic=0;

  int maxVert = 0;
  unsigned long long int nmic=0;
  int nic1=0,nic2=0,nic3=0;
  int hit6=0, hit8=0;
  //-----------------------Histograms
  TH1F *h_mass = new TH1F("h_mass", "Mass", 1000,0,200);
  TH1F *h_chi2 = new TH1F("h_chi2", "Chi2", 1000,0,100);
  TH1F *h_target = new TH1F("h_target", "Distance to target", 2000,-100,100);
  TH1F *h_tmom = new TH1F("h_tmom", "Absolute momentum", 1000,0,100);
  TH1F *h_Pt = new TH1F("h_Pt", "Transverse momentum", 1000,0,100);

  TH1F *h_Emic = new TH1F("h_Emic", "Emic", 1000,0,200);
  TH1F *h_Pmic = new TH1F("h_Pmic", "Pmic", 1000,0,200);
  TH1F *h_Mmic = new TH1F("h_Mmic", "Mmic", 1000,0,200);

  TH1F *h_MPho = new TH1F("h_MPho", "MPho", 1000,0,200);

  TH1F *h_massP = new TH1F("h_massP", "MassP", 1000,0,200);
  TH1F *h_EPho = new TH1F("h_EPho", "EPho", 1000,0,200);
  TH1F *h_EP = new TH1F("h_EP", "EP", 1000,0,200);
  TH1F *h_EPgr20 = new TH1F("h_EPg20", "EPg20", 1000,0,200);
  TH1F *h_EPl20 = new TH1F("h_EPl20", "EPl20", 1000,0,200);
  TH1F *h_PhoPl20 = new TH1F("h_PhoPl20", "PhoPl20", 1000,0,200);
  TH1F *h_PhoPtl20 = new TH1F("h_PhoPtl20", "PhoPtl20", 1000,0,200);
  TH1F *h_PhoPgr20 = new TH1F("h_PhoPl20", "PhoPl20", 1000,0,200);
  TH1F *h_PhoPtgr20 = new TH1F("h_PhoPtl20", "PhoPtl20", 1000,0,200);

  TH1F *h_EPt = new TH1F("h_EPt", "EPt", 1000,0,200);
  TH1F *h_EP_true = new TH1F("h_EPt_true", "EPt true", 1000,0,200);
  TH1F *h_EPho_true = new TH1F("h_EPhoTrue", "EPho True", 1000,0,200);
  TH2F *h_PmMass = new TH2F("h_PmMass", "Momentum Vs Mass", 1000,0,200,1000,0,40);
  TH2F *h_xy = new TH2F("h_xy", "x Vs y", 1000,-25,25,1000,-25,25);
  TH2F *h_rz = new TH2F("h_zr", "z Vs r", 1000,-80,80,500,0,25);
  TH2F *h_rzRec = new TH2F("h_zrRec", "z Vs r Rec", 1000,-80,80,500,0,25);
  TH1F *h_xPho = new TH1F("h_xPho", "xPho", 1000,-100,100);
  TH1F *h_yPho = new TH1F("h_yPho", "yPho", 1000,-100,100);
  TH1F *h_zPho = new TH1F("h_zPho", "zPho", 1050,-100,150);

  TH2F *h_PEpho= new TH2F("h_PEpho", "PEpho", 1000,0,200,1000,0,100);

  // ------ save also a TTree with vertex information in the file
  // ---------------------------------------------------------------
  bool saveTree = true; // option not to save it if you do not need it
  bool timing = false;
  TTree t1("t1","Tree for the information");
  Int_t           v_run;
  Int_t           v_event;
  Int_t          v_nvert;
  Double_t        v_weight;
  std::vector<double> v_vx, v_vy, v_vz;
  std::vector<double> * v0_vx = &v_vx;
  std::vector<double>  *v0_vy = &v_vy;
  std::vector<double>  *v0_vz = &v_vz;
  std::vector<double> v_chi2;
  std::vector<double>  *v0_chi2 = &v_chi2;
  std::vector<double> v_px1,v_py1,v_pz1;
  std::vector<double>  *v0_px1 = &v_px1;
  std::vector<double>  *v0_py1 = &v_py1;
  std::vector<double>  *v0_pz1 = &v_pz1;
  std::vector<double> v_true_px1,v_true_py1,v_true_pz1;
  std::vector<double>  *v0_true_px1 = &v_true_px1;
  std::vector<double>  *v0_true_py1 = &v_true_py1;
  std::vector<double>  *v0_true_pz1 = &v_true_pz1;
  std::vector<double> v_true_cx1,v_true_cy1,v_true_cz1;
  std::vector<double>  *v0_true_cx1 = &v_true_cx1;
  std::vector<double>  *v0_true_cy1 = &v_true_cy1;
  std::vector<double>  *v0_true_cz1 = &v_true_cz1;
  std::vector<double> v_true_cx2,v_true_cy2,v_true_cz2;
  std::vector<double>  *v0_true_cx2 = &v_true_cx2;
  std::vector<double>  *v0_true_cy2 = &v_true_cy2;
  std::vector<double>  *v0_true_cz2 = &v_true_cz2;
  std::vector<double> v_true_cx3,v_true_cy3,v_true_cz3;
  std::vector<double>  *v0_true_cx3 = &v_true_cx3;
  std::vector<double>  *v0_true_cy3 = &v_true_cy3;
  std::vector<double>  *v0_true_cz3 = &v_true_cz3;
  std::vector<int> v_type1;
  std::vector<int>     *v0_type1 = &v_type1;
  std::vector<double> v_px2,v_py2,v_pz2;
  std::vector<double>  *v0_px2 = &v_px2;
  std::vector<double>  *v0_py2 = &v_py2;
  std::vector<double>  *v0_pz2 = &v_pz2;
  std::vector<double> v_true_px2,v_true_py2,v_true_pz2;
  std::vector<double>  *v0_true_px2 = &v_true_px2;
  std::vector<double>  *v0_true_py2 = &v_true_py2;
  std::vector<double>  *v0_true_pz2 = &v_true_pz2;
  std::vector<int> v_type2;
  std::vector<int>     *v0_type2 = &v_type2;
  std::vector<double> v_px3,v_py3,v_pz3;
  std::vector<double>  *v0_px3 = &v_px3;
  std::vector<double>  *v0_py3 = &v_py3;
  std::vector<double>  *v0_pz3 = &v_pz3;
  std::vector<double> v_true_px3,v_true_py3,v_true_pz3;
  std::vector<double>  *v0_true_px3 = &v_true_px3;
  std::vector<double>  *v0_true_py3 = &v_true_py3;
  std::vector<double>  *v0_true_pz3 = &v_true_pz3;
  std::vector<int> v_type3;
  std::vector<int>     *v0_type3 = &v_type3;
  std::vector<double> v_nhit1,v_nhit2,v_nhit3;
  std::vector<double> *v0_nhit1 = &v_nhit1;
  std::vector<double> *v0_nhit2 = &v_nhit2;
  std::vector<double> *v0_nhit3 = &v_nhit3;
  std::vector<double> v_targetdist;
  std::vector<double> *v0_targetdist = &v_targetdist;
  std::vector<double>  v_t0_fb1,  v_t0_fb2, v_t0_fb3, v_t0_tl1, v_t0_tl2, v_t0_tl3, v_t0_mc1, v_t0_mc2, v_t0_mc3;
  std::vector<double>  v_tv_1, v_tv_2, v_tv_3,v_tv_mc1, v_tv_mc2, v_tv_mc3;
  std::vector<double>  *v0_t0_fb1 = &v_t0_fb1;
  std::vector<double>  *v0_t0_fb2 = &v_t0_fb2;
  std::vector<double>  *v0_t0_fb3 = &v_t0_fb3;
  std::vector<double>  *v0_t0_tl1 = &v_t0_tl1;
  std::vector<double>  *v0_t0_tl2 = &v_t0_tl2;
  std::vector<double>  *v0_t0_tl3 = &v_t0_tl3;
  std::vector<double>  *v0_t0_mc1 = &v_t0_mc1;
  std::vector<double>  *v0_t0_mc2 = &v_t0_mc2;
  std::vector<double>  *v0_t0_mc3 = &v_t0_mc3;
  std::vector<double>  *v0_tv_1 = &v_tv_1;
  std::vector<double>  *v0_tv_2= &v_tv_2;
  std::vector<double>  *v0_tv_3= &v_tv_3;
  std::vector<double>  *v0_tv_mc1= &v_tv_mc1;
  std::vector<double>  *v0_tv_mc2= &v_tv_mc2;
  std::vector<double>  *v0_tv_mc3= &v_tv_mc3;
  
  std::vector<int> v_mid1,v_mid2,v_mid3;
  std::vector<int>     *v0_mid1 = &v_mid1;
  std::vector<int>     *v0_mid2 = &v_mid2;
  std::vector<int>     *v0_mid3 = &v_mid3;
  std::vector<int> v_id1,v_id2,v_id3;
  std::vector<int>     *v0_id1 = &v_id1;
  std::vector<int>     *v0_id2 = &v_id2;
  std::vector<int>     *v0_id3 = &v_id3;

  if (saveTree) {
    t1.Branch("run",&v_run,"v_run/I");
    t1.Branch("event",&v_event,"v_event/I");
    t1.Branch("nvert",&v_nvert, "v_nvert/I");
    t1.Branch("weight",&v_weight,"v_weight/D");
    t1.Branch("vx","vector<double> " ,&v_vx);
    t1.Branch("vy","vector<double> " ,&v_vy);
    t1.Branch("vz","vector<double> " ,&v_vz);
    t1.Branch("chi2","vector<double> " ,&v_chi2);
    t1.Branch("px1","vector<double> " ,&v_px1);
    t1.Branch("py1","vector<double> " ,&v_py1);
    t1.Branch("pz1","vector<double> " ,&v_pz1);
    t1.Branch("true_px1","vector<double> " ,&v_true_px1);
    t1.Branch("true_py1","vector<double> " ,&v_true_py1);
    t1.Branch("true_pz1","vector<double> " ,&v_true_pz1);
    t1.Branch("true_cx1","vector<double> " ,&v_true_cx1);
    t1.Branch("true_cy1","vector<double> " ,&v_true_cy1);
    t1.Branch("true_cz1","vector<double> " ,&v_true_cz1);
    t1.Branch("true_cx2","vector<double>",  &v_true_cx2);
    t1.Branch("true_cy2","vector<double>",  &v_true_cy2);
    t1.Branch("true_cz2","vector<double>",  &v_true_cz2);
    t1.Branch("true_cx3","vector<double>",  &v_true_cx3);
    t1.Branch("true_cy3","vector<double>",  &v_true_cy3);
    t1.Branch("true_cz3","vector<double>",  &v_true_cz3);
    t1.Branch("type1","vector<int>    " ,&v_type1);
    t1.Branch("px2","vector<double>"  ,&v_px2);
    t1.Branch("py2","vector<double>",  &v_py2);
    t1.Branch("pz2","vector<double>",  &v_pz2);
    t1.Branch("true_px2","vector<double> ", &v_true_px2);
    t1.Branch("true_py2","vector<double>",  &v_true_py2);
    t1.Branch("true_pz2","vector<double>",  &v_true_pz2);
    t1.Branch("type2","vector<int>",     &v_type2);
    t1.Branch("px3","vector<double>",  &v_px3);
    t1.Branch("py3","vector<double>",  &v_py3);
    t1.Branch("pz3","vector<double>",  &v_pz3);
    t1.Branch("true_px3","vector<double>",  &v_true_px3);
    t1.Branch("true_py3","vector<double>",  &v_true_py3);
    t1.Branch("true_pz3","vector<double>",  &v_true_pz3);
    t1.Branch("type3","vector<int>",&v_type3);
    t1.Branch("mid1","vector<int>",&v_mid1);
    t1.Branch("mid2","vector<int>",&v_mid2);
    t1.Branch("mid3","vector<int>",&v_mid3);
    t1.Branch("id1","vector<int>",&v_id1);
    t1.Branch("id2","vector<int>",&v_id2);
    t1.Branch("id3","vector<int>",&v_id3);
    t1.Branch("nhit1","vector<double>",&v_nhit1);
    t1.Branch("nhit2","vector<double>",&v_nhit2);
    t1.Branch("nhit3","vector<double>",&v_nhit3);
    t1.Branch("targetdist","vector<double>",&v_targetdist);
    if(timing){
      t1.Branch("t0_fb1","vector<double>",&v_t0_fb1);
      t1.Branch("t0_fb2","vector<double>",&v_t0_fb2);
      t1.Branch("t0_fb3","vector<double>",&v_t0_fb3);
      t1.Branch("t0_tl1","vector<double>",&v_t0_tl1);
      t1.Branch("t0_tl2","vector<double>",&v_t0_tl2);
      t1.Branch("t0_tl3","vector<double>",&v_t0_tl3);
      t1.Branch("t0_mc1","vector<double>",&v_t0_mc1);
      t1.Branch("t0_mc2","vector<double>",&v_t0_mc2);
      t1.Branch("t0_mc3","vector<double>",&v_t0_mc3);
      t1.Branch("tv_1","vector<double>",&v_tv_1);
      t1.Branch("tv_2","vector<double>",&v_tv_2);
      t1.Branch("tv_3","vector<double>",&v_tv_3);
      t1.Branch("tv_mc1","vector<double>",&v_tv_mc1);
      t1.Branch("tv_mc2","vector<double>",&v_tv_mc2);
      t1.Branch("tv_mc3","vector<double>",&v_tv_mc3);
    }
  }

  std::cout<<"Total entries "<<nentries<<std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (jentry % 50000 == 0) std::cout << "Entry " << jentry << std::endl;
    if (ientry < 0) break;
    if (jentry > cut and cut>0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // Code to find the sum of the weights - same implamentation from mu3eAnaWeightSum
    if(weight==1.0) nframesweight1++;
    double y = weight - weightsumcor;
    double t = weightsum + y;
    weightsumcor = (t-weightsum) -y;
    weightsum= t;
    weightsum2 += (weight*weight);

    //Checking if the decay happens within the target region
    if (nvert >= 1) { c_1vtx +=weight  ; }
    else { continue; };
    if (hasVertexInAcceptance()) { c_trueVtxAccp += weight; }
    else { continue; }

    //Finds all verticies clusters and only keep the best chi2 one
    std::vector<int> iv_new;
    if (nvert > 1){
      vector<VtxChi2> chitest(nvert);
      std::vector<double> chi;
      double chitemp[nvert][2];
      for (int i=0;i<(int)nvert;i++){
	chitest[i].vert=i;
	chitest[i].chi2=chi2->at(i);
	//chitemp[i][1]=i;
	//	chitemp[i][0]=chi2->at(i);
      }     
      std::sort(chitest.begin(),chitest.end(),sortChi2);
      // for (int k = 0; k < (int)nvert; k++){
      // 	for( int p = k+1; p < (int)nvert; p++){
      // 	  if( chitemp[k][0] > chitemp[p][0]){
      // 	    swap(chitemp[k][0], chitemp[p][0]);
      // 	    swap(chitemp[k][1], chitemp[p][1]);
      // 	  }
      // 	}
      // }
      double DCUT = 0.8;
      for (int k = 0; k < (int)nvert; k++){
	if( chitest[k].vert == -10000 ) continue;
	iv_new.push_back(chitest[k].vert);
	for (int p = k+1; p < (int)nvert; p++){
	  if( chitest[p].vert == 10000 ) continue;
	  double d=VtxDistance(chitest[k].vert,chitest[p].vert);
	  if( d < DCUT ){
	    chitest[p].vert = -10000;
	  }	  
	}
      }

    }
    else {std::iota(std::begin(iv_new),std::end(iv_new),0); }
    c_vtxTovtx += weight ;


    if (saveTree) {
      v0_vx->clear();
      v0_vy->clear();
      v0_vz->clear();
      v0_chi2->clear();
      v0_px1->clear();
      v0_py1->clear();
      v0_pz1->clear();
      v0_true_px1->clear();
      v0_true_py1->clear();
      v0_true_pz1->clear();
      v0_true_cx1->clear();
      v0_true_cy1->clear();
      v0_true_cz1->clear();
      v0_true_cx2->clear();
      v0_true_cy2->clear();
      v0_true_cz2->clear();
      v0_true_cx3->clear();
      v0_true_cy3->clear();
      v0_true_cz3->clear();
      v0_type1->clear();
      v0_px2->clear();
      v0_py2->clear();
      v0_pz2->clear();
      v0_true_px2->clear();
      v0_true_py2->clear();
      v0_true_pz2->clear();
      v0_type2->clear();
      v0_px3->clear();
      v0_py3->clear();
      v0_pz3->clear();
      v0_true_px3->clear();
      v0_true_py3->clear();
      v0_true_pz3->clear();
      v0_type3->clear();
      v0_mid1->clear();
      v0_mid2->clear();
      v0_mid3->clear();
      v0_id1->clear();
      v0_id2->clear();
      v0_id3->clear();
      v0_nhit1->clear();
      v0_nhit2->clear();
      v0_nhit3->clear();
      v0_targetdist->clear();
      if(timing){
	v0_t0_fb1->clear();
	v0_t0_fb2->clear();
	v0_t0_fb3->clear();
	v0_t0_tl1->clear();
	v0_t0_tl2->clear();
	v0_t0_tl3->clear();
	v0_t0_mc1->clear();
	v0_t0_mc2->clear();
	v0_t0_mc3->clear();
	v0_tv_1->clear(); 
	v0_tv_2->clear();
	v0_tv_3->clear();
	v0_tv_mc1->clear();
	v0_tv_mc2->clear();
	v0_tv_mc3->clear();
      }
    }

    int long0=0,long1=0,long2=0,long3=0;
    int c7long0 = 0, c7long1 = 0, c7long2 = 0, c7long3 = 0, nvert_c7=0;
    int flong0 = 0, flong1 = 0, flong2 = 0, flong3 = 0, nvert_tot=0;
    int filong0 = 0, filong1 = 0, filong2 = 0, filong3 = 0, tot=0;
    int icmic = 0;
    int count = 0;
    int nvPast=0;
    int sameTrack =0;
    int nvert_ovl=0;
    for (const int& nv : iv_new){
      if (!checkVertexConsistency(nv)) continue;
      sameTrack += 1;
      if( sameTrack == 1) c_sameTrack += weight ;
      int trackType = getTrack(nv);
      if (trackType != 16) continue;
      countPhoMic += 1;
      std::vector<int> numTrack( getTrackType(nv) );
      if (numTrack[0] ==1 ) long0 +=1 ;
      if (numTrack[1] ==1 ) long1 +=1 ;
      if (numTrack[2] ==1 ) long2 +=1 ;
      if (numTrack[3] ==1 ) long3 +=1 ;
      nvert_ovl += 1;

      TLorentzVector el1;
      TLorentzVector el2;
      TLorentzVector el3;
      TLorentzVector mu;
      el1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))+0.511*0.511);
      el2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))+0.511*0.511);
      el3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))+0.511*0.511);
      mu=el1+el2+el3;

      TLorentzVector tel1;
      TLorentzVector tel2;
      TLorentzVector tel3;
      TLorentzVector tmu;
      tel1.SetPxPyPzE(true_px1->at(nv),true_py1->at(nv),true_pz1->at(nv),TMath::Sqrt(true_px1->at(nv)*true_px1->at(nv)+true_py1->at(nv)*true_py1->at(nv)+true_pz1->at(nv)*true_pz1->at(nv))+0.511*0.511);
      tel2.SetPxPyPzE(true_px2->at(nv),true_py2->at(nv),true_pz2->at(nv),TMath::Sqrt(true_px2->at(nv)*true_px2->at(nv)+true_py2->at(nv)*true_py2->at(nv)+true_pz2->at(nv)*true_pz2->at(nv))+0.511*0.511);
      tel3.SetPxPyPzE(true_px3->at(nv),true_py3->at(nv),true_pz3->at(nv),TMath::Sqrt(true_px3->at(nv)*true_px3->at(nv)+true_py3->at(nv)*true_py3->at(nv)+true_pz3->at(nv)*true_pz3->at(nv))+0.511*0.511);
      tmu=tel1+tel2+tel3;
      
      h_chi2->Fill((*chi2)[nv],weight);
      if (abs(chi2->at(nv)) > 45 ){ continue; }

    if (saveTree){
      if(timing){
	v0_t0_fb1->push_back(t0_fb1->at(nv));
	v0_t0_fb2->push_back(t0_fb2->at(nv));
	v0_t0_fb3->push_back(t0_fb3->at(nv));
	v0_t0_tl1->push_back(t0_tl1->at(nv));
	v0_t0_tl2->push_back(t0_tl2->at(nv));
	v0_t0_tl3->push_back(t0_tl3->at(nv));
	v0_t0_mc1->push_back(t0_mc1->at(nv));
	v0_t0_mc2->push_back(t0_mc2->at(nv));
	v0_t0_mc3->push_back(t0_mc3->at(nv));
	v0_tv_1-> push_back(tv_1->at(nv));
	v0_tv_2->push_back(tv_2->at(nv));
	v0_tv_3->push_back(tv_3->at(nv));
	v0_tv_mc1->push_back(tv_mc1->at(nv));
	v0_tv_mc2->push_back(tv_mc2->at(nv));
	v0_tv_mc3->push_back(tv_mc3->at(nv));
      }
      v0_vx->push_back(vx->at(nv));
      v0_vy->push_back(vy->at(nv));
      v0_vz->push_back(vz->at(nv));
      v0_chi2->push_back(chi2->at(nv));
      v0_px1->push_back(px1->at(nv));
      v0_py1->push_back(py1->at(nv));
      v0_pz1->push_back(pz1->at(nv));
      v0_true_px1->push_back(true_px1->at(nv));
      v0_true_py1->push_back(true_py1->at(nv));
      v0_true_pz1->push_back(true_pz1->at(nv));
      v0_true_cx1->push_back(true_cx1->at(nv));
      v0_true_cy1->push_back(true_cy1->at(nv));
      v0_true_cz1->push_back(true_cz1->at(nv));
      v0_true_cx2->push_back(true_cx2->at(nv));
      v0_true_cy2->push_back(true_cy2->at(nv));
      v0_true_cz2->push_back(true_cz2->at(nv));
      v0_true_cx3->push_back(true_cx3->at(nv));
      v0_true_cy3->push_back(true_cy3->at(nv));
      v0_true_cz3->push_back(true_cz3->at(nv));
      v0_type1->push_back(type1->at(nv));
      v0_px2->push_back(px2->at(nv));
      v0_py2->push_back(py2->at(nv));
      v0_pz2->push_back(pz2->at(nv));
      v0_true_px2->push_back(true_px2->at(nv));
      v0_true_py2->push_back(true_py2->at(nv));
      v0_true_pz2->push_back(true_pz2->at(nv));
      v0_type2->push_back(type2->at(nv));
      v0_px3->push_back(px3->at(nv));
      v0_py3->push_back(py3->at(nv));
      v0_pz3->push_back(pz3->at(nv));
      v0_true_px3->push_back(true_px3->at(nv));
      v0_true_py3->push_back(true_py3->at(nv));
      v0_true_pz3->push_back(true_pz3->at(nv));
      v0_type3->push_back(type3->at(nv));
      v0_mid1->push_back(mid1->at(nv));
      v0_mid2->push_back(mid2->at(nv));
      v0_mid3->push_back(mid3->at(nv));
      v0_id1->push_back(id1->at(nv));
      v0_id2->push_back(id2->at(nv));
      v0_id3->push_back(id3->at(nv));
      v0_nhit1->push_back(nhit1->at(nv));
      v0_nhit2->push_back(nhit2->at(nv));
      v0_nhit3->push_back(nhit3->at(nv));
      v0_targetdist->push_back(targetdist->at(nv));
      v_weight = weight;
      v_event = event;
      v_run = run;
      v_nvert = iv_new.size();
      t1.Fill();
    }

      if (abs(chi2->at(nv)) > 30 ){ continue; }
      c_chi2 += weight;


	TLorentzVector ep1;
	TLorentzVector ep2;
	TLorentzVector ep3;
	TLorentzVector ep1True;
	TLorentzVector ep2True;
	TLorentzVector ep3True;
	ep1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(TMath::Sqrt(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))+0.511*0.511));
	ep2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(TMath::Sqrt(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))+0.511*0.511));
	ep3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(TMath::Sqrt(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))+0.511*0.511));
	ep1True.SetPxPyPzE(true_px1->at(nv),true_py1->at(nv),true_pz1->at(nv),TMath::Sqrt(TMath::Sqrt(true_px1->at(nv)*true_px1->at(nv)+true_py1->at(nv)*true_py1->at(nv)+true_pz1->at(nv)*true_pz1->at(nv))+0.511*0.511));
	ep2True.SetPxPyPzE(true_px2->at(nv),true_py2->at(nv),true_pz2->at(nv),TMath::Sqrt(TMath::Sqrt(true_px2->at(nv)*true_px2->at(nv)+true_py2->at(nv)*true_py2->at(nv)+true_pz2->at(nv)*true_pz2->at(nv))+0.511*0.511));
	ep3True.SetPxPyPzE(true_px3->at(nv),true_py3->at(nv),true_pz3->at(nv),TMath::Sqrt(TMath::Sqrt(true_px3->at(nv)*true_px3->at(nv)+true_py3->at(nv)*true_py3->at(nv)+true_pz3->at(nv)*true_pz3->at(nv))+0.511*0.511));
	TLorentzVector pho;
	TLorentzVector phoTrue;
	int first = 0;
	int second = 0;
	if(mid1->at(nv)==mid2->at(nv)){
	  if ( (type1->at(nv) == 41 || type1->at(nv) == 42) && (type2->at(nv) == 41 || type2->at(nv) == 42)){
	    pho=ep1+ep2;
	    phoTrue=ep1True+ep2True;
	    first=+1;
	  }
	}
	if(mid1->at(nv)==mid3->at(nv)){
	  if ( (type1->at(nv) == 41 || type1->at(nv) == 42) && (type3->at(nv) == 41 || type3->at(nv) == 42)){
	    pho=ep1+ep3;
	    phoTrue=ep1True+ep3True;
	    first=+1;

	  }
	}
	if(mid2->at(nv)==mid3->at(nv)){
	  if ( (type2->at(nv) == 41 || type2->at(nv) == 42) && (type3->at(nv) == 41 || type3->at(nv) == 42)){
	    pho=ep2+ep3;
	    phoTrue=ep2True+ep3True;
	    second=+1;

	  }
	}

	h_EPho->Fill(pho.E());
	h_EP->Fill(pho.P());
	h_EPt->Fill(pho.Pt());
	h_EP_true->Fill(phoTrue.P());
	h_EPho_true->Fill(phoTrue.E());
	h_PEpho->Fill(pho.P(),(*pm)[nv]);

      h_target->Fill((*targetdist)[nv],weight);
      if (abs(targetdist->at(nv)) > 3){ continue; }
      c_tDis += weight;

	if(TMath::Sqrt(true_cx1->at(nv)*true_cx1->at(nv)+true_cy1->at(nv)*true_cy1->at(nv)) >= 20){ 
	  h_EPgr20->Fill(pho.E());
	  h_PhoPgr20->Fill(pho.P());
	  h_PhoPtgr20->Fill(pho.Pt());
	}
	if(TMath::Sqrt(true_cx1->at(nv)*true_cx1->at(nv)+true_cy1->at(nv)*true_cy1->at(nv)) < 20){
	  h_EPl20->Fill(pho.E());
	  h_PhoPl20->Fill(pho.P());
	  h_PhoPtl20->Fill(pho.Pt());
	}

	if( first == 1){
	  h_xy->Fill(true_cx1->at(nv),true_cy1->at(nv));
	  h_rz->Fill(true_cz1->at(nv),TMath::Sqrt(true_cx1->at(nv)*true_cx1->at(nv)+true_cy1->at(nv)*true_cy1->at(nv)));
	  h_rzRec->Fill(vz->at(nv),TMath::Sqrt(vx->at(nv)*vx->at(nv)+vy->at(nv)*vy->at(nv)));
	  h_xPho->Fill(vx->at(nv)-true_cx1->at(nv));
	  h_yPho->Fill(vy->at(nv)-true_cy1->at(nv));
	  h_zPho->Fill(vz->at(nv)-true_cz1->at(nv));
	} else if(second == 1){
	  h_xy->Fill(true_cx2->at(nv),true_cy2->at(nv));
	  h_rz->Fill(true_cz2->at(nv),TMath::Sqrt(true_cx2->at(nv)*true_cx2->at(nv)+true_cy2->at(nv)*true_cy2->at(nv)));
	  h_rzRec->Fill(vz->at(nv),TMath::Sqrt(vx->at(nv)*vx->at(nv)+vy->at(nv)*vy->at(nv)));
	  h_xPho->Fill(vx->at(nv)-true_cx2->at(nv));
	  h_yPho->Fill(vy->at(nv)-true_cy2->at(nv));
	  h_zPho->Fill(vz->at(nv)-true_cz2->at(nv));
	}
	  
      
    
    if(type1->at(nv) == 11){
      h_Emic->Fill(el1.E()); 
      h_Pmic->Fill(el1.P());
    }
    if(type2->at(nv) == 11){
      h_Emic->Fill(el2.E()); 
      h_Pmic->Fill(el2.P());
    }
    if(type3->at(nv) == 11){
      h_Emic->Fill(el3.E()); 
      h_Pmic->Fill(el3.P());
    }





      h_massP->Fill((*mmass)[nv],weight);
      if (numTrack[0] ==1 ) flong0 +=1 ;
      if (numTrack[1] ==1 ) flong1 +=1 ;
      if (numTrack[2] ==1 ) flong2 +=1 ;
      if (numTrack[3] ==1 ) flong3 +=1 ;
      nvert_tot += 1;
      h_Pt->Fill(mu.Pt());

      // std::cout << "Entry " << jentry << std::endl;
      //  std::cout<<"Hit number "<<nhit1->at(nv)<<" "<<nhit2->at(nv)<<" "<<nhit3->at(nv)<<std::endl;
      //  std::cout<<"Type "<<type1->at(nv)<<" "<<type2->at(nv)<<" "<<type3->at(nv)<<std::endl;
      //  std::cout<<"Id "<<id1->at(nv)<<" "<<id2->at(nv)<<" "<<id3->at(nv)<<std::endl;
      //  std::cout<<"Vertex location "<<vx->at(nv)<<" "<<vy->at(nv)<<" "<<vz->at(nv)<<std::endl;
      //  std::cout<<"Momentum 1 "<<px1->at(nv)<<" "<<py1->at(nv)<<" "<<pz1->at(nv)<<std::endl;
      //  std::cout<<"Momentum 2 "<<px2->at(nv)<<" "<<py2->at(nv)<<" "<<pz2->at(nv)<<std::endl;
      //  std::cout<<"Momentum 3 "<<px3->at(nv)<<" "<<py3->at(nv)<<" "<<pz3->at(nv)<<std::endl;
      //  std::cout<<"1 "<<true_cx1->at(nv)<<" "<<true_cy1->at(nv)<<" "<<true_cz1->at(nv)<<std::endl;
      //  std::cout<<"2 "<<true_cx2->at(nv)<<" "<<true_cy2->at(nv)<<" "<<true_cz2->at(nv)<<std::endl;
      //  std::cout<<"3 "<<true_cx3->at(nv)<<" "<<true_cy3->at(nv)<<" "<<true_cz3->at(nv)<<std::endl;
      //  std::cout<<"r1 "<<TMath::Sqrt(true_cx1->at(nv)*true_cx1->at(nv)+true_cy1->at(nv)*true_cy1->at(nv))<<std::endl;
      //  std::cout<<"r2 "<<TMath::Sqrt(true_cx2->at(nv)*true_cx2->at(nv)+true_cy2->at(nv)*true_cy2->at(nv))<<std::endl;
      //  std::cout<<"r3 "<<TMath::Sqrt(true_cx3->at(nv)*true_cx3->at(nv)+true_cy3->at(nv)*true_cy3->at(nv))<<std::endl;

      h_PmMass->Fill((*mmass)[nv],(*pm)[nv],weight);

    h_tmom->Fill((*pm)[nv],weight);
    if (pm->at(nv) > 8){ continue; }
    c_pm += weight;

    if (numTrack[3] == 1) {
      h_mass->Fill((*mmass)[nv],weight);
    }

    if(mmass->at(nv) >= 103.5 && mmass->at(nv) <= 115){
      c_mass+=weight;
      nvert_c7 += 1;
      if (numTrack[0] ==1 ) c7long0 +=1 ;
      if (numTrack[1] ==1 ) c7long1 +=1 ;
      if (numTrack[2] ==1 ) c7long2 +=1 ;
      if (numTrack[3] ==1 ) c7long3 +=1 ;
    } 

  }

  if (nvert_ovl == 1 ){
    if (long0 ==1) { vtx1_c5[0] += weight; }
    if (long1 ==1) vtx1_c5[1] += weight;
    if (long2 ==1) vtx1_c5[2] += weight;
    if (long3 ==1) vtx1_c5[3] += weight;
  }   
  if (nvert_ovl == 2 ){
    if (long0 ==2) vtx2_c5[0] += weight;
    if (long1 ==2) vtx2_c5[1] += weight;
    if (long2 ==2) vtx2_c5[2] += weight;
    if (long3 ==2) vtx2_c5[3] += weight;
  }     
  if (nvert_ovl >= 3 ){
    if (long0==nvert_ovl) vtx3_c5[0] += weight;
    if (long1 ==nvert_ovl) vtx3_c5[1] +=weight;
    if (long2 ==nvert_ovl) vtx3_c5[2] += weight;
    if (long3 ==nvert_ovl) vtx3_c5[3] += weight;
  }
  if (nvert_ovl ==1 ) totVtx_c5[0] +=weight;
  if (nvert_ovl ==2 ) totVtx_c5[1] +=weight;         
  if (nvert_ovl >=3 ) totVtx_c5[2] +=weight;

  if (nvert_tot ==1 ) totVtx_c6[0] +=weight;
  if (nvert_tot ==2 ) totVtx_c6[1] +=weight;     
  if (nvert_tot >=3 ) totVtx_c6[2] +=weight;

  if (nvert_tot == 1 ){
    if (flong0 ==1) { vtx1_c6[0] += weight; }
    if (flong1 ==1) vtx1_c6[1] += weight;
    if (flong2 ==1) vtx1_c6[2] += weight;
    if (flong3 ==1) vtx1_c6[3] += weight;
  }   
  if (nvert_tot == 2 ){
    if (flong0 ==2) vtx2_c6[0] += weight;
    if (flong1 ==2) vtx2_c6[1] += weight;
    if (flong2 ==2) vtx2_c6[2] += weight;
    if (flong3 ==2) vtx2_c6[3] += weight;
  }
  if (nvert_tot >= 3 ){
    if (flong0 ==nvert_tot) vtx3_c6[0] += weight;
    if (flong1 ==nvert_tot) vtx3_c6[1] += weight;
    if (flong2 ==nvert_tot) vtx3_c6[2] += weight;
    if (flong3 ==nvert_tot) vtx3_c6[3] += weight;
  }

  if (nvert_c7 ==1 ) totVtx_c7[0] +=weight;
  if (nvert_c7 ==2 ) totVtx_c7[1] +=weight;     
  if (nvert_c7 >=3 ) totVtx_c7[2] +=weight;

  if (nvert_c7 == 1 ){
    if (c7long0 ==1) { vtx1_c7[0] += weight; }
    if (c7long1 ==1) vtx1_c7[1] += weight;
    if (c7long2 ==1) vtx1_c7[2] += weight;
    if (c7long3 ==1) vtx1_c7[3] += weight;
  }   
  if (nvert_c7 == 2 ){
    if (c7long0 ==2) vtx2_c7[0] += weight;
    if (c7long1 ==2) vtx2_c7[1] += weight;
    if (c7long2 ==2) vtx2_c7[2] += weight;
    if (c7long3 ==2) vtx2_c7[3] += weight;
  }
  if (nvert_c7 >= 3 ){
    if (c7long0 ==nvert_c7) vtx3_c7[0] += weight;
    if (c7long1 ==nvert_c7) vtx3_c7[1] += weight;
    if (c7long2 ==nvert_c7) vtx3_c7[2] += weight;
    if (c7long3 ==nvert_c7) vtx3_c7[3] += weight;
  }

}

    
  

if (saveTree) {
  t1.Write();
 }
h_chi2->Write();
h_target->Write();
h_tmom->Write();
h_Pt->Write();
h_mass->Write();
h_PmMass->Write();
h_EPho_true->Write();
h_EP_true->Write();
h_massP->Write();
h_EPho->Write();
h_EP->Write();
h_Mmic->Write();
h_MPho->Write();
h_EPt->Write();
h_xy->Write();
h_rz->Write();
h_rzRec->Write();
h_xPho->Write();
h_yPho->Write();
h_zPho->Write();
h_EPgr20->Write(); 
h_EPl20->Write(); 
h_PhoPl20->Write();
h_PhoPtl20->Write(); 
h_PhoPgr20->Write(); 
h_PhoPtgr20->Write();
h_Emic->Write();
h_Pmic->Write();
h_PEpho->Write();
std::cout<<"Max frame "<<maxVert<<std::endl;
double Nmuons = 0 ;
Nmuons=weightsum;
printf("Starting %d after %d\n",countPhoMStart,countPhoM);
printf("Combinations with same photon %d while not is %d \n",countSamePho,countDiffPho);
printf("\n");
printf("\\begin{table}[h] \n");
printf("\\begin{center} \n");
printf("\\caption{} \n");
printf("\\begin{tabular}{l r r r r} \n");
printf("\\hline \n");
printf("Cut &   & Efficiency & & \\\\ \n");
printf("\\hline \n");
printf("Generated Number of muon decays & %2.3e $\\pm$ %2.3e  & - && \\\\ \n",Nmuons,TMath::Sqrt(weightsum2));
printf("\\hline \n"); 
printf("Number of frames passing the following cuts:    &&&& \\\\ \n");
printf("(Cut \\#1) $\\geq$1 vertex  & %2.3e & %2.3f && \\\\ \n",c_1vtx,c_1vtx/Nmuons);
printf("(Cut \\#2) Recon vtx within acceptance  &  %2.3e  & %2.3f && \\\\ \n",c_trueVtxAccp,c_trueVtxAccp/Nmuons);
printf("(Cut \\#3) Duplicate removal (vtx-to-vtx distance) & %2.3e & %2.3f && \\\\ \n",c_vtxTovtx,c_vtxTovtx/Nmuons);
printf("(Cut \\#4) Duplicate removal (same tracks) & %2.3e  & %2.3f && \\\\ \n",c_sameTrack,c_sameTrack/Nmuons);
printf("(Cut \\#5) 2 Photon 1 Michel   & %2.3e & %2e && \\\\ \n",vtx1_c5[0]+vtx2_c5[0]+vtx3_c5[0],(vtx1_c5[0]+vtx2_c5[0]+vtx3_c5[0])/(float)Nmuons);
printf("\\hline \n"); 
printf("Break-up in different vertex track quality & Short or better & $\\geq$1 long & $\\geq$2 long & 3 long \\\\ \n");
printf("\\hline \n"); 
printf("frames with 1 vertex & %2.3e & %2.3e & %2.3e & %2.3e  \\\\ \n",vtx1_c5[0],vtx1_c5[1],vtx1_c5[2],vtx1_c5[3]);
printf("frames with 2 vertex & %2.3e & %2.3e & %2.3e & %2.3e  \\\\ \n",vtx2_c5[0],vtx2_c5[1],vtx2_c5[2],vtx2_c5[3]);
printf("frames $\\geq 3$ vertex & %2.3e & %2.3e & %2.3e & %2.3e  \\\\ \n",vtx3_c5[0],vtx3_c5[1],vtx3_c5[2],vtx3_c5[3]);
printf("\\hline \n"); 
printf("Total number of frames  & %2.3e &&& \\\\ \n",vtx1_c5[0]+vtx2_c5[0]+vtx3_c5[0]);
printf("Efficiency & %2e  & %2e & %2e & %2e \\\\ \n",(vtx1_c5[0]+vtx2_c5[0]+vtx3_c5[0])/(float)Nmuons,(vtx1_c5[1]+vtx2_c5[1]+vtx3_c5[1])/(float)Nmuons,(vtx1_c5[2]+vtx2_c5[2]+vtx3_c5[2])/(float)Nmuons,(vtx1_c5[3]+vtx2_c5[3]+vtx3_c5[3])/(float)Nmuons);
printf("\\hline \n");
printf("Number of vertices per frame classification  &  1 vertex   & 2 vertices & $\\geq$3 vertices & \\\\ \n");
printf("Number of frames  & %2.3e &  %2.3e & %2.3e & \\\\ \n",totVtx_c5[0],totVtx_c5[1],totVtx_c5[2]);  
printf("\\hline \n");
printf("\\hline \n");
printf("Cut \\# 6 details & No of Frames & Efficiency && \\\\ \n");
printf("\\hline \n");
printf(" $\\chi^2 < 30 $  & %2.3f & %2e && \\\\ \n",c_chi2,c_chi2/(float)Nmuons);
printf("vertex target distance $<$3~mm    & %2.3f & %2e && \\\\ \n",c_tDis,c_tDis/(float)Nmuons);
printf("3-track system momentum $<$8~MeV  & %2.3f & %2e && \\\\ \n",c_pm,c_pm/(float)Nmuons);
printf("\\hline \n");
printf("Break-up in different vertex track quality & Short or better & $\\geq$1 long & $\\geq$2 long & 3 long \\\\ \n");
printf("\\hline \n"); 
printf("frames with 1 vertex & %2.2e & %2.2e & %2.2e & %2.2e  \\\\ \n",vtx1_c6[0],vtx1_c6[1],vtx1_c6[2],vtx1_c6[3]);
printf("frames with 2 vertex & %2.2e & %2.2e & %2.2e & %2.2e  \\\\ \n",vtx2_c6[0],vtx2_c6[1],vtx2_c6[2],vtx2_c6[3]);
printf("frames $\\geq 3$ vertex & %2.0f & %2.0f & %2.0f & %2.0f  \\\\ \n",vtx3_c6[0],vtx3_c6[1],vtx3_c6[2],vtx3_c6[3]);
printf("\\hline \n"); 
printf("Total number of frames  & %2.2e &&& \\\\ \n",vtx1_c6[0]+vtx2_c6[0]+vtx3_c6[0]);
printf("Efficiency & %2e  & %2e & %2e & %2e \\\\ \n",(vtx1_c6[0]+vtx2_c6[0]+vtx3_c6[0])/(float)Nmuons,(vtx1_c6[1]+vtx2_c6[1]+vtx3_c6[1])/(float)Nmuons,(vtx1_c6[2]+vtx2_c6[2]+vtx3_c6[2])/(float)Nmuons,(vtx1_c6[3]+vtx2_c6[3]+vtx3_c6[3])/(float)Nmuons);
printf("\\hline \n");
printf("Number of vertices per frame classification  &  1 vertex   & 2 vertices & $\\geq$3 vertices & \\\\ \n");
printf("Number of frames  & %2.2e &  %2.2e & %2.2e  \\\\ \n",totVtx_c6[0],totVtx_c6[1],totVtx_c6[2]);
printf("Number of frame with both Photon conversion particles %2.2e \\\\ \n",countSamePho);
printf("\\hline \n");
printf("\\end{tabular} \n");
printf("\\end{center} \n");
printf("\\end{table} \n");


fileout.Close();
}
