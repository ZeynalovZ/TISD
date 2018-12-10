#ifndef __ARR_H__
#define __ARR_H__
#include "list.h"
int arr_push(QUEUE **pin, QUEUE *pout, QUEUE *begin, int entries_count);
int arr_pop(QUEUE **pout, QUEUE *begin, int *entries_count);
#endif
