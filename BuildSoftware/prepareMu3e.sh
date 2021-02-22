#!/bin/bash

#------------------
# mu3e build, based on AG's steps on gamma.
# This part just prepares the software.
# sj, 20 Dec 2019
#------------------

# Install the code in the right place; expect Andrew to use git clone or similar...
#cd $HOME/dev
#rm -rf mu3e
#tar -xf mu3e.tar

#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

git clone git@bitbucket.org:mu3e/mu3e.git

mkdir -p mu3e/run/data/

cd mu3e

# Modify CMakeLists.txt as per AG procedure (note: do up the versions if they change)
sed -i "/project/ r /dev/stdin" CMakeLists.txt <<'EOF1'
list(APPEND CMAKE_PREFIX_PATH /user/software/geant4/geant4.10.02.p03-x86_64-cc7-48/)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX};/user/software/clhep/clhep-2.3.4.5-x86_64-cc748;/usr/include/gtkmm-3.0/;/usr/lib64/gtkmm-3.0/)
EOF1

# Modify util/src/CMakeLists.txt as per AG procedure (note: do up the versions if they change)
{ cat - util/src/CMakeLists.txt  > util/src/CMakeLists.txt.new && mv util/src/CMakeLists.txt.new  util/src/CMakeLists.txt ; } <<EOF2
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_INCLUDE_DIR /user/software/boost/boost-1.69-x86_64-cc7/include)
set(Boost_LIBRARY_DIR /user/software/boost/boost-1.69-x86_64-cc7/lib)
EOF2

# Modify mu3e/3rdparty/CMakeLists.txt, since someone released a new version of looptools (dec 23, 2019) but forgot to increment 
# the version number, hence the MD5 is false. Also, second change occurred TBD.
#sed -i 3rdparty/CMakeLists.txt -e "s/d13291db5e4d073600a03ec182280830/6e71adea2fa83d0c35879515b98421ac/"
#sed -i 3rdparty/CMakeLists.txt -e "s/d13291db5e4d073600a03ec182280830/8de9fbbf28def0cfcf64907bd9255375/"

