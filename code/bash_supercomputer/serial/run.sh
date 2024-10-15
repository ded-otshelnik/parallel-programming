#!/bin/bash

# name of script is always obtained in param $0
script_name=$0

# func that prints help string
function usage() {
    echo "Usage: $script_name <task>
        [-c|--compile]
        [-d|--delete]"
}

# if source file exists
if [[ -f "$1.c" ]];
then
    # set name of task and move to next params
    task=$1
    shift
else
    echo "Source file does not exist. Use correct source file name."
    usage
    exit 1
fi

opts=$(getopt \
        --longoptions compile,delete,help\
        --options hcd \
        --name $script_name \
        -- "$@")

eval set --${opts}

# parse flags
while [[ $# -gt 0 ]]; do
    case $1 in
        -n | --num_proc)
            # set number of processors
            n=$2
            shift
        ;;
        -c | --compile)
            # compile task by gcc
            gcc $task.c -o $task -std=gnu99 -fopenmp
        ;;
        -d | --delete)
            # delete previous jobs results
            find . -name "$task-*.out" -type f -delete
            find . -name "$task-*.err" -type f -delete
        ;;
        --)
            # it indicates the end of flags
            # all next after "--" args  will be ignored
            shift
            break
        ;;
        *) 
            echo "Unsupported option $1"
            usage $script_name
            exit 1
        ;;
    esac
    # go to next parameter
    shift
done

# if binary file exists program will run a job
if [[ -f "$task" ]];
then
    # specify output files for out and error streams respectively
    # in following format "$task-serial-%A.*" where %A - master task ID
    error=$task-serial-%A.err
    output=$task-serial-%A.out

    # create a job for slurm scheduler
    sbatch --partition=stu --error=$error --output=$output --time=5 --wrap="./$task"
else
    echo "Binary file does not exist. It must be compiled earlier or use flag "-c"."
    usage
    exit 1
fi

exit 0