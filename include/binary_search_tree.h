#ifndef B_TREE_H
#define B_TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct BSTNode
{
    int index;
    const char *name;
    struct BSTNode *parent;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct BinarySearchTree
{
    struct BSTNode *root;
} BinarySearchTree;

BSTNode *search_bst(BinarySearchTree *tree, int index);
BSTNode *insert_bst_node(BinarySearchTree *tree, int index, const char *name);
BSTNode *insert_node(BSTNode *node, int index, const char *name);
int remove_bst_node(BinarySearchTree *tree, int index);
void transplant_bst_node(
    BinarySearchTree *tree,
    BSTNode *to_replace,
    BSTNode *replacement);
// Memory
BinarySearchTree *init_bst(void);
BSTNode *create_bst_node(int index, const char *name, BSTNode *left, BSTNode *right);
void free_bst(BinarySearchTree *tree);
void free_node(BSTNode *node);

// Display
void print_node(const BSTNode *node, int depth);
void print_tree(const BinarySearchTree *tree);
#endif
