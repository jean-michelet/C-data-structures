#include "str_equals.h"

bool str_equals(const char *left, const char *right)
{
    if (left == NULL || right == NULL)
    {
        return false;
    }

    size_t lenL = strlen(left);
    size_t lenR = strlen(right);
    if (lenL != lenR)
    {
        return false;
    }

    for (size_t i = 0; i < lenL; ++i)
    {
        if (left[i] != right[i])
        {
            return false;
        }
    }

    return true;
}
