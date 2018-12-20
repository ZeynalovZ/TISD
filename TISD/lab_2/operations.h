#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__
#include "io.h"
int show_table(void);

int delete_line(user *base, int *count);

int add_line(user *base, int count);

void bubble_keys(key *keys, int count);

void bubble_sort_table(user *base, int count);

unsigned long long tick(void);

void time_table(user *table, key *keys, int count);
void print_table_by_keys(user *base, key *keys, int count);
void time_keys(user *table, key *keys, int count);
#endif
