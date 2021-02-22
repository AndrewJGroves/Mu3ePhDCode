#!/bin/bash

cd ${WORKDIR1}/${TAG}

source /user/software/gcc/gccSetup.sh 6.2.0
export LD_LIBRARY_PATH=/user/software/boost/boost-1.69-x86_64-cc7/lib:$LD_LIBRARY_PATH
source ${MU3EACT}
source /user/software/geant4/geant4.10.02.p03-x86_64-cc7-48/bin/geant4.sh


SEED=$(printf "%06d" ${SLURM_ARRAY_TASK_ID})

# run your job or whatever else here
mu3eSim r${SLURM_ARRAY_TASK_ID}.mac 
mu3eSort ./data/mu3e_run_${SEED}.root ./data/run${SEED}-sort.root
rm ./data/mu3e_run_${SEED}.root
mu3eTrirec ./data/run${SEED}-sort.root ./data/run${SEED}-reco.root
rm ./data/run${SEED}-sort.root
mu3eAnaVertexfit ./data/run${SEED}-reco.root ./data/run${SEED}-ana_vertexfit.root
rm ./data/run${SEED}-reco.root
cd /bundle/data/Mu3e/build_4.3/
if [ ! -d $filename ]; then
    mkdir -p /bundle/data/Mu3e/build_4.3/$filename
fi
cd ${WORKDIR1}/${TAG}/
cp ./data/* /bundle/data/Mu3e/build_4.3/$filename/
