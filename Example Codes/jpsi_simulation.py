from ROOT import *
import math
import sim_cal


muon1=TLorentzVector()
muon2=TLorentzVector()
trmuon1=TLorentzVector()
trmuon2=TLorentzVector()
photon=TLorentzVector()
muont=TLorentzVector()
trmuont=TLorentzVector()
sys=TLorentzVector()
trsys=TLorentzVector()
f=TFile('jpsi_100k_spincor.root')
g=f.Get('T;1')
c=TCanvas("Number of Photons","Number of Photons",700,500); 
#c.Divide(2,1)
gStyle.SetOptStat("0")
#gStyle.SetOptStat("u")

def jpsi(x,par):
    return par[0]*TMath.Gaus(x[0], par[1], par[2])

#----Setting up histograms---------------------------------------------
"""
hist_trpt2=TH1F("pt2 lim","pt2 lim",10,0,2)
hist_pt2=TH1F("pt2 lim","pt2 lim",10,0,2)
hist_nopho=TH1F("number of photons","number of photons",5,-0.5,4.5)
hist_nlong=TH1F("number of long tracks","number of long tracks",5,-0.5,4.5)
#hist_nspd=TH1F("npsd","nspd",5,-0.5,4.5)
#hist_pt2=TH1F("pt2 lim","pt2 lim",10,0,2)

hist_Pt=TH1F("Transverse momentum","Transverse momentum",100,-0.5,2999.5)
hist_tpt=TH1F("True Transverse momentum"," TrueTransverse momentum",100,-0.5,2999.5)

#hist_rapPT=TH1F("Transverse momentum rap","Transverse momentum rap",100,-0.5,2999.5)
hist_Pt0=TH1F("Transverse momentum","Transverse momentum1",100,-0.5,2999.5)
hist_Pt1=TH1F("Transverse momentum","Transverse momentum2",100,-0.5,2999.5)
hist_Pt2=TH1F("Transverse momentum","Transverse momentum3",100,-0.5,2999.5)
hist_P0=TH1F("Transverse momentum","Transverse momentum1",100,-0.5,2999.5)
hist_P1=TH1F("Transverse momentum","Transverse momentum2",100,-0.5,2999.5)
hist_P2=TH1F("Transverse momentum","Transverse momentum3",100,-0.5,2999.5)
"""
hist_mass=TH1F("Mass","Mass",300,0,4000)
hist_trmass=TH1F("Truth Mass","Truth Mass",300,0,4000)
hist_trmass2=TH1F("Truth Mass with 2 long","Truth Mass with 2 long",100,2900,3300)
hist_mass2=TH1F("Mass with 2 long","Mass with 2 long",100,2900,3300)
"""
hist_trlmass2=TH1F("Truth Mass with 2 long limited","Truth Mass with 2 long limited",300,1900,3300)
hist_lmass2=TH1F("Mass with 2 long limited","Mass with 2 long limited",100,2900,3300)


hist_rap=TH1F("Rapidity","Rapidity",100,-2,10)
hist_trap=TH1F("Truth Rapidity","Truth Rapidity",100,-2,10)
hist_prap=TH1F("Psudorapidity1","Psudorapidity1",100,0,10)
hist_trprap=TH1F("Psudorapidity1","Psudorapidity1",100,0,10)
hist_prap0=TH1F("Psudorapidity0","Psudorapidity0",100,0,6)
hist_prap1=TH1F("Psudorapidity1","Psudorapidity1",100,0,6)
hist_prap2=TH1F("Psudorapidity2","Psudorapidity2",100,0,10)
hist_rap0=TH1F("rapidity0","rapidity0",100,0,10)
hist_rap1=TH1F("rapidity1","rapidity1",100,0,10)
hist_rap2=TH1F("rapidity2","rapidity2",100,0,10)
#hist_0rap=TH1F("rapidity0l","rapidity0l",100,0,10)

hist_nlong=TH1F("number of long tracks","number of long tracks",3,0.5,3.5)
hist_lnlong=TH1F("number of long tracks","number of long tracks",3,0.5,3.5)
hist_prappho=TH1F("Psudorapidity of photon","Psudorapidity of photon",100,0,10)
hist_phoe=TH1F("Photon Energy","Photon Energy",200,0,2000)
hist_phopt=TH1F("Photon transverse momentum","Photon transverse momentum",200,0,500)
hist_lprappho=TH1F("Psudorapidity of photon","Psudorapidity of photon",100,0,10)
hist_lphoe=TH1F("Photon Energy","Photon Energy",200,0,2000)
hist_lphopt=TH1F("Photon transverse momentum","Photon transverse momentum",200,0,500)

#hist_ang=TH1F("Phi","Phi of photons",100,-0.5,0.5)
gr=TGraph()
gr1=TGraph()
gr2=TGraph()
gr3=TGraph()
"""
def fit(hist,f,colour,title,xaxis):      
    hist.Draw(f)
    hist.SetLineColor(colour)
    hist.SetTitle(title)
    hist.SetYTitle("No of Events")
    hist.SetXTitle(xaxis)


