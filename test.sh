echo -----------------------------------------------------------
echo Tests du programme Analog B3402
echo -----------------------------------------------------------

nombreTest=25;
nSuccesfulTests=0
ficherResultat="resultatTest.txt";


#--------------------- Boucle de traitement des paramètres-----------------------

for ((o=1; $#; o++))
	do
		case $1 in
        -N)
           nombreTest=$2;     
           ;;
    esac
    shift;
done

echo -e "COMPTE RENDU DU TEST\n">$ficherResultat;
 
#--------------------- Boucle de de passage de tests ----------------------------


for ((i=1; i<=$nombreTest; i++)) # On parcours les différents Tests
  do
       cat Test$i/description; # on affiche la description du test
        
       echo -e "\tTest$i : ---------\n">>$ficherResultat;
       
       Test$i/run > Test$i/res.out 2> Test$i/res.err; # on redirige les sorties standard et d'erreur vers des fichier resultat
       
       # on compare la sortie standarde résultante et la sortie standarde attendue.
       echo -e "- stdout DIFF :">>$ficherResultat;
       diff -wB Test$i/res.out Test$i/std.out >>$ficherResultat;  
       stdoutValide=$?;
       
        # on compare la sortie d'erreur résultante et la sortie d'erreur attendue.
       echo -e "- stderr DIFF :">>$ficherResultat;
       diff -wB Test$i/res.err Test$i/std.err >>$ficherResultat;
       stderrValide=$?;
       
       if [ $i -ge 21 ] # a partir du 20ème test on compare les graphes produits
        then
            # on compare le graphe produit et le graphe attendu
            diff -wB Test$i/logApache.dot.res Test$i/logApache.dot >>$ficherResultat;
            grapheValide=$?;
            if [ $grapheValide -eq 0 ] 
                then
                     echo -e "\tGRAPHE VALIDE\n";
                else
                     echo -e "\tGRAPHE INVALIDE\n";
            fi
       fi
        
       if [[ $stdoutValide -eq 0 && $stderrValide -eq 0 ]] #Si les deux sorties sont correctes
          then
            echo -e "\tVALIDE\n";       # on affiche VALIDE
            let "nSuccesfulTests=$nSuccesfulTests+1";
            nStrResult=$nStrResult" 1";            
            echo -e "\t\t==>VALIDE\n">>$ficherResultat;
            
          else                        # sinon on affiche ECHOUE
            echo -e "\tECHOUE\t check $ficherResultat for more informations.\n";
            nStrResult=$nStrResult" 0";
            echo -e "\t\t==>ECHOUE\n">>$ficherResultat;
        fi
  done
  
echo -e "\n-----------------------------------------------------------";
echo RESULTS
echo -----------------------------------------------------------
echo Results: $nSuccesfulTests/$nombreTest
