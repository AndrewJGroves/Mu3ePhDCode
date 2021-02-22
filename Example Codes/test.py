import ROOT as R


myfile = R.TFile("../StandardTMVA/mlpHiggs.root","read")

mytree = myfile.Get("sig_filtered")

print 'This mytree has',mytree.GetEntries(),"entries"

h = R.TH1F("h","h",100,0.,0.5)

for i in range(0,100):
    mytree.GetEntry(i)
    print mytree.ptsumf
    h.Fill(mytree.ptsumf)

c = R.TCanvas()
h.Draw()
c.Print("test.png")
