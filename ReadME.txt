Hexanome : H4314 (Antoine Breton, Nicolas Brunet, Nathan Arsac, Luca Hennart,Youssef Chettar, Maxime Rauturier, Quentin Toulou).
------

Bilan des fonctionnalités

------
Vous trouverez ci-dessous une liste des fonctionnalités qui sont prises en compte. Nous avons séparés les fonctionnalités prises en compte par le frontend et celles par le backend.


Résultats des fonctionnalités prises en compte par le FrontEnd :

Le frontend prend en compte :
- main vide
- déclaration de variable (rajout en table des symboles, pas un noeud de l'AST)
- affectation de variable
- déclaration et affection simultanée (même ligne)
- déclaration multiple (meme ligne)
- les if (tous les cas)
- les for et while
- les additions
- les soustractions
- les multiplication
- les divisions
- les modulo
- les appels de fonctions (uniquement avec parametre(s) )
- l'utilisation de bloc arbitraire

Des passes sur l'AST permettent de :
- vérifier la présence d'un main
- verifier la correction du return;
- résoudre la portée des variables (une variable est définit partout dans son bloc, meme si elle est définit en derniere instruction)


Le frontend ne prend pas en compte :
- les appel de fonction sans parametres
- les tableaux


Pour les test, faire tourner ./runTest.sh

Des ajustements de dernieres minutes font bugger l'affichage de l'affectation des chars et donc echouer un test, mais c'est uniquement un probleme d'affichage
----------------------------------------------------------------------------------------

Résultats des fonctionnalités prises en compte par le BackEnd :

Le backend prend en compte :
- main vide
- declaration de variable (ne fait rien)
- assignation de variable
- affichage de constante
- affichage de variable (via ascii)
- comparaison(< ; < ; <= ; >= ; == ; !=) : constante/constante; constante/variable; variable/variable
- les if et else 
- les additions : constante/constante; constante/variable; variable/variable 
- les soustractions : constante/constante; constante/variable; variable/variable
- les multiplications : constante/constante; constante/variable; variable/variable
- les priorités arithmétiques avec les parenthèses
- le putchar


Le backend ne prend pas en compte :

- les appels de fonctions
- return de fonction
- les elseIf
- les ifs imbriqués
- les for 
- while (l'IR est quasiment prête, il manque l'étiquette dans l'assembleur pour revenir sur l'instruction de comparaison et quelques bugs encore présents)
- l'utilisation de bloc arbitraire (les instructions entre les {} n'apparaissent pas)
- les divisions
- les modulo

pour les test, faire tourner ./runTestBackEnd.sh
