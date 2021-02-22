from ROOT import *
import csv
from Style import AtlasStyle
import math
import datetime

gStyle.SetOptStat("0")
"""
style = AtlasStyle()
gROOT.SetStyle( style.GetName() )
gROOT.ForceStyle()
TGaxis.SetMaxDigits(  )
gStyle.SetPalette(1)
"""
gStyle.SetPalette(kViridis)

def fit(hist,f,colour,title,yaxis):      
    hist.Draw(f)
    hist.SetLineColor(colour)
    hist.SetTitle(" ")
    hist.GetYaxis().SetTitleOffset(1.4)
    hist.SetYTitle(yaxis)
    hist.GetXaxis().SetLabelSize(0)
    hist.GetXaxis().SetLabelOffset(999)

def _ss(data):
    """Return sum of square deviations of sequence data."""
    c = mean(data)
    ss = sum((x-c)**2 for x in data)
    return ss

def stddev(data, ddof=0):
    """Calculates the population standard deviation
    by default; specify ddof=1 to compute the sample
    standard deviation."""
    n = len(data)
    if n < 2:
        raise ValueError('variance requires at least two data points')
    ss = _ss(data)
    pvar = ss/(n-ddof)
    return pvar**0.5

def mean(data):
    """Return the sample arithmetic mean of data."""
    n = len(data)
    if n < 1:
        raise ValueError('mean requires at least one data point')
    return sum(data)/n # in Python 2 use sum(data)/float(n)

def rotation(res):
    errorx=0.2
    errory=0.2
    a=365.821107845078*0.000001
    rotx=res[1]*math.cos(a)+res[3]*math.sin(a)
    roty=-res[1]*math.sin(a)+res[3]*math.cos(a)
    chi2x=(abs(res[1]-res[0]))**2/errorx**2
    new_chi2x=(abs(rotx-res[0]))**2/errorx**2
    chi2y=(abs(res[3]-res[2]))**2/errory**2
    new_chi2y=(abs(roty-res[2]))**2/errory**2
    new=[res[0],rotx,res[2],roty,chi2x,new_chi2x,chi2y,new_chi2y]
    return new

def aveg(a,b):
    av=(a+b)/2
    return av

def mini(a,b,c,d):
    av_ab=aveg(a,b)
    av_cd=aveg(c,d)
    min_av=min(av_ab,av_cd)
    return min_av

def maxi(a,b,c,d):
    av_ab=aveg(a,b)
    av_cd=aveg(c,d)
    max_av=max(av_ab,av_cd)
    return max_av

