from ROOT import *
import csv
import math
from array import array
import datetime

filename='bare600_1.csv'
outname='bare600_1'
def run(outname):
    filename = outname+'.csv'
    outfile = outname+'.pdf'
    force1 = []
    extension1 = []
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            nom = float(row[0])
            act= float(row[1])
            force1.append(nom)
            extension1.append(act)


    force = array( 'f', force1 )
    extension = array( 'f', extension1 )
    n = len(force)

    c1 = TCanvas()
    gr = TGraph( n, extension, force)
    gr.SetTitle( '' )
    gr.GetXaxis().SetTitle( 'Exention [#mum]' )
    gr.GetYaxis().SetTitle( 'Force [N]' )
    gr.Draw( 'ACP' )
    c1.Print(outfile)

files=['bare600_1','bare600_3','Full100_2','Full200_1','Full200_3','Ladder200_2','Ladder500_1','Ladder500_3','bare600_2','Full100_1','Full100_3','Full200_2','Ladder200_1','Ladder200_3','Ladder500_2']

for i in range(len(files)):
    run(files[i])
