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
   StructureControle* structctrl;
   BlocIf* blocif;
   BlocWhile* blocwhile;
   BlocFor* blocfor;
  // void* expr;
   void* opebin;

   void* TODO;
   Affectation* affect;
   Expression* valvar;
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
   AppelFonction* app_fonction;
   std::vector<Expression*>* liste_expr;
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
%type <structctrl> structure_de_controle
%type <blocif> bloc_if
%type <structctrl> bloc_boucle
%type <blocfor> bloc_for
%type <blocwhile> bloc_while
%type <TODO> suffixe_tab
%type <instrv> bloc
%type <TODO> contenu_bloc
%type <expression> expression
%type <TODO> declaration_droite
%type <declaration> declaration
%type <expression> expression_for
%type <affect> affectation
%type <valvar> valeur_variable
%type <fonc> fonction
%type <paramDeclar> parametre_declaration
%type <app_fonction> appel_fonction
%type <liste_expr> liste_expression
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

appel_fonction : IDENTIFIANT PAROUVR liste_expression PARFERM { /* $$->setIdentifiant($1); */ $$->setParametres($3); };

liste_expression : liste_expression VIRGULE expression { $$->push_back($3); }   // On push l'expression dans la liste d'expressions
                | expression {$$->push_back($1); };
                        // On a pas encore trouve de liste_expression. On en cree une et on y mets l'expression courante


type : INT32 { $$ = new string("INT32");}
		 | INT64 { $$ = new string("INT64");}
		 | CHAR { $$ = new string("CHAR");}
		 | VOID { $$ = new string("VOID");};

instrv : expression PV {$$ = $1;}
       | structure_de_controle {$$ = $1;}
       | bloc {$$ = $1;}
       | RETURN CROCHOUVR expression CROCHFERM PV {$$ = $3;}
       | PV;
       
instr : instrv declaration PV;

programme : programme fonction
          | programme declaration
          |;


prototype : type IDENTIFIANT PAROUVR parametres_declaration PARFERM;

parametres_declaration : type;



expression : NOT expression { $$ = new Not($2); }
           | expression AND expression { $$ = new OperateurAND($1, $3); }
           | expression OR expression { $$ = new OperateurOR($1, $3); }
           | expression INF expression { $$ = new OperateurInf($1, $3); }
           | expression SUP expression { $$ = new OperateurSup($1, $3); }
           | expression INFEGAL expression { $$ = new OperateurInfEgal($1, $3); }
           | expression SUPEGAL expression { $$ = new OperateurSupEgal($1, $3); }
           | expression EGALEGAL expression { $$ = new OperateurEgal($1, $3); }
           | expression DIFF expression { $$ = new OperateurDifferent($1, $3); }
           | expression PLUS expression { $$ = new OperateurPlus($1, $3); }
           | expression MOINS expression { $$ = new OperateurMoins($1, $3); }
           | expression MULT expression { $$ = new OperateurMultiplier($1, $3); }
           | expression DIV expression { $$ = new OperateurDivise($1, $3); }
           | expression DIVEUCL expression { $$ = new OperateurModulo($1, $3); }
           | PAROUVR expression PARFERM { $$ = $2; }
           | appel_fonction { $$ = new AppelFonction(); }
           | affectation { $$ = new Affectation(); }
           | IDENTIFIANT
           | valeur_variable { $$ = $1; };


           
valeur_variable : VAL
                | CARACTERE;


affectation : IDENTIFIANT EGAL_AFFECTATION expression { $$->setValeur($3); };



/**** QUENTIN ****/
structure_de_controle : bloc_if {$$ = $1;}
                      | bloc_boucle {$$ = $1;};

bloc_if : IF PAROUVR expression PARFERM instrv ELSE instrv {$$ = new BlocIf($3,$5,$7);}
        | IF PAROUVR expression PARFERM instrv { $$ = new BlocIf($3,$5);} ;

bloc_boucle : bloc_for {$$ = $1;}
            | bloc_while{$$ = $1;};

expression_for : expression { $$ = $1;}
               | {$$ = new Val(1);};

bloc_for : FOR PAROUVR expression_for PV expression_for PV expression_for PV PARFERM instrv { $$ = new BlocFor($3,$5,$7,$10);};

bloc_while : WHILE PAROUVR expression PARFERM instrv { $$ = new BlocWhile($3,$5);};
////*******/////



bloc : ACCOLOUVR contenu_bloc ACCOLFERM;
contenu_bloc : contenu_bloc instr 
             | instr;

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
