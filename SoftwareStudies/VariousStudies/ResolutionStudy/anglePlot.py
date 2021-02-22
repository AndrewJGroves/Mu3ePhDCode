import ROOT as R
import sys
import numpy as np
from math import sqrt

def runJob(fname):
    R.TH1.SetDefaultSumw2()
    h_file = R.TFile(fname,"read")
    t = h_file.Get("t1")
    px_true = None
    px_reco = None
    py_true = None
    py_reco = None
    pz_true = None
    pz_reco = None
    angleS = None
    pxl_true = None
    pxl_reco = None
    pyl_true = None
    pyl_reco = None
    pzl_true = None
    pzl_reco = None
    anglel = None
    pxl8_true = None
    pxl8_reco = None
    pyl8_true = None
    pyl8_reco = None
    pzl8_true = None
    pzl8_reco = None
    anglel8 = None
    for e in t:
        px_true = np.array(e.px_true)
        px_reco = np.array(e.px_reco)
        py_true = np.array(e.py_true)
        py_reco = np.array(e.py_reco)
        pz_true = np.array(e.pz_true)
        pz_reco = np.array(e.pz_reco)
        angleS = np.array(e.angleS)
        px_truel = np.array(e.pxl_true)
        px_recol = np.array(e.pxl_reco)
        py_truel = np.array(e.pyl_true)
        py_recol = np.array(e.pyl_reco)
        pz_truel = np.array(e.pzl_true)
        pz_recol = np.array(e.pzl_reco)
        anglel = np.array(e.anglel)
        px_truel8 = np.array(e.pxl8_true)
        px_recol8 = np.array(e.pxl8_reco)
        py_truel8 = np.array(e.pyl8_true)
        py_recol8 = np.array(e.pyl8_reco)
        pz_truel8 = np.array(e.pzl8_true)
        pz_recol8 = np.array(e.pzl8_reco)
        anglel8 = np.array(e.anglel8)
    p_reco =   np.sqrt( px_reco*px_reco + py_reco*py_reco + pz_reco*pz_reco )
    p_recol =  np.sqrt( px_recol*px_recol + py_recol*py_recol + pz_recol*pz_recol )
    p_recol8 = np.sqrt( px_recol8*px_recol8 + py_recol8*py_recol8 + pz_recol8*pz_recol8 )


    h_total  = R.TH2F("h_PAng", "Momentum Vs Ang", 200,-1.5,1.5,200,0,60);
    h_totalShort  = R.TH2F("h_PAngShort", "Momentum Vs Ang", 200,-1.5,1.5,200,0,60);
    h_totalLong  = R.TH2F("h_PAngLong", "Momentum Vs Ang", 200,-1.5,1.5,200,0,60);

    for i in range(len(p_reco)):
        h_total.Fill(angleS[i],p_reco[i]);
        h_totalShort.Fill(angleS[i],p_reco[i]);
    for i in range(len(p_recol)):
        h_total.Fill(anglel[i],p_recol[i]);
        h_totalLong.Fill(anglel[i],p_recol[i]);
    for i in range(len(p_recol8)):
        h_total.Fill(anglel8[i],p_recol8[i]);
        h_totalLong.Fill(anglel8[i],p_recol8[i]);

    f_out = R.TFile("test.root","recreate")
    h_totalShort.Divide(h_total)
    h_totalLong.Divide(h_total)
    c0 = R.TCanvas()
    h_totalShort.Draw("COLZ")
    h_totalShort.GetYaxis().SetTitle("p [MeV/c]")
    h_totalShort.GetXaxis().SetTitle("#lamda [rad]" )
    c0.Print("ShortAngle.png")
    c1 = R.TCanvas()
    h_totalLong.Draw("COLZ")
    h_totalLong.GetYaxis().SetTitle("p [MeV/c]")
    h_totalLong.GetXaxis().SetTitle("#lamda [rad]" )
    c1.Print("LongAngle.png")

    h_total.Write()
    h_totalShort.Write()
    h_totalLong.Write()



runJob("signal.root")
sys.exit()
