
%{
#include <stdio.h>
#include "lab4b.tab.h"
#include "symbol.h"
extern int yylval;
extern void error_lex(char *);
%}

%option noyywrap

%%
[ \t\n]+ { /* ignore whitespace */ }
[0-9]+ { yylval = atoi(yytext); return NUM; }
[a-z]+ { int p = lookup(yytext); 
         if(p == 0) { 
            p = insert(yytext, ID); 
         } 
         yylval = p;
         return ID; };

.      { return *yytext; }  // . -> return any character

%%

int  lastchar = - 1;
int lastentry = 0;
char lexemes[STRMAX];


int lookup(char *s)         /*  returns position of entry for s */
{
  int p;
  for (p = lastentry; p > 0; p = p - 1)
    if (strcmp(symtable[p].lexptr, s) == 0)
      return p;
  return 0;
}

int insert(char *s, int tok)    /*  returns position of entry for s */
{
  int len;
  len = strlen(s);  /*  strlen computes length of s     */
  if (lastentry + 1 >= SYMMAX)
    error_lex ("symbol table full");
  if (lastchar + len + 1 >= STRMAX)
    error_lex ("lexemes array full");
  lastentry = lastentry + 1;
  symtable[lastentry].token = tok;
  symtable[lastentry].lexptr = &lexemes[lastchar + 1];
  lastchar = lastchar + len + 1;
  strcpy(symtable[lastentry].lexptr, s);
  return lastentry;
}

void error_lex(char* m)  /* generates all error messages  */
{
  fflush(stdout);
  fprintf(stderr, "%s\n", m);
  exit(EXIT_FAILURE);  /*  unsuccessful termination  */
}