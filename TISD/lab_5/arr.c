#include <stdio.h>

#include "arr.h"
#include "err.h"
// Проверять на пустой список в вызывающей стороне
int arr_push(double **pin, double *begin, int entries_count)
{
    if (*pin == NULL || begin == NULL)
    {
        return ERR_NULL;
    }
    **pin = entries_count;
    *pin += 1;
    if (*pin == begin + SIZE)
    {
        *pin = begin;
    }
    return OK;
}

int arr_pop(double **pout, double *begin, int *entries_count)
{
    if (*pout == NULL || begin == NULL)
    {
        return ERR_NULL;
    }
    *entries_count = **pout;
    *pout += 1;
    if (*pout == begin + SIZE)
    {
        *pout = begin;
    }
    return OK;
}
