#include "binary_search_tree.h"
#include <stdio.h>

BinarySearchTree *init_bst()
{
    BinarySearchTree *tree = malloc(sizeof(BinarySearchTree));
    tree->root = NULL;

    return tree;
}

BSTNode *create_bst_node(int index, const char *name, BSTNode *left, BSTNode *right)
{
    BSTNode *node = malloc(sizeof(BSTNode));
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

BSTNode *search_bst(BinarySearchTree *tree, int index)
{
    if (!tree || !tree->root)
    {
        return NULL;
    }

    BSTNode *current = tree->root;
    while (current != NULL && current->index != index)
    {
        current = index < current->index ? current->left : current->right;
    }

    return current;
}

BSTNode *insert_bst_node(BinarySearchTree *tree, int index, const char *name)
{
    if (tree->root == NULL)
    {
        tree->root = create_bst_node(index, name, NULL, NULL);
        return tree->root;
    }

    return insert_node(tree->root, index, name);
}

BSTNode *insert_node(BSTNode *parent, int index, const char *name)
{
    if (parent->index == index)
    {
        return NULL;
    }

    if (index < parent->index)
    {
        if (parent->left == NULL)
        {
            parent->left = create_bst_node(index, name, NULL, NULL);
            parent->left->parent = parent;
            return parent->left;
        }

        return insert_node(parent->left, index, name);
    }

    if (parent->right == NULL)
    {
        parent->right = create_bst_node(index, name, NULL, NULL);
        parent->right->parent = parent;
        return parent->right;
    }

    return insert_node(parent->right, index, name);
}

void transplant_bst_node(
    BinarySearchTree *tree,
    BSTNode *to_replace,
    BSTNode *replacement)
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

int remove_bst_node(BinarySearchTree *tree, int index)
{
    BSTNode *target = search_bst(tree, index);
    if (!target)
    {
        return -1;
    }

    if (!target->left)
    {
        transplant_bst_node(tree, target, target->right);
    }
    else if (!target->right)
    {
        transplant_bst_node(tree, target, target->left);
    }
    else
    {
        // look for successor
        BSTNode *successor = target->right;
        while (successor->left)
        {
            successor = successor->left;
        }

        if (successor->parent != target)
        {
            transplant_bst_node(tree, successor, successor->right);

            successor->right = target->right;
            successor->right->parent = successor;
        }

        transplant_bst_node(tree, target, successor);

        successor->left = target->left;
        successor->left->parent = successor;
    }

    free(target);

    return index;
}

void free_bst(BinarySearchTree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    free_node(tree->root);
    free(tree);
}

void free_node(BSTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    free_node(node->left);
    free_node(node->right);
    free(node);
}

void print_node(const BSTNode *node, int depth)
{
    if (!node)
        return;

    // Print right subst first
    print_node(node->right, depth + 1);

    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }

    printf("%d (%s)\n", node->index, node->name);

    // Print left subst
    print_node(node->left, depth + 1);
}

void print_tree(const BinarySearchTree *tree)
{
    if (!tree || !tree->root)
    {
        printf("(empty tree)\n");
        return;
    }
    print_node(tree->root, 0);
}