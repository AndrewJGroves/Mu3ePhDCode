import ROOT as R
from Style import AtlasStyle
import math
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits(  )
R.gStyle.SetPalette(1)

def plot3reso(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname,norm):
    h_bkg=f_bkg[0].Get(his1[0]) #E = 40
    h_sig=f_bkg[1].Get(his1[0]) #E = 20
    h_sig25=f_bkg[2].Get(his1[1])

    leg = R.TLegend(0.2,0.55,0.4,0.8)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()
    #4.435686e-06
    scale1 =2.5e15 * 4.534386e-06 * 6.03e-8 * 1/0.0952715 * 0.01 #*7.0/800.0#8.75e-3 #0.240546
    scale2 =2.5e15 * 9.681504e-06 * 6.03e-8 * 0.01  #*252.0/19360.0#0.0952715 #0.0143436
    scale3 =2.5e15 * 4.534386e-06 * 6.03e-8  *0.01  #*252.0/19360.0#0.0952715 #0.0143436

#6.03e-8
#6.03e-8*17.6824
#3.3e-3*0.0565534
#3.3e-3

#10 up to 20  = 0.24
#10 up to 40  = 0.014 

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
        h_bkg.GetYaxis().SetRangeUser(1,binmax*1000000000)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
        

    if rebin>0:
        h_sig.Rebin(rebin)
        h_sig25.Rebin(rebin)

    h_sig.Scale(1./h_sig.Integral())
    h_bkg.Scale(1./h_bkg.Integral())
    h_sig25.Scale(1./h_sig25.Integral())

    h_sig.Scale(scale1)
    h_bkg.Scale(scale2)
    h_sig25.Scale(scale3)

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

    h_bkg.SetLineColor(R.kGreen);
    h_bkg.Draw("EP,same")
    leg.AddEntry(h_bkg, histTitle[0], "L")


    h_sig.SetLineWidth(2)
    h_sig.SetLineColor(R.kRed)
    h_sig.SetMarkerStyle(1)
    h_sig.Draw("EP,same")
    leg.AddEntry(h_sig, histTitle[1], "L")

    h_sig25.SetLineWidth(2)
    h_sig25.SetLineColor(R.kBlue)
    h_sig25.SetMarkerStyle(1)
    h_sig25.Draw("EP,same")
    leg.AddEntry(h_sig25, histTitle[2], "L")


    c.Update()
    leg.Draw("same")
    tex = R.TLatex(0.2, 0.83, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname) 

def plot1res(f_bkg,his,axisLim,axistitle,unit,rebin,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()#"Effiency","Effiency",1000,600)
    #R.gStyle.SetOptStat("o,u")
    if rebin>0:
        h_bkg.Rebin(rebin)
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

    h_bkg.DrawCopy("EP")

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    #tex1 = R.TLatex(0.5,0.80, "Phase-I, 9.3x10^{11} #mu decayed")
    #tex1.SetNDC()
    #tex1.Draw()

    R.gPad.RedrawAxis()
    c.Print(outname)

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
    h_bkg.DrawCopy("HIST")
    h_bkg.SetFillColor(R.kBlue);
    h_bkg.SetFillStyle(3345);
    if( his != "h_weight"):
        h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kRed-4);
    h_bkg.SetFillStyle(1001);

    tex = R.TLatex(0.17, 0.95, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    #tex1 = R.TLatex(0.5,0.80, "Phase-I, 9.3x10^{11} #mu decayed")
    #tex1.SetNDC()
    #tex1.Draw()
    

    if( his == "h_diff"):
        err1 = R.Double(0.0)
        err2 = R.Double(0.0)
        h_bkg.IntegralAndError(0,1,err1)
        h_bkg.IntegralAndError(0,999999,err2)
        frac = h_bkg.Integral(0,1)/h_bkg.Integral(0,999999)
        err = frac * math.sqrt((err1/h_bkg.Integral(0,1))**2 + (err2/h_bkg.Integral(0,999999))**2)
        print "Fraction of vertices closer than 2mm ", frac," +- ", err
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
    h_bkg.GetYaxis().SetTitle("Number of Vertices")
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

    h_bkg.SetFillColor(R.kYellow)
    h_bkg.Draw("HIST")
    h_bkg.SetFillColor(R.kBlue);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kYellow);
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
        h_sig[i].SetLineColor(i+2)
        h_sig[i].SetMarkerStyle(1)
        if rebin>0:
            h_sig[i].Rebin(rebin)
        h_sig[i].DrawCopy("HIST,same")
        h_sig[i].SetFillColor(R.kRed);
        h_sig[i].SetFillStyle(3354);
        h_sig[i].DrawCopy("E2,same")
        leg.AddEntry(h_sig[i], histTitle[i+1], "L")
        i_binmax = h_sig[i].GetBinContent( h_sig[i].GetMaximumBin()  )
        if i_binmax > binmax:
            binmax = i_binmax
    if not useLog:
        h_bkg.GetYaxis().SetRangeUser(0, binmax+40)

    leg.Draw("same")
    tex = R.TLatex(0.2, 0.87, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)

