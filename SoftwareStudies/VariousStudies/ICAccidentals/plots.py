import ROOT as R
from Style import AtlasStyle
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)

def plot1(f_bkg,his,histTitle,axisLim,axistitle,unit,rebin,outname):
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
    h_bkg.Smooth()
    h_bkg.Scale(scale/h_bkg.Integral())
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


f    = R.TFile("plots.root","read")

#plot1(f,"icmass","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"icmass.png")
#plot1(f,"icmomentum","",[0,0],"Momentum [MeV/c]","[MeV/c]",0,"icmomentum.png")
#plot1(f,"eminusspectrum","",[0,0],"",0,"eminusspectrum.png")
#plot1(f,"eplusspectrum","",[0,0],"",0,"elpusspectrum.png")
#plot1(f,"icmassPart","",[0,0],"mass (MeV)",0,"icmassPart.png")
#plot1(f,"mass1michel","",[0,0],"mass (MeV)",0,"mass1michel.png")
#plot1(f,"momentum1michel","",[0,0],"momentum (MeV/c)",0,"momentum1michel.png")
#plot1(f,"momentum2michel","",[0,0],"momentum (MeV/c)",0,"momentum2michel.png")
#plot1(f,"mass2michel","",[0,0],"mass (MeV)",0,"mass2michel.png")
#plot1(f,"massmomentum2michel","",[0,0],"mass (MeV)",0,"massmomentum2michel.png")
#plot1(f,"massmomentum1michel","",[0,0],"mass (MeV)",0,"massmomentum.png")

plot1(f,"mass2","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"mass2.png")
plot1(f,"mass1","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"mass1.png")
plot1(f,"mom1","",[0,0],"Momentum [MeV/c]","[MeV/c]",4,"mom1.png")
plot1(f,"mom2","",[0,0],"Momentum [MeV/c]","[MeV/c]",4,"mom2.png")

plot1(f,"mass1_mass95","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"mass1_mass95.png")
plot1(f,"mass2_mass95","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"mass2_mass95.png")
plot1(f,"mom1_mass95","",[0,0],"Momentum [MeV/c]","[MeV/c]",0,"mom1_mass95.png")
plot1(f,"mom2_mass95","",[0,0],"Momentum [MeV/c]","[MeV/c]",0,"mom2_mass95.png")

plot1(f,"mass1_mom8","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"mass1_mom8.png")
plot1(f,"mass2_mom8","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",0,"mass2_mom8.png")
plot1(f,"mom1_mom8","",[0,0],"Momentum [MeV/c]","[MeV/c]",0,"mom1_mom8.png")
plot1(f,"mom2_mom8","",[0,0],"Momentum [MeV/c]","[MeV/c]",0,"mom2_mom8.png")
plot1(f,"mass1_mass95mom8","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"mass1_mass95mom8.png")
plot1(f,"mass2_mass95mom8","",[0,0],"Mass [MeV/c^{2}]","[MeV/c^{2}]",4,"mass2_mass95mom8.png")
plot1(f,"mom1_mass95mom8","",[0,0],"Momentum [MeV/c]","[MeV/c]",4,"mom1_mass95mom8.png")
plot1(f,"mom2_mass95mom8","",[0,0],"Momentum [MeV/c]","[MeV/c]",4,"mom2_mass95mom8.png")

#plot1(f,"target","",[0,0],"z (mm)",0,"target.png")
