struct node *parent(struct node *n)
{
 return n->parent;
}

struct node *grandparent(struct node *n)
{
 struct node *p = parent(n);
 if (p == NULL)
  return NULL; // No parent means no grandparent
 return parent(p);
}

struct node *sibling(struct node *n)
{
 struct node *p = parent(n);
 if (p == NULL)
  return NULL; // No parent means no sibling
 if (n == p->left)
  return p->right;
 else
  return p->left;
}

struct node *uncle(struct node *n)
{
 struct node *p = parent(n);
 struct node *g = grandparent(n);
 if (g == NULL)
  return NULL; // No grandparent means no uncle
 return sibling(p);
}

void rotate_left(struct node *n)
{
 struct node *nnew = n->right;
 assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
 n->right = nnew->left;
 nnew->left = n;
 nnew->parent = n->parent;
 n->parent = nnew;
 // (the other related parent and child links would also have to be updated)
}

void rotate_right(struct node *n)
{
 struct node *nnew = n->left;
 assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
 n->left = nnew->right;
 nnew->right = n;
 nnew->parent = n->parent;
 n->parent = nnew;
 // (the other related parent and child links would also have to be updated)
}