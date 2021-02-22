import ROOT as R

R.gStyle.SetOptStat(0)

def plot(name,axis,title):
    f = R.TFile("plots.root","read")
    xres = f.Get(name)
    c = R.TCanvas()
    low = -2
    high = 2
    dist = high-low
    g = R.TF1("dg","gaus(0)+gaus(3)",low,high)
    sg = R.TF1("sg","gaus",low+dist/3,high-dist/3)
    mu0 = xres.GetMean()
    rms = xres.GetRMS()
    n0 = xres.GetEntries()
    
    sg.SetParameter(0, n0);
    sg.SetParameter(1, mu0);
    sg.SetParameter(2, rms*0.8);
    
    xres.Fit(sg, "","",low+dist/2.7,high-dist/2.7);
    
    g.SetParameter(0, sg.GetParameter(0));
    g.SetParameter(3, n0);
    g.FixParameter(1, sg.GetParameter(1));
    g.FixParameter(4, sg.GetParameter(1));
    g.FixParameter(2, sg.GetParameter(2));
    g.SetParLimits(2, 0.1*sg.GetParameter(2), rms/2);
    g.SetParameter(5, rms*1.5);
    g.SetParLimits(5, sg.GetParameter(2), rms*2);
    xres.Fit(g,"","",low, high);
    
    if(xres.Fit(g,"","",low, high)):
        g.SetParameter(0, sg.GetParameter(0));
        g.SetParameter(3, sg.GetParameter(0)*0.7);
        g.FixParameter(1, sg.GetParameter(1));
        g.FixParameter(4, sg.GetParameter(1));
        g.FixParameter(2, sg.GetParameter(2)*0.8);
        g.SetParameter(5, rms*1.2);
        g.SetParLimits(5, sg.GetParameter(2), rms*2);
        xres.Fit(g,"","",low, high);

    xres.Fit(g,"","",low, high);
    


    xres.GetYaxis().SetRangeUser((xres.GetBinContent(xres.GetMinimumBin()))*0.5,(xres.GetBinContent(xres.GetMaximumBin()))*4)
    R.gPad.SetLogy(1)
    xres.SetTitle("")
    xres.GetXaxis().SetTitle(axis)
    xres.Draw()
    
    rms = "RMS = (%2.4f \pm %2.4f)  mm " %(xres.GetRMS(),xres.GetRMSError())
    mean = "\mu = (%2.4f \pm %2.4f)  mm " %(xres.GetMean(),xres.GetMeanError())
    sig = "\sigma = (%2.4f \pm %2.4f) mm " %(g.GetParameter(2),g.GetParError(2))
    
    
    tex = R.TLatex(1,1,"XXX")
    tex.SetNDC()
    tex.SetTextAlign(11);
    tex.SetTextColor(1);
    tex.SetTextFont(42);
    tex.SetTextSize(0.05);
    tex.DrawLatex(0.12,0.84,rms)
    tex.DrawLatex(0.18,0.79,mean)
    tex.DrawLatex(0.18,0.74,sig)
    
    c.Modified()
    c.Update()
    c.Print(title)

plot("xres_3rec","x_{rec}-x_{true} [mm]","xres.png")
plot("yres_3rec","y_{rec}-y_{true} [mm]","yres.png")
plot("zres_3rec","z_{rec}-z_{true} [mm]","zres.png")
