#!/bin/sh


source /user/software/gcc/gccSetup.sh 8.2.0 
#cd /hepstore/agroves/MasterDev/mupix8_daq/build/analysis
cd /hepstore/agroves/Atlas_quick/mupix8_daq/build/analysis


#./analyze_dut 201910 2362 1 1 0 1 0 2372
#./analyze_dut 201910 2373 1 1 0 1 0 2382
#./analyze_dut 201910 2383 1 1 0 1 0 2389
#./analyze_dut 201910 2390 1 1 0 1 0 2396
#./analyze_dut 201910 2397 1 1 0 1 0 2403
#./analyze_dut 201910 2404 1 1 0 1 0 2413
#./analyze_dut 201910 2414 1 1 0 1 0 2420
#./analyze_dut 201910 2421 1 1 0 1 0 2427


./andrew 201910 2362 2372
./andrew 201910 2373 2382
./andrew 201910 2383 2389
./andrew 201910 2390 2396
./andrew 201910 2397 2403
./andrew 201910 2404 2413
./andrew 201910 2414 2420
./andrew 201910 2421 2427
