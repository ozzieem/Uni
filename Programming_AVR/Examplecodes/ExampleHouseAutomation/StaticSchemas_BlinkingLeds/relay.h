#ifndef _RELAY_H
#define _RELAY_H

typedef struct
{
  char out; //state variable
  char delta; //half value of the hyst.
} relay;

void relay_init(relay *this, int de );
int relay_run(relay *this, int e);

#endif

