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
     BEGIN = 267,
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
     ARRAY = 278,
     TINT = 279,
     TREAL = 280,
     OF = 281,
     ASSIGN = 282,
     ADD = 283,
     SUB = 284,
     MUL = 285,
     DIV = 286,
     MOD = 287,
     AND = 288,
     OR = 289,
     NOT = 290,
     GT = 291,
     LT = 292,
     EQ = 293,
     NEQ = 294,
     GTE = 295,
     LTE = 296,
     INT = 297,
     REAL = 298,
     ID = 299
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
#define BEGIN 267
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
#define ARRAY 278
#define TINT 279
#define TREAL 280
#define OF 281
#define ASSIGN 282
#define ADD 283
#define SUB 284
#define MUL 285
#define DIV 286
#define MOD 287
#define AND 288
#define OR 289
#define NOT 290
#define GT 291
#define LT 292
#define EQ 293
#define NEQ 294
#define GTE 295
#define LTE 296
#define INT 297
#define REAL 298
#define ID 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE paslval;


