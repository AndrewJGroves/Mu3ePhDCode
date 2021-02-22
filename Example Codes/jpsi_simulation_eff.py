from ROOT import *
import math
from decimal import *
f=TFile('jpsi_100k_spincor.root')
g=f.Get('T;1')
c=TCanvas("Effiency","Effiency",700,500);
#c1=TCanvas("Effiency1","Effiency1",700,500);
gStyle.SetOptStat("0")


nbin = 10;
hlo = 2.;
hhi = 4.5;
"""
muacc_all =TH1F("acc_all","acc_all",nbin,hlo,hhi);
muacc_pass =TH1F("acc_pass","acc_pass",nbin,hlo,hhi);
muacc_eff =TH1F("acc_eff","acc_eff",nbin,hlo,hhi);
track_all =TH1F("track_all","track_all",nbin,hlo,hhi);
track_pass =TH1F("track_pass","track_pass",nbin,hlo,hhi);
track_eff =TH1F("track_eff","track_eff",nbin,hlo,hhi);

muon_all =TH1F("muon_all","muon_all",nbin,hlo,hhi);
muon_pass =TH1F("muon_pass","muon_pass",nbin,hlo,hhi);
muon_eff =TH1F("muon_eff","muon_eff",nbin,hlo,hhi);

trig_all =TH1F("trig_all","trig_all",nbin,hlo,hhi);
trig_pass =TH1F("trig_pass","trig_pass",nbin,hlo,hhi);
trig_eff =TH1F("trig_eff","trig_eff",nbin,hlo,hhi);
"""
cut_all =TH1F("cut_all","cut_all",nbin,hlo,hhi);
cut_pass =TH1F("cut_pass","cut_pass",nbin,hlo,hhi);
cut_eff =TH1F("cut_eff","cut_eff",nbin,hlo,hhi);

e_cuttA,e_cuttB = 0, 0
e_tracktA,e_tracktB = 0, 0
e_muatA,e_muatB = 0, 0
e_muontA,e_muontB = 0, 0
e_trigtA,e_trigtB =0,0
for i, e in enumerate(g):
    if (i%10000==0): print "Entry ",i
    muon1=TLorentzVector()
    muon2=TLorentzVector()
    trmuon1=TLorentzVector()
    trmuon2=TLorentzVector()

    if e.nout==1:
        em1 = math.sqrt(e.px[0]**2+e.py[0]**2+e.pz[0]**2+105.**2);
        muon1.SetPxPyPzE(e.px[0],e.py[0],e.pz[0],em1)
    if e.nout==2:
        em1 = math.sqrt(e.px[0]**2+e.py[0]**2+e.pz[0]**2+105.**2);
        em2 = math.sqrt(e.px[1]**2+e.py[1]**2+e.pz[1]**2+105.**2);
        muon1.SetPxPyPzE(e.px[0],e.py[0],e.pz[0],em1)
        muon2.SetPxPyPzE(e.px[1],e.py[1],e.pz[1],em2)
        muont=muon1+muon2
    else:
        muont=muon1
    
    tem1 = math.sqrt(e.trupx[0]**2+e.trupy[0]**2+e.trupz[0]**2+105.**2);
    tem2 = math.sqrt(e.trupx[1]**2+e.trupy[1]**2+e.trupz[1]**2+105.**2);
    trmuon1.SetPxPyPzE(e.trupx[0],e.trupy[0],e.trupz[0],tem1)
    trmuon2.SetPxPyPzE(e.trupx[1],e.trupy[1],e.trupz[1],tem2)
    trmuont=trmuon1+trmuon2
    praptr1=trmuon1.PseudoRapidity()
    praptr2=trmuon2.PseudoRapidity()
    
    if e.nphotons==1:
        pang=e.phy[0]/e.phz[0]
        phe = math.sqrt(e.phx[0]**2+e.phy[0]**2+e.phz[0]**2)
    prap1=muon1.PseudoRapidity()
    prap2=muon2.PseudoRapidity()
    if e.nout==1:ang1=e.py[0]/e.pz[0]
    if e.nout==2:ang2=e.py[1]/e.pz[1]


    """
    #---Track effiency ----------------------------------------------------
    if  2<=praptr1 and praptr1<=4.5 and 2<=praptr2 and praptr2<=4.5:
        e_tracktB=e_tracktB+1
        track_all.Fill(trmuont.Rapidity())
    if  e.nlong==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5:
        e_tracktA=e_tracktA+1
        track_pass.Fill(muont.Rapidity())

    
    #----Muacc effiency -----------------------------------------------------
    if e.nlong==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5:
        e_muatB=e_muatB+1
        muacc_all.Fill(muont.Rapidity())
    if e.nlong==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5 and e.muacc[0]==1 and e.muacc[1]==1 :
        e_muatA=e_muatA+1
        muacc_pass.Fill(muont.Rapidity())
    
    #----Muon effiency -----------------------------------------------------
    if e.nlong==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5 and e.muacc[0]==1 and e.muacc[1]==1:
        e_muontB=e_muontB+1
        muon_all.Fill(muont.Rapidity())
    if e.nlong==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5 and e.muon[0]==1 and e.muon[1]==1 and e.muacc[0]==1 and e.muacc[1]==1:
        e_muontA=e_muontA+1
        muon_pass.Fill(muont.Rapidity())
    
    #----Trigger effiency -----------------------------------------------------
    if e.nlong==2 and e.nout==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5 and e.muon[0]==1 and e.muon[1]==1:
        e_trigtB=e_trigtB+1
        trig_all.Fill(muont.Rapidity())
    if e.nout==2 and e.nlong==2 and 2<=prap1 and prap1<=4.5 and 2<=prap2 and prap2<=4.5 and e.muon[0]==1 and e.muon[1]==1 and e.trigmu>1:
        e_trigtA=e_trigtA+1
        trig_pass.Fill(muont.Rapidity())
    """
    if  e.nphotons==1 and e.nout==2:
        e_cuttB=e_cuttB+1
        cut_all.Fill(muont.Rapidity())
    if e.nphotons==1 and e.nout==2 and phe>200 and (pang-0.014>ang1 or ang1>pang+0.014) and (pang-0.014>ang2 or ang2>pang+0.014) and (e.etprev1<150 or e.etprev2<150) and e.nspd<=7:
        e_cuttA=e_cuttA+1
        cut_pass.Fill(muont.Rapidity())
    
    
