/* error.c */

#include "global.h"

void error(char* m)  /* generates all error messages  */
{
  fflush(stdout);
  fprintf(stderr, "line %d: %s\n", lineno, m);
  exit(EXIT_FAILURE);  /*  unsuccessful termination  */
}
