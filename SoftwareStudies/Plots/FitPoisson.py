import ROOT as R
from Style import AtlasStyle
#style = AtlasStyle()
#R.gROOT.SetStyle( style.GetName() )
#R.gROOT.ForceStyle()
#R.TGaxis.SetMaxDigits( 4 )
#R.gStyle.SetPalette(1)


f_signal = R.TFile("RootFiles/icmic_60mill.root","read")
h_bkg=f_signal.Get("h_icmic")
c = R.TCanvas()

R.gStyle.SetOptStat("0")
h_bkg.SetFillColor(R.kYellow)
h_bkg.SetTitle("")
h_bkg.GetXaxis().SetTitle("Decays per frame")
h_bkg.GetYaxis().SetTitle("Number of vertieces")
#f= R.TF1("f", "[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1.)", 0, 20)
f= R.TF1("f", "[0]*TMath::Poisson(x,[1])", 1, 15)
f.SetParameter(0,300e9)
f.SetParameter(1,5)
#f.SetParameter(2,1)

binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
useLog = False
#if "_log" in outname:
h_bkg.GetXaxis().SetRangeUser(0,12)
#    R.gPad.SetLogy(1)
#    useLog = True
#else:
#    R.gPad.SetLogy(0)

h_bkg.Fit(f,"R")
h_bkg.Draw("HIST")
h_bkg.Draw("E1,same")
tex = R.TLatex(0.6, 0.86, "#mu3e, work in progress")
tex.SetNDC()
tex.Draw()
R.gPad.RedrawAxis()
c.Print("Figures/ICmic/h_icmic.png")
chi = f.GetChisquare()/f.GetNDF()
print "the chi2/ndf",  chi
