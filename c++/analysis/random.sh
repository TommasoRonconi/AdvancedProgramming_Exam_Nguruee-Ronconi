#!/bin/bash

max=-1
num=10
seed=$$
while [ $# -gt 0 ]
do
    case $1 in
	-m|--maximum)
	    max=$2
	    shift
	    ;;
	-n|--number)
	    num=$2
	    shift
	    ;;
	-s|--seed)
	    seed=$2
	    if [ $seed -lt 0 ] || [ $seed -gt 32727 ] ; then
		echo "Error: provided seed value must be in range (0,32767)!"
		exit 666
	    fi
	    shift
	    ;;
	-h|--help)
	    echo -e "Usage:\t $(basename $0) [-m|--maximum M, -n|--number N, -s|--seed S]\n"
	    echo -e "M\t maximum value of the randomly generated values (default=32767)"
	    echo -e "N\t total number of randomly generated values (default=10)"
	    echo -e "S\t seed of the random number generator (default=process number)"
	    exit 0
	    ;;
	*)
	    echo "Unknown option $1"
	    exit 1
	    ;;
    esac
    shift
done

RANDOM=$seed

unbounded_random ()
{
    echo $RANDOM
}

bounded_random ()
{
    echo $((RANDOM % ((max+1)) ))
}

# echo $num
func=unbounded_random
if [ $max -gt 0 ]; then
    func=bounded_random
fi
for ii in $( seq 0 $(( $num - 1 )) ) 
do
    $func
done

