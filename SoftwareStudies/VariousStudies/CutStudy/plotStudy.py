import ROOT as R
from Style import AtlasStyle
import math
from array import array
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits(  )
R.gStyle.SetPalette(1)

def HisttoGraph(hist,tot,cuts):
    xdata, ydata = array( 'd' ), array( 'd' )
    for i in range(hist.GetXaxis().GetNbins()):
        for p in range(len(cuts)):
            if (cuts[p] == hist.GetBinLowEdge(i)):
                print "Bin Centre", hist.GetBinLowEdge(i)
                print "Eff ",hist.GetBinContent(i-1)/tot
                ydata.append(hist.GetBinContent(i-1)/tot)
    for i in range(len(cuts)):
        xdata.append(cuts[i])
    return R.TGraph(len(xdata),xdata,ydata)


def ArrayFromGraph(axis,graph):
    datax , datay = array( 'd' ) , array( 'd' )
    for i in range(graph.GetN()):
        graph_x = R.Double(0.0)
        graph_y = R.Double(0.0)
        graph.GetPoint(i,graph_x,graph_y)
        #print graph_y
        #print graph_x
        if(graph_y <= 1):
            datax.append(graph_x)
            datay.append(graph_y)
    if(axis == "x"):
        return datax
    elif(axis == "y"):
        return datay  
    else:
        print "Fail"
        return -1  


def Plot2Save(hist1,hist2,legName,xaxis,yaxis,outname):
    c = R.TCanvas()
    multi=R.TMultiGraph();
    leg = R.TLegend(0.7,0.7,0.85,0.85)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)  
    hist1.SetTitle("")
    hist2.SetTitle("")
    hist1.SetMarkerColor(R.kRed)
    hist2.SetMarkerColor(R.kBlack)
    leg.AddEntry(hist1, legName[0], "P")
    leg.AddEntry(hist2, legName[1], "P")
    multi.Add(hist1)
    multi.Add(hist2)
    multi.Draw("A*")
    multi.GetXaxis().SetTitle(xaxis)
    multi.GetYaxis().SetTitle(yaxis)
    leg.Draw()
    #hist1.Draw("A*")
    #hist2.Draw("A*,same")
    c.Print(outname)

def PlotFromArray(xaxis,y,yall):
    xdata, ydata = array( 'd' ), array( 'd' )
    for i in range(len(xaxis)):
        xdata.append(xaxis[i])
        #print y[i]
        ydata.append(y[i]/yall)
    return R.TGraph(len(xdata),xdata,ydata)

def ROC(xgraph,ygraph,outname,outname2,xaxis,cut,axisLim):
    xdata, ydata, cut1 = array( 'd' ), array( 'd' ), array( 'd' )
    print xgraph.GetN()
    print ygraph.GetN()
    for i in range(xgraph.GetN()):
        xgraph_x = R.Double(0.0)
        xgraph_y = R.Double(0.0)
        ygraph_x = R.Double(0.0)
        ygraph_y = R.Double(0.0)
        xgraph.GetPoint(i,xgraph_x,xgraph_y)
        ygraph.GetPoint(i,ygraph_x,ygraph_y)
        if(xgraph_y < 1):
            #print "Cut ",cut[i]
            #print "x ",1-xgraph_y
            #print "y ",ygraph_y
            #print ""
            cut1.append(cut[i])
            xdata.append(1-xgraph_y)
            ydata.append(ygraph_y)
    c = R.TCanvas()
    gr = R.TGraph(len(xdata),xdata,ydata)
    gr.GetXaxis().SetTitle("Background rejection")
    gr.GetYaxis().SetTitle("Signal Effiency")
    gr.SetTitle("")
    gr.Draw("")
    if(axisLim[0]>axisLim[1]):
        gr.GetXaxis().SetRangeUser(axisLim[0],axisLim[1])
    if(axisLim[2]<axisLim[3]):
        print "Hi"
        gr.GetYaxis().SetRangeUser(axisLim[2],axisLim[3])
    gr.Draw("A*")
    c.Print(outname)
    gr1 = R.TGraph(xgraph.GetN(),cut1,ydata)
    gr2 = R.TGraph(xgraph.GetN(),cut1,xdata)
    Plot2Save(gr2,gr1,["IC","Sig"],xaxis,"Effiency",outname2)