def ox_read(filename,ladder_num,ladder_file):
    print filename
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        nominal = []
        actual = []
        for row in reader:
            nom = float(row[1])
            act= float(row[2])
            nominal.append(nom)
            actual.append(act)
    ll_notch=[nominal[0],actual[0],nominal[1],actual[1]]
    ul_notch=[nominal[2],actual[2],nominal[3],actual[3]]
    ur_notch=[nominal[4],actual[4],nominal[5],actual[5]]
    lr_notch=[nominal[6],actual[6],nominal[7],actual[7]]
    lowerv_ll=[nominal[8],actual[8],nominal[9],actual[9]]
    lowerv_ul=[nominal[10],actual[10],nominal[11],actual[11]]
    lowerv_lr=[nominal[12],actual[12],nominal[13],actual[13]]
    lowerv_ur=[nominal[14],actual[14],nominal[15],actual[15]]
    upperv_ll=[nominal[16],actual[16],nominal[17],actual[17]]
    upperv_ul=[nominal[18],actual[18],nominal[19],actual[19]]
    upperv_lr=[nominal[20],actual[20],nominal[21],actual[21]]
    upperv_ur=[nominal[22],actual[22],nominal[23],actual[23]]
    ur_tab=[nominal[24],actual[24],nominal[25],actual[25]]
    lr_tab=[nominal[26],actual[26],nominal[27],actual[27]]
    ll_tab=[nominal[28],actual[28],nominal[29],actual[29]]
    ul_tab=[nominal[30],actual[30],nominal[31],actual[31]]
    lowerv_ll_s=[nominal[32],actual[32],nominal[33],actual[33]]
    lowerv_ul_s=[nominal[34],actual[34],nominal[35],actual[35]]
    lowerv_lr_s=[nominal[36],actual[36],nominal[37],actual[37]]
    lowerv_ur_s=[nominal[38],actual[38],nominal[39],actual[39]]
    upperv_ll_s=[nominal[40],actual[40],nominal[41],actual[41]]
    upperv_ul_s=[nominal[42],actual[42],nominal[43],actual[43]]
    upperv_lr_s=[nominal[44],actual[44],nominal[45],actual[45]]
    upperv_ur_s=[nominal[46],actual[46],nominal[47],actual[47]]

    rll_notch=rotation(ll_notch)
    rul_notch=rotation(ul_notch)
    rur_notch=rotation(ur_notch)
    rlr_notch=rotation(lr_notch)
    rlowerv_ll=rotation(lowerv_ll)
    rlowerv_ul=rotation(lowerv_ul)
    rlowerv_lr=rotation(lowerv_lr)
    rlowerv_ur=rotation(lowerv_ur)
    rupperv_ll=rotation(upperv_ll)
    rupperv_ul=rotation(upperv_ul)
    rupperv_lr=rotation(upperv_lr)
    rupperv_ur=rotation(upperv_ur)
    rur_tab=rotation(ur_tab)
    rlr_tab=rotation(lr_tab)
    rll_tab=rotation(ll_tab)
    rul_tab=rotation(ul_tab)
    rlowerv_ll_s=rotation(lowerv_ll_s)
    rlowerv_ul_s=rotation(lowerv_ul_s)
    rlowerv_lr_s=rotation(lowerv_lr_s)
    rlowerv_ur_s=rotation(lowerv_ur_s)
    rupperv_ll_s=rotation(upperv_ll_s)
    rupperv_ul_s=rotation(upperv_ul_s)
    rupperv_lr_s=rotation(upperv_lr_s)
    rupperv_ur_s=rotation(upperv_ur_s)


    ll_ul=[0.4,rul_notch[1]-rll_notch[1],(rul_notch[1]-rll_notch[1])-0.4]
    ll_lr=[383.8,rlr_notch[1]-rll_notch[1],(rlr_notch[1]-rll_notch[1])-383.8]
    ll_ur=[384.2,rur_notch[1]-rll_notch[1],(rur_notch[1]-rll_notch[1])-384.2]
    ur_lr=[0.4,rur_notch[1]-rlr_notch[1],(rur_notch[1]-rlr_notch[1])-0.4]
    ll_v=[10.3,mini(rlowerv_ul[1],rlowerv_ll[1],rupperv_ul[1],rupperv_ll[1])-rll_notch[1],(mini(rlowerv_ul[1],rlowerv_ll[1],rupperv_ul[1],rupperv_ll[1])-rll_notch[1])-10.3]
    ur_v=[10.3,rur_notch[1]-maxi(rupperv_ur[1],rupperv_lr[1],rlowerv_ur[1],rlowerv_lr[1]),(rur_notch[1]-maxi(rupperv_ur[1],rupperv_lr[1],rlowerv_ur[1],rlowerv_lr[1]))-10.3]
    len_lowerv=[363.6,aveg(rlowerv_ur[1],rlowerv_lr[1])-aveg(rlowerv_ul[1],rlowerv_ll[1]),(aveg(rlowerv_ur[1],rlowerv_lr[1])-aveg(rlowerv_ul[1],rlowerv_ll[1]))-363.6]
    len_upperv=[363.6,aveg(rupperv_ur[1],rupperv_lr[1])-aveg(rupperv_ul[1],rupperv_ll[1]),(aveg(rupperv_ur[1],rupperv_lr[1])-aveg(rupperv_ul[1],rupperv_ll[1]))-363.6]
    longest_len=[363.6,(maxi(rupperv_lr[1],rupperv_ur[1],rlowerv_lr[1],rlowerv_ur[1])-mini(rlowerv_ll[1],rlowerv_ul[1],rupperv_ll[1],rupperv_ul[1])),(maxi(rupperv_lr[1],rupperv_ur[1],rlowerv_lr[1],rlowerv_ur[1])-mini(rlowerv_ll[1],rlowerv_ul[1],rupperv_ll[1],rupperv_ul[1]))-363.6]
    lowerv_l=[8,rlowerv_ul[3]-rlowerv_ll[3],(rlowerv_ul[3]-rlowerv_ll[3])-8]
    lowerv_r=[8,rlowerv_ur[3]-rlowerv_lr[3],(rlowerv_ur[3]-rlowerv_lr[3])-8]
    upperv_l=[8,rupperv_ul[3]-rupperv_ll[3],(rupperv_ul[3]-rupperv_ll[3])-8]
    upperv_r=[8,rupperv_ur[3]-rupperv_lr[3],(rupperv_ur[3]-rupperv_lr[3])-8]
    lowerv_wid_l=[4,rlowerv_ul_s[3]-rlowerv_ll_s[3],(rlowerv_ul_s[3]-rlowerv_ll_s[3])-4]
    lowerv_wid_r=[4,rlowerv_ur_s[3]-rlowerv_lr_s[3],(rlowerv_ur_s[3]-rlowerv_lr_s[3])-4]
    upperv_wid_l=[4,rupperv_ul_s[3]-rupperv_ll_s[3],(rupperv_ul_s[3]-rupperv_ll_s[3])-4]
    upperv_wid_r=[4,rupperv_ur_s[3]-rupperv_lr_s[3],(rupperv_ur_s[3]-rupperv_lr_s[3])-4]
    len_tabUp=[390,rur_tab[1]-rul_tab[1],(rur_tab[1]-rul_tab[1])-390]
    len_tabLo=[390,rlr_tab[1]-rll_tab[1],(rlr_tab[1]-rll_tab[1])-390]

    notchs=[ll_ul[1],ll_ul[2],ur_lr[1],ur_lr[2],ll_lr[1],ll_lr[2],ll_ur[1],ll_ur[2]]
    len_v=[len_lowerv[1],len_lowerv[2],len_upperv[1],len_upperv[2],longest_len[1],longest_len[2]]
    notch_notch=[ll_v[1],ll_v[2],ur_v[1],ur_v[2]]
    v_widths=[lowerv_wid_l,lowerv_wid_r,upperv_wid_l,upperv_wid_r]
    tab_len=[len_tabUp,len_tabLo]

    fin=[notchs,len_v,notch_notch,v_widths,tab_len]

    file=open(ladder_file,"w")
    file.write("\documentclass{article} \n")
    file.write("\usepackage[a4paper,total={6in,10in}]{geometry} \n")  
    file.write("\usepackage[parfill]{parskip} \n")
    file.write("\usepackage[utf8]{inputenc} \n")
    file.write("\usepackage{hyperref} \n")
    file.write("\usepackage{graphicx} \n")
    file.write("\usepackage{float} \n")
    file.write("\usepackage{longtable} \n")
    file.write("\\begin{document} \n") 
    file.write("\centerline{\huge{%s}}" %ladder_num)
    file.write("\\begin{table}[H] \n")
    file.write("\\begin{center} \n")
    file.write("\\begin{tabular}{|l|c|c|c|c|} \n")
    file.write("\hline \n")
    file.write("& Nominal & Actual & Rotated & deviation \\\\ \n")
    file.write("\hline \n ")
    file.write("LL notch &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(ll_notch[0],ll_notch[1],rll_notch[1],rll_notch[1]-ll_notch[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(ll_notch[2],ll_notch[3],rll_notch[3],rll_notch[3]-ll_notch[2]))
    file.write("\hline \n ")
    file.write("UL notch &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(ul_notch[0],ul_notch[1],rul_notch[1],rul_notch[1]-ul_notch[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(ul_notch[2],ul_notch[3],rul_notch[3],rul_notch[3]-ul_notch[2]))
    file.write("\hline \n ")
    file.write("UR notch &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(ur_notch[0],ur_notch[1],rur_notch[1],rur_notch[1]-ur_notch[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(ur_notch[2],ur_notch[3],rur_notch[3],rur_notch[3]-ur_notch[2]))
    file.write("\hline \n ")
    file.write("LR notch &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lr_notch[0],lr_notch[1],rlr_notch[1],rlr_notch[1]-lr_notch[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lr_notch[2],lr_notch[3],rlr_notch[3],rlr_notch[3]-lr_notch[2]))
    file.write("\hline \n ")
    file.write("Lower V LL &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ll[0],lowerv_ll[1],rlowerv_ll[1],rlowerv_ll[1]-lowerv_ll[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ll[2],lowerv_ll[3],rlowerv_ll[3],rlowerv_ll[3]-lowerv_ll[2]))
    file.write("\hline \n ")
    file.write("Lower V UL &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ul[0],lowerv_ul[1],rlowerv_ul[1],rlowerv_ul[1]-lowerv_ul[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ul[2],lowerv_ul[3],rlowerv_ul[3],rlowerv_ul[3]-lowerv_ul[2]))
    file.write("\hline \n ")
    file.write("Lower V UR &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ur[0],lowerv_ur[1],rlowerv_ur[1],rlowerv_ur[1]-lowerv_ur[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ur[2],lowerv_ur[3],rlowerv_ur[3],rlowerv_ur[3]-lowerv_ur[2]))
    file.write("\hline \n ")
    file.write("Lower V LR &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_lr[0],lowerv_lr[1],rlowerv_lr[1],rlowerv_lr[1]-lowerv_lr[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_lr[2],lowerv_lr[3],rlowerv_lr[3],rlowerv_lr[3]-lowerv_lr[2]))
    file.write("\hline \n ")
    file.write("Upper V LL &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ll[0],upperv_ll[1],rupperv_ll[1],rupperv_ll[1]-upperv_ll[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ll[2],upperv_ll[3],rupperv_ll[3],rupperv_ll[3]-upperv_ll[2]))
    file.write("\hline \n ")
    file.write("Upper V UL &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ul[0],upperv_ul[1],rupperv_ul[1],rupperv_ul[1]-upperv_ul[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ul[2],upperv_ul[3],rupperv_ul[3],rupperv_ul[3]-upperv_ul[2]))
    file.write("\hline \n ")
    file.write("Upper V UR &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ur[0],upperv_ur[1],rupperv_ur[1],rupperv_ur[1]-upperv_ur[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ur[2],upperv_ur[3],rupperv_ur[3],rupperv_ur[3]-upperv_ur[2]))
    file.write("\hline \n ")
    file.write("Upper V LR &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_lr[0],upperv_lr[1],rupperv_lr[1],rupperv_lr[1]-upperv_lr[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_lr[2],upperv_lr[3],rupperv_lr[3],rupperv_lr[3]-upperv_lr[2]))
    file.write("\hline \n ")
    file.write("UR tab &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(ur_tab[0],ur_tab[1],rur_tab[1],rur_tab[1]-ur_tab[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(ur_tab[2],ur_tab[3],rur_tab[3],rur_tab[3]-ur_tab[2]))
    file.write("\hline \n ")
    file.write("LR tab &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lr_tab[0],lr_tab[1],rlr_tab[1],rlr_tab[1]-lr_tab[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lr_tab[2],lr_tab[3],rlr_tab[3],rlr_tab[3]-lr_tab[2]))
    file.write("\hline \n ")
    file.write("LL tab &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(ll_tab[0],ll_tab[1],rll_tab[1],rll_tab[1]-ll_tab[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(ll_tab[2],ll_tab[3],rll_tab[3],rll_tab[3]-ll_tab[2]))
    file.write("\hline \n ")
    file.write("UL tab &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(ul_tab[0],ul_tab[1],rul_tab[1],rul_tab[1]-ul_tab[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(ul_tab[2],ul_tab[3],rul_tab[3],rul_tab[3]-ul_tab[2]))
    file.write("\hline \n ")
    file.write("Lower V Lower Fold left &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ll_s[0],lowerv_ll_s[1],rlowerv_ll_s[1],rlowerv_ll_s[1]-lowerv_ll_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ll_s[2],lowerv_ll_s[3],rlowerv_ll_s[3],rlowerv_ll_s[3]-lowerv_ll_s[2]))
    file.write("\hline \n ")
    file.write("Lower V Upper Fold left &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ul_s[0],lowerv_ul_s[1],rlowerv_ul_s[1],rlowerv_ul_s[1]-lowerv_ul_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ul_s[2],lowerv_ul_s[3],rlowerv_ul_s[3],rlowerv_ul_s[3]-lowerv_ul_s[2]))
    file.write("\hline \n ")
    file.write("\end{tabular} \n")
    file.write("\end{center} \n")
    file.write("\end{table} \n")

    file.write("\\begin{table}[H] \n")
    file.write("\\begin{center} \n")
    file.write("\\begin{tabular}{|l|c|c|c|c|} \n")
    file.write("\hline \n ")
    file.write("Lower V Lower Fold right &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_lr_s[0],lowerv_lr_s[1],rlowerv_lr_s[1],rlowerv_lr_s[1]-lowerv_lr_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_lr_s[2],lowerv_lr_s[3],rlowerv_lr_s[3],rlowerv_lr_s[3]-lowerv_lr_s[2]))
    file.write("\hline \n ")
    file.write("Lower V Upper Fold right &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ur_s[0],lowerv_ur_s[1],rlowerv_ur_s[1],rlowerv_ur_s[1]-lowerv_ur_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(lowerv_ur_s[2],lowerv_ur_s[3],rlowerv_ur_s[3],rlowerv_ur_s[3]-lowerv_ur_s[2]))
    file.write("\hline \n ")
    file.write("Upper V Lower Fold left &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ll_s[0],upperv_ll_s[1],rupperv_ll_s[1],rupperv_ll_s[1]-upperv_ll_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ll_s[2],upperv_ll_s[3],rupperv_ll_s[3],rupperv_ll_s[3]-upperv_ll_s[2]))
    file.write("\hline \n ")
    file.write("Upper V Upper Fold left &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ul_s[0],upperv_ul_s[1],rupperv_ul_s[1],rupperv_ul_s[1]-upperv_ul_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ul_s[2],upperv_ul_s[3],rupperv_ul_s[3],rupperv_ul_s[3]-upperv_ul_s[2]))
    file.write("\hline \n ")
    file.write("Upper V Lower Fold right &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_lr_s[0],upperv_lr_s[1],rupperv_lr_s[1],rupperv_lr_s[1]-upperv_lr_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_lr_s[2],upperv_lr_s[3],rupperv_lr_s[3],rupperv_lr_s[3]-upperv_lr_s[2]))
    file.write("\hline \n ")
    file.write("Upper V Upper Fold right &&&& \\\\ \n")
    file.write("X & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ur_s[0],upperv_ur_s[1],rupperv_ur_s[1],rupperv_ur_s[1]-upperv_ur_s[0]))
    file.write("Y & %2f & %2f & %2f & %2f \\\\ \n" %(upperv_ur_s[2],upperv_ur_s[3],rupperv_ur_s[3],rupperv_ur_s[3]-upperv_ur_s[2]))
    file.write("\hline \n ")
    file.write("\end{tabular} \n")
    file.write("\end{center} \n")
    file.write("\end{table} \n")

    file.write("\\begin{table}[H] \n")
    file.write("\\begin{center} \n")
    file.write("\\begin{tabular}{|l|c|c|c|} \n")
    file.write("\hline \n")
    file.write("& Nominal & Measured & Deviation \\\\ \n")
    file.write("\hline \n ")
    file.write("LL to UL & %2f & %2f & %2f \\\\ \n" %(ll_ul[0],ll_ul[1],ll_ul[2]))
    file.write("LL to LR & %2f & %2f & %2f \\\\ \n" %(ll_lr[0],ll_lr[1],ll_lr[2]))
    file.write("LL to UR & %2f & %2f & %2f \\\\ \n" %(ll_ur[0],ll_ur[1],ll_ur[2]))
    file.write("UR to LR & %2f & %2f & %2f \\\\ \n" %(ur_lr[0],ur_lr[1],ur_lr[2]))
    file.write("LL to leftmost V & %2f & %2f & %2f \\\\ \n" %(ll_v[0],ll_v[1],ll_v[2]))
    file.write("UR to rightmost V & %2f & %2f & %2f \\\\ \n" %(ur_v[0],ur_v[1],ur_v[2]))
    file.write("length lower V & %2f & %2f & %2f \\\\ \n" %(len_lowerv[0],len_lowerv[1],len_lowerv[2]))
    file.write("length upper v & %2f & %2f & %2f \\\\ \n" %(len_upperv[0],len_upperv[1],len_upperv[2]))
    file.write("Longest lenght & %2f & %2f & %2f \\\\ \n" %(longest_len[0],longest_len[1],longest_len[2]))
    file.write("Lower v-fold width l & %2f & %2f & %2f \\\\ \n" %(lowerv_wid_l[0],lowerv_wid_l[1],lowerv_wid_l[2]))
    file.write("Lower v-fold width r & %2f & %2f & %2f \\\\ \n" %(lowerv_wid_r[0],lowerv_wid_r[1],lowerv_wid_r[2]))
    file.write("Upper v-fold width l & %2f & %2f & %2f \\\\ \n" %(upperv_wid_l[0],upperv_wid_l[1],upperv_wid_l[2]))
    file.write("Upper v-fold width r & %2f & %2f & %2f \\\\ \n" %(upperv_wid_r[0],upperv_wid_r[1],upperv_wid_r[2]))
    file.write("Lower v width l & %2f & %2f & %2f \\\\ \n" %(lowerv_l[0],lowerv_l[1],lowerv_l[2]))
    file.write("Lower v width r & %2f & %2f & %2f \\\\ \n" %(lowerv_r[0],lowerv_r[1],lowerv_r[2]))
    file.write("Upper v width l & %2f & %2f & %2f \\\\ \n" %(upperv_l[0],upperv_l[1],upperv_l[2]))
    file.write("Upper v width r & %2f & %2f & %2f \\\\ \n" %(upperv_r[0],upperv_r[1],upperv_r[2]))

    file.write("\hline \n ")
    file.write("\end{tabular} \n")
    file.write("\end{center} \n")
    file.write("\end{table} \n")
    file.write("\end{document} \n")
    file.close()

    return fin


with open('ladder_names.txt') as f:
    ladder_name = f.read().splitlines() 


with open('ladderdates.txt') as f:
    ladder_date = f.read().splitlines() 

date=[]
length=[]
dates=[]
for i in range(0,len(ladder_date),2):
    date.extend([ladder_date[i]])
for i in range(1,len(ladder_date),2):
    length.extend([ladder_date[i]])
for i in range(len(length)):
    dates.extend([i+1])
    length[i] = int(length[i])
    if (i > 0):
        length[i] = length[i] + length[i-1]



hist_lenv=TH2F("Lenght of v","Length of v",len(dates),1,len(dates)+1,20,362.8,364.2)
hist_notToV=TH2F("Notch to V","Notch to V",len(dates),1,len(dates)+1,20,9.9,10.7)
hist_notnot1=TH2F("Notch to Notch","Notch to Notch",len(dates),1,len(dates)+1,20,0.29,0.55)
hist_notnot2=TH2F("Notch to Notch US to DS","Notch to Notch US to DS",len(dates),len(dates)+1,4,20,383,385)
hist_space=TH2F("Spacer dist","Spacer dist",len(dates),1,len(dates)+1,40,389,392)

file=open("Summary.txt","w")
file.write("\documentclass{article} \n")
file.write("\usepackage[left=0.5cm, right=0.5cm, top=0.5cm]{geometry} \n")  
file.write("\usepackage[parfill]{parskip} \n")
file.write("\usepackage[utf8]{inputenc} \n")
file.write("\usepackage{hyperref} \n")
file.write("\usepackage{graphicx} \n")
file.write("\usepackage{float} \n")
file.write("\\begin{document} \n") 
file.write("\centerline{\huge{\\textbf{Summary}}}")

notch=[]
ll_ulDiv=[]
lr_urDiv=[]
ll_lrDiv=[]
ll_urDiv=[]
file.write("\large{Notch to Notch} \\\\ \n")
file.write("\\begin{table}[H] \n")
file.write("\\begin{center} \n")
file.write("\\begin{tabular}{|l|c|c|c|c|c|c|c|c|}\n")
file.write("\hline \n ")
file.write("& LL to UL & & LR to UR & & LL to LR & & LL to UR & \\\\ \n")
file.write("\hline \n ")
file.write("Nominal & 0.4 && 0.4 && 383.8 && 384.2 & \\\\ \n")
file.write("\hline \n ")
for i in range(len(ladder_name)):
    ladder = './Ladders/'+ladder_name[i]+'.csv'
    ladder_file = './Ladders/'+ladder_name[i]+'.txt' 
    g=ox_read(ladder,ladder_name[i],ladder_file)
    temp=g[0]
    for g in range(0,len(length)):
        print "i ", i , " g ", g , " length ", length[g]
        if (g>0):
            if (i<length[g] and i>length[g-1]):
                hist_notnot1.Fill(dates[g],temp[0])
                hist_notnot1.Fill(dates[g],temp[2])
                hist_notnot2.Fill(dates[g],temp[4])
                hist_notnot2.Fill(dates[g],temp[6])
        else:
            if (i<length[g]):
                hist_notnot1.Fill(dates[g],temp[0])
                hist_notnot1.Fill(dates[g],temp[2])
                hist_notnot2.Fill(dates[g],temp[4])
                hist_notnot2.Fill(dates[g],temp[6])
    ll_ulDiv.append(temp[1])
    lr_urDiv.append(temp[3])
    ll_lrDiv.append(temp[5])
    ll_urDiv.append(temp[7])
    notch.append(temp)
    file.write("%s & %2f & %2f & %2f & %2f & %2f & %2f & %2f & %2f \\\\ \n" %(ladder_name[i],temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7]))
file.write("\hline \n ")
file.write("min dev && %2f && %2f && %2f && %2f \\\\ \n" %(min(ll_ulDiv),min(lr_urDiv),min(ll_lrDiv),min(ll_urDiv)))
file.write("max dev && %2f && %2f && %2f && %2f \\\\ \n" %(max(ll_ulDiv),max(lr_urDiv),max(ll_lrDiv),max(ll_urDiv)))
file.write("\hline \n ")
file.write("average offset && %2f && %2f && %2f && %2f \\\\ \n" %(mean(ll_urDiv),mean(lr_urDiv),mean(ll_lrDiv),mean(ll_urDiv)))
file.write("max dev && %2f && %2f && %2f && %2f \\\\ \n" %(stddev(ll_urDiv),stddev(lr_urDiv),stddev(ll_lrDiv),stddev(ll_urDiv)))
file.write("\hline \n ")
file.write("\end{tabular} \n")
file.write("\end{center} \n")
file.write("\end{table} \n")

v_folds=[]
lowerv_Div=[]
upperv_Div=[]
longest_Div=[]
file.write("\large{V-fold length} \\\\ \n")
file.write("\\begin{table}[H] \n")
file.write("\\begin{center} \n")
file.write("\\begin{tabular}{|l|c|c|c|c|c|c|}\n")
file.write("\hline \n ")
file.write("& Length Lower V & & Length Upper V & & Longest Length &  \\\\ \n")
file.write("\hline \n ")
file.write("Nominal & 363.6 && 363.6 && 363.6 & \\\\ \n")
file.write("\hline \n ")
for i in range(len(ladder_name)):
    ladder = './Ladders/'+ladder_name[i]+'.csv'
    ladder_file = './Ladders/'+ladder_name[i]+'.txt' 
    g=ox_read(ladder,ladder_name[i],ladder_file)
    temp=g[1]
    for g in range(0,len(length)):
        if (g>0):
            if (i<length[g] and i>length[g-1]):
                hist_lenv.Fill(dates[g],temp[0])
                hist_lenv.Fill(dates[g],temp[2])
                hist_lenv.Fill(dates[g],temp[4])
        else:
            if (i<length[g]):
                hist_lenv.Fill(dates[g],temp[0])
                hist_lenv.Fill(dates[g],temp[2])
                hist_lenv.Fill(dates[g],temp[4])
    lowerv_Div.append(temp[1])
    upperv_Div.append(temp[3])
    longest_Div.append(temp[5])
    v_folds.append(temp)
    file.write("%s & %2f & %2f & %2f & %2f & %2f & %2f \\\\ \n" %(ladder_name[i],temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]))
file.write("\hline \n ")
file.write("min dev && %2f && %2f && %2f  \\\\ \n" %(min(lowerv_Div),min(upperv_Div),min(longest_Div)))
file.write("max dev && %2f && %2f && %2f \\\\ \n" %(max(lowerv_Div),max(upperv_Div),max(longest_Div)))
file.write("\hline \n ")
file.write("average offset && %2f && %2f && %2f \\\\ \n" %(mean(lowerv_Div),mean(upperv_Div),mean(longest_Div)))
file.write("max dev && %2f && %2f && %2f  \\\\ \n" %(stddev(lowerv_Div),stddev(upperv_Div),stddev(longest_Div)))
file.write("\hline \n ")
file.write("\end{tabular} \n")
file.write("\end{center} \n")
file.write("\end{table} \n")


notchToNotch=[]
right_Div=[]
left_Div=[]
file.write("\large{Notch to notch distance \\\\ \n")
file.write("\\begin{table}[H] \n")
file.write("\\begin{center} \n")
file.write("\\begin{tabular}{|l|c|c|c|c|}\n")
file.write("\hline \n ")
file.write("& LL to leftmost v & & UR to rightmost v &  \\\\ \n")
file.write("\hline \n ")
file.write("Nominal & 10.3 && 10.3 & \\\\ \n")
file.write("\hline \n ")
for i in range(len(ladder_name)):
    ladder = './Ladders/'+ladder_name[i]+'.csv'
    ladder_file = './Ladders/'+ladder_name[i]+'.txt'
    g=ox_read(ladder,ladder_name[i],ladder_file)
    temp=g[2]
    for g in range(0,len(length)):
        if (g>0):
            if (i<length[g] and i>length[g-1]):
                hist_notToV.Fill(dates[g],temp[0])
                hist_notToV.Fill(dates[g],temp[2])
        else:
            if (i<length[g]):
                hist_notToV.Fill(dates[g],temp[0])
                hist_notToV.Fill(dates[g],temp[2])
    left_Div.append(temp[1])
    right_Div.append(temp[3])
    notchToNotch.append(temp)
    file.write("%s & %2f & %2f & %2f & %2f \\\\ \n" %(ladder_name[i],temp[0],temp[1],temp[2],temp[3]))
file.write("\hline \n ")
file.write("min dev && %2f && %2f   \\\\ \n" %(min(left_Div),min(right_Div)))
file.write("max dev && %2f && %2f \\\\ \n" %(max(left_Div),max(right_Div)))
file.write("\hline \n ")
file.write("average offset && %2f && %2f  \\\\ \n" %(mean(left_Div),mean(right_Div)))
file.write("max dev && %2f && %2f  \\\\ \n" %(stddev(left_Div),stddev(right_Div)))
file.write("\hline \n ")
file.write("\end{tabular} \n")
file.write("\end{center} \n")
file.write("\end{table} \n")

file.write("\large{Spacer to spacer \\\\ \n")
file.write("\\begin{table}[H] \n")
file.write("\\begin{center} \n")
file.write("\\begin{tabular}{|l|c|c|c|c|}\n")
file.write("\hline \n ")
file.write("& Upper & & Lower &  \\\\ \n")
file.write("\hline \n ")
file.write("Nominal & 390 && 390 & \\\\ \n")
file.write("\hline \n ")
for i in range(len(ladder_name)):
    ladder = './Ladders/'+ladder_name[i]+'.csv'
    ladder_file = './Ladders/'+ladder_name[i]+'.txt' 
    g=ox_read(ladder,ladder_name[i],ladder_file)
    temp=g[4]
    up_tab=temp[0]
    do_tab=temp[1]
    for g in range(0,len(length)):
        if (g>0):
            if (i<length[g] and i>length[g-1]):
                hist_space.Fill(dates[g],do_tab[1])
                hist_space.Fill(dates[g],up_tab[1])
        else:
            if (i<length[g]):
                hist_space.Fill(dates[g],do_tab[1])
                hist_space.Fill(dates[g],up_tab[1])
    file.write("%s & %2f & %2f & %2f & %2f \\\\ \n" %(ladder_name[i],up_tab[1],up_tab[2],do_tab[1],do_tab[2]))
file.write("\hline \n ")
file.write("\end{tabular} \n")
file.write("\end{center} \n")
file.write("\end{table} \n")



file.write("\large{Summary} \\\\ \n")
file.write("\\begin{table}[H] \n")
file.write("\\begin{center} \n")
file.write("\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|}\n")
file.write("\hline \n ")
file.write("& LL & UR & L end of V & R end of V & L endwall v & R endwall & L v-clearance & R v-clearnance & bend  \\\\ \n")
file.write("\hline \n ")
file.write("Nominal & -192.1 & 192.1 & -181.8 & 181.8 & -182 & 182 & 0.2 & 0.2 & 0.47 \\\\ \n")
file.write("\hline \n ")
for i in range(len(ladder_name)):
    noc=notch[i]
    v_fol=v_folds[i]
    noc_noc=notchToNotch[i]
    file.write("%s & %2.2f & %2.2f & %2.2f & %2.2f  & %2.2f  & %2.2f  & %2f  & %2f  & %2.4f \\\\ \n" %(ladder_name[i],-(noc[6]/2),noc[6]/2,(-(noc[6]/2)+noc_noc[0]),noc[6]/2-noc_noc[2],-182-0.105,182+0.105,(-(noc[6]/2)+noc_noc[0])-(-182-0.105),(noc[6]/2-noc_noc[2])-(182+0.105),noc_noc[0]-((-(noc[6]/2)+noc_noc[0])-(-182-0.105))-9.63))
file.write("\hline \n ")
file.write("\end{tabular} \n")
file.write("\end{center} \n")
file.write("\end{table} \n")


file.write("\end{document} \n")
file.close()

tex1 = TLatex(1,1,"XXX")
#tex1.SetNDC()
tex1.SetTextAlign(11);
tex1.SetTextColor(1);
tex1.SetTextFont(42);
tex1.SetTextSize(0.03);

myarrow1 =TArrow(1,363.6,len(dates)+1,363.6,0.02,"|");
myarrow1.SetLineWidth(4)
myarrow2 =TArrow(1,0.4,len(dates)+1,0.4,0.02,"|");
myarrow2.SetLineWidth(4)
myarrow3 =TArrow(1,383.8,len(dates)+1,383.8,0.02,"|");
myarrow3.SetLineWidth(4)
myarrow4 =TArrow(1,384.2,len(dates)+1,384.2,0.02,"|");
myarrow4.SetLineWidth(4)
myarrow5 =TArrow(1,10.3,len(dates)+1,10.3,0.02,"|");
myarrow5.SetLineWidth(4)
myarrow6 =TArrow(1,390,len(dates)+1,390,0.02,"|");
myarrow6.SetLineWidth(4)

fit(hist_lenv,"colz",kBlack,"Length of V","Length of V [mm]")
myarrow1.Draw()
for g in range(0,len(length)):
    tex1.DrawLatex(1.05+g,362.73,date[g])

c1.Print("lenv.pdf")

fit(hist_notToV,"colz",kBlack,"Notch to V","Notch to V (mm)")
myarrow5.Draw()
for g in range(0,len(length)):
    tex1.DrawLatex(1.34+g,9.86,date[g])

c1.Print("notToV.png")

fit(hist_notnot1,"colz",kBlack,"Notch to Notch","Notch to Notch (mm)")
myarrow2.Draw()
for g in range(0,len(length)):
    tex1.DrawLatex(1.34+g,0.278,date[g])

c1.Print("notnot1.png")

fit(hist_notnot2,"colz",kBlack,"Notch to Notch US to DS","Notch to Notch US to DS (mm)")
myarrow3.Draw()
for g in range(0,len(length)):
    tex1.DrawLatex(1.34+g,383.1,date[g])
myarrow4.Draw()
c1.Print("notnot2.png")

fit(hist_space,"colz",kBlack,"Spacer dist","Spacer distance [mm]")
myarrow6.Draw()
for g in range(0,len(length)):
    tex1.DrawLatex(1+g,388.87,date[g])
c1.Print("spacer.pdf")

