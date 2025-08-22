#include "b_tree.h"
#include "test_runner.h"

void test_init_btree(void)
{
    BTree *tree = init_btree();
    ASSERT_TRUE(tree->root == NULL);

    tree->root = create_tnode(2, "Jean",
                              create_tnode(1, "Anthony", NULL, NULL),
                              create_tnode(3, "Mark", NULL, NULL));

    ASSERT_TRUE(tree->root->index == 2);
    ASSERT_STR_EQ(tree->root->name, "Jean");

    ASSERT_TRUE(tree->root->left->index == 1);
    ASSERT_STR_EQ(tree->root->left->name, "Anthony");

    ASSERT_TRUE(tree->root->right->index == 3);
    ASSERT_STR_EQ(tree->root->right->name, "Mark");

    free_btree(tree);
}

void test_search_btree(void)
{
    BTree *tree = init_btree();
    tree->root = create_tnode(5, "Anthony",
                              create_tnode(2, "Jean", NULL, NULL),
                              create_tnode(10, "Mark",
                                           create_tnode(7, "Paul", NULL, NULL),
                                           create_tnode(12, "Adam", NULL, NULL)));

    ASSERT_STR_EQ(search_btree(tree, 2)->name, "Jean");
    ASSERT_STR_EQ(search_btree(tree, 5)->name, "Anthony");
    ASSERT_STR_EQ(search_btree(tree, 10)->name, "Mark");
    ASSERT_STR_EQ(search_btree(tree, 7)->name, "Paul");
    ASSERT_STR_EQ(search_btree(tree, 12)->name, "Adam");

    free_btree(tree);
}

void test_insert_tnode_left(void)
{
    BTree *tree = init_btree();

    TNode *node = insert_btree_tnode(tree, 10, "Jack");
    ASSERT_STR_EQ(node->name, "Jack");
    ASSERT_STR_EQ(search_btree(tree, 10)->name, "Jack");

    node = insert_btree_tnode(tree, 5, "Antoine");
    ASSERT_STR_EQ(node->name, "Antoine");
    ASSERT_STR_EQ(tree->root->left->name, "Antoine");
    ASSERT_STR_EQ(search_btree(tree, 5)->name, "Antoine");

    node = insert_btree_tnode(tree, 2, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->left->left->name, "Camille");
    ASSERT_STR_EQ(search_btree(tree, 2)->name, "Camille");

    free_btree(tree);
}

void test_insert_tnode_right(void)
{
    BTree *tree = init_btree();

    TNode *node = insert_btree_tnode(tree, 10, "Jack");
    ASSERT_STR_EQ(node->name, "Jack");
    ASSERT_STR_EQ(search_btree(tree, 10)->name, "Jack");

    node = insert_btree_tnode(tree, 15, "Antoine");
    ASSERT_STR_EQ(node->name, "Antoine");
    ASSERT_STR_EQ(tree->root->right->name, "Antoine");
    ASSERT_STR_EQ(search_btree(tree, 15)->name, "Antoine");

    node = insert_btree_tnode(tree, 20, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->right->right->name, "Camille");
    ASSERT_STR_EQ(search_btree(tree, 20)->name, "Camille");

    free_btree(tree);
}

void test_insert_tnode_balanced(void)
{
    BTree *tree = init_btree();

    TNode *node = insert_btree_tnode(tree, 10, "Jack");
    ASSERT_STR_EQ(node->name, "Jack");
    ASSERT_STR_EQ(search_btree(tree, 10)->name, "Jack");

    node = insert_btree_tnode(tree, 5, "Antoine");
    ASSERT_STR_EQ(node->name, "Antoine");
    ASSERT_STR_EQ(tree->root->left->name, "Antoine");
    ASSERT_STR_EQ(search_btree(tree, 5)->name, "Antoine");

    node = insert_btree_tnode(tree, 15, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->right->name, "Camille");
    ASSERT_STR_EQ(search_btree(tree, 15)->name, "Camille");

    node = insert_btree_tnode(tree, 12, "Camille");
    ASSERT_STR_EQ(node->name, "Camille");
    ASSERT_STR_EQ(tree->root->right->left->name, "Camille");
    ASSERT_STR_EQ(search_btree(tree, 12)->name, "Camille");

    free_btree(tree);
}

void test_insert_tnode_existing_value(void)
{
    BTree *tree = init_btree();

    insert_btree_tnode(tree, 10, "Jack");
    ASSERT_STR_EQ(search_btree(tree, 10)->name, "Jack");

    ASSERT_TRUE(insert_btree_tnode(tree, 10, "Jack") == NULL);

    insert_btree_tnode(tree, 12, "Paul");
    ASSERT_STR_EQ(search_btree(tree, 12)->name, "Paul");
    ASSERT_TRUE(insert_btree_tnode(tree, 12, "Paul") == NULL);

    free_btree(tree);
}

void test_remove_null_tree(void)
{
    BTree *tree = NULL;

    ASSERT_TRUE(remove_btree_tnode(tree, 10) == -1);
}

void test_remove_null_root(void)
{
    BTree *tree = init_btree();

    ASSERT_TRUE(remove_btree_tnode(tree, 10) == -1);
    free_btree(tree);
}

void test_remove_root_whithout_children(void)
{
    BTree *tree = init_btree();
    insert_btree_tnode(tree, 10, "Jack");
    ASSERT_TRUE(remove_btree_tnode(tree, 10) == 10);
    ASSERT_TRUE(search_btree(tree, 10) == NULL);
    free_btree(tree);
}

