%{
#include <stdio.h>
#include <stdint.h>
#include "General.h"
#include "Expression.h"
#include "Fonction.h"
#include "Structure.h"
#define YYDEBUG 1

void yyerror(int *, const char *);
int yylex(void);
%}
%union {
   Val* val32;
   Val* val64;
	 string* identifiant;
   string* type;
   RetourExpr* retour;//return reservé
   //void* proto;
   Instruction* instr;
   InstructionV* instrv;
   Programme* prog;
 //  void* dirprepro;
   void* blocboucle;
   StructureControle* structctrl;
   BlocIf* blocif;
   BlocWhile* blocwhile;
   BlocFor* blocfor;
  // void* expr;
   void* opebin;
   Bloc* bloc;
   void* TODO;
   Affectation* affect;
   Val* valvar;
   int* inutile;
   Not *non;
   Val* valeur;
   Caractere* cval;
   Expression* expression;
   Declaration* declaration;
   Fonction* fonc;
   Prototype* proto;
   ParamDeclar* paramDeclar;
   std::vector<Identifiant*>* listeIdentifiants;
   AppelFonction* app_fonction;
   std::vector<Expression*>* liste_expr;
   std::vector<Declaration*>* parametres_declaration;
}

/*
%token PLUS MOINS DIV OPEN CLOSE MUL
%token <ival> ENTIER

%type <ival> expr
*/



%token <identifiant> IDENTIFIANT
%token PAROUVR PARFERM
%token <val32> INT32
%token <val64> INT64 
%token <cval> CHAR 
%token VOID
%token PV                   // ;
%token <retour> RETURN
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
%type <instr> instr
%type <prog> programme
%type <proto> prototype 
//%type <dirprepro> dirpreprocesseur
%type <prog> axiome
%type <structctrl> structure_de_controle
%type <blocif> bloc_if
%type <structctrl> bloc_boucle
%type <blocfor> bloc_for
%type <blocwhile> bloc_while
%type <valvar> suffixe_tab
%type <bloc> bloc
%type <bloc> contenu_bloc
%type <expression> expression
%type <declaration> declaration_droite
%type <declaration> declaration
%type <expression> expression_for
%type <affect> affectation
%type <valvar> valeur_variable
%type <fonc> fonction
%type <parametres_declaration> parametre_declaration
%type <app_fonction> appel_fonction
%type <liste_expr> liste_expression
%type <listeIdentifiants> separateur_decl
%type <declaration> declaration_param_fonction


//%left IDENTIFIANT PAROUVR PARFERM INT32 INT64 CHAR VOID
%parse-param { int * resultat }

%%

/*** ANTOINE *****/
//déclaration Variables

axiome : programme { $$->Afficher();};

suffixe_tab : CROCHOUVR valeur_variable CROCHFERM {$$ = $2;}
            | {$$ = NULL;};

declaration_droite : type IDENTIFIANT suffixe_tab { $$ = new Declaration(*$1,$3,new Identifiant($2));};

separateur_decl : separateur_decl VIRGULE IDENTIFIANT { $$->push_back(new Identifiant($3));}	// A chaque appel on push l'identifiant courant dans la liste
                | /* vide */ { $$ = new std::vector<Identifiant*>();};			// On crée la liste d'identifiant quand on est sur vide

declaration : declaration_droite separateur_decl { $$ = $1; $$->addAllIdentifiants($2);}
            | declaration_droite separateur_decl EGAL_AFFECTATION expression { $$ = $1; $$->addAllIdentifiants($2); } ; /* TODO gerer l'affectation */

//fonction
fonction : prototype PV {new Fonction($1);}
         | prototype bloc {$$ = new Fonction($1,$2);};

declaration_param_fonction : type IDENTIFIANT suffixe_tab { $$ = new Declaration(*$1,$3,new Identifiant($2));}
                            | type IDENTIFIANT EGAL_AFFECTATION expression;

parametre_declaration : parametre_declaration VIRGULE declaration_param_fonction {$$->push_back($3);}
                      | declaration_param_fonction {$$ = new std::vector<Declaration*>(); $$->push_back($1);}
                      | {$$ = new std::vector<Declaration*>();};

prototype : type IDENTIFIANT PAROUVR parametre_declaration PARFERM {$$ = new Prototype($1,$4,new Identifiant($2));};
         // A REVOIR | type IDENTIFIANT PAROUVR VOID PARFERM {$$ = new Prototype($1,NULL,new Identifiant($2));};


appel_fonction : IDENTIFIANT PAROUVR liste_expression PARFERM { $$->setIdentifiant(new Identifiant($1)); $$->setParametres($3); };

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
       | RETURN expression PV {$$ = new RetourExpr($2);}
       | PV;
       
instr : instrv {$$ = $1;}
      | declaration PV {$$ = $1;};

programme : programme fonction {$$=$1; $$->ajouterInstruction($2);}
          | programme declaration {$$=$1; $$->ajouterInstruction($2);}
          |{ $$ = new Programme();};

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
           | IDENTIFIANT { $$ = new Identifiant(yylval.identifiant); }
           | valeur_variable { $$ = $1; };


           
valeur_variable : VAL
                | CARACTERE ;


affectation : IDENTIFIANT EGAL_AFFECTATION expression { $$->setValeur($3); $$->setIdentifiant(new Identifiant($1));};



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



bloc : ACCOLOUVR contenu_bloc ACCOLFERM {$$ = $2;};
contenu_bloc : contenu_bloc instr {$$->AjouterInstr($2);}
             | instr {$$ = new Bloc($1);};

%%
void yyerror(int * res, const char * msg) {
   printf("Syntax error : %s\n",msg);
}

int main(void) {
yydebug =1;
   int res = 0;
   yyparse(&res);
   printf("Résutlat : %d\n",res);
   return 0;
}
