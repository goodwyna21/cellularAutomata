#!/bin/bash

if [ -z "$1" ]
then
    width=20
else
    width="$(($1 + 0))"
fi

if [ -z "$2" ]
then
    height=20
else
    height="$(($2 + 0))"
fi

if [ -z "$3" ]
then
    fname="newboard.txt"
else
    fname="$3"
fi
touch "Boards/$fname"
echo "$width $height" > "Boards/$fname"

y=1
while [[ $y -le $height ]]
do
    x=1
    while [[ $x -le $width ]]
    do
        echo -n "." >> "Boards/$fname"
        ((x = x + 1))
    done
    echo "" >> "Boards/$fname"
    ((y = y + 1))
done

vim "Boards/$fname"
