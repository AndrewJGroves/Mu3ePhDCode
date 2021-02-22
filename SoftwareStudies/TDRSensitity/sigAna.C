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
  int count_Bhabb = countTracks(nv,25);

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
  if (count_Bhabb == 2 && count_mic == 1) return 12;
  //if (count_pho >=1) return 11;
  //if (count_brem >=1) return 12;
  //if (count_posAnn >=1) return 13;
  //if (count_comp >=1) return 14;
  if (count_rad ==3) return 15;
  if (count_rad == 2 && count_pho == 1) return 16;
  if (count_rad == 2 && count_brem == 1) return 17;
  if (count_rad == 2 && count_comp == 1) return 18;
  if (count_mic == 1 && count_pho == 2) return 19;
  if (count_rad == 1 && count_brem == 2) return 20;
  if (count_rad == 1 && count_comp == 2) return 21;
  return 22;
}


void sigAna::Loop(float WeightSum, int VertexType, int cut)
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
  int TargetCutValue = 3; 		

  bool MomentumCut = true;
  int MomentumCutValue = 4;

  bool DielecCut = true;
  int DieleLow = 5;
  int DieleHigh = 10;

  bool MassCut = true;
  int MassCutLow = 103;
  int MassCutHigh = 110;

  bool MassPho = true;

  bool PlotMuonP = true;
  bool PlotMassReso = true;
  bool CutStudy = true;

  bool saveTree = true;
  //---------------------------counters 
  double Cut1vtx = 0, CutTrueVtxAccp = 0, CutChi = 0, CutChiLong = 0, CutP = 0, CutPLong=0, CutDielec = 0, CutDielecLong = 0;
  double CutMass = 0, CutMassLong = 0, CutTarget = 0, CutTargetLong=0; 
  double Cut1vtx2 = 0, CutTrueVtxAccp2 = 0, CutChi2 = 0, CutChiLong2 = 0, CutP2 = 0, CutPLong2=0, CutDielec2 = 0, CutDielecLong2 = 0;
  double CutMass2 = 0, CutMassLong2 = 0, CutTarget2 = 0, CutTargetLong2=0; 
  float weightsum = 0, weightsumcor = 0, weightsum2 = 0;
  float nframesweight1=0;
  int typeSelection=VertexType;
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

  TH2F *h_MassDie = new TH2F("h_MassDie", "Momentum Vs Die", 1000,0,200,1000,0,100);
  
  TH1F *h_massLongPho = new TH1F("h_massLongPho", "Mass long pho", 1000,0,200);


  TH1F *h_mpx = new TH1F("h_mpx", "Muon px", 1000,-20,20);
  TH1F *h_mpy = new TH1F("h_mpy", "Muon py", 1000,-20,20);
  TH1F *h_mpz = new TH1F("h_mpz", "Muon pz", 1000,-20,20);

  TH1F *h_MassReso = new TH1F("h_massReso", "Mass Reso", 200,-10,10);

  //------------------------------Tree
  Double_t        v_weight;
  std::vector<double> v_mmass;
  std::vector<double> * v0_mmass = &v_mmass;
  TTree t1("t1","Tree for the information");
  if(saveTree){
    t1.Branch("weight",&v_weight,"v_weight/D");
    t1.Branch("mmass","vector<double> " ,&v_mmass);
  }

  //-------------------------------Cut study

  const int nCut=12;
  Double_t chicut[]={35,30,28,26,24,22,20,17,15,13,10,5};
  Double_t pcut[]={10,9,8,7,6,5.5,5,4,3,2,1,0};
  Double_t masscut[]={97,99,100,101,102,103,104,105,106,107,109,110};
  Double_t dielecutLow[]={0,1,2,3,3.5,4,4.5,5,5.5,6,6.5,7};
  Double_t dielecutUp[]={10,12,14,15,16,17,18,19,20,21,22,23};
  double CutOpP = 0, CutOpChi=0, CutOpMass=0, CutDiElec=0;
  double PCutDetial[nCut]={0};
  double ChiCutDetial[nCut]={0};
  double MassCutDetial[nCut]={0};
  double DieElecLowCutDetial[nCut]={0};
  double DieElecUpCutDetial[nCut]={0};


  //--------------------------------
  if (cut>0) std::cout<<"Cut value is "<<cut<<std::endl;
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

    if (saveTree) v0_mmass->clear();
    for (int nv=0;nv<(int)nvert;nv++){
      std::vector<int> numTrack( getTrackType(nv) );
      int trackType = getTrack(nv);
      if (typeSelection != -1){
	if (trackType != typeSelection) continue;}

      if(CutStudy){
	CutOpChi += weight;
	if (chi2->at(nv) < ChiCutValue ) CutOpP += weight;
	if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue){
	  CutDiElec += weight; 
	  if (mep1->at(nv) < DieleLow || mep1->at(nv) > DieleHigh){
	    CutOpMass+= weight;
	  }
	}
	for(int i=0; i <nCut ; i ++){
	  if(chi2->at(nv) < chicut[i]) ChiCutDetial[i] += weight; 
	  if(chi2->at(nv) < ChiCutValue ){
	    if(pm->at(nv) < pcut[i]) {PCutDetial[i] += weight;}
	  }
	  if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue){
	    if(mep1->at(nv) < dielecutLow[i] || mep1->at(nv) > DieleHigh) DieElecLowCutDetial[i] += weight;
	    if(mep1->at(nv) > dielecutUp[i] || mep1->at(nv) < DieleLow) DieElecUpCutDetial[i] += weight;}
	  if (chi2->at(nv) < ChiCutValue && pm->at(nv) < MomentumCutValue){
	    if(mep1->at(nv) < DieleLow || mep1->at(nv) > DieleHigh){
	      if(mmass->at(nv) > masscut[i]){MassCutDetial[i] += weight;}
	    }
	  }  
	}
      }


      if(ChiCut){	
	if (numTrack[3] == 1) h_chi2Long->Fill((*chi2)[nv],weight);
	h_chi2->Fill((*chi2)[nv],weight);
	if (chi2->at(nv) > ChiCutValue ) continue; 
	if (numTrack[3] == 1) CutChiLong += weight;
	if (numTrack[3] == 1) CutChiLong2 += weight*weight;
	CutChi += weight;
	CutChi2 += weight*weight;
      }


      if(TargetCut){
	if (numTrack[3] == 1) h_targetLong->Fill((*targetdist)[nv],weight);
	h_target->Fill((*targetdist)[nv],weight);
	if (abs(targetdist->at(nv)) > TargetCutValue) continue; 
	if( numTrack[3] == 1) CutTargetLong += 1;	
	CutTarget += weight;

      }

      if((mep1->at(nv) < DieleLow || mep1->at(nv) > DieleHigh)){
	h_PmMass->Fill((*mmass)[nv],(*pm)[nv],weight);
	if(MassPho && numTrack[3]==1) h_massLongPho->Fill((*mmass)[nv],weight);
	//CutDielecLong += weight;
      }
      if(MomentumCut){
	if (numTrack[3] == 1) h_tmomLong->Fill((*pm)[nv],weight);
	h_tmom->Fill((*pm)[nv],weight);
	if (pm->at(nv) > MomentumCutValue){ continue; }
	CutP += weight;
	CutP2 += weight*weight;
	if (numTrack[3] == 1) CutPLong += weight;
	if (numTrack[3] == 1) CutPLong2 += weight*weight;

      }


      if(DielecCut){
	h_Diele->Fill((*mep1)[nv],weight);
	if( numTrack[3] == 1) h_DieleLong->Fill((*mep1)[nv],weight);
	if( numTrack[3] == 1) h_MassDie->Fill((*mmass)[nv],(*mep1)[nv],weight);
	if(mep1->at(nv) > DieleLow && mep1->at(nv) < DieleHigh) continue;
	CutDielec += weight;
	CutDielec += weight*weight;
	if(numTrack[3] == 1) CutDielecLong += weight;
	if(numTrack[3] == 1) CutDielecLong2 += weight*weight;

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
	if (numTrack[3] == 1 && saveTree){ 
	  v_weight = weight;
	  v0_mmass->push_back(mmass->at(nv));
	  t1.Fill();
	}
	if(mmass->at(nv) <= MassCutLow && mmass->at(nv) >= MassCutHigh) continue;     
	CutMass += weight;
	if(numTrack[3] == 1) CutMassLong += weight;	
      }


      if(numTrack[3] == 1) h_massFinal->Fill((*mmass)[nv],weight);
      if(numTrack[3] == 1) h_PmMassFinal->Fill((*mmass)[nv],(*pm)[nv],weight);

    }

  }


  if(saveTree) t1.Write();
  if(PlotMassReso) h_MassReso->Write();
  if(PlotMuonP){
    h_mpx->Write();
    h_mpy->Write();
    h_mpz->Write();
  }
  if(MassPho) h_massLongPho->Write();
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
  h_MassDie->Write();

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

  float Nmuons = 0;
  //Nmuons=weightsum;
  if(WeightSum > 0) Nmuons=WeightSum;
  else Nmuons=weightsum; 

  std::cout<<" "<<std::endl;
  printf("\n");
  printf("\\begin{table}[h] \n");
  printf("\\begin{center} \n");
  printf("\\caption{} \n");
  printf("\\begin{tabular}{l r r r r} \n");
  printf("\\hline \n");
  printf("Cut & No of Frames  & Efficiency & Step Effiency & \\\\ \n");
  printf("\\hline \n");
  printf("Generated Number of muon decays & %2.3e \\pm %2.3e & - && \\\\ \n",Nmuons,TMath::Sqrt(weightsum2));
  printf("\\hline \n"); 
  printf("$\\geq$1 vertex  & %2.3e & %2.3e && \\\\ \n",Cut1vtx,Cut1vtx/Nmuons);
  printf("True vtx within acceptance  &  %2.3e  & %2.3e & %2.3f & \\\\ \n",CutTrueVtxAccp,CutTrueVtxAccp/(float)Nmuons, CutTrueVtxAccp/(float)Cut1vtx);
  printf("\\hline \n"); 
  if(ChiCut){
    if(CutChi/Nmuons > 0.01) printf("$\\chi^2 <$ %2d All Tracks & %2.3e \\pm %2.3e & %2.3f  & %2.3f & \\\\ \n",ChiCutValue, CutChi,CutChi2,CutChi/(float)Nmuons, CutChi/(float)CutTrueVtxAccp);
    else  printf("$\\chi^2 <$ %2d All Tracks & %2.3e \\pm %2.3e & %2.3e  & %2.3f & \\\\ \n",ChiCutValue, CutChi,CutChi2,CutChi/(float)Nmuons, CutChi/(float)CutTrueVtxAccp);
    if(CutChiLong/Nmuons > 0.01) printf("$\\chi^2 <$ %2d Long Tracks & %2.3e \\pm %2.3e & %2.3f  & %2.3f & \\\\ \n",ChiCutValue, CutChiLong,CutChiLong2,CutChiLong/(float)Nmuons, CutChiLong/(float)CutTrueVtxAccp);
    else printf("$\\chi^2 <$ %2d Long Tracks & %2.3e \\pm %2.3e  & %2.3e  & %2.3f & \\\\ \n",ChiCutValue, CutChiLong,CutChiLong2,CutChiLong/(float)Nmuons, CutChiLong/(float)CutTrueVtxAccp);}
  if(TargetCut && ChiCut){
    if(CutTarget/Nmuons > 0.01) printf("Vertex target distance $<$ %2d ~mm All tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTarget,CutTarget/(float)Nmuons,CutTarget/(float)CutChi);
    else printf("Vertex target distance $<$ %2d ~mm All tracks   & %2.3e & %2.3e & %2.3f & \\\\ \n",TargetCutValue, CutTarget,CutTarget/(float)Nmuons,CutTarget/(float)CutChi);
    if(CutTargetLong/Nmuons > 0.01) printf("Vertex target distance $<$ %2d ~mm Long tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTargetLong,CutTargetLong/(float)Nmuons,CutTargetLong/(float)CutChiLong);
    else printf("Vertex target distance $<$ %2d ~mm Long tracks   & %2.3e & %2.3e & %2.3f & \\\\ \n",TargetCutValue, CutTargetLong,CutTargetLong/(float)Nmuons,CutTargetLong/(float)CutChiLong);}
  if(TargetCut && !ChiCut){
    if(CutTarget/Nmuons > 0.01) printf("Vertex target distance $<$ %2d ~mm All tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTarget,CutTarget/(float)Nmuons,CutTarget/(float)CutTrueVtxAccp);
    else printf("Vertex target distance $<$ %2d ~mm All tracks   & %2.3e & %2.3e & %2.3f & \\\\ \n",TargetCutValue, CutTarget,CutTarget/(float)Nmuons,CutTarget/(float)CutTrueVtxAccp);
    if(CutTarget/Nmuons > 0.01) printf("Vertex target distance $<$ %2d ~mm Long tracks   & %2.3e & %2.3f & %2.3f & \\\\ \n",TargetCutValue, CutTargetLong,CutTargetLong/(float)Nmuons,CutTargetLong/(float)CutTrueVtxAccp);
    else printf("Vertex target distance $<$ %2d ~mm Long tracks   & %2.3e & %2.3e & %2.3f & \\\\ \n",TargetCutValue, CutTargetLong,CutTargetLong/(float)Nmuons,CutTargetLong/(float)CutTrueVtxAccp);}
  if(MomentumCut && !TargetCut){
    if(CutP/Nmuons > 0.01) printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e \\pm %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutP,CutP2, CutP/(float)Nmuons, CutP/(float)CutChi);
    else printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e \\pm %2.3e & %2e & %2.3e & \\\\ \n", MomentumCutValue, CutP,CutP2, CutP/(float)Nmuons, CutP/(float)CutChi);
    if(CutP/Nmuons > 0.01) printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e \\pm %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutPLong,CutPLong2, CutPLong/(float)Nmuons, CutP/(float)CutChiLong);
    else printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e \\pm %2.3e & %2e & %2.3e & \\\\ \n", MomentumCutValue, CutPLong,CutPLong2, CutPLong/(float)Nmuons, CutP/(float)CutChiLong);}
  if(MomentumCut && TargetCut){
    if(CutP/Nmuons > 0.01) printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutTarget);
    else printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2e & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutTarget);
    if(CutP/Nmuons > 0.01) printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutTargetLong);
    else printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutTargetLong);}
  if(MomentumCut && !TargetCut && !ChiCut){
    if(CutP/Nmuons > 0.01) printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutTrueVtxAccp);
    else printf("3-track system momentum $<$ %2d ~MeV All tracks & %2.3e & %2e & %2.3e & \\\\ \n", MomentumCutValue, CutP, CutP/(float)Nmuons, CutP/(float)CutTrueVtxAccp);
    if(CutP/Nmuons > 0.01) printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutTrueVtxAccp);
    else printf("3-track system momentum $<$ %2d ~MeV Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n", MomentumCutValue, CutPLong, CutPLong/(float)Nmuons, CutP/(float)CutTrueVtxAccp);}
  if(DielecCut && MomentumCut){
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e \\pm %2.3e& %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec2, CutDielec/(float)Nmuons, CutDielec/(float)CutP);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e \\pm %2.3e& %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec2, CutDielec/(float)Nmuons, CutDielec/(float)CutP);
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e \\pm %2.3e& %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong,CutDielecLong2, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutPLong);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e \\pm %2.3e& %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong,CutDielecLong2, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutPLong);}
  if(DielecCut && !MomentumCut && TargetCut){
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutTarget);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutTarget);
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutTargetLong);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutTargetLong);}
  if(DielecCut && !MomentumCut && !TargetCut && CutChi){
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutChi);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutChi);
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutChiLong);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutChiLong);}
  if(DielecCut && !MomentumCut && !TargetCut && !CutChi){
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutTrueVtxAccp);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielec, CutDielec/(float)Nmuons, CutDielec/(float)CutTrueVtxAccp);
    if(CutDielec/Nmuons > 0.01) printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutTrueVtxAccp);
    else printf("$m_{ee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",DieleLow, DieleHigh, CutDielecLong, CutDielecLong/(float)Nmuons, CutDielecLong/(float)CutTrueVtxAccp);}
  if(MassCut && DielecCut){
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutDielec);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutDielec);
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutDielecLong);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutDielecLong);}
  if(MassCut && !DielecCut && MomentumCut){
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutP);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutP);
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutPLong);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutPLong);}
  if(MassCut && !DielecCut && !MomentumCut && TargetCut){
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutTarget);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutTarget);
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutTargetLong);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutTargetLong);}
  if(MassCut && DielecCut && !MomentumCut && !TargetCut && ChiCut){
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutChi);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutChi);
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutChiLong);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutChiLong);}
  if(MassCut && DielecCut && !MomentumCut && !TargetCut && !ChiCut){
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutTrueVtxAccp);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d All Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMass, CutMass/(float)Nmuons, CutMass/(float)CutTrueVtxAccp);
    if(CutMass/Nmuons > 0.01) printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2f & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutTrueVtxAccp);
    else printf("$m_{eee}$ $<$ %2d and $>$ %2d Long Tracks & %2.3e & %2e & %2.3e & \\\\ \n",MassCutLow, MassCutHigh, CutMassLong, CutMassLong/(float)Nmuons, CutMassLong/(float)CutTrueVtxAccp);}
  printf("\\hline \n");
  printf("\\hline \n"); 
  printf("\\end{tabular} \n");
  printf("\\end{center} \n");
  printf("\\end{table} \n");
 

  fileout.Close();
}
