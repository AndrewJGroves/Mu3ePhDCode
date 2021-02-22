import ROOT as R
from Style import AtlasStyle



Ntarget = 1e15    
SigEfficiency = 0.149873

ICEff = 3.094575e-06 * 0.0210#0.011396  
ICmicEff =  3.660731949e-9


axisLim = [95,112,0,1]
outname = "FullMassICmic_log.png"

f_signal = R.TFile("./Signal/RootFiles/signal.root","read")
f_IC     = R.TFile("./IC/RootFiles/IC.root","read")
f_ICmic  = R.TFile("./CombinationBackground/ICmic/RootFiles/ICmic.root","read")

binRange=[104,109.9999999]

ICmic=True
#---------------------------------------------------------------------------------------------------

style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)
leg = R.TLegend(0.8,0.58,1,0.89)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  
c = R.TCanvas()

h_IC2     = f_IC.Get("h_massLong")
h_sig1   = f_signal.Get("h_massLong")
h_ICmic  = f_ICmic.Get("h_massLong;1")
histTitle = ["IC","10^{-12}","10^{-13}","10^{-14}","10^{-15}","IC + michel"]

NormFactor = SigEfficiency *  Ntarget * 0.9
# multiply now by the BR that you want
signalweight_12 = NormFactor*1e-12;
signalweight_13 = NormFactor*1e-13;
signalweight_14 = NormFactor*1e-14;
signalweight_15 = NormFactor*1e-15;
sigweight=[signalweight_12, signalweight_13 ,signalweight_14 ,signalweight_15 ]

#### normalization of the background
ic_BR = 3.4e-5
ICscale = Ntarget * ic_BR * 0.9 * ICEff 

timming = 0.01
ic_acceptance = 0.62577 #For acceptance of 10 for pt and 0.8 costheata
mic_acceptance = 0.461745
ICmicScale = Ntarget * 3.4e-5 * ICmicEff  * timming * ic_acceptance  * mic_acceptance
print ICmicScale
h_sig12=h_sig1.Clone()
h_sig13=h_sig1.Clone()
h_sig14=h_sig1.Clone()
h_sig15=h_sig1.Clone()
h_sig=[h_sig12,h_sig13,h_sig14,h_sig15]

# you need to start with shape: normalize them to unity
for h in h_sig:
    nbins = h.GetNbinsX()
    xmin = h.GetBinLowEdge(1)
    xmax = h.GetBinLowEdge(nbins+1)
    h.Scale(1./(h.Integral(0,nbins+1)  ))
    #h.Smooth()
#h_IC2.Rebin(2)
#h_ICmic.Rebin(2)
h_IC2.Scale(1./(h_IC2.Integral(0,9999999999999)))
if(ICmic):
    h_ICmic.Scale(1./(h_ICmic.Integral(0,9999999999)))
#h_IC2.Smooth()
#h_ICmic.Smooth()

h_IC2.Scale(ICscale)
if(ICmic):
    h_ICmic.Scale(ICmicScale)
h_IC=h_IC2.Clone()
if(ICmic):
    h_IC.Add(h_ICmic)


h_IC.SetFillColor(R.kRed-9)
if(ICmic):
    h_ICmic.SetFillColor(R.kBlue+3)
    h_ICmic.SetLineColor(R.kBlue+3)
    h_ICmic.SetFillStyle(3001)
h_IC.GetXaxis().SetTitle("m_{rec} [MeV/c^{2}]")

binWidth=h_IC.GetXaxis().GetBinWidth(2)
h_IC.GetYaxis().SetTitle('Events / %0.1f [MeV/c^{2}]' %(binWidth))
h_IC_tot = h_IC.Integral()
err1 = R.Double(0.0)
n1=h_IC.GetXaxis().FindBin(binRange[0])
n2=h_IC.GetXaxis().FindBin(binRange[1])
n3=h_ICmic.GetXaxis().FindBin(binRange[0])
n4=h_ICmic.GetXaxis().FindBin(binRange[1])
if(ICmic):
    h_ICmic.IntegralAndError(n3,n4,err1)
err2 = R.Double(0.0)
h_IC2.IntegralAndError(n1,n2,err2)
errortot=0.0
#for i in range(n1,n2):
    #print "Bin edge", h_ICmic.GetBinLowEdge(i), " Entries ",  h_ICmic.GetBinContent(i), " error ", h_ICmic.GetBinError(i)
    #errortot+=h_ICmic.GetBinError(i)
#print "Error check ", error
if(ICmic):
    print "IC and michel estimate in the signal region of ",binRange[0],"-",binRange[1]," is ", h_ICmic.Integral(n3,n4)," +- ", err1