#-----Making calculatins for momentum and energy--------------------

for i, e in enumerate(g):
    if (i%10000==0): print "Entry ",i
    #if i>400: break
    """
    if e.nphotons==1:
        phe = math.sqrt(e.phx[0]**2+e.phy[0]**2+e.phz[0]**2);
        photon.SetPxPyPzE(e.phx[0],e.phy[0],e.phz[0],phe)
        tem1 = math.sqrt(e.trupx[0]**2+e.trupy[0]**2+e.trupz[0]**2+105.**2)
        tem2 = math.sqrt(e.trupx[1]**2+e.trupy[1]**2+e.trupz[1]**2+105.**2);
        trmuon1.SetPxPyPzE(e.trupx[0],e.trupy[0],e.trupz[0],tem1)
        trmuon2.SetPxPyPzE(e.trupx[1],e.trupy[1],e.trupz[1],tem2)
        trmuont=trmuon1+trmuon2+photon
    else:
    """
    tem1 = math.sqrt(e.trupx[0]**2+e.trupy[0]**2+e.trupz[0]**2+105.**2)
    tem2 = math.sqrt(e.trupx[1]**2+e.trupy[1]**2+e.trupz[1]**2+105.**2);
    trmuon1.SetPxPyPzE(e.trupx[0],e.trupy[0],e.trupz[0],tem1)
    trmuon2.SetPxPyPzE(e.trupx[1],e.trupy[1],e.trupz[1],tem2)
    trmuont=trmuon1+trmuon2
    
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
    """
    if e.nphotons==1:
        phe = math.sqrt(e.phx[0]**2+e.phy[0]**2+e.phz[0]**2);
        photon.SetPxPyPzE(e.phx[0],e.phy[0],e.phz[0],phe)
        #sys=muont+photon
        #trsys=trmuont+photon
    #else:
        #sys=muont
        #trsys=trmuont
    
    if e.nphotons==1:
        #byang1,byang2,bxang1,bxang2=sim_cal.angle(e)
        pang=e.phy[0]/e.phz[0]
    if e.nout==1 or e.nout==2: ang1=e.py[0]/e.pz[0]
    if e.nout==2: ang2=e.py[1]/e.pz[1]
    prap_pho=photon.PseudoRapidity()
    phopt=photon.Pt()

    
    
    pt=muont.Pt()
    rap=muont.Rapidity()
    trrap=trmuont.Rapidity()
    prap=muont.PseudoRapidity()
    trprap=trmuont.PseudoRapidity()
    mass=muont.M()
    trmass=trsys.M()
    if e.nlong==2:
        trmass_2=trmuont.M()
        mass_2=muont.M()
        prap_2=muont.PseudoRapidity()
        rap_2=trmuont.Rapidity()
    if e.nlong==1:
        prap_1=muont.PseudoRapidity()
        rap_1=trmuont.Rapidity()
    if e.nlong==0:
        prap_0=muont.PseudoRapidity()
        rap_1=trmuont.Rapidity()
    trpt=trmuont.Pt()

    trrap_muon=trmuont.Rapidity()
    
    

    leg_pt2=TLegend(0.65,0.63,0.89,0.87)    
    trpt2=(trmuont.Pt()**2)*10**-6
    hist_trpt2.Fill(trpt2)
    pt2=(muont.Pt()**2)*10**-6
    hist_pt2.Fill(pt2)
    leg_pt2.AddEntry(hist_pt2,"Reconstructed","l") 
    leg_pt2.AddEntry(hist_trpt2,"Truth","l")
    leg_pt2.SetBorderSize(0)
    #if e.nphotons==1 and e.nout==2: gr.SetPoint(i,bxang1,bxang2)
    #if e.nphotons==1 and e.nout==2 and (pang-0.014>ang1 or ang1>pang+0.014) : gr.SetPoint(i,ang1,pang)
    #if e.nphotons==1 and e.nout==2: hist_ang.Fill(bxang2)
    
    #hist_nspd.Fill(e.nspd)
    #hist_nopho.Fill(e.nphotons)
    
    #hist_nlong.Fill(e.nlong)
    
    
    leg_pt=TLegend(0.65,0.63,0.89,0.87)
    hist_Pt.Fill(pt)
    hist_tpt.Fill(trpt)
    #if rap>2 : hist_rapPT.Fill(pt)
    leg_pt.AddEntry(hist_Pt,"Reconstructed","l") 
    leg_pt.AddEntry(hist_tpt,"Truth","l")
    #leg_pt.AddEntry(hist_rapPT,"Rapidity limit","l")
    leg_pt.SetBorderSize(0)
    
    leg_ptl=TLegend(0.67,0.67,0.87,0.87)
    if e.nlong==2 : hist_Pt2.Fill(trpt)
    if e.nlong==1:  hist_Pt1.Fill(trpt)
    if e.nlong==0: hist_Pt0.Fill(trpt)
    leg_ptl.AddEntry(hist_Pt0,"0 long tracks","l") 
    leg_ptl.AddEntry(hist_Pt1,"1 long tracks","l")
    leg_ptl.AddEntry(hist_Pt2,"2 long tracks","l")
    leg_ptl.SetBorderSize(0)
    
    leg_pl=TLegend(0.67,0.67,0.87,0.87)
    if e.nlong==2 : hist_P2.Fill(pt)
    if e.nlong==1:  hist_P1.Fill(pt)
    if e.nlong==0: hist_P0.Fill(pt)
    leg_pl.AddEntry(hist_P0,"0 long tracks","l") 
    leg_pl.AddEntry(hist_P1,"1 long tracks","l")
    leg_pl.AddEntry(hist_P2,"2 long tracks","l")
    leg_pl.SetBorderSize(0)
    
    """
    leg_mass2=TLegend(0.67,0.67,0.87,0.87)
    if e.nout==2:
        hist_mass2.Fill(muont.M())
    hist_trmass2.Fill(trmuont.M())
    leg_mass2.AddEntry(hist_mass2,"Reconstructed","l") 
    leg_mass2.AddEntry(hist_trmass2,"Truth","l")
    leg_mass2.SetBorderSize(0)
    """
    
    leg_mass2=TLegend(0.67,0.67,0.87,0.87)
    if e.nlong==2: hist_mass2.Fill(sys.M())
    if e.nlong==2 and e.nphotons==1 and (pang-0.014<ang1<pang+0.014) and (pang-0.014<ang2<pang+0.014): hist_lmass2.Fill(sys.M())
    leg_mass2.AddEntry(hist_mass2,"Unlimited","l") 
    leg_mass2.AddEntry(hist_lmass2,"Limited","l")
    leg_mass2.SetBorderSize(0)

    leg_mass3=TLegend(0.67,0.67,0.87,0.87)
    if e.nlong==2: hist_trmass2.Fill(trsys.M())
    if e.nlong==2 and e.nphotons==1 and (pang-0.014<ang1<pang+0.014) and (pang-0.014<ang2<pang+0.014): hist_trlmass2.Fill(trsys.M())
    leg_mass3.AddEntry(hist_trmass2,"Unlimited","l") 
    leg_mass3.AddEntry(hist_trlmass2,"Limited","l")
    leg_mass3.SetBorderSize(0)
    
    
    
    leg_rap=TLegend(0.67,0.67,0.87,0.87) 
    hist_rap.Fill(rap)
    hist_trap.Fill(trrap)
    leg_rap.AddEntry(hist_rap,"Rapidity","l")
    leg_rap.AddEntry(hist_trap,"True Rapidity","l")
    leg_rap.SetBorderSize(0)
    
    leg_rapl=TLegend(0.67,0.67,0.87,0.87) 
    if e.nlong==2: hist_rap2.Fill(rap)
    if e.nlong==0: hist_rap0.Fill(rap)
    if e.nlong==1 :hist_rap1.Fill(rap)
    leg_rapl.AddEntry(hist_rap0,"0 tracks","l") 
    leg_rapl.AddEntry(hist_rap1,"1 tracks","l")
    leg_rapl.AddEntry(hist_rap2,"2 tracks","l")
    leg_rapl.SetBorderSize(0)
    
    leg_prap=TLegend(0.69,0.69,0.89,0.89)
    hist_prap.Fill(prap)
    hist_trprap.Fill(trprap)
    leg_prap.AddEntry(hist_prap,"Reconstructed","l") 
    leg_prap.AddEntry(hist_trprap,"Truth","l")
    leg_prap.SetBorderSize(0)
    
    #leg_prapl=TLegend(0.67,0.67,0.87,0.87) 
    if e.nlong==2:hist_prap0.Fill(muon1.PseudoRapidity())
    if e.nlong==2:hist_prap1.Fill(muon2.PseudoRapidity())
    #if e.nlong==2: hist_prap2.Fill(prap_2)
    #leg_prapl.AddEntry(hist_prap0,"0 tracks","l") 
    #leg_prapl.AddEntry(hist_prap1,"1 tracks","l")
    #leg_prapl.AddEntry(hist_prap2,"2 tracks","l")
    #leg_prapl.SetBorderSize(0)
    
   
    
    if (2<rap<4.5 and e.nlong==0):
        hist_0rap.Fill(rap)
    
    if e.nphotons==1 and e.nout==2: gr.SetPoint(i,ang1,pang)
    if e.nphotons==1 and e.nout==2 and (pang-0.025>ang1 or ang1>pang+0.025) : gr1.SetPoint(i,ang1,pang)
    if e.nphotons==1 and e.nout==2: gr2.SetPoint(i,ang2,pang)
    if e.nphotons==1 and e.nout==2 and (pang-0.025>ang2 or ang2>pang+0.025) : gr3.SetPoint(i,ang2,pang)
    
    if e.nphotons==1 and e.nout==2 and (pang-0.02>ang1 or ang1>pang+0.02) and (pang-0.02>ang2 or ang2>pang+0.02):
        hist_lprappho.Fill(prap_pho)
        hist_lphoe.Fill(phe)
        hist_lphopt.Fill(phopt)
        hist_lnlong.Fill(e.nout)
    
    if e.nphotons==1 and e.nout==2:
        hist_prappho.Fill(prap_pho)
        hist_phoe.Fill(phe)
        hist_phopt.Fill(phopt)
        hist_nlong.Fill(e.nout)
    """


