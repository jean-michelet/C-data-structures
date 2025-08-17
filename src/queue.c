#include "queue.h"

Queue *init_queue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;

    return queue;
}

Queue *enqueue(Queue *queue, int value)
{
    Node* node = init_node();
    node->value = value;
    if (queue->back == NULL) {
        queue->back = node;
        queue->front = node;
    } else {
        queue->back->next = node;
        queue->back = node;
    }

    return queue;
}

// Understanding the algorithm
// enqueue(1)
// back = p1
// front = p1

// enqueue(3)
// back(p1).next = p3, front(p1) is alias to back(p1), so front(p1).next = p3
// back(p1) = p3

// enqueue(7)
// back(p3).next = p7, front(p1).next(p3).next = p(7)
// back(p3) = p7

int dequeue(Queue *queue)
{
    if (queue->front == NULL) {
        return -1;
    }

    int value = queue->front->value;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
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
