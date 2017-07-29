#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "lab5.tab.h"   // For NUM, ID
#include "symbol.h"     // Symboltable in printTree

// NODE FUNCTIONS 

Node* mkleaf(int type, int value) {
  Node* p = malloc(sizeof(*p));
  p->type = type;
  p->leaf_value = value;
  return p;
}

Node* mknode(int type, Node* left, Node* right) {
  Node* p = malloc(sizeof(*p));
  p->type = type; 	//	printf("%c\n", type);
  p->left = left; 	//	printf("%d\n", left->leaf_value);
  p->right = right; //	printf("%d\n", right->leaf_value);
  return p;
}


// PRINT TREE

void printTreeRec(Node *p, int level) {
  if (p == 0)
    ;
  else if (p->type == ID) {
    printf("%*s", 2 * level, "");
    printf("%s\n", symtable[p->leaf_value].lexptr);
  }
  else if (p->type == NUM) {
    printf("%*s", 2 * level, "");
    printf("%d\n", p->leaf_value);
  }
  else if (p->type == '+') {
    printf("%*s", 2*level, "");
    printf("+\n");
    printTreeRec(p->right, level + 1);
    printTreeRec(p->left, level + 1);
  }
  else if (p->type == '-') {
    printf("%*s", 2*level, "");
    printf("-\n");
    printTreeRec(p->right, level + 1);
    printTreeRec(p->left, level + 1);
  }
  else if (p->type == ';') {
  	printf("%*s", 2*level, "");
    printTreeRec(p->right, level + 1);
    printf("%*s", 2*level, "");
    printf(";\n");
    printTreeRec(p->left, level);
  }
}
