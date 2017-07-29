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

list:	expr ';' list
	| /* empty */	
	;

expr: expr '=' expr { $$ = mknode('=', $1, $3); }
	| ID  { $$ = mkleaf(ID, yylval.idV); } /* Sets leaf_value to symtable index */
  | NUM { $$ = mkleaf(NUM, $1); } 	
	| expr '+' expr { $$ = mknode('+', $1, $3); } //printf("+\n"); }
	| expr '-' expr { $$ = mknode('-', $1, $3); } //printf("-\n"); }
	| expr '*' expr { $$ = mknode('*', $1, $3); } //printf("*\n"); }
	| expr '/' expr { $$ = mknode('/', $1, $3); } //printf("/\n"); }
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

int myPow(int base, int exponent){
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}
