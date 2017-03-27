%{
#include <stdio.h>
#include <stdint.h>
#include "Expression.h"
#include "Fonction.h"
#include "Structure.h"
#include "General.h"

void yyerror(int *, const char *);
int yylex(void);
%}
%union {
   Val* val32;
   Val* val64;
	 string* identifiant;
   string* type;
   //void* proto;
   void* instr;
   InstructionV* instrv;
   void* prog;
 //  void* dirprepro;
   void* blocboucle;
   BlocIf* blocif;
   BlocWhile* blocwhile;
   BlocFor* blocfor;
   void* expr;
   void* opebin;

   void* TODO;
   void* affect;
   void* valvar;
   int* inutile;
   Not *non;
   Val* valeur;
   Caractere* cval;
   Expression* expression;
	 Declaration* declaration;
   Fonction* fonc;
   Prototype* proto;
   ParametreDeclar* paramDeclar;
   std::vector<string>* listeIdentifiants;
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
%token <non> NOT

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
%type <instrv> instrv
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
%type <expression> expression
%type <TODO> declaration_droite
%type <declaration> declaration
%type <TODO> expression_for
%type <affect> affectation
%type <valvar> valeur_variable
%type <fonc> fonction
%type <paramDeclar> parametre_declaration
%type <TODO> appel_fonction
%type <TODO> liste_expression
%type <listeIdentifiants> separateur_decl

//%left IDENTIFIANT PAROUVR PARFERM INT32 INT64 CHAR VOID
%parse-param { int * resultat }

%%

/*** ANTOINE *****/
//déclaration Variables

axiome : programme;

suffixe_tab : CROCHOUVR valeur_variable CROCHFERM
            | {$$ = NULL;}
            ;

declaration_droite : type IDENTIFIANT suffixe_tab { $$ = new Declaration(*$1);};

separateur_decl : separateur_decl VIRGULE IDENTIFIANT { $$->push_back("test");}	// A chaque appel on push l'identifiant courant dans la liste
                | /* vide */ { $$ = new std::vector<string>();};			// On crée la liste d'identifiant quand on est sur vide

declaration : declaration_droite separateur_decl { $$->setIdentifiants($2);}
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


type : INT32 { $$ = new string("INT32");}
		 | INT64 { $$ = new string("INT64");}
		 | CHAR { $$ = new string("CHAR");}
		 | VOID { $$ = new string("VOID");};

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



expression : NOT expression { $$ = new Not($2); }
           | expression AND expression
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
           | PAROUVR expression PARFERM 
           | appel_fonction
           | affectation
           | IDENTIFIANT
           | valeur_variable;


           
valeur_variable : VAL
                | CARACTERE


affectation : IDENTIFIANT EGAL_AFFECTATION expression;



/**** QUENTIN ****/
structure_de_controle : bloc_if 
                      | bloc_boucle;

bloc_if : IF PAROUVR expression PARFERM instrv ELSE instrv 
        | IF PAROUVR expression PARFERM instrv { $$ = new BlocIf($3,$5);} ;

bloc_boucle : bloc_for | bloc_while;
/* pas dans la structure de données
expression_for : expression
               | ;
*/
bloc_for : FOR PAROUVR expression PV expression PV expression PV PARFERM instrv { $$ = new BlocFor($3,$5,$7,$10);};

bloc_while : WHILE PAROUVR expression PARFERM instrv { $$ = new BlocWhile($3,$5);};
////*******/////



bloc : ACCOLOUVR contenu_bloc ACCOLFERM;
contenu_bloc : contenu_bloc instr 
             | instr;


void yyerror(int * res, const char * msg) {
   printf("Syntax error : %s\n",msg);
}

int main(void) {
   int res = 0;
   yyparse(&res);
   printf("Résutlat : %d\n",res);
   return 0;
}
