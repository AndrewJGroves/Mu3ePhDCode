//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul 29 15:21:18 2018 by ROOT version 6.06/08
// from TTree vertex/vertex
// found on file: vertex.root
//////////////////////////////////////////////////////////

#ifndef sigAna_h
#define sigAna_h

#include <vector>
#include <iostream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TVector3.h>
#include <TString.h>


class sigAna {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   UInt_t          ncomb;
   UInt_t          nrightchargecomb;
   UInt_t          nvert;
   UInt_t          ntwoone;
   Double_t        weight;
   vector<double>  *vx;
   vector<double>  *vy;
   vector<double>  *vz;
   vector<double>  *chi2;
   vector<double>  *true_vx;
   vector<double>  *true_vy;
   vector<double>  *true_vz;
   vector<double>  *true_mass;
   vector<double>  *true_pxm;
   vector<double>  *true_pym;
   vector<double>  *true_pzm;
   vector<double>  *guess_vx;
   vector<double>  *guess_vy;
   vector<double>  *guess_vz;
   vector<double>  *px1;
   vector<double>  *py1;
   vector<double>  *pz1;
   vector<double>  *true_px1;
   vector<double>  *true_py1;
   vector<double>  *true_pz1;
   vector<double>  *r1;
   vector<double>  *rerr21;
   vector<int>     *id1;
   vector<int>     *pid1;
   vector<int>     *type1;
   vector<int>     *mid1;
   vector<int>     *hid1;
   vector<int>     *prime1;
   vector<double>  *px2;
   vector<double>  *py2;
   vector<double>  *pz2;
   vector<double>  *true_px2;
   vector<double>  *true_py2;
   vector<double>  *true_pz2;
   vector<double>  *r2;
   vector<double>  *rerr22;
   vector<int>     *id2;
   vector<int>     *pid2;
   vector<int>     *type2;
   vector<int>     *mid2;
   vector<int>     *hid2;
   vector<int>     *prime2;
   vector<double>  *px3;
   vector<double>  *py3;
   vector<double>  *pz3;
   vector<double>  *true_px3;
   vector<double>  *true_py3;
   vector<double>  *true_pz3;
   vector<double>  *r3;
   vector<double>  *rerr23;
   vector<int>     *id3;
   vector<int>     *pid3;
   vector<int>     *type3;
   vector<int>     *mid3;
   vector<int>     *hid3;
   vector<int>     *prime3;
   vector<double>  *pxm;
   vector<double>  *pym;
   vector<double>  *pzm;
   vector<double>  *mmass;
   vector<double>  *pcoplanar;
   vector<double>  *pacoplanar;
   vector<double>  *pm;
   vector<double>  *targetdist;
   vector<double>  *mep1;
   vector<double>  *mep2;
   vector<int>     *nhit1;
   vector<int>     *nhit2;
   vector<int>     *nhit3;
   vector<int>     *nsharedhit1;
   vector<int>     *nsharedhit2;
   vector<int>     *nsharedhit3;
   vector<int>     *nsharedseg1;
   vector<int>     *nsharedseg2;
   vector<int>     *nsharedseg3;
   vector<double>  *guessx;
   vector<double>  *guessy;
   vector<double>  *guessz;
   vector<double>  *guessdist;
   vector<double>  *true_targetdist;
   vector<int>     *mc_signal;
   vector<double>  *fit_tolerance;
   vector<int>     *fit_steps;
   vector<double>  *cosalpha;
   vector<double>  *theta_kuno;
   vector<double>  *phi_kuno;


   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ncomb;   //!
   TBranch        *b_nrightchargecomb;   //!
   TBranch        *b_nvert;   //!
   TBranch        *b_ntwoone;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_chi2;   //!
   TBranch        *b_true_vx;   //!
   TBranch        *b_true_vy;   //!
   TBranch        *b_true_vz;   //!
   TBranch        *b_true_mass;   //!
   TBranch        *b_true_pxm;   //!
   TBranch        *b_true_pym;   //!
   TBranch        *b_true_pzm;   //!
   TBranch        *b_guess_vx;   //!
   TBranch        *b_guess_vy;   //!
   TBranch        *b_guess_vz;   //!
   TBranch        *b_px1;   //!
   TBranch        *b_py1;   //!
   TBranch        *b_pz1;   //!
   TBranch        *b_true_px1;   //!
   TBranch        *b_true_py1;   //!
   TBranch        *b_true_pz1;   //!
   TBranch        *b_r1;   //!
   TBranch        *b_rerr21;   //!
   TBranch        *b_id1;   //!
   TBranch        *b_pid1;   //!
   TBranch        *b_type1;   //!
   TBranch        *b_mid1;   //!
   TBranch        *b_hid1;   //!
   TBranch        *b_prime1;   //!
   TBranch        *b_px2;   //!
   TBranch        *b_py2;   //!
   TBranch        *b_pz2;   //!
   TBranch        *b_true_px2;   //!
   TBranch        *b_true_py2;   //!
   TBranch        *b_true_pz2;   //!
   TBranch        *b_r2;   //!
   TBranch        *b_rerr22;   //!
   TBranch        *b_id2;   //!
   TBranch        *b_pid2;   //!
   TBranch        *b_type2;   //!
   TBranch        *b_mid2;   //!
   TBranch        *b_hid2;   //!
   TBranch        *b_prime2;   //!
   TBranch        *b_px3;   //!
   TBranch        *b_py3;   //!
   TBranch        *b_pz3;   //!
   TBranch        *b_true_px3;   //!
   TBranch        *b_true_py3;   //!
   TBranch        *b_true_pz3;   //!
   TBranch        *b_r3;   //!
   TBranch        *b_rerr23;   //!
   TBranch        *b_id3;   //!
   TBranch        *b_pid3;   //!
   TBranch        *b_type3;   //!
   TBranch        *b_mid3;   //!
   TBranch        *b_hid3;   //!
   TBranch        *b_prime3;   //!
   TBranch        *b_pxm;   //!
   TBranch        *b_pym;   //!
   TBranch        *b_pzm;   //!
   TBranch        *b_mmass;   //!
   TBranch        *b_pcoplanar;   //!
   TBranch        *b_pacoplanar;   //!
   TBranch        *b_pm;   //!
   TBranch        *b_targetdist;   //!
   TBranch        *b_mep1;   //!
   TBranch        *b_mep2;   //!
   TBranch        *b_nhit1;   //!
   TBranch        *b_nhit2;   //!
   TBranch        *b_nhit3;   //!
   TBranch        *b_nsharedhit1;   //!
   TBranch        *b_nsharedhit2;   //!
   TBranch        *b_nsharedhit3;   //!
   TBranch        *b_nsharedseg1;   //!
   TBranch        *b_nsharedseg2;   //!
   TBranch        *b_nsharedseg3;   //!
   TBranch        *b_guessx;   //!
   TBranch        *b_guessy;   //!
   TBranch        *b_guessz;   //!
   TBranch        *b_guessdist;   //!
   TBranch        *b_true_targetdist;   //!
   TBranch        *b_mc_signal;   //!
   TBranch        *b_fit_tolerance;   //!
   TBranch        *b_fit_steps;   //!
   TBranch        *b_cosalpha;   //!
   TBranch        *b_theta_kuno;   //!
   TBranch        *b_phi_kuno;   //!

