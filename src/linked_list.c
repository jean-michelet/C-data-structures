#include "linked_list.h"
#include <stdlib.h>


Node* init_node()
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;

    return node;
}

Node *insert(Node *head, int value, size_t index)
{
    if (index == 0)
    {
        Node *new_head = init_node();
        if (!new_head)
        {
            return NULL;
        }

        new_head->value = value;
        new_head->next = head;

        return new_head;
    }

    Node *current = head;
    Node *previous = NULL;
    size_t count = 0;
    while (count < index && current != NULL)
    {
        previous = current;
        current = current->next;
        count++;
    }

    if (!current)
    {
        return NULL;
    }

    Node *node = init_node();
    if (!node)
    {
        return NULL;
    }

    node->value = value;
    node->next = previous->next;
    previous->next = node;

    return head;
}

Node *remove_node(Node *head, int value)
{
    if (head->value == value)
    {
        Node *new_head = head->next;
        free(head);
        return new_head;
    }

    Node *current = head;
    Node *previous = NULL;
    while (current != NULL && current->value != value)
    {
        previous = current;
        current = current->next;
    }

    if (!current)
    {
        return NULL;
    }

    previous->next = current->next;
    free(current);

    return head;
}

void free_linked_list(Node* head)
{
    Node* current = head;
    Node* previous = NULL;
    while(current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }

    free(current);
}
