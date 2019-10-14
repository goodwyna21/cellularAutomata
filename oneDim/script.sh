#!/bin/bash

for i in {0..255}
do
    echo -en "\b\b\b$i"
    ./automata "$i" 200 1 "saves/allrules/$i.pbm"
done
