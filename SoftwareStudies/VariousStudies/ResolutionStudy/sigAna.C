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
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom3.h"
#include "TPad.h"
#include <algorithm>
#include "TF1.h"
#include <iomanip>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <set> 
#include <random>
#include <algorithm>
#include "Math/SpecFunc.h"
#include "Math/DistFunc.h"
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

bool sigAna::hasTrueVertexInAcceptance(){
  for (int n=0; n<(int)nvert;n++){
    double true_r = sqrt( ((*true_vx)[n]*(*true_vx)[n])  + ((*true_vy)[n]*(*true_vy)[n]));
    if (true_r < 20 && abs(true_vz->at(n)) < 50) return true;
  }
  return false;
}

bool sigAna::hasVertexInAcceptance(){
  for (int n=0; n<(int)nvert;n++){
    double r = sqrt( ((*vx)[n]*(*vx)[n])  + ((*vy)[n]*(*vy)[n]));
    if (r < 20 && abs(vz->at(n)) < 50) return true;
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
  if (count_pho >=1) return 11;
  if (count_brem >=1) return 12;
  if (count_posAnn >=1) return 13;
  if (count_comp >=1) return 14;
  if (count_rad ==3) return 15;
  return 16;
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
  double weightsum = 0;
  double weightsumcor = 0;
  double weightsum2 = 0;
  double count_int=0;
  int count_mic=0, count_rad=0, count_pho=0, count_bhab=0,  count_brem=0, count_posAnn=0, count_comp=0,  count_sig=0;
  int int2mic1=0, int1mic2=0, pho1=0, brem1=0, posAnn1=0, comp1=0, other=0; 
  int tot_IC=0, tot_mic=0, tot_pho = 0, tot_com = 0 ;
  int ic_2=0;

  unsigned long long int nmic=0;
  int nic1=0,nic2=0,nic3=0;
  int hit6=0, hit8=0;
  //-----------------------Histograms
 TH1F *h_12 = new TH1F("h_12","h_12",8,10.01,12);
  TH1F *h_14 = new TH1F("h_14","h_14",8,12.01,14);
  TH1F *h_16 = new TH1F("h_16","h_16",8,16.01,16);
  TH1F *h_18 = new TH1F("h_18","h_18",8,18.01,18);
  TH1F *h_20 = new TH1F("h_20","h_20",8,20.01,20);
  TH1F *h_22 = new TH1F("h_22","h_22",8,22.01,22);
  TH1F *h_24 = new TH1F("h_24","h_24",8,24.01,24);
  TH1F *h_26 = new TH1F("h_26","h_26",8,26.01,26);
  TH1F *h_28 = new TH1F("h_28","h_28",8,28.01,28);
  TH1F *h_30 = new TH1F("h_30","h_30",8,30.01,30);
  TH1F *h_32 = new TH1F("h_32","h_32",8,32.01,32);
  TH1F *h_34 = new TH1F("h_34","h_34",8,34.01,34);
  TH1F *h_36 = new TH1F("h_36","h_36",8,36.01,35);
  TH1F *h_38 = new TH1F("h_38","h_38",8,38.01,38);
  TH1F *h_40 = new TH1F("h_40","h_40",8,40.01,40);
  TH1F *h_42 = new TH1F("h_42","h_42",8,42.01,42);
  TH1F *h_44 = new TH1F("h_44","h_44",8,44.01,44);
  TH1F *h_46 = new TH1F("h_46","h_46",8,46.01,46);
  TH1F *h_48 = new TH1F("h_48","h_48",8,48.01,48);
  TH1F *h_50 = new TH1F("h_50","h_50",8,50.01,50);
  TH1F *h_52 = new TH1F("h_52","h_52",8,52.01,52);
  TH1F *h_54 = new TH1F("h_54","h_54",8,54.01,54);
  TH1F *h_56 = new TH1F("h_56","h_56",8,56.01,56);
  TH1F *h_58 = new TH1F("h_58","h_58",8,58.01,60);

  int nbins = 20; double x0 = -10., x1 = 10.;
  TH1F *sh_12 = new TH1F("sh_12","sh_12",nbins,x0,x1);
  TH1F *sh_14 = new TH1F("sh_14","sh_14",nbins,x0,x1);
  TH1F *sh_16 = new TH1F("sh_16","sh_16",nbins,x0,x1);
  TH1F *sh_18 = new TH1F("sh_18","sh_18",nbins,x0,x1);
  TH1F *sh_20 = new TH1F("sh_20","sh_20",nbins,x0,x1);
  TH1F *sh_22 = new TH1F("sh_22","sh_22",nbins,x0,x1);
  TH1F *sh_24 = new TH1F("sh_24","sh_24",nbins,x0,x1);
  TH1F *sh_26 = new TH1F("sh_26","sh_26",nbins,x0,x1);
  TH1F *sh_28 = new TH1F("sh_28","sh_28",nbins,x0,x1);
  TH1F *sh_30 = new TH1F("sh_30","sh_30",nbins,x0,x1);
  TH1F *sh_32 = new TH1F("sh_32","sh_32",nbins,x0,x1);
  TH1F *sh_34 = new TH1F("sh_34","sh_34",nbins,x0,x1);
  TH1F *sh_36 = new TH1F("sh_36","sh_36",nbins,x0,x1);
  TH1F *sh_38 = new TH1F("sh_38","sh_38",nbins,x0,x1);
  TH1F *sh_40 = new TH1F("sh_40","sh_40",nbins,x0,x1);
  TH1F *sh_42 = new TH1F("sh_42","sh_42",nbins,x0,x1);
  TH1F *sh_44 = new TH1F("sh_44","sh_44",nbins,x0,x1);
  TH1F *sh_46 = new TH1F("sh_46","sh_46",nbins,x0,x1);
  TH1F *sh_48 = new TH1F("sh_48","sh_48",nbins,x0,x1);
  TH1F *sh_50 = new TH1F("sh_50","sh_50",nbins,x0,x1);
  TH1F *sh_52 = new TH1F("sh_52","sh_52",nbins,x0,x1);
  TH1F *sh_54 = new TH1F("sh_54","sh_54",nbins,x0,x1);
  TH1F *sh_56 = new TH1F("sh_56","sh_56",nbins,x0,x1);
  TH1F *sh_58 = new TH1F("sh_58","sh_58",nbins,x0,x1);
  TGraph *graph = new TGraph();


  // ------ save also a TTree with vertex information in the file
  // ---------------------------------------------------------------
  TTree t1("t1","Tree for the information");
  std::vector<float> px1_true;
  std::vector<float> py1_true;
  std::vector<float> pz1_true;
  std::vector<float> px1_reco;
  std::vector<float> py1_reco;
  std::vector<float> pz1_reco;
  std::vector<float> angle1;

  std::vector<float> px2_true;
  std::vector<float> py2_true;
  std::vector<float> pz2_true;
  std::vector<float> px2_reco;
  std::vector<float> py2_reco;
  std::vector<float> pz2_reco;
  std::vector<float> angle2;

  std::vector<float> px3_true;
  std::vector<float> py3_true;
  std::vector<float> pz3_true;
  std::vector<float> px3_reco;
  std::vector<float> py3_reco;
  std::vector<float> pz3_reco;
  std::vector<float> angle3;


  std::vector<float> *px_true=&px1_true;
  std::vector<float> *py_true=&py1_true;
  std::vector<float> *pz_true=&pz1_true;
  std::vector<float> *px_reco=&px1_reco;
  std::vector<float> *py_reco=&py1_reco;
  std::vector<float> *pz_reco=&pz1_reco;
  std::vector<float> *angleS=&angle1;

  std::vector<float> *pxl_true=&px2_true;
  std::vector<float> *pyl_true=&py2_true;
  std::vector<float> *pzl_true=&pz2_true;
  std::vector<float> *pxl_reco=&px2_reco;
  std::vector<float> *pyl_reco=&py2_reco;
  std::vector<float> *pzl_reco=&pz2_reco;
  std::vector<float> *anglel=&angle2;

  std::vector<float> *pxl8_true=&px3_true;
  std::vector<float> *pyl8_true=&py3_true;
  std::vector<float> *pzl8_true=&pz3_true;
  std::vector<float> *pxl8_reco=&px3_reco;
  std::vector<float> *pyl8_reco=&py3_reco;
  std::vector<float> *pzl8_reco=&pz3_reco;
  std::vector<float> *anglel8=&angle3;

  t1.Branch("px_true","std::vector < float >",&px_true);
  t1.Branch("py_true","std::vector < float >",&py_true);
  t1.Branch("pz_true","std::vector < float >",&pz_true);
  t1.Branch("px_reco","std::vector < float >",&px_reco);
  t1.Branch("py_reco","std::vector < float >",&py_reco);
  t1.Branch("pz_reco","std::vector < float >",&pz_reco);
  t1.Branch("angleS","std::vector < float >",&angleS);

  t1.Branch("pxl_true","std::vector < float >",&pxl_true);
  t1.Branch("pyl_true","std::vector < float >",&pyl_true);
  t1.Branch("pzl_true","std::vector < float >",&pzl_true);
  t1.Branch("pxl_reco","std::vector < float >",&pxl_reco);
  t1.Branch("pyl_reco","std::vector < float >",&pyl_reco);
  t1.Branch("pzl_reco","std::vector < float >",&pzl_reco);
  t1.Branch("anglel","std::vector < float >",&anglel);

  t1.Branch("pxl8_true","std::vector < float >",&pxl8_true);
  t1.Branch("pyl8_true","std::vector < float >",&pyl8_true);
  t1.Branch("pzl8_true","std::vector < float >",&pzl8_true);
  t1.Branch("pxl8_reco","std::vector < float >",&pxl8_reco);
  t1.Branch("pyl8_reco","std::vector < float >",&pyl8_reco);
  t1.Branch("pzl8_reco","std::vector < float >",&pzl8_reco);
  t1.Branch("anglel8","std::vector < float >",&anglel8);

  std::vector <double> tru;
  std::vector <double> sig;

   
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


    //Removes Verticies where it uses the same track which has been misreconstruted
    std::vector<int> v_vtx;
    for (int nv=0; nv<(int)nvert;nv++){
      if (checkVertexConsistency(nv)){
    	v_vtx.push_back(nv);
      }
    }    
    int nvert1 = v_vtx.size();
    if (nvert1 == 0) continue;
    c_sameTrack += weight ;


    //Finds all verticies clusters and only keep the best chi2 one
    std::vector<int> iv_new;
    if (nvert1 > 1){
    std::vector<double> chi;
    double chitemp[nvert1][2];
    for (int i=0;i<nvert1;i++){
      chitemp[i][1]=v_vtx[i];
      chitemp[i][0]=chi2->at(v_vtx[i]);
    }
    for (int k = 0; k < nvert1; k++){
      for( int p = k+1; p < nvert1; p++){
    	if( chitemp[k][0] > chitemp[p][0]){
    	  swap(chitemp[k][0], chitemp[p][0]);
    	  swap(chitemp[k][1], chitemp[p][1]);
    	}
      }
    }
    double DCUT = 0.8;
    for (int k = 0; k < nvert1; k++){
      if( chitemp[k][1] == 10000 ) continue;
      iv_new.push_back(chitemp[k][1]);
      for (int p = 0; p < nvert1; p++){
    	if( p == k ) continue;
    	if( chitemp[p][1] == 10000 ) continue;
    	double d=VtxDistance(chitemp[k][1],chitemp[p][1]);
    	if( d < DCUT ){
    	  chitemp[p][1] = 10000;
    	}	  
      }
    }
    }
    else { for (int j=0;j<(int)nvert;j++){ iv_new.push_back(j);} }
     int nvert_ovl = iv_new.size();
     if (nvert_ovl == 0){ continue; }
    c_vtxTovtx += weight ;


    int long0=0,long1=0,long2=0,long3=0;
    int c7long0 = 0, c7long1 = 0, c7long2 = 0, c7long3 = 0, nvert_c7=0;
    int flong0 = 0, flong1 = 0, flong2 = 0, flong3 = 0, nvert_tot=0;
    int filong0 = 0, filong1 = 0, filong2 = 0, filong3 = 0, tot=0;
    int icmic = 0;
    int count = 0;
    int nvPast=0;
    for (const int& nv : iv_new){
      
      
      if (chi2->at(nv) > 30 ){ continue; }

      if (targetdist->at(nv) > 3){ continue; }

      //if (pm->at(nv) > 8){ continue; }
      TLorentzVector e1;
      TLorentzVector e2;
      TLorentzVector e3;
      double em = 0.511;
      double p1 = TMath::Sqrt(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv));
      e1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(p1*p1+em*em));
      double p2 = TMath::Sqrt(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv));
      e2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(p2*p2+em*em));
      double p3 = TMath::Sqrt(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv));
      e3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(p3*p3+em*em));

      //if (numTrack[3] == 0) continue;  
      double true_mc=TMath::Sqrt((*true_pxm)[nv]*(*true_pxm)[nv]+(*true_pym)[nv]*(*true_pym)[nv]+(*true_pzm)[nv]*(*true_pzm)[nv]);
      double momres=true_mc-(*pm)[nv];
      if (true_mc > 10 && true_mc<55 && fabs(momres)<0.45) {
	tru.push_back(true_mc);
	sig.push_back(momres);
      }

      // test: only nhit1->at(nv) > 4 : long tracks, all other
      if (nhit1->at(nv) == 4) {
	px_true->push_back(float(true_px1->at(nv))); px_reco->push_back(float(px1->at(nv)));
	py_true->push_back(float(true_py1->at(nv))); py_reco->push_back(float(py1->at(nv)));
	pz_true->push_back(float(true_pz1->at(nv))); pz_reco->push_back(float(pz1->at(nv)));
	angleS->push_back(float(TMath::Pi()/2-e1.Theta()));
      }
      if (nhit2->at(nv) == 4) {
	px_true->push_back(float(true_px2->at(nv))); px_reco->push_back(float(px2->at(nv)));
	py_true->push_back(float(true_py2->at(nv))); py_reco->push_back(float(py2->at(nv)));
	pz_true->push_back(float(true_pz2->at(nv))); pz_reco->push_back(float(pz2->at(nv)));
	angleS->push_back(float(TMath::Pi()/2-e2.Theta()));
      }
      if (nhit3->at(nv) == 4) {
	px_true->push_back(float(true_px3->at(nv))); px_reco->push_back(float(px3->at(nv)));
	py_true->push_back(float(true_py3->at(nv))); py_reco->push_back(float(py3->at(nv)));
	pz_true->push_back(float(true_pz3->at(nv))); pz_reco->push_back(float(pz3->at(nv)));
	angleS->push_back(float(TMath::Pi()/2-e3.Theta()));
      }
      
      if (nhit1->at(nv) == 6) {
	pxl_true->push_back(float(true_px1->at(nv))); pxl_reco->push_back(float(px1->at(nv)));
	pyl_true->push_back(float(true_py1->at(nv))); pyl_reco->push_back(float(py1->at(nv)));
	pzl_true->push_back(float(true_pz1->at(nv))); pzl_reco->push_back(float(pz1->at(nv)));
	anglel->push_back(float(TMath::Pi()/2-e1.Theta()));
      }
      if (nhit2->at(nv) == 6) {
	pxl_true->push_back(float(true_px2->at(nv))); pxl_reco->push_back(float(px2->at(nv)));
	pyl_true->push_back(float(true_py2->at(nv))); pyl_reco->push_back(float(py2->at(nv)));
	pzl_true->push_back(float(true_pz2->at(nv))); pzl_reco->push_back(float(pz2->at(nv)));
	anglel->push_back(float(TMath::Pi()/2-e2.Theta()));
      }
      if (nhit3->at(nv) == 6) {
	pxl_true->push_back(float(true_px3->at(nv))); pxl_reco->push_back(float(px3->at(nv)));
	pyl_true->push_back(float(true_py3->at(nv))); pyl_reco->push_back(float(py3->at(nv)));
	pzl_true->push_back(float(true_pz3->at(nv))); pzl_reco->push_back(float(pz3->at(nv)));
	anglel->push_back(float(TMath::Pi()/2-e3.Theta()));
      }
      
      if (nhit1->at(nv) == 8) {
	pxl8_true->push_back(float(true_px1->at(nv))); pxl8_reco->push_back(float(px1->at(nv)));
	pyl8_true->push_back(float(true_py1->at(nv))); pyl8_reco->push_back(float(py1->at(nv)));
	pzl8_true->push_back(float(true_pz1->at(nv))); pzl8_reco->push_back(float(pz1->at(nv)));
	anglel8->push_back(float(TMath::Pi()/2-e1.Theta()));
      }
      if (nhit2->at(nv) == 8) {
	pxl8_true->push_back(float(true_px2->at(nv))); pxl8_reco->push_back(float(px2->at(nv)));
	pyl8_true->push_back(float(true_py2->at(nv))); pyl8_reco->push_back(float(py2->at(nv)));
	pzl8_true->push_back(float(true_pz2->at(nv))); pzl8_reco->push_back(float(pz2->at(nv)));
	anglel8->push_back(float(TMath::Pi()/2-e2.Theta()));
      }
      if (nhit3->at(nv) == 8) {
	pxl8_true->push_back(float(true_px3->at(nv))); pxl8_reco->push_back(float(px3->at(nv)));
	pyl8_true->push_back(float(true_py3->at(nv))); pyl8_reco->push_back(float(py3->at(nv)));
	pzl8_true->push_back(float(true_pz3->at(nv))); pzl8_reco->push_back(float(pz3->at(nv)));
	anglel8->push_back(float(TMath::Pi()/2-e3.Theta()));
      }
      
      if (true_mc<=12 && true_mc>10) h_12->Fill(true_mc);
      if (true_mc<=14 && true_mc>12) h_14->Fill(true_mc);
      if (true_mc<=16 && true_mc>14) h_16->Fill(true_mc);
      if (true_mc<=18 && true_mc>16) h_18->Fill(true_mc);
      if (true_mc<=20 && true_mc>18) h_20->Fill(true_mc);
      if (true_mc<=22 && true_mc>20) h_22->Fill(true_mc);
      if (true_mc<=24 && true_mc>22) h_24->Fill(true_mc);
      if (true_mc<=26 && true_mc>24) h_26->Fill(true_mc);
      if (true_mc<=28 && true_mc>26) h_28->Fill(true_mc);
      if (true_mc<=30 && true_mc>28) h_30->Fill(true_mc);
      if (true_mc<=32 && true_mc>30) h_32->Fill(true_mc);
      if (true_mc<=34 && true_mc>32) h_34->Fill(true_mc);
      if (true_mc<=36 && true_mc>34) h_36->Fill(true_mc);
      if (true_mc<=38 && true_mc>36) h_38->Fill(true_mc);
      if (true_mc<=40 && true_mc>38) h_40->Fill(true_mc);
      if (true_mc<=42 && true_mc>40) h_42->Fill(true_mc);
      if (true_mc<=44 && true_mc>42) h_44->Fill(true_mc);
      if (true_mc<=46 && true_mc>44) h_46->Fill(true_mc);
      if (true_mc<=48 && true_mc>46) h_48->Fill(true_mc);
      if (true_mc<=50 && true_mc>48) h_50->Fill(true_mc);
      if (true_mc<=52 && true_mc>50) h_52->Fill(true_mc);
      if (true_mc<=54 && true_mc>52) h_54->Fill(true_mc);
      if (true_mc<=56 && true_mc>54) h_56->Fill(true_mc);
      if (true_mc<=58 && true_mc>56) h_58->Fill(true_mc);

      if (true_mc<=12 && true_mc>10) sh_12->Fill(momres);
      if (true_mc<=14 && true_mc>12) sh_14->Fill(momres);
      if (true_mc<=16 && true_mc>14) sh_16->Fill(momres);
      if (true_mc<=18 && true_mc>16) sh_18->Fill(momres);
      if (true_mc<=20 && true_mc>18) sh_20->Fill(momres);
      if (true_mc<=22 && true_mc>20) sh_22->Fill(momres);
      if (true_mc<=24 && true_mc>22) sh_24->Fill(momres);
      if (true_mc<=26 && true_mc>24) sh_26->Fill(momres);
      if (true_mc<=28 && true_mc>26) sh_28->Fill(momres);
      if (true_mc<=30 && true_mc>28) sh_30->Fill(momres);
      if (true_mc<=32 && true_mc>30) sh_32->Fill(momres);
      if (true_mc<=34 && true_mc>32) sh_34->Fill(momres);
      if (true_mc<=36 && true_mc>34) sh_36->Fill(momres);
      if (true_mc<=38 && true_mc>36) sh_38->Fill(momres);
      if (true_mc<=40 && true_mc>38) sh_40->Fill(momres);
      if (true_mc<=42 && true_mc>40) sh_42->Fill(momres);
      if (true_mc<=44 && true_mc>42) sh_44->Fill(momres);
      if (true_mc<=46 && true_mc>44) sh_46->Fill(momres);
      if (true_mc<=48 && true_mc>46) sh_48->Fill(momres);
      if (true_mc<=50 && true_mc>48) sh_50->Fill(momres);
      if (true_mc<=52 && true_mc>50) sh_52->Fill(momres);
      if (true_mc<=54 && true_mc>52) sh_54->Fill(momres);
      if (true_mc<=56 && true_mc>54) sh_56->Fill(momres);
      if (true_mc<=58 && true_mc>56) sh_58->Fill(momres);


    }

    

    }

      t1.Fill();
  for(int i=0; i<tru.size();i++){
    graph->SetPoint(i,tru.at(i),sig.at(i));
  }
  t1.Write();
