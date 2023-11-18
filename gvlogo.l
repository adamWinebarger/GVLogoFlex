%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "gvlogo.tab.h"

extern void yyerror(const char* s);
%}

%option noyywrap


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

\"[a-zA-Z0-9\ _!.,/\\]+\" {yylval.s = yytext; return STRING;}
[0-9]+   {yylval.f = atof(yytext); return NUMBER;}
[ \t\r\n]			;

"+" {return PLUS;}
";" {return SEP;}
"=" {return EQUALS;}

.			{ yyerror("Lexing Syntax error.\n"); }

%%
