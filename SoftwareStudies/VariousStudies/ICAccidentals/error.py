import ROOT as R

f = R.TFile("cut_10.root","read")
h_bkg=f.Get("mass1michel")
h_bkg.Sumw2()
sumw = h_bkg.GetSumOfWeights()
print sumw
