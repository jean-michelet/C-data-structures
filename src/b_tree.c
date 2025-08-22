#include "b_tree.h"
#include <stdio.h>

BTree *init_btree()
{
    BTree *tree = malloc(sizeof(BTree));
    tree->root = NULL;

    return tree;
}

TNode *create_tnode(int index, const char *name, TNode *left, TNode *right)
{
    TNode *node = malloc(sizeof(TNode));
    if (!node)
        return NULL;

    node->parent = NULL;
    node->index = index;
    node->name = name;

    if (left != NULL)
    {
        left->parent = node;
    }

    node->left = left;

    if (right != NULL)
    {
        right->parent = node;
    }

    node->right = right;

    return node;
}

TNode *insert_btree_tnode(BTree *tree, int index, const char *name)
{
    if (tree->root == NULL)
    {
        tree->root = create_tnode(index, name, NULL, NULL);
        return tree->root;
    }
    else
    {
        TNode *node = insert_tnode(tree->root, index, name);
        return node;
    }
}

TNode *insert_tnode(TNode *parent, int index, const char *name)
{
    if (parent->index == index)
    {
        return NULL;
    }

    if (index < parent->index)
    {
        if (parent->left == NULL)
        {
            parent->left = create_tnode(index, name, NULL, NULL);
            parent->left->parent = parent;
            return parent->left;
        }

        return insert_tnode(parent->left, index, name);
    }

    if (parent->right == NULL)
    {
        parent->right = create_tnode(index, name, NULL, NULL);
        parent->right->parent = parent;
        return parent->right;
    }

    return insert_tnode(parent->right, index, name);
}

void transplant_btree_node(
    BTree *tree,
    TNode *to_replace,
    TNode *replacement)
{
    if (!to_replace->parent)
    {
        tree->root = replacement;
    }
    else if (to_replace->parent->left == to_replace)
    {
        to_replace->parent->left = replacement;
    }
    else if (to_replace->parent->right == to_replace)
    {
        to_replace->parent->right = replacement;
    }

    if (replacement)
    {
        replacement->parent = to_replace->parent;
    }
}

int remove_btree_tnode(BTree *tree, int index)
{
    TNode *target = search_btree(tree, index);
    if (!target)
    {
        return -1;
    }

    if (!target->left)
    {
        transplant_btree_node(tree, target, target->right);
    }
    else if (!target->right)
    {
        transplant_btree_node(tree, target, target->left);
    }
    else
    {
        // look for successor
        TNode *successor = target->right;
        while (successor->left)
        {
            successor = successor->left;
        }

        if (successor->parent != target)
        {
            transplant_btree_node(tree, successor, successor->right);

            successor->right = target->right;
            successor->right->parent = successor;
        }

        transplant_btree_node(tree, target, successor);

        successor->left = target->left;
        successor->left->parent = successor;
    }

    free(target);

    return index;
}

TNode *search_btree(BTree *tree, int index)
{
    if (!tree || !tree->root)
    {
        return NULL;
    }

    TNode *current = tree->root;
    while (current != NULL && current->index != index)
    {
        current = index < current->index ? current->left : current->right;
    }

    return current;
}

void free_btree(BTree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    free_tnode(tree->root);
    free(tree);
}

void free_tnode(TNode *node)
{
    if (node == NULL)
    {
        return;
    }

    free_tnode(node->left);
    free_tnode(node->right);
    free(node);
}