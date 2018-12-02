#include <stdio.h>

#include "arr.h"
#include "err.h"
// Проверять на пустой список в вызывающей стороне
int arr_push(double **pin, double *begin, double time)
{
    if (*pin == NULL || begin == NULL)
    {
        return ERR_NULL;
    }
    **pin = time;
    *pin += 1;
    if (*pin == begin + SIZE)
    {
        *pin = begin;
    }
    return OK;
}

int arr_pop(double **pout, double *begin)
{
    if (*pout == NULL || begin == NULL)
    {
        return ERR_NULL;
    }
    *pout += 1;
    if (*pout == begin + SIZE)
    {
        *pout = begin;
    }
    return OK;
}
