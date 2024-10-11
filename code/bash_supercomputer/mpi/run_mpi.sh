#!/bin/bash

# name of script is always obtained in param $0
script_name=$0

# func that prints help string
function usage() {
     echo "Usage: $script_name <executable> -n|--num_proc=<number> [-r|--recompile] [-d|--delete]";
}

# set name of executable file and move to next params
task=$1
shift

# reload modules related to MPI
module purge
module load gcc/4.8.5 openmpi/3.0.5

# parse flags
while [[ $# -gt 0 ]]; do
    case "$1" in
        "-n" | "--num_proc")
            # set number of processors
            n=$2
            shift
        ;;
        "-r" | "--recompile")
            # compile task by mpicc
            mpicc $task.c -o $task -std=gnu99
        ;;
        "--mem-per-cpu")
            # set memory amount of real memory per each cpu
            mem_per_cpu=$2
            shift
        ;;
        "-d" | "--delete")
            # delete previous jobs results
            find . -name "$task-$n-*" -type f -delete
            shift
        ;;
    esac
    # go to next parameter
    shift
done

# specify output files for out and error streams respectively
# in following format "task-num_proc-%A.*" where %A - master task ID
error=$task-$n-%A.err
output=$task-$n-%A.out

# unlock all available memory
ulimit -s unlimited

# create a job for slurm scheduler
sbatch -n $n --mem-per-cpu=$mem_per_cpu --partition=stu --error=$error --output=$output --time=5 --wrap="mpirun ./$task"