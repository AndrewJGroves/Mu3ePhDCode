#!/bin/sh


source /user/software/gcc/gccSetup.sh 8.2.0 
#cd /hepstore/agroves/MasterDev/mupix8_daq/build/analysis
cd /hepstore/agroves/Atlas_quick/mupix8_daq/build/analysis

#./analyze_dut 201910 2232 1 1 0 1 0 2242
#./analyze_dut 201910 2243 1 1 0 1 0 2253
#./analyze_dut 201910 2254 1 1 0 1 0 2262
#./analyze_dut 201910 2263 1 1 0 1 0 2269
#./analyze_dut 201910 2270 1 1 0 1 0 2276
#./analyze_dut 201910 2277 1 1 0 1 0 2284
#./analyze_dut 201910 2285 1 1 0 1 0 2291
#./analyze_dut 201910 2292 1 1 0 1 0 2298



./andrew 201910 2232 2242
./andrew 201910 2243 2253
./andrew 201910 2254 2262
./andrew 201910 2263 2269
./andrew 201910 2270 2276
./andrew 201910 2277 2284
./andrew 201910 2285 2291
./andrew 201910 2292 2298
