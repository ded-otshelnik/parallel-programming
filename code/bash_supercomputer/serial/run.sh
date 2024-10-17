#!/bin/bash

# name of script is always obtained in param $0
script_name=$0

# func that prints help string
function usage() {
    echo "Usage: $script_name
         -t | --task=<task>
        [-h | --help]
        [-c | --compile]
        [-d | --delete]
        [-u | --unlock-mem]"
}

opts=$(getopt \
        --longoptions task:,compile,delete,help,unlock-mem\
        --options ht:cdu \
        --name $script_name \
        -- "$@")

eval set --${opts}

# parse flags
while [[ $# -gt 0 ]]; do
    case $1 in
        -h | --help)
            usage
            exit 0
        ;;
        -t|--task)
            # if source file exists
            if [[ -f "$2.c" ]];
            then
                # set name of task and move to next params
                task=$2
                shift
            else
                echo "Source file does not exist or was not specified correctly. Use right source file name."
                usage
                exit 1
            fi
        ;;
        -c | --compile)
            # if task source file exists
            if [[ -f "$task" ]];
            then        
                # compile task by gcc
                gcc $task.c -o $task -std=gnu99 -fopenmp -Wall -g -lm
            else
                echo "Task was not specified. Use correct source file or disable flag."
                usage
                exit 1
            fi
        ;;
        -d | --delete)
            # delete previous jobs results
            find . -name "$task-*.out" -type f -delete
            find . -name "$task-*.err" -type f -delete
        ;;
        -u | --unlock-mem)
            # unlock all available memory
            ulimit -s unlimited
            shift
        ;;
        --)
            # it indicates the end of flags
            # all next args after "--" will be ignored
            shift
            break
        ;;
        *) 
            echo "Unsupported option $1"
            usage
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