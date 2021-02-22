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
    h_bkg.GetYaxis().SetTitle('Events / %0.1e %2s' %(binWidth,unit))
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
    h_bkg.SetFillColor(R.kRed-9)
    h_bkg.Draw("HIST")
    h_bkg.SetFillColor(R.kBlue);
    h_bkg.SetFillStyle(3345);
    if( his != "h_weight"):
        h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kRed-9);
    h_bkg.SetFillStyle(1001);

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    #tex1 = R.TLatex(0.5,0.80, "Phase-I, 9.3x10^{11} #mu decayed")
    #tex1.SetNDC()
    #tex1.Draw()
    
    R.gPad.RedrawAxis()
    c.Print(outname)



def plot2ang(f_bkg,his1,his2,histTitle,axisLim,axistitle,rebin,outname,norm):
    h_bkg=f_bkg.Get(his1)
    h_sig=[f_bkg.Get(his2)]
    leg = R.TLegend(0.2,0.71,0.5,0.84)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()

    h_bkg.SetMarkerStyle(1)
    h_bkg.GetXaxis().SetTitle(axistitle)

    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    h_bkg.GetYaxis().SetTitle('Events / %0.1f [rad]' %(binWidth))
    h_bkg_tot = h_bkg.Integral()
    if rebin>0:
        h_bkg.Rebin(rebin)
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    if "_log" in outname:
        h_bkg.GetYaxis().SetRangeUser(1,binmax*1000000000)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
   
    leg.AddEntry(h_bkg, histTitle[0], "F")

    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2], axisLim[3])


    for i in range(0,len(h_sig)):
        if norm > 0:
            h_sig[i].Scale(norm * h_bkg_tot / h_sig[i].Integral())
        if rebin>0:
            h_sig[i].Rebin(rebin)
        i_binmax = h_sig[i].GetBinContent( h_sig[i].GetMaximumBin()  )
        if i_binmax > binmax:
            binmax = i_binmax
    if not useLog:
        h_bkg.GetYaxis().SetRangeUser(0, binmax+binmax/4)

    h_bkg.SetFillColor(R.kRed-9)
    h_bkg.Draw("HIST")
    h_bkg.SetFillColor(R.kBlue);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kRed-9);
    h_bkg.SetFillStyle(1001);

    a=h_bkg.GetXaxis()
    a.ChangeLabel(1,-1,-1,-1,-1,-1,"0")
    a.ChangeLabel(-1,-1,-1,-1,-1,-1,"#pi")
    a.ChangeLabel(4,-1,-1,-1,-1,-1,"#pi/2")
    a.ChangeLabel(2,-1,-1,-1,-1,-1," ")
    a.ChangeLabel(3,-1,-1,-1,-1,-1," ")
    a.ChangeLabel(5,-1,-1,-1,-1,-1," ")
    a.ChangeLabel(6,-1,-1,-1,-1,-1," ")
    for i in range(0,len(h_sig)):
        if norm > 0:
            h_sig[i].Scale(norm * h_bkg_tot / h_sig[i].Integral())
        h_sig[i].SetLineWidth(2)
        h_sig[i].SetLineColor(R.kBlue+3)
        h_sig[i].SetMarkerStyle(1)
        if rebin>0:
            h_sig[i].Rebin(rebin)
        h_sig[i].DrawCopy("HIST,same")
        h_sig[i].SetFillColor(R.kBlue+3);
        h_sig[i].SetFillStyle(3354);
        h_sig[i].DrawCopy("E2,same")
        leg.AddEntry(h_sig[i], histTitle[i+1], "L")
        i_binmax = h_sig[i].GetBinContent( h_sig[i].GetMaximumBin()  )
        if i_binmax > binmax:
            binmax = i_binmax
    if not useLog:
        h_bkg.GetYaxis().SetRangeUser(0, binmax+700)

    leg.Draw("same")
    tex = R.TLatex(0.2, 0.87, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)

