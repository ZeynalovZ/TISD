#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"
#include "err.h"
#define SHIFT 4

int hash_func(int num, int prime)
{
    return num % prime;
}

int select_prime(int max)
{
    // для упрощения алгоритма воспользуемся первыми 20 простыми числами
    //printf("max in func is %d\n", max);
    int prime_nums[20] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
    for (int i = 19; i >= 0; i--)
    {
        if (prime_nums[i] < max)
        {
            //printf("prime is %d", prime_nums[i]);
            return prime_nums[i];
        }
    }
    return max - 1;
}

int create_table(table_t **table, char *filename, int *len)
{
    FILE *f;
    f = fopen(filename, "r");
    if (!f)
        return ERR_IO;
    *table = NULL;
    int max = 0;
    int n;
    int count_nums_in_file = 0;
    if (fscanf(f, "%d", &n) == 1)
    {
        count_nums_in_file++;
        max = n;
    }
    while (fscanf(f, "%d", &n) == 1)
    {
        if (n > max)
        {
            max = n;
        }
        count_nums_in_file++;
    }
    //printf("1\n");
    if (count_nums_in_file != 0)
    {
        rewind(f);
        int index = 0;
        int prime = select_prime(count_nums_in_file);
        //printf("max is %d\n", max);
        table_t *tmp_table = malloc(count_nums_in_file * sizeof(table_t));
        //printf("sizeof is %I64d", sizeof(tmp_table));
        if (tmp_table != NULL)
        {
            for (int i = 0; i < max; i++)
            {
                tmp_table[i].sign = 0;
            }
            while (fscanf(f, "%d", &n) == 1 || !feof(f))
            {
                index = hash_func(n, prime);
                // Распишем закрытое хеширование
                if ((tmp_table[index]).sign != 0)
                {
                    while ((tmp_table[index].sign) != 0)
                    {
                        if (index == n)
                        {
                            index = 0;
                            continue;
                        }
                        index++;
                    }
                    tmp_table[index].n = n;
                    tmp_table[index].sign = 1;
                }
                else
                {
                    tmp_table[index].n = n;
                    tmp_table[index].sign = 1;
                }
            }
            *table = tmp_table;
        }
        else
        {
            return ERR_MEM;
        }
    }
    *len = count_nums_in_file;
    fclose(f);
    //printf("1\n");
    return OK;
}
int search_table(table_t *table, int size, int search)
{
    int cmp = 1;
    int prime = select_prime(size);
    int index = hash_func(search, prime);
    if (table[index].sign != 0 && table[index].n == search)
    {
        return cmp;
    }
    else if (table[index].sign != 0 && table[index].n != search)
    {
        while (table[index].sign != 0 && table[index].n != search)
        {
            cmp++;
            index++;
            if (index == size)
            {
                index = 0;
            }
        }
    }
    return cmp;
}
void print_hash_table(table_t *table, int max)
{
    printf("hash_table is:\n");
    for (int i = 0; i < max; i++)
    {
        printf("%4d ", i);
    }
    printf("\n");
    for (int i = 0; i < max; i++)
    {
        if (table[i].sign != 0)
        {
            printf("%4d ", (table[i]).n);
        }
        else
        {
            printf("     ");
        }
    }
    printf("\n");
}

int restruct(table_t *table, int n, int search, table_t **new_table, int *new_size, int max)
{
    *new_table = NULL;
    int cmp;
    int prime;
    int index;
    *new_size = n;
    table_t *new_tmp = NULL;
    do
    {
        *new_size += SHIFT;
        printf("new size is %d\n", *new_size);
        new_tmp = malloc(*new_size * sizeof(table_t));
        if (new_tmp)
        {
            for (int i = 0; i < *new_size; i++)
            {
                new_tmp[i].sign = 0;
            }
            prime = select_prime(*new_size);
            printf("prime is %d\n", prime);
            for (int i = 0; i < n; ++i)
            {
                if (table[i].sign != 0)
                {
                    index = hash_func(table[i].n, prime);
                    printf("index is %d\n", index);
                    if (new_tmp[index].sign != 0)
                    {
                        while ((new_tmp[index].sign) != 0)
                        {
                            if (index == *new_size)
                            {
                                index = 0;
                                continue;
                            }
                            index++;
                        }
                        new_tmp[index].n = table[i].n;
                        new_tmp[index].sign = 1;
                    }
                    else
                    {
                        new_tmp[index].n = table[i].n;
                        new_tmp[index].sign = 1;
                    }

                }

            }
            *new_table = new_tmp;
        }
        else
            return -1;
        cmp = search_table(*new_table, *new_size, search);
    } while (cmp > max);
    return cmp;
}

/*
int restruct(hashlist **table, int n, int search,  int max, int (*func)(int, int), hashlist ***new_table, int *new_size)
{
    *new_table = NULL;
    int cmp;
    *new_size = n;
    do
    {
        *new_size += SHIFT;
        *new_table = calloc(*new_size, sizeof(hashlist*));
        if (*new_table)
        {
            for (int i = 0; i < n; ++i)
            {
                hashlist *el = table[i];
                while (el)
                {
                    int index = func(el->value, *new_size);
                    add_to_table(*new_table, index, el->value);
                    el = el->next;
                }
            }
        }
        else
            return -1;
        cmp = search_table(*new_table, *new_size, search, func);
    } while (cmp > max);
    return cmp;
}
*/
