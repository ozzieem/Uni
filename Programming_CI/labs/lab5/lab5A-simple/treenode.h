#define MAX_ARGS 3

struct TreeNode {
  int type;
  int leaf_value;
  TreeNode* args[MAX_ARGS];
};

TreeNode* mkleaf(int, int);
TreeNode* mknode(int type, TreeNode* a0 = 0, TreeNode* a1 = 0, TreeNode* a2 = 0);