def plot3(f_bkg,his1,his2,histTitle,axisLim,axistitle,rebin,outname,norm):
    h_bkg=f_bkg.Get(his1)
    h_sig=[None] * len(his2)
    for i in range(len(his2)):
        h_sig[i]=f_bkg.Get(his2[i])

    leg = R.TLegend(0.6,0.6,0.85,0.8)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()

    h_bkg.SetMarkerStyle(1)
    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    h_bkg.GetYaxis().SetTitle('Events / %0.1f [mm]' %(binWidth))
    h_bkg.GetXaxis().SetTitle("Distance from Michel vertex to IC vertex [mm]")
    h_bkg_tot = h_bkg.Integral()
    if rebin>0:
        h_bkg.Rebin(rebin)
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    if "_log" in outname:
        h_bkg.GetYaxis().SetRangeUser(1,binmax*1000000000)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
   
    leg.AddEntry(h_bkg, histTitle[0], "F")


    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    if axisLim[2] < axisLim[3]:
        h_bkg.GetYaxis().SetRangeUser(axisLim[2], axisLim[3])

    for i in range(0,len(h_sig)):
        if norm > 0:
            h_sig[i].Scale(norm * h_bkg_tot / h_sig[i].Integral())
        if rebin>0:
            h_sig[i].Rebin(rebin)
        i_binmax = h_sig[i].GetBinContent( h_sig[i].GetMaximumBin()  )
        if i_binmax > binmax:
            binmax = i_binmax
    if not useLog:
        h_bkg.GetYaxis().SetRangeUser(0, binmax+binmax/10)


    h_bkg.SetFillColor(R.kRed-9)
    h_bkg.DrawCopy("HIST")
    h_bkg.SetFillColor(R.kRed-9);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kRed-9);
    h_bkg.SetFillStyle(1001);

    for i in range(0,len(h_sig)):
        h_sig[i].SetLineWidth(2)
        h_sig[i].SetLineColor(i+2)
        h_sig[i].SetMarkerStyle(1)
        h_sig[i].DrawCopy("HIST,same")
        h_sig[i].SetFillColor(R.kRed-9);
        h_sig[i].SetFillStyle(3354);
        h_sig[i].DrawCopy("E2,same")
        leg.AddEntry(h_sig[i], histTitle[i+1], "L")

    c.Update()
    leg.Draw("same")
    tex = R.TLatex(0.50, 0.85, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)


def plot2(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname):
    h_bkg=f_bkg.Get(his1[0]) 
    h_sig=f_bkg.Get(his1[1]) 

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

def plot2comp(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname):
    h_bkg=f_bkg[0].Get(his1) 
    h_sig=f_bkg[1].Get(his1) 

    leg = R.TLegend(0.7,0.55,0.90,0.8)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()

    h_bkg.SetMarkerStyle(1)
    h_bkg.GetXaxis().SetTitle(axistitle)
    binWidth=h_bkg.GetXaxis().GetBinWidth(2)
    h_bkg.GetYaxis().SetTitle('Events / %0.1e %2s' %(binWidth,unit))
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
    tex = R.TLatex(0.5, 0.83, "Mu3e Phase 1 Simulation")
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

    tex1 = R.TLatex(0.53, 0.31, "IC + Michel electron")
    tex1.SetTextColor(R.kRed);
    tex1.SetTextSize(0.04);
    tex1.SetNDC()
    tex1.Draw()
    tex2 = R.TLatex(0.53, 0.25, "1 dot: 1 event per 10^{15} #mu stops")
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



fVertex = R.TFile("/hepstore/agroves/ICmicRootFiles/ICmicAll.root","read")
fIC = R.TFile("/hepstore/agroves/MyStudies/SoftwareStudies/RootFiles/IC.root","read")

fWeightHigh =  R.TFile("/hepstore/agroves/MyStudies/SoftwareStudies/VariousStudies/HighWeight/plots_high.root","read")
fWeightNormal =  R.TFile("/hepstore/agroves/MyStudies/SoftwareStudies/VariousStudies/HighWeight/plots_normal.root","read")