#-----Exiting for loop------------------------------------------------------------
"""
hist_trpt2.SetTitleOffset(1.4,"y")
fit(hist_trpt2,"",kRed,"Tranverse momentum squared cut","Pt (GeV^{2})")
fit(hist_pt2,"same",kBlack,"Tranverse momentum squared cut","Pt (GeV^{2})")
leg_pt2.Draw()
#fit(hist_nopho,"",kBlack,"Number of photons","Photon number")

gr.SetMarkerStyle(7)  
gr.SetTitle("phx[0]/phz[0]-px[0]/pz[0]-780*charge[0]/pz[0] vs phx[0]/phz[0]-px[1]/pz[1]-780*charge[1]/pz[1]")
gr.GetXaxis().SetTitle("phx[0]/phz[0]-px[0]/pz[0]-780*charge[0]/pz[0]")
gr.GetYaxis().SetTitle("phx[0]/phz[0]-px[1]/pz[1]-780*charge[1]/pz[1]")
gr.Draw("AP") 

#fit(hist_ang,"",kBlack,"phx[0]/phz[0]-px[1]/pz[1]-780*charge[1]/pz[1]","phx[0]/phz[0]-px[1]/pz[1]-780*charge[1]/pz[1]")



c.cd(1)
hist_nopho.SetTitleOffset(1.6,"y")
fit(hist_nopho,"",kBlack,"Number of photons","Photon number")
c.cd(2)
hist_nlong.SetTitleOffset(1.6,"y")
fit(hist_nlong,"",kBlack,"Number of long tracks","Long track number")


hist_tpt.SetTitleOffset(1.2,"y")
fit(hist_tpt,"",kRed,"Transverse Momentum","Momentum (MeV)")
fit(hist_Pt,"same",kBlack,"Transverse Momentum","Momentum (MeV)")
#fit(hist_rapPT,"same",kGreen,"Transverse Momentum rap","Momentum (MeV)")
leg_pt.Draw()

c.cd(1)
hist_Pt1.SetTitleOffset(1.4,"y")
fit(hist_Pt1,"",kRed,"True Transverse Momentum","Momentum (MeV)")
fit(hist_Pt2,"same",kBlack,"True Transverse Momentum","Momentum (MeV)")
fit(hist_Pt0,"same",kGreen,"True Transverse Momentum","Momentum (MeV)")
leg_ptl.Draw()
c.cd(2)

hist_P2.SetTitleOffset(1.4,"y")
fit(hist_P2,"",kBlack,"Transverse Momentum","Momentum (MeV)")
fit(hist_P1,"same",kRed,"Transverse Momentum","Momentum (MeV)")
fit(hist_P0,"same",kGreen,"Transverse Momentum","Momentum (MeV)")
leg_pl.Draw()

c.cd(1)

hist_mass.SetTitleOffset(1.6,"y")
fit(hist_mass,"",kBlack,"Invariant Mass","Mass (MeV)")
fit(hist_trmass,"same",kRed,"truth Invariant Mass","Mass (MeV)")
leg_mass.Draw()

c.cd(2)
"""
hist_trmass2.SetTitleOffset(1.4,"y")          
fit(hist_trmass2,"",kRed,"Invariant Mass of only 2 long tracks","Mass (MeV)")
fit(hist_mass2,"same",kBlack,"Invariant Mass of only 2 long tracks","Mass (MeV)") 
leg_mass2.Draw()

