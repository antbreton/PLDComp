#!/bin/bash

nSuccesfulTests=0
nombreTest=`ls ./testsBackEnd | wc -l`

#Gestion paramètres
for ((o=1; $#; o++))
	do
		case $1 in
  		-st) cat testsBackEnd/Test$2/test
        	exit;;
      -o) cat testsBackEnd/Test$2/out
        	exit;;
      -e) cat testsBackEnd/Test$2/expected
        	exit;;
      -soe) cat testsBackEnd/Test$2/out > testsBackEnd/Test$2/expected
        	exit;;
			-h|--help) 
        	echo -e "COMMANDS : \t./runTests.sh executes all tests\n\t\t-st <testN> show the C code of the testN\n\t\t-o <testN> display out of the testN\n\t\t-soe <testN> set the expectation of the testN to the current out of the testN.\n\t\t-e <testN> display expectation of testN"
        	exit;;
    esac
    shift;
done

rm main.s | rm exe
# Boucle de test #
for ((i=1; i<=$nombreTest; i++)) # On parcours les différents Tests
 do
 	description=`cat testsBackEnd/Test$i/desc`
 	
	echo -e "\tTest$i : $description\n"

	./gc+ < testsBackEnd/Test$i/test > /dev/null
	make assembleur
	./exe > testsBackEnd/Test$i/out
	# on récupère le frontend
	#sed -i -n '/%%%Frontend%%%/,/%%%Backend%%%/ { //!p }' testsBackEnd/Test$i/out
	#sed -i '/^$/d' testsBackEnd/Test$i/out
	
	
	diff -wB testsBackEnd/Test$i/out testsBackEnd/Test$i/expected >> /dev/null
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
