#!/bin/bash -l

#SBATCH –J omp
#SBATCH –p regular
#SBATCH –N 1
#SBATCH –t 4:00:00
#SBATCH –L SCRATCH
#SBATCH –-mail-user=shaw@ucsc.edu
#SBATCH –-mail-type=ALL

export OMP_NUM_THREADS=24
./omp_hello.x
