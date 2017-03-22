%{
#include <stdio.h>
#include <stdint.h>
#include "Expression.h"

void yyerror(int *, const char *);
int yylex(void);
%}
%union {
   VAL* val32;
   VAL* val64;

   void* type;
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

   void* TODO;
   void* affect;
   void* valvar;
   int inutile;
   
   //expression
   OperateurUnaire* opeun;
   VAL* valeur;
   CARACTERE* cval;
}

/*
%token PLUS MOINS DIV OPEN CLOSE MUL
%token <ival> ENTIER

%type <ival> expr
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
%token <valeur> VAL
%token <cval> CARACTERE
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

%left VIRGULE
%right EGAL_AFFECTATION
%left OR
%left AND
%left EGALEGAL DIFF
%left INFEGAL SUPEGAL INF SUP
%left MOINS PLUS
%left MULT DIV DIVEUCL
%right NOT
%left CROCHOUVR CROCHFERM ACCOLOUVR ACCOLFERM


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

axiome : programme;

suffixe_tab : CROCHOUVR valeur_variable CROCHFERM
            | {$$ = NULL;}
            ;

declaration_droite : type IDENTIFIANT suffixe_tab;

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


type : INT32 | INT64 | CHAR | VOID;

instrv : expression PV
       | structure_de_controle
       | bloc
       | RETURN CROCHOUVR expression CROCHFERM PV
       | PV;
       
instr : instrv declaration PV;

programme : programme fonction
          | programme declaration
          |;


prototype : type IDENTIFIANT PAROUVR parametres_declaration PARFERM;

parametres_declaration : type;


expression : NOT expression { $$ = new OperateurUnaire($1); }
           | expression AND expression
           | expression OR expression
           | expression INF expression
           | expression SUP expression
           | expression INFEGAL expression
           | expression SUPEGAL expression
           | expression EGALEGAL expression
           | expression DIFF expression
           | expression PLUS expression
           | expression MOINS expression
           | expression MULT expression
           | expression DIV expression
           | expression DIVEUCL expression


           
valeur_variable : VAL { $$ = new VAL($1); }
                | CARACTERE { $$ = new CARACTERE($1); };


affectation : IDENTIFIANT EGAL_AFFECTATION expression;


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



bloc : ACCOLOUVR contenu_bloc ACCOLFERM;
contenu_bloc : contenu_bloc instr 
             | instr;

/************************/

/*axiome : expr { *resultat = $1; }
       ;

expr : expr PLUS expr { $$ = $1 + $3; }
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