void test_remove_not_root_whithout_children(void)
{
    BTree *tree = init_btree();
    insert_btree_tnode(tree, 10, "Pierre");
    insert_btree_tnode(tree, 5, "Paul");
    insert_btree_tnode(tree, 15, "Jack");

    ASSERT_TRUE(remove_btree_tnode(tree, 5) == 5);
    ASSERT_TRUE(search_btree(tree, 5) == NULL);
    ASSERT_TRUE(remove_btree_tnode(tree, 15) == 15);
    ASSERT_TRUE(search_btree(tree, 15) == NULL);
    free_btree(tree);
}

void test_remove_root_whith_one_child(void)
{
    // 1 - target is an orphan left node
    BTree *tree = init_btree();
    insert_btree_tnode(tree, 10, "Pierre");
    TNode *paul = insert_btree_tnode(tree, 5, "Paul");

    ASSERT_TRUE(remove_btree_tnode(tree, 10) == 10);
    ASSERT_TRUE(search_btree(tree, 10) == NULL);
    ASSERT_TRUE(tree->root == paul);

    free_btree(tree);

    // 2 - target is an orphan right node
    tree = init_btree();
    insert_btree_tnode(tree, 10, "Pierre");
    paul = insert_btree_tnode(tree, 15, "Paul");

    ASSERT_TRUE(remove_btree_tnode(tree, 10) == 10);
    ASSERT_TRUE(search_btree(tree, 10) == NULL);
    ASSERT_TRUE(tree->root == paul);

    free_btree(tree);
}

void test_remove_not_root_whith_one_child(void)
{
    // 1 - target is an orphan left node
    BTree *tree = init_btree();
    TNode *pierre = insert_btree_tnode(tree, 10, "Pierre");
    insert_btree_tnode(tree, 5, "Thomas");
    TNode *jack = insert_btree_tnode(tree, 15, "Jack");
    TNode *paul = insert_btree_tnode(tree, 12, "Paul");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(remove_btree_tnode(tree, 15) == 15);
    ASSERT_TRUE(search_btree(tree, 15) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == paul);
    ASSERT_TRUE(paul->parent == pierre);

    free_btree(tree);

    // 2 - target is an orphan right node
    tree = init_btree();
    pierre = insert_btree_tnode(tree, 10, "Pierre");
    insert_btree_tnode(tree, 5, "Paul");
    jack = insert_btree_tnode(tree, 15, "Jack");
    paul = insert_btree_tnode(tree, 17, "Paul");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(remove_btree_tnode(tree, 15) == 15);
    ASSERT_TRUE(search_btree(tree, 15) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == paul);
    ASSERT_TRUE(paul->parent == pierre);

    free_btree(tree);
}

void test_remove_not_root_with_children_successor_beeing_child(void)
{
    BTree *tree = init_btree();
    TNode *pierre = insert_btree_tnode(tree, 10, "Pierre");
    insert_btree_tnode(tree, 5, "Paul");
    TNode *jack = insert_btree_tnode(tree, 15, "Jack");
    TNode *adam = insert_btree_tnode(tree, 12, "Adam");
     // Right child not having left child = direct successor of its parent
    TNode *thomas = insert_btree_tnode(tree, 17, "Thomas");

    // before replacement
    ASSERT_TRUE(tree->root == pierre);
    ASSERT_TRUE(pierre->right == jack);

    ASSERT_TRUE(jack->right == thomas);
    ASSERT_TRUE(thomas->parent == jack);

    ASSERT_TRUE(jack->left == adam);
    ASSERT_TRUE(adam->parent == jack);

    ASSERT_TRUE(remove_btree_tnode(tree, 15) == 15);
    ASSERT_TRUE(search_btree(tree, 15) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == thomas);
    ASSERT_TRUE(thomas->parent == pierre);
    ASSERT_TRUE(thomas->left == adam);
    ASSERT_TRUE(adam->parent == thomas);

    free_btree(tree);
}

void test_remove_not_root_with_children_with_nested_successor(void)
{
    BTree *tree = init_btree();
    TNode *pierre = insert_btree_tnode(tree, 10, "Pierre");
    insert_btree_tnode(tree, 5, "Paul");
    TNode *jack = insert_btree_tnode(tree, 20, "Jack");
    TNode *adam = insert_btree_tnode(tree, 12, "Adam");
    TNode *thomas = insert_btree_tnode(tree, 25, "Thomas");
    TNode *franck = insert_btree_tnode(tree, 23, "Franck");
    TNode *anna = insert_btree_tnode(tree, 24, "Anna");

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

    ASSERT_TRUE(remove_btree_tnode(tree, 20) == 20);
    ASSERT_TRUE(search_btree(tree, 20) == NULL);

    // after replacement
    ASSERT_TRUE(pierre->right == franck);
    ASSERT_TRUE(franck->parent == pierre);

    ASSERT_TRUE(franck->left == adam);
    ASSERT_TRUE(adam->parent == franck);

    ASSERT_TRUE(franck->right == thomas);
    ASSERT_TRUE(thomas->parent == franck);

    ASSERT_TRUE(thomas->left == anna);
    ASSERT_TRUE(anna->parent == thomas);

    free_btree(tree);
}

void run_btree_tests(void)
{
    test_init_btree();
    test_search_btree();
    test_insert_tnode_left();
    test_insert_tnode_right();
    test_insert_tnode_balanced();
    test_insert_tnode_existing_value();
    test_remove_null_tree();
    test_remove_null_root();
    test_remove_root_whithout_children();
    test_remove_not_root_whithout_children();
    test_remove_root_whith_one_child();
    test_remove_not_root_whith_one_child();
    test_remove_not_root_with_children_successor_beeing_child();
    test_remove_not_root_with_children_with_nested_successor();
}
