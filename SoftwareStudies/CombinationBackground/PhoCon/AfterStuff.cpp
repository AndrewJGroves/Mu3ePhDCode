
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>

std::vector<int> getTrackType(double hit1, double hit2, double hit3){
  int trlong = 0, trshort = 0, long3 =0, long2 =0, long1 =0, long0=0;
  if (hit1 <= 4) trshort += 1;
  else trlong += 1;
  if (hit2 <= 4) trshort += 1;
  else trlong += 1;
  if (hit3 <= 4) trshort += 1;
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


void AfterStuff(){
  TFile *f = new TFile("../RootFiles/Rad40/RadAll.root","READ");
  TTree *t1 = (TTree*)f->Get("t1");

  TFile fileout("RadAll.root","RECREATE");
  TH1::SetDefaultSumw2();

 //-------------------Cut Scan
  int basechi2 = 30;
  int basepm = 8;
  int basetardist = 3;
  bool CutStudy=true;
  const int nCut1=15;
  Double_t chicut[]={60,55,50,45,40,35,30,28,26,24,22,20,15,10,5};
  //const int nCut1=chicut.size()-1;
  double chiallF=0,PDchiallF=0,DchiallF=0,PchiallF=0;
  double chiall[nCut1]={0};
  double PDchiall[nCut1]={0};
  double Dchiall[nCut1]={0};
  double Pchiall[nCut1]={0};

  const int nCut2=nCut1;
  Double_t pcut[]={16,14,12,10,9,8,7,6,5.5,5,4,3,2,1,0};
  double pF=0,pChiF=0,pDF=0,pChiDF=0;
  double p[nCut2]={0};
  double pChi[nCut2]={0};
  double pD[nCut2]={0};
  double pChiD[nCut2]={0};

  Double_t dcut[]={10,9,8,7,6,5,4,3,2.5,2,1.7,1.5,1,0.5,0};
  double dF=0,dChiF=0,dPF=0,dPChiF=0;
  double d[nCut2]={0};
  double dChi[nCut2]={0};
  double dP[nCut2]={0};
  double dPChi[nCut2]={0};

  Double_t masscut[]={95,97,99,101,103,104,105,106,107,109,111,113,115,116,117};
  double massF=0;
  double massCuts[nCut2]={0};

  Int_t nvert;
  vector<double> *px1=0,*py1=0,*pz1=0;
  vector<double> *px2=0,*py2=0,*pz2=0;
  vector<double> *px3=0,*py3=0,*pz3=0;
  vector<double> *true_px1=0,*true_py1=0,*true_pz1=0;
  vector<double> *true_px2=0,*true_py2=0,*true_pz2=0;
  vector<double> *true_px3=0,*true_py3=0,*true_pz3=0;
  vector<double> *chi2=0,*targetdist=0;
  vector<int> *type1=0,*type2=0,*type3=0;
  vector<int> *mid1=0,*mid2=0,*mid3=0;
  vector<int> *id1=0,*id2=0,*id3=0;
  vector<double> *nhit1=0,*nhit2=0,*nhit3=0;

  t1->SetBranchAddress("nhit1",&nhit1);
  t1->SetBranchAddress("nhit2",&nhit2);
  t1->SetBranchAddress("nhit3",&nhit3);
  t1->SetBranchAddress("px1",&px1);
  t1->SetBranchAddress("py1",&py1);
  t1->SetBranchAddress("pz1",&pz1);
  t1->SetBranchAddress("px2",&px2);
  t1->SetBranchAddress("py2",&py2);
  t1->SetBranchAddress("pz2",&pz2);
  t1->SetBranchAddress("px3",&px3);
  t1->SetBranchAddress("py3",&py3);
  t1->SetBranchAddress("pz3",&pz3);
  t1->SetBranchAddress("true_px1",&true_px1);
  t1->SetBranchAddress("true_py1",&true_py1);
  t1->SetBranchAddress("true_pz1",&true_pz1);
  t1->SetBranchAddress("true_px2",&true_px2);
  t1->SetBranchAddress("true_py2",&true_py2);
  t1->SetBranchAddress("true_pz2",&true_pz2);
  t1->SetBranchAddress("true_px3",&true_px3);
  t1->SetBranchAddress("true_py3",&true_py3);
  t1->SetBranchAddress("true_pz3",&true_pz3);
  t1->SetBranchAddress("chi2",&chi2);
  t1->SetBranchAddress("targetdist",&targetdist);
  t1->SetBranchAddress("type1",&type1);
  t1->SetBranchAddress("type2",&type2);
  t1->SetBranchAddress("type3",&type3);
  t1->SetBranchAddress("mid1",&mid1);
  t1->SetBranchAddress("mid2",&mid2);
  t1->SetBranchAddress("mid3",&mid3);
  t1->SetBranchAddress("id1",&id1);
  t1->SetBranchAddress("id2",&id2);
  t1->SetBranchAddress("id3",&id3);
  t1->SetBranchAddress("nvert", &nvert);   

  TH1F *h_PhoTheta = new TH1F("h_PhoTheta", "PhoTheta", 100,-10,10);
  TH1F *h_PhoPhi = new TH1F("h_PhoPhi", "PhoPho", 100,-10,10);
  TH1F *h_EP_true = new TH1F("h_EPt_true", "EPt true", 1000,0,200);
  TH1F *h_EP = new TH1F("h_EPt", "EPt", 1000,0,200);
  TH2F *h_Pth= new TH2F("h_Pth", "Pth", 1000,0,200,100,-10,10);
  TH1F *h_Reso = new TH1F("h_Reso", "Reso", 100,-10,10);
  TH1F *h_Reso40 = new TH1F("h_Reso40", "Reso40", 100,-10,10);
  TH2F *h_PPhoMass = new TH2F("h_PPhoMass", "Momentum Vs Mass", 1000,0,70,1000,0,200);

  TH1F *h_massLong = new TH1F("h_massLong", "Mass long", 1000,0,200);
  TH1F *h_chi2Long = new TH1F("h_chi2Long", "Chi2 long", 1000,0,100);
  TH1F *h_targetLong = new TH1F("h_targetLong", "Distance to target long", 2000,-100,100);
  TH1F *h_tmomLong = new TH1F("h_tmomLong", "Absolute momentum long", 1000,0,100);
  TH1F *h_mass = new TH1F("h_mass", "Mass", 1000,0,200);
  TH1F *h_chi2 = new TH1F("h_chi2", "Chi2", 1000,0,100);
  TH1F *h_target = new TH1F("h_target", "Distance to target", 2000,-100,100);
  TH1F *h_tmom = new TH1F("h_tmom", "Absolute momentum", 1000,0,100);

  int count_p=0,count_d=0,count_chi=0;

  int masswindow = 0;
  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    //if (i > 1e6) break;
    t1->GetEntry(i);
    double weight = 1;
    for(int nv=0; nv<(int)px1->size() ; nv++){
      std::vector<int> numTrack( getTrackType((*nhit1)[nv],(*nhit2)[nv],(*nhit3)[nv]) );

      TLorentzVector ep1;
      TLorentzVector ep2;
      TLorentzVector ep3;
      TLorentzVector ep1True;
      TLorentzVector ep2True;
      TLorentzVector ep3True;
      ep1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))+0.511*0.511);
      ep2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))+0.511*0.511);
      ep3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))+0.511*0.511);
      ep1True.SetPxPyPzE(true_px1->at(nv),true_py1->at(nv),true_pz1->at(nv),TMath::Sqrt(true_px1->at(nv)*true_px1->at(nv)+true_py1->at(nv)*true_py1->at(nv)+true_pz1->at(nv)*true_pz1->at(nv))+0.511*0.511);
      ep2True.SetPxPyPzE(true_px2->at(nv),true_py2->at(nv),true_pz2->at(nv),TMath::Sqrt(true_px2->at(nv)*true_px2->at(nv)+true_py2->at(nv)*true_py2->at(nv)+true_pz2->at(nv)*true_pz2->at(nv))+0.511*0.511);
      ep3True.SetPxPyPzE(true_px3->at(nv),true_py3->at(nv),true_pz3->at(nv),TMath::Sqrt(true_px3->at(nv)*true_px3->at(nv)+true_py3->at(nv)*true_py3->at(nv)+true_pz3->at(nv)*true_pz3->at(nv))+0.511*0.511);

      TLorentzVector muon;
      TLorentzVector truemuon;
      muon=ep1+ep2+ep3;
      truemuon=ep1True+ep2True+ep3True;

