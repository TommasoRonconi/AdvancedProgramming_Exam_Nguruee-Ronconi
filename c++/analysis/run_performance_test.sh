#! /bin/bash

workdir=${PWD}/..
output=${workdir}/output
tools=${workdir}/analysis
mkdir -p output

cd ${workdir}
make clean
make OPT+=-DPERFORMANCE
cd ${tools}

function random_input {
    ${tools}/random.sh -m 10000000 -n $(( 2*$1 )) | awk 'BEGIN{tmp=0;} { if (FNR%2 != 0) tmp = $1; else print int(tmp), $1/1000. }' | ./tree.x
}

function ordered_input {
    ${tools}/random.sh -m 1000 -n $1 | awk ' { print FNR, $1/1000. }'
}

{
    for size in 500 1000 1500 2000 2500 3000 3500 4000
    do
	{
	    for ii in {1..10}
	    do
		ordered_input $size | ${workdir}/tree.x
	    done
	} | awk -v run="$size" -f ${tools}/avg_min_max.awk
    done
} > ${output}/test_ordered.dat

    
