# Passes de compilation
## Analyse Lexicale
Nous vérifions que les mots du programme passé en entrée existent dans notre langage. Cette partie est éffectuée en lex.

## Analyse Syntaxique
Nous vérifions que le programme passé en entrée vérifie notre grammaire et nous construisons un arbre AST, représentation de ce programme avec notre structure de donnée.

## Analyse sémentique
### Test de présence des return
On regarde pour chaque fonction, s'il y a un return du bon type associé (void ou Expression). On ne regarde pas si la méthode passe forcément par le return.

### Test de présence d'un main
Nous regardons s'il y a un point d'entrée. C'est à dire présence d'une fonction main

### Test de variable non initialisé
Nous regardons si toutes les variables sont initialisées

### Test d'existance d'un identifiant
Quand nous vérifions que lorsque l'on parle d'un identifiant, celui ci existe dans la table de symbole.
Ceci gère également la portée d'un identifiant. Ainsi, si une variable n'est pas dans la table de symbole du contexte courant et de ceux de ses ancètre, alors la variable est inconnue.