if(CutStudy){
	chiallF += weight;
	pF += weight;
	dF += weight;
	if(abs(targetdist->at(nv)) < basetardist){
	  DchiallF += weight;
	  pDF += weight;
	}
	if(abs(targetdist->at(nv)) < basetardist && muon.P() < basepm && chi2->at(nv) < basechi2) massF += weight;
	if(abs(targetdist->at(nv)) < basetardist && muon.P() < basepm) PDchiallF += weight;
	if(muon.P() < basepm && chi2->at(nv) < basechi2) dPChiF += weight;
	if(abs(targetdist->at(nv)) < basetardist && chi2->at(nv) < basechi2) pChiDF += weight;
	if(muon.P() < basepm){
	  PchiallF += weight;
	  dPF += weight;
	}
	if(chi2->at(nv) < basechi2){
	  dChiF += weight;
	  pChiF += weight;
	}

	int nCut = nCut1;
	//std::cout<<"nCut1 "<<nCut<<std::endl;
	for(int i=0; i < nCut ; i++){
	  if(abs(targetdist->at(nv)) < basetardist && muon.P() < basepm && chi2->at(nv) < basechi2){
	    if(muon.M() > masscut[i]){
	      // std::cout<<i<<" "<<masscut[i]<<" "<<mmass->at(nv)<<" "<<weight<<" "<<massCuts[i]<<std::endl;
	      massCuts[i] += weight;}
	  }
	  //std::cout<<i<<std::endl;
	  if(muon.P() < pcut[i]) {p[i] += weight;}
	  if(abs(targetdist->at(nv)) < dcut[i]) {d[i] += weight;}
	  if(chi2->at(nv) < chicut[i]) {chiall[i] += weight;}
	  if(abs(targetdist->at(nv)) < basetardist){
	    if(chi2->at(nv) < chicut[i]) {Dchiall[i] += weight;}
	    if(muon.P() < pcut[i]) {pD[i] += weight;}
	  }
	  if(abs(targetdist->at(nv)) < basetardist && muon.P() < basepm){
	    if(chi2->at(nv) < chicut[i]) {PDchiall[i] += weight;}
	  }
	  if(muon.P() < basepm){
	    if(chi2->at(nv) < chicut[i]) {Pchiall[i] += weight;}
	    if(abs(targetdist->at(nv)) < dcut[i]){ dP[i] += weight;}
	  }
	  if(chi2->at(nv) < basechi2){
	    if(abs(targetdist->at(nv)) < dcut[i]) { dChi[i] += weight;}
	    if(muon.P() < pcut[i]) {pChi[i] += weight;}
	  }
	  if(chi2->at(nv) < basechi2 && abs(targetdist->at(nv)) < basetardist){
	    if(muon.P() < pcut[i]) {pChiD[i] += weight;}
	  }
	  if(chi2->at(nv) < basechi2 && muon.P() < basepm){
	    if(abs(targetdist->at(nv)) < dcut[i]) {dPChi[i] += weight;}
	  }
	}
    
      }
      if (numTrack[3] == 1) h_chi2Long->Fill((*chi2)[nv],weight);
      h_chi2->Fill((*chi2)[nv],weight);
      if(chi2->at(nv) > 15) continue;

      TLorentzVector pho;
      TLorentzVector phoTrue;
      int first = 0;
      int second = 0;
      if(mid1->at(nv)==mid2->at(nv) && id1->at(nv)!=id2->at(nv)){
	pho=ep1+ep2;
	phoTrue=ep1True+ep2True;
	first=+1;

      }
      if(mid1->at(nv)==mid3->at(nv)&& id1->at(nv)!=id3->at(nv)){
	pho=ep1+ep3;
	phoTrue=ep1True+ep3True;
	first=+1;
      }
      if(mid2->at(nv)==mid3->at(nv)&& id2->at(nv)!=id3->at(nv)){
	pho=ep2+ep3;
	phoTrue=ep2True+ep3True;
	second=+1;
      }
      h_PhoTheta->Fill(pho.Theta()); 
      h_PhoPhi->Fill(pho.Phi()); 
      h_EP_true->Fill(phoTrue.P()); 
      h_EP->Fill(pho.P()); 
      h_Pth->Fill(phoTrue.P(),phoTrue.Py()/phoTrue.Pz());
      h_Reso->Fill(phoTrue.P()-pho.P());
      count_chi += 1;

      if (numTrack[3] == 1) h_targetLong->Fill((*targetdist)[nv],weight);
      h_target->Fill((*targetdist)[nv],weight);
      if (abs(targetdist->at(nv)) > 1){ continue; }


      count_d += 1;

      h_PPhoMass->Fill(pho.P(),muon.M());
      if(phoTrue.P() >= 40){
	h_Reso40->Fill(phoTrue.P()-pho.P());
	h_mass->Fill(muon.M());
	h_tmom->Fill(muon.P());
      }

      h_tmom->Fill(muon.P(),weight);
      if (numTrack[3] == 1) h_tmomLong->Fill(muon.P(),weight);
      if(muon.P() > 6) continue;
      count_p += 1;

      h_mass->Fill(muon.M(),weight);
      if (numTrack[3] == 1) {
	h_massLong->Fill(muon.M(),weight);
      }

    }

  }

  printf(" $\\chi^2 < 30 $  & %2d & \\\\ \n",count_chi);
  printf("vertex target distance $<$3~mm    & %2d &   \\\\ \n",count_d);
  printf("3-track system momentum $<$8~MeV  & %2d &  \\\\ \n",count_p);
  
  h_chi2->Write();
  h_target->Write();
  h_tmom->Write();
  h_mass->Write();
  h_chi2Long->Write();
  h_targetLong->Write();
  h_tmomLong->Write();
  h_massLong->Write();
  h_Reso40->Write();
  h_mass->Write();
  h_tmom->Write();
  h_PPhoMass->Write();
  h_Pth->Write();
  h_PhoTheta->Write(); 
  h_PhoPhi->Write(); 
  h_EP_true->Write(); 
  h_EP->Write(); 
  h_Reso->Write();
