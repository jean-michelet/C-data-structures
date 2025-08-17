#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "linked_list.h"

typedef struct Queue
{
    struct Node *front;
    struct Node *back;
} Queue;

Queue* init_queue();
Queue* enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
void freeQueue(Queue *queue);
#endif
