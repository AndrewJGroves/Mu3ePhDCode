import ROOT as R
from array import array
from Style import AtlasStyle
style = AtlasStyle()
R.gROOT.SetStyle( style.GetName() )
R.gROOT.ForceStyle()
R.TGaxis.SetMaxDigits( 4 )
R.gStyle.SetPalette(1)

c1 = R.TCanvas( 'c1', 'A Simple Graph with error bars', 200, 10, 700, 500 )
 
c1.SetGrid()
#c1.GetFrame().SetFillColor( 21 )
#c1.GetFrame().SetBorderSize( 12 )
 
n = 8;
y13 = array( 'f', [0.816662 ,0.828026 ,0.837717 ,0.797405 ,0.76739 ,0.72871 ,0.614155 ,0.494528] )
ey13 = array( 'f', [0.00283115 , 0.000849441 , 0.00252481 , 0.0021157 , 0.00347891 , 0.00207559 , 0.0035446 , 0.0025937 ] )
x13  = array( 'f', [620-500,615-500,610-500,630-500,640-500,650-500,675-500,700-500] )
ex = array( 'f', [0,0,0,0,0,0,0,0] )

y14 = array( 'f',[0.788634 ,0.656127 ,0.462739 ,0.301367 ,0.200388 ,0.107792 ,0.035318 ,0.0159673 ])
ey14= array( 'f',[0.00276724 , 0.00297314 , 0.00228913 , 0.00331217 , 0.00397889 , 0.00503897 , 0.000968488 , 0.000740674 ])
x14  = array( 'f', [45,50,60,70,80,100,150,200])

y15 =array( 'f', [0.732111 ,0.648612 ,0.564889 ,0.402142 ,0.28377 ,0.13589 ,0.0443831 ,0.0218771])
ey15 =array( 'f', [0.00323666 , 0.00271847 , 0.00347157 , 0.0035979 , 0.00203046 , 0.00222788 , 0.00115874 , 0.000778888 ])
x15  = array( 'f', [50,55,60,70,80,100,150,200])

y16 =array( 'f', [0.787353 ,0.718501 ,0.647549 ,0.50049 ,0.359734 ,0.183454 ,0.0555802 ,0.0284629 ])
ey16 =array( 'f', [0.00317927 , 0.0026915 , 0.00261502 , 0.00542957 , 0.00293562 , 0.00155295 , 0.00168318 , 0.000872934 ])
x16  = array( 'f', [50,55,60,70,80,100,150,200])

y17 =array( 'f', [0.783359 ,0.733238 ,0.665332 ,0.603559 ,0.464706 ,0.254408 ,0.0762362 ,0.0358645 ])
ey17 =array( 'f',[0.00229909 , 0.00204733 , 0.00263238 , 0.00326339 , 0.00163105 , 0.0028285 , 0.00149845 , 0.000890699 ])
x17  = array( 'f', [55,60,65,70,80,100,150,200])

leg = R.TLegend(0.7,0.65,0.95,0.89)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  


gr13 = R.TGraphErrors( n, x13, y13, ex, ey13 )
gr13.SetTitle( 'TGraphErrors Example' )
gr13.GetXaxis().SetTitle( 'Threshold/mV' )
gr13.GetYaxis().SetTitle( 'Efficiency' )
gr13.SetMarkerColor( 4 )
gr13.SetMarkerStyle( 21 )

gr14 = R.TGraphErrors( n, x14, y14, ex, ey14 )
gr15 = R.TGraphErrors( n, x15, y15, ex, ey15 )
gr16 = R.TGraphErrors( n, x16, y16, ex, ey16 )
gr17 = R.TGraphErrors( n, x17, y17, ex, ey17 )
gr14.SetMarkerColor( 5 )
gr14.SetMarkerStyle( 22 )
gr15.SetMarkerColor( 6 )
gr15.SetMarkerStyle( 23 )
gr16.SetMarkerColor( 7 )
gr16.SetMarkerStyle( 24 )
gr17.SetMarkerColor( 8 )
gr17.SetMarkerStyle( 25 )

leg.AddEntry(gr13, "MuPix 8 DAQ", "LP")
leg.AddEntry(gr14, "VNPix = 0", "LP")
leg.AddEntry(gr15, "VNPix = 2", "LP")
leg.AddEntry(gr16, "VNPix = 5", "LP")
leg.AddEntry(gr17, "VNPix = 10", "LP")

mg = R.TMultiGraph()
mg.Add(gr13)
mg.Add(gr14)
mg.Add(gr15)
mg.Add(gr16)
mg.Add(gr17)
mg.Draw("ALP")
leg.Draw("same")
mg.GetXaxis().SetLimits(40,250)
mg.GetYaxis().SetTitle( "Efficiency" )
mg.GetXaxis().SetTitle( "Threshold/mV" )
#gr13.Draw( "ALP" )
#gr14.Draw( "LP" )
#gr15.Draw( 'ALP,same' )
#gr16.Draw( 'LP' )
#gr17.Draw( 'LP' )


c1.Print("Mupix9_eff.png")
c1.Update()



