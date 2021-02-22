#!/bin/bash
## runner.C+(The run list file , The location of the simulation runs , The output file name )
root -b -l -q 'runner.C+("signal.txt","/bundle/data/Mu3e/build_4.3/signal/","signal.root")'
