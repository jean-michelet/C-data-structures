#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node* insert(Node* head, int value, size_t index);
Node* remove_node(Node* head, int value);
void free_linked_list(Node* head);
#endif
