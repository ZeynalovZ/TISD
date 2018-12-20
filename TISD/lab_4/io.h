#ifndef __IO_H__
#define __IO_H__
#include "list.h"
int user_input(int *choice);
void err_output(int err_type);
void print_arr(base *array, int readed_count);
int read_expression(base *array, unsigned *count_readed);
int user_input_type(int *choice);
void print_array(void **array, int count);
#endif