fitFcn =TF1("fitFcn",jpsi,3000,3800,3);
fitFcn.SetLineColor(kOrange)
fitFcn.SetParameter(0,1)
fitFcn.SetParameter(1,3096.9)
fitFcn.SetParameter(2,1)
hist_mass2.Fit("fitFcn");
#hist_trmass2.Fit("fitFcn")
print 2*math.sqrt(2*math.log(2))*fitFcn.GetParameter(2)
"""
c.cd(1)
fit(hist_mass2,"",kGreen,"Invariant Mass of only 2 long tracks","Mass (MeV/c2)") 
fit(hist_lmass2,"same",kBlack,"Invariant Mass of only 2 long tracks","Mass (MeV/c2)")
leg_mass2.Draw()
c.cd(2)       
fit(hist_trmass2,"",kBlack,"truth invariant Mass of only 2 long tracks","Mass (MeV/c2)")
fit(hist_trlmass2,"same",kRed,"truth Invariant Mass of only 2 long tracks","Mass (MeV/c2)")
leg_mass3.Draw()

c.cd(1)
hist_rap.SetTitleOffset(1.4,"y")
fit(hist_rap,"",kBlack,"Rapidity","Rapidity")
fit(hist_trap,"same",kRed,"Rapidity of Jpsi in truth level","Rapidity")
leg_rap.Draw()
c.cd(2)
hist_rap1.SetTitleOffset(1.4,"y")
fit(hist_rap1,"",kRed,"Rapidity of long tracks","Rapidity")
fit(hist_rap0,"same",kBlack,"Rapidity of long tracks","Rapidity")
fit(hist_rap2,"same",kGreen,"Rapidity of long tracks","Rapidity")
leg_rapl.Draw()

c.cd(1)
hist_prap.SetTitleOffset(1.4,"y")
fit(hist_prap,"",kBlack,"Psudorapidity of long tracks","Psudorapidity")
fit(hist_trprap,"same",kGreen,"Psudorapidity of long tracks","Psudorapidity")
leg_prap.Draw()
c.cd(2)

hist_prap1.SetTitleOffset(1.2,"y")
hist_prap0.SetTitleOffset(1.2,"y")
#fit(hist_prap0,"",kBlack,"Psudorapidity of long tracks","Psudorapidity")
fit(hist_prap1,"",kBlack,"Psudorapidity of long tracks","Psudorapidity")
#fit(hist_prap0,"same",kBlack,"Psudorapidity of long tracks","Psudorapidity")
#leg_prapl.Draw()

#fit(hist_0rap,"",kBlack,"Rapidity of 0 long tracks between 2-4.5","Rapidity")
#c.cd(1)
leg_prap=TLegend(0.69,0.69,0.89,0.89)
leg_prap.AddEntry(hist_prappho,"Unlimited","l")
leg_prap.AddEntry(hist_lprappho,"Limited","l")
leg_prap.SetBorderSize(0)

hist_prappho.SetTitleOffset(1.3,"y")
fit(hist_prappho,"",kBlack,"Photon Psudorapidity","Psudorapidity")
fit(hist_lprappho,"same",kRed,"Photon Psudorapidity","Psudorapidity")

#c.cd(2)
hist_phoe.SetTitleOffset(1.3,"y")
fit(hist_phoe,"",kBlack,"Photon Energy","Energy (MeV)")
fit(hist_lphoe,"same",kRed,"Photon Energy","Energy (MeV)")
hist_phopt.SetTitleOffset(1.3,"y")
fit(hist_phopt,"",kBlack,"Photon Tranverse momentum","Tranverse momentum (MeV/c)")
fit(hist_lphopt,"same",kRed,"Photon Tranverse momentum","Tranverse momentum (MeV/c)")
leg_prap.Draw()
"""
    
#c.Print("/Users/Andrew/Google Drive/Masters project/Graphs/simultaion/prap_muon2.pdf")

