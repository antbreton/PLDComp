%{
#include <stdio.h>
#include <stdlib.h>
#include "test.tab.h"
%}
%option noyywrap
entier [0-9]+
string [a-zA-Z]+
texte "[a-zA-Z]+"
caractere '[a-zA-Z]{1}' 

%%
"#.*\n" { /* ignore */ }
[ \n\t]  	{ /* ignore */ }


{caractere}	{ return CARACTERE; }
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

{entier} 	{ yylval.val32 = atoi(yytext); return INT32; }

{string} 	{ return IDENTIFIANT; }

