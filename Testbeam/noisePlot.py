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

pixel=960 
n = 8;
y13 = array( 'f', [19143.3/pixel ,20109.5/pixel ,21928.1/pixel ,17979/pixel ,17059.2/pixel ,15248.1/pixel ,13579.6/pixel ,10887.6/pixel ] )
x13  = array( 'f', [620-500,615-500,610-500,630-500,640-500,650-500,675-500,700-500] )
ex = array( 'f', [0,0,0,0,0,0,0,0] )
ey = array( 'f', [0,0,0,0,0,0,0,0] )

y14 = array( 'f',[2.06219e+06/pixel ,132740/pixel ,10284.7/pixel ,6862.74/pixel ,4690.5/pixel ,2561.1/pixel ,1063.12/pixel ,593.811/pixel ])
x14  = array( 'f', [45,50,60,70,80,100,150,200])

y15 =array( 'f', [271416/pixel ,32072.5/pixel ,12313.4/pixel ,8742.04/pixel ,6154.31/pixel ,3294.37/pixel ,1299.81/pixel ,722.01/pixel])
x15  = array( 'f', [50,55,60,70,80,100,150,200])

y16 =array( 'f', [494583/pixel ,78964.3/pixel ,18353.9/pixel ,10832.9/pixel ,7943/pixel ,4295.45/pixel ,1512.93/pixel ,866.504/pixel  ])
x16  = array( 'f', [50,55,60,70,80,100,150,200])

y17 =array( 'f', [189572/pixel ,37783.2/pixel ,16072.3/pixel ,13221.8/pixel ,10144.9/pixel ,5729.41/pixel ,2005.97/pixel ,1053.15/pixel  ])
x17  = array( 'f', [55,60,65,70,80,100,150,200])

leg = R.TLegend(0.7,0.65,0.95,0.89)
leg.SetFillStyle(0)
leg.SetBorderSize(0)  


gr13 = R.TGraphErrors( n, x13, y13, ex, ey )
gr13.SetTitle( 'TGraphErrors Example' )
gr13.GetXaxis().SetTitle( 'Threshold/mV' )
gr13.GetYaxis().SetTitle( 'Noise' )
gr13.SetMarkerColor( 4 )
gr13.SetMarkerStyle( 21 )

gr14 = R.TGraphErrors( n, x14, y14, ex, ey )
gr15 = R.TGraphErrors( n, x15, y15, ex, ey )
gr16 = R.TGraphErrors( n, x16, y16, ex, ey )
gr17 = R.TGraphErrors( n, x17, y17, ex, ey )
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
R.gPad.SetLogy(1)

mg.Draw("ALP")
leg.Draw("same")
#mg.GetYaxis().SetRangeUser(0,550000)
mg.GetXaxis().SetLimits(40,250)
mg.GetYaxis().SetTitle( "Noice rate per pixel / hz" )
mg.GetXaxis().SetTitle( "Threshold / mV" )
#gr13.Draw( "ALP" )
#gr14.Draw( "LP" )
#gr15.Draw( 'ALP,same' )
#gr16.Draw( 'LP' )
#gr17.Draw( 'LP' )


c1.Print("Mupix9_noise.png")
c1.Update()



