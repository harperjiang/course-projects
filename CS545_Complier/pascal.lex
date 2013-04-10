%{
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "parser.h"

extern void paserror(const char* input);
extern void error(const char* info);

int yyline = 1;
int yycol = 0;

void handle_line() {
	paslloc.first_line = yyline;
	paslloc.last_line = yyline;
	paslloc.first_column = yycol;
	paslloc.last_column = yycol + strlen(pastext);
	yycol += strlen(pastext);
}

#define YY_USER_ACTION handle_line();

void lex_error() {
	char* buffer = new char[200];
	sprintf(buffer,"Parse error: unrecognized token `%s' at line %d, col %d",pastext, yyline, yycol - (int)strlen(pastext));
	error(buffer);
	delete buffer;
}
%}

NUMBER					[0-9]+
ID						[a-zA-Z_][a-zA-Z0-9_]*
%option noyywrap

%%
{NUMBER}"."{NUMBER} 	{paslval.tokenval = pastext; return REAL;}
{NUMBER}				{paslval.tokenval = pastext; return INT;}
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
":"						{return COLON;}
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
{ID}				 	{paslval.tokenval = pastext; return ID;}
[\t ]					{;}
\n						{yyline++;yycol = 0;}
.                  		{lex_error();}
%%