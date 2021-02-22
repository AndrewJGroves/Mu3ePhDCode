#!/bin/bash

#------------------
# mu3e build, based on AG's steps on gamma.
# This part assembles the dependencies into the install dir.
# sj, 20 Dec 2019
#------------------

dirc=$1
echo $dirc
cd $dirc/

# Select the compiler. Change both settings at once.
source /user/software/gcc/gccSetup.sh 6.2.0; GCC=gcc-6.2.0-x86_64-cc7

# Select cmake.
source /user/software/cmake/cmakeSetup.sh 3.7.1

mostLibs=`./getLibs.pl mu3e | grep -v geant4`
# e.g. 
# /user/software/root/root-cc7/lib
# /user/software/boost/boost-1.69-x86_64-cc7/lib
# ALSO ADD $GCC ...
mostLibs="$mostLibs /user/software/gcc/$GCC/lib64/"

for lib in $mostLibs; do
  echo $dirc
  cd $lib                 # e.g. /user/software/root/root-cc7/lib
  cd ..     
  WD=`pwd`                # /user/software/root/root-cc7
  DIRNAME=`basename $WD`  # root-cc7
  cd ..                   # /user/software/root/
  
  rm -rf $dirc/mu3e/install/$DIRNAME
  mkdir -p $dirc/mu3e/install/$DIRNAME

  LIBDIR=`basename $lib` # lib or lib64
                               # /root-cc7/lib/
  mkdir -p $dirc/mu3e/install/$DIRNAME/$LIBDIR/
  
  rsync -al --delete $lib/ $dirc/mu3e/install/$DIRNAME/$LIBDIR/
  echo "export LD_LIBRARY_PATH=\$PREFIX/$DIRNAME/$LIBDIR/:\$LD_LIBRARY_PATH" >> $dirc/mu3e/install/activate.sh

  if [ -d $WD/etc/ ]; then
    rsync -al --delete $WD/etc/ $dirc/mu3e/install/$DIRNAME/etc/
  fi 

done

# Geant4 is special. Needs all the app + the data dir
cd $dirc/
GEANT4USEDTOLINK=`./getLibs.pl mu3e | sed -e "s/.*geant4\///" -e "s/\/.*//" | tr -d '\n'`

mkdir -p $dirc/mu3e/install/geant4/
mkdir -p $dirc/mu3e/install/geant4/data/
mkdir -p $dirc/mu3e/install/geant4/$GEANT4USEDTOLINK

rsync -al --delete /user/software/geant4/data/ $dirc/mu3e/install/geant4/data/
rsync -al --delete /user/software/geant4/$GEANT4USEDTOLINK/ $dirc/mu3e/install/geant4/$GEANT4USEDTOLINK/
echo "export LD_LIBRARY_PATH=\$PREFIX/geant4/$GEANT4USEDTOLINK/lib64:\$LD_LIBRARY_PATH" >> $dirc/mu3e/install/activate.sh

# Deal with Qt5 and libpcre2-16
mkdir -p $dirc/mu3e/install/oas/lib64/
ODDSANDSODS=`ldd ./mu3e/install/bin/mu3eSim | grep -e Qt5 -e libpcre2-16 | sed -e "s/.* =. //" -e "s/ .0x.*//"`
for lib in $ODDSANDSODS; do
  cp $lib $dirc/mu3e/install/oas/lib64/
done
echo "export LD_LIBRARY_PATH=\$PREFIX/oas/lib64/:\$LD_LIBRARY_PATH" >> $dirc/mu3e/install/activate.sh

# Next, find the path of all /cvmfs/grid.cern.ch stuff, and add that path to the activate.sh
GRIDCERNCH=`ldd ./mu3e/install/bin/mu3eSim | grep grid.cern.ch | sed -e "s/.* =. //" -e "s/lib64.*/lib64/" | sort | uniq`
echo "export LD_LIBRARY_PATH=$GRIDCERNCH:\$LD_LIBRARY_PATH" >> $dirc/mu3e/install/activate.sh

echo "export PATH=\$PREFIX/geant4/geant4.10.02.p03-x86_64-cc7-48/bin:\$PATH" >> $dirc/mu3e/install/activate.sh
echo "export PATH=\$PREFIX/root-cc7/bin:\$PATH" >> $dirc/mu3e/install/activate.sh
echo "export G4ABLADATA=\$PREFIX/geant4/data/G4ABLA3.0" >> $dirc/mu3e/install/activate.sh
echo "export G4ENSDFSTATEDATA=\$PREFIX/geant4/data/G4ENSDFSTATE1.2.3" >> $dirc/mu3e/install/activate.sh
echo "export G4LEDATA=\$PREFIX/geant4/data/G4EMLOW6.48" >> $dirc/mu3e/install/activate.sh
echo "export G4LEVELGAMMADATA=\$PREFIX/geant4/data/PhotonEvaporation3.2" >> $dirc/mu3e/install/activate.sh
echo "export G4NEUTRONHPDATA=\$PREFIX/geant4/data/G4NDL4.5" >> $dirc/mu3e/install/activate.sh
echo "export G4NEUTRONXSDATA=\$PREFIX/geant4/data/G4NEUTRONXS1.4" >> $dirc/mu3e/install/activate.sh
echo "export G4PIIDATA=\$PREFIX/geant4/data/G4PII1.3" >> $dirc/mu3e/install/activate.sh
echo "export G4RADIOACTIVEDATA=\$PREFIX/geant4/data/RadioactiveDecay4.3.1" >> $dirc/mu3e/install/activate.sh
echo "export G4REALSURFACEDATA=\$PREFIX/geant4/data/RealSurface1.0" >> $dirc/mu3e/install/activate.sh
echo "export G4SAIDXSDATA=\$PREFIX/geant4/data/G4SAIDDATA1.1" >> $dirc/mu3e/install/activate.sh
