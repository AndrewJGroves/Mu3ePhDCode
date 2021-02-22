import ROOT as R


muonGen = 0
muonDecAfterWin = 0
muonDecBeforTar = 0
muonDecInTar = 0
muonDecAfterTar = 0

for i in range(5,7):
    run = format(i,'06d')
    f = R.TFile("/bundle/data/Mu3e/build_4.3/IC/mu3e_run_"+run+".root","read")
    tr = f.Get("stat/muonstat")
    muonsta = tr.GetString()
    p=str(muonsta)
    a1=p[33:40]
    a2=p[74:80]
    a3=p[114:119]
    a4=p[153:159]
    a5=p[193:198]
    a6=p[232:240]
    a7=p[274:282]
    a8=p[326:334]
    a9=p[368:376]
    b1=int(a1)
    b2=int(a2)
    b3=int(a3)
    b4=int(a4)
    b5=int(a5)
    b6=float(a6)
    b7=float(a7)
    b8=float(a8)
    b9=float(a9)

    muonGen += b1
    muonDecAfterWin += b2
    muonDecBeforTar += b3
    muonDecInTar += b4
    muonDecAfterTar += b5

print "Muon generated ", muonGen
print "Muons decayed after window ",  muonDecAfterWin
print "Muons decayed before target ",    muonDecBeforTar
print "Muons decayed in target ",muonDecInTar
print "Muons decayed after target ",   muonDecAfterTar
print "Target stopping fraction (window) ", float(muonDecInTar)/float(muonDecAfterWin)
#print "Target stopping fraction ",        
#print "Traget stopping fraction relative to total ",  
#print "Muons making it to target region ",

