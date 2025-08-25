#include "binary_search_tree.h"
#include "test_runner.h"

void test_init_bst(void)
{
    BinarySearchTree *tree = init_bst();
    ASSERT_TRUE(tree->root == NULL);

    tree->root = create_bst_node(2, "Jean",
                              create_bst_node(1, "Anthony", NULL, NULL),
                              create_bst_node(3, "Mark", NULL, NULL));

    ASSERT_TRUE(tree->root->index == 2);
    ASSERT_STR_EQ(tree->root->name, "Jean");

    ASSERT_TRUE(tree->root->left->index == 1);
    ASSERT_STR_EQ(tree->root->left->name, "Anthony");

    ASSERT_TRUE(tree->root->right->index == 3);
    ASSERT_STR_EQ(tree->root->right->name, "Mark");

    free_bst(tree);
}

void test_search_bst(void)
{
    BinarySearchTree *tree = init_bst();
    tree->root = create_bst_node(5, "Anthony",
                              create_bst_node(2, "Jean", NULL, NULL),
                              create_bst_node(10, "Mark",
                                           create_bst_node(7, "Paul", NULL, NULL),
                                           create_bst_node(12, "Adam", NULL, NULL)));

    ASSERT_STR_EQ(search_bst(tree, 2)->name, "Jean");
    ASSERT_STR_EQ(search_bst(tree, 5)->name, "Anthony");
    ASSERT_STR_EQ(search_bst(tree, 10)->name, "Mark");
    ASSERT_STR_EQ(search_bst(tree, 7)->name, "Paul");
    ASSERT_STR_EQ(search_bst(tree, 12)->name, "Adam");

    free_bst(tree);
}

void test_insert_node_left(void)
{
    BinarySearchTree *tree = init_bst();

    BSTNode *node = insert_bst_node(tree, 10, "Jack");
    ASSERT_STR_EQ(node->name, "Jack");
    ASSERT_STR_EQ(search_bst(tree, 10)->name, "Jack");

    node = insert_bst_node(tree, 5, "Antoine");
    ASSERT_STR_EQ(node->name, "Antoine");
    ASSERT_STR_EQ(tree->root->left->name, "Antoine");
    ASSERT_STR_EQ(search_bst(tree, 5)->name, "Antoine");

    node = insert_bst_node(tree, 2, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->left->left->name, "Camille");
    ASSERT_STR_EQ(search_bst(tree, 2)->name, "Camille");

    free_bst(tree);
}

void test_insert_node_right(void)
{
    BinarySearchTree *tree = init_bst();

    BSTNode *node = insert_bst_node(tree, 10, "Jack");
    ASSERT_STR_EQ(node->name, "Jack");
    ASSERT_STR_EQ(search_bst(tree, 10)->name, "Jack");

    node = insert_bst_node(tree, 15, "Antoine");
    ASSERT_STR_EQ(node->name, "Antoine");
    ASSERT_STR_EQ(tree->root->right->name, "Antoine");
    ASSERT_STR_EQ(search_bst(tree, 15)->name, "Antoine");

    node = insert_bst_node(tree, 20, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->right->right->name, "Camille");
    ASSERT_STR_EQ(search_bst(tree, 20)->name, "Camille");

    free_bst(tree);
}

void test_insert_node_balanced(void)
{
    BinarySearchTree *tree = init_bst();

    BSTNode *node = insert_bst_node(tree, 10, "Jack");
    ASSERT_STR_EQ(node->name, "Jack");
    ASSERT_STR_EQ(search_bst(tree, 10)->name, "Jack");

    node = insert_bst_node(tree, 5, "Antoine");
    ASSERT_STR_EQ(node->name, "Antoine");
    ASSERT_STR_EQ(tree->root->left->name, "Antoine");
    ASSERT_STR_EQ(search_bst(tree, 5)->name, "Antoine");

    node = insert_bst_node(tree, 15, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->right->name, "Camille");
    ASSERT_STR_EQ(search_bst(tree, 15)->name, "Camille");

    node = insert_bst_node(tree, 12, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->right->left->name, "Camille");
    ASSERT_STR_EQ(search_bst(tree, 12)->name, "Camille");

    free_bst(tree);
}

void test_insert_node_existing_value(void)
{
    BinarySearchTree *tree = init_bst();

    insert_bst_node(tree, 10, "Jack");
    ASSERT_STR_EQ(search_bst(tree, 10)->name, "Jack");

    ASSERT_TRUE(insert_bst_node(tree, 10, "Jack") == NULL);

    insert_bst_node(tree, 12, "Paul");
    ASSERT_STR_EQ(search_bst(tree, 12)->name, "Paul");
    ASSERT_TRUE(insert_bst_node(tree, 12, "Paul") == NULL);

    free_bst(tree);
}

void test_remove_null_tree(void)
{
    BinarySearchTree *tree = NULL;

    ASSERT_TRUE(remove_bst_node(tree, 10) == -1);
}

void test_remove_null_root(void)
{
    BinarySearchTree *tree = init_bst();

    ASSERT_TRUE(remove_bst_node(tree, 10) == -1);
    free_bst(tree);
}

void test_remove_root_whithout_children(void)
{
    BinarySearchTree *tree = init_bst();
    insert_bst_node(tree, 10, "Jack");
    ASSERT_TRUE(remove_bst_node(tree, 10) == 10);
    ASSERT_TRUE(search_bst(tree, 10) == NULL);
    free_bst(tree);
}

