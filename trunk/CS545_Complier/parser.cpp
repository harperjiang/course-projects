/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         pasparse
#define yylex           paslex
#define yyerror         paserror
#define yylval          paslval
#define yychar          paschar
#define yydebug         pasdebug
#define yynerrs         pasnerrs
#define yylloc          paslloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "pascal.yacc"

#include <stdio.h>
#include <vector>
#include "node.h"
#include "parser.h"

extern void error(const char* info);

void paserror(const char* s) {
  	char* buffer = new char[200];
  	sprintf(buffer,"Parse error: `%s' at line %d, col %d",s, paslloc.first_line, paslloc.first_column);
  	error(buffer);
	delete buffer;
}
    
extern int paslex();
extern BasicType* TYPE_REAL;
extern BasicType* TYPE_INT;
Program* parse_result;


/* Line 268 of yacc.c  */
#line 101 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
#line 43 "pascal.yacc"

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



/* Line 293 of yacc.c  */
#line 260 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 285 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    14,    21,    22,    25,    26,    37,    46,
      52,    56,    60,    64,    65,    69,    71,    78,    83,    88,
      92,    94,    98,   100,   104,   108,   111,   115,   119,   123,
     127,   131,   135,   138,   142,   146,   150,   154,   158,   162,
     164,   166,   168,   170,   172,   174,   178,   183,   188,   190,
     195,   197,   206,   208,   210,   214,   216,   218,   220,   222,
     224,   226
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,     3,    70,    19,    68,    20,    14,    53,
      54,    57,    17,    -1,    53,     6,    68,    16,    66,    14,
      -1,    -1,    54,    55,    -1,    -1,     4,    70,    19,    56,
      20,    16,    67,    53,    57,    14,    -1,     5,    70,    19,
      56,    20,    53,    57,    14,    -1,    56,    14,    68,    16,
      66,    -1,    68,    16,    66,    -1,    12,    58,    13,    -1,
      58,    14,    59,    -1,    -1,    65,    29,    61,    -1,    62,
      -1,     7,    61,     9,    59,     8,    59,    -1,     7,    61,
       9,    59,    -1,    10,    61,    11,    59,    -1,    12,    58,
      13,    -1,    49,    -1,    60,    15,    61,    -1,    61,    -1,
      61,    30,    61,    -1,    61,    31,    61,    -1,    31,    61,
      -1,    61,    32,    61,    -1,    61,    33,    61,    -1,    61,
      34,    61,    -1,    19,    61,    20,    -1,    61,    35,    61,
      -1,    61,    36,    61,    -1,    37,    61,    -1,    61,    38,
      61,    -1,    61,    39,    61,    -1,    61,    42,    61,    -1,
      61,    43,    61,    -1,    61,    40,    61,    -1,    61,    41,
      61,    -1,    62,    -1,    70,    -1,    71,    -1,    69,    -1,
      63,    -1,    64,    -1,    23,    19,    20,    -1,    24,    19,
      60,    20,    -1,    70,    19,    60,    20,    -1,    70,    -1,
      70,    21,    61,    22,    -1,    67,    -1,    25,    21,    72,
      18,    72,    22,    28,    67,    -1,    27,    -1,    26,    -1,
      68,    15,    70,    -1,    70,    -1,    47,    -1,    48,    -1,
      46,    -1,    72,    -1,    45,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    92,    92,    94,    95,    97,    98,   100,   101,   103,
     104,   106,   108,   109,   111,   112,   113,   114,   115,   116,
     117,   119,   120,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   143,   144,   146,   147,   149,   151,   152,
     154,   155,   157,   158,   160,   161,   163,   164,   166,   168,
     169,   170
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "FUNCTION", "PROCEDURE",
  "VAR", "IF", "ELSE", "THEN", "WHILE", "DO", "BGIN", "END", "SEMICOLON",
  "COMMA", "COLON", "DOT", "DOTDOT", "LP", "RP", "LSQ", "RSQ", "READ",
  "WRITE", "ARRAY", "TINT", "TREAL", "OF", "ASSIGN", "ADD", "SUB", "MUL",
  "DIV", "MOD", "AND", "OR", "NOT", "GT", "LT", "EQ", "NEQ", "GTE", "LTE",
  "INT", "REAL", "ID", "TRUE", "FALSE", "BREAK", "UMINUS", "$accept",
  "program", "declares", "subs", "sub", "params", "program_body", "stmts",
  "stmt", "exp_list", "exp", "call", "syscall", "usercall", "var", "type",
  "stdtype", "id_list", "boolexp", "id", "num", "int", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    69,    70,    71,
      71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    10,     6,     0,     2,     0,    10,     8,     5,
       3,     3,     3,     0,     3,     1,     6,     4,     4,     3,
       1,     3,     1,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     4,     4,     1,     4,
       1,     8,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    58,     0,     1,     0,     0,    55,     0,
       0,    54,     4,     6,     0,     0,     0,     0,     0,    13,
       5,     0,     0,     0,     0,     0,     2,     0,    53,    52,
       0,    50,     0,     0,    11,     0,     0,     3,     0,     0,
       0,     0,     0,    13,     0,     0,    20,    12,    15,    43,
      44,     0,    48,    61,     0,     0,     0,     0,     4,     0,
       0,     0,    60,    56,    57,     0,    39,    42,    40,    41,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     0,    25,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    45,     0,    22,    14,     0,     0,     0,     0,
       4,     0,    29,    17,    23,    24,    26,    27,    28,    30,
      31,    33,    34,    37,    38,    35,    36,    18,     0,    46,
      47,    49,     0,     9,     0,     8,     0,    21,     0,     0,
      16,    51,     7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    13,    15,    20,    38,    21,    25,    47,   103,
     104,    66,    49,    50,    51,    30,    31,    39,    67,    68,
      69,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -79
