import ROOT as R

### fit the function and also show a ratio plot
### to judge how good the fit is
def doPlot(hmass, **kwargs):
    #R.gROOT.SetStyle("ATLAS") # if you run ROOT 6.13 or higher
    R.gROOT.LoadMacro("/user/agroves/Software/MyStudies/Plots/AtlasStyle.C")
    R.SetAtlasStyle()
    ## since we cannot do an unbinned fit we will do a fit on the histogram
    xtitle = "m_{eee} [MeV]"
    x = R.RooRealVar("x",xtitle,90., 120.)

    hmass1 = R.RooDataHist("h_mass1","h_mass1", R.RooArgList(x, "x"), hmass)


    #### fitting the function 
    mean = R.RooRealVar("mean","mean", 105., 90., 115.)
    sigma= R.RooRealVar("sigma","sigma", 10., 0., 50.)
    alpha= R.RooRealVar("alpha","alpha", 1., 0., 30.)
    npar = R.RooRealVar("npar","npar", 1., 1., 5.)
    
    cb = R.RooCBShape("cb","cb", x, mean, sigma, alpha, npar)
    cb.fitTo(hmass1)


    ## do the plot here
    ######################
    c = R.TCanvas()
    
    showRatio = False
    isLogy = False
    if "log" in kwargs:
        if kwargs["log"] == 1:
            print 'log scale requested'
            isLogy = True


    c.cd()
    c.SetGridx(0)
    c.SetGridy(0)
    t1 = R.TPad("t1","t1", 0.0, 0., 1.0, 1.0);
    t1.SetRightMargin(0.05);
    t2 = None

    if showRatio:
        t1 = R.TPad("t1","t1", 0.0, 0.27, 1.0, 1.0)
        t1.SetBottomMargin(0.04)
        t2 = R.TPad("t2","t2", 0.0, 0.0, 1.0, 0.23)
        t2.SetBottomMargin(0.4)
        t2.SetTopMargin(0.04)
        t2.SetGridy(True)
        t1.SetRightMargin(0.05)
        t2.SetRightMargin(0.05)
        t2.Draw()
   
    t1.Draw()
    t1.cd()
    if isLogy:
        t1.SetLogy(True);
    
    frame = x.frame(R.RooFit.Title("reconstructed m_{eee}"))
    hmass1.plotOn(frame)    
    cb.plotOn(frame, R.RooFit.LineColor(2))
    frame.SetYTitle("Entries");
    frame.SetXTitle(xtitle);
    frame.Draw()

    # label
    tex = R.TLatex(0.2, 0.88, "#mu3e, work in progress")
    tex.SetNDC()
    tex.Draw()
    tex1 = R.TLatex(0.2,0.82, "Phase-I, XX #mu on target")
    tex1.SetNDC()
    tex1.Draw()
    
    if isLogy:
        frame.SetMinimum(0.1)
    else:
        frame.SetMinimum(0)

    ymax_ = frame.GetMaximum()
    if isLogy:
        frame.SetMaximum(ymax_*10.)
    else:
        frame.SetMaximum(ymax_*1.2)

    
    if showRatio:
        frame.GetYaxis().SetTitleSize(0.06)
        frame.GetYaxis().SetTitleOffset(1.22)
        
        frame.GetXaxis().SetTitle()
        frame.GetXaxis().SetLabelSize(0)

        t2.cd()
        hresid = frame.residHist()
        hpull = frame.pullHist()
        frame3 =x.frame(R.RooFit.Title("Pull/residual"))
        plot_pull = True 
        if plot_pull:
            frame3.addPlotable(hpull,"P")
        else:
            frame3.addPlotable(hresid, "P")

        frame3.GetYaxis().SetLabelSize(0.15);
        frame3.GetYaxis().SetNdivisions(3);
        frame3.GetYaxis().SetTickLength(0.02);
        frame3.GetYaxis().SetTitleSize(0.19);
        frame3.GetYaxis().SetTitleOffset(0.32);
        
        frame3.GetXaxis().SetTitleOffset(0.8);
        frame3.GetXaxis().SetLabelSize(0.16);
        frame3.GetXaxis().SetTitleSize(0.21);
        frame3.GetXaxis().SetTickLength(0.12);
     
     
        frame3.GetXaxis().SetNdivisions(5 + 100*2 + 10000*5);
        frame3.GetYaxis().SetNdivisions(3 + 100*5 + 10000*0);
        
        frame3.GetYaxis().SetTitle("#frac{Sim-Fit}{#sigma_{stat}}");
        #frame3.GetXaxis().SetTitle("#it{m}_{#ell#ell#gamma#gamma} [GeV]");
        frame3.GetXaxis().SetTitle(xtitle);

        frame3.Draw();
        ## set the y axis range here
        frame3.SetMinimum(-10) ;
        frame3.SetMaximum(+10) ;




    #
    t1.cd()
    frame.Draw("same")
    
    pname = "test_mass_reso.png"
    if "pname" in kwargs:
        pname = kwargs["pname"]
    c.Print(pname)
    



f = R.TFile("/user/agroves/Software/MyStudies/Plots/RootFiles/normal.root")

hmass = f.Get("h_decay")

#hmass.Rebin(2)
#hmass.Scale(1./hmass.Integral(0,99999))

print hmass.Integral()

doPlot(hmass, log=0, pname="test_mass_reso.png")
#doPlot(hmass, log=0, pname="test_mass_reso.png")
## test resolution of the signal
print 'mean', hmass.GetMean(), "sigma", hmass.GetStdDev()
