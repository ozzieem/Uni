
typedef struct Node Node;

struct Node {
  int type;
  int leaf_value;
  Node* left;
  Node* right;
};

Node* mkleaf(int, int);
Node* mknode(int type, Node*, Node*);
void printTreeRec(Node*, int); 
