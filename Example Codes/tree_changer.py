from ROOT import *
import math
from array import array

f=TFile('merge_d_calculated.root')
g=f.Get('T')


nEntries = g.GetEntries() 

#--- Throw away some branches
"""
g.SetBranchStatus("*",0)
g.SetBranchStatus("px",1)
g.SetBranchStatus("py",1)
g.SetBranchStatus("pz",1)
g.SetBranchStatus("phx",1)
g.SetBranchStatus("phy",1)
g.SetBranchStatus("phz",1)
g.SetBranchStatus("nphotons",1)
g.SetBranchStatus("charge",1)
g.SetBranchStatus("nspd",1)
g.SetBranchStatus("etprev2",1)
g.SetBranchStatus("etprev1",1)
g.SetBranchStatus("chih",1)
"""


outFile = "merge_d_calculated_1photon.root" 
newFile = TFile(outFile,"RECREATE")
T = g.CloneTree(0)
"""
photon=TLorentzVector()
muont=TLorentzVector()
sys=TLorentzVector()
mass=array('f', [ 0.0 ] )
smass=array('f', [ 0.0 ] )
pt=array('f', [ 0.0 ] )
rap=array('f', [ 0.0 ] )
prap=array('f', [ 0.0 ] )
spt=array('f', [ 0.0 ] )
srap=array('f', [ 0.0 ] )
sprap=array('f', [ 0.0 ] )
phopt=array('f', [ 0.0 ] )
prap_pho=array('f', [ 0.0 ] )
ang1=array('f', [ 0.0 ] )
ang2=array('f', [ 0.0 ] )
pang=array('f', [ 0.0 ] )

T.Branch( "mass", mass, "mass/F" )
T.Branch( "smass", smass, "smass/F" )
T.Branch( "pt", pt, "pt/F" )
T.Branch( "rap", rap, "rap/F" )
T.Branch( "prap", prap, "prap/F" )
T.Branch( "spt", spt, "spt/F" )
T.Branch( "srap", srap, "srap/F" )
T.Branch( "sprap", sprap, "sprap/F" )
T.Branch( "prap_pho", prap_pho, "prap_pho/F" )
T.Branch( "phopt", phopt, "phopt/F" )
"""
for i in range(nEntries): 
    g.GetEntry(i)
    #if i > 1000: break
    if i%10000==0:
        print "Processing event nr. %i of %i" % (i,nEntries)
    #--- Only write out certain events that pass some cut
    """
    if g.nout==1 or g.nout==2:
        muon1=TLorentzVector()
        em1 = math.sqrt(g.px[0]**2+g.py[0]**2+g.pz[0]**2+105.**2);
        muon1.SetPxPyPzE(g.px[0],g.py[0],g.pz[0],em1)
    if g.nout==2:
        muon2=TLorentzVector()
        em2 = math.sqrt(g.px[1]**2+g.py[1]**2+g.pz[1]**2+105.**2);
        muon2.SetPxPyPzE(g.px[1],g.py[1],g.pz[1],em2)
        muont=muon1+muon2
    else:
        muont=muon1
    if g.nphotons==1:
        phe = math.sqrt(g.phx[0]**2+g.phy[0]**2+g.phz[0]**2);
        photon.SetPxPyPzE(g.phx[0],g.phy[0],g.phz[0],phe)
        sys=muont+photon
    else:
        sys=muont
    
    mass[0]=muont.M()
    smass[0]=sys.M()
    mass[0]=muont.M()
    smass[0]=sys.M()
    pt[0]=muont.Pt()
    rap[0]=muont.Rapidity()
    prap[0]=muont.PseudoRapidity()
    prap_pho[0]=photon.PseudoRapidity()
    phopt[0]=photon.Pt()
    spt[0]=sys.Pt()
    srap[0]=sys.Rapidity()
    sprap[0]=sys.PseudoRapidity()
    prap_pho[0]=photon.PseudoRapidity()
    phopt[0]=photon.Pt()
    """
    if g.nphotons==1:
        T.Fill() 
 
# use GetCurrentFile just in case we went over the
# (customizable) maximum file size
T.GetCurrentFile().Write() 
T.GetCurrentFile().Close()
