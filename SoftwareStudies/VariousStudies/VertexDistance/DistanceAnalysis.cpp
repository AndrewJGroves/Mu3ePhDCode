#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <vector>


std::vector<double> circle(double px,double py,double verx, double very, double rad){
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

std::vector<int> getTrackType(int nhit1, int nhit2, int nhit3){
  int trlong = 0, trshort = 0, long3 =0, long2 =0, long1 =0, long0=0;
  if (nhit1 <= 4) trshort += 1;
  else trlong += 1;
  if (nhit2 <= 4) trshort += 1;
  else trlong += 1;
  if (nhit3 <= 4) trshort += 1;
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

void test(){
  TFile *f = new TFile("/hepstore/agroves/MyStudies/SoftwareStudies/RootFiles/ICmic.root","READ");//test1.root","READ");
  TTree *t1 = (TTree*)f->Get("t1");
  TFile fileout("plots.root","RECREATE");

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



  double icpp = 0;
  double icpn = 0;
  Long64_t n = t1->GetEntries();
  std::cout<<"Number of entries "<< n << std::endl;
  for( Long64_t i=0 ; i<n ; i++){
    if (i % 100000 == 0) std::cout<<"Entry " << i << std::endl;
    t1->GetEntry(i);
    for( int nv=0; nv < (int)type1->size(); nv ++){
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


      e1.SetPxPyPzE(px1->at(nv),py1->at(nv),pz1->at(nv),TMath::Sqrt(emass*emass+(px1->at(nv)*px1->at(nv)+py1->at(nv)*py1->at(nv)+pz1->at(nv)*pz1->at(nv))));
      e2.SetPxPyPzE(px2->at(nv),py2->at(nv),pz2->at(nv),TMath::Sqrt(emass*emass+(px2->at(nv)*px2->at(nv)+py2->at(nv)*py2->at(nv)+pz2->at(nv)*pz2->at(nv))));
      e3.SetPxPyPzE(px3->at(nv),py3->at(nv),pz3->at(nv),TMath::Sqrt(emass*emass+(px3->at(nv)*px3->at(nv)+py3->at(nv)*py3->at(nv)+pz3->at(nv)*pz3->at(nv))));


       double t1 = t0_mc1->at(nv)-((event)*50);
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
	if(t0_tl1->at(nv) != -1 && t0_tl1->at(nv) < 47 && t0_tl1->at(nv) > 0.5) h_time->Fill(TMath::Abs(t1-t0_tl1->at(nv)),diff);
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


	// std::cout<<"\\hline"<<std::endl;
      //std::cout<<"Distance to IC & "<<diff<<"& & \\\\"<<std::endl;
      	// // std::cout<<"run = "<<run<<std::endl;
      	// // std::cout<<"event = "<<event<<std::endl;
	// // std::cout<<"Theta "<<e1.Theta()<<" "<<e2.Theta()<<" "<<e3.Theta()<<std::endl;
	// std::cout<<"\\hline"<<std::endl;
      	// std::cout<<"& "<<type1->at(nv)<<"& "<<type2->at(nv)<<"& "<<type3->at(nv)<<" \\\\ "<<std::endl;
	// std::cout<<"\\hline"<<std::endl;
      	// std::cout<<"Number of hits & "<<nhit1->at(nv)<<"& "<<nhit2->at(nv)<<"& "<<nhit3->at(nv)<<" \\\\ "<<std::endl;
      	// // std::cout<<"vtx = [ "<<vx->at(nv)<<", "<<vy->at(nv)<<", "<<vz->at(nv)<<" ] "<<std::endl;
      	// std::cou// t<<"True vetex t  "<<tv_mc1->at(nv)<<", "<<tv_mc2->at(nv)<<", "<<tv_mc3->at(nv)<<" ] "<<std::endl;
      // 	// std::cout<<"Vertex t  "<<tv_1->at(nv)<<", "<<tv_2->at(nv)<<", "<<tv_3->at(nv)<<" ]"<<std::endl;
      if(t1-t0_fb1->at(nv) > 10 && t2-t0_fb2->at(nv) > 10 && t3-t0_fb3->at(nv) > 10 && diff < 10 && t0_fb1->at(nv) != -1 && t0_fb2->at(nv) != -1 && t0_fb3->at(nv) != -1){
      	 std::cout<<"Distance to IC & "<<diff<<"& & \\\\"<<std::endl;

      	  std::cout<<"Fibre time & "<<t0_fb1->at(nv)<<"& "<<t0_fb2->at(nv)<<"&"<<t0_fb3->at(nv)<<" \\\\"<<std::endl;
      	  std::cout<<"True time & "<<t1<<"& "<<t2<<"& "<<t3<<" \\\\"<<std::endl;
      	  std::cout<<"Fibre Difference & "<<t1-t0_fb1->at(nv)<<"& "<<t2-t0_fb2->at(nv)<<"& "<<t3-t0_fb3->at(nv)<<" \\\\"<<std::endl;
      	std::cout<<" "<<std::endl;

      }
      	 // // std::cout<<"Tile "<<t0_tl1->at(nv)<<", "<<t0_tl2->at(nv)<<", "<<t0_tl3->at(nv)<<" ]"<<std::endl;
      // std::cout<<"Tile Difference = [ "<<t1-t0_tl1->at(nv)<<", "<<t2-t0_tl2->at(nv)<<", "<<t3-t0_tl3->at(nv)<<" ]"<<std::endl;
      	// // // std::cout<<"p1 = [ "<<px1->at(nv)<<", "<<py1->at(nv)<<", "<<pz1->at(nv)<<" ] "<<std::endl;
      	// // // std::cout<<"p2 = [ "<<px2->at(nv)<<", "<<py2->at(nv)<<", "<<pz2->at(nv)<<" ]"<<std::endl;
      	// // // std::cout<<"p3 = [ "<<px3->at(nv)<<", "<<py3->at(nv)<<", "<<pz3->at(nv)<<" ]"<<std::endl;
      	// std::cout<<"Radius & "<<r1->at(nv)<<"& "<<r2->at(nv)<<"& "<<r3->at(nv)<<" \\\\"<<std::endl;
      	//std::cout<<"r & "<<(TMath::Pi()*2*r1->at(nv)*0.01)/3e8<<"& "<<(TMath::Pi()*2*r2->at(nv)*0.01)/3e8<<"& "<<(TMath::Pi()*2*r3->at(nv)*0.01)/3e8<<" \\\\"<<std::endl;
      	// // std::cout<<"v1 = [ "<<true_cx1->at(nv)<<", "<<true_cy1->at(nv)<<", "<<true_cz1->at(nv)<<" ]"<<std::endl;
      	// // std::cout<<"v2 = [ "<<true_cx2->at(nv)<<", "<<true_cy2->at(nv)<<", "<<true_cz2->at(nv)<<" ]"<<std::endl;
      	// // std::cout<<"v3 = [ "<<true_cx3->at(nv)<<", "<<true_cy3->at(nv)<<", "<<true_cz3->at(nv)<<" ]"<<std::endl;
	

  

    }
  }

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
  fileout.Close();
}
