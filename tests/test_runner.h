#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <stdio.h>
#include <string.h> 

extern int tests_run;
extern int tests_failed;

#define ASSERT_TRUE(expr)                                                                 \
    do                                                                                    \
    {                                                                                     \
        ++tests_run;                                                                      \
        if (!(expr))                                                                      \
        {                                                                                 \
            ++tests_failed;                                                               \
            fprintf(stderr, "Assertion failed: %s (%s:%d)\n", #expr, __FILE__, __LINE__); \
        }                                                                                 \
    } while (0)

#define ASSERT_STR_EQ(expected, actual)                                     \
    do                                                                      \
    {                                                                       \
        ++tests_run;                                                        \
        const char *exp_str = (expected);                                   \
        const char *act_str = (actual);                                     \
        if (((exp_str) == NULL && (act_str) != NULL) ||                     \
            ((exp_str) != NULL && (act_str) == NULL) ||                     \
            ((exp_str) && (act_str) && strcmp((exp_str), (act_str)) != 0))  \
        {                                                                   \
            ++tests_failed;                                                 \
            fprintf(stderr, "Assertion failed: strings not equal (%s:%d)\n" \
                            "  expected: \"%s\"\n  actual:   \"%s\"\n",     \
                    __FILE__, __LINE__,                                     \
                    exp_str ? exp_str : "(null)",                           \
                    act_str ? act_str : "(null)");                          \
        }                                                                   \
    } while (0)

#endif
