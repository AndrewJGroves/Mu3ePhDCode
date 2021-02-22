#include "TMath.h"
#include <vector>
#include <iostream>
#include "TRandom3.h"
#include <numeric>


void BR(){
  double BR_IC = 3.4E-5;
  int BR_M = 1;
  TRandom3 gen;
  gen.SetSeed(0);
  int n1 = 2e7;

  std::vector <double> ic1; 
  std::vector <double> ic2; 
  std::vector <double> ic3; 
  std::vector <double> ic4; 

  for(int p=0 ; p<n1 ;p++){
    double n = gen.Poisson(5);

    for ( int i = 0 ; i < n ; i++){
      double BR_tot = (TMath::Factorial(n)/(TMath::Factorial(i)*TMath::Factorial(n-i)))*TMath::Power(BR_IC,i)*TMath::Power(BR_M,n-i);
      if (i == 1) ic1.push_back(BR_tot);
      if (i == 2) ic2.push_back(BR_tot);
      if (i == 3) ic3.push_back(BR_tot);
      if (i == 4) ic4.push_back(BR_tot);

    }
  }
  double test = 0;
  double meanic1 = std::accumulate(ic1.begin(),ic1.end(),test)/ic1.size();
  double meanic2 = std::accumulate(ic2.begin(),ic2.end(),test)/ic2.size();
  double meanic3 = std::accumulate(ic3.begin(),ic3.end(),test)/ic3.size();
  double meanic4 = std::accumulate(ic4.begin(),ic4.end(),test)/ic4.size();

  printf("BR 1 IC %3.2e \n",meanic1);
  printf("BR 2 IC %3.2e \n",meanic2);
  printf("BR 3 IC %3.2e \n",meanic3);
  printf("BR 4 IC %3.2e \n",meanic4);


}
