#include "linked_list.h"
#include "test_runner.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

Node *create_node(int value, Node *next)
{
    Node *node = init_node();
    node->value = value;
    node->next = next;

    return node;
}

void test_create_node(void)
{
    Node *head = create_node(1, create_node(3, NULL));

    ASSERT_TRUE(head->value == 1);
    ASSERT_TRUE(head->next->value == 3);
    free_linked_list(head);
}

void test_insert_new_head(void)
{
    Node *head = create_node(1, create_node(3, NULL));
    Node *new_head = insert(head, 5, 0);

    ASSERT_TRUE(new_head->value == 5);
    ASSERT_TRUE(new_head->next->value == 1);
    ASSERT_TRUE(new_head->next->next->value == 3);
    free_linked_list(new_head);
}

void test_insert_out_of_range(void)
{
    Node *head = create_node(1, create_node(3, NULL));
    Node *new_head = insert(head, 5, 4);

    ASSERT_TRUE(new_head == NULL);
    free_linked_list(head);
}

void test_insert(void)
{
    Node *head = create_node(1, create_node(3, NULL));
    Node *new_head = insert(head, 5, 1);

    ASSERT_TRUE(new_head->value == 1);
    ASSERT_TRUE(new_head->next->value == 5);
    ASSERT_TRUE(new_head->next->next->value == 3);
    free_linked_list(new_head);
}

void test_remove_first(void)
{
    Node *head = create_node(1, create_node(3, create_node(5, NULL)));
    Node *new_head = remove_node(head, 1);

    ASSERT_TRUE(new_head->value == 3);
    ASSERT_TRUE(new_head->next->value == 5);
    free_linked_list(new_head);
}

void test_remove(void)
{
    Node *head = create_node(1, create_node(3, create_node(5, NULL)));
    Node *new_head = remove_node(head, 3);

    ASSERT_TRUE(new_head->value == 1);
    ASSERT_TRUE(new_head->next->value == 5);
    free_linked_list(new_head);
}

void test_remove_end(void)
{
    Node *head = create_node(1, create_node(3, create_node(5, NULL)));
    Node *new_head = remove_node(head, 5);

    ASSERT_TRUE(new_head->value == 1);
    ASSERT_TRUE(new_head->next->value == 3);
    free_linked_list(new_head);
}

void run_linked_list_tests(void)
{
    test_create_node();
    test_insert_new_head();
    test_insert_out_of_range();
    test_insert();
    test_remove_first();
    test_remove_end();
    test_remove();
}
