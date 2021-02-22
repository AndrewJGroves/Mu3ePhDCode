import ROOT as R
from math import sqrt, cos

"""

random distribution

"""


def d0R(dR, theta):
    return sqrt(1+dR**2 + 2*cos(theta)*dR ) - dR


def getRandomDOR(ran, h):
    dor = ran.Uniform(0,1.2)
    w = h.GetBinContent(  h.FindBin(dor) )
    return [dor, w]


f = R.TFile("plots.root","read")
hDOR = f.Get("h_doR")
hDOR.Scale(1./hDOR.Integral())

h_dr = f.Get("h_dR")

nb = h_dr.GetNbinsX()
xmin = h_dr.GetBinLowEdge(1)
xmax = h_dr.GetBinLowEdge(nb+1)

h = R.TH1F("h", "h", nb, xmin, xmax)


h1 = R.TH1F("h1", "h1", nb, xmin, xmax)
h2 = R.TH1F("h2", "h2", nb, xmin, xmax)
h3 = R.TH1F("h3", "h3", nb, xmin, xmax)

ran = R.TRandom3()

nb = hDOR.GetNbinsX()
xmin = hDOR.GetBinLowEdge(1)
xmax = hDOR.GetBinLowEdge(nb+1)

h_dor_test = R.TH1F("h_dor_test", "h_dor_test", nb, xmin, xmax)

#dR = 0.5

for i in range(10000):
    theta = ran.Uniform(0, 2*R.TMath.Pi())
    dor = getRandomDOR(ran, hDOR)
    d = d0R(dor[0], theta)
    h.Fill(d, dor[1])
    h_dor_test.Fill(dor[0], dor[1])
    
    d = d0R(0.3, theta)
    h1.Fill(d)

    d = d0R(0.5, theta)
    h2.Fill(d)

    d = d0R(1.0, theta)
    h3.Fill(d)

    

R.gROOT.SetStyle("ATLAS")
c = R.TCanvas()
h.SetFillColor(R.kYellow + 1)
h.SetLineColor(R.kYellow + 2)
h.GetXaxis().SetTitle("d/R")
h.DrawNormalized("HIST")


#h1.SetLineColor(4)
#h1.SetLineWidth(2)
#h1.SetLineStyle(9)
#h1.DrawNormalized("HIST,same")
h_dr.SetLineColor(4)
h_dr.SetLineWidth(2)
h_dr.SetLineStyle(9)
h_dr.DrawNormalized("HIST,same")

h2.SetLineColor(4)
h2.DrawNormalized("HIST,same")

h3.SetLineColor(2)

h3.DrawNormalized("HIST,same")

leg = R.TLegend(0.2,0.5, 0.5, 0.9)

leg.AddEntry(h, "d_{0}/R exp. from random", "F")
leg.AddEntry(h_dr, "from simul.", "L")
leg.AddEntry(h2, "d_{0}/R = 0.5", "L")
leg.AddEntry(h3, "d_{0}/R = 1.0", "L")

leg.Draw("same")

c.Print("D0R.png")

## plot the distribution
c1 = R.TCanvas()
hDOR.SetFillColor(R.kYellow+2)
hDOR.Draw("HIST")
h_dor_test.SetLineColor(4)
h_dor_test.SetLineWidth(2)
h_dor_test.DrawNormalized("HIST,same")
c1.Print("test_d0R_MC.png")
