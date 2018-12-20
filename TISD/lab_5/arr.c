#include <stdio.h>
#include "list.h"
#include "arr.h"
#include "err.h"
// Проверять на пустой список в вызывающей стороне
int arr_push(QUEUE **pin, QUEUE *pout, QUEUE *begin, int entries_count)
{
    if (*pin == NULL || begin == NULL)
    {
        return ERR_NULL;
    }
    (**pin).entry = entries_count;
    *pin += 1;
    if (*pin == pout)
    {
        return ERR_FULL;
    }
    if (*pin == begin + SIZE)
    {
        *pin = begin;
    }
    return OK;
}

int arr_pop(QUEUE **pout, QUEUE *begin, int *entries_count)
{
    if (*pout == NULL || begin == NULL)
    {
        return ERR_NULL;
    }
    *entries_count = (**pout).entry;
    *pout += 1;
    if (*pout == begin + SIZE)
    {
        *pout = begin;
    }
    return OK;
}
