#include <stdlib.h>
#include <stdbool.h>
#include "arrays_equal.h"

bool arrays_equal(const int *a, const int *b, size_t n)
{
    if (n == 0)
    {
        return true;
    }

    if (a == NULL || b == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < n; ++i)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    
    return true;
}