#!/bin/sh
#sbatch -p compute -c 8 Scan13_analyze.sh 
#sbatch -p compute -c 8 Scan14_analyze.sh 
#sbatch -p compute -c 8 Scan15_analyze.sh 
#sbatch -p compute -c 8 Scan16_analyze.sh 
#sbatch -p compute -c 8 Scan17_analyze.sh 

sbatch -p short -c 8 -t 08:00:00 Scan13_analyze.sh 
sbatch -p short -c 8 -t 08:00:00 Scan14_analyze.sh 
sbatch -p short -c 8 -t 08:00:00 Scan15_analyze.sh 
sbatch -p short -c 8 -t 08:00:00 Scan16_analyze.sh 
sbatch -p short -c 8 -t 08:00:00 Scan17_analyze.sh 
