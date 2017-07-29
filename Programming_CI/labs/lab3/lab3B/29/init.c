/* init.c */

#include "global.h"

Stack theStack;
struct entry keywords[] = {
  { "div", DIV },
  { "mod", MOD, },
  { 0,     0 }
};

void init()  /*  loads keywords into symtable  */
{
  Stack_Init(&theStack);
  struct entry *p;
  for (p = keywords; p->token; p++)
    insert(p->lexptr, p->token);
}