def plot2(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname,norm):
    h_bkg=f_bkg[0].Get(his1) #E = 40
    h_sig=f_bkg[1].Get(his1) #E = 20

    leg = R.TLegend(0.2,0.65,0.4,0.8)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()
    #4.435686e-06
    scale1 =1 #*7.0/800.0#8.75e-3 #0.240546
    scale2 = 0.0952715   #*252.0/19360.0#0.0952715 #0.0143436
#6.03e-8
#6.03e-8*17.6824
#3.3e-3*0.0565534
#3.3e-3

#10 up to 20  = 0.24
#10 up to 40  = 0.014 

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
        h_bkg.GetYaxis().SetRangeUser(1,binmax*1000000000)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
   
    leg.AddEntry(h_bkg, histTitle[0], "F")


    if rebin>0:
        h_sig.Rebin(rebin)
    h_sig.Scale(1./h_sig.Integral())
    h_bkg.Scale(1./h_bkg.Integral())

    h_sig.Scale(scale1)
    h_bkg.Scale(scale2)

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
    h_bkg.SetFillColor(R.kYellow);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kRed-9);
    h_bkg.SetFillStyle(1001);

    h_sig.SetLineWidth(2)
    h_sig.SetLineColor(R.kBlue+4)
    h_sig.SetMarkerStyle(1)
    h_sig.DrawCopy("HIST,same")
    h_sig.SetFillColor(R.kBlack);
    h_sig.SetFillStyle(3354);
    h_sig.DrawCopy("E2,same")
    leg.AddEntry(h_sig, histTitle[1], "L")

    c.Update()
    leg.Draw("same")
    tex = R.TLatex(0.2, 0.83, "Mu3e Phase 1 Simulation")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)


def plot3(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname,norm):
    h_bkg=f_bkg[0].Get(his1) #E = 40
    h_sig=f_bkg[1].Get(his1) #E = 20
    h_sig25=f_bkg[2].Get(his1)

    leg = R.TLegend(0.2,0.65,0.4,0.8)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    c = R.TCanvas()
    #4.435686e-06
    scale1 =2.5e15 * 4.534386e-06 * 6.03e-8 * 1/0.0952715 * 0.01 #*7.0/800.0#8.75e-3 #0.240546
    scale2 =2.5e15 * 6.445e-07 * 6.03e-8 * 22 * 0.01  #*252.0/19360.0#0.0952715 #0.0143436
    scale3 =2.5e15 * 5.485109e-06 * 6.03e-8  * 1/0.14744 *0.01  #*252.0/19360.0#0.0952715 #0.0143436

#6.03e-8
#6.03e-8*17.6824
#3.3e-3*0.0565534
#3.3e-3