plot3(fVertex,"h_diff4",["h_diff6","h_diff8"],["4 michel hits","6 michel hits","8 michel hits"],[0,0,0,0],"Distance from Michel vertex to IC vertex / [mm]",0,"../Figures/ICmic/VertexDiffHits.png",0)
plot2ang(fVertex,"h_Theta20","h_Theta10",["> 20 mm","< 10 mm"],[0,3,0,0],"#theta of Michel electron [rad]",0,"../Figures/ICmic/MichelTheta.png",1)
plot1(fVertex,"h_weight",[0,0],"Weight","",0,"../Figures/ICmic/Weight_log.png")
plot1(fIC,"h_weight",[0,1000e3],"Weight","",0,"../Figures/ICmic/WeightIC_log.png")
plot2DScat(fVertex,"h_PmMass","Mass [MeV/c^{2}]","Momentum [MeV/c]",[95,160,0,20],[2,0],"../Figures/ICmic/MassP.png")
plot1(fVertex,"h_chi2",[0,0],"#chi^{2}","",0,"../Figures/ICmic/chi2.png")
plot1(fVertex,"h_target",[0,0],"Distance to target [mm]","[mm]",0,"../Figures/ICmic/distar.png")
plot1(fVertex,"h_tmom",[0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"../Figures/ICmic/tmom.png")

plot2comp([fWeightHigh,fWeightNormal],"h_angleE1E2",["High weight","Normal Weight"],[0,3.5,0,0],"Angle [Rad]","[Rad]",2,"../Figures/ICmic/anglee1e2.png")
plot2comp([fWeightHigh,fWeightNormal],"h_angleE2E3",["High weight","Normal Weight"],[0,3.5,0,0],"Angle [Rad]","[Rad]",2,"../Figures/ICmic/anglee2e3.png")
plot2comp([fWeightHigh,fWeightNormal],"h_angleE1E3",["High weight","Normal Weight"],[0,3.5,0,10000],"Angle [Rad]","[Rad]",2,"../Figures/ICmic/anglee1e3.png")
plot2comp([fWeightHigh,fWeightNormal],"h_tmomnu1",["High weight","Normal Weight"],[0,0,0,0],"Momentum [MeV/c]","[MeV/c]",4,"../Figures/ICmic/tmomnu1.png")
plot2comp([fWeightHigh,fWeightNormal],"h_tmomnu2",["High weight","Normal Weight"],[0,0,0,0],"Momentum [MeV/c]","[MeV/c]",4,"../Figures/ICmic/tmomnu2.png")

plot2comp([fWeightHigh,fWeightNormal],"h_massmu3e",["High weight","Normal Weight"],[0,140,0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"../Figures/ICmic/mass_log.png")
"""
#plot2(fIC,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,50,0,0],"#chi^{2}","",4,"Figures/IC/chi2.png")
#plot2(fIC,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,0,0,0],"#chi^{2}","",2,"Figures/IC/chi2_log.png")
#plot2(fIC,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-5,4,0,0],"Distance to target [mm]","[mm]",2,"Figures/IC/DisTar.png")
#plot2(fIC,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-5,4,0,0],"Distance to target [mm]","[mm]",0,"Figures/IC/DisTar.png")
plot2(fIC,["h_tmom","h_tmomLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",0,"Figures/IC/tmom.png")
plot2(fIC,["h_tmom","h_tmomLong"],["All Tracks","3 Long tracks"],[0,0,0,0],"3 Track Momentum [MeV/c]","[MeV/c]",2,"Figures/IC/tmom_log.png")
plot2(fIC,["h_mass","h_massLong"],["All Tracks","3 Long tracks"],[95,115,0,1000e3],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"Figures/IC/mass.png")
plot2(fIC,["h_mass","h_massLong"],["All Tracks","3 Long tracks"],[95,115,0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",2,"Figures/IC/mass_log.png")


"""
