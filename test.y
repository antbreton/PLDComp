%{
#include <stdio.h>
#include <stdint.h>
void yyerror(int *, const char *);
int yylex(void);
%}
%union {
   int32_t val32;
   int64_t val64;
   char cval;
   void* type;
   void* typev;
   void* proto;
   void* instr;
   void* instrv;
   void* prog;
 //  void* dirprepro;
   void* blocboucle;
   void* blocif;
   void* blocwhile;
   void* expr;
   void* opebin;
   void* opeun;
   void* TODO;
   void* affect;
   void* valvar;
 int inutile;
}
/*
%token PLUS MOINS DIV OPEN CLOSE MUL
%token <ival> ENTIER

%type <ival> expr

%left MOINS PLUS
%left MUL DIV
*/
%token IDENTIFIANT
%token PAROUVR PARFERM
%token <val32> INT32
%token <val64> INT64 
%token <cval> CHAR 
%token VOID
%token PV                   // ;
%token RETURN
%token CROCHOUVR
%token CROCHFERM
%token ACCOLOUVR
%token ACCOLFERM
%token IF
%token ELSE
%token WHILE
%token FOR
%token VIRGULE
%token EGALEGAL
%token EGAL_AFFECTATION
%token VAL
%token CARACTERE
%token AND
%token OR
%token INF
%token SUP
%token INFEGAL
%token SUPEGAL
%token DIFF
%token PLUS
%token MOINS
%token MULT
%token DIV
%token DIVEUCL
%token NOT



%type <typev> typev
%type <type> type
%type <TODO> instrv
%type <TODO> instr
%type <prog> programme
%type <proto> prototype 
//%type <dirprepro> dirpreprocesseur
%type <inutile> axiome
%type <blocif> bloc_if
%type <blocboucle> bloc_boucle
%type <blocfor> bloc_for
%type <blocwhile> bloc_while
%type <TODO> suffixe_tab
%type <TODO> bloc
%type <TODO> contenu_bloc
%type <expr> expression
%type <opebin> operateurbinaire
%type <opeun> operateurunaire
%type <TODO> declaration_droite
%type <TODO> expression_for
%type <affect> affectation
%type <valvar> valeur_variable
%type <TODO> fonction
%type <TODO> parametre_declaration
%type <TODO> appel_fonction
%type <TODO> liste_expression


//%left IDENTIFIANT PAROUVR PARFERM INT32 INT64 CHAR VOID
%parse-param { int * resultat }

%%

/*** ANTOINE *****/
//déclaration Variables

suffixe_tab : CROCHOUVR valeur_variable CROCHFERM
            | {$$ = NULL;}
            ;

declaration_droite : typev IDENTIFIANT suffixe_tab;

separateur_decl : separateur_decl VIRGULE IDENTIFIANT
                | /* vide */;

declaration : declaration_droite separateur_decl
            | declaration_droite separateur_decl EGAL_AFFECTATION expression;

//fonction
fonction : prototype PV
         | prototype bloc;

parametre_declaration : parametre_declaration VIRGULE declaration_droite
                    | declaration_droite;


prototype : type IDENTIFIANT PAROUVR parametre_declaration PARFERM;

appel_fonction : IDENTIFIANT PAROUVR liste_expression PARFERM;

liste_expression : expression VIRGULE liste_expression
                | expression;

typev : INT32 | INT64 | CHAR;
type : typev | VOID;
instrv : expression PV
       | structure_de_controle
       | bloc
       | RETURN CROCHOUVR expression CROCHFERM PV
       | PV;
instr : instrv declaration PV
programme : programme fonction
          | programme declaration
          |;
axiome : programme;

prototype : type IDENTIFIANT PAROUVR parametres_declaration PARFERM;
parametres_declaration : type;

expression : operateurunaire expression
           | expression operateurbinaire expression
           | PAROUVR expression PARFERM 
           | appel_fonction
           | affectation
           | IDENTIFIANT
           | valeur_variable;
valeur_variable : VAL
                | CARACTERE;
affectation : IDENTIFIANT EGAL_AFFECTATION expression;
operateurbinaire : AND
                 | OR
                 | INF
                 | SUP
                 | INFEGAL
                 | SUPEGAL
                 | EGALEGAL
                 | DIFF
                 | PLUS
                 | MOINS
                 | MULT
                 | DIV
                 | DIVEUCL;
operateurunaire : NOT;

/**** QUENTIN ****/
structure_de_controle : bloc_if | bloc_boucle;

bloc_if : IF PAROUVR expression PARFERM instrv ELSE instrv 
        | IF PAROUVR expression PARFERM instrv;

bloc_boucle : bloc_for | bloc_while;
expression_for : expression
              | ;
bloc_for : FOR PAROUVR expression_for PV expression_for PV expression_for PV PARFERM instrv;

bloc_while : WHILE PAROUVR expression PARFERM instrv;
////*******/////


/******LUCA SANS S******/
bloc : ACCOLOUVR contenu_bloc ACCOLFERM;
contenu_bloc : contenu_bloc instr 
             | instr;

/************************/

/*axiome : expr { *resultat = $1; }
       ;

expr : expr PLUS expr { $$ = /$1 + $3; }
     | expr MUL expr  { $$ = $1 * $3; }
     | expr DIV expr  { $$ = $1 / $3; }
     | expr MOINS expr{ $$ = $1 - $3; }
     | OPEN expr CLOSE{ $$ = $2; }
     | ENTIER         { $$ = $1; }
     ;
*/



%%

void yyerror(int * res, const char * msg) {
   printf("Syntax error : %s\n",msg);
}

int main(void) {
   int res = 0;
   yyparse(&res);
   printf("Résutlat : %d\n",res);
   return 0;
}