#10 up to 20  = 0.24
#10 up to 40  = 0.014 

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
        h_bkg.GetYaxis().SetRangeUser(1,binmax*1000000000)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
   
    leg.AddEntry(h_bkg, histTitle[0], "F")


    if rebin>0:
        h_sig.Rebin(rebin)
        h_sig25.Rebin(rebin)

    h_sig.Scale(1./h_sig.Integral())
    h_bkg.Scale(1./h_bkg.Integral())
    h_sig25.Scale(1./h_sig25.Integral())

    h_sig.Scale(scale1)
    h_bkg.Scale(scale2)
    h_sig25.Scale(scale3)

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
    h_bkg.SetFillColor(R.kYellow);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kRed-9);
    h_bkg.SetFillStyle(1001);

    h_sig.SetLineWidth(2)
    h_sig.SetLineColor(R.kBlue+4)
    h_sig.SetMarkerStyle(1)
    h_sig.DrawCopy("HIST,same")
    h_sig.SetFillColor(R.kBlack);
    h_sig.SetFillStyle(3354);
    h_sig.DrawCopy("E2,same")
    leg.AddEntry(h_sig, histTitle[1], "L")

    h_sig25.SetLineWidth(2)
    h_sig25.SetLineColor(R.kBlue)
    h_sig25.SetMarkerStyle(1)
    h_sig25.DrawCopy("HIST,same")
    h_sig25.SetFillColor(R.kBlue);
    h_sig25.SetFillStyle(3354);
    h_sig25.DrawCopy("E2,same")
    leg.AddEntry(h_sig25, histTitle[2], "L")


    c.Update()
    leg.Draw("same")
    tex = R.TLatex(0.2, 0.83, "Mu3e Phase 1 Simulation")
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

    tex1 = R.TLatex(0.21, 0.31, "Michel + Photon Conversion")
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

def plot2base(f_bkg,his1,histTitle,axisLim,axistitle,unit,rebin,outname):
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


    #h_bkg.Smooth()
    #h_sig.Smooth()
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



fRad25 = R.TFile("../RootFiles/Rad25.root","read")
fRad = R.TFile("../RootFiles/Rad40/RadAll.root","read")
fRadNo = R.TFile("../RootFiles/Rad.root","read")
fRad2 = R.TFile("testing.root","read")
fRadNo2 = R.TFile("Plots20.root","read")
fRad225 = R.TFile("Plots25.root","read")
fbase = R.TFile("RadAll.root","read")
f20 = R.TFile("Plots20_sim.root","read")
f40 = R.TFile("Plots40_sim.root","read")


