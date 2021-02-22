#!/bin/bash

#------------------
# mu3e build, based on AG's steps on gamma.
# This part runs make and make install
# sj, 20 Dec 2019
#------------------

dirc=$1

cd $dirc

cd mu3e

git submodule init; git submodule update --init --recursive

mkdir build
cd build

source /user/software/cmake/cmakeSetup.sh 3.7.1

source /user/software/gcc/gccSetup.sh 8.2.0

export LD_LIBRARY_PATH=/user/software/boost/boost-1.69-x86_64-cc7/lib:$LD_LIBRARY_PATH
export BOOST_ROOT="/user/software/boost/boost-1.69-x86_64-cc7"

cmake ..
make -j$(nproc --ignore=20)
make install


