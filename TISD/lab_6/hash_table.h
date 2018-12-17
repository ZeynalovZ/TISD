#ifndef __HASH__TABLE__
#define __HASH__TABLE__
typedef struct TABLE table_t;
struct TABLE
{
    int n;
    int sign;
};
int create_table(table_t **table, char *filename, int *len);
void print_hash_table(table_t *table, int max);
int search_table(table_t *table, int size, int search);
#endif
