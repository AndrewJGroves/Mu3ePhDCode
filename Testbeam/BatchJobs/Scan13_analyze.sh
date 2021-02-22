#!/bin/sh


source /user/software/gcc/gccSetup.sh 8.2.0 
#cd /hepstore/agroves/MasterDev/mupix8_daq/build/analysis
cd /hepstore/agroves/Atlas_quick/mupix8_daq/build/analysis
pwd
#./analyze_dut 201910 2164 1 1 0 1 0 2169
#./analyze_dut 201910 2171 1 1 0 1 0 2177
#./analyze_dut 201910 2178 1 1 0 1 0 2185
#./analyze_dut 201910 2186 1 1 0 1 0 2193
#./analyze_dut 201910 2194 1 1 0 1 0 2200
#./analyze_dut 201910 2201 1 1 0 1 0 2207
#./analyze_dut 201910 2208 1 1 0 1 0 2214
#./analyze_dut 201910 2215 1 1 0 1 0 2221

./andrew 201910 2164 2169
./andrew 201910 2171 2177
./andrew 201910 2178 2185
./andrew 201910 2186 2193
./andrew 201910 2194 2200
./andrew 201910 2201 2207
./andrew 201910 2208 2214
./andrew 201910 2215 2221
