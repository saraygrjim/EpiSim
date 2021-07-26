#!/bin/bash
FILES="./DataStrain*.csv"
for f in $FILES
do
  python3 plot.py $f
  
done