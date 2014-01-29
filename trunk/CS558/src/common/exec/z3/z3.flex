package common.exec.z3;

import java_cup.runtime.Symbol;
%%

%class Lexer
%public
%cup
%unicode
%eofclose
%eofval{
  return symbol(Syms.EOF);
%eofval}

ID = [A-Za-z][A-Za-z0-9_]*
NUM = [1-9][0-9]*

%{
StringBuilder builder;

private Symbol symbol(int type) {
    return new Symbol(type, yyline, yycolumn);
}

private Symbol symbol(int type, Object value) {
    return new Symbol(type, yyline, yycolumn, value);
}

%}

%state STRING

%%

<STRING>{
\"					{ yybegin(YYINITIAL);return symbol(Syms.STRING,builder.toString()); }
[^\n\r\"]			{ builder.append(yytext());}
}
<YYINITIAL> {
\"					{ builder = new StringBuilder(); yybegin(STRING);}
"model"				{ return symbol(Syms.MODEL);}
"unsat"				{ return symbol(Syms.UNSAT);}
"sat"				{ return symbol(Syms.SAT);}
"Bool"				{ return symbol(Syms.BOOL);}
"Int"				{ return symbol(Syms.INT);}
"true"				{ return symbol(Syms.TRUE);}
"false"				{ return symbol(Syms.FALSE);}
"error"				{ return symbol(Syms.ERROR);}
"define-fun"		{ return symbol(Syms.DEFINE);}
"("					{ return symbol(Syms.LB);}
")"					{ return symbol(Syms.RB);}
{NUM}				{ return symbol(Syms.NUM, Integer.parseInt(yytext()));}
{ID}				{ return symbol(Syms.ID, yytext());}
[\ \t\b\f\r\n]+ 	{ /* Ignore*/	}
.       			{ throw new RuntimeException("Unknow character:"+yytext()); }
}