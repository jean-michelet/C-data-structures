#include "queue.h"

Queue *init_queue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;

    return queue;
}

/*
Understanding enqueue step by step (using p1, p3, p7 as new nodes):

enqueue(1)
    queue->front = p1
    queue->back  = p1

enqueue(3)
    queue->back->next = p3    // p1->next = p3
    queue->back = p3          // back now points to p3
    front still points to p1, but p1->next = p3

enqueue(7)
    queue->back->next = p7    // p3->next = p7
    queue->back = p7          // back now points to p7
    front still points to p1, but we can reach the chain p1->p3->p7
*/
Queue *enqueue(Queue *queue, int value)
{
    Node *node = init_node();
    node->value = value;
    if (queue->back == NULL)
    {
        queue->back = node;
        queue->front = node;
    }
    else
    {
        queue->back->next = node;
        queue->back = node;
    }

    return queue;
}

int dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        return -1;
    }

    int value = queue->front->value;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        free(queue->back);
        queue->back = NULL;
    }

    return value;
}

void freeQueue(Queue *queue)
{
    free_linked_list(queue->front);
    free(queue);
}
