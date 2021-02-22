#!/bin/sh


source /user/software/gcc/gccSetup.sh 8.2.0 
#cd /hepstore/agroves/MasterDev/mupix8_daq/build/analysis
cd /hepstore/agroves/Atlas_quick/mupix8_daq/build/analysis

#./analyze_dut 201910 2309 1 1 0 1 0 2318
#./analyze_dut 201910 2319 1 1 0 1 0 2325
#./analyze_dut 201910 2326 1 1 0 1 0 2332
#./analyze_dut 201910 2333 1 1 0 1 0 2339
#./analyze_dut 201910 2340 1 1 0 1 0 2346
#./analyze_dut 201910 2347 1 1 0 1 0 2354
#./analyze_dut 201910 2355 1 1 0 1 0 2361

./andrew 201910 2309 2318
./andrew 201910 2319 2325
./andrew 201910 2326 2332
./andrew 201910 2333 2339
./andrew 201910 2340 2346
./andrew 201910 2347 2354
./andrew 201910 2355 2361
