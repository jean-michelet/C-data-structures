#include "stack.h"
#include "test_runner.h"

void test_init_stack(void)
{
    Stack *stack = init_stack(100);

    ASSERT_TRUE(stack->index == 0);
    ASSERT_TRUE(stack->limit == 100);
    freeStack(stack);
}

void test_push(void)
{
    Stack *stack = init_stack(10);
    push(stack, 1);
    push(stack, 3);

    ASSERT_TRUE(stack->values[0] == 1);
    ASSERT_TRUE(stack->values[1] == 3);
    freeStack(stack);
}

void test_push_out_of_limit(void)
{
    Stack *stack = init_stack(1);
    push(stack, 1);

    ASSERT_TRUE(push(stack, 2) == NULL);
    freeStack(stack);
}

void test_pop(void)
{
    Stack *stack = init_stack(10);
    push(stack, 1);
    push(stack, 3);
    push(stack, 5);

    ASSERT_TRUE(stack->index == 3);
    ASSERT_TRUE(pop(stack) == 5);
    ASSERT_TRUE(pop(stack) == 3);
    ASSERT_TRUE(pop(stack) == 1);
    ASSERT_TRUE(pop(stack) == -1);
    ASSERT_TRUE(stack->index == 0);
    freeStack(stack);
}

void run_stack_tests(void)
{
    test_init_stack();
    test_push();
    test_push_out_of_limit();
    test_pop();
}
