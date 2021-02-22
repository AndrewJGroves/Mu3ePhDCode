import ROOT as R
from Style import AtlasStyle
import math
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits(  )
R.gStyle.SetPalette(1)



def plot1(f_bkg,his,axisLim,axistitle,unit,rebin,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()#"Effiency","Effiency",1000,600)
    #R.gStyle.SetOptStat("o,u")
    if rebin>0:
        h_bkg.Rebin(rebin)
    h_bkg.SetFillColor(R.kRed-4)
    h_bkg.GetXaxis().SetTitle(axistitle)
    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    h_bkg.GetYaxis().SetTitle('Events / %0.1f %2s' %(binWidth,unit))
    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    h_bkg.SetMinimum(0);
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    scale = h_bkg.Integral();
    #h_bkg.Smooth()
    #h_bkg.Scale(scale/h_bkg.Integral())
    if "_log" in outname:
        h_bkg.GetYaxis().SetRangeUser(1,binmax*10)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
        h_bkg.GetYaxis().SetRangeUser(1,binmax+binmax/8)
    h_bkg.SetMarkerStyle(1)
    h_bkg.SetFillColor(R.kRed-4)
    h_bkg.Draw("HIST")
    #h_bkg.SetFillColor(R.kBlue);
    #h_bkg.SetFillStyle(3345);
    #if( his != "h_weight"):
    #    h_bkg.DrawCopy("E2,same")
    #h_bkg.SetFillColor(R.kRed-4);
    #h_bkg.SetFillStyle(1001);

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    #tex1 = R.TLatex(0.5,0.80, "Phase-I, 9.3x10^{11} #mu decayed")
    #tex1.SetNDC()
    #tex1.Draw()
    
    R.gPad.RedrawAxis()
    c.Print(outname)



def plot2(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname):
    h_bkgTem=f_bkg.Get(his1[0]) 
    h_sigTem=f_bkg.Get(his1[1]) 

    h_bkg=h_bkgTem.Clone()
    h_sig=h_sigTem.Clone()

    leg = R.TLegend(0.7,0.57,0.90,0.82)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()

    h_bkg.SetMarkerStyle(1)
    h_bkg.GetXaxis().SetTitle(axistitle)
    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    h_bkg.GetYaxis().SetTitle('Events / %0.1f %2s' %(binWidth,unit))
    h_bkg_tot = h_bkg.Integral()
    if rebin>0:
        h_bkg.Rebin(rebin)
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    if "_log" in outname:
        h_bkg.GetYaxis().SetRangeUser(1,binmax*100)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
   
    leg.AddEntry(h_bkg, histTitle[0], "F")


    if rebin>0:
        h_sig.Rebin(rebin)

    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    i_binmax = h_sig.GetBinContent( h_sig.GetMaximumBin()  )
    if i_binmax > binmax:
        binmax = i_binmax
    if not useLog:
        h_bkg.GetYaxis().SetRangeUser(0, binmax+binmax/10)
    if axisLim[0] < axisLim[1]:
        h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2], axisLim[3])
    
    if (his1[0]=="h_mass"):
        h_bkg.GetXaxis().SetNdivisions(15)
        h_sig.GetXaxis().SetNdivisions(15)


    h_bkg.Smooth()
    h_sig.Smooth()
    h_bkg.SetFillColor(R.kRed-9)
    h_bkg.DrawCopy("HIST")
    #h_bkg.SetFillColor(R.kYellow);
    #h_bkg.SetFillStyle(3345);
    #h_bkg.DrawCopy("E2,same")
    #h_bkg.SetFillColor(R.kRed);
    #h_bkg.SetFillStyle(1001);

    h_sig.SetLineWidth(2)
    h_sig.SetLineColor(R.kBlue+4)
    h_sig.SetMarkerStyle(1)
    h_sig.DrawCopy("HIST,same")
    #h_sig.SetFillColor(R.kBlack);
    #h_sig.SetFillStyle(3354);
    #h_sig.DrawCopy("E2,same")
    leg.AddEntry(h_sig, histTitle[1], "L")

    c.Update()
    leg.Draw("same")
    tex = R.TLatex(0.55, 0.85, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)


