#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TRandom3.h"
#include <iostream>


void test(){

  //0.041801
  TRandom3 gen ;

  TH1F *h = new TH1F("h", "h", 1000,0,0.0717107);
  int n=100000000;
  for( int i=0;i<n;i++){
    h->Fill(gen.Gaus(0.0248766297491, 0.00846550838809));
  }
  h->Draw();
  TF1  *f1 = new TF1("f1","gaus");
  h->Fit(f1);

   // for( int i=200;i<600;i++){
   //   std::cout<<i<<" "<< h->GetBinLowEdge(i)<<std::endl;
   // }

  double en = h->GetEntries();
  double en2 = h->Integral(121,583);
  std::cout<<en2/en*100<<std::endl;
  std::cout<<h->GetBinCenter(356)<<std::endl;
  std::cout<<h->GetBinLowEdge(584)<<std::endl;

}
