#!bin/bash

# This script record the mining time of each hashing case

[ ! "$#" -eq 2 ] && echo "You must indicate the number of zeros in the second argument" && exit 0 ;

declare -i Hashing=$1;
bitcoin=$(head -c $2 < /dev/zero | tr '\0' '\60')

START=$(date +%s) ;
i=1 ;

while [ 1==1 ]
do
	Ans=$(./MSHA3 "$Hashing") ;
	subAns=${Ans:0:$2} ;
	
	if [ ${subAns} == ${bitcoin} ]; then
		
		echo "$Hashing Hash out !!!!" ;
		
		END=$(date +%s) ;
		echo "It took $(($END-$START)) second to hash" ;
		
		exit 0 ;		
	fi
	
	i=${i}+1
	Hashing=$((${Hashing} + ${i})) ;
done

