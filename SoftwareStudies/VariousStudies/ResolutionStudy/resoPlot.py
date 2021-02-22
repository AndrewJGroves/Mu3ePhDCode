import ROOT as R
import numpy as np

def plotter(g, tag, g_tdr, ymax):
    c0 = R.TCanvas()
    g.SetTitle("Momentum resolution of "+tag+" tracks")
    g.SetMarkerStyle(20)
    g.GetYaxis().SetRangeUser(0.,ymax)
    g.GetYaxis().SetTitle("#sigma [MeV]")
    g.GetXaxis().SetTitle("true track momentum [MeV]")
    g.Draw("APEL")
    g_tdr.SetLineColor(2)
    g_tdr.SetLineWidth(2)
    g_tdr.Draw("L,same")
    leg = R.TLegend(0.7,0.2,0.85,0.4)
    leg.AddEntry(g,"Liverpool Sample","LP")
    leg.AddEntry(g_tdr,"TDR line","L")
    leg.Draw("same")
    c0.Print("test_reso_"+tag+".png")


g_tdr_short =R.TGraph(6, np.array([12.,20.,30.,37.,45.,52.0]),np.array([0.5,1.0,1.5,2.0,2.5,2.9]))

g_tdr_long = R.TGraph(21, np.array([12.,14.,16.,18.,20.,22.,24.,26.,28.,30.,32.,34.,36.,38.,40.,42.,44.,46.,48.,50.,52.]),np.array([0.27,0.245,0.155,0.11,0.1,0.11,0.13,0.145,0.15,0.17,0.18,0.19,0.21,0.22,0.24,0.25,0.29,0.32,0.35,0.38,0.41]))


f1 = R.TFile("reso_short.root","read")
f2 = R.TFile("reso_long6.root","read")
#f3 = R.TFile("reso_long8.root","read")

g_new_short = f1.Get("Graph")
g_new_long6 = f2.Get("Graph")
#g_new_long8 = f3.Get("Graph")

plotter(g_new_short, "short", g_tdr_short, 3.)
plotter(g_new_long6, "long", g_tdr_long, 0.5)
#plotter(g_new_long8, "long8", g_tdr_long, 0.8)