def significance(sW,bW,bTot):
    sigTot = 4.214e+08
    bTot = 1.124e13
    Ntarget = 1e15
    ic_BR = 3.4e-5
    sig_BR = 1e-15
    s = Ntarget * sig_BR * sW/float(sigTot);
    b = Ntarget * ic_BR * 4e-2 * 0.9 * bW/float(bTot)
    x1=s+b
    x2=0
    if b <= 0:
        x2=0
    else:
        x2=R.TMath.Log(1+(s/float(b)))
    return R.TMath.Sqrt(2*(x1*x2-s))

def signifancePlot(back,sig,xax,outname,xtitle,btot):
    c=R.TCanvas()
    xaxis, yaxis = array( 'd' ), array( 'd' )
    for i in range(len(back)):
        print xax[i]
        print back[i]
        print sig[i]
        if sig[i]>0 and back[i]>0:
            xaxis.append(xax[i])
            print xax[i]
            print back[i]
            print sig[i]
            yaxis.append(significance(sig[i],back[i],btot))
            print significance(sig[i],back[i],btot)
    gr = R.TGraph(len(xaxis),xaxis,yaxis)
    gr.GetXaxis().SetTitle(xtitle)
    gr.GetYaxis().SetTitle("Significance")
    gr.SetTitle("")
    gr.Draw("A*")
    c.Print(outname)



fSignal = R.TFile("../../RootFiles/signalNew.root","read")
fIC = R.TFile("../../RootFiles/IC.root","read")
fICmic = R.TFile("/hepstore/agroves/MyStudies/SoftwareStudies/CombinationBackground/PhoCon/RadAll.root","read")
ICTot = 1.124e7
ICmicTot = 5.7781e+09


chiNoCut=fSignal.Get("Graph;1")
DCCut=fSignal.Get("Graph;8")
PDCCut=fSignal.Get("Graph;12")


chiNoCut_ICmic=fICmic.Get("Graph;1")
DCCut_ICmic=fICmic.Get("Graph;8")

PDCCut_IC=fIC.Get("Graph;12")

chicut=[60,55,50,45,40,35,30,28,26,24,22,20,15,10,5]
pcut=[16,14,12,10,9,8,7,6,5.5,5,4,3,2]
dcut=[10,9,8,7,6,5,4,3,2.5,2,1.7,1.5,1,0.5,0]
masscut=[95,97,99,101,103,104,105,106,107,109,111,113,115]
chicut2=[40,35,30,28,26,24,22,20,15,10,5]
dielecutLow=[0,1,2,3,3.5,4,4.5,5,5.5,6,6.5,7]
dielecutUp=[10,12,14,15,16,17,18,19,20,21,22,23]

fNewSignal = R.TFile("/hepstore/agroves/backup/SoftwareStudies/TDRSensitity/Signal/RootFiles/signal.root","read")
DielecLow = fNewSignal.Get("Graph;1")
DielecUp = fNewSignal.Get("Graph;2")
fNewIC = R.TFile("/hepstore/agroves/backup/SoftwareStudies/TDRSensitity/IC/RootFiles/IC.root","read")
DielecLowIC = fNewIC.Get("Graph;1")
DielecUpIC = fNewIC.Get("Graph;2")

Sig_chiallF=1.76514e+08
Sig_chiall=[1.02056e+08,1.01878e+08,1.01676e+08,1.01435e+08,1.01141e+08,1.00754e+08,1.00211e+08,9.99205e+07,9.95696e+07,9.9134e+07,9.85822e+07,9.78665e+07,9.47644e+07,8.69651e+07,6.32085e+07]
Sig_pChiDF=1.76514e+08
Sig_pChiD=[9.71917e+07,9.70176e+07,9.66995e+07,9.60833e+07,9.55686e+07,9.48182e+07,9.3697e+07,9.19392e+07,9.06677e+07,8.89907e+07,8.36403e+07,7.30696e+07,5.09525e+07]
Sig_dChiF=1.00211e+08
Sig_dChi=[9.96396e+07,9.94753e+07,9.92823e+07,9.90599e+07,9.88051e+07,9.85122e+07,9.81693e+07,9.77248e+07,9.73889e+07,9.68466e+07,9.63033e+07,9.57597e+07,9.28105e+07,8.03397e+07,0]

