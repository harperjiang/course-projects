%{
#include <stdio.h>
#include "node.h"
#include "parser.h"

extern void calerror(char* input);

%}

%option noyywrap


%%
[0-9]+              	{callval.stringTerm = caltext; return NUM;}
"="						{return ASSIGN;}
";"						{return SEMICOLON;}
"("                 	{return LP;}
")"                 	{return RP;}
"{"						{return LB;}
"}"						{return RB;}
"+"                 	{return ADD;}
"-"                 	{return SUB;}
"*"                 	{return MUL;}
"/"                 	{return DIV;}
[a-zA-Z_][a-zA-Z0-9_]* 	{callval.stringTerm = caltext; return ID;}
[\t\n ]					{/* ignore*/;}
.                  		{calerror(caltext);}
%%