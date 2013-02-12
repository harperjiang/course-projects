%{
#include <stdio.h>
#include "node.h"
    
void calerror(char* s) {
	fprintf(stderr,"%s",s);
}
    
extern int callex();

Statements* parse_result;

%}

%union {
    char* stringTerm;
    Statements*	stmts;
    Statement* stmt;
    Expression* exp;
    Identifier* id;
}
%token LP RP ADD SUB MUL DIV ASSIGN SEMICOLON
%token NUM ID

%type <stmts> stmts
%type <stmt> stmt
%type <exp> exp
%type <id> id

%left LOW
%left ADD SUB
%left MUL DIV
%left HIGH

%start stmts

%%
stmts	: 	stmt stmts 				{$$ = $2; $$->insert($1,0);}
		|	stmt					{$$ = new Statements();$$->insert($1,0);parse_result = $$;};
stmt	:	id ASSIGN exp SEMICOLON	{$$ = new AssignStatement($1,$3);}
		|	exp SEMICOLON			{$$ = new PrintStatement($1);};
exp		:	LP exp RP				{$$ = $2;}
		|	exp ADD exp				{$$ = new ArithExpression($1,OADD,$3);}
		|	exp SUB exp				{$$ = new ArithExpression($1,OSUB,$3);}
		|	exp MUL	exp				{$$ = new ArithExpression($1,OMUL,$3);}
		|	exp DIV exp				{$$ = new ArithExpression($1,ODIV,$3);}
		|	NUM						{$$ = new NumConstant(atoi(callval.stringTerm));}
		|	id						{$$ = $1;};
id		:	ID						{$$ = new Identifier(callval.stringTerm);};
%%