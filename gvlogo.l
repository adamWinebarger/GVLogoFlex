%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "gvlogo.tab.h"

extern void yyerror(const char* s);
%}

%option noyywrap

VARNAME     [a-zA-Z_][a-zA-Z0-9_]*



%%

"penup" {return PENUP;}
"pendown" {return PENDOWN;}
"print" {return PRINT;}
"turn" {return TURN;}
"move" {return MOVE;}
"where" {return WHERE;}
"goto"  {return GOTO;}
"exit"  {return END;}
"clear" {return CLEAR;}
"color" {return COLOR;}
"change_color" {return CHANGE_COLOR;}
"string" {return STRINGVAR;}
"num"   {return NUM;}
"save" {return SAVE;}

"+" {return PLUS;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
";" {return SEP;}
"=" {return EQUALS;}

[a-zA-Z_]+ {yylval.s = strdup(yytext); return VAR;}

\"[^\"]*\" {yylval.s = strdup(yytext); return STRING;}
[0-9]+\.[0-9]+ {yylval.f = atof(yytext); return NUMBER;}
[0-9]+  {yylval.f = atof(yytext); return NUMBER;}
[ \t\r\n]			;

.			{ yyerror("Lexing Syntax error.\n"); }

%%
