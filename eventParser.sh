#!/bin/bash

if [ "$1" ==  "" ]; then
  file=slight.out
else
  file=$1
fi

if [ "$2" == "" ]; then
  out=eventsParsed.txt
else
  out=eventsParsed.txt
fi

echo "Using input file: $file and output file: $out"

awk '{if(/TRACK/) print $NF, $6, $3, $4, $5}' $file > $out


