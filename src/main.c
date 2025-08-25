#include <stdio.h>
#include "b_tree.h"

int main(void) {
    // Initialize an empty tree
    BinarySearchTree *tree = init_bst();

    // Insert some nodes
    insert_bst_node(tree, 10, "Pierre");
    insert_bst_node(tree, 5, "Paul");
    insert_bst_node(tree, 15, "Jack");
    insert_bst_node(tree, 3, "Anna");
    insert_bst_node(tree, 7, "Marie");
    insert_bst_node(tree, 12, "Sophie");
    insert_bst_node(tree, 18, "Jean");

    printf("Binary Tree structure:\n");
    print_tree(tree);

    // Search a node
    int key = 7;
    BSTNode *found = search_bst(tree, key);
    if (found) {
        printf("\nFound node with index %d: %s\n", key, found->name);
    } else {
        printf("\nNode with index %d not found.\n", key);
    }

    // Remove a node
    printf("\nRemoving node with index 15 (Jack)...\n");
    remove_bst_node(tree, 15);
    print_tree(tree);

    // Free all allocated memory
    free_bst(tree);

    return 0;
}
