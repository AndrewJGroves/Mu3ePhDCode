import ROOT as R
from Style import AtlasStyle

style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)


ICeff = 0.006903 * 3.094575e-06
SigEff = 0.149873
Ntarget =2.5e15

#### normalization of the background
ic_BR = 3.6e-5
ICscale = Ntarget * ic_BR * 0.9 * ICeff

f_signal = R.TFile("../TDRSensitity/signal.root","read")
f_bkg    = R.TFile("../TDRSensitity/IC.root","read")
h_bkg=f_bkg.Get("h_massLong;1")
h_sig1=f_signal.Get("h_massLong")

print "h_bkg integral:", h_bkg.Integral()

leg = R.TLegend(0.2,0.6,0.35,0.85)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  
c = R.TCanvas()

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
    #h.Scale(nbins/(h.Integral(0,nbins+1)* (xmax-xmin)  ))
    h.Scale(1./(h.Integral(0,nbins+1)  ))

h_bkg.Scale(1./(h_bkg.Integral(0,nbins+1)))
print 'bin width: ',h_sig12.GetBinWidth(1)
#rebin = 0
outname = "Figures/mass_log.png"
histTitle = ["Background","10^{-12}","10^{-13}","10^{-14}","10^{-15}"]
axisLim = [95,110]


NormFactor = SigEff *  Ntarget * 0.9
# multiply now by the BR that you want
signalweight_12 = NormFactor*1e-12;
signalweight_13 = NormFactor*1e-13;
signalweight_14 = NormFactor*1e-14;
signalweight_15 = NormFactor*1e-15;
sigweight=[signalweight_12, signalweight_13 ,signalweight_14 ,signalweight_15 ]



            
h_bkg.SetFillColor(R.kYellow)
h_bkg.GetXaxis().SetTitle("Mass (MeV)")
h_bkg.GetYaxis().SetTitle("Number of vertieces")
h_bkg_tot = h_bkg.Integral()
h_bkg.Scale(ICscale)

n1=h_bkg.GetXaxis().FindBin(103.0001)
n2=h_bkg.GetXaxis().FindBin(109.9999)
for i in range(n1,n2):
    print "Bin edge", h_bkg.GetBinLowEdge(i), " Entries ",  h_bkg.GetBinContent(i), " error ", h_bkg.GetBinError(i)
err2 = R.Double(0.0)
h_bkg.IntegralAndError(n1,n2,err2)
print "IC estimate in the signal region of 103-110 is ",  h_bkg.Integral(n1,n2)," +- ", err2


#if rebin>0:
#    h_bkg.Rebin(rebin)
binmax = h_bkg.GetBinContent( h_bkg.GetMaximumBin()  )
useLog = False
if "_log" in outname:
    h_bkg.GetYaxis().SetRangeUser(5e-4,1e2)
    R.gPad.SetLogy(1)
    useLog = True
else:
    R.gPad.SetLogy(0)
    
leg.AddEntry(h_bkg, histTitle[0], "F")
leg.AddEntry(h_bkg, "BR(#mu #rightarrow eee)", "")
if len(axisLim) > 0:
    if axisLim[0] < axisLim[1]:
        print 'Set axis limits ',axisLim
        h_bkg.GetXaxis().SetRangeUser(axisLim[0], axisLim[1])
            
h_bkg.Draw("HIST")
h_bkg.SetMarkerStyle(1)
h_bkg.Draw("E1,same")

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
        h_bkg.GetYaxis().SetRangeUser(0, binmax)
                
leg.Draw("same")
R.gPad.RedrawAxis()
c.Print(outname)
text = raw_input()
