%{
  #include <stdlib.h> /* Required to compile with C++ */
  #include <stdio.h>
  #include <ctype.h>
  #include "symbol.h"

  extern int myPow(int,int);
  extern int yyparse(); /* Required to compile with C++ */
  extern void yyerror(char*); /* Required to compile with C++ */
  extern int yylex(void); /* Required to compile with C++ */
  extern int yylval;

%}

%token ID NUM

%right '?' ':'
%left '|'
%left '&'
%left '<' '>'
%left '+' '-'
%left '*' '/' '%'
%right '^'

%%

start: 	list ';'
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
	| expr '%' expr { $$ = $1 % $3; printf("%%\n"); }
	| expr '&' expr { $$ = $1 & $3; printf("&\n"); }
	| expr '|' expr { $$ = $1 | $3; printf("|\n"); }
	| expr '<' expr { $$ = $1 < $3; printf("<\n"); }
	| expr '>' expr { $$ = $1 > $3; printf(">\n"); }
	| expr '?' expr ':' expr { $$ = $1 ? $3 : $5; printf("?:\n"); }
	;

assign: var '=' expr { symtable[$1].value = $3; printf("=\nValue: %d\n", $3); }
	;

var: ID { $$ = $1; printf("%s\n", symtable[yylval].lexptr); }
	;

%%

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

int myPow(int base, int exponent){
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main() {
		yyparse();
}