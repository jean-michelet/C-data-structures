#include "insertion_sort.h"
#include "test_runner.h"
#include "arrays_equal.h"

void test_sorts_correctly(void) {
    {
        int arr[] = {3, 2, 1};
        int expect[] = {1, 2, 3};
        insertion_sort(arr, 3);
        ASSERT_TRUE(arrays_equal(arr, expect, 3));
    }
    {
        int arr[] = {2, 3, 1, 4, 2};
        int expect[] = {1, 2, 2, 3, 4};
        insertion_sort(arr, 5);
        ASSERT_TRUE(arrays_equal(arr, expect, 5));
    }
    {
        int arr[] = {1};
        int expect[] = {1};
        insertion_sort(arr, 1);
        ASSERT_TRUE(arrays_equal(arr, expect, 1));
    }
    {
        int arr[] = {};
        insertion_sort(arr, 0);
        ASSERT_TRUE(arrays_equal(arr, NULL, 0));
    }
}

void test_does_not_mutate_original(void) {
    int original[] = {3, 2, 1};
    int snapshot[] = {3, 2, 1};

    int copy[3];
    for (size_t i = 0; i < 3; ++i) copy[i] = original[i];

    insertion_sort(copy, 3);

    ASSERT_TRUE(arrays_equal(original, snapshot, 3));
}

void run_insertion_sort_tests(void) {
    test_sorts_correctly();
    test_does_not_mutate_original();
}
