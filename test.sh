#!/bin/bash
echo "Threads,User Time,System Time,Clock Time"
for i in `seq 1 15`
do
    for j in `seq 1 20`
    do
        output="$(ls -1d $1 | ./proj4 thread $i | sed -n '8p;9p;10p' | awk 'BEGIN{ORS=","} {print $3}')"
        echo "$i,$output"
    done
done
