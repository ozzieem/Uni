/* lab3B.y */

%{
#include <stdio.h>
#include <math.h>
extern int yyerror(char const *msg);
extern int lexan();
%}

%token PLUS MINUS STAR DIV EXP LPAREN RPAREN NUMBER NEWLINE
%left PLUS MINUS
%left STAR DIV
%left EXP

%%
line : /* empty */
     | line expr NEWLINE      { printf("%d\n", $2); }
expr : LPAREN expr RPAREN     { $$ = $2; }
     | expr PLUS expr         { $$ = $1 + $3; }
     | expr MINUS expr        { $$ = $1 - $3; }
     | expr STAR expr         { $$ = $1 * $3; }
     | expr DIV expr          { $$ = $1 / $3; }
     | expr EXP expr 	      { $$ = myPow($1,$3); }
     | NUMBER                 { $$ = $1; }
     ;

%%


int myPow(int base, int exponent){
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int yyerror(char const *msg) {
    printf("Error: %s\n", msg);
    return 0;
}

int main() {
    printf("%d\n", yyparse());
    return 0;
}
