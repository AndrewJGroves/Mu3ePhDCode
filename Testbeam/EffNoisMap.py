import ROOT as R
from Style import AtlasStyle
import math
import sys
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits(  )
R.gStyle.SetPalette(1)

f9 = R.TFile("analysis_PSI_2019_10_002164-002184_dut-01_searchWindow-0900_timeCut-0100_HP-REMOVAL-OFF_new.root","read")
h_eff=f9.Get("MatchingHistograms_DUT_1/efficiency/efficiency_map")
h_noise=f9.Get("MatchingHistograms_DUT_1/efficiency/noise_map")
h_map=f9.Get("TrackHistograms/track_position_map")

f8 = R.TFile("analysis_001436-001436_dut-01_searchWindow-0400_timeCut-0020_HP-REMOVAL-OFF.root","read")
h_eff=f8.Get("layer_1_matchingHists/efficiency")
h_noise=f8.Get("layer_1_matchingHists/noise_rate")

mupix = sys.argv[1]
R.gStyle.SetPalette(R.kViridis)

c = R.TCanvas()       
h_eff.GetXaxis().SetTitle("col / pixel")
h_eff.GetYaxis().SetTitle("row / pixel")
h_eff.GetZaxis().SetTitle("Efficiency")
if(int(mupix) == 8):
    h_eff.GetXaxis().SetRangeUser(0,49)
    h_eff.GetYaxis().SetRangeUser(0,200)
if(int(mupix) == 9):
    h_noise.GetXaxis().SetRangeUser(0,49)
    h_noise.GetYaxis().SetRangeUser(0,19)
h_eff.Draw("COLZ")
c.Print("Plots/effmap"+str(mupix)+".png")

c1 = R.TCanvas()       
h_noise.GetXaxis().SetTitle("col / pixel")
h_noise.GetYaxis().SetTitle("row / pixel")
h_noise.GetZaxis().SetTitle("Noise rate / Hz")
if(int(mupix) == 8):
    h_eff.GetXaxis().SetRangeUser(0,49)
    h_eff.GetYaxis().SetRangeUser(0,200)
if(int(mupix) == 9):
    h_noise.GetXaxis().SetRangeUser(0,49)
    h_noise.GetYaxis().SetRangeUser(0,19)
R.gPad.SetLogz(1)
h_noise.Draw("COLZ")
c1.Print("Plots/noisemap"+str(mupix)+".png")

if(int(mupix) != 8):
    c2 = R.TCanvas()       
    #h_map.GetXaxis().SetTitle("col / pixel")
    #h_noie.GetYaxis().SetTitle("row / pixel")
    h_map.GetXaxis().SetRangeUser(0,4000)
    h_map.GetYaxis().SetRangeUser(0,16000)
    h_map.Draw("COLZ")
    c2.Print("Plots/trackmap"+str(mupix)+".png")
