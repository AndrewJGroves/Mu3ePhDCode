#!/usr/bin/env python

import sys
from math import sqrt
import ROOT as R


def func(x):
    if x < 10 or x > 100:
        return 0
    return x/100.


h_all  = R.TH1F("h_all","h_all",100,0.,100.)
h_pass = R.TH1F("h_pass","h_pass",100,0.,100.)


ran = R.TRandom3(1)

N=1000

for i in range(0,N):
    entry = ran.Exp(20.)
    h_all.Fill( entry )
    eff = ran.Uniform()
    if func(entry) > eff:
        h_pass.Fill(entry)

c = R.TCanvas()
R.gPad.SetLogy()
h_all.SetStats(0)
h_all.SetTitle("")
h_pass.SetFillColor(5)
h_all.Draw()
h_pass.Draw("HIST,same")
R.gPad.RedrawAxis()
# just to keep the window open
text = raw_input()
