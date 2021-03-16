#!/bin/bash
read -p "Input file: " command
read -p "Output file: " dest
read -p "Start value: " n
read -p "Delta: " delta

touch $dest
cat /dev/null > $dest

for i in {0..10}
do
	let "x =$n + $delta * $i"
	echo -e `$command $x` >> $dest
done
