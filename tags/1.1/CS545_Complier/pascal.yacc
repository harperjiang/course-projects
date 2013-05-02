%{
#include <stdio.h>
#include <vector>
#include <tr1/memory>
#include "node.h"
#include "parser.h"
#define _CALL_READ 1
#define _CALL_WRITE 2

extern void error(const char* info);


void paserror(const char* s) {
  	char* buffer = new char[200];
  	sprintf(buffer,"Parse error: `%s' at line %d, col %d",s, paslloc.first_line, paslloc.first_column);
  	error(buffer);
	delete buffer;
}
    
extern int paslex();
extern Type* TYPE_REAL;
extern Type* TYPE_INT;

Program* parse_result;
%}

%token PROGRAM FUNCTION PROCEDURE
%token VAR IF ELSE THEN WHILE DO BGIN END FOR TO
%token SEMICOLON COMMA COLON DOT DOTDOT
%token LP RP LSQ RSQ

%token READ WRITE
%token ARRAY TINT TREAL OF
%token ASSIGN ADD SUB MUL DIV MOD AND OR NOT GT LT EQ NEQ GTE LTE
%token INT REAL ID
%token TRUE FALSE BREAK

%left THEN
%left ELSE
%left OR
%left AND
%right NOT
%left EQ NEQ
%left GT LT GTE LTE 
%left ADD SUB 
%left MUL DIV MOD
%right UMINUS

%union {
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
}

%locations
%error-verbose

%type<program> program
%type<declares> declares
%type<subs> subs
%type<sub> sub
%type<params> params
%type<program_body> program_body
%type<stmts> stmts
%type<stmt> stmt
%type<exp_list> exp_list
%type<exp> exp
%type<exp> boolexp
%type<call> call
%type<call> syscall
%type<call> usercall
%type<var> var
%type<type> type
%type<type> stdtype
%type<id_list> id_list
%type<id> id
%type<num> num
%type<inte> int

%start program

%%
program		:	PROGRAM id LP id_list RP SEMICOLON declares subs program_body DOT 	{parse_result = new Program($2,$4,$7,$8,$9);};

declares	: 	declares VAR id_list COLON type SEMICOLON	{for(std::vector<Identifier*>::iterator ite = $3->begin();ite != $3->end();ite++) {Declare* dec = new Declare($5,*ite); $1->push_back(dec); $$ = $1;}}
			|												{$$ = new std::vector<Declare*>(); };
			
subs		:	subs sub 			{$$ = $1; $$->push_back($2);}
			|			 			{$$ = new std::vector<Subprogram*>();};

sub			:	FUNCTION id LP params RP COLON stdtype SEMICOLON declares subs program_body SEMICOLON		{$$ = new Function($2, $4, $7, $9, $10, $11);}
			|	PROCEDURE id LP params RP SEMICOLON declares subs program_body SEMICOLON					{$$ = new Procedure($2, $4, $7, $8, $9);};
			|	PROCEDURE id SEMICOLON declares subs program_body SEMICOLON									{$$ = new Procedure($2, new std::vector<Param*>(), $4, $5, $6);}

params		:	params SEMICOLON id_list COLON type		{$$ = $1; for(std::vector<Identifier*>::iterator ite = $3->begin();ite!=$3->end();ite++) {$$->push_back(new Param($5,*ite));}}
			|	id_list COLON type 						{$$ = new std::vector<Param*>();for(std::vector<Identifier*>::iterator ite = $1->begin();ite!=$1->end();ite++){$$->push_back(new Param($3,*ite));}};

program_body:	BGIN stmts END			{$$ = new StatementBlock($2);};

stmts		:	stmt SEMICOLON stmts	{$$ = $3; $$->insert($3->begin(), $1);}
			|	stmt					{$$ = new std::vector<Statement*>();$$->push_back($1);}
			|							{$$ = new std::vector<Statement*>();};

stmt		:	var ASSIGN exp 						{$$ = new AssignStatement($1,$3);}
			|	call								{$$ = new CallStatement($1);}
			|	IF exp THEN stmt ELSE stmt 			{$$ = new IfStatement($2, $4, $6);}
			|	IF exp THEN stmt					{$$ = new IfStatement($2, $4, NULL);}
			|	WHILE exp DO stmt					{$$ = new WhileStatement($2, $4);}
			|	FOR id ASSIGN exp TO exp DO stmt 	{$$ = new ForStatement($2, $4, $6, $8);}
			|	BGIN stmts END						{$$ = new StatementBlock($2);}
			|	BREAK								{$$ = new BreakStatement();$$->setloc(@1);}
			|	id									{$$ = new CallStatement(new CallExpression($1, new std::vector<Expression*>()));};
			
