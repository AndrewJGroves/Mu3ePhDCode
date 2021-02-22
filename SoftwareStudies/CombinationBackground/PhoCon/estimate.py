import ROOT as R
import math


def esti(W,Werr,m,merr,p,perr,f):
    BR=6.03e-8
    BRerr =0.66e-8

    estimate=2.5e15 * 0.01 * 0.5 * BR * f * W * 0.461745 * p * m
    esterr=estimate * math.sqrt((BRerr/BR)**2+(Werr/W)**2+(merr/m)**2+(perr/p)**2)
    print estimate, " pm ", esterr
    print "Upper lim ",estimate+2*esterr



top=9.764e4
bottom=1.456e10
W40=top/bottom 
Werr40 =W40*math.sqrt((math.sqrt(top)/top)**2+(math.sqrt(bottom)/bottom)**2)
print Werr40
W20=2756.0/6.078e8
Werr20 =W20*math.sqrt((math.sqrt(2756.0)/2756.0)**2+(2.465e4/6.078e8)**2)

W25=4277.0/7.797e8
Werr25 =W25*math.sqrt((math.sqrt(4277.0)/4277.0)**2+(2.792e4/7.797e8)**2)

filter20 = 1/0.0952715
filter25 = 1/0.14744


mom40=2.04845e-05
momer40=1.44848e-05


mass40=0.000993113
masser40=0.000103591




perr20=1e-3
p20=1.67e-3
m20=0.00519

#esti(W40,Werr40,mass40e,masser40e,mom40e,momer40e,1)
esti(W40,Werr40,mass40,masser40,mom40,momer40,1)

#esti(W20,Werr20,m20,0,p20,perr20,filter20)
