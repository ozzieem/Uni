%{
  #include <stdlib.h> /* Required to compile with C++ */
  #include <stdio.h>
  #include <ctype.h>
  #include "global.h"
  extern int yyparse(); /* Required to compile with C++ */
  extern void yyerror(char*); /* Required to compile with C++ */
  extern int yylex(void); /* Required to compile with C++ */
%}

%token NUM DIV MOD ID DONE

%left '+' '-'
%left '*' '/'
%right '^'

%%

start: 	list DONE
	;

list:	expr ';' list 
	| assign ';' list
	| /* empty */	
	;

expr:	var { $$ = symtable[$1].value; /*printf("%s\n", symtable[$1].lexptr);*/ }
	| NUM { $$ = $1; printf("%d\n", $1); }	
	| expr '+' expr { $$ = $1 + $3; printf("+\n"); }
	| expr '-' expr { $$ = $1 - $3; printf("-\n"); }
	| expr '*' expr { $$ = $1 * $3; printf("*\n"); }
	| expr '/' expr { $$ = $1 / $3; printf("/\n"); }
	| expr '^' expr { $$ = myPow($1, $3); printf("^\n"); }
	;

assign: var '=' expr { symtable[$1].value = $3; printf("=\nValue: %d\n", $3); }
	;

var: ID { $$ = $1; printf("%s\n", symtable[$1].lexptr); }
	;

%%

int yylex(void) {
  return lexan();
}

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

