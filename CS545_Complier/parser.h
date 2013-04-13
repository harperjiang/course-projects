/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     FUNCTION = 259,
     PROCEDURE = 260,
     VAR = 261,
     IF = 262,
     ELSE = 263,
     THEN = 264,
     WHILE = 265,
     DO = 266,
     BGIN = 267,
     END = 268,
     SEMICOLON = 269,
     COMMA = 270,
     COLON = 271,
     DOT = 272,
     DOTDOT = 273,
     LP = 274,
     RP = 275,
     LSQ = 276,
     RSQ = 277,
     READ = 278,
     WRITE = 279,
     ARRAY = 280,
     TINT = 281,
     TREAL = 282,
     OF = 283,
     ASSIGN = 284,
     ADD = 285,
     SUB = 286,
     MUL = 287,
     DIV = 288,
     MOD = 289,
     AND = 290,
     OR = 291,
     NOT = 292,
     GT = 293,
     LT = 294,
     EQ = 295,
     NEQ = 296,
     GTE = 297,
     LTE = 298,
     INT = 299,
     REAL = 300,
     ID = 301,
     TRUE = 302,
     FALSE = 303,
     BREAK = 304,
     UMINUS = 305
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define FUNCTION 259
#define PROCEDURE 260
#define VAR 261
#define IF 262
#define ELSE 263
#define THEN 264
#define WHILE 265
#define DO 266
#define BGIN 267
#define END 268
#define SEMICOLON 269
#define COMMA 270
#define COLON 271
#define DOT 272
#define DOTDOT 273
#define LP 274
#define RP 275
#define LSQ 276
#define RSQ 277
#define READ 278
#define WRITE 279
#define ARRAY 280
#define TINT 281
#define TREAL 282
#define OF 283
#define ASSIGN 284
#define ADD 285
#define SUB 286
#define MUL 287
#define DIV 288
#define MOD 289
#define AND 290
#define OR 291
#define NOT 292
#define GT 293
#define LT 294
#define EQ 295
#define NEQ 296
#define GTE 297
#define LTE 298
#define INT 299
#define REAL 300
#define ID 301
#define TRUE 302
#define FALSE 303
#define BREAK 304
#define UMINUS 305




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 49 "pascal.yacc"

	char* tokenval;
	Program* program;
	std::vector<Declare*>* declares;
	std::vector<Subprogram*>* subs;
	Subprogram* sub;
	std::vector<Param*>* params;
	StatementBlock* program_body;
	std::vector<Statement*>* stmts;
	Statement* stmt;
	std::vector<Expression*>* exp_list;
	Expression* exp;
	CallExpression* call;
	Variable* var;
	Type* type;
	std::vector<Identifier*>* id_list;			
	Identifier* id;
	NumConstant* num;
	int inte;



/* Line 2068 of yacc.c  */
#line 173 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE paslval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE paslloc;

