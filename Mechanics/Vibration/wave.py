from ROOT import *
import csv
import math
import datetime
import numpy as np
from array import array

filename='NoVfold-midf2020-12-10_12.03.15.477_A0000.csv'
outname='NoVfold.png'
sumT=0
with open(filename, 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    time, dist = array( 'd' ), array('d')
    count = 0
    baset=0
    for row in reader:
        if count == 0:
            baset=float(row[0])
        t = float(row[0])
        d= float(row[1])
        tim1=t-baset
        if tim1 < 0.5:
            count += 1;
            time.append(t-baset)
            dist.append(d)

mid=(max(dist)+min(dist))/2

dist2 = array( 'd' )
for i in range(len(dist)):
    dist2.append(dist[i]-mid)

c=TCanvas()
gr = TGraph(count,time,dist2)
#gr.SetLineColor( 2 )
#gr.SetLineWidth( 4 )
#gr.SetMarkerColor( 4 )
#gr.SetMarkerStyle( 21 )
gr.SetTitle( 'V fold glued' )
gr.GetYaxis().SetTitle( 'Distance [#mum]' )
gr.GetXaxis().SetTitle( 'Time [s]' )
f1=TF1("f1","[0]*sin([1]*x+[2])+[3]",0,0.4)
f1.FixParameter(0,80);
f1.SetParameter(1,350);
f1.FixParameter(2,1.5);
f1.FixParameter(3,-10);

f1.SetParNames ("Constant","Signma","X postio","Y postion");
#gr.Fit(f1,'','',0.1,0.4)
gr.Draw( 'ACP' )
c.Print(outname)

print "The applitude ", (max(dist)-min(dist))/2
