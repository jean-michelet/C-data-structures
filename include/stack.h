#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct stack {
    int *values;
    size_t limit;
    size_t index;
} Stack;

Stack* init_stack(size_t size);
Stack* push(Stack* stack, int value);
int pop(Stack* stack);
void freeStack(Stack *stack);
#endif
