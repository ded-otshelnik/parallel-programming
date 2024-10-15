#!/bin/bash

# name of script is always obtained in param $0
script_name=$0

# func that prints help string
function usage() {
    echo "Usage: $script_name <executable>
        -n <number of cores>|--num-proc=<number of cores>
        [--mem-per-cpu=<memory for one CPU>]
        [-c|--compile]
        [-d|--delete]"
}

# if source file exists
if [[ -f "$1.c" ]];
then
    # set name of executable file and move to next params
    task=$1
    shift
else
    echo "Source file does not exist. Use correct source file name."
    usage
    exit 1
fi

# reload modules related to MPI
module purge
module load gcc/4.8.5 openmpi/3.0.5

# parse flags by pattern
opts=$(getopt \
        --longoptions compile,delete,help,num-proc:,mem-per-cpu:\
        --options hn:cd \
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
        -n | --num-proc)
            # set number of processors
            n=$2
            shift 2
        ;;
        -c | --compile)
            # compile task by mpicc
            mpicc $task.c -o $task -std=gnu99
            shift
        ;;
        --mem-per-cpu)
            # set memory amount of real memory per each cpu
            mem_per_cpu=$2
            shift 2
        ;;
        -d | --delete)
            # delete previous jobs results
            find . -name "$task-$n-*" -type f -delete
            shift
        ;;
        --)
            # all args that does not matched by getopt
            # will be ignored
            shift
            break
        ;;
    esac
    # go to next parameter
done

if [ -z "${n}" ]; then
    echo "Number of cores was not set"
    usage $script_name
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

    if [ -z "${mem_per_cpu}" ];
    then
        # create a job for slurm scheduler
        sbatch -n $n --partition=stu --error=$error --output=$output --time=5 --wrap="mpirun ./$task"
    else
        # create a job for slurm scheduler and specify mem_per_cpu value
        sbatch -n $n --mem-per-cpu=$mem_per_cpu --partition=stu --error=$error --output=$output --time=5 --wrap="mpirun ./$task"
    fi
else
    echo "Binary file does not exist. It must be compiled earlier or use flag "-c"."
    usage
    exit 1
fi

exit 0