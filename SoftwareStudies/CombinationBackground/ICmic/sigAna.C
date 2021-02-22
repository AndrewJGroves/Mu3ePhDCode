#define sigAna_cxx
#include "sigAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include "TLorentzVector.h"
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
#include "TF1.h"
#include <iomanip>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <set> 
#include <random>
#include <utility>
#include <algorithm>
#include "Math/SpecFunc.h"
#include "Math/DistFunc.h"
static inline double computeSquare (double x) { return x*x; }

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

bool sigAna::hasVertexInAcceptance(){
  vector<double> vx2(true_vx->size());
  vector<double> vy2(true_vy->size());
  vector<double> vza(true_vz->size());
  vector<double> v2(true_vx->size());
  vector<double> r(true_vy->size());
  std::transform(true_vx->begin(), true_vx->end(), vx2.begin(), computeSquare);
  std::transform(true_vy->begin(), true_vy->end(), vy2.begin(), computeSquare);
  std::transform(vy2.begin(), vy2.end(), vx2.begin(), v2.begin(), std::plus<double>());
  std::transform(v2.begin(), v2.end(), r.begin(),(double(*)(double)) sqrt);
  std::transform(true_vz->begin(), true_vz->end(), vza.begin(),static_cast<double (*)(double)>(&std::abs));
  auto it = std::find_if(r.begin(), r.end(), [](int i){return i < 20;});
  //std::cout<<*it<<endl;
  while (it != std::end(r)) {
    if(vza[std::distance(std::begin(r), it)] < 50) return true;
    it = std::find_if(std::next(it), std::end(r), [](int i){return i < 20;});
  }
  // for (int n=0; n<(int)nvert;n++){
  //    double r1 = sqrt( ((*vx)[n]*(*vx)[n])  + ((*vy)[n]*(*vy)[n]));
  //    if (r1 < 20 && abs(vz->at(n)) < 50) return true;
  // }
  return false;
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
  if (count_rad == 2 && count_pho == 1) return 16;
  if (count_rad == 2 && count_brem == 1) return 17;
  if (count_rad == 2 && count_comp == 1) return 18;
  if (count_rad == 1 && count_pho == 2) return 19;
  if (count_rad == 1 && count_brem == 2) return 20;
  if (count_rad == 1 && count_comp == 2) return 21;
  return 22;
}


