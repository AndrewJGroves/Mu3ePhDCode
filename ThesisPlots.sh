#!/bin/bash

## This script contains all the locations for the thesis plots by chapter


##########################################################
#Chapter 4 - Testbeam
source /user/software/root/rootSetup.sh 6.18.00
cd /hepstore/agroves/MyStudies/Testbeam/

root -b -l -q 'Allignment.cpp(true)'    #Allignment Profile plots
root -b -l -q 'Allignment.cpp(false)'   #Residual Plots
python Cluster.py                       #Clusting Plots
python effiencyPlot.py                  #MuPix 9 Effiency plots
python EffNoisMap.py 8                  #MuPix 8 Track,Eff,Noise map 
python noisePlot.py                     #MuPix 9 noise plots
python EffNoisMap.py 9                  #MuPix 9 Track,Eff,Noise map 

#Matching dist and Chi2 plot missing
git add . 
git commit -m 'Testbeam Plots'
git push

##########################################################
#Chapter 5 - Mecanics

cd /hepstore/agroves/MyStudies/Mechanics/Metrology/L4TapeHeaters
python anay.py          #Produces L4 tape heater plots
cd /hepstore/agroves/MyStudies/Mechanics/PullTest
python plotting.py     #Pull Test on ladder plot
cd /hepstore/agroves/MyStudies/Mechanics/

git add . 
git commit -m 'Metrology Plots'
git push

##########################################################
#Chapter 6 - Sensitivity study

#IC and signal plots
#Anayalsis
cd /hepstore/agroves/MyStudies/SoftwareStudies/SimulationAnalysis/
bash AnalyzeIC.sh
bash AnalyzeSignal.sh  # Still need to separte so can run both at the same time/ turn to sbatch
####Plotting part
cd /hepstore/agroves/MyStudies/SoftwareStudies/Plots/
python plotter.py
python massplotter.py
git add .
git commit -m 'IC and Signal plots'
git push 
#Plots located in Figures directory 

#Resolution plots located in VariousStudies/SignalAna, taken from the mu3e software

#Sensitivty estimate 
cd /hepstore/agroves/MyStudies/SoftwareStudies/VariousStudies/SensitivityStudy/
root -b -l -q 'sensitivity.cpp+'
git add .
git commit -m 'Sensitivity BR'
git push


##########################################################
#Chapter 7 - ICmic study
#Root files have been scimmed and important varibles and plots saved at /hepstore/agroves/ICmicRootFiles

#The weight study plots 
cd /hepstore/agroves/MyStudies/SoftwareStudies/VariousStudies/HighWeight
root -b -l -q 'MainStudy.cpp+("highweight.root","plots_high.root")'
root -b -l -q 'MainStudy.cpp+("normalweight.root","plots_normal.root")'

cd /hepstore/agroves/MyStudies/SoftwareStudies/CombinationBackground/ICmic/
source /user/software/root/rootSetup.sh 6.18.00
python plotter.py
python PlotMassICmic.py

git add .
git commit -m 'IC mic Plots'
git push


############################################################
#Chapter 8 - PhoCon study
#Root files have been scimmed 

cd /hepstore/agroves/MyStudies/SoftwareStudies/CombinationBackground/PhoCon/
root -b -l -q 'AfterStuff.cpp+'
python plotter.py 
root -b -l -q 'CystralBallFit.cpp+'
root -b -l -q 'Momentum.cpp+'


git add .
git commit -m 'PhoCon'
git push