"""
plot2DColz(f20,"h_xyz","z [mm]","r [mm]",[0,0,0,100],[8,8],"../Figures/rz20smS.png")
plot2DColz(f20,"h_xyz","z [mm]","r [mm]",[0,0,0,0],[0,8],"../Figures/rz20S.png")
plot2DColz(fRad,"h_PEpho","E_{#gamma} [MeV]","P [MeV/c]",[20,70,0,0],[6,12],"../Figures/PhoCon40/Pho40EP.png")
plot2DColz(fRadNo,"h_PEpho","E_{#gamma} [MeV]","P [MeV/c]",[20,70,0,0],[6,12],"../Figures/PhoCon40/PhoEP.png")
plot2DColz(fRad25,"h_PEpho","E_{#gamma} [MeV]","P [MeV/c]",[20,70,0,0],[6,12],"../Figures/PhoCon40/PhoEP25.png")
plot2DColz(f20,"h_xyz","z [mm]","r [mm]",[0,0,0,100],[8,8],"../Figures/PhoCon40/rz20sm.png")
plot2DColz(f20,"h_xyz","z [mm]","r [mm]",[0,0,0,0],[0,8],"../Figures/PhoCon40/rz20.png")
plot1res(fRad2,"h_Reso",[0,0],"Momentum Resolution [MeV/c]","[MeV/c]",2,"../Figures/PhoCon40/Reso40.png")
plot1res(fRadNo2,"h_Reso",[0,0],"Momentum Resolution [MeV/c]","[MeV/c]",2,"../Figures/PhoCon40/Reso20.png")
plot1res(fRad2,"h_Reso",[0,0],"Momentum Resolution [MeV/c]","[MeV/c]",2,"../Figures/PhoCon40/Reso40_log.png")
plot1res(fRadNo2,"h_Reso",[0,0],"Momentum Resolution [MeV/c]","[MeV/c]",2,"../Figures/PhoCon40/Reso20_log.png")
plot1(fRad,"h_chi2",[0,85],"#chi^{2}","",10,"../Figures/PhoCon40/chi240.png")
plot1(fRad,"h_target",[-20,30],"Distance to target [mm]","[mm]",2,"../Figures/PhoCon40/DisTar40.png")
plot1(fRadNo,"h_chi2",[0,85],"#chi^{2}","",10,"../Figures/PhoCon40/chi220.png")
plot1(fRadNo,"h_target",[-20,30],"Distance to target [mm]","[mm]",10,"../Figures/PhoCon40/DisTar20.png")
plot1(fRad25,"h_chi2",[0,85],"#chi^{2}","",10,"../Figures/PhoCon40/chi225.png")
plot1(fRad25,"h_target",[-20,30],"Distance to target [mm]","[mm]",10,"../Figures/PhoCon40/DisTar25.png")
plot2DColz(fRad,"h_xy","x [mm]","y [mm]",[0,0,0,0],[2,2],"../Figures/PhoCon40/Radxy.png")
plot2DColz(fRad,"h_zr","z [mm]","r [mm]",[0,0,0,0],[2,2],"../Figures/PhoCon40/Radzr.png")
plot2DColz(fRad,"h_zrRec","z [mm]","r [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/RadzrRec.png")
plot2DColz(fRad25,"h_xy","x [mm]","y [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/Radxy25.png")
plot2DColz(fRad25,"h_zr","z [mm]","r [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/Radzr25.png")
plot2DColz(fRad25,"h_zrRec","z [mm]","r [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/RadzrRec25.png")
plot2DColz(fRadNo,"h_xy","x [mm]","y [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/Radxy20.png")
plot2DColz(fRadNo,"h_zr","z [mm]","r [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/Radzr20.png")
plot2DColz(fRadNo,"h_zrRec","z [mm]","r [mm]",[0,0,0,0],[10,10],"../Figures/PhoCon40/RadzrRec20.png")
plot2DScat(fRad,"h_PmMass","Mass [MeV/c^{2}]","Momentum [MeV/c]",[20,120,0,40],[2,0],"../Figures/PhoCon40/RadMassP.png")
plot2DScat(fRadNo,"h_PmMass","Mass [MeV/c^{2}]","Momentum [MeV/c]",[20,120,0,40],[2,0],"../Figures/PhoCon40/RadMassP20.png")
plot2DScat(fRad25,"h_PmMass","Mass [MeV/c^{2}]","Momentum [MeV/c]",[20,120,0,40],[2,0],"../Figures/PhoCon40/RadMassP25.png")
plot2([f40,f20],"h_EPt",["E_{#gamma} > 40","E_{#gamma} > 20"],[0,80,0,0.2],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoCompSim.png",1)
plot2([f40,f20],"h_EPt_true",["E_{#gamma} > 40","E_{#gamma} > 20"],[0,60,0,0.2],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoCompTrueSim.png",1)
plot1(fRad,"h_tmom",[0,0],"Absolute Momentum [MeV/c]","[MeV/c]",20,"../Figures/PhoCon40/tmom.png")
plot1(fRad,"h_tmom",[0,0],"Absolute Momentum [MeV/c]","[MeV/c]",0,"../Figures/PhoCon40/tmom_log.png")
plot1(fRadNo,"h_tmom",[0,0],"Absolute Momentum [MeV/c]","[MeV/c]",20,"../Figures/PhoCon40/tmom20.png")
plot1(fRadNo,"h_tmom",[0,0],"Absolute Momentum [MeV/c]","[MeV/c]",0,"../Figures/PhoCon40/tmom20_log.png")
plot1(fRad25,"h_tmom",[0,0],"Absolute Momentum [MeV/c]","[MeV/c]",20,"../Figures/PhoCon40/tmom25.png")
plot1(fRad25,"h_tmom",[0,0],"Absolute Momentum [MeV/c]","[MeV/c]",0,"../Figures/PhoCon40/tmom25_log.png")
plot3([fRad2,fRadNo2,fRad225],"h_EPt",["E_{#gamma} > 40","E_{#gamma} > 20","E_{#gamma} > 25"],[20,80,0,3],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoComp.png",1)
plot3([fRad2,fRadNo2,fRad225],"h_EPt_true",["E_{#gamma} > 40","E_{#gamma} > 20","E_{#gamma} > 25"],[20,60,0,3],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoCompTrue.png",1)
plot3reso([fRad2,fRadNo2,fRadNo2],["h_Reso","h_Reso40"],["E_{#gamma} > 40","E_{#gamma} > 20","E_{#gamma} > 20 Selection"],[0,0,0,0],"Momentum Resolution [MeV/c]","[MeV/c]",2,"../Figures/PhoCon40/Reso3_log.png",1)
plot3reso([fRad2,fRadNo2,fRadNo2],["h_Reso","h_Reso40"],["E_{#gamma} > 40","E_{#gamma} > 20","E_{#gamma} > 20 Selection"],[0,0,0,0],"Momentum Resolution [MeV/c]","[MeV/c]",0,"../Figures/PhoCon40/Reso3.png",1)
plot2DColz(fRad2,"h_PPhoMass","E_{#gamma} [MeV]","Mass [MeV/c^{2}]",[20,60,0,120],[8,8],"../Figures/PhoCon40/Pho40EM.png")
plot2DColz(fRadNo2,"h_PPhoMass","E_{#gamma} [MeV]","Mass [MeV/c^{2}]",[20,60,0,120],[8,8],"../Figures/PhoCon40/PhoEM.png")
plot2DColz(fRad225,"h_PPhoMass","E_{#gamma} [MeV]","Mass [MeV/c^{2}]",[20,60,0,120],[8,8],"../Figures/PhoCon40/PhoEM25.png")
"""

