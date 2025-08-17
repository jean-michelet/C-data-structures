#include "insertion_sort.h"
#include <stdlib.h>

#include "insertion_sort.h"
#include <stddef.h>

void insertion_sort(int *arr, size_t n)
{
    if (arr == NULL || n <= 1)
    {
        return;
    }

    for (size_t i = 1; i < n; ++i)
    {
        int current = arr[i];
        ssize_t j = (ssize_t)i - 1;

        while (j >= 0 && arr[j] > current)
        {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = current;
    }
}
