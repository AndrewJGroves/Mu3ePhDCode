import ROOT as R
from Style import AtlasStyle
import math
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits(  )
R.gStyle.SetPalette(1)


def plot1res(f_bkg,his,axisLim,axistitle,unit,rebin,fit,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()
    if rebin>0:
        h_bkg.Rebin(rebin)
    h_bkg.GetXaxis().SetTitle(axistitle)
    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    h_bkg.SetMinimum(0);
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    h_bkg.GetYaxis().SetRangeUser(1,binmax*10)
    R.gPad.SetLogy(1)
    useLog = True

    h_bkg.Draw("EP")


    f1=R.TF1("f1","gaus",fit[0],fit[1])
    h_bkg.Fit("f1","R")
    mean=f1.GetParameter(1)
    sig=f1.GetParameter(2)
    meanerr=f1.GetParError(1)
    sigerr=f1.GetParError(2)

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()

    meanText = 'mu = {:.3e} pm {:.3e}'.format(mean,meanerr)
    sigText = 'sig = {:.3e} pm {:.3e}'.format(sig,sigerr)
    sig = R.TLatex(0.7,0.8,meanText)
    me = R.TLatex(0.7,0.7,sigText)
    sig.SetNDC()
    me.SetNDC()
    sig.Draw()
    me.Draw()

    R.gPad.RedrawAxis()
    c.Print(outname)



fSignal = R.TFile("../TDRSensitity/signal.root","read")
fIC = R.TFile("../TDRSensitity/IC.root","read")

plot1res(fSignal,"h_mpx",[-6,6],"p_{x,cms} [MeV/c]","[MeV/c]",0,[-20,20],"./Figures/Signal/mpx.png")
plot1res(fSignal,"h_mpy",[-6,6],"p_{y,cms} [MeV/c]","[MeV/c]",0,[-20,20],"./Figures/Signal/mpy.png")
plot1res(fSignal,"h_mpz",[-6,6],"p_{z,cms} [MeV/c]","[MeV/c]",0,[-20,20],"./Figures/Signal/mpz.png")
plot1res(fSignal,"h_massReso",[-20,20],"m_{reco} - m_{true} [MeV/c^{2}]","[MeV/c]",0,[-20,20],"./Figures/Signal/massReso.png")