if(CutStudy){
  Double_t chiall2[nCut1]={0};
  Double_t PDchiall2[nCut1]={0};
  Double_t Dchiall2[nCut1]={0};
  Double_t Pchiall2[nCut1]={0};
  //std::cout<<"chi all "<<chiallF<<std::endl;
  std::cout<<"---------------------------"<<std::endl;
  std::cout<<"Chi 2 "<<std::endl;
  for(int i=0; i < nCut1; i++){
    if(chicut[i] == basechi2){
      std::cout<<"No Cut eff at "<<chicut[i]<<" is "<<1-chiall[i]/chiallF<<std::endl;
      std::cout<<"Chi cut eff at "<<chicut[i]<<" is "<<1-Pchiall[i]/PchiallF<<std::endl;
      std::cout<<"Tar Dist cut eff at "<<chicut[i]<<" is "<<1-Dchiall[i]/DchiallF<<std::endl;
      std::cout<<"Both Cut eff at "<<chicut[i]<<" is "<<1-PDchiall[i]/PDchiallF<<std::endl;
    }
    //std::cout<<chiall[i]/chiallF<<std::endl;
    chiall2[i] = chiall[i]/chiallF;
    PDchiall2[i] = PDchiall[i]/PDchiallF;
    Dchiall2[i] = Dchiall[i]/DchiallF;
    Pchiall2[i] = Pchiall[i]/PchiallF;
  } 
  std::cout<<"chiallF="<<chiallF<<std::endl;
  std::cout<<"chiall=[";
  for(int i=0; i < nCut1; i++){
    std::cout<<chiall[i]<<",";
  }
  std::cout<<"]"<<std::endl;

  TGraph* chiNoCut = new TGraph(nCut1,chicut,chiall2);
  chiNoCut->SetTitle("Chi2 no other cut");
  chiNoCut->GetYaxis()->SetTitle("Efficiency");
  chiNoCut->GetXaxis()->SetTitle("#chi^{2}");
  TGraph* chiPCut = new TGraph(nCut1,chicut,Pchiall2);
  chiPCut->SetTitle("Chi2 and Momentum cut");
  chiPCut->GetXaxis()->SetTitle("#chi^{2}");
  chiPCut->GetYaxis()->SetTitle("Efficiency");
  TGraph* chiPDCut = new TGraph(nCut1,chicut,PDchiall2);
  chiPDCut->SetTitle("Chi2 and Momentum and distance cut");
  chiPDCut->GetXaxis()->SetTitle("#chi^{2}");
  chiPDCut->GetYaxis()->SetTitle("Efficiency");
  TGraph* chiDCut = new TGraph(nCut1,chicut,Dchiall2);
  chiDCut->SetTitle("Chi2 and distance cut");
  chiDCut->GetXaxis()->SetTitle("#chi^{2}");
  chiDCut->GetYaxis()->SetTitle("Efficiency");

  Double_t p2[nCut2]={0};
  Double_t pChi2[nCut2]={0};
  Double_t pD2[nCut2]={0};
  Double_t pChiD2[nCut2]={0};
  //std::cout<<pDF<<std::endl;
  std::cout<<"---------------------------"<<std::endl;
  std::cout<<"Momentum "<<std::endl;
  for(int i=0; i < nCut2; i++){
    if(pcut[i] == basepm){
      std::cout<<"No Cut eff at "<<pcut[i]<<" is "<<1-p[i]/pF<<std::endl;
      std::cout<<"Chi cut eff at "<<pcut[i]<<" is "<<1-pChi[i]/pChiF<<std::endl;
      std::cout<<"Tar Dist cut eff at "<<pcut[i]<<" is "<<1-pD[i]/pDF<<std::endl;
      std::cout<<"Both Cut eff at "<<pcut[i]<<" is "<<1-pChiD[i]/pChiDF<<std::endl;
    }
    p2[i] = p[i]/pF;
    pChi2[i] = pChi[i]/pChiF;
    pD2[i] = pD[i]/pDF;
    pChiD2[i] = pChiD[i]/pChiDF;

  } 
  std::cout<<"pChiDF="<<pF<<std::endl;
  std::cout<<"pChiD=[";
  for(int i=0; i < nCut1; i++){
    std::cout<<pChiD[i]<<",";
  }
  std::cout<<"]"<<std::endl;


  TGraph* PNoCut = new TGraph(nCut2,pcut,p2);
  PNoCut->SetTitle("P no other cut");
  PNoCut->GetYaxis()->SetTitle("Efficiency");
  PNoCut->GetXaxis()->SetTitle("P");
  TGraph* PCCut = new TGraph(nCut2,pcut,pChi2);
  PCCut->SetTitle("P and Chi cut");
  PCCut->GetYaxis()->SetTitle("Efficiency");
  PCCut->GetXaxis()->SetTitle("P");
  TGraph* PDCut = new TGraph(nCut2,pcut,pD2);//broke
  PDCut->SetTitle("P and distance cut");
  PDCut->GetYaxis()->SetTitle("Efficiency");
  PDCut->GetXaxis()->SetTitle("P");
  TGraph* PDCCut = new TGraph(nCut2,pcut,pChiD2);
  PDCCut->SetTitle("P and Momentum and distance cut");
  PDCCut->GetYaxis()->SetTitle("Efficiency");
  PDCCut->GetXaxis()->SetTitle("P");

  Double_t d2[nCut2]={0};
  Double_t dChi2[nCut2]={0};
  Double_t dP2[nCut2]={0};
  Double_t dPChi2[nCut2]={0};
  std::cout<<"---------------------------"<<std::endl;
  std::cout<<"Target distance "<<std::endl;
  for(int i=0; i < nCut2; i++){
    if(dcut[i] == basetardist){
      std::cout<<"No Cut eff at "<<dcut[i]<<" is "<<1-d[i]/dF<<std::endl;
      std::cout<<"Chi cut eff at "<<dcut[i]<<" is "<<1-dChi[i]/dChiF<<std::endl;
      std::cout<<"Mom cut eff at "<<dcut[i]<<" is "<<1-dP[i]/dPF<<std::endl;
      std::cout<<"Both Cut eff at "<<dcut[i]<<" is "<<1-dPChi[i]/dPChiF<<std::endl;
    }
    d2[i] = d[i]/dF;
    dChi2[i] = dChi[i]/dChiF;
    dP2[i] = dP[i]/dPF;
    dPChi2[i] = dPChi[i]/dPChiF;
  } 
  std::cout<<"dChiF="<<dChiF<<std::endl;
  std::cout<<"dChi=[";
  for(int i=0; i < nCut2; i++){
    std::cout<<dChi[i]<<",";
  }
  std::cout<<"]"<<std::endl;

  TGraph* DNoCut = new TGraph(nCut2,dcut,d2);
  DNoCut->SetTitle("D no other cut");
  DNoCut->GetYaxis()->SetTitle("Efficiency");
  DNoCut->GetXaxis()->SetTitle("Target distance");
  TGraph* DPCut = new TGraph(nCut2,dcut,dP2);
  DPCut->SetTitle("D with momentum cut");
  DPCut->GetYaxis()->SetTitle("Efficiency");
  DPCut->GetXaxis()->SetTitle("Target distance");
  TGraph* DPCCut = new TGraph(nCut2,dcut,dPChi2);
  DPCCut->SetTitle("D wiht momentum and Chi cut");
  DPCCut->GetYaxis()->SetTitle("Efficiency");
  DPCCut->GetXaxis()->SetTitle("Target distance");
  TGraph* DCCut = new TGraph(nCut2,dcut,dChi2);
  DCCut->SetTitle("D with chi cut");
  DCCut->GetYaxis()->SetTitle("Efficiency");
  DCCut->GetXaxis()->SetTitle("Target distance");

  Double_t massCuts2[nCut2]={0};
  std::cout<<"---------------------------"<<std::endl;
  std::cout<<"Mass "<<std::endl;
  for(int i=0; i < nCut2; i++){
    massCuts2[i] =massCuts[i]/massF;
  } 
  std::cout<<"massF="<<massF<<std::endl;
  std::cout<<"massCuts=[";
  for(int i=0; i < nCut2; i++){
    std::cout<<massCuts[i]<<",";
  }
  std::cout<<"]"<<std::endl;
  TGraph* massEff = new TGraph(nCut2,masscut,massCuts2);
  massEff->SetTitle("Mass with all cuts");
  massEff->GetYaxis()->SetTitle("Efficiency");
  massEff->GetXaxis()->SetTitle("Mass");

  chiNoCut->Write();
  chiPCut->Write();
  chiPDCut->Write();
  chiDCut->Write();
  DNoCut->Write();
  DPCut->Write();
  DPCCut->Write();
  DCCut->Write();
  PNoCut->Write();
  PCCut->Write();
  PDCut->Write();
  PDCCut->Write();
  massEff->Write();

  }

  fileout.Close();

}