exp_list	:	exp_list COMMA exp			{$$ = $1; $1->push_back($3);}
			|	exp							{$$ = new std::vector<Expression*>(); $$->push_back($1);};
			
exp			:	exp ADD exp					{$$ = new ArithExpression($1,_ADD, $3);$$->setloc($1->loc,$3->loc);}
			| 	exp SUB exp 				{$$ = new ArithExpression($1,_SUB, $3);$$->setloc($1->loc,$3->loc);}
			|	SUB exp %prec UMINUS		{$$ = new ArithExpression(NULL, _SUB, $2);$$->setloc(&@1,$2->loc);}
			|	exp MUL exp 				{$$ = new ArithExpression($1,_MUL, $3);$$->setloc($1->loc,$3->loc);}
			| 	exp DIV exp 				{$$ = new ArithExpression($1,_DIV, $3);$$->setloc($1->loc,$3->loc);}
			| 	exp MOD exp 				{$$ = new ArithExpression($1,_MOD, $3);$$->setloc($1->loc,$3->loc);}
			|	LP exp RP 					{$$ = $2;$$->setloc(&@1,&@3);}
			|	exp AND exp 				{$$ = new LogicExpression($1,_AND, $3);$$->setloc($1->loc,$3->loc);}
			| 	exp OR 	exp 				{$$ = new LogicExpression($1,_OR, $3);$$->setloc($1->loc,$3->loc);}
			|	NOT exp						{$$ = new LogicExpression(NULL,_NOT, $2);$$->setloc(&@1,$2->loc);}
			|	exp GT  exp					{$$ = new RelExpression($1,_GT, $3);$$->setloc($1->loc,$3->loc);}
			|	exp LT	exp					{$$ = new RelExpression($1,_LT, $3);$$->setloc($1->loc,$3->loc);}
			|	exp GTE	exp 				{$$ = new RelExpression($1,_GTE, $3);$$->setloc($1->loc,$3->loc);}
			|	exp LTE exp 				{$$ = new RelExpression($1,_LTE, $3);$$->setloc($1->loc,$3->loc);}
			|	exp EQ exp					{$$ = new RelExpression($1,_EQ, $3);$$->setloc($1->loc,$3->loc);}
			|	exp NEQ exp 				{$$ = new RelExpression($1,_NEQ, $3);$$->setloc($1->loc,$3->loc);}
			|	call						{$$ = $1;}
			|	var							{$$ = $1;}
			|	num							{$$ = $1;}
			|	boolexp						{$$ = $1;};
	
call		:	syscall 	{$$ = $1;}
			| 	usercall	{$$ = $1;};
							
syscall		: 	READ LP exp_list RP  {$$ = new SysCall(_CALL_READ, $3);$$->setloc(&@1,&@4);} 
			|	WRITE LP exp_list RP {$$ = new SysCall(_CALL_WRITE,$3);$$->setloc(&@1,&@4);};

usercall	:	id LP exp_list RP {$$ = new CallExpression($1,$3);$$->setloc($1->loc,&@4);};

var			:	id						{$$ = $1;}
			|	id LSQ exp RSQ			{$$ = new ArrayElement($1,$3);$$->setloc($1->loc,&@4);};

type		:	stdtype				{$$ = $1;}
			|	ARRAY LSQ int DOTDOT int RSQ OF stdtype		{$$ = new ArrayType($8,$3,$5);$$->setloc(&@1,$8->loc);};

stdtype		:	TREAL				{$$ = TYPE_REAL;$$->setloc(@1);}
			|	TINT				{$$ = TYPE_INT;$$->setloc(@1);};

id_list		:	id_list COMMA id	{$$ = $1; $$->push_back($3);}
			|	id					{$$ = new std::vector<Identifier*>();$$->push_back($1);};

boolexp		:	TRUE	{$$ = new BoolConstant(true);$$->setloc(@1);}
			|	FALSE	{$$ = new BoolConstant(false);$$->setloc(@1);};

id			:	ID	{$$ = new Identifier(paslval.tokenval);$$->setloc(@1);};

num			:	int {$$ = new IntConstant($1);$$->setloc(@1);}
			|   REAL {$$ = new RealConstant(atof(paslval.tokenval));$$->setloc(@1);};
int			:	INT {$$ = atoi(paslval.tokenval);@$=@1;};
%%