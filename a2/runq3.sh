#!/bin/bash
i="0"
while [ $i -lt 10 ] 
do
    ./a.out 10000000
    i=$[$i+1]
done
