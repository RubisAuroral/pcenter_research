#!/bin/sh

dr='instances'
result='solutions'

for file in `ls $dr`
do
	nbnode=$(head -n 1 "$dr/$file" | tr -s ' ' | cut -d ' ' -f 2)
	for pop in $((nbnode/2)) ${nbnode} $(($nbnode*2))
	do
		for nbgen in 50 100 200 350
		do
			for tm in 1 3 5
			do
				best=`./main -g -f $dr/$file -G $nbgen -p $pop -m $tm`
				coutTotal=`echo $best | cut -d ';' -f 1`
				genTotal=`echo $best | cut -d ';' -f 2`
				i=1
				while [ $i -ne 10 ]
				do
					i=$(($i+1))
					best2=`./main -g -f $dr/$file -G $nbgen -p $pop -m $tm`
					coutTotal=$(($coutTotal+`echo $best2 | cut -d ';' -f 1`))
					genTotal=$(($genTotal+`echo $best2 | cut -d ';' -f 2`))
					if [ `echo $best | cut -d ';' -f 1` -gt `echo $best2 | cut -d ';' -f 1` ]
					then
						best=$best2
					fi
				done
				echo $nbgen";" $pop";" $tm"%;" `echo $best | cut -d ';' -f 1`";" `echo $best | cut -d ';' -f 2`";" `echo $best | cut -d ';' -f 3`";" `expr $coutTotal / 10`";" `expr $genTotal / 10` >> $result/$file._algogen.csv
			done
		done
	done
	sed -i '1iNombre de génération; Taille de la population; Taux de mutation; Cout meilleure solution trouvée; Génération où la meilleure solution a été rencontrée; Centre de la solution; CoutMoyen; Generation moyenne à laquelle est trouvé la meilleure' $result/$file_algogen.csv
done
