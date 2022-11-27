#!/bin/sh

dr='instances'
result='solutions'

best=1000
i=0
while [ $i -ne 100 ]
do
	echo $i
	i=$(($i+1))
	best2=`./main -f $dr/pmed4.txt -G 1000 -p 100 -m 1`
	coutTotal=$(($coutTotal+$best2))
	if [ $best -gt $best2 ]
	then
		best=$best2
	fi
	echo $best2 >> $result/v2.csv
done
sed -i '1i'$best $result/v2.csv
sed -i '1i'$(($coutTotal/100)) $result/v2.csv
