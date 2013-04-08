%{
#include <stdio.h>
#include "node.h"
#include "parser.h"

extern void paserror(char* input);

%}

NUMBER					[0-9]+
ID						[a-zA-Z_][a-zA-Z0-9_]*
%option noyywrap

%%
{NUMBER}.{NUMBER} 	 	{paslval.stringTerm = pastext; return REAL;}
{NUMBER}				{paslval.stringTerm = pastext; return INT;}
"program"				{return PROGRAM;}
"function"				{return FUNCTION;}
"procedure"				{return PROCEDURE;}
"begin"					{return BGIN;}
"end"					{return END;}
"if"					{return IF;}
"then"					{return THEN;}
"else"					{return ELSE;}
"while"					{return WHILE;}
"do"					{return DO;}
"read"					{return READ;}
"write"					{return WRITE;}
"var"					{return VAR;}
"real"					{return TREAL;}
"int"					{return TINT;}
"array"					{return ARRAY;}
"of"					{return OF;}
"true"					{return TRUE;}
"false"					{return FALSE;}
"break"					{return BREAK;}
"."						{return DOT;}
".."					{return DOTDOT;}
","						{return COMMA;}
":="					{return ASSIGN;}
";"						{return SEMICOLON;}
"("                 	{return LP;}
")"                 	{return RP;}
"["						{return LSQ;}
"]"						{return RSQ;}
"+"                 	{return ADD;}
"-"                 	{return SUB;}
"*"                 	{return MUL;}
"/"                 	{return DIV;}
"&&"					{return AND;}
"||"					{return OR;}
"!"						{return NOT;}
"="						{return EQ;}
"!="					{return NEQ;}
">"						{return GT;}
"<"						{return LT;}
">="					{return GTE;}
"<="					{return LTE;}
{ID}				 	{paslval.stringTerm = pastext; return ID;}
[\t\n ]					{/* ignore*/;}
.                  		{paserror(pastext);}
%%