void sigAna::Loop(int cut)
{
  if (fChain == 0) return;
  TH1::SetDefaultSumw2();
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TFile fileout(_fileoutname, "recreate");

 //---------------------------- Cut values
  bool ChiCut = true;
  int ChiCutValue = 15;

  bool TargetCut = false;
  int TargetCutValue = 1; 		

  bool MomentumCut = true;
  int MomentumCutValue = 4;

  bool DielecCut = true;
  int DieleLow = 5;
  int DieleHigh = 10;

  bool MassCut = true;
  int MassCutLow = 103;
  int MassCutHigh = 110;

  bool isSignal=false;
  double sigNormRes=87790543;

  bool PlotMuonP = true;
  bool PlotMassReso = true;
  bool CutStudy = true;
  //---------------------------counters 
  double Cut1vtx = 0, CutTrueVtxAccp = 0, CutChi = 0, CutChiLong = 0, CutP = 0, CutPLong=0, CutDielec = 0, CutDielecLong = 0;
  double CutMass = 0, CutMassLong = 0, CutTarget = 0, CutTargetLong; 
  double weightsum = 0, weightsumcor = 0, weightsum2 = 0;
  double nframesweight1=0;
  //-----------------------Histograms

  TH1F *h_chi2 = new TH1F("h_chi2", "Chi2", 1000,0,100);
  TH1F *h_chi2Long = new TH1F("h_chi2Long", "Chi2 long", 1000,0,100);

  TH1F *h_target = new TH1F("h_target", "Distance to target", 2000,-100,100);
  TH1F *h_targetLong = new TH1F("h_targetLong", "Distance to target long", 2000,-100,100);

  TH1F *h_tmom = new TH1F("h_tmom", "Absolute momentum", 1000,0,100);
  TH1F *h_tmomLong = new TH1F("h_tmomLong", "Absolute momentum long", 1000,0,100);

  TH1F *h_Diele = new TH1F("h_Diele", "Dielectron Mass", 1000,0,100);
  TH1F *h_DieleLong = new TH1F("h_DieleLong", "Dielectron Mass long", 1000,0,100);

  TH1F *h_mass = new TH1F("h_mass", "Mass", 1000,0,200);
  TH1F *h_massLong = new TH1F("h_massLong", "Mass long", 1000,0,200);
  TH1F *h_massFinal = new TH1F("h_massFinal", "Mass Final", 1000,0,200);

  TH2F *h_PmMass = new TH2F("h_PmMass", "Momentum Vs Mass", 1000,0,200,1000,0,20);
  TH2F *h_PmMassFinal = new TH2F("h_PmMassFinal", "Momentum Vs Mass", 1000,0,200,1000,0,20);

  TH1F *h_mpx = new TH1F("h_mpx", "Muon px", 1000,-20,20);
  TH1F *h_mpy = new TH1F("h_mpy", "Muon py", 1000,-20,20);
  TH1F *h_mpz = new TH1F("h_mpz", "Muon pz", 1000,-20,20);

  TH1F *h_MassReso = new TH1F("h_massReso", "Mass Reso", 200,-200,200);

  TH1F *h_weight = new TH1F("h_weight", "Weight", 200,0,6e6);
  TH2F *h_close = new TH2F("h_close", "Close", 20,0,50,35,0,35);
  TH2F *h_time = new TH2F("h_time", "Time", 20,0,50,40,0,100);
  TH1F *h_Theta10 = new TH1F("h_Theta10", "Theta10", 20,-3,3);
  TH1F *h_Theta20 = new TH1F("h_Theta20", "Theta20", 20,-3,3);
  TH1F *h_diff = new TH1F("h_diff", "diff", 40,0,100);
  TH1F *h_diff4 = new TH1F("h_diff4", "diff4", 40,0,100);
  TH1F *h_diff6 = new TH1F("h_diff6", "diff6", 40,0,100);
  TH1F *h_diff8 = new TH1F("h_diff8", "diff8", 40,0,100);
  TH1F *h_doR = new TH1F("h_doR", "doR", 20,0,1.4);
  TH1F *h_dR = new TH1F("h_dR", "dR", 100,0,1);

  //-------------------------------Cut study

  const int nCut=12;
  Double_t chicut[]={35,30,28,26,24,22,20,17,15,13,10,5};
  Double_t pcut[]={10,9,8,7,6,5.5,5,4,3,2,1,0};
  Double_t masscut[]={97,99,100,101,102,103,104,105,106,107,109,110};
  Double_t dielecutLow[]={0,1,2,3,3.5,4,4.5,5,5.5,6,6.5,7};
  Double_t dielecutUp[]={7,7.5,8,8.5,9,9.5,10,10.5,11,11.5,12,13};
  double CutOpP = 0, CutOpChi=0, CutOpMass=0, CutDiElec=0;
  double PCutDetial[nCut]={0};
  double ChiCutDetial[nCut]={0};
  double MassCutDetial[nCut]={0};
  double DieElecLowCutDetial[nCut]={0};
  double DieElecUpCutDetial[nCut]={0};


//--------------------------------

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
    if (nvert >= 1) { Cut1vtx +=weight  ; }
    else { continue; };
    if (hasVertexInAcceptance()) { CutTrueVtxAccp += weight; }
    else { continue; }

 
    for (int nv=0;nv<(int)nvert;nv++){
      std::vector<int> numTrack( getTrackType(nv) );
      int trackType = getTrack(nv);
      //if (trackType != 3) continue;

      if(CutStudy){
	CutOpChi += weight;
	if (chi2->at(nv) < ChiCutValue ) CutOpP += weight;
	if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue) CutDiElec += weight; 
	if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue && mep1->at(nv) < DieleLow && mep1->at(nv) > DieleHigh) CutOpMass+= weight;
	for(int i=0; i <nCut ; i ++){
	  if(chi2->at(nv) < chicut[i]) ChiCutDetial[i] += weight; 
	  if(chi2->at(nv) < ChiCutValue ){
	    if(pm->at(nv) < pcut[i]) {PCutDetial[i] += weight;}
	  }
	  if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue){
		if(mep1->at(nv) < dielecutLow[i] && mep1->at(nv) > DieleHigh) DieElecLowCutDetial[i] += weight;
		if(mep1->at(nv) > dielecutUp[i] && mep1->at(nv) < DieleLow) DieElecUpCutDetial[i] += weight;}
	  if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue && mep1->at(nv) < DieleLow && mep1->at(nv) > DieleHigh){
	    if(mmass->at(nv) > masscut[i]){MassCutDetial[i] += weight;}
	  }  
	}
      }


      if(ChiCut){	
	if (numTrack[3] == 1) h_chi2Long->Fill((*chi2)[nv],weight);
	h_chi2->Fill((*chi2)[nv],weight);
	if (chi2->at(nv) > ChiCutValue ) continue; 
	if (numTrack[3] == 1) CutChiLong += weight;
	CutChi += weight;
      }


      if(TargetCut){
	if (numTrack[3] == 1) h_targetLong->Fill((*targetdist)[nv],weight);
	h_target->Fill((*targetdist)[nv],weight);
	if (abs(targetdist->at(nv)) > TargetCutValue) continue; 
	if( numTrack[3] == 1) CutTargetLong += 1;	
	CutTarget += weight;

      }

      h_PmMass->Fill((*mmass)[nv],(*pm)[nv],weight);

      if(MomentumCut){
	if (numTrack[3] == 1) h_tmomLong->Fill((*pm)[nv],weight);
	h_tmom->Fill((*pm)[nv],weight);
	if (pm->at(nv) > MomentumCutValue){ continue; }
	CutP += weight;
	if (numTrack[3] == 1) CutPLong += weight;
      }


      if(DielecCut){
	h_Diele->Fill((*mep1)[nv],weight);
	if( numTrack[3] == 1) h_DieleLong->Fill((*mep1)[nv],weight);
	if(mep1->at(nv) > DieleLow && mep1->at(nv) < DieleHigh) continue;
	CutDielec += weight;
	if(numTrack[3] == 1) CutDielecLong += weight;
      }


      if(ICmicStudy){
 double diff = 0;
	  double diffxy = 0;
	  double diffzy = 0;
	  if(type1->at(nv) == 31 || type1->at(nv) == 32){
	    if(type2->at(nv) == 11){
	      diffxy = TMath::Sqrt((((*true_cx2)[nv]-(*true_cx1)[nv]) * ((*true_cx2)[nv]-(*true_cx1)[nv]))+(((*true_cy2)[nv]-(*true_cy1)[nv]) * ((*true_cy2)[nv]-(*true_cy1)[nv])));
	      diffzy = TMath::Sqrt((((*true_cy2)[nv]-(*true_cy1)[nv]) * ((*true_cy2)[nv]-(*true_cy1)[nv])) +  (((*true_cz2)[nv]-(*true_cz1)[nv]) * ((*true_cz2)[nv]-(*true_cz1)[nv])));
	      diff = TMath::Sqrt((((*true_cx2)[nv]-(*true_cx1)[nv]) * ((*true_cx2)[nv]-(*true_cx1)[nv]))+(((*true_cy2)[nv]-(*true_cy1)[nv]) * ((*true_cy2)[nv]-(*true_cy1)[nv])) + (((*true_cz2)[nv]-(*true_cz1)[nv]) * ((*true_cz2)[nv]-(*true_cz1)[nv])));
	    }
	    if(type3->at(nv) == 11){
	      diffxy = TMath::Sqrt((((*true_cx3)[nv]-(*true_cx1)[nv]) * ((*true_cx3)[nv]-(*true_cx1)[nv]))+(((*true_cy3)[nv]-(*true_cy1)[nv]) * ((*true_cy3)[nv]-(*true_cy1)[nv])));
	      diffzy = TMath::Sqrt((((*true_cy3)[nv]-(*true_cy1)[nv]) * ((*true_cy3)[nv]-(*true_cy1)[nv])) +  (((*true_cz3)[nv]-(*true_cz1)[nv]) * ((*true_cz3)[nv]-(*true_cz1)[nv])));
	      diff = TMath::Sqrt((((*true_cx3)[nv]-(*true_cx1)[nv]) * ((*true_cx3)[nv]-(*true_cx1)[nv]))+(((*true_cy3)[nv]-(*true_cy1)[nv]) * ((*true_cy3)[nv]-(*true_cy1)[nv]))+  (((*true_cz3)[nv]-(*true_cz1)[nv]) * ((*true_cz3)[nv]-(*true_cz1)[nv])));
	    }
	  }
	  else{
	    diffzy = TMath::Sqrt((((*true_cy3)[nv]-(*true_cy1)[nv]) * ((*true_cy3)[nv]-(*true_cy1)[nv])) +  (((*true_cz3)[nv]-(*true_cz1)[nv]) * ((*true_cz3)[nv]-(*true_cz1)[nv])));
	    diffxy = TMath::Sqrt((((*true_cx3)[nv]-(*true_cx1)[nv]) * ((*true_cx3)[nv]-(*true_cx1)[nv]))+(((*true_cy3)[nv]-(*true_cy1)[nv]) * ((*true_cy3)[nv]-(*true_cy1)[nv])));
	    diff = TMath::Sqrt((((*true_cx3)[nv]-(*true_cx1)[nv]) * ((*true_cx3)[nv]-(*true_cx1)[nv]))+(((*true_cy3)[nv]-(*true_cy1)[nv]) * ((*true_cy3)[nv]-(*true_cy1)[nv]))+  (((*true_cz3)[nv]-(*true_cz1)[nv]) * ((*true_cz3)[nv]-(*true_cz1)[nv])));
	  }
	  h_diff->Fill(diff);
	  TLorentzVector e1;
	  TLorentzVector e2;
	  TLorentzVector e3;
	  e1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(emass*emass+(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))));
	  e2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(emass*emass+(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))));
	  e3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(emass*emass+(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))));
	  double ti1 = t0_mc1->at(nv)-((event)*50);
	  double t2 = t0_mc2->at(nv)-((event)*50);
	  double t3 = t0_mc3->at(nv)-((event)*50);
	  double x1; //Finding distance of closest approch in transverse plane
	  if(type2->at(nv) == 11){
	    if(t0_tl1->at(nv) != -1 && t0_tl1->at(nv) < 47 && t0_tl1->at(nv) > 0.5) h_time->Fill(TMath::Abs(t2-t0_tl2->at(nv)),diff);

	    if(nhit2->at(nv) == 4) h_diff4->Fill(diff);
	    if(nhit2->at(nv) == 6) h_diff6->Fill(diff);
	    if(nhit2->at(nv) == 8) h_diff8->Fill(diff);

	    h_doR->Fill(diff/TMath::Abs((*r2)[nv]));
	    std::vector<double> cer( circle(e2.Px(),e2.Py(),(*vx)[nv],(*vy)[nv],(*r2)[nv]) ); 
	    double x = TMath::Sqrt((((*true_cx2)[nv]-cer[0])*((*true_cx2)[nv]-cer[0]))+(((*true_cy2)[nv]-cer[1])*((*true_cy2)[nv]-cer[1])));
	    if (x >  TMath::Abs(r2->at(nv))){
	      x1=x-TMath::Abs((*r2)[nv]);
	    }
	    if (x <  TMath::Abs(r2->at(nv))){
	      x1=TMath::Abs((*r2)[nv])-x;
	    }
	    h_dR->Fill(TMath::Abs(x1)/TMath::Abs((*r2)[nv]));
	    h_close->Fill(diffxy,TMath::Abs(x1));
	  }

	  if(type3->at(nv) == 11){
	    if(t0_tl1->at(nv) != -1 && t0_tl1->at(nv) < 47 && t0_tl1->at(nv) > 0.5 ) h_time->Fill(TMath::Abs(t3-t0_tl3->at(nv)),diff);
	    if(nhit3->at(nv) == 4) h_diff4->Fill(diff);
	    if(nhit3->at(nv) == 6) h_diff6->Fill(diff);
	    if(nhit3->at(nv) == 8) h_diff8->Fill(diff);
	    h_doR->Fill(diff/TMath::Abs((*r3)[nv]));
	    std::vector<double> cer( circle(e3.Px(),e3.Py(),(*vx)[nv],(*vy)[nv],(*r3)[nv]) ); 
	    double x = TMath::Sqrt((((*true_cx3)[nv]-cer[0])*((*true_cx3)[nv]-cer[0]))+(((*true_cy3)[nv]-cer[1])*((*true_cy3)[nv]-cer[1])));
	    if (x > TMath::Abs(r3->at(nv))){
	      x1=x-TMath::Abs((*r3)[nv]);
	    }
	    if (x <  TMath::Abs(r3->at(nv))){
	      x1=TMath::Abs((*r3)[nv])-x;
	    }
	    h_dR->Fill(TMath::Abs(x1)/TMath::Abs((*r3)[nv]));
	    h_close->Fill(diffxy,TMath::Abs(x1));
	  }
      
	  if(type1->at(nv) == 11){
	    if(t0_tl1->at(nv) != -1 && t0_tl1->at(nv) < 47 && t0_tl1->at(nv) > 0.5) h_time->Fill(TMath::Abs(ti1-t0_tl1->at(nv)),diff);
	    if(nhit1->at(nv) == 4) h_diff4->Fill(diff);
	    if(nhit1->at(nv) == 6) h_diff6->Fill(diff);
	    if(nhit1->at(nv) == 8) h_diff8->Fill(diff);
	    std::vector<double> cer( circle((*px1)[nv],(*py1)[nv],(*vx)[nv],(*vy)[nv],(*r1)[nv]) ); 
	    double x = TMath::Sqrt((((*true_cx1)[nv]-cer[0])*((*true_cx1)[nv]-cer[0]))+(((*true_cy1)[nv]-cer[1])*((*true_cy1)[nv]-cer[1])));
	    if (x > TMath::Abs(r1->at(nv))){
	      x1=x-TMath::Abs((*r1)[nv]);
	    }
	    if (x < TMath::Abs(r1->at(nv))){
	      x1=TMath::Abs((*r1)[nv])-x;
	    }
	    h_dR->Fill(TMath::Abs(x1)/TMath::Abs((*r1)[nv]));
	    h_close->Fill(diffxy,TMath::Abs(x1));
	  }

	  if ( diff > 20){
	    if(type1->at(nv) == 11){
	      h_Theta20->Fill(e1.Theta());
	    }
	    else if(type2->at(nv) == 11){
	      h_Theta20->Fill(e2.Theta());
	    }
	    else if(type3->at(nv) == 11){
	      h_Theta20->Fill(e3.Theta());
	    }
	  }

	  if ( diff < 10){
	    if(type1->at(nv) == 11){
	      h_Theta10->Fill(e1.Theta());
	    }
	    else if(type2->at(nv) == 11){
	      h_Theta10->Fill(e2.Theta());
	    }
	    else if(type3->at(nv) == 11){
	      h_Theta10->Fill(e3.Theta());
	    }
	  }
      }




      if(PlotMassReso){
	if(numTrack[3] == 1){
	  double reso = (*mmass)[nv] - (*true_mass)[nv];
	  h_MassReso->Fill(reso);
	}
      }

      if(PlotMuonP){
	if(numTrack[3] == 1){
	  h_mpx->Fill((*pxm)[nv],weight);
	  h_mpy->Fill((*pym)[nv],weight);
	  h_mpz->Fill((*pzm)[nv],weight);
	}
      }

      if(MassCut){
	h_mass->Fill((*mmass)[nv],weight);
	if (numTrack[3] == 1) h_massLong->Fill((*mmass)[nv],weight);
	if(mmass->at(nv) <= MassCutLow && mmass->at(nv) >= MassCutHigh) continue;     
	CutMass += weight;
	if(numTrack[3] == 1) CutMassLong += weight;	
      }


      if(numTrack[3] == 1) h_massFinal->Fill((*mmass)[nv],weight);
      if(numTrack[3] == 1) h_PmMassFinal->Fill((*mmass)[nv],(*pm)[nv],weight);

    }

  }

    
  if(PlotMassReso) h_MassReso->Write();
  if(PlotMuonP){
    h_mpx->Write();
    h_mpy->Write();
    h_mpz->Write();
  }
  if(ChiCut) h_chi2->Write();
  if(TargetCut) h_target->Write();
  if(MomentumCut) h_tmom->Write();
  if(MassCut) h_mass->Write();
  if(ChiCut) h_chi2Long->Write();
  if(TargetCut) h_targetLong->Write();
  if(MomentumCut) h_tmomLong->Write();
  if(DielecCut) h_DieleLong->Write();
  if(DielecCut) h_Diele->Write();
  if(MassCut) h_massLong->Write();
  h_PmMass->Write();
  h_PmMassFinal->Write();
  h_massFinal->Write();

  if(ICmicStudy){
    h_weight->Write();
    h_doR->Write();
    h_dR->Write();
    h_diff->Write();
    h_diff4->Write();
    h_diff6->Write();
    h_diff8->Write();
    h_Theta20->Write();
    h_Theta10->Write();
    h_close->Write();
    h_time->Write();
  }

  if(CutStudy){
    Double_t chiall2[nCut]={0};
    Double_t pall2[nCut]={0};
    Double_t massall2[nCut]={0};
   Double_t DieUp[nCut]={0};
    Double_t DieLow[nCut]={0};
    for(int i=0; i < nCut; i++){ 
chiall2[i] = ChiCutDetial[i]/CutOpChi; 
pall2[i] = PCutDetial[i]/CutOpP;
massall2[i] = MassCutDetial[i]/CutOpMass;
DieUp[i] = DieElecUpCutDetial[i]/CutDiElec; 
DieLow[i] = DieElecLowCutDetial[i]/CutDiElec; 
} 
    TGraph* chiNoCut = new TGraph(nCut,chicut,chiall2);
    chiNoCut->SetTitle("Chi2 no other cut");
    chiNoCut->GetYaxis()->SetTitle("Efficiency");
    chiNoCut->GetXaxis()->SetTitle("#chi^{2}");
    TGraph* pCutGraph = new TGraph(nCut,pcut,pall2);
    pCutGraph->SetTitle("Momentum");
    pCutGraph->GetYaxis()->SetTitle("Efficiency");
    pCutGraph->GetXaxis()->SetTitle("Momentum");
    TGraph* massCutGraph = new TGraph(nCut,masscut,massall2);
    massCutGraph->SetTitle("Mass");
    massCutGraph->GetYaxis()->SetTitle("Efficiency");
    massCutGraph->GetXaxis()->SetTitle("Mass");
    TGraph* DieUpCutGraph = new TGraph(nCut, dielecutUp,DieUp);
   DieUpCutGraph->SetTitle("DieElectron Up");
   DieUpCutGraph->GetYaxis()->SetTitle("Efficiency");
    DieUpCutGraph->GetXaxis()->SetTitle("DiElectron Mass");
    TGraph* DieLowCutGraph = new TGraph(nCut, dielecutLow,DieLow);
   DieLowCutGraph->SetTitle("DieElectron Low");
   DieLowCutGraph->GetYaxis()->SetTitle("Efficiency");
    DieLowCutGraph->GetXaxis()->SetTitle("DiElectron Mass");
DieLowCutGraph->Write();
DieUpCutGraph->Write();	
    massCutGraph->Write();
    pCutGraph->Write();
    chiNoCut->Write();
  }

  double Nmuons = 0;
  //Nmuons=weightsum;
  if(isSignal) Nmuons=sigNormRes;
  else Nmuons=weightsum; 
  printf("\n");
  printf("\\begin{table}[h] \n");
  printf("\\begin{center} \n");
  printf("\\caption{} \n");
  printf("\\begin{tabular}{l r r r r} \n");
  printf("\\hline \n");
  printf("Cut & No of Frames  & Efficiency & Step Effiency & \\\\ \n");
  printf("\\hline \n");
  printf("Generated Number of muon decays & %2.3e $\\pm$ %2.3e  & - && \\\\ \n",Nmuons,TMath::Sqrt(weightsum2));
  printf("\\hline \n"); 
  printf("$\\geq$1 vertex  & %2.3e & %2.3f && \\\\ \n",Cut1vtx,Cut1vtx/Nmuons);
  printf("True vtx within acceptance  &  %2.3e  & %2.3f & %2.3f & \\\\ \n",CutTrueVtxAccp,CutTrueVtxAccp/(float)Nmuons, CutTrueVtxAccp/(float)Cut1vtx);
  printf("\\hline \n"); 
  if(ChiCut){
    printf("$\\chi^2 <$ %2d All Tracks & %2.3e & %2.3f  & %2.3f & \\\\ \n",ChiCutValue, CutChi,CutChi/(float)Nmuons, CutChi/(float)CutTrueVtxAccp);
    printf("$\\chi^2 <$ %2d Long Tracks & %2.3e & %2.3f  & %2.3f & \\\\ \n",ChiCutValue, CutChiLong,CutChiLong/(float)Nmuons, CutChiLong/(float)CutTrueVtxAccp);}
  if(TargetCut){
    printf("Vertex target distance $<$ %2d ~mm All tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTarget,CutTarget/(float)Nmuons,CutTarget/(float)CutChi);
    printf("Vertex target distance $<$ %2d ~mm Long tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTargetLong,CutTargetLong/(float)Nmuons,CutTargetLong/(float)CutChiLong);}
  if(TargetCut && !ChiCut){
    printf("Vertex target distance $<$ %2d ~mm All tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTarget,CutTarget/(float)Nmuons,CutTarget/(float)CutTrueVtxAccp);
    printf("Vertex target distance $<$ %2d ~mm Long tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTargetLong,CutTargetLong/(float)Nmuons,CutTargetLong/(float)CutTrueVtxAccp);}
  if(MomentumCut && !TargetCut){
    printf("Problem");
    printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutChi);
    printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutChiLong);}
  if(MomentumCut && TargetCut){
    printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutTarget);
    printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutTargetLong);}
  if(MomentumCut && !TargetCut && !ChiCut){
    printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutTrueVtxAccp);
    printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutTrueVtxAccp);}
  if(DielecCut && MomentumCut){
    printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutP);
    printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutPLong);}
  if(DielecCut && !MomentumCut && TargetCut){
    printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutTarget);
    printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutTargetLong);}
  if(DielecCut && !MomentumCut && !TargetCut && CutChi){
    printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutChi);
    printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutChiLong);}
  if(DielecCut && !MomentumCut && !TargetCut && !CutChi){
    printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutTrueVtxAccp);
    printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutTrueVtxAccp);}
  if(MassCut && DielecCut){
    printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutDielec);
    printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutDielecLong);}
  if(MassCut && !DielecCut && MomentumCut){
    printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutP);
    printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutPLong);}
  if(MassCut && !DielecCut && !MomentumCut && TargetCut){
    printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutTarget);
    printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutTargetLong);}
  if(MassCut && DielecCut && !MomentumCut && !TargetCut && ChiCut){
    printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutChi);
    printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutChiLong);}
  if(MassCut && DielecCut && !MomentumCut && !TargetCut && !ChiCut){
    printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutTrueVtxAccp);
    printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutTrueVtxAccp);}
  printf("\\hline \n");
  printf("\\hline \n"); 
  printf("\\end{tabular} \n");
  printf("\\end{center} \n");
  printf("\\end{table} \n");
 

  fileout.Close();
}
