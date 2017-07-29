/* parser.c -- without the optimizations */

#include "global.h"

int lookahead;

void match(int);

void assignment();

int myPow(int, int);

void calc(char);

void start(), list(), expr(), moreterms(), term(), morefactors(), factor(), exponent(), moreexponents();

void parse()  /*  parses and translates expression list  */
{
  lookahead = lexan();
  start();
}

void start ()
{
  /* Just one production for start, so we don't need to check lookahead */
  list(); match(DONE);
}

void list()
{
    if (lookahead == ID) {
        assignment(); match(';'); list();
    }

    else {
    /* Empty */
    }
}

void assignment() {
    int idIndex = tokenval;
    emit(ID, tokenval); match(ID); match('='); expr(); emit('=', tokenval);
    symtable[idIndex].value = Stack_Pop(&theStack);
    printf("Value: %d\n", symtable[idIndex].value);
}

void expr ()
{
  /* Just one production for expr, so we don't need to check lookahead */
  term(); moreterms();
}

int myPow(int base, int exponent){
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

void calc(char symbol) {
    int result, first, second;
    first = Stack_Pop(&theStack);
    second = Stack_Pop(&theStack);

    switch (symbol) {
        case '+':
            result = second + first;
            break;
        case '-':
            result = second - first;
            break;
        case '*':
            result = second * first;
            break;
        case '/':
            result = second / first;
            break;
        case '^':
            result = myPow(second, first);
            break;
    }

    Stack_Push(&theStack, result);
}

void moreterms()
{
  if (lookahead == '+') {
    match('+'); term(); calc('+'); emit('+', tokenval); moreterms();
  }
  else if (lookahead == '-') {
    match('-'); term(); calc('-'); emit('-', tokenval); moreterms();
  }
  else {
    /* Empty */
  }
}

void term ()
{
  /* Just one production for term, so we don't need to check lookahead */
  factor(); morefactors();
}

void morefactors ()
{
  if (lookahead == '*') {
    match('*'); factor(); calc('*'); emit('*', tokenval); morefactors();
  }
  else if (lookahead == '/') {
    match('/'); factor(); calc('/'); emit('/', tokenval); morefactors();
  }
  else if (lookahead == DIV) {
    match(DIV); factor(); emit(DIV, tokenval); morefactors();
  }
  else if (lookahead == MOD) {
    match(MOD); factor(); emit(MOD, tokenval); morefactors();
  }

  else {
    /* Empty */
  }
}

void factor()
{
    exponent(); moreexponents();
}

void moreexponents() {
    if (lookahead == '^') {
        match('^'); exponent(); calc('^'); emit('^', tokenval); moreexponents();
    }
    else{
        /* Empty */
    }
}

void exponent() {
    if (lookahead == '(') {
        match('('); expr(); match(')');
    }
    else if (lookahead == ID) {
        int id_lexeme = tokenval;
        int id_value = symtable[id_lexeme].value;
        Stack_Push(&theStack, id_value);
        match(ID);
        emit(ID, id_lexeme);
    }
    else if (lookahead == NUM) {
        int num_value = tokenval;
        Stack_Push(&theStack, num_value);
        match(NUM);
        emit(NUM, num_value);
    }

    else
        error("syntax error in exponent");
}

void match(int t)
{
  if (lookahead == t)
    lookahead = lexan();
  else
    error ("syntax error in match");
}