plot3([fRad2,fRadNo2,fRad225],"h_EPt_true",["E_{#gamma} > 40 MeV","E_{#gamma} > 20 MeV","E_{#gamma} > 25 MeV"],[20,60,0,3],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoCompTrue.png",1)
plot3([fRad2,fRadNo2,fRad225],"h_EPt",["E_{#gamma} > 40 MeV","E_{#gamma} > 20 MeV","E_{#gamma} > 25 MeV"],[20,80,0,3],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoComp.png",1)
plot2([f40,f20],"h_EPt_true",["E_{#gamma} > 40 MeV","E_{#gamma} > 20 MeV"],[0,60,0,0.2],"Momentum [MeV/c]","[MeV/c]",8,"../Figures/PhoCon40/PPhoCompTrueSim.png",1)
"""
plot3reso([fRad2,fRadNo2,fRadNo2],["h_Reso","h_Reso40"],["E_{#gamma} > 40","E_{#gamma} > 20","E_{#gamma} > 20 Selection"],[0,0,0,0],"Momentum Resolution [MeV/c]","[MeV/c]",2,"../Figures/PhoCon40/Reso3_log.png",1)
plot2DColz(fRad2,"h_PPhoMass","E_{#gamma} [MeV]","Mass [MeV/c^{2}]",[20,60,0,120],[8,8],"../Figures/PhoCon40/Pho40EM.png")
plot2DColz(fRad225,"h_PPhoMass","E_{#gamma} [MeV]","Mass [MeV/c^{2}]",[20,60,0,120],[8,8],"../Figures/PhoCon40/PhoEM25.png")
plot2DColz(fRad,"h_PEpho","E_{#gamma} [MeV]","P [MeV/c]",[20,70,0,0],[6,12],"../Figures/PhoCon40/Pho40EP.png")
plot2DColz(fRad25,"h_PEpho","E_{#gamma} [MeV]","P [MeV/c]",[20,70,0,0],[6,12],"../Figures/PhoCon40/PhoEP25.png")
plot2DColz(f20,"h_xyz","z [mm]","r [mm]",[0,0,0,100],[8,8],"../Figures/PhoCon40/rz20sm.png")  #Doesnt work well
plot2DColz(f20,"h_xyz","z [mm]","r [mm]",[0,0,0,0],[0,8],"../Figures/PhoCon40/rz20.png")      #Doesnt work well
plot2DColz(fRad,"h_xy","x [mm]","y [mm]",[0,0,0,0],[2,2],"../Figures/PhoCon40/Radxy.png")
plot2DColz(fRad,"h_zr","z [mm]","r [mm]",[0,0,0,0],[2,2],"../Figures/PhoCon40/Radzr.png")
plot2DScat(fRad,"h_PmMass","Mass [MeV/c^{2}]","Momentum [MeV/c]",[20,120,0,40],[2,0],"../Figures/PhoCon40/RadMassP.png")
"""
"""
plot2base(fbase,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,45,0,0],"#chi^{2}","",4,"../Figures/PhoCon40/chi2.png")
plot2base(fbase,["h_chi2","h_chi2Long"],["All Tracks","3 Long tracks"],[0,45,0,0],"#chi^{2}","",2,"../Figures/PhoCon40/chi2_log.png")
plot2base(fbase,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-20,100,0,0],"Distance to target [mm]","[mm]",4,"../Figures/PhoCon40/DisTar.png")
plot2base(fbase,["h_target","h_targetLong"],["All Tracks","3 Long tracks"],[-20,100,0,0],"Distance to target [mm]","[mm]",0,"../Figures/PhoCon40/DisTar_log.png")
"""
