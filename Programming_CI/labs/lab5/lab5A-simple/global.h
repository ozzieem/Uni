/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include <math.h>
#include "parser.tab.hpp"

#define BSIZE  128  /* buffer size */
#define NONE   -1
#define EOS    '\0'

extern int tokenval;   /*  value of token attribute */  
extern int lineno;

struct entry {  /*  form of symbol table entry  */
  char *lexptr; 
  int  token;
    int value;
};

extern struct entry symtable[];  /* symbol table  */

extern void error(char* m);  /*  generates all error messages  */
extern int lexan();  /*  lexical analyzer  */
extern int insert(char *s, int tok);  /*  returns position of entry for s */
extern int lookup(char *s);  /*  returns position of entry for s */