Sig_massF=9.48182e+07
Sig_massCuts=[9.47097e+07,9.44521e+07,9.3406e+07,9.05499e+07,8.28957e+07,7.41566e+07,5.2444e+07,1.97853e+07,9.70759e+06,3.25091e+06,1.00475e+06,244486,74883]
Sig_massCutsBig=[Sig_massF-Sig_massCuts[0],Sig_massF-Sig_massCuts[1],Sig_massF-Sig_massCuts[2],Sig_massF-Sig_massCuts[3],Sig_massF-Sig_massCuts[4],Sig_massF-Sig_massCuts[5],Sig_massF-Sig_massCuts[6],Sig_massF-Sig_massCuts[7],Sig_massF-Sig_massCuts[8],Sig_massF-Sig_massCuts[9],Sig_massF-Sig_massCuts[10],Sig_massF-Sig_massCuts[11],Sig_massF-Sig_massCuts[12]]

IC_pChiDF=2.98839e+12
IC_pChiD=[1.43344e+10,8.79313e+09,4.96296e+09,2.61395e+09,1.82886e+09,1.19929e+09,7.62672e+08,4.52983e+08,3.38854e+08,2.47451e+08,1.23066e+08,5.02124e+07,1.45885e+07]
IC_massF2=1.19929e+09
IC_massF=1.0699e+07
IC_massCuts=[1.0699e+07,4.10021e+06,1.19201e+06,299987,80418.6,40771.9,23169.5,10470.8,5557.17,1650.25,394.251,52.4246,16.5081]
IC_massCutsBig=[IC_massF-IC_massCuts[0],IC_massF-IC_massCuts[1],IC_massF-IC_massCuts[2],IC_massF-IC_massCuts[3],IC_massF-IC_massCuts[4],IC_massF-IC_massCuts[5],IC_massF-IC_massCuts[6],IC_massF-IC_massCuts[7],IC_massF-IC_massCuts[8],IC_massF-IC_massCuts[9],IC_massF-IC_massCuts[10],IC_massF-IC_massCuts[11],IC_massF-IC_massCuts[12]]

ROC(DielecUpIC,DielecUp,"figures/DieUp.png","DieUp.png","Di-electron Mass [MeV/c^{2}]",dielecutUp,[0,0,0,0])
signifancePlot(ArrayFromGraph("y",DielecUpIC),ArrayFromGraph("y",DielecUp),dielecutUp,"DieUpZ.png","Di-electron Mass [MeV/c^{2}]",ICTot)
ROC(DielecLowIC,DielecLow,"figures/DieLow.png","DieLow.png","Di-electron Mass [MeV/c^{2}]",dielecutLow,[0,0,0,0])
signifancePlot(ArrayFromGraph("y",DielecLowIC),ArrayFromGraph("y",DielecLow),dielecutLow,"DieLowZ.png","Di-electron Mass [MeV/c^{2}]",ICTot)




#ROC(PDCCut_IC,PDCCut,"figures/p.png","test.png","Momentum [MeV/c]",pcut,[0,0,0,0])
#signifancePlot(ArrayFromGraph("y",PDCCut_IC),Sig_pChiD,pcut,"pZ.png","Momentum [MeV/c]",ICTot)

#ROC(PlotFromArray(masscut,IC_massCuts,IC_massF),PlotFromArray(masscut,Sig_massCuts,Sig_massF),"figures/masss.png","test.png","Mass [MeV/c^{2}]",masscut,[0,0,0,0])
#ROC(PlotFromArray(masscut,IC_massCutsBig,IC_massF2),PlotFromArray(masscut,Sig_massCutsBig,Sig_massF),"figures/masssBig.png","massBig.png","Mass [MeV/c^{2}]",masscut,[0,0,0,0])
#signifancePlot(IC_massCuts,Sig_massCuts,masscut,"massZ.png","Mass [MeV/c^{2}]",ICTot)
#signifancePlot(IC_massCutsBig,Sig_massCutsBig,masscut,"massZBig.png","Mass [MeV/c^{2}]",ICTot)


#ROC(chiNoCut_ICmic,PlotFromArray(chicut,Sig_chiall,Sig_chiallF),"figures/chiROC.png","figures/chi.png","#chi^{2}",chicut,[0,0,0,0])
#ROC(DCCut_ICmic,DCCut,"figures/dROC.png","figures/d.png","Target Distance [mm]",dcut,[0,0,0.7,1])
#signifancePlot(ArrayFromGraph("y",chiNoCut_ICmic),Sig_chiall,chicut,"chiZ.png","#chi^{2}",ICmicTot)
#signifancePlot(ArrayFromGraph("y",DCCut_ICmic),Sig_dChi,dcut,"dZ.png","Target Distance [mm]",ICmicTot)


