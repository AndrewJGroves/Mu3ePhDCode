from ROOT import *
import csv
import math
import datetime

gStyle.SetOptStat("0")


def fit(hist,f,colour,title,yaxis):      
    hist.Draw(f)
    hist.SetLineColor(colour)
    hist.SetTitle(title)
    hist.GetYaxis().SetTitleOffset(1.4)
    hist.SetYTitle(yaxis)
    hist.GetXaxis().SetLabelSize(0)
    hist.GetXaxis().SetLabelOffset(999)

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

    fin = [[lowerv_ll,lowerv_ul,lowerv_lr,lowerv_ur,upperv_ll,upperv_ul,upperv_lr,upperv_ur],[lowerv_ll_s,lowerv_ul_s,lowerv_lr_s,lowerv_ur_s,upperv_ll_s,upperv_ul_s,upperv_lr_s,upperv_ur_s]]

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



hist_lowervll=TH2F("Lenght of v","Length of v",len(dates),1,len(dates)+1,40,-1,1)
hist_lowervul=TH2F("Lenght of vu","Length of vu",len(dates),1,len(dates)+1,40,-1,1)
hist_lowervur=TH2F("test1","test1",len(dates),1,len(dates)+1,40,-1,1)
hist_lowervlr=TH2F("test2","test2",len(dates),1,len(dates)+1,40,-1,1)

hist_uppervll=TH2F("Lenght of v1","1Length of v",len(dates),1,len(dates)+1,40,-1,1)
hist_uppervul=TH2F("Lenght of vu1","1Length of vu",len(dates),1,len(dates)+1,40,-1,1)
hist_uppervur=TH2F("test11","test11",len(dates),1,len(dates)+1,40,-1,1)
hist_uppervlr=TH2F("test21","test21",len(dates),1,len(dates)+1,40,-1,1)

hist_sepr=TH2F("testa","testa",len(dates),1,len(dates)+1,40,0,4)
hist_sepl=TH2F("testb","testb",len(dates),1,len(dates)+1,40,0,4)



for i in range(len(ladder_name)):
    ladder = './Ladders/'+ladder_name[i]+'.csv'
    ladder_file = './Ladders/'+ladder_name[i]+'.txt' 
    g=ox_read(ladder,ladder_name[i],ladder_file)
    vs = g[0]
    lowerv_ll = vs[0]
    lowerv_ul = vs[1]
    lowerv_lr = vs[2]
    lowerv_ur = vs[3]
    upperv_ll = vs[4]
    upperv_ul = vs[5]
    upperv_lr = vs[6]
    upperv_ur = vs[7]
    print lowerv_ur[3]
    for g in range(0,len(length)):
        if (g>0):
            if (i<length[g] and i>length[g-1]):
                hist_lowervll.Fill(dates[g],lowerv_ll[2]-lowerv_ll[3])
                hist_lowervul.Fill(dates[g],lowerv_ul[2]-lowerv_ul[3])
                hist_lowervur.Fill(dates[g],lowerv_ur[2]-lowerv_ur[3])
                hist_lowervlr.Fill(dates[g],lowerv_lr[2]-lowerv_lr[3])
                hist_uppervll.Fill(dates[g],upperv_ll[2]-upperv_ll[3])
                hist_uppervul.Fill(dates[g],upperv_ul[2]-upperv_ul[3])
                hist_uppervur.Fill(dates[g],upperv_ur[2]-upperv_ur[3])
                hist_uppervlr.Fill(dates[g],upperv_lr[2]-upperv_lr[3])

                hist_sepl.Fill(dates[g],abs(lowerv_ul[3]-upperv_ll[3]))
                hist_sepr.Fill(dates[g],abs(lowerv_ur[3]-upperv_lr[3]))

        else:              
            if (i<length[g]):
                hist_lowervll.Fill(dates[g],lowerv_ll[2]-lowerv_ll[3])
                hist_lowervul.Fill(dates[g],lowerv_ul[2]-lowerv_ul[3])
                hist_lowervur.Fill(dates[g],lowerv_ur[2]-lowerv_ur[3])
                hist_lowervlr.Fill(dates[g],lowerv_lr[2]-lowerv_lr[3])
                hist_uppervll.Fill(dates[g],upperv_ll[2]-upperv_ll[3])
                hist_uppervul.Fill(dates[g],upperv_ul[2]-upperv_ul[3])
                hist_uppervur.Fill(dates[g],upperv_ur[2]-upperv_ur[3])
                hist_uppervlr.Fill(dates[g],upperv_lr[2]-upperv_lr[3])

                hist_sepl.Fill(dates[g],abs(lowerv_ul[3]-upperv_ll[3]))
                hist_sepr.Fill(dates[g],abs(lowerv_ur[3]-upperv_lr[3]))




tex1 = TLatex(1,1,"XXX")
#tex1.SetNDC()
tex1.SetTextAlign(11);
tex1.SetTextColor(1);
tex1.SetTextFont(42);
tex1.SetTextSize(0.03);

c=TCanvas("Deviaton","Deviation",1200,500); 
c.Divide(2,1)
c.cd(1)
fit(hist_lowervul,"colz",kBlack,"Deviation of Lower V UL","Deviation of Lower V UL (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c.cd(2)
fit(hist_lowervll,"colz",kBlack,"Deviation of Lower V LL","Deviation of Lower V LL (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c.Print("DeviationLowerV_left.png")


c1=TCanvas("test1","test1",1200,500); 
c1.Divide(2,1)
c1.cd(1)
fit(hist_lowervur,"colz",kBlack,"Deviation of Lower V UR","Deviation of Lower V UR (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c1.cd(2)
fit(hist_lowervlr,"colz",kBlack,"Deviation of Lower V LR","Deviation of Lower V LR (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c1.Print("DeviationLowerV_right.png")


c2=TCanvas("Deviato1n","D1viation",1200,500); 
c2.Divide(2,1)
c2.cd(1)
fit(hist_uppervul,"colz",kBlack,"Deviation of Upper V UL","Deviation of Upper V UL (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c2.cd(2)
fit(hist_uppervll,"colz",kBlack,"Deviation of Upper V LL","Deviation of Upper V LL (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c2.Print("DeviationUppperV_left.png")


c3=TCanvas("test2","test2",1200,500); 
c3.Divide(2,1)
c3.cd(1)
fit(hist_uppervur,"colz",kBlack,"Deviation of Upper V UR","Deviation of Upper V UR (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c3.cd(2)
fit(hist_uppervlr,"colz",kBlack,"Deviation of Upper V LR","Deviation of Upper V LR (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-1.13,date[g])
c3.Print("DeviationUpperV_right.png")



c4=TCanvas("test3","test3",600,500); 
fit(hist_sepl,"colz",kBlack,"Seperation of ladders left","Seperation of ladders left (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-0.12,date[g])
c4.Print("LadderSepLeft.png")

c5=TCanvas("test4","test4",600,500); 
fit(hist_sepr,"colz",kBlack,"Seperation of ladders right","Seperation of ladders right (mm)")
for g in range(0,len(length)):
    tex1.DrawLatex(1.2+g,-0.12,date[g])
c5.Print("LadderSepRight.png")
