/* symtable.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include <math.h>

#define BSIZE  128  /* buffer size */
#define NONE   -1
#define EOS    '\0'
#define STRMAX 999  /*  size of lexemes array  */
#define SYMMAX 100  /*  size of symbol table */

struct entry {  /*  form of symbol table entry  */
  char *lexptr; 
  int  token;
    int value;
};


int insert(char *s, int tok);  /*  returns position of entry for s */
int lookup(char *s);  /*  returns position of entry for s */

struct entry symtable[100];