print "IC estimate in the signal region of ",binRange[0],"-",binRange[1]," is ",  h_IC2.Integral(n1,n2)," +- ", err2
print "Total background in the signal region of ",binRange[0],"-",binRange[1]," is ",  h_IC.Integral(n1,n2)

binmax = h_IC.GetBinContent( h_IC.GetMaximumBin()  )
useLog = False
if "_log" in outname:
    #if axisLim[2] < axisLim[3]:
    h_IC.GetYaxis().SetRangeUser(1e-7, 1e2)
    R.gPad.SetLogy(1)
    useLog = True
else:
    R.gPad.SetLogy(0)
    
leg.AddEntry(h_IC, histTitle[0], "F")
if(ICmic):
    leg.AddEntry(h_ICmic, histTitle[len(histTitle)-1], "F")
#leg.AddEntry(h_IC, "#mu #rightarrow eee", "")
leg.AddEntry(h_IC, " ", "")
if len(axisLim) > 0:
    if axisLim[0] < axisLim[1]:
        h_IC.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
h_IC.Draw("HIST")
if(ICmic):
    h_ICmic.Draw("HIST,same")
#h_IC.Draw("E1,same")
#h_ICmic.Draw("HIST,same")
#h_ICmic.Draw("E1,same")
#hs.Add(h_IC)
#hs.Add(h_ICmic)
#hs.Draw("HIST")
#hs.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])


for i in range(0,len(h_sig)):
    h_sig[i].Scale(sigweight[i])
    h_sig[i].SetLineWidth(2)
    if i+2 != 5:
        h_sig[i].SetLineColor(i+2)
    else:
        h_sig[i].SetLineColor(R.kRed+4)
    #if rebin>0:
    #    h_sig[i].Rebin(rebin)
    h_sig[i].Draw("HIST,same")
    #hs.Add(h_sig[i])
    leg.AddEntry(h_sig[i], histTitle[i+1], "L")
    i_binmax = h_sig[i].GetBinContent( h_sig[i].GetMaximumBin()  )
    if i_binmax > binmax:
        binmax = i_binmax
    if not useLog:
        h_IC.GetYaxis().SetRangeUser(0, binmax)

tex = R.TLatex(0.62, 0.95, "Mu3e Phase 1 Simulation")
tex.SetNDC()
tex.Draw()

tex1 = R.TLatex(0.8, 0.8, "#mu #rightarrow eee")
tex1.SetNDC()
#tex1.Draw()


max12 = h_sig[0].GetMaximum();
max13 = h_sig[1].GetMaximum();
max14 = h_sig[2].GetMaximum();
max15 = h_sig[3].GetMaximum();

tt0 = R.TLatex(108.7,max12*2.5,"#it{#mu} #rightarrow #it{eee}");
tt0.SetTextFont(42);
#tt0.Draw();
  
a12 = R.TArrow(106, max12, 109.2, max12, 0.02, "<|");
a12.Draw();
t12 = R.TLatex(109.3,max12*0.8,"at 10^{-12}");
t12.SetTextFont(42);
t12.Draw();

a13 = R.TArrow(106, max13, 109.2, max13, 0.02, "<|");
a13.Draw();
t13 =R.TLatex(109.3,max13*0.8,"at 10^{-13}");
t13.SetTextFont(42);
t13.Draw();

a14 = R.TArrow(106, max14, 109.2, max14, 0.02, "<|");
a14.Draw();
t14 = R.TLatex(109.3,max14*0.8,"at 10^{-14}");
t14.SetTextFont(42);
t14.Draw();

a15 = R.TArrow(106, max15, 109.2, max15, 0.02, "<|");
a15.Draw();
t15 = R.TLatex(109.3,max15*0.8,"at 10^{-15}");
t15.SetTextFont(42);
t15.Draw();

  
tic = R.TLatex(97.5,22,"#it{#mu #rightarrow eee#nu#bar{#nu}}");
tic.SetTextFont(42);
tic.SetTextColor(2);
tic.Draw();

tb = R.TLatex(102.5,1e-4,"#it{#mu #rightarrow eee#nu#bar{#nu}}");
tb.SetTextFont(42);
tb.SetTextColor(R.kBlue+3);
tb.Draw();

tb2 = R.TLatex(102.5,3e-5,"+Michel");
tb2.SetTextFont(42);
tb2.SetTextColor(R.kBlue+3);
tb2.Draw();

#leg.Draw("same")
R.gPad.RedrawAxis()
c.Print(outname)
text = raw_input()
