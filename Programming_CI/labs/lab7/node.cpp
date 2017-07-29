#include "node.h"

// NODE FUNCTIONS

Node::Node()
{
  this->type = -1;
  this->leaf_value = 0;
  this->args[0] = nullptr;
  this->args[1] = nullptr;
  this->args[2] = nullptr;
}

Node *mkleaf(int token, int value)
{
  Node *p = new Node();
  p->type = token;
  p->leaf_value = value;
  return p;
}

Node *mknode(int type, Node *arg1, Node *arg2)
{
  Node *p = new Node();
  p->type = type;
  p->args[0] = arg1;
  p->args[1] = arg2;
  p->args[2] = 0;
  return p;
}

Node *mkifnode(Node *cond, Node *thennode, Node *elsenode)
{
  Node *p = new Node();
  p->type = 'I';
  p->args[0] = cond;
  p->args[1] = thennode;
  p->args[2] = elsenode;
  return p;
}

Node *mkwhilenode(Node *cond, Node *thennode)
{
  Node *p = new Node();
  p->type = 'W';
  p->args[0] = cond;
  p->args[1] = thennode;
  return p;
}

Node *mkreadnode(Node *var)
{
  Node *p = new Node();
  p->type = 'R';
  p->args[0] = var;
  return p;
}

Node *mkprintnode(Node *var)
{
  Node *p = new Node();
  p->type = 'P';
  p->args[0] = var;
  return p;
}