static const yytype_int16 yypact[] =
{
       6,     2,    53,   -79,    46,   -79,     2,    22,   -79,     2,
      66,   -79,   -79,    81,     2,    14,    13,     2,     2,   -79,
     -79,    84,    64,    85,    86,    33,   -79,    82,   -79,   -79,
      95,   -79,     2,     2,   -79,    74,    67,   -79,     0,    20,
      10,    69,    69,   -79,    91,    93,   -79,   -79,   -79,   -79,
     -79,    89,    -9,   -79,   101,     2,   105,    64,   -79,    69,
      69,    69,   -79,   -79,   -79,    98,   -79,   -79,   103,   -79,
     -79,   113,    37,   106,    69,    69,    69,    69,    67,    47,
      56,   -79,    21,   130,   -79,   173,    74,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      74,   -79,   -79,    23,   159,   159,    29,   145,   120,    64,
     -79,   111,   -79,   119,    62,    62,   -79,   -79,   -79,   173,
     173,   187,   187,   187,   187,   187,   187,   -79,    69,   -79,
     -79,   -79,   129,   -79,    21,   -79,    74,   159,    56,   144,
     -79,   -79,   -79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -54,   -79,   -79,   126,   -76,   131,   -75,   132,
     -20,   -34,   -79,   -79,   -79,   -50,   -78,     9,   -79,    -1,
     -79,   -33
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       4,    48,   110,    54,    82,     8,   111,    81,    11,     1,
      76,   113,    77,     8,    55,     7,    23,    24,    17,    18,
      56,    65,    71,    16,    55,   127,    19,    14,     9,    22,
      58,     8,     8,    19,    52,     9,    57,     9,   128,    83,
      84,    85,    10,   129,   128,   108,    34,    35,     3,   130,
     101,    35,    48,     5,     8,   105,   134,   107,   139,   133,
     141,   140,     9,   109,    79,     6,    48,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      12,    41,    28,    29,    42,    52,    43,    14,    59,    27,
      28,    29,    44,    45,    89,    90,    91,    44,    45,    52,
      60,    26,    48,    36,    32,    33,    61,    86,   137,    37,
      73,    53,    74,    53,    62,     3,    63,    64,    75,    78,
       3,    80,    76,    46,   100,   135,   102,   136,    87,    88,
      89,    90,    91,    92,    93,    52,    94,    95,    96,    97,
      98,    99,   132,    87,    88,    89,    90,    91,    92,    93,
     112,    94,    95,    96,    97,    98,    99,   138,   142,    40,
      87,    88,    89,    90,    91,    92,    93,   131,    94,    95,
      96,    97,    98,    99,    72,    87,    88,    89,    90,    91,
      92,    93,     0,    94,    95,    96,    97,    98,    99,    87,
      88,    89,    90,    91,    92,    93,     0,    94,    95,    96,
      97,    98,    99,    87,    88,    89,    90,    91,   106,     0,
       0,    94,    95,    96,    97,    98,    99,    87,    88,    89,
      90,    91
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-79))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    35,    80,    36,    58,     6,    82,    57,     9,     3,
      19,    86,    21,    14,    14,     6,    17,    18,     4,     5,
      20,    41,    42,    14,    14,   100,    12,     6,    15,    16,
      20,    32,    33,    12,    35,    15,    16,    15,    15,    59,
      60,    61,    20,    20,    15,    78,    13,    14,    46,    20,
      13,    14,    86,     0,    55,    75,   110,    77,   134,   109,
     138,   136,    15,    16,    55,    19,   100,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      14,     7,    26,    27,    10,    86,    12,     6,    19,    25,
      26,    27,    23,    24,    32,    33,    34,    23,    24,   100,
      31,    17,   136,    21,    19,    19,    37,     9,   128,    14,
      19,    44,    19,    44,    45,    46,    47,    48,    29,    18,
      46,    16,    19,    49,    11,    14,    20,     8,    30,    31,
      32,    33,    34,    35,    36,   136,    38,    39,    40,    41,
      42,    43,    22,    30,    31,    32,    33,    34,    35,    36,
      20,    38,    39,    40,    41,    42,    43,    28,    14,    33,
      30,    31,    32,    33,    34,    35,    36,    22,    38,    39,
      40,    41,    42,    43,    43,    30,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    30,
      31,    32,    33,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    30,    31,    32,    33,    34,    76,    -1,
      -1,    38,    39,    40,    41,    42,    43,    30,    31,    32,
      33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    52,    46,    70,     0,    19,    68,    70,    15,
      20,    70,    14,    53,     6,    54,    68,     4,     5,    12,
      55,    57,    16,    70,    70,    58,    17,    25,    26,    27,
      66,    67,    19,    19,    13,    14,    21,    14,    56,    68,
      56,     7,    10,    12,    23,    24,    49,    59,    62,    63,
      64,    65,    70,    44,    72,    14,    20,    16,    20,    19,
      31,    37,    45,    47,    48,    61,    62,    69,    70,    71,
      72,    61,    58,    19,    19,    29,    19,    21,    18,    68,
      16,    66,    53,    61,    61,    61,     9,    30,    31,    32,
      33,    34,    35,    36,    38,    39,    40,    41,    42,    43,
      11,    13,    20,    60,    61,    61,    60,    61,    72,    16,
      67,    57,    20,    59,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    59,    15,    20,
      20,    22,    22,    66,    53,    14,     8,    61,    28,    57,
      59,    67,    14
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 92 "pascal.yacc"
    {parse_result = new Program((yyvsp[(2) - (10)].id),(yyvsp[(4) - (10)].id_list),(yyvsp[(7) - (10)].declares),(yyvsp[(8) - (10)].subs),(yyvsp[(9) - (10)].program_body));}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 94 "pascal.yacc"
    {for(std::vector<Identifier*>::iterator ite = (yyvsp[(3) - (6)].id_list)->begin();ite != (yyvsp[(3) - (6)].id_list)->end();ite++) {Declare* dec = new Declare((yyvsp[(5) - (6)].type),*ite); (yyvsp[(1) - (6)].declares)->push_back(dec); (yyval.declares) = (yyvsp[(1) - (6)].declares);}}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 95 "pascal.yacc"
    {(yyval.declares) = new std::vector<Declare*>(); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 97 "pascal.yacc"
    {(yyval.subs) = (yyvsp[(1) - (2)].subs); (yyval.subs)->push_back((yyvsp[(2) - (2)].sub));}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 98 "pascal.yacc"
    {(yyval.subs) = new std::vector<Subprogram*>();}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 100 "pascal.yacc"
    {(yyval.sub) = new Function((yyvsp[(2) - (10)].id), (yyvsp[(4) - (10)].params), (yyvsp[(7) - (10)].type), (yyvsp[(8) - (10)].declares), (yyvsp[(9) - (10)].program_body));}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 101 "pascal.yacc"
    {(yyval.sub) = new Procedure((yyvsp[(2) - (8)].id), (yyvsp[(4) - (8)].params), (yyvsp[(6) - (8)].declares), (yyvsp[(7) - (8)].program_body));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 103 "pascal.yacc"
    {(yyval.params) = (yyvsp[(1) - (5)].params); for(std::vector<Identifier*>::iterator ite = (yyvsp[(3) - (5)].id_list)->begin();ite!=(yyvsp[(3) - (5)].id_list)->end();ite++) {(yyval.params)->push_back(new Param((yyvsp[(5) - (5)].type),*ite));}}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 104 "pascal.yacc"
    {(yyval.params) = new std::vector<Param*>();for(std::vector<Identifier*>::iterator ite = (yyvsp[(1) - (3)].id_list)->begin();ite!=(yyvsp[(1) - (3)].id_list)->end();ite++){(yyval.params)->push_back(new Param((yyvsp[(3) - (3)].type),*ite));}}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 106 "pascal.yacc"
    {(yyval.program_body) = new StatementBlock((yyvsp[(2) - (3)].stmts));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 108 "pascal.yacc"
    {(yyval.stmts) = (yyvsp[(1) - (3)].stmts); (yyval.stmts)->push_back((yyvsp[(3) - (3)].stmt));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 109 "pascal.yacc"
    {(yyval.stmts) = new std::vector<Statement*>();}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 111 "pascal.yacc"
    {(yyval.stmt) = new AssignStatement((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].exp));}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 112 "pascal.yacc"
    {(yyval.stmt) = new CallStatement((yyvsp[(1) - (1)].call));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 113 "pascal.yacc"
    {(yyval.stmt) = new IfStatement((yyvsp[(2) - (6)].exp), (yyvsp[(4) - (6)].stmt), (yyvsp[(6) - (6)].stmt));}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 114 "pascal.yacc"
    {(yyval.stmt) = new IfStatement((yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].stmt), NULL);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 115 "pascal.yacc"
    {(yyval.stmt) = new WhileStatement((yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].stmt));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 116 "pascal.yacc"
    {(yyval.stmt) = new StatementBlock((yyvsp[(2) - (3)].stmts));}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 117 "pascal.yacc"
    {(yyval.stmt) = new BreakStatement();}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 119 "pascal.yacc"
    {(yyval.exp_list) = (yyvsp[(1) - (3)].exp_list); (yyvsp[(1) - (3)].exp_list)->push_back((yyvsp[(3) - (3)].exp));}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 120 "pascal.yacc"
    {(yyval.exp_list) = new std::vector<Expression*>();}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 122 "pascal.yacc"
    {(yyval.exp) = new ArithExpression((yyvsp[(1) - (3)].exp),_ADD, (yyvsp[(3) - (3)].exp));}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 123 "pascal.yacc"
    {(yyval.exp) = new ArithExpression((yyvsp[(1) - (3)].exp),_SUB, (yyvsp[(3) - (3)].exp));}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 124 "pascal.yacc"
    {(yyval.exp) = new ArithExpression(NULL, _SUB, (yyvsp[(2) - (2)].exp));}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 125 "pascal.yacc"
    {(yyval.exp) = new ArithExpression((yyvsp[(1) - (3)].exp),_MUL, (yyvsp[(3) - (3)].exp));}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 126 "pascal.yacc"
    {(yyval.exp) = new ArithExpression((yyvsp[(1) - (3)].exp),_DIV, (yyvsp[(3) - (3)].exp));}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 127 "pascal.yacc"
    {(yyval.exp) = new ArithExpression((yyvsp[(1) - (3)].exp),_MOD, (yyvsp[(3) - (3)].exp));}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 128 "pascal.yacc"
    {(yyval.exp) = (yyvsp[(2) - (3)].exp);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 129 "pascal.yacc"
    {(yyval.exp) = new LogicExpression((yyvsp[(1) - (3)].exp),_AND, (yyvsp[(3) - (3)].exp));}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 130 "pascal.yacc"
    {(yyval.exp) = new LogicExpression((yyvsp[(1) - (3)].exp),_OR, (yyvsp[(3) - (3)].exp));}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 131 "pascal.yacc"
    {(yyval.exp) = new LogicExpression(NULL,_NOT, (yyvsp[(2) - (2)].exp));}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 132 "pascal.yacc"
    {(yyval.exp) = new RelExpression((yyvsp[(1) - (3)].exp),_GT, (yyvsp[(3) - (3)].exp));}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 133 "pascal.yacc"
    {(yyval.exp) = new RelExpression((yyvsp[(1) - (3)].exp),_LT, (yyvsp[(3) - (3)].exp));}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 134 "pascal.yacc"
    {(yyval.exp) = new RelExpression((yyvsp[(1) - (3)].exp),_GTE, (yyvsp[(3) - (3)].exp));}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 135 "pascal.yacc"
    {(yyval.exp) = new RelExpression((yyvsp[(1) - (3)].exp),_LTE, (yyvsp[(3) - (3)].exp));}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 136 "pascal.yacc"
    {(yyval.exp) = new RelExpression((yyvsp[(1) - (3)].exp),_EQ, (yyvsp[(3) - (3)].exp));}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 137 "pascal.yacc"
    {(yyval.exp) = new RelExpression((yyvsp[(1) - (3)].exp),_NEQ, (yyvsp[(3) - (3)].exp));}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 138 "pascal.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].call);}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 139 "pascal.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].id);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 140 "pascal.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].num);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 141 "pascal.yacc"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 143 "pascal.yacc"
    {(yyval.call) = (yyvsp[(1) - (1)].call);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 144 "pascal.yacc"
    {(yyval.call) = (yyvsp[(1) - (1)].call);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 146 "pascal.yacc"
    {(yyval.call) = new CallExpression(new Identifier("read"),NULL);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 147 "pascal.yacc"
    {(yyval.call) = new CallExpression(new Identifier("write"),(yyvsp[(3) - (4)].exp_list));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 149 "pascal.yacc"
    {(yyval.call) = new CallExpression((yyvsp[(1) - (4)].id),(yyvsp[(3) - (4)].exp_list));}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 151 "pascal.yacc"
    {(yyval.var) = (yyvsp[(1) - (1)].id);}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 152 "pascal.yacc"
    {(yyval.var) = new ArrayElement((yyvsp[(1) - (4)].id),(yyvsp[(3) - (4)].exp));}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 154 "pascal.yacc"
    {(yyval.type) = (yyvsp[(1) - (1)].type);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 155 "pascal.yacc"
    {(yyval.type) = new ArrayType((yyvsp[(8) - (8)].type),(yyvsp[(3) - (8)].inte),(yyvsp[(5) - (8)].inte));}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 157 "pascal.yacc"
    {(yyval.type) = TYPE_REAL;}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 158 "pascal.yacc"
    {(yyval.type) = TYPE_INT;}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 160 "pascal.yacc"
    {(yyval.id_list) = (yyvsp[(1) - (3)].id_list); (yyval.id_list)->push_back((yyvsp[(3) - (3)].id));}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 161 "pascal.yacc"
    {(yyval.id_list) = new std::vector<Identifier*>();(yyval.id_list)->push_back((yyvsp[(1) - (1)].id));}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 163 "pascal.yacc"
    {(yyval.exp) = new BoolConstant(true);}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 164 "pascal.yacc"
    {(yyval.exp) = new BoolConstant(false);}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 166 "pascal.yacc"
    {(yyval.id) = new Identifier(paslval.tokenval);}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 168 "pascal.yacc"
    {(yyval.num) = new IntConstant((yyvsp[(1) - (1)].inte));}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 169 "pascal.yacc"
    {(yyval.num) = new RealConstant(atof(paslval.tokenval));}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 170 "pascal.yacc"
    {(yyval.inte) = atoi(paslval.tokenval);}
    break;



/* Line 1806 of yacc.c  */
#line 2113 "parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 171 "pascal.yacc"

