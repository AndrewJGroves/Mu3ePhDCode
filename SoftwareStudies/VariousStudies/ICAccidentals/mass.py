import ROOT as R
from Style import AtlasStyle

style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)


f_signal = R.TFile("../../RootFiles/signal.root","read")
f_bkg    = R.TFile("plots2020.root","read")
h_mic1=f_bkg.Get("mass1_mass95mom8")
h_mic2=f_bkg.Get("mass2_mass95mom8")

h_sig1=f_signal.Get("h_mass")


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

h_mic1.Scale(1./(h_mic1.Integral(0,nbins+1)))
h_mic2.Scale(1./(h_mic2.Integral(0,nbins+1)))

print 'bin width: ',h_sig12.GetBinWidth(1)
#rebin = 0
outname = "mass_log2.png"
histTitle = ["Background","10^{-12}","10^{-13}","10^{-14}","10^{-15}"]
axisLim = [95,110]

Ntarget = 1e15    
SigEfficiency = 0.186341
NormFactor = SigEfficiency *  Ntarget 

# multiply now by the BR that you want
signalweight_12 = NormFactor*1e-12;
signalweight_13 = NormFactor*1e-13;
signalweight_14 = NormFactor*1e-14;
signalweight_15 = NormFactor*1e-15;
sigweight=[signalweight_12, signalweight_13 ,signalweight_14 ,signalweight_15 ]

#### normalization of the background
"""
ICefficiency = 0.000430953592521 # 4.05e-06  #  0.066847  #  
ic_BR = 3.4e-5
intscale = Ntarget * ICefficiency * ic_BR 
"""

ic_BR = 3.4e-5
timing_eff = 0.0140845
rec_eff = 0.9
gen_eff = 500000000.0/22134371064.0
mic1_eff=7.422768e+06/5.309941e+09
mic2_eff=2.798887e+03/6.051550e+06
ic_acceptance = 0.62577 
mic_acceptance = 0.461745

mic2scale=Ntarget * mic2_eff * ic_BR * rec_eff * gen_eff * ic_acceptance * mic_acceptance * timing_eff * timing_eff

mic1scale=Ntarget * mic1_eff * ic_BR * rec_eff * gen_eff * ic_acceptance * mic_acceptance * timing_eff 
print "mic 1 ", mic1scale
print "mic 2 ", mic2scale


h_mic2.SetFillColor(R.kYellow)

h_mic2.GetXaxis().SetTitle("Mass (MeV)")
h_mic2.GetYaxis().SetTitle("Number of vertieces")
h_mic2_tot = h_mic2.Integral()
h_mic2.Scale(mic2scale)
h_mic1.Scale(mic1scale)

h_mic1.SetFillColor(R.kCyan)


binmax = h_mic2.GetBinContent( h_mic1.GetMaximumBin()  )
useLog = False
if "_log" in outname:
    h_mic2.GetYaxis().SetRangeUser(5e-4,1e2)
    R.gPad.SetLogy(1)
    useLog = True
else:
    R.gPad.SetLogy(0)
    
#leg.AddEntry(h_mic1, histTitle[0], "F")
leg.AddEntry(h_mic2, "Michel 2", "F")
leg.AddEntry(h_mic1, "Michel 1", "F")


h_mic2.GetXaxis().SetRangeUser(95, 110)
h_mic1.GetXaxis().SetRangeUser(95, 110)


h_mic2.Draw("HIST")
#h_mic1L.Draw("HIST,same")
#h_mic1M.Draw("HIST,same")
#h_mic1H.Draw("HIST,same")
#h_mic2L.Draw("HIST,same")
#h_mic2M.Draw("HIST,same")
#h_mic2H.Draw("HIST,same")
h_mic1.Rebin(8)
h_mic1.Draw("HIST,same")
h_mic1.Draw("E1,same")



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
        h_mic2.GetYaxis().SetRangeUser(0, binmax)
       
    
tex = R.TLatex(1,1,"XXX")
tex.SetNDC()
tex.SetTextAlign(11);
tex.SetTextColor(1);
tex.SetTextFont(42);
tex.SetTextSize(0.05);  
#tex.DrawLatex(0.2,0.87,"Scaling = 1000")

   
leg.Draw("same")
R.gPad.RedrawAxis()
c.Print(outname)
mic1_err=R.Double(0.0)
mic2_err = R.Double(0.0)
h_mic2.IntegralAndError(0,99999,mic2_err)
h_mic1.IntegralAndError(0,99999,mic1_err)
print "2 mic intgral ", h_mic2.Integral(0, 9999999)
print "2 mic error ", mic2_err
print "1 mic intgral ", h_mic1.Integral(0,999999)
print "1 mic error ", mic1_err
text = raw_input()
