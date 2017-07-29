
%{
   #include <stdio.h>
   #include "lab5.tab.hpp"
   #include "node.h"

   entry symtable[100];
   extern void error_lex(char *);
   extern int insert(char *s, int tok);  /*  returns position of entry for s */
   extern int lookup(char *s);  /*  returns position of entry for s */
%}

%option noyywrap

%%

"if" { return IF; }
"else"	{ return ELSE; }
"while" { return WHILE; }
"print" { return PRINT; }
"read"  { return READ; }

[0-9]+      { yylval.numV = atoi(yytext); return NUM; }
([A-Za-z])+ { int p = lookup(yytext); /*printf("lookup returned: %d\n", p)*/;
              if(p == 0) { p = insert(yytext, ID); }
              yylval.idV = p;
              /*printf("yylval.idV: %d\n", yylval.idV)*/;
              return ID; 
            }
[ \t\n]+    { /* ignore whitespace */ }
.      { return *yytext; }  // . -> return any character

%%

char lexemes[999];
int  lastchar = -1;
int lastentry = 0;

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
  //if (lastentry + 1 >= SYMMAX)
    //error ("symbol table full");
  //if (lastchar + len + 1 >= STRMAX)
    //error ("lexemes array full");
  lastentry = lastentry + 1;
  symtable[lastentry].token = tok;
  symtable[lastentry].lexptr = &lexemes[lastchar + 1];
  lastchar = lastchar + len + 1;
  strcpy(symtable[lastentry].lexptr, s);
  //printf("Inserted: %s in %d\n", yytext, lastentry);    //DEBUG
  return lastentry;
}
