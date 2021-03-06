%{
#include <stdio.h>
#include <stdlib.h>
#include "Expression.h"
#include "Structure.h"
#include "Fonction.h"
#include "test.tab.h"


%}
%option noyywrap
entier [0-9]+
string [a-zA-Z0-9_]+
texte "[a-zA-Z]+"
caractere '([\x20-\x7F]|\\n|\\t)'

%%
"#.*\n" { /* ignore */ }
[ \n\t]  	{ /* ignore */ }


{caractere}	{ if( strlen(yytext)==3){yylval.cval = new Caractere(yytext[1]);} else if (yytext[2]=='n'){yylval.cval = new Caractere(10);}  else if (yytext[2]=='t'){yylval.cval = new Caractere(9);} return CARACTERE; }
"("      	{ return PAROUVR; }
")"      	{ return PARFERM; }
"int32_t"	{ return INT32;}
"int64_t"	{ return INT64;}
"char"   	{ return CHAR;}
"void"   	{ return VOID;}
"if" 		{ return IF;}
"else"		{ return ELSE;}
"{"         { return ACCOLOUVR;}
"}"         { return ACCOLFERM;}
"for"       { return FOR;}
";"         { return PV;}
"return"    { return RETURN;}
"while"     { return WHILE;}
","         { return VIRGULE;}
"["         { return CROCHOUVR;}
"]"         { return CROCHOUVR;}
"="         { return EGAL_AFFECTATION;}
"&&"        { return AND;}
"||"        { return OR;}
"<"         { return INF;}
">"         { return SUP;}
"<="        { return INFEGAL;}
">="        { return SUPEGAL;}
"=="        { return EGALEGAL;} 
"!="        { return DIFF;}
"+"         { return PLUS;}
"-"         { return MOINS;}
"*"         { return MULT;}
"/"         { return DIV;}
"%"         { return DIVEUCL;}
"!"         { return NOT;}  

{entier} 	{ yylval.val32 = new Val(atoi(yytext)); return VAL; }

{string} 	{ yylval.identifiant = new string(yytext); return IDENTIFIANT; }

