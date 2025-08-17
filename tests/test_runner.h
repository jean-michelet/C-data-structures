#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <stdio.h>

extern int tests_run;
extern int tests_failed;

#define ASSERT_TRUE(expr) do {                                                    \
    ++tests_run;                                                                  \
    if (!(expr)) {                                                                \
        ++tests_failed;                                                           \
        fprintf(stderr, "Assertion failed: %s (%s:%d)\n", #expr, __FILE__, __LINE__); \
    }                                                                             \
} while(0)

#endif
