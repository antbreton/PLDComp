# Passes de compilation
## Analyse Lexicale
Nous vérifions que les mots du programme passé en entrée existent dans notre langage. Cette partie est éffectuée en lex.

## Analyse Syntaxique
Nous vérifions que le programme passé en entrée vérifie notre grammaire et nous construisons un arbre AST, représentation de ce programme avec notre structure de donnée.

## Analyse sémentique
### Passe 1 : Test de présence des return
On regarde pour chaque fonction, s'il y a un return du bon type associé (void ou Expression). On ne regarde pas si la méthode passe forcément par le return.

### Passe 2 : Test de présence d'un main
Nous regardons s'il y a un point d'entrée. C'est à dire présence d'une fonction main

### Passe 3 : Test de variable non initialisée
Nous regardons si toutes les variables sont initialisées

### Passe 4 : Test d'existance d'un identifiant
Quand nous vérifions que lorsque l'on parle d'un identifiant, celui ci existe dans la table de symbole.
Ceci gère également la portée d'un identifiant. Ainsi, si une variable n'est pas dans la table de symbole du contexte courant et de ceux de ses ancètres, alors la variable est inconnue.
####Bugs
- On ne vérifie pas l'éxistance d'un identifiant dans la condition d'un if
- l'affectation avant la déclaration est acceptée
- Ne marche pas si on a pas de bloc dans une structure de controle 
