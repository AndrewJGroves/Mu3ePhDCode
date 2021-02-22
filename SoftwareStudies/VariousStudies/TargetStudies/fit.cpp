#include "TMath.h"
#include "TH1F.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <iostream>
#include <vector>
#include <algorithm>

double R0 = 19;
double Z0 = 50;

double DistNat3(double ran1,double phi1, double ran2, double phi2, double ran3, double phi3){
  double r1 = (R0/Z0)*TMath::Abs(TMath::Abs(ran1) - Z0);
  double r2 = (R0/Z0)*TMath::Abs(TMath::Abs(ran2) - Z0);
  double r3 = (R0/Z0)*TMath::Abs(TMath::Abs(ran3) - Z0);
  double x1 = r1 * TMath::Cos(phi1);
  double x2 = r2 * TMath::Sin(phi2);
  double x3 = r3 * TMath::Sin(phi3);
  double y1 = r1 * TMath::Cos(phi1);
  double y2 = r2 * TMath::Sin(phi2);
  double y3 = r3 * TMath::Sin(phi3);
  double dist = TMath::Sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (ran1-ran2)*(ran1-ran2) );
  double dist2 = 10;
  double dist3 = 10;
  if (dist < 1){
      dist2 = TMath::Sqrt( (x1-x3)*(x1-x3) + (y1-y3)*(y1-y3) + (ran1-ran3)*(ran1-ran3) );
      dist3 = TMath::Sqrt( (x2-x3)*(x2-x3) + (y2-y3)*(y2-y3) + (ran2-ran3)*(ran2-ran3) );
  }
  if (dist2 < 1 || dist3 < 1) return 0.1;
  else return 10;
}


std::vector <double> GetDistancePoints3(double ran [], int n){
  TRandom3 gen;
  gen.SetSeed(0);
  double phi[n];
  for(int j=0; j<n ; j++){
    phi[j] = gen.Rndm()*2*M_PI;
  }
  std::vector <double> v_distance;
  for (int i = 0 ; i < n ; i++){
    for (int i1=0 ; i1 < n ; i1++){
      if (i1 <= i) continue;
      if (i1+1 >=n) break;
      v_distance.push_back(DistNat3(ran[i],phi[i],ran[i1],phi[i1],ran[i1+1],phi[i1+1]));
    }
    //std::sort(v_distance.begin(),v_distance.end());
  }
  return v_distance;
}


double DistNat(double ran1,double phi1, double ran2, double phi2){
  double r1 = (R0/Z0)*TMath::Abs(TMath::Abs(ran1) - Z0);
  double r2 = (R0/Z0)*TMath::Abs(TMath::Abs(ran2) - Z0);
  double x1 = r1 * TMath::Cos(phi1);
  double x2 = r2 * TMath::Sin(phi2);
  double y1 = r1 * TMath::Cos(phi1);
  double y2 = r2 * TMath::Sin(phi2);
  double dist = TMath::Sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (ran1-ran2)*(ran1-ran2) );
  return dist;
}


std::vector <double> GetDistancePoints(double ran [], int n){
  TRandom3 gen;
  gen.SetSeed(0);
  double phi[n];
  for(int j=0; j<n ; j++){
    phi[j] = gen.Rndm()*2*M_PI;
  }
  std::vector <double> v_distance;
  for (int i = 0 ; i < n ; i++){
    for (int i1=0 ; i1 < n ; i1++){
      if (i1 <= i) continue;
      v_distance.push_back(DistNat(ran[i],phi[i],ran[i1],phi[i1]));
    }
    //std::sort(v_distance.begin(),v_distance.end());
  }
  return v_distance;
}

void test(int n_close){
  TFile *f = new TFile("plots.root","READ");
  TH1F *hist = (TH1F*)f->Get("target");
  //double theMax = hist->GetBinContent(hist->GetMaximumBin());
  //hist->Scale((double)1/theMax);
  //hist->Draw();
  TRandom3 gen1;
  gen1.SetSeed(0);

  int n=2e7;
  double DistMIN = 1;
  int n_vertices_pass = 0;
  int N_frame_pass = 0;
  
  for(int i=0;i<n;i++){
    if (i % 10000000000000 == 0 ) std::cout<<"New frame "<<i<<std::endl;
    int n1 = gen1.Poisson(5);
    double ran[n1];
    for(int j=0; j<n1 ; j++){
      ran[j] = hist->GetRandom();
    }
    std::vector <double> dist;
    if (n_close == 2) dist = GetDistancePoints(ran,n1);
    if (n_close == 3) dist = GetDistancePoints3(ran,n1);
    int n_vertices = 0;
    for(int p=0;p<(int)dist.size();p++){
      if (dist[p] < DistMIN) n_vertices += 1; 
    }
    n_vertices_pass += n_vertices;
    if (n_vertices > 0) N_frame_pass += 1;
  }


  std::cout<<"Frames used " << n << " overplapping vertices " << n_vertices_pass << " frames in which these found " << N_frame_pass<<std::endl; 
  std::cout<<"Fraction of frames with overlapping "<< (double)N_frame_pass/(double)n<<std::endl;

}
