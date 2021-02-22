#!/bin/bash

WORKDIR=/hepstore/agroves/backup/SoftwareStudies/TDRSensitity

#sbatch -p compute -c 10 -e ${WORKDIR}/Signal/RootFiles/SignalCut.err -o ${WORKDIR}/Signal/RootFiles/SignalCut.log   ./Signal/AnalyzeSignal.sh
sbatch -p compute -c 10 -e ${WORKDIR}/IC/RootFiles/IC.err -o ${WORKDIR}/IC/RootFiles/IC.log   ./IC/AnalyzeIC.sh
#sbatch -p compute -c 10 -e ${WORKDIR}/IC/RootFiles/ICold.err -o ${WORKDIR}/IC/RootFiles/ICold.log   ./IC/AnalyzeICOLD.sh
