#! /bin/bash

#PBS -q regular
#PBS -l nodes=1:ppn=20
#PBS -l walltime=01:00:00
#PBS -o /home/tronconi/MHPC/AdvancedProgramming_Exam_Nguruee-Ronconi/c++/analysis/balance.out
#PBS -e /home/tronconi/MHPC/AdvancedProgramming_Exam_Nguruee-Ronconi/c++/analysis/balance.err

cd ${PBS_O_WORKDIR}

workdir=${PWD}/..
output=${workdir}/output
tools=${workdir}/analysis
mkdir -p ${output}

cd ${workdir}
make clean
make OPT+=-DTEST_BALANCE
cd ${tools}

function ordered_input {
    ${tools}/random.sh -m 100000 -n $1 | awk ' { print FNR, $1/1000. }'
}

{
    for size in 100 500 1000 5000 10000 15000 20000 25000 30000
    do
	{
	    for ii in {1..10}
	    do
		ordered_input $size | ${workdir}/tree.x
	    done
	} | awk -v run="$size" -f ${tools}/avg_min_max.awk
    done
} > ${output}/test_balance.dat

    
