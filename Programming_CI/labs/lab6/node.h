#pragma once
#include <stdio.h>

#include "lab6.tab.hpp"   // For NUM, ID

typedef struct Node Node;

class Node
{
public:
  int type;
  int leaf_value;
  Node *args[3];

  Node();
};

Node *mkleaf(int, int);
Node *mknode(int type, Node *, Node *);
Node *mkifnode(Node *, Node *, Node *);
Node *mkwhilenode(Node *, Node *);
void printTreeRec(Node *, int);

#define BSIZE 128 /* buffer size */
#define NONE -1
#define EOS '\0'
#define STRMAX 999 /*  size of lexemes array  */
#define SYMMAX 100 /*  size of symbol table */

class entry
{ /*  form of symbol table entry  */
public:
  char* lexptr;
  int token;
  int value;

  entry()
  {
    lexptr = NULL;
    token = -1;
    value = 0;
  }
};