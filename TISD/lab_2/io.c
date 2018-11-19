#include "io.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_string(user *base, int kind)
{
    printf("%-15s ", base->name);
    printf("%-20s ", base->surname);
    printf("%-20s ", base->adress);
    printf("%-18s ", base->phone_number);
    if (kind == 0)
    {
        printf("%-5d ", base->type_user.personal.day);
        printf("%-5d ", base->type_user.personal.month);
        printf("%-8d ", base->type_user.personal.year);
        printf("     -  ");
        printf("     -  ");
    }
    else
    {
        printf("   - ");
        printf("   - ");
        printf("   -      ");
        printf("%-15s", base->type_user.service.post);
        printf("%-15s", base->type_user.service.service_name);
    }
    printf("|");
    printf("\n");
}
void print_table(user *base, int count)
{
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|Номер   Имя     Фамилия      Адрес              Номер          день  месяц  год   должность организация|\n");
    printf("|-------------------------------------------------------------------------------------------------------|\n");

    for (int i = 0; i < count; i++)
    {
        printf("| ");
        printf("%-5d ", i + 1);
        print_string(&base[i], base[i].kind);
    }
    printf("\n");
}
int read_base(user *base)
{

    FILE *filename;
    filename = fopen("table2.txt", "r");
    int i = 0;
    char var_pole[FILE_LENGHT];
    while (fscanf(filename, "%s", base[i].name) != EOF)
    {
        //printf("name is %s\n",base[i].name);
        fscanf (filename, "%s", base[i].surname);
        //printf("surname is %s\n",base[i].surname);
        fscanf (filename, "%s", base[i].adress);
        //printf("adress is %s\n",base[i].adress);
        fscanf (filename, "%s", base[i].phone_number);
        fscanf(filename, "%d", &base[i].kind);
        if (base[i].kind == 1)
        {
            fscanf (filename, "%s", base[i].type_user.service.post);
            fscanf (filename, "%s", base[i].type_user.service.service_name);
        }
        else
        {
            fscanf (filename, "%d", &base[i].type_user.personal.day);
            fscanf (filename, "%d", &base[i].type_user.personal.month);
            fscanf (filename, "%d", &base[i].type_user.personal.year);
        }
        i++;
    }
    fclose(filename);
    return i;
}
int read_line(char *str, int size)
{
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        if (i < size)
        {
            str[i] = ch;
            i++;
        }
    if (i > size)
    {
        return -1;
    }
    str[i] = '\0';
    return i;
}

int read_int(int *a, int n)
{
    char *chars = calloc(n, sizeof(char));
    if (chars == NULL)
        return ERR_MEM;
    int num = read_line(chars, n);
    if (num < 1)
    {
        return ERR_INPUT;
    }
    char *end_ptr;
    *a = (int)strtol(chars, &end_ptr, 10);

    if (*end_ptr)
        return ERR_INPUT;
    free(chars);
    return OK;
}

int get_all(FILE *f, user **base, size_t *n)
{
    int rc = OK;
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);
    if (size < sizeof(user))
        return -10;
    *base = malloc(size * sizeof(char));

    if (!*base)
        rc = ERR_MEM;
    else if (fread(*base, size, 1, f) != 1)
    {
        free(*base);
        rc = ERR_INPUT;
    }
    else
        *n = size / sizeof(user);

    rewind(f);

    return rc;
}
int find_all(FILE *f)
{
    user *base;
    size_t n;
    int rc = get_all(f, &base, &n);

    if (rc != OK)
        return rc;
    printf("string is %s\n", base->name);
    //print_base(&base, n);

    free(base);

    return OK;
}

char *word(char *base)
{
    int i = 0;
    //printf("\n\n%c\n\n",base[0][0]);
    while (base[i] != '\n')
    {
        //printf("%c", base[i]);
        i++;
    }
    return base;
}

void read_keys(key *keys, user *base, int count)
{
    for (int i = 0; i < count; i++)
    {
        keys[i].index = i + 1;
        strcpy(keys[i].name, base[i].name);
    }
}

void print_keys(key *keys, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\nИндекс %d\n", keys[i].index);
        printf("Имя: %s\n", keys[i].name);
    }
}



