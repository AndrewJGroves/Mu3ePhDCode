import ROOT as R
from Style import AtlasStyle
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)


f_signal = R.TFile("../RootFiles/signal_noTree.root","read")
f_IC     = R.TFile("../RootFiles/IC_noTree.root","read")
f_ICmic  = R.TFile("../RootFiles/ICmic_noTree.root","read")
h_IC     = f_IC.Get("h_PmMass")
h_sig   = f_signal.Get("h_PmMass")
h_ICmic  = f_ICmic.Get("h_PmMass")




h_ICmic.SetMarkerColor(R.kBlue)
h_ICmic.SetMarkerStyle(7)
h_IC.SetMarkerColor(R.kRed)
h_IC.SetMarkerStyle(7)
h_IC.GetXaxis().SetRangeUser(95,110)
h_IC.GetYaxis().SetRangeUser(0,12)
h_IC.GetXaxis().SetTitle("m_{rec} [MeV/c^{2}]")
h_IC.GetYaxis().SetTitle("p_{cms} [MeV/c]")
h_IC.Draw()
h_ICmic.Draw("same")


text = raw_input()

