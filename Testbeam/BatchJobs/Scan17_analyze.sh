#!/bin/sh


source /user/software/gcc/gccSetup.sh 8.2.0 
#cd /hepstore/agroves/MasterDev/mupix8_daq/build/analysis
cd /hepstore/agroves/Atlas_quick/mupix8_daq/build/analysis

#./analyze_dut 201910 2428 1 1 0 1 0 2437
#./analyze_dut 201910 2438 1 1 0 1 0 2447
#./analyze_dut 201910 2448 1 1 0 1 0 2453
#./analyze_dut 201910 2454 1 1 0 1 0 2460
#./analyze_dut 201910 2461 1 1 0 1 0 2467
#./analyze_dut 201910 2468 1 1 0 1 0 2474
#./analyze_dut 201910 2475 1 1 0 1 0 2481
#./analyze_dut 201910 2482 1 1 0 1 0 2488

./andrew 201910 2428 2437
./andrew 201910 2438 2447
./andrew 201910 2448 2453
./andrew 201910 2454 2460
./andrew 201910 2461 2467
./andrew 201910 2468 2474
./andrew 201910 2475 2481
./andrew 201910 2482 2488
