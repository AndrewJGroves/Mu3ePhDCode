import ROOT as R
import sys
import numpy as np
from math import sqrt

def histo_printer(hist, pname, label):
    c = R.TCanvas()
    hist.SetTitle(label)
    hist.Scale( 1/hist.Integral(0,99999) )
    mean = hist.GetMean()
    sigma = hist.GetRMS()
    r = hist.Fit("gaus","S","",mean-1.5*sigma,mean+1.5*sigma)
    rmean =  r.Parameter(1)
    rsigma =  r.Parameter(2)
    rsigma_err =  r.ParError(2)
    hist.Draw()
    lat = R.TLatex()
    lat.DrawLatexNDC(0.15,0.7,"mean="+str(round(rmean,3)))
    lat.DrawLatexNDC(0.15,0.8,"sigma="+str(round(rsigma,3)))
    c.Print(pname)
    return [rmean, rsigma, rsigma_err]

def runJob(fname, tag, nbins=50,xmin=-10,xmax=10):
    R.TH1.SetDefaultSumw2()
    h_file = R.TFile(fname,"read")
    t = h_file.Get("t1")
    px_true = None
    px_reco = None
    py_true = None
    py_reco = None
    pz_true = None
    pz_reco = None
    for e in t:
        if tag == "short":
            px_true = np.array(e.px_true)
            px_reco = np.array(e.px_reco)
            py_true = np.array(e.py_true)
            py_reco = np.array(e.py_reco)
            pz_true = np.array(e.pz_true)
            pz_reco = np.array(e.pz_reco)
        elif tag == "long6":
            px_true = np.array(e.pxl_true)
            px_reco = np.array(e.pxl_reco)
            py_true = np.array(e.pyl_true)
            py_reco = np.array(e.pyl_reco)
            pz_true = np.array(e.pzl_true)
            pz_reco = np.array(e.pzl_reco)
            

    print 'tree read, now calculating mom'
    p_true = np.sqrt( px_true*px_true + py_true*py_true + pz_true*pz_true )
    p_reco = np.sqrt( px_reco*px_reco + py_reco*py_reco + pz_reco*pz_reco )

    print "mom calculated, entries:",len(px_true)
    ### try to do the resolution
    diff = p_true - p_reco
    diffx = px_true - px_reco
    diffy = py_true - py_reco
    diffz = pz_true - pz_reco

    # calculate resolution in ranges of pT bins
    ptb = [10,11,12,13,14,15,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,48,50,55]
    sigmas = []
    sigmaerr = []
    x_ptb = []
    x_err = []
    sigma_fit = []
    sigma_fit_err = []

    for i in range( len(ptb) -1 ):
        pmin = ptb[i]
        pmax = ptb[i+1]
        print "doing bin:",pmin,pmax
        #a1 = np.where( px_reco >= pmin)
        #a2 = np.where( px_reco < pmax)

        a1 = np.where( p_true >= pmin)
        a2 = np.where( p_true < pmax)

        a = np.intersect1d(a1[0],a2[0])
        std = np.std( diff[ a  ]  )
        err = sqrt( 2*std*std / (len(a) - 1))
        sigmas.append( std  )
        x_ptb.append( pmin + (pmax-pmin)*0.5  )
        x_err.append( (pmax-pmin)*0.5 )
        sigmaerr.append(err)
        h_diff  = R.TH1F("h1","h1",nbins,xmin,xmax)
        for j in a:
            #print diff[j]
            #if p_true[j]>pmax or p_true[j]<pmin:
                #print p_true[j]
            h_diff.Fill(diff[j])
        res = histo_printer(h_diff, "test_reso_"+tag+"_"+str(i)+".png","p(true)-p(reco) bin "+str(pmin)+"-"+str(pmax)+" for "+tag+" tracks")
        sigma_fit.append(res[1])
        sigma_fit_err.append(res[2])

    print sigmas
    print "overall", np.std( diff )
    #g = R.TGraphErrors(len(x_ptb), np.array(x_ptb), np.array(sigmas), np.array(x_err),np.array(sigmaerr))
    g = R.TGraphErrors(len(x_ptb), np.array(x_ptb), np.array(sigma_fit), np.array(x_err),np.array(sigma_fit_err))
    
    f_out = R.TFile("reso_"+tag+".root","recreate")
    g.Write()
    return 
    # AK resolution
    g_short = R.TGraph(5, np.array([12.,20.,30.,37.,45.,52.0]),np.array([0.5,1.0,1.5,2.0,2.5,2.9]))
    g_short.SetLineColor(2)
    g_short.SetLineWidth(2)

    c0 = R.TCanvas()
    g.SetTitle("Momentum resolution of "+tag+" tracks")
    g.SetMarkerStyle(20)
    g.GetYaxis().SetRangeUser(0.,3.)
    g.GetYaxis().SetTitle("#sigma [MeV]")
    g.GetXaxis().SetTitle("true track momentum [MeV]")
    g.Draw("APEL")
    g_short.Draw("L,same")
    leg = R.TLegend(0.8,0.2,0.95,0.4)
    leg.AddEntry(g,"v4.1","L")
    leg.AddEntry(g_short,"TDR line","L")
    c0.Print("test_reso_"+tag+".png")

    h_diff = R.TH1F("h1","h1",100,-5.,5.)
    for i in diffy:
        h_diff.Fill(i)
        
    histo_printer(h_diff, "test_h_resoy"+tag+".png", "p(true)-p(reco) all bins y")
    #return 

    text = raw_input()

runJob("signal.root","short", 50, -10., 10.)
runJob("signal.root","long6", 50, -2.5,  2.5)
#runJob("signal.root","long8", 50, -2.5,  2.5)

sys.exit()
