/* lab3B.lex */

%{
#include <stdio.h>
#include "lab3B.tab.h"
%}

%option noyywrap

%%

[ \t]+    { /* ignore whitespace */ }
"("       { return LPAREN; }
")"       { return RPAREN; }
"+"       { return PLUS; }
"-"       { return MINUS; }
"*"       { return STAR; }
"/"       { return DIV; }
"^"	  { return EXP; }
\n        { return NEWLINE; }
[0-9]+    { yylval = atoi(yytext); return NUMBER; }
.         { printf("Ignoring invalid character '%s'\n", yytext); }

%%
