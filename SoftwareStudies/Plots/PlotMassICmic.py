import ROOT as R
from Style import AtlasStyle
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)
leg = R.TLegend(0.2,0.6,0.35,0.85)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  
c = R.TCanvas()

f_signal = R.TFile("../RootFiles/signal_noTree.root","read")
f_IC     = R.TFile("../RootFiles/IC_noTree.root","read")
f_ICmic  = R.TFile("../RootFiles/ICmic_noTree.root","read")
h_IC     = f_IC.Get("h_mass")
h_sig1   = f_signal.Get("h_mass")
h_ICmic  = f_ICmic.Get("h_mass")

outname = "Figures/FullMass_log.png"
histTitle = ["IC","10^{-12}","10^{-13}","10^{-14}","10^{-15}","10^{-16}","IC + michel"]
axisLim = [95,110]



Ntarget = 1e15    
SigEfficiency = 0.210218
NormFactor = SigEfficiency *  Ntarget 

# multiply now by the BR that you want
signalweight_12 = NormFactor*1e-12;
signalweight_13 = NormFactor*1e-13;
signalweight_14 = NormFactor*1e-14;
signalweight_15 = NormFactor*1e-15;
signalweight_16 = NormFactor*1e-16;
sigweight=[signalweight_12, signalweight_13 ,signalweight_14 ,signalweight_15,signalweight_16 ]

#### normalization of the background
ICweightTot = 230926919138.993164 
ICweightPass = 28100303
ic_BR = 3.6e-5
ICscale = Ntarget * ic_BR * 4e-2 * 0.9 * 7.629000e-05 #ICweightPass/ICweightTot 

timming = 0.01
ic_acceptance = 0.62577 #For acceptance of 10 for pt and 0.8 costheata

ICmicScale = Ntarget * ic_BR * 197682708/183767577535133.81250 * timming * ic_acceptance * 0.5 * 0.80


h_sig12=h_sig1.Clone()
h_sig13=h_sig1.Clone()
h_sig14=h_sig1.Clone()
h_sig15=h_sig1.Clone()
h_sig16=h_sig1.Clone()
h_sig=[h_sig12,h_sig13,h_sig14,h_sig15,h_sig16]


# you need to start with shape: normalize them to unity
for h in h_sig:
    nbins = h.GetNbinsX()
    xmin = h.GetBinLowEdge(1)
    xmax = h.GetBinLowEdge(nbins+1)
    h.Scale(1./(h.Integral(0,nbins+1)  ))
h_IC.Scale(1./(h_IC.Integral(0,9999999999999)))
h_ICmic.Scale(1./(h_ICmic.Integral(0,9999999999)))


h_IC.SetFillColor(R.kYellow)
h_ICmic.SetFillColor(R.kBlue+10)
h_IC.GetXaxis().SetTitle("m_{rec} [MeV/c^{2}]")
h_IC.GetYaxis().SetTitle("Number of Vertices")
h_IC_tot = h_IC.Integral()
h_IC.Scale(ICscale)
h_ICmic.Scale(ICmicScale)

err1 = R.Double(0.0)
h_ICmic.IntegralAndError(476,551,err1)
err2 = R.Double(0.0)
h_IC.IntegralAndError(517,551,err2)

print "IC and michel estimate in the range ",axisLim[0], " to " ,axisLim[1], " is ",  h_ICmic.Integral(517,551)," +- ", err1
print "IC estimate in the signal region of 103-110 is ",  h_IC.Integral(517,551)," +- ", err2

binmax = h_IC.GetBinContent( h_IC.GetMaximumBin()  )
useLog = False
if "_log" in outname:
    h_IC.GetYaxis().SetRangeUser(5e-5,1e2)
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
h_IC.Draw("E1,same")
h_ICmic.Draw("HIST,same")
h_ICmic.Draw("E1,same")

tot = 0.0
num = 0
for i in range(476,551):
    tot += h_ICmic.GetBinContent(i)
    num += 1
mean = tot/num
gr = R.TGraph()
gr.SetPoint(1,90,mean)
gr.SetPoint(2,115,mean)
gr.SetLineWidth(3)
gr.Draw("L,same")

esti = (110-103)*mean

print "No events predicted inside the signal region for IC + michel ",esti

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
    leg.AddEntry(h_sig[i], histTitle[i+1], "L")
    i_binmax = h_sig[i].GetBinContent( h_sig[i].GetMaximumBin()  )
    if i_binmax > binmax:
        binmax = i_binmax
    if not useLog:
        h_IC.GetYaxis().SetRangeUser(0, binmax)
                
leg.Draw("same")
R.gPad.RedrawAxis()
c.Print(outname)
text = raw_input()