void test_remove_not_root_whithout_children(void)
{
    BinarySearchTree *tree = init_bst();
    insert_bst_node(tree, 10, "Pierre");
    insert_bst_node(tree, 5, "Paul");
    insert_bst_node(tree, 15, "Jack");

    ASSERT_TRUE(remove_bst_node(tree, 5) == 5);
    ASSERT_TRUE(search_bst(tree, 5) == NULL);
    ASSERT_TRUE(remove_bst_node(tree, 15) == 15);
    ASSERT_TRUE(search_bst(tree, 15) == NULL);
    free_bst(tree);
}

void test_remove_root_whith_one_child(void)
{
    // 1 - target is an orphan left node
    BinarySearchTree *tree = init_bst();
    insert_bst_node(tree, 10, "Pierre");
    BSTNode *paul = insert_bst_node(tree, 5, "Paul");

    ASSERT_TRUE(remove_bst_node(tree, 10) == 10);
    ASSERT_TRUE(search_bst(tree, 10) == NULL);
    ASSERT_TRUE(tree->root == paul);

    free_bst(tree);

    // 2 - target is an orphan right node
    tree = init_bst();
    insert_bst_node(tree, 10, "Pierre");
    paul = insert_bst_node(tree, 15, "Paul");

    ASSERT_TRUE(remove_bst_node(tree, 10) == 10);
    ASSERT_TRUE(search_bst(tree, 10) == NULL);
    ASSERT_TRUE(tree->root == paul);

    free_bst(tree);
}

void test_remove_not_root_whith_one_child(void)
{
    // 1 - target is an orphan left node
    BinarySearchTree *tree = init_bst();
    BSTNode *pierre = insert_bst_node(tree, 10, "Pierre");
    insert_bst_node(tree, 5, "Thomas");
    BSTNode *jack = insert_bst_node(tree, 15, "Jack");
    BSTNode *paul = insert_bst_node(tree, 12, "Paul");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(remove_bst_node(tree, 15) == 15);
    ASSERT_TRUE(search_bst(tree, 15) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == paul);
    ASSERT_TRUE(paul->parent == pierre);

    free_bst(tree);

    // 2 - target is an orphan right node
    tree = init_bst();
    pierre = insert_bst_node(tree, 10, "Pierre");
    insert_bst_node(tree, 5, "Paul");
    jack = insert_bst_node(tree, 15, "Jack");
    paul = insert_bst_node(tree, 17, "Paul");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(remove_bst_node(tree, 15) == 15);
    ASSERT_TRUE(search_bst(tree, 15) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == paul);
    ASSERT_TRUE(paul->parent == pierre);

    free_bst(tree);
}

void test_remove_not_root_with_children_successor_beeing_child(void)
{
    BinarySearchTree *tree = init_bst();
    BSTNode *pierre = insert_bst_node(tree, 10, "Pierre");
    insert_bst_node(tree, 5, "Paul");
    BSTNode *jack = insert_bst_node(tree, 15, "Jack");
    BSTNode *adam = insert_bst_node(tree, 12, "Adam");
     // Right child not having left child = direct successor of its parent
    BSTNode *thomas = insert_bst_node(tree, 17, "Thomas");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(jack->right == thomas);
    ASSERT_TRUE(thomas->parent == jack);

    ASSERT_TRUE(jack->left == adam);
    ASSERT_TRUE(adam->parent == jack);

    ASSERT_TRUE(remove_bst_node(tree, 15) == 15);
    ASSERT_TRUE(search_bst(tree, 15) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == thomas);
    ASSERT_TRUE(thomas->parent == pierre);
    ASSERT_TRUE(thomas->left == adam);
    ASSERT_TRUE(adam->parent == thomas);

    free_bst(tree);
}

void test_remove_not_root_with_children_with_nested_successor(void)
{
    BinarySearchTree *tree = init_bst();
    BSTNode *pierre = insert_bst_node(tree, 10, "Pierre");
    insert_bst_node(tree, 5, "Paul");
    BSTNode *jack = insert_bst_node(tree, 20, "Jack");
    BSTNode *adam = insert_bst_node(tree, 12, "Adam");
    BSTNode *thomas = insert_bst_node(tree, 25, "Thomas");
    BSTNode *franck = insert_bst_node(tree, 23, "Franck");
    BSTNode *anna = insert_bst_node(tree, 24, "Anna");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(jack->right == thomas);
    ASSERT_TRUE(thomas->parent == jack);
    ASSERT_TRUE(thomas->left == franck);
    ASSERT_TRUE(franck->parent == thomas);
    ASSERT_TRUE(franck->right == anna);
    ASSERT_TRUE(anna->parent == franck);

    ASSERT_TRUE(jack->left == adam);
    ASSERT_TRUE(adam->parent == jack);

    ASSERT_TRUE(remove_bst_node(tree, 20) == 20);
    ASSERT_TRUE(search_bst(tree, 20) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == franck);
    ASSERT_TRUE(franck->parent == pierre);

    ASSERT_TRUE(franck->left == adam);
    ASSERT_TRUE(adam->parent == franck);

    ASSERT_TRUE(franck->right == thomas);
    ASSERT_TRUE(thomas->parent == franck);

    ASSERT_TRUE(thomas->left == anna);
    ASSERT_TRUE(anna->parent == thomas);

    free_bst(tree);
}

void run_bst_tests(void)
{
    test_init_bst();
    test_search_bst();
    test_insert_node_left();
    test_insert_node_right();
    test_insert_node_balanced();
    test_insert_node_existing_value();
    test_remove_null_tree();
    test_remove_null_root();
    test_remove_root_whithout_children();
    test_remove_not_root_whithout_children();
    test_remove_root_whith_one_child();
    test_remove_not_root_whith_one_child();
    test_remove_not_root_with_children_successor_beeing_child();
    test_remove_not_root_with_children_with_nested_successor();
}
