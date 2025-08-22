#ifndef B_TREE_H
#define B_TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct TNode
{
    int index;
    const char *name;
    struct TNode *parent;
    struct TNode *left;
    struct TNode *right;
} TNode;

typedef struct BTree
{
    struct TNode *root;
} BTree;

TNode *search_btree(BTree *tree, int index);
TNode *insert_btree_tnode(BTree *tree, int index, const char *name);
TNode *insert_tnode(TNode *node, int index, const char *name);
int remove_btree_tnode(BTree *tree, int index);
void transplant_btree_node(
    BTree *tree,
    TNode *to_replace,
    TNode *replacement);
// Memory
BTree *init_btree(void);
TNode *create_tnode(int index, const char *name, TNode *left, TNode *right);
void free_btree(BTree *tree);
void free_tnode(TNode *node);

#endif
