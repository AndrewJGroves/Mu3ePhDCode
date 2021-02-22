import ROOT as R
from Style import AtlasStyle
import math
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)

def plot1(f_bkg,his,histTitle,axisLim,axistitle,rebin,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()#"Effiency","Effiency",1000,600)
    #R.gStyle.SetOptStat("o,u")
    h_bkg.SetFillColor(R.kYellow)
    h_bkg.GetXaxis().SetTitle(axistitle)
    h_bkg.GetYaxis().SetTitle("Number of Vertices")
    if rebin>0:
        h_bkg.Rebin(rebin)
    if len(axisLim) > 0:
        if axisLim[0] < axisLim[1]:
            h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
    binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
    useLog = False
    if "_log" in outname:
        h_bkg.GetYaxis().SetRangeUser(1,binmax*10)
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)
        h_bkg.GetYaxis().SetRangeUser(1,binmax+30)
    h_bkg.SetMarkerStyle(1)
    h_bkg.SetFillColor(R.kYellow)
    h_bkg.DrawCopy("HIST")
    h_bkg.SetFillColor(R.kBlue);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kYellow);
    h_bkg.SetFillStyle(1001);

    tex = R.TLatex(0.57, 0.86, "#mu3e, work in progress")
    tex.SetNDC()
    tex.Draw()
    #tex1 = R.TLatex(0.5,0.80, "Phase-I, 9.3x10^{11} #mu decayed")
    #tex1.SetNDC()
    #tex1.Draw()
    
    err1 = R.Double(0.0)
    err2 = R.Double(0.0)
    h_bkg.IntegralAndError(0,1,err1)
    h_bkg.IntegralAndError(0,999999,err2)
    frac = h_bkg.Integral(0,1)/h_bkg.Integral(0,999999)
    err = frac * math.sqrt((err1/h_bkg.Integral(0,1))**2 + (err2/h_bkg.Integral(0,999999))**2)

    print "fraction ", frac," +- ", err


    R.gPad.RedrawAxis()
    c.Print(outname)

def plot2ang(f_bkg,his1,his2,histTitle,axisLim,axistitle,rebin,outname,norm):
    h_bkg=f_bkg.Get(his1)
    h_sig=[f_bkg.Get(his2)]
    leg = R.TLegend(0.6,0.7,0.75,0.8)
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



    h_bkg.SetFillColor(R.kYellow)
    h_bkg.DrawCopy("HIST")
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
    tex = R.TLatex(0.6, 0.83, "#mu3e, work in progress")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)

def plot2(f_bkg,his1,his2,histTitle,axisLim,axistitle,rebin,outname,norm):
    h_bkg=f_bkg.Get(his1)
    h_sig=[None] * len(his2)
    for i in range(len(his2)):
        h_sig[i]=f_bkg.Get(his2[i])

    leg = R.TLegend(0.6,0.6,0.85,0.8)
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

    #a=h_bkg.GetXaxis()
    #a.ChangeLabel(1,-1,-1,-1,-1,-1,"0")
    #a.ChangeLabel(-1,-1,-1,-1,-1,-1,"#pi")
    #a.ChangeLabel(4,-1,-1,-1,-1,-1,"#pi/2")
    #a.ChangeLabel(2,-1,-1,-1,-1,-1," ")
    #a.ChangeLabel(3,-1,-1,-1,-1,-1," ")
    #a.ChangeLabel(5,-1,-1,-1,-1,-1," ")
    #a.ChangeLabel(6,-1,-1,-1,-1,-1," ")

    h_bkg.SetFillColor(R.kYellow)
    h_bkg.DrawCopy("HIST")
    h_bkg.SetFillColor(R.kBlue);
    h_bkg.SetFillStyle(3345);
    h_bkg.DrawCopy("E2,same")
    h_bkg.SetFillColor(R.kYellow);
    h_bkg.SetFillStyle(1001);

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
        h_bkg.GetYaxis().SetRangeUser(0, binmax+120)

    leg.Draw("same")
    tex = R.TLatex(0.6, 0.83, "#mu3e, work in progress")
    tex.SetNDC()
    tex.Draw()
    R.gPad.RedrawAxis()
    c.Print(outname)

def plot2d(f_bkg,his,xaxistitle,yaxistitle,outname):
    h_bkg=f_bkg.Get(his)
    c = R.TCanvas()

    if "_log" in outname:
        R.gPad.SetLogy(1)
        useLog = True
    else:
        R.gPad.SetLogy(0)

    R.gPad.SetLogz(1)
    h_bkg.GetXaxis().SetTitle(xaxistitle)
    h_bkg.GetYaxis().SetTitle(yaxistitle)
    h_bkg.Draw("COLZ")


    c.Print(outname)


f_signal = R.TFile("plots.root","read")

#plot1(f_signal,"h_diff","h_diff",[0,0],"Distance to IC",0,"h_diff.png")

#plot1(f_signal,"h_diff","h_diff",[0,0],"Distance to IC",0,"h_diff_log.png")
#plot1(f_signal,"h_diffxy","h_diffxy",[0,0],"Distance to IC",0,"h_diffxy.png")
#plot1(f_signal,"h_diffzy","h_diffzy",[0,0],"Distance to IC",0,"h_diffzy.png")

plot2ang(f_signal,"h_Theta204","h_Theta104",[">20 mm","<10 mm"],[0,3,0,65],"theta",0,"theta.png",1)
#plot2(f_signal,"h_vz20",["h_vz10"],[">20","<10"],[0,0,0,21],"true z postion",2,"truez.png",1)
plot2(f_signal,"h_diff4",["h_diff6","h_diff8"],["4 michel hits","6 michel hits","8 michel hits"],[0,0,0,65],"Distance from michel vertex to IC vertex",0,"diffco.png",0)
#plot2(f_signal,"h_Theta204",["h_Theta206","h_Theta208","h_Theta104","h_Theta206","h_Theta208"],[">20 mm 4 michel hits",">20 mm 6 michel hits",">20 mm 8 michel hits","<10 mm 4 michel hits","<10 mm 6 michel hits","<10 mm 8 michel hits"],[0,0,0,0],"Distance from michel vertex to IC vertex",0,"theta2.png",0)

#plot2d(f_signal,"h_close","d_{2}","d_{1}","close.png")
#plot2d(f_signal,"h_pdisxy","Transverse Momentum of michel","Transverse Distance to IC","pdisxy.png")
#plot2d(f_signal,"h_pdiszy","Longitudinal Momentum of michel","Longitudinal Distance to IC","pdiszy.png")

#plot2d(f_signal,"h_close","d_{2}","d_{1}","close_log.png")

#plot2d(f_signal,"h_vzdiffxyP","True michel vertex in z","Distance to IC in y","h_vzdiffxyP.png")
#plot2d(f_signal,"h_vzdiffxyN","True michel vertex in z","Distance to IC in y","h_vzdiffxyN.png")