def plot2DScat(f_bkg,his,xaxistitle,yaxistitle,axisLim,rebin,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()

    if "_log" in outname:
        R.gPad.SetLogz(1)
        useLog = True
    else:
        R.gPad.SetLogz(0)
    if rebin[0] > 0:
        h_bkg.RebinX(rebin[0])
    if rebin[1] > 0:
        h_bkg.RebinY(rebin[1])

    h_bkg.GetXaxis().SetTitle(xaxistitle)
    h_bkg.GetYaxis().SetTitle(yaxistitle)
    if axisLim[0] < axisLim[1]:
        h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2], axisLim[3])
    h_bkg.SetMarkerColor(R.kRed)
    h_bkg.Draw("SCAT")

    tex1 = R.TLatex(0.21, 0.31, "IC Conversion")
    tex1.SetTextColor(R.kRed);
    tex1.SetTextSize(0.04);
    tex1.SetNDC()
    tex1.Draw()
    tex2 = R.TLatex(0.21, 0.25, "1 dot: 1 event per 10^{15} #mu stops")
    tex2.SetTextColor(R.kRed);
    tex2.SetTextSize(0.04);
    tex2.SetNDC()
    tex2.Draw()

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()

    c.Print(outname)

def plot2comp(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname,eff):
    h_bkg=f_bkg[0].Get(his1) 
    h_sig=f_bkg[1].Get(his1) 

    leg = R.TLegend(0.75,0.60,0.90,0.8)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()

    h_bkg.SetMarkerStyle(1)
    h_bkg.GetXaxis().SetTitle(axistitle)
    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    h_bkg.GetYaxis().SetTitle('Events / %0.1f %2s' %(binWidth,unit))
    h_bkg_tot = h_bkg.Integral()
    if rebin>0:
        h_bkg.Rebin(rebin)
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    if "_log" in outname:
        h_bkg.GetYaxis().SetRangeUser(1,binmax*100)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
   
    leg.AddEntry(h_bkg, histTitle[0], "F")


    if rebin>0:
        h_sig.Rebin(rebin)

    icscale=2.5e15*3.4e-5*0.9*eff[0]
    signalscale=2.5e15*1e-14*0.9*eff[1]
    h_bkg.Scale(icscale)
    h_bkg.Scale(signalscale)

    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    i_binmax = h_sig.GetBinContent( h_sig.GetMaximumBin()  )
    if i_binmax > binmax:
        binmax = i_binmax
    if not useLog:
        h_bkg.GetYaxis().SetRangeUser(0, binmax+binmax/10)
    if axisLim[0] < axisLim[1]:
        h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2], axisLim[3])
    
    

    h_bkg.SetFillColor(R.kRed)
    h_bkg.DrawCopy("HIST")
    #h_bkg.SetFillColor(R.kYellow);
    #h_bkg.SetFillStyle(3345);
    #h_bkg.DrawCopy("E2,same")
    #h_bkg.SetFillColor(R.kRed);
    #h_bkg.SetFillStyle(1001);

    h_sig.SetLineWidth(2)
    h_sig.SetLineColor(R.kBlue+4)
    h_sig.SetMarkerStyle(1)
    h_sig.DrawCopy("HIST,same")
    #h_sig.SetFillColor(R.kBlack);
    #h_sig.SetFillStyle(3354);
    #h_sig.DrawCopy("E2,same")
    leg.AddEntry(h_sig, histTitle[1], "L")

    c.Update()
    leg.Draw("same")
    tex = R.TLatex(0.55, 0.83, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)


def plot2DScat(f_bkg,his,xaxistitle,yaxistitle,axisLim,rebin,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()

    if "_log" in outname:
        R.gPad.SetLogz(1)
        useLog = True
    else:
        R.gPad.SetLogz(0)
    if rebin[0] > 0:
        h_bkg.RebinX(rebin[0])
    if rebin[1] > 0:
        h_bkg.RebinY(rebin[1])

    h_bkg.GetXaxis().SetTitle(xaxistitle)
    h_bkg.GetYaxis().SetTitle(yaxistitle)
    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2], axisLim[3])
    h_bkg.SetMarkerColor(R.kRed)
    h_bkg.Draw("SCAT")

    tex1 = R.TLatex(0.21, 0.31, "IC Conversion")
    tex1.SetTextColor(R.kRed);
    tex1.SetTextSize(0.04);
    tex1.SetNDC()
    tex1.Draw()
    tex2 = R.TLatex(0.21, 0.25, "1 dot: 1 event per 10^{15} #mu stops")
    tex2.SetTextColor(R.kRed);
    tex2.SetTextSize(0.04);
    tex2.SetNDC()
    tex2.Draw()

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()

    c.Print(outname)

