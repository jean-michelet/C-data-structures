#include <stdio.h>

#define ANSI_RESET "\033[0m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"

int tests_run = 0;
int tests_failed = 0;

void run_str_equals_tests(void);
void run_insertion_sort_tests(void);
void run_linked_list_tests(void);
void run_stack_tests(void);
void run_queue_tests(void);
void run_btree_tests(void);

int main(void)
{
    run_str_equals_tests();
    run_insertion_sort_tests();
    run_linked_list_tests();
    run_stack_tests();
    run_queue_tests();
    run_btree_tests();

    if (tests_failed == 0)
    {
        printf(ANSI_GREEN "\nAll tests passed (%d assertions).\n\n" ANSI_RESET, tests_run);
        return 0;
    }
    else
    {
        fprintf(stderr, ANSI_RED "\n%d/%d assertions failed.\n\n" ANSI_RESET,
                tests_failed, tests_run);
        return 1;
    }
}
