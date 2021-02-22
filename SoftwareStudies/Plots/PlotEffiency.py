import ROOT as R

f = R.TFile("./RootFiles/icmic_60mill.root","read")
h = f.Get("h_combi_clone;1")
c = R.TCanvas()

#h.SetMarkerStyle(21)
#h.SetMarkerSize(1.4)
h.SetStatisticOption(1)
h.SetTitle("Effiency to reconstruct 2+1")
h.Draw()
tex = R.TLatex(0.56, 0.83, "#mu3e, work in progress")
tex.SetNDC()
tex.Draw()

for i in range(31):
    bi = h.GetGlobalBin(i) 
    if (h.GetEfficiency(bi) > 0):
        print (' {0} &  {1:.5} \\\\'.format(bi,h.GetEfficiency(bi)))


c.Print("noraml.png")