// std::cout<<"Abouve 10 "<<count_tmp<<std::endl;
  // h_12->Write();
  // h_14->Write();
  // h_16->Write();
  // h_18->Write();
  // h_20->Write();
  // h_22->Write();
  // h_24->Write();
  // h_26->Write();
  // h_28->Write();
  // h_30->Write();
  // h_32->Write();
  // h_34->Write();
  // h_36->Write();
  // h_38->Write();
  // h_40->Write();
  // h_42->Write();
  // h_44->Write();
  // h_46->Write();
  // h_48->Write();
  // h_50->Write();
  // h_52->Write();
  // h_54->Write();
  // h_56->Write();
  // h_58->Write();

  // sh_12->Write();
  // sh_14->Write();
  // sh_16->Write();
  // sh_18->Write();
  // sh_20->Write();
  // sh_22->Write();
  // sh_24->Write();
  // sh_26->Write();
  // sh_28->Write();
  // sh_30->Write();
  // sh_32->Write();
  // sh_34->Write();
  // sh_36->Write();
  // sh_38->Write();
  // sh_40->Write();
  // sh_42->Write();
  // sh_44->Write();
  // sh_46->Write();
  // sh_48->Write();
  // sh_50->Write();
  // sh_52->Write();
  // sh_54->Write();
  // sh_56->Write();
  // sh_58->Write();
  // graph->SetMarkerStyle(8);
  // graph->Draw("ap");

  fileout.Close();
}
