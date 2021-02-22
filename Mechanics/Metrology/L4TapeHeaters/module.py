from ROOT import *
import csv
import math
import datetime

gStyle.SetOptStat("0")
now = datetime.datetime.now()
date=now.strftime('%d-%m-%y')


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


with open('module_name.txt') as f:
    module_name = f.read().splitlines() 


length = []
for i in range(len(module_name)):
    module = 'Modules/'+module_name[i]+'.csv'
    print module_name[i]
    with open(module, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        nominal = []
        actual = []
        for row in reader:
            nom = float(row[1])
            act= float(row[2])
            nominal.append(nom)
            actual.append(act)
    print len(actual)
    print len(nominal)
    us_4=[nominal[0],actual[0],nominal[1],actual[1]]
    us_1=[nominal[2],actual[2],nominal[3],actual[3]]
    ds_1=[nominal[4],actual[4],nominal[5],actual[5]]
    ds_4=[nominal[6],actual[6],nominal[7],actual[7]]

    ladder4_us=[nominal[36],actual[36],nominal[37],actual[37],nominal[38],actual[38],nominal[39],actual[39]] 
    ladder4_ds=[nominal[8],actual[8],nominal[9],actual[9],nominal[10],actual[10],nominal[11],actual[11]] 
    ladder3_us=[nominal[32],actual[32],nominal[33],actual[33],nominal[34],actual[34],nominal[35],actual[35]] 
    ladder3_ds=[nominal[12],actual[12],nominal[13],actual[13],nominal[14],actual[14],nominal[15],actual[15]]
    ladder2_us=[nominal[28],actual[28],nominal[29],actual[29],nominal[30],actual[30],nominal[31],actual[31]] 
    ladder2_ds=[nominal[16],actual[16],nominal[17],actual[17],nominal[18],actual[18],nominal[19],actual[19]]
    ladder1_us=[nominal[24],actual[24],nominal[25],actual[25],nominal[26],actual[26],nominal[27],actual[27]] 
    ladder1_ds=[nominal[20],actual[20],nominal[21],actual[21],nominal[22],actual[22],nominal[23],actual[23]]


    end_len=[us_4[1]-ds_4[1],us_1[1]-ds_1[1]]
    end_rot=[ds_4[1]-ds_1[1],us_4[1]-us_1[1]]

    ladder1_len=[ladder1_us[1]-ladder1_ds[1],ladder1_us[5]-ladder1_ds[5]]
    ladder2_len=[ladder2_us[1]-ladder2_ds[1],ladder2_us[5]-ladder2_ds[5]]
    ladder3_len=[ladder3_us[1]-ladder3_ds[1],ladder3_us[5]-ladder3_ds[5]]    
    ladder4_len=[ladder4_us[1]-ladder4_ds[1],ladder4_us[5]-ladder4_ds[5]]

    ladder1_rot=[ladder1_us[3]-ladder1_us[7],ladder1_ds[3]-ladder1_ds[7]]
    ladder2_rot=[ladder2_us[3]-ladder2_us[7],ladder2_ds[3]-ladder2_ds[7]]
    ladder3_rot=[ladder3_us[3]-ladder3_us[7],ladder3_ds[3]-ladder3_ds[7]]
    ladder4_rot=[ladder4_us[3]-ladder4_us[7],ladder4_ds[3]-ladder4_ds[7]]

    ladder1_ds_x=mean([ladder1_ds[1],ladder1_ds[1]])
    ladder2_ds_x=mean([ladder2_ds[1],ladder2_ds[1]])
    ladder3_ds_x=mean([ladder3_ds[1],ladder3_ds[1]])
    ladder4_ds_x=mean([ladder4_ds[1],ladder4_ds[1]])

    ladder1_us_x=mean([ladder1_us[1],ladder1_us[1]])
    ladder2_us_x=mean([ladder2_us[1],ladder2_us[1]])
    ladder3_us_x=mean([ladder3_us[1],ladder3_us[1]])
    ladder4_us_x=mean([ladder4_us[1],ladder4_us[1]])

    allign_ds=[ladder2_ds_x-ladder1_ds_x,ladder3_ds_x-ladder1_ds_x,ladder4_ds_x-ladder1_ds_x]
    allign_us=[ladder2_us_x-ladder1_us_x,ladder3_us_x-ladder1_us_x,ladder4_us_x-ladder1_us_x]

    module_file = module_name[i]+'.txt' 
    file=open(module_file,"w")
    file.write("\documentclass{article} \n")
    file.write("\usepackage[a4paper,total={6in,10in}]{geometry} \n")  
    file.write("\usepackage[parfill]{parskip} \n")
    file.write("\usepackage[utf8]{inputenc} \n")
    file.write("\usepackage{hyperref} \n")
    file.write("\usepackage{graphicx} \n")
    file.write("\usepackage{float} \n")
    file.write("\usepackage{longtable} \n")
    file.write("\\begin{document} \n") 
    file.write("\centerline{\huge{Modele}}")
    file.write("\\begin{table}[H] \n")
    file.write("\\begin{center} \n")
    file.write("\\begin{tabular}{|l|c|c|c|c|} \n")
    file.write("\hline \n ")
    file.write(" & Length & Nominal & Rotation & Align to ladder 1 \\\\ \n")
    file.write("\hline \n ")
    file.write("Ladder 1 endpiece & %2.4f & 380 &  %2.4f & - \\\\ \n" %(end_len[0],end_rot[0]))
    file.write("Ladder 4 endpiece & %2.4f & 380 &  %2.4f & - \\\\ \n" %(end_len[1],end_rot[1]))
    file.write("Ladder 1 & %2.4f &    & %2.4f & - \\\\ \n" %(mean([ladder1_len[0],ladder1_len[1]]),mean([ladder1_rot[0],ladder1_rot[1]])))
    file.write("Ladder 2 & %2.4f &    & %2.4f & %2f \\\\ \n" %(mean([ladder2_len[0],ladder2_len[1]]),mean([ladder2_rot[0],ladder2_rot[1]]),mean([allign_ds[0],allign_us[0]])))
    file.write("Ladder 3 & %2.4f &    & %2.4f & %2f \\\\ \n" %(mean([ladder3_len[0],ladder3_len[1]]),mean([ladder3_rot[0],ladder3_rot[1]]),mean([allign_ds[1],allign_us[1]])))
    file.write("Ladder 4 & %2.4f &    & %2.4f & %2f \\\\ \n" %(mean([ladder4_len[0],ladder4_len[1]]),mean([ladder4_rot[0],ladder4_rot[1]]),mean([allign_ds[2],allign_us[2]])))
    file.write("\hline \n ")
    file.write("\end{tabular} \n")
    file.write("\end{center} \n")
    file.write("\end{table} \n")
    file.write("\end{document} \n")
    file.close()

    length.append((end_len[0]+end_len[1])/2)

for i in range(len(length)):
    print "Module ", i+1, " Length ",length[i]

