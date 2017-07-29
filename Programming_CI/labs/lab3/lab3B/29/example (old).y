%{
  #include <stdio.h>
  #include "global.h"
  extern void yyerror(char*);
%}

%token DONE ID NUM DIV MOD

%%

start: list DONE
        ;

list: assignment ';' list
	| expr ';' list
	| /* empty */
        ;

expr: term moreterms
       	;

assignment: ID {idIndex = tokenval; emit(ID, tokenval);} '=' expr {emit('=', tokenval); symtable[idIndex].value = Stack_Pop(&theStack); printf("Value: %d\n", symtable[idIndex].value);} 
	;

moreterms: '+' term {calc('+'); emit('+', tokenval);} moreterms
	| '-' term {calc('-'); emit('-', tokenval);} moreterms
	| /* empty */
	;
	
term: factor morefactors
	;

morefactors: '*' factor {calc('*'); emit('*', tokenval);} morefactors
	| '/' factor {calc('/'); emit('/', tokenval);} morefactors
	| DIV factor {emit(DIV, tokenval);} morefactors
	| MOD factor {emit(MOD, tokenval);} morefactors
	| /* empty */
	;

factor: exponent moreexponents
	;

moreexponents: '^' exponent {calc('^'); emit('^', tokenval);} moreexponents
	| /* empty */	
	; 

exponent: '(' expr ')'
	| { Stack_Push(&theStack, tokenval); emit(NUM, tokenval);} NUM
	| { Stack_Push(&theStack, symtable[tokenval].value); emit(ID, tokenval);} ID
	| { yyerror("exponent error");}
	;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int yylex(void) {
  return lexan();
}