"""

#---Track plotting and calc ---------------------------------------
c.cd()
track_eff.SetTitleOffset(1.2,"y")
track_eff.SetYTitle("Efficiency")
track_eff.SetXTitle("Rapidity")
track_eff.Divide(track_pass,track_all,1.0,1.0,"B");
track_eff.Draw()
e_track=float(e_tracktA)/float(e_tracktB)
print e_track
c.Print("/Users/Andrew/Google Drive/Masters project/Graphs/effiency/track_eff.pdf")

#---Muacc plotting and calc ---------------------------------------
c1.cd()
muacc_eff.SetTitleOffset(1.2,"y")
muacc_eff.SetYTitle("Efficiency")
muacc_eff.SetXTitle("Rapidity")
muacc_eff.Divide(acc_pass,acc_all,1.0,1.0,"B");
muacc_eff.Draw()
e_muat=float(e_muatA)/float(e_muatB)
print e_muat
c1.Print("/Users/Andrew/Google Drive/Masters project/Graphs/effiency/muacc_eff.pdf")


#---Muon plotting and calc ---------------------------------------
c.cd()
muon_eff.SetTitleOffset(1.2,"y")
muon_eff.SetYTitle("Efficiency")
muon_eff.SetXTitle("Rapidity")
muon_eff.Divide(muon_pass,muon_all,1.0,1.0,"B");
muon_eff.Draw()
e_muon=float(e_muontA)/float(e_muontB)
print e_muon
c.Print("/Users/Andrew/Google Drive/Masters project/Graphs/effiency/muon_eff.pdf")


#---Trigger plotting and calc ---------------------------------------
c1.cd()
trig_eff.SetTitleOffset(1.2,"y")
trig_eff.SetYTitle("Efficiency")
trig_eff.SetXTitle("Rapidity")
trig_eff.Divide(trig_pass,trig_all,1.0,1.0,"B");
trig_eff.Draw()
e_trig=float(e_trigtA)/float(e_trigtB)
c1.Print("/Users/Andrew/Google Drive/Masters project/Graphs/effiency/trig_eff.pdf")

"""
cut_eff.SetTitleOffset(1.2,"y")
cut_eff.SetYTitle("Efficiency")
cut_eff.SetXTitle("Rapidity")
cut_eff.Divide(cut_pass,cut_all,1.0,1.0,"B");
cut_eff.Draw()
e_cut=float(e_cuttA)/float(e_cuttB)
c.Print("/Users/Andrew/Google Drive/Masters project/Graphs/effiency/cut_eff.pdf")
