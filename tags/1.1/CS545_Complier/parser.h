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
     FOR = 269,
     TO = 270,
     SEMICOLON = 271,
     COMMA = 272,
     COLON = 273,
     DOT = 274,
     DOTDOT = 275,
     LP = 276,
     RP = 277,
     LSQ = 278,
     RSQ = 279,
     READ = 280,
     WRITE = 281,
     ARRAY = 282,
     TINT = 283,
     TREAL = 284,
     OF = 285,
     ASSIGN = 286,
     ADD = 287,
     SUB = 288,
     MUL = 289,
     DIV = 290,
     MOD = 291,
     AND = 292,
     OR = 293,
     NOT = 294,
     GT = 295,
     LT = 296,
     EQ = 297,
     NEQ = 298,
     GTE = 299,
     LTE = 300,
     INT = 301,
     REAL = 302,
     ID = 303,
     TRUE = 304,
     FALSE = 305,
     BREAK = 306,
     UMINUS = 307
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
#define FOR 269
#define TO 270
#define SEMICOLON 271
#define COMMA 272
#define COLON 273
#define DOT 274
#define DOTDOT 275
#define LP 276
#define RP 277
#define LSQ 278
#define RSQ 279
#define READ 280
#define WRITE 281
#define ARRAY 282
#define TINT 283
#define TREAL 284
#define OF 285
#define ASSIGN 286
#define ADD 287
#define SUB 288
#define MUL 289
#define DIV 290
#define MOD 291
#define AND 292
#define OR 293
#define NOT 294
#define GT 295
#define LT 296
#define EQ 297
#define NEQ 298
#define GTE 299
#define LTE 300
#define INT 301
#define REAL 302
#define ID 303
#define TRUE 304
#define FALSE 305
#define BREAK 306
#define UMINUS 307




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
#line 177 "parser.h"
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

