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
        "-r" | "--recompile")
            # compile task by gcc
            gcc $task.c -o $task -std=gnu99 -fopenmp
        ;;
        "-d" | "--delete")
            # delete previous jobs results
            find . -name "$task-serial-*" -type f -delete
        ;;
    esac
    # go to next parameter
    shift
done

# specify output files for out and error streams respectively
# in following format "$task-serial-%A.*" where %A - master task ID
error=$task-serial-%A.err
output=$task-serial-%A.out

# create a job for slurm scheduler
sbatch --partition=stu --error=$error --output=$output --time=5 --wrap="./$task"