#!/bin/bash
## batch system details: see here
## https://hep.ph.liv.ac.uk/twiki/Computing/BatchProcessing

## information needed
BUILDPATH=/hepstore/agroves/dev/mu3e
EMAIL=sgagrove@liverpool.ac.uk
MU3EACT=${BUILDPATH}/install/activate.sh
MACPATH=${BUILDPATH}/run

echo The Build for this simualtion is ${BUILDPATH}
echo The email address to send finished email to is ${EMAIL}
echo 
echo What is the start run number?
read START
echo What is the end run number?
read END
vals=($(seq $START 1 $END))
echo How many frames do you want to generate?
read tot
echo What directory name shall it be saved as?
read filename
dif=$(($END-$START+1))
fil=$((116*$dif))
totevent=$(($tot+$fil))
size=$(($totevent/$dif))
TAG="myTestJob_"

WORKDIR=/scratch/$USER/mu3ejobs/${TAG}
mkdir -p ${WORKDIR}
cd ${WORKDIR}
ln -s ${MACPATH}/* .
find . -name data -type l -delete
mkdir -p data
for i in ${vals[@]}; do
## Makes the run macro with the Seed and the size and saves it to the path
    echo /mu3e/run/setRunNumber ${i} >> r${i}.mac
    echo /run/beamOn ${size} >> r${i}.mac
done
#echo "Made directory ${WORKDIR}"
#echo " and copied setup from ${MACPATH}"
WORKDIR1=/scratch/$USER/mu3ejobs
cd /hepstore/agroves/MyStudies/SoftwareStudies/SimulationScripts/Version2/
# this is the actual submission command
sbatch -p compute -t 48:00:00 -c 1 -o /$WORKDIR1/out%A_%a.out --array=$START-$END%50 --mail-user=${EMAIL} --mail-type=END --export=TAG=${TAG},WORKDIR1=${WORKDIR1},MU3EACT=${MU3EACT},filename=${filename},SEED=${SEED} prepareAndRun.sh





