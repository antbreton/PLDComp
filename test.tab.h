/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_TEST_TAB_H_INCLUDED
# define YY_YY_TEST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIANT = 258,
    PAROUVR = 259,
    PARFERM = 260,
    INT32 = 261,
    INT64 = 262,
    CHAR = 263,
    VOID = 264,
    PV = 265,
    RETURN = 266,
    CROCHOUVR = 267,
    CROCHFERM = 268,
    ACCOLOUVR = 269,
    ACCOLFERM = 270,
    IF = 271,
    ELSE = 272,
    WHILE = 273,
    FOR = 274,
    VIRGULE = 275,
    EGALEGAL = 276,
    EGAL_AFFECTATION = 277,
    VAL = 278,
    CARACTERE = 279,
    AND = 280,
    OR = 281,
    INF = 282,
    SUP = 283,
    INFEGAL = 284,
    SUPEGAL = 285,
    DIFF = 286,
    PLUS = 287,
    MOINS = 288,
    MULT = 289,
    DIV = 290,
    DIVEUCL = 291,
    NOT = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "test.y" /* yacc.c:1909  */

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

#line 124 "test.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (int * resultat);

#endif /* !YY_YY_TEST_TAB_H_INCLUDED  */
