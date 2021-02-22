#!/bin/bash

dirc=/user/agroves/mu3e_44
CVMFS=false

echo The directory where the software will be compiled is $dirc
echo Prepare for CVMFS $CVMFS


bash prepareMu3e.sh
bash makeInstallMu3e.sh $dirc

if [ "$CVMFS" = true ] ; then
    bash assembleMu3e.sh $dirc
    cd $dirc/mu3e
    #Modify the activate.sh script to make it relocatable in CVMFS
    sed -i ./install/activate.sh -e "s%/hepstore/agroves/grid4.4/mu3e/install%\$CVMFSLOCATION/%"
    #Make all the files writable - needed for CVMFS distribution
    find ./ -type d -exec chmod go+rx {} \;
    find ./ -type d -exec chmod go+r {} \;
    cd ../
    tar -cvf mu3e.tar mu3e
fi
