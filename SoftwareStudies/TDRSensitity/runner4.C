#include "TROOT.h"
#include "sigAna.h"
#include <iostream>
#include "TMath.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TF1.h"
#include "TVector3.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void runner4(TString input, TString path, TString output, int VertexType = -1, float Weight = -1) {
  gROOT->LoadMacro("./sigAna.C+");

  
  TString outputfile = output;//"/hepstore/agroves/MyStudies/SoftwareStudies/RootFiles/"+output;
  std::vector<TString> fnames; 
  std::ifstream file(input);
  std::string str;
  while (std::getline(file, str)) {
    TString name = TString(str);
    fnames.push_back(path+name);
  }
  
  sigAna f(fnames);
  f.setOutputFileName(outputfile);
  f.Loop(Weight,VertexType);

}
