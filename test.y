%{
#include <stdio.h>
#include <stdint.h>
#include "General.h"
#include "Expression.h"
#include "Fonction.h"
#include "Structure.h"
#include "IR/IR.h"
#include <iostream>

#define YYDEBUG 1

void yyerror(Programme** , const char *);
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
   std::vector<Variable*>* declaration;
   Variable* variable;
   Fonction* fonc;
   ParamDeclar* paramDeclar;
   std::vector<Identifiant*>* listeIdentifiants;
   AppelFonction* app_fonction;
   std::vector<Expression*>* liste_expr;
   std::vector<Variable*>* parametres_declaration;
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
%type <instr> instr
%type <prog> programme
%type <fonc> prototype 
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
%type <variable> declaration_droite
%type <declaration> declaration
%type <expression> expression_for
%type <affect> affectation
%type <valvar> valeur_variable
%type <fonc> fonction
%type <declaration> parametre_declaration
%type <app_fonction> appel_fonction
%type <liste_expr> liste_expression
%type <declaration> separateur_decl
%type <variable> declaration_param_fonction


//%left IDENTIFIANT PAROUVR PARFERM INT32 INT64 CHAR VOID
%parse-param { Programme ** prog }

%%

/*** ANTOINE *****/
//déclaration Variables

axiome : programme { *prog= $1;};

suffixe_tab : CROCHOUVR valeur_variable CROCHFERM {$$ = $2;}
            | {$$ = NULL;};

declaration_droite : type IDENTIFIANT suffixe_tab { $$ = new Variable(*$1,*$2);};

separateur_decl : separateur_decl VIRGULE IDENTIFIANT { $$->push_back(new Variable(*$3));}	// A chaque appel on push l'identifiant courant dans la liste
                | /* vide */ { $$ = new std::vector<Variable*>();};			// On crée la liste d'identifiant quand on est sur vide

declaration : declaration_droite separateur_decl PV { $$ = $2; $$->push_back($1); for(int i=0; i<$$->size();i++) {(*$$)[i]->setType($1->getType());}} // On crée un vecteur de variables qui auront toutes le type de la première déclaration
            | declaration_droite separateur_decl EGAL_AFFECTATION expression PV { $$ = $2; $$->push_back($1); for(int i=0; i<$$->size();i++) {(*$$)[i]->setType($1->getType());} if($$->size()==1) {(*$$)[0]->setValeur($4);} else {(*$$)[$$->size()-2]->setValeur($4);}  } ; /* on recupere la liste dans $2 et on rajoute le premier $1 en dernier. Ensuite on recupere le type de $1 et on l'affecte a tout ceux de la liste. Ensuite on affecte la valeur au dernier de la liste(donc l'avant dernier du vecteur) ou bien a la seul variable*/

//fonction
fonction : prototype PV {$$ = $1;}
         | prototype bloc {$$=$1; $$->RajouterBloc($2);};

// Instancie la fonction avec son type, son ID et en lui ajoutant sa liste de variable. 
prototype : type IDENTIFIANT PAROUVR parametre_declaration PARFERM {$$ = new Fonction (*$1, *$2, $4);};

declaration_param_fonction : type IDENTIFIANT suffixe_tab { $$ = new Variable(*$1,*$2); }; /* TODO gerer les tabs */

// Crée une liste de variable
parametre_declaration : parametre_declaration VIRGULE declaration_param_fonction {$$->push_back($3);} // on ajoute la variable
                      | parametre_declaration declaration_param_fonction { $$->push_back($2);} // on ajoute la variable correspondante
                      | {$$ = new std::vector<Variable*>();}; // on crée le vecteur de variable

appel_fonction : IDENTIFIANT PAROUVR liste_expression PARFERM { $$ = new AppelFonction(); $$->setIdentifiant(new Identifiant($1)); $$->setParametres($3); };

liste_expression : liste_expression VIRGULE expression { $$->push_back($3); }   // On push l'expression dans la liste d'expressions
                | expression {$$ = new std::vector<Expression*>(); $$->push_back($1); };
                        // On a pas encore trouve de liste_expression. On en cree une et on y mets l'expression courante

type : INT32 { $$ = new string("INT32");}
		 | INT64 { $$ = new string("INT64");}
		 | CHAR { $$ = new string("CHAR");}
		 | VOID { $$ = new string("VOID");};

instr : expression PV {$$ = $1; $1->setIsInline(1); $1->ancetre = $$;}
       | structure_de_controle {$$ = $1; $1->ancetre = $$;}
       | bloc {$$ = $1; $1->ancetre = $$;}
       | RETURN expression PV {$$ = new RetourExpr($2); $1->ancetre = $$;}
       | RETURN PV { $$ = new RetourExpr(); $1->ancetre = $$;}
       | PV;
       


programme : programme fonction {$$=$1; $$->ajouterFonction($2);}
          | programme declaration {$$=$1; $$->ajouterListeVariable($2);}
          |{ $$ = new Programme();};

expression : NOT expression { $$ = new Not($2); $1->ancetre = $$;}
           | expression AND expression { $$ = new OperateurAND($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression OR expression { $$ = new OperateurOR($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression INF expression { $$ = new OperateurInf($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression SUP expression { $$ = new OperateurSup($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression INFEGAL expression { $$ = new OperateurInfEgal($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression SUPEGAL expression { $$ = new OperateurSupEgal($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression EGALEGAL expression { $$ = new OperateurEgal($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression DIFF expression { $$ = new OperateurDifferent($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression PLUS expression { $$ = new OperateurPlus($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression MOINS expression { $$ = new OperateurMoins($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression MULT expression { $$ = new OperateurMultiplier($1, $3); $1->ancetre = $$; $3->ancetre = $$; }
           | expression DIV expression { $$ = new OperateurDivise($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | expression DIVEUCL expression { $$ = new OperateurModulo($1, $3); $1->ancetre = $$; $3->ancetre = $$;}
           | PAROUVR expression PARFERM { $$ = $2; $2->ancetre = $$;}
           | appel_fonction { $$ = $1; $1->ancetre = $$;}
           | affectation { $$ = $1; $1->ancetre = $$;}
           | IDENTIFIANT { Identifiant* id= new Identifiant(yylval.identifiant); $$ =id; if(!id->checkExists()) 	cout << endl<< "Erreur de synthaxe : '"<< yylval.identifiant<< "' est inconnue dans ce scope" << endl; 
} // Ici on vérifie que l'identifiant existe bien
           | valeur_variable { $$ = $1; $1->ancetre = $$;};


           
valeur_variable : VAL
                | CARACTERE ;


affectation : IDENTIFIANT EGAL_AFFECTATION expression { $$ = new Affectation(); $$->setValeur($3); $$->setIdentifiant(new Identifiant($1));};



/**** QUENTIN ****/
structure_de_controle : bloc_if {$$ = $1;}
                      | bloc_boucle {$$ = $1;};
                      
// Dans ce cas, nous devons traiter le cas ou l'instruction est elle même un bloc et lui désigné le bloc courant comme ancêtre
bloc_if : IF PAROUVR expression PARFERM instr ELSE instr {$$ = new BlocIf($3,$5,$7);}
        | IF PAROUVR expression PARFERM instr { $$ = new BlocIf($3,$5);} ;

bloc_boucle : bloc_for {$$ = $1;}
            | bloc_while {$$ = $1;};

expression_for : expression { $$ = $1;}
               | {$$ = new Val(1);};

bloc_for : FOR PAROUVR expression_for PV expression_for PV expression_for PARFERM instr { $$ = new BlocFor($3,$5,$7,$9);};

bloc_while : WHILE PAROUVR expression PARFERM instr { $$ = new BlocWhile($3,$5);};
////*******/////


bloc : ACCOLOUVR contenu_bloc ACCOLFERM {$$ = $2;};

contenu_bloc :contenu_bloc declaration {$$->ajouterListeVariable($2);} // On ajoute la liste des variables résultantes de la déclaration dans le bloc
							// Dans ce cas, nous devons traiter le cas ou l'instruction est elle même un bloc et lui désigné le bloc courant comme ancêtre
						 | contenu_bloc instr { $$->AjouterInstr($2); $2->ancetre = $$;}
						 | {$$ = new Bloc();};
%%
void yyerror(Programme ** res, const char * msg) {
   printf("Syntax error : %s\n",msg);
}

