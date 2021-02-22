import ROOT as R
from Style import AtlasStyle
import math
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)

f_bkg    = R.TFile("RootFiles/icmic_60mill.root","read")
h_bkg = f_bkg.Get("h_track2")
h_2 = f_bkg.Get("h_icmic")

c = R.TCanvas()

h_bkg.SetFillColor(R.kYellow)
h_bkg.GetXaxis().SetTitle("Number of decays")
h_bkg.GetYaxis().SetTitle("Number of Vertices")
#R.gPad.SetLogy(1)
h_bkg.Draw("HIST")
h_bkg.Draw("E1,same")
tex = R.TLatex(0.2, 0.88, "#mu3e, work in progress")
tex.SetNDC()
tex.Draw()
tex1 = R.TLatex(0.2,0.82, "Phase-I, XX #mu on target")
tex1.SetNDC()
tex1.Draw()
#c.Print("track2_log.png")
err1 = R.Double(0.0)
err2 = R.Double(0.0)
h_bkg.IntegralAndError(0,5,err1)
h_bkg.IntegralAndError(0,999999,err2)
frac = h_bkg.Integral(0,5)/h_bkg.Integral(0,999999)
err = frac * math.sqrt((err1/h_bkg.Integral(0,5))**2 + (err2/h_bkg.Integral(0,5))**2)

print "fraction ", frac," +- ", err

