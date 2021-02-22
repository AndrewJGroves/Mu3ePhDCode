from ROOT import *
import math
import time
import real_cal
t0 = time.time()
def fit(hist,f,colour,title,xaxis):  
    #hist.Draw(f)
    hist.SetLineColor(colour)
    hist.SetTitle(title)
    hist.SetYTitle("No of Events")
    hist.SetXTitle(xaxis)
    hist.DrawNormalized(f)
c=TCanvas("Number of Photons","Number of Photons",650,500); 
#c.Divide(2,1)
gStyle.SetOptStat("0")
#gStyle.SetOptStat("u")

f=TFile('merge_u_calculated_1photon.root')
g=f.Get('T')
f1=TFile('jpsi_100k_spincor.root')
g1=f1.Get('T;1')

#hist_nopho=TH1F("number of photons","number of photons",10,-0.5,9.5)

hist_Pt=TH1F("Transverse momentum","Transverse momentum",100,-0.5,2999.5)
hist_rap=TH1F("Rapidity","Rapidity",50,0,7)
hist_prap=TH1F("Psudorapidity","Psudorapidity",100,0,10)
hist_Pts=TH1F("Transverse momentum","Transverse momentum",100,-0.5,2999.5)
hist_raps=TH1F("Rapidity","Rapidity",50,0,7)
hist_praps=TH1F("Psudorapidity","Psudorapidity",100,0,10)
"""
hist_sPt=TH1F("Transverse momentum of chic","Transverse momentum of chic",100,-0.5,2999.5)
hist_srap=TH1F("Rapidity of chic","Rapidity of chic",100,-2,10)
hist_sprap=TH1F("Psudorapidity of chic","Psudorapidity of chic",100,-2,10)

hist_lsPt=TH1F("Transverse momentum of chic lim","Transverse momentum of chic lim",100,-0.5,2999.5)
hist_lsrap=TH1F("Rapidity of chic lim","Rapidity of chic lim",100,-2,10)
hist_lsprap=TH1F("Psudorapidity of chic lim","Psudorapidity of chic lim",100,-2,10)


hist_phi=TH1F("Photon phi","Photon phi",500,-2,2)
hist_phoe=TH1F("Photon Energy","Photon Energy",200,0,2000)
hist_phopt=TH1F("Photon transverse momentum","Photon transverse momentum",200,0,500)
hist_prappho=TH1F("Psudorapidity of photon","Psudorapidity of photon",100,0,10)
hist_lphoe=TH1F("Photon Energy lim","Photon Energy lim",200,0,2000)
hist_lphopt=TH1F("Photon transverse momentum lim","Photon transverse momentum lim",200,0,500)
hist_lprappho=TH1F("Psudorapidity of photon lim","Psudorapidity of photon lim",100,0,10)
"""

muon1=TLorentzVector()
muon2=TLorentzVector()
muont=TLorentzVector()
for i, e in enumerate(g1):
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
        
    if e.nlong==2:
        #hist_Pts.Fill(muont.Pt())
        #hist_raps.Fill(muont.Rapidity())
        hist_praps.Fill(muont.PseudoRapidity())

n=100000

for i, e in enumerate(g):
    if (i%10000==0): print "Entry ",i
    #if i>n: break
    #leg_prapl.SetBorderSize(0)
    #muon1,muon2,photon,muont,sys,ang1,ang2,pang = real_cal.cal(e)
    #if e.nphotons==1:phe = math.sqrt(e.phx[0]**2+e.phy[0]**2+e.phz[0]**2);
    #phi=math.atan(e.phy[0]/e.phx[0])
    #hist_nopho.Fill(e.nphotons)
    
    #hist_Pt.Fill(e.pt)
    
    #hist_rap.Fill(e.rap)
    hist_prap.Fill(e.prap)
    
    #hist_sPt.Fill(e.spt)
    #hist_srap.Fill(e.srap)
    #hist_sprap.Fill(e.sprap)
    
    """
    if (phi<1.12 or phi>1.16):
        hist_lprappho.Fill(e.prap_pho)
        hist_phi.Fill(phi)
    #hist_phoe.Fill(phe)
    #hist_phopt.Fill(e.phopt)
    hist_prappho.Fill(e.prap_pho)
    
    if (e.pang-0.014>e.ang1 or e.ang1>e.pang+0.014) and (e.pang-0.014>e.ang2 or e.ang2>e.pang+0.014):
        #hist_lsPt.Fill(e.spt)
        #hist_lsrap.Fill(e.srap)
        #hist_lsprap.Fill(e.sprap)
        hist_lprappho.Fill(e.prap_pho)
        hist_lphoe.Fill(phe)
        hist_lphopt.Fill(e.phopt)
    """
    

#hist_nopho.SetTitleOffset(1.1,"y")
#fit(hist_nopho,"",kBlack,"Number of photons","Photon number")

leg=TLegend(0.6,0.65,0.88,0.85);
hist_prap.SetTitleOffset(1.3,"y")
fit(hist_prap,"",kBlack,"Transverse Momentum","Pseudorapidity")
fit(hist_praps,"same",kRed,"Transverse Momentum","Momentum (MeV)")
leg.AddEntry(hist_prap,"Data","l");
leg.AddEntry(hist_praps,"Simulated","l");
leg.SetBorderSize(0)
leg.Draw()
"""
hist_rap.SetTitleOffset(1.5,"y")
fit(hist_rap,"",kBlack,"Rapidity","Rapidity")

hist_prap.SetTitleOffset(1.5,"y")
fit(hist_prap,"",kBlack,"Pseudorapidity","Pseudorapidity")

hist_sPt.SetTitleOffset(1.3,"y")
fit(hist_sPt,"",kBlack,"Transverse Momentum of system","Momentum (MeV)")

#fit(hist_lsPt,"same",kRed,"Transverse Momentum of system","Momentum (MeV)")
hist_srap.SetTitleOffset(1.3,"y")
fit(hist_srap,"",kBlack,"Rapidity of system","Rapidity")

#fit(hist_lsrap,"same",kRed,"Rapidity of system","Rapidity")
hist_sprap.SetTitleOffset(1.3,"y")
fit(hist_sprap,"",kBlack,"Psudorapidity of system","Psudorapidity")

#fit(hist_lsprap,"same",kRed,"Psudorapidity of system","Psudorapidity")



leg=TLegend(0.6,0.65,0.88,0.85);
leg.AddEntry(hist_prappho,"Unlimited","l");
leg.AddEntry(hist_lprappho,"Limited","l");
leg.SetBorderSize(0)
hist_prappho.SetTitleOffset(1.4,"y")
hist_phoe.SetTitleOffset(1.2,"y")
hist_phopt.SetTitleOffset(1.2,"y")

fit(hist_prappho,"",kBlack,"Photon Psudorapidity","Psudorapidity")
fit(hist_lprappho,"same",kRed,"Photon Psudorapidity","Psudorapidity")
#fit(hist_phoe,"",kBlack,"Photon Energy","Energy (MeV)")
#fit(hist_lphoe,"same",kRed,"Photon Energy","Energy (MeV)")
#fit(hist_phopt,"",kBlack,"Photon Tranverse momentum","Tranverse momentum (MeV)")
#fit(hist_lphopt,"same",kRed,"Photon Tranverse momentum","Tranverse momentum (MeV)")
#leg.Draw()
"""

#c.Print("/Users/Andrew/Google Drive/Masters project/Graphs/pt.pdf")



t1 = time.time()
total = t1-t0
print "Time to complete" ,total