def plot2DColz(f_bkg,his,xaxistitle,yaxistitle,axisLim,rebin,outname):
    h_bkg=f_bkg.Get(his)
    R.gStyle.SetPadRightMargin( 0.04 )
    c = R.TCanvas()
    R.gStyle.SetPalette(R.kViridis)

    if "_log" in outname:
        R.gPad.SetLogz(1)
        useLog = True
    else:
        R.gPad.SetLogz(0)
    if rebin[0] > 0:
        h_bkg.RebinX(rebin[0])
    if rebin[1] > 0:
        h_bkg.RebinY(rebin[1])

    h_bkg.GetXaxis().SetTitle(xaxistitle)
    h_bkg.GetYaxis().SetTitle(yaxistitle)
    if axisLim[0] < axisLim[1]:
        h_bkg.GetXaxis().SetRangeUser(axisLim[0],axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2],axisLim[3])

    h_bkg.Draw("COLZ")

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()

    c.Print(outname)





fSignal = R.TFile("../TDRSensitity/Signal/RootFiles/signal.root","read")
fIC = R.TFile("../TDRSensitity/IC/RootFiles/IC.root","read")
f = R.TFile("/hepstore/agroves/ICmicVariousData/ic.root","read")

#plot1(f,"icmomentum",[0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"Figures/IC/ICtruthNocut.png")

#plot1(fIC,"h_tmomTrue",[0,0],"3 Track Momentum [MeV/c]","[MeV/c]",4,"Figures/IC/tmomTruth.png")
#plot1(fIC,"h_tmomTrue",[0,0],"3 Track Momentum [MeV/c]","[MeV/c]",4,"Figures/IC/tmomTruth_log.png")
plot2(fSignal,["h_Diele","h_DieleLong"],["All Tracks","3 Long tracks"],[0,120,0,70000],"Lowest Dielectron Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/Signal/Diele.png")
"""
plot2(fSignal,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,50,0,0],"#chi^{2}","",10,"Figures/Signal/chi2.png")
plot2(fSignal,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,0,0,0],"#chi^{2}","",0,"Figures/Signal/chi2_log.png")
#plot2(fSignal,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-5,4,0,0],"Distance to target [mm]","[mm]",0,"Figures/Signal/DisTar.png") 
#plot2(fSignal,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-5,4,0,0],"Distance to target [mm]","[mm]",0,"Figures/Signal/DisTar_log.png")
plot2(fSignal,["h_tmom","h_tmomLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"Figures/Signal/tmom.png")
plot2(fSignal,["h_tmom","h_tmomLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"Figures/Signal/tmom_log.png")
plot2(fSignal,["h_Diele","h_DieleLong"],["All Tracks","3 Long tracks"],[0,200,0,0],"Lowest Dielectron Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/Signal/Diele.png")
plot2(fSignal,["h_mass","h_massLong"],["All Tracks","3 Long tracks"],[95,115,0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/Signal/mass.png")
plot2(fSignal,["h_mass","h_massLong"],["All Tracks","3 Long tracks"],[95,115,0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/Signal/mass_log.png")

plot2(fIC,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,50,0,0],"#chi^{2}","",4,"Figures/IC/chi2.png")
plot2(fIC,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,0,0,0],"#chi^{2}","",2,"Figures/IC/chi2_log.png")
#plot2(fIC,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-5,4,0,0],"Distance to target [mm]","[mm]",2,"Figures/IC/DisTar.png")
#plot2(fIC,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-5,4,0,0],"Distance to target [mm]","[mm]",0,"Figures/IC/DisTar.png")
plot2(fIC,["h_tmom","h_tmomLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"Figures/IC/tmom.png")
plot2(fIC,["h_tmom","h_tmomLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",2,"Figures/IC/tmom_log.png")
plot2(fIC,["h_Diele","h_DieleLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"Lowest Dielectron Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/IC/Diele.png")
plot2(fIC,["h_mass","h_massLong"],["All Tracks","3 Long tracks"],[95,115,0,1000e3],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/IC/mass.png")
plot2(fIC,["h_mass","h_massLong"],["All Tracks","3 Long tracks"],[95,115,0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",2,"Figures/IC/mass_log.png")
"""

#plot2comp([fIC,fSignal],"h_chi2",["Internal Convestion","Signal"],[0,50,0,0],"#chi^{2}","",4,"Figures/chi2.png",[1,1])
#plot2comp([fIC,fSignal],"h_target",["Internal Convestion","Signal"],[-5,4,0,0],"Distance to target [mm]","[mm]",2,"Figures/DisTar.png",[1,1])
#plot2comp([fIC,fSignal],"h_tmom",["Internal Convestion","Signal"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"Figures/tmom.png",[1,1])
#plot2comp([fIC,fSignal],"h_mass",["Internal Convestion","Signal"],[95,115,0,1000e3],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/mass.png",[1,1])

