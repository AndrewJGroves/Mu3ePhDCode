import ROOT as R
from Style import AtlasStyle
import math
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits(  )
R.gStyle.SetPalette(1)


def mapc(h,axisLim,outname):
    c = R.TCanvas("c","c",300,400)
    R.gStyle.SetPalette(R.kViridis)
    if axisLim[0] < axisLim[1]:
        h.GetXaxis().SetRangeUser(axisLim[0],axisLim[1])
    if axisLim[2] < axisLim[3]:
        h.GetYaxis().SetRangeUser(axisLim[2],axisLim[3])
    h.Draw("COLZ")
    c.Print("./Plots/Cluster/"+outname)

f = R.TFile("analysis_001436-001436_dut-01_searchWindow-0400_timeCut-0020_HP-REMOVAL-OFF.root","read")

h_vert=f.Get("cluster_1_matched_hits__cornersCounted/vertical_size")
h_hor=f.Get("cluster_1_matched_hits__cornersCounted/horizontal_size")
leg = R.TLegend(0.75,0.65,0.9,0.9)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  
c = R.TCanvas()       
h_vert.GetXaxis().SetRangeUser(0, 9)
h_vert.SetLineColor(R.kRed)
h_hor.SetLineColor(R.kBlack)
leg.AddEntry(h_vert, "Vertical", "L")
leg.AddEntry(h_hor, "Horizontal", "L")
R.gPad.SetLogy(1)
h_vert.Draw()
h_hor.Draw("same")
leg.Draw()
c.Print("./Plots/Cluster/horver.png")
totalhor = 0.
totalvert = 0.
for i in range(3,20):
    print "i ",i
    totalhor += h_hor.GetBinContent(i)
    totalvert += h_vert.GetBinContent(i)
print "Total horizontal ", totalhor
print "Total Vertial ", totalvert
eff2=h_vert.GetBinContent(3)/totalvert - h_hor.GetBinContent(3)/totalhor
eff3=h_vert.GetBinContent(4)/totalvert - h_hor.GetBinContent(4)/totalhor
print "Eff 2 ",eff2
print "Eff 3 ",eff3

h_all=f.Get("cluster_1_matched_hits__cornersCounted/clusterposition")
h_1=f.Get("cluster_1_matched_hits__cornersCounted/clusterposition_1hit")
h_2=f.Get("cluster_1_matched_hits__cornersCounted/clusterposition_2hit")
h_3=f.Get("cluster_1_matched_hits__cornersCounted/clusterposition_3hit")
mapc(h_all,[0,48,0,0],"clusterMap.png")
mapc(h_1,[0,48,0,0],"clusterMap_1hit.png")
mapc(h_2,[0,48,0,0],"clusterMap_2hit.png")
mapc(h_3,[0,48,0,0],"clusterMap_3hit.png")


h_verAll=f.Get("cluster_1_matched_hits__cornersCounted/vertical_pos")
h_ver2=f.Get("cluster_1_matched_hits__cornersCounted/vertical_double_pos")
h_ver3=f.Get("cluster_1_matched_hits__cornersCounted/vertical_triple_pos")
#h_horAll=f.Get("cluster_1_matched_hits__cornersCounted/horizontal_pos")
h_hor2=f.Get("cluster_1_matched_hits__cornersCounted/horizontal_double_pos")
h_hor3=f.Get("cluster_1_matched_hits__cornersCounted/horizontal_triple_pos")

