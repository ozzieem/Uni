%{
  #include <stdlib.h>
  #include <stdio.h>
  #include <ctype.h>
  #include "symbol.h"
  #include "node.h"

  extern int myPow(int,int);
  extern int yyparse(); 
  extern void yyerror(char*);
  extern int yylex(void);

  extern Node* mkleaf(int, int);
  extern Node* mknode(int type, Node*, Node*);
  extern void printTree(Node*, int);
%}

%token ID NUM

%left '='
%right '?' ':'
%left '|'
%left '&'
%left '<' '>'
%left '+' '-'
%left '*' '/' '%'
%right '^'

%%

%union {
	struct Node* p; 
	int numV;
	int idV;
};

%type <p> expr;
%type <numV> NUM;	// Tell NUM that it's of type yylval.numV, enables use of $1, instead of yylval.numV
%type <idV> ID;

start: 	list ';'
	;

list:	expr ';' { $1 = mknode(';', $1, 0); printTree($1, 0); } list
	| /* empty */	
	;

expr:
  ID  { $$ = mkleaf(ID, yylval.idV); } /* Sets leaf_value to symtable index */
  | NUM { $$ = mkleaf(NUM, $1); }
  | expr '=' expr { $$ = mknode('=', $1, $3); }
	| expr '+' expr { $$ = mknode('+', $1, $3); }
	| expr '-' expr { $$ = mknode('-', $1, $3); }
	| expr '*' expr { $$ = mknode('*', $1, $3); }
	| expr '/' expr { $$ = mknode('/', $1, $3); }
  | expr '%' expr { $$ = mknode('%', $1, $3); }
  | expr '^' expr { $$ = mknode('^', $1, $3); }
	;

%%

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

void debug(){
}

int main() {
		yyparse();
}

void printTree(Node* tree, int level) {
	printf("Syntax tree:\n");
	printTreeRec(tree,0);
}