   sigAna(std::vector<TString> fnames={}, TString treeName="vertex");
   virtual ~sigAna();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();  //  (TTree *tree);
   virtual void     Loop(float WeightSum = -1, int VertexType=-1, int cut=-1);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void setOutputFileName(TString fin="");

 private:
   // Declaration of user defined functions;
   std::vector<int> getTrackType(int nv);//!
   bool hasVertexInAcceptance();//!
   int countTracks(int n, int i); //!
   int getTrack(int nv); //!
   TString _fileoutname;//!

};

#endif

#ifdef sigAna_cxx
sigAna::sigAna(std::vector<TString> fnames, TString treeName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  setOutputFileName();

  fChain = new TChain(treeName);
  
  for (TString fn : fnames) {
    fChain->AddFile(fn);
    std::cout << "Adding file " << fn 
	      << "  total entries: " << fChain->GetEntries()  << std::endl;
  }

  //TTree *tree = 0;
  //TFile *f = new TFile(fname,"read");
  //f->GetObject(treeName,tree);
  //Init(tree);
  Init();
}

sigAna::~sigAna()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t sigAna::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t sigAna::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void sigAna::Init()   // (TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   vx = 0;
   vy = 0;
   vz = 0;
   chi2 = 0;
   true_vx = 0;
   true_vy = 0;
   true_vz = 0;
   true_mass = 0;
   true_pxm = 0;
   true_pym = 0;
   true_pzm = 0;
   guess_vx = 0;
   guess_vy = 0;
   guess_vz = 0;
   px1 = 0;
   py1 = 0;
   pz1 = 0;
   true_px1 = 0;
   true_py1 = 0;
   true_pz1 = 0;
   r1 = 0;
   rerr21 = 0;
   id1 = 0;
   pid1 = 0;
   type1 = 0;
   mid1 = 0;
   hid1 = 0;
   prime1 = 0;
   px2 = 0;
   py2 = 0;
   pz2 = 0;
   true_px2 = 0;
   true_py2 = 0;
   true_pz2 = 0;
   r2 = 0;
   rerr22 = 0;
   id2 = 0;
   pid2 = 0;
   type2 = 0;
   mid2 = 0;
   hid2 = 0;
   prime2 = 0;
   px3 = 0;
   py3 = 0;
   pz3 = 0;
   true_px3 = 0;
   true_py3 = 0;
   true_pz3 = 0;
   r3 = 0;
   rerr23 = 0;
   id3 = 0;
   pid3 = 0;
   type3 = 0;
   mid3 = 0;
   hid3 = 0;
   prime3 = 0;
   pxm = 0;
   pym = 0;
   pzm = 0;
   mmass = 0;
   pcoplanar = 0;
   pacoplanar = 0;
   pm = 0;
   targetdist = 0;
   mep1 = 0;
   mep2 = 0;
   nhit1 = 0;
   nhit2 = 0;
   nhit3 = 0;
   nsharedhit1 = 0;
   nsharedhit2 = 0;
   nsharedhit3 = 0;
   nsharedseg1 = 0;
   nsharedseg2 = 0;
   nsharedseg3 = 0;
   guessx = 0;
   guessy = 0;
   guessz = 0;
   guessdist = 0;
   true_targetdist = 0;
   mc_signal = 0;
   fit_tolerance = 0;
   fit_steps = 0;
   cosalpha = 0;
   theta_kuno = 0;
   phi_kuno = 0;



   // Set branch addresses and branch pointers
   if (!fChain) return;
   //fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ncomb", &ncomb, &b_ncomb);
   fChain->SetBranchAddress("nrightchargecomb", &nrightchargecomb, &b_nrightchargecomb);
   fChain->SetBranchAddress("nvert", &nvert, &b_nvert);
   fChain->SetBranchAddress("ntwoone", &ntwoone, &b_ntwoone);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("chi2", &chi2, &b_chi2);
   fChain->SetBranchAddress("true_vx", &true_vx, &b_true_vx);
   fChain->SetBranchAddress("true_vy", &true_vy, &b_true_vy);
   fChain->SetBranchAddress("true_vz", &true_vz, &b_true_vz);
   fChain->SetBranchAddress("true_mass", &true_mass, &b_true_mass);
   fChain->SetBranchAddress("true_pxm", &true_pxm, &b_true_pxm);
   fChain->SetBranchAddress("true_pym", &true_pym, &b_true_pym);
   fChain->SetBranchAddress("true_pzm", &true_pzm, &b_true_pzm);
   fChain->SetBranchAddress("guess_vx", &guess_vx, &b_guess_vx);
   fChain->SetBranchAddress("guess_vy", &guess_vy, &b_guess_vy);
   fChain->SetBranchAddress("guess_vz", &guess_vz, &b_guess_vz);
   fChain->SetBranchAddress("px1", &px1, &b_px1);
   fChain->SetBranchAddress("py1", &py1, &b_py1);
   fChain->SetBranchAddress("pz1", &pz1, &b_pz1);
   fChain->SetBranchAddress("true_px1", &true_px1, &b_true_px1);
   fChain->SetBranchAddress("true_py1", &true_py1, &b_true_py1);
   fChain->SetBranchAddress("true_pz1", &true_pz1, &b_true_pz1);
   fChain->SetBranchAddress("r1", &r1, &b_r1);
   fChain->SetBranchAddress("rerr21", &rerr21, &b_rerr21);
   fChain->SetBranchAddress("id1", &id1, &b_id1);
   fChain->SetBranchAddress("pid1", &pid1, &b_pid1);
   fChain->SetBranchAddress("type1", &type1, &b_type1);
   fChain->SetBranchAddress("mid1", &mid1, &b_mid1);
   fChain->SetBranchAddress("hid1", &hid1, &b_hid1);
   fChain->SetBranchAddress("prime1", &prime1, &b_prime1);
   fChain->SetBranchAddress("px2", &px2, &b_px2);
   fChain->SetBranchAddress("py2", &py2, &b_py2);
   fChain->SetBranchAddress("pz2", &pz2, &b_pz2);
   fChain->SetBranchAddress("true_px2", &true_px2, &b_true_px2);
   fChain->SetBranchAddress("true_py2", &true_py2, &b_true_py2);
   fChain->SetBranchAddress("true_pz2", &true_pz2, &b_true_pz2);
   fChain->SetBranchAddress("r2", &r2, &b_r2);
   fChain->SetBranchAddress("rerr22", &rerr22, &b_rerr22);
   fChain->SetBranchAddress("id2", &id2, &b_id2);
   fChain->SetBranchAddress("pid2", &pid2, &b_pid2);
   fChain->SetBranchAddress("type2", &type2, &b_type2);
   fChain->SetBranchAddress("mid2", &mid2, &b_mid2);
   fChain->SetBranchAddress("hid2", &hid2, &b_hid2);
   fChain->SetBranchAddress("prime2", &prime2, &b_prime2);
   fChain->SetBranchAddress("px3", &px3, &b_px3);
   fChain->SetBranchAddress("py3", &py3, &b_py3);
   fChain->SetBranchAddress("pz3", &pz3, &b_pz3);
   fChain->SetBranchAddress("true_px3", &true_px3, &b_true_px3);
   fChain->SetBranchAddress("true_py3", &true_py3, &b_true_py3);
   fChain->SetBranchAddress("true_pz3", &true_pz3, &b_true_pz3);
   fChain->SetBranchAddress("r3", &r3, &b_r3);
   fChain->SetBranchAddress("rerr23", &rerr23, &b_rerr23);
   fChain->SetBranchAddress("id3", &id3, &b_id3);
   fChain->SetBranchAddress("pid3", &pid3, &b_pid3);
   fChain->SetBranchAddress("type3", &type3, &b_type3);
   fChain->SetBranchAddress("mid3", &mid3, &b_mid3);
   fChain->SetBranchAddress("hid3", &hid3, &b_hid3);
   fChain->SetBranchAddress("prime3", &prime3, &b_prime3);
   fChain->SetBranchAddress("pxm", &pxm, &b_pxm);
   fChain->SetBranchAddress("pym", &pym, &b_pym);
   fChain->SetBranchAddress("pzm", &pzm, &b_pzm);
   fChain->SetBranchAddress("mmass", &mmass, &b_mmass);
   fChain->SetBranchAddress("pcoplanar", &pcoplanar, &b_pcoplanar);
   fChain->SetBranchAddress("pacoplanar", &pacoplanar, &b_pacoplanar);
   fChain->SetBranchAddress("pm", &pm, &b_pm);
   fChain->SetBranchAddress("targetdist", &targetdist, &b_targetdist);
   fChain->SetBranchAddress("mep1", &mep1, &b_mep1);
   fChain->SetBranchAddress("mep2", &mep2, &b_mep2);
   fChain->SetBranchAddress("nhit1", &nhit1, &b_nhit1);
   fChain->SetBranchAddress("nhit2", &nhit2, &b_nhit2);
   fChain->SetBranchAddress("nhit3", &nhit3, &b_nhit3);
   fChain->SetBranchAddress("nsharedhit1", &nsharedhit1, &b_nsharedhit1);
   fChain->SetBranchAddress("nsharedhit2", &nsharedhit2, &b_nsharedhit2);
   fChain->SetBranchAddress("nsharedhit3", &nsharedhit3, &b_nsharedhit3);
   fChain->SetBranchAddress("nsharedseg1", &nsharedseg1, &b_nsharedseg1);
   fChain->SetBranchAddress("nsharedseg2", &nsharedseg2, &b_nsharedseg2);
   fChain->SetBranchAddress("nsharedseg3", &nsharedseg3, &b_nsharedseg3);
   fChain->SetBranchAddress("guessx", &guessx, &b_guessx);
   fChain->SetBranchAddress("guessy", &guessy, &b_guessy);
   fChain->SetBranchAddress("guessz", &guessz, &b_guessz);
   fChain->SetBranchAddress("guessdist", &guessdist, &b_guessdist);
   fChain->SetBranchAddress("true_targetdist", &true_targetdist, &b_true_targetdist);
   fChain->SetBranchAddress("mc_signal", &mc_signal, &b_mc_signal);
   fChain->SetBranchAddress("fit_tolerance", &fit_tolerance, &b_fit_tolerance);
   fChain->SetBranchAddress("fit_steps", &fit_steps, &b_fit_steps);
   fChain->SetBranchAddress("cosalpha", &cosalpha, &b_cosalpha);
   fChain->SetBranchAddress("theta_kuno", &theta_kuno, &b_theta_kuno);
   fChain->SetBranchAddress("phi_kuno", &phi_kuno, &b_phi_kuno);
   Notify();
}

Bool_t sigAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void sigAna::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t sigAna::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef sigAna_cxx
