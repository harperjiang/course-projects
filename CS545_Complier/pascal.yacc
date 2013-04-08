%{
#include <stdio.h>
    
void calerror(char* s) {
	fprintf(stderr,"%s",s);
}
    
extern int paslex();


%}

%token PROGRAM FUNCTION PROCEDURE
%token VAR IF ELSE THEN WHILE DO BEGIN END
%token SEMICOLON COMMA COLON DOT DOTDOT
%token LP RP LSQ RSQ

%token ARRAY TINT TREAL OF
%token ASSIGN ADD SUB MUL DIV MOD AND OR NOT GT LT EQ NEQ GTE LTE
%token INT REAL ID

%left AND OR
%right NOT
%left GT LT GTE LTE EQ NEQ
%left ADD SUB 
%left MUL DIV MOD
%left THEN
%left ELSE


%start program

%%
program		:	PROGRAM id SEMICOLON declares subs program_body DOT 	{};

declares	: 	declares var id_lists COLON type SEMICOLON			{}
			|	VAR id_lists COLON type SEMICOLON					{};
			
subs		:	subs sub 			{}
			|			 			{};

sub			:	function 			{}
			|	procedure			{};

function	:	FUNCTION LP args RP COLON stdtype program_body SEMICOLON	{};

procedure	:	PROCEDURE LP args RP program_body SEMICOLON				{};

args		:	args SEMICOLON id_lists COLON type	{}
			|	id_lists COLON type {};

program_body:	BEGIN stmts END	{};

stmts		:	stmts SEMICOLON stmt	{}
			|							{};

stmt		:	var ASSIGN exp 				{}
			|	id LP exp_list RP 			{}
			|	id							{}
			|	IF exp THEN stmt ELSE stmt 	{}
			|	IF exp THEN stmt			{}
			|	WHILE exp DO stmt			{}
			|	BEGIN stmts END				{};
			
exp_list	:	exp_list COMMA exp			{}
			|	exp							{};
			
exp			:	exp ADD exp	{}
			| 	exp SUB exp {}
			|	SUB exp 	{}
			|	exp MUL exp {}
			| 	exp DIV exp {}
			| 	exp MOD exp {}
			|	LP exp RP 	{}
			|	exp AND exp {}
			| 	exp OR 	exp {}
			|	NOT exp		{}
			|	exp GT  exp	{}
			|	exp LT	exp	{}
			|	exp GTE	exp {}
			|	exp LTE exp {}
			|	exp EQ exp{}
			|	exp NEQ exp {}
			|	id			{}
			|	num			{};	

var			:	id						{}
			|	id LSQ exp RSQ			{};

type		:	stdtype	{}
			|	ARRAY LSQ INT DOTDOT INT RSQ OF stdtype					{};

stdtype		:	TREAL												{}
			|	TINT													{};

id_lists	:	id_lists COMMA id									{}
			|													{};

id			:	ID	{};
num			:	INT {}
			|   REAL {};
%%