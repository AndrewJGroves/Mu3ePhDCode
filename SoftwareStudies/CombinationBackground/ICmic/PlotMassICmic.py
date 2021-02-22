import ROOT as R
from Style import AtlasStyle
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)
leg = R.TLegend(0.76,0.6,0.91,0.85)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  
c = R.TCanvas()

f_signal = R.TFile("../../RootFiles/signal.root","read")
f_IC     = R.TFile("../../RootFiles/IC.root","read")
f_ICmic  = R.TFile("/hepstore/agroves/ICmicRootFiles/ICmicAll.root","read")
h_IC2     = f_IC.Get("h_massLong")
h_sig1   = f_signal.Get("h_massLong")
h_ICmic  = f_ICmic.Get("h_mass")

outname = "../Figures/ICmic/FullMassSmooth_log.png"
histTitle = ["IC","10^{-12}","10^{-13}","10^{-14}","10^{-15}","IC + michel"]
axisLim = [95,110]

Ntarget = 1e15    
SigEfficiency =  0.227533#0.186341
NormFactor = SigEfficiency *  Ntarget 

# multiply now by the BR that you want
signalweight_12 = NormFactor*1e-12;
signalweight_13 = NormFactor*1e-13;
signalweight_14 = NormFactor*1e-14;
signalweight_15 = NormFactor*1e-15;
sigweight=[signalweight_12, signalweight_13 ,signalweight_14 ,signalweight_15 ]

#### normalization of the background
ICweightTot = 1.124e+13 
ICweightPass = 1.199e+09
ic_BR = 3.6e-5
ICscale = Ntarget * ic_BR * 4e-2 * 0.9 * 7.629000e-05 #ICweightPass/ICweightTot 

timming = 0.01
ic_acceptance = 0.62577 #For acceptance of 10 for pt and 0.8 costheata
mic_acceptance = 0.461745
ICmicScale = Ntarget * ic_BR * 2.0106373509e-07  * timming * ic_acceptance * 0.5 * mic_acceptance

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
    h.Scale(1./(h.Integral()  ))
    #h.Smooth()

#h_IC2.Rebin(2)
#h_ICmic.Rebin(2)
h_IC2.Scale(1./(h_IC2.Integral(0,9999999999999)))
h_ICmic.Scale(1./(h_ICmic.Integral(0,9999999999)))
#h_IC2.Smooth()
#h_ICmic.Smooth()

h_IC2.Scale(ICscale)
h_ICmic.Scale(ICmicScale)
h_IC=h_IC2.Clone()
h_IC.Add(h_ICmic)

#h_IC.Sumw2();
#h_ICmic.Sumw2();

h_IC.SetFillColor(R.kYellow)
h_ICmic.SetFillColor(R.kBlue+10)
h_IC.GetXaxis().SetTitle("m_{rec} [MeV/c^{2}]")
h_IC.GetYaxis().SetTitle("Number of Vertices")
h_IC_tot = h_IC.Integral()
err1 = R.Double(0.0)
n1=516#258
n2=551#275
h_ICmic.IntegralAndError(n1,n2,err1)
err2 = R.Double(0.0)
h_IC2.IntegralAndError(n1,n2,err2)
errortot=0.0
for i in range(n1,n2):
    print "Bin edge", h_ICmic.GetBinLowEdge(i), " Entries ",  h_ICmic.GetBinContent(i), " error ", h_ICmic.GetBinError(i)
    errortot+=h_ICmic.GetBinError(i)
print "Error check ", errortot
print "IC and michel estimate in the signal region of 103-110 is ", h_ICmic.Integral(n1,n2)," +- ", err1
print "IC estimate in the signal region of 103-110 is ",  h_IC2.Integral(n1,n2)," +- ", err2

binmax = h_IC.GetBinContent( h_IC.GetMaximumBin()  )
useLog = False
if "_log" in outname:
#    h_IC.GetYaxis().SetRangeUser(5e-5,1e2)
    R.gPad.SetLogy(1)
    useLog = True
else:
    R.gPad.SetLogy(0)
    
leg.AddEntry(h_IC, histTitle[0], "F")
leg.AddEntry(h_ICmic, histTitle[len(histTitle)-1], "F")
leg.AddEntry(h_IC, "BR(#mu #rightarrow eee)", "")
if len(axisLim) > 0:
    if axisLim[0] < axisLim[1]:
        h_IC.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])

h_IC.Draw("HIST")
h_ICmic.Draw("HIST,same")
h_IC.Draw("E1,same")
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

tex = R.TLatex(0.62, 0.87, "#mu3e, work in progress")
tex.SetNDC()
tex.Draw()

leg.Draw("same")
R.gPad.RedrawAxis()
c.Print(outname)
text = raw_input()
