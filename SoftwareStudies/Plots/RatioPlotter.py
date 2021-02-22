from ROOT import *
from StyleRatio import AtlasStyle
import math
style = AtlasStyle()
gROOT.SetStyle( style.GetName() )
gROOT.ForceStyle()
TGaxis.SetMaxDigits(  )
gStyle.SetPalette(1)


def ratio(fil,hist,histTitle,axisLim,axistitle,unit,rebin,ratioLim,norm,outname):
    c1 = TCanvas("c1", "A ratio example",800,500)
    leg = TLegend(0.7,0.57,0.90,0.82)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    h1 = fil[0].Get(hist)
    h2 = fil[1].Get(hist)
    #h2.Scale(norm)
    if rebin > 0:
        h3 = h1.Rebin(rebin,"h3")
        h4 = h2.Rebin(rebin,"h4")
    else:
        h3 = h1.Clone()
        h4 = h2.Clone()
    h3.Scale(norm/h3.Integral())
    h4.Scale(norm/h4.Integral())
    rp = TRatioPlot(h3, h4)
    binmax2 = h3.GetBinContent( h3.GetMaximumBin()  )
    binmax1 = h4.GetBinContent( h4.GetMaximumBin()  )
    binmax = 0
    if binmax1 > binmax2:
        binmax = binmax1
    else:
        binmax = binmax2
    useLog = False
    if "_log" in outname:
        h3.GetYaxis().SetRangeUser(1,binmax*100)
        gPad.SetLogy(1)
        useLog = True
    else:
        gPad.SetLogy(0)

    h3.SetStats(0)
    h3.SetFillColor(kRed-9)
    h3.SetTitle("")
    binWidth=h3.GetXaxis().GetBinWidth(2)
    h3.GetYaxis().SetTitle('Events / %0.1f %2s' %(binWidth,unit))
    #h3.GetYaxis().SetTitleOffset(1.2)
    h3.GetXaxis().SetTitle(axistitle)

    h4.SetStats(0)
    h4.SetLineColor(kBlue)
    h4.SetLineWidth(4)

    leg.AddEntry(h3, histTitle[1], "F")
    leg.AddEntry(h4, histTitle[0], "L")

    rp.SetH2DrawOpt("hist");
    rp.SetH1DrawOpt("hist");
    rp.Draw()
    rp.GetLowerRefYaxis().SetLabelSize(0.02)
    rp.GetLowerRefYaxis().SetTitle("Ratio")
    rp.GetLowerRefGraph().SetMinimum(ratioLim[0])
    rp.GetLowerRefGraph().SetMaximum(ratioLim[1])

    rp.GetUpperPad().cd()
    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h3.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    h3.GetYaxis().SetRangeUser(0,1.3)
    h3.Draw("HIST,same")
    #h3.Draw("E1,same")
    h4.Draw("HIST,same")
    leg.Draw("same")
    c1.Update()
    c1.Print(outname)


print ("rootSetup 6.10.08")
f_bkg1    = TFile("../TDRSensitity/IC/RootFiles/IC.root","read")
f_bkg    = TFile("../TDRSensitity/Signal/RootFiles/signal.root","read")
f_bkg2    = TFile("/hepstore/agroves/MyStudies/SoftwareStudies/CombinationBackground/PhoCon/RadAll.root","read")
f_bkg3    = TFile("/hepstore/agroves/ICmicRootFiles/ICmicAll.root","read")

#ratio([f_bkg,f_bkg1],"h_mass",["Internal Coversion","Signal"],[90,115],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,[0,0],1,"./Figures/mass_log.png")
#ratio([f_bkg,f_bkg1],"h_massLong;1",["Internal Coversion","Signal"],[90,115],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,[0,0],1,"./Figures/mass.png")
#ratio([f_bkg,f_bkg1],"h_chi2",["Internal Coversion","Signal"],[0,50],"#chi^{2}","",2,[-1,1],8,"./Figures/chi.png")
#ratio([f_bkg,f_bkg1],"h_chi2Long",["Internal Coversion","Signal"],[0,50],"#chi^{2}","",2,[0.6,1.4],8,"./Figures/chiLong.png")
#ratio([f_bkg,f_bkg1],"h_targetLong",["Internal Coversion","Signal"],[-5,5],"Distance to target [mm]","[mm]",0,[0,2],4,"./Figures/targetLong.png")
#ratio([f_bkg,f_bkg1],"h_target",["Internal Coversion","Signal"],[-5,5],"Distance to target [mm]","[mm]",0,[0,2],4,"./Figures/target.png")
#ratio([f_bkg,f_bkg1],"h_tmomLong",["Internal Coversion","Signal"],[0,40],"3 Track Momentum [MeV/c]","[MeV/c]",0,[0,0],8,"./Figures/tmom.png")
#ratio([f_bkg,f_bkg1],"h_tmomLong",["Internal Coversion","Signal"],[0,40],"3 Track Momentum [MeV/c]","[MeV/c]",0,[0,0],1,"./Figures/tmom_log.png")
ratio([f_bkg,f_bkg1],"h_DieleLong",["Internal Coversion","Signal"],[0,80],"Lowest Dielectron Mass [MeV/c^{2}]","[MeV/c^{2}]",0,[0,0],100,"./Figures/dielectron.png")


#ratio([f_bkg,f_bkg2],"h_chi2",["Photon Conversion and Michel","Signal"],[0,50],"#chi^{2}","",2,[0,2],8,"./Figures/chiPhoMic.png")
#ratio([f_bkg,f_bkg2],"h_chi2Long",["Photon Conversion and Michel","Signal"],[0,50],"#chi^{2}","",2,[0,2],8,"./Figures/chiPhoMicLong.png")
#ratio([f_bkg,f_bkg2],"h_target",["Photon Coversion and Michel","Signal"],[-20,20],"Distance to target [mm]","[mm]",0,[0,0],4,"./Figures/targetPhoMic.png")
