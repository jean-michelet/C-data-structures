#include "queue.h"
#include "test_runner.h"
#include <stdlib.h>

void test_init_queue(void)
{
    Queue *queue = init_queue();

    ASSERT_TRUE(queue->front == NULL);
    ASSERT_TRUE(queue->back == NULL);
    freeQueue(queue);
}

void test_enqueue(void)
{
    Queue *queue = init_queue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    ASSERT_TRUE(queue->front->value == 1);
    ASSERT_TRUE(queue->front->next->value == 2);
    ASSERT_TRUE(queue->front->next->next->value == 3);
    ASSERT_TRUE(queue->back->value == 3);
    freeQueue(queue);
}

void test_dequeue(void)
{
    Queue *queue = init_queue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    ASSERT_TRUE(dequeue(queue) == 1);
    ASSERT_TRUE(dequeue(queue) == 2);
    ASSERT_TRUE(dequeue(queue) == 3);
    ASSERT_TRUE(dequeue(queue) == -1);
    freeQueue(queue);
}


void run_queue_tests(void)
{
    test_init_queue();
    test_enqueue();
}
