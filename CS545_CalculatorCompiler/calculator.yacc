%{
#include <stdio.h>
#include "node.h"
    
void calerror(char* s) {
	fprintf(stderr,"%s",s);
}
    
extern int callex();

Program* parse_result;

%}

%union {
    char* stringTerm;
    Program* program;
    Statements*	stmts;
    StatementBlock* block;
    Statement* stmt;
    Expression* exp;
    Identifier* id;
}
%token LP RP ADD SUB MUL DIV ASSIGN SEMICOLON LB RB
%token NUM ID

%type <program> program
%type <stmts> stmts
%type <stmt> stmt
%type <exp> exp
%type <id> id
%type <block> block;

%left LOW
%left ADD SUB
%left MUL DIV
%left HIGH

%start program

%%
program :	block					{$$ = new Program();$$->block = $1; parse_result = $$;};
stmts	: 	stmt stmts 				{$$ = $2; $$->insert($1,0);}
		|	stmt					{$$ = new Statements();$$->insert($1,0);};
block	:	LB stmts RB				{$$ = new StatementBlock(); $$->content = $2;};
stmt	:	id ASSIGN exp SEMICOLON	{$$ = new AssignStatement($1,$3);}
		|	exp SEMICOLON			{$$ = new PrintStatement($1);}
		|	block					{$$ = $1;};
exp		:	LP exp RP				{$$ = $2;}
		|	exp ADD exp				{$$ = new ArithExpression($1,OADD,$3);}
		|	exp SUB exp				{$$ = new ArithExpression($1,OSUB,$3);}
		|	exp MUL	exp				{$$ = new ArithExpression($1,OMUL,$3);}
		|	exp DIV exp				{$$ = new ArithExpression($1,ODIV,$3);}
		|	NUM						{$$ = new NumConstant(atoi(callval.stringTerm));}
		|	id						{$$ = $1;};
id		:	ID						{$$ = new Identifier(callval.stringTerm);};
%%