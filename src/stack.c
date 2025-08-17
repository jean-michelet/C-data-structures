#include "stack.h"

Stack *init_stack(size_t limit)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->values = malloc(limit * sizeof(int));
    stack->limit = limit;
    stack->index = 0;

    return stack;
}

Stack *push(Stack *stack, int value)
{
    if (stack->index == stack->limit)
    {
        return NULL;
    }

    stack->values[stack->index++] = value;

    return stack;
}

int pop(Stack *stack)
{
    if (stack->index == 0) {
        return -1;
    }

    int value = stack->values[--stack->index];

    return value;
}

void freeStack(Stack *stack)
{
    free(stack->values);
    free(stack);
}