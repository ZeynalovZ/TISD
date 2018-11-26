#ifndef __ARR_H__
#define __ARR_H__
#include "list.h"
void arr_push(base *array, unsigned *curr);
void arr_pop(base *array, unsigned *last);
int calculate_arr(base *array, int last, int *result);
#endif
