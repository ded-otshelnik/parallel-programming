#!/bin/bash

# name of script is always obtained in param $0
script_name=$0

# func that prints help string
function usage() {
    echo "Usage: $script_name 
        -t <task> | --task=<task>
        -n <number of threads>|--num-threads=<number of threads>
        [-c | --compile]
        [-d | --delete]
        [-u | --unlock-mem]"
}

# parse flags by pattern
opts=$(getopt \
        --longoptions task:,compile,delete,help,num-threads:,unlock-mem\
        --options t:hn:cdu \
        --name $script_name \
        -- "$@")
eval set --${opts}

# process flags and args
while [[ $# -gt 0 ]];
do
    case $1 in
        -h | --help)
            usage
            exit 0
        ;;
        -t | --task)
            # if source file exists
            if [[ -f "$2.c" ]];
            then
                # set name of task and move to next params
                task=$2
                shift 2
            else
                echo "Source file does not exist or was not specified correctly. Use right source file name."
                usage
                exit 1
            fi
        ;;
        -n | --num-threads)
            # set number of processors
            n=$2
            shift 2
        ;;
        -c | --compile)
            # compile task by mpicc
            gcc $task.c -o $task -std=gnu99 -fopenmp
            shift
        ;;
        -d | --delete)
            # delete previous jobs results
            find . -name "$task-$n-*" -type f -delete
            shift
        ;;
        -u | --unlock-mem)
            # unlock all available memory
            ulimit -s unlimited
            shift
        ;;
        --)
            # all args that does not matched by getopt
            # will be ignored
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
done

if [ -z "${n}" ]; then
    echo "Number of threads was not set"
    usage
    exit 1
fi

# if binary file exists program will run a job
if [[ -f "$task" ]];
then
    # specify output files for out and error streams respectively
    # in following format "task-num_proc-%A.*" where %A - master task ID
    error=$task-$n-%A.err
    output=$task-$n-%A.out

    # unlock all available memory
    ulimit -s unlimited

    # create a job for slurm scheduler
    sbatch -n $n --partition=stu --error=$error --output=$output --time=5 --wrap="./$task"
else
    echo "Binary file does not exist. It must be compiled earlier or use flag "-c"."
    usage
    exit 1
fi

exit 0