#!/bin/bash

nSuccesfulTests=0
nombreTest=`ls ./test | wc -l`

# Boucle de test #
for ((i=1; i<=$nombreTest; i++)) # On parcours les différents Tests
 do
 	description=`cat test/Test$i/desc`
 	
	echo -e "\tTest$i : $description\n"

	./gc+ <test/Test$i/test > test/Test$i/out 2> /dev/null
	sed -i '/^$/d' test/Test$i/out
	
	diff -wB test/Test$i/out test/Test$i/expected >> /dev/null
	stdoutValide=$?;

	if [[ $stdoutValide -eq 0 ]] #Si la sortie est correcte
	then
		((nSuccesfulTests++))          
		echo -e "\033[32m\t\tVALIDE\n\033[0m"
		
	else                        # sinon on affiche ECHOUE

		echo -e "\033[31m\t\tECHOUE\n\033[0m"
	fi
done

echo -----------------------------------------------------------
echo Results: $nSuccesfulTests/$nombreTest
