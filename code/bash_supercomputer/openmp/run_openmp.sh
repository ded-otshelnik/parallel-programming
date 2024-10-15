#!/bin/bash

# name of script is always obtained in param $0
script_name=$0

# func that prints help string
function usage() {
     echo "Usage: $script_name <executable> [-r|--recompile] [-d|--delete]";
}

# set name of executable file and move to next params
task=$1
shift

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
            gcc $task.c -o $task -std=gnu99 -fopenmp
        ;;
        "-d" | "--delete")
            # delete previous jobs results
            find . -name "$task-$n-*" -type f -delete
        ;;
    esac
    # go to next parameter
    shift
done

if [ -z "${n}" ]; then
    echo "Number of processors was not set"
    usage $script_name
    exit 1
fi

# specify output files for out and error streams respectively
# in following format "task-num_proc-%A.*" where %A - master task ID
error=$task-$n-%A.err
output=$task-$n-%A.out

# create a job for slurm scheduler
sbatch -n $n --partition=stu --error=$error --output=$output --time=5 --wrap="./$task"