#include "operations.h"
#include <stdio.h>
#include "err.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "err.h"
#include "operations.h"
#include "io.h"
int add_line(user *base, int count)
{
    FILE *filename;
    filename = fopen("table2.txt", "a+");
    int rc = OK;
    int buff;
    if (filename == NULL)
    {
        return FILE_READ;
    }

    int kind_phone;
    printf("What kind of phone number? (1) - personal, (2) - service\n Input 1 or 2: ");
    if ((rc = read_int(&kind_phone, 1)) != OK)
    {
        return ERR_INPUT;
    }
    if (kind_phone != 1 && kind_phone != 2)
    {
        return ERR_INPUT;
    }
    printf("Структура таблицы имеет следующий формат:\n");

    while (true)
    {
        printf("Введите имя пользователя (до %i символов):\n ", NAME_LENGHT);
        buff = read_line(base[count].name, NAME_LENGHT);
        if (buff > 0)
            break;
        printf("ERR_INPUT"); // заменить кодом ошибки
    }

    while (true)
    {
        printf("Введите фамилию пользователя (до %i символов):\n ", SURNAME_LENGHT);
        buff = read_line(base[count].surname, SURNAME_LENGHT);
        if (buff > 0)
            break;
        printf("ERR_INPUT"); // заменить кодом ошибки
    }
    while (true)
    {
        printf("Введите адресс проживания пользователя (до %i символов):\n ", ADRESS_LENGHT);
        buff = read_line(base[count].adress, ADRESS_LENGHT);
        if (buff > 0)
            break;
        printf("ERR_INPUT"); // заменить кодом ошибки
    }
    while (true)
    {
        printf("Введите номер пользователя (до %i символов):\n ", PHONE_NUMBER_LENGTH);
        buff = read_line(base[count].phone_number, PHONE_NUMBER_LENGTH);
        if (buff > 0)
            break;
        printf("ERR_INPUT"); // заменить кодом ошибки
    }
    if (kind_phone == 1)
    {
        base[count].kind = 0;
        printf("input day: ");
        while (true)
        {
            printf("Введите день рождения (до %i символов):\n ", 2);
            int rc = read_int(&buff, 2);
            if (rc == OK)
            {
                if (buff > 0)
                {
                    base[count].type_user.personal.day = (int)buff;
                    break;
                }

                printf("ERR_INPUT"); // заменить кодом ошибки
            }
            else
                {
                    printf("ERR_rc");
                }
        }

        while (true)
        {
            printf("Введите месяц рождения (до %i символов):\n ", 2);
            int rc = read_int(&buff, 2);
            if (rc == OK)
            {
                if (buff > 0)
                {
                    base[count].type_user.personal.month = (int)buff;
                    break;
                }

                printf("ERR_INPUT"); // заменить кодом ошибки
            }
            else
                {
                    printf("ERR_rc");
                }
        }

        while (true)
        {
            printf("Введите год рождения (до %i символов):\n ", 4);
            int rc = read_int(&buff, 5);
            if (rc == OK)
            {
                if (buff > 0)
                {
                    base[count].type_user.personal.year = (int)buff;
                    break;
                }

                printf("ERR_INPUT"); // заменить кодом ошибки
            }
            else
                {
                    printf("ERR_rc");
                }
        }
        // строковый литерал не есть массив !!! Обработать Массивы путем добавления вперед пробелов
        fprintf(filename,"%s %s %s %s %d %d %d %d\n", base[count].name, base[count].surname,\
               base[count].adress, base[count].phone_number, base[count].kind, base[count].type_user.personal.day,\
               base[count].type_user.personal.month, base[count].type_user.personal.year);
    }
    else
    {
        base[count].kind = 1;
        while (true)
        {
            printf("Введите должность (до %i символов):\n ", POST_LENGHT);
            buff = read_line(base[count].type_user.service.post, POST_LENGHT);
            if (buff > 0)
                break;
            printf("ERR_INPUT"); // заменить кодом ошибки
        }

        while (true)
        {
            printf("Введите название организации (до %i символов):\n ",SERVICE_LENGHT );
            buff = read_line(base[count].type_user.service.service_name, SERVICE_LENGHT);
            if (buff > 0)
                break;
            printf("ERR_INPUT"); // заменить кодом ошибки
        }

        fprintf(filename, "%s %s %s %s %d %s %s\n", base[count].name, base[count].surname,\
               base[count].adress, base[count].phone_number, base[count].kind, base[count].type_user.service.post, \
               base[count].type_user.service.service_name);
    }
    fclose(filename);
    return OK;
}

int delete_line(user *base, int *count)
{
    FILE *f;
    f = fopen("table2.txt", "w");
    assert(f != NULL);
    char name[NAME_LENGHT + 1];
    int count1 = 0;
    printf("Введите Имя пользователя, которого хотите удалить из базы:\n");
    int buf = read_line(name, NAME_LENGHT);
    if (buf < 1)
    {
        printf("ERR_INPUT"); // Код ошибки
    }
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(base[i].name, name) != 0)
        {
            if (base[i].kind == 0)
            {
                fprintf(f,"%s %s %s %s %d %d %d %d\n", base[i].name, base[i].surname,\
                       base[i].adress, base[i].phone_number, base[i].kind, base[i].type_user.personal.day,\
                       base[i].type_user.personal.month, base[i].type_user.personal.year);
            }
            else
            {
                fprintf(f, "%s %s %s %s %d %s %s\n", base[i].name, base[i].surname,\
                       base[i].adress, base[i].phone_number, base[i].kind, base[i].type_user.service.post, \
                       base[i].type_user.service.service_name);
            }
        }
        else
        {
            printf("count is %d, i is %d\n", *count, i);
            for (int j = i; j < *count - 1; j++)
            {
                base[j] = base[j + 1];
            }
            printf("count after %d\n", *count);
            count1 += 1;
        }
    }
    *count -= count1;
    printf("count after %d\n", *count);
    fclose(f);
    return OK;
}

void bubble_keys(key *keys, int count)
{
    key tmp;
    for (int i = 0; i < count - 1; i++)
    {
         for (int j = i + 1; j < count; j++)
         {
             if (strcmp(keys[i].name, keys[j].name) > 0)
             {
                 strcpy(tmp.name, keys[j].name);
                 strcpy(keys[j].name, keys[i].name);
                 strcpy(keys[i].name, tmp.name);

                 tmp.index = keys[j].index;
                 keys[j].index = keys[i].index;
                 keys[i].index = tmp.index;
             }
         }
    }
}

void bubble_sort_table(user *base, int count)
{
    user tmp;
    for (int i = 0; i < count - 1; i++)
    {
         for (int j = i + 1; j < count; j++)
         {
             if (strcmp(base[i].name, base[j].name) > 0)
             {
                 tmp = base[j];
                 base[j] = base[i];
                 base[i] = tmp;
             }
         }
    }

}
void print_table_by_keys(user *base, key *keys, int count)
{
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|Номер   Имя     Фамилия      Адрес              Номер          день  месяц  год   должность организация|\n");
    printf("|-------------------------------------------------------------------------------------------------------|\n");
    for (int i = 0; i < count; i++)
    {
        printf("| ");
        print_string(&base[keys[i].index - 1], base[keys[i].index - 1].kind);
    }
    printf("\n");
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void time_table(user *table, key *keys, int count)
{
    unsigned long long tb, te, all_k = 0, all_t = 0;
    user table_test[count];
    float result;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < count; j++)
            table_test[j] = table[j];
        read_keys(keys, table, count);
        tb = tick();
        bubble_keys(keys, count);
        te = tick();
        all_k += te - tb;
        tb = tick();
        bubble_sort_table(table_test, count);
        te = tick();
        all_t += te - tb;
    }
    if (all_t >= all_k)
    {
        result = (all_t - all_k)/(float)all_t * 100;
        printf("\nСортировка по ключам быстрее сортировки таблицы на %.3f %%", result);
    }
    else if (all_t < all_k)
    {
        result = (all_k - all_t)/(float)all_k * 100;
        printf("\nСортировка таблицы быстрее сортировки по ключам на %.3f %%", result);
    }
}
int cmp_str(const void *a, const void *b)
{
    const char *li = a;
    const char *ri = b;
    return strcmp(li, ri);
}
void time_keys(user *table, key *keys, int count)
{
    float result;
    unsigned long long tb, te, all_k1 = 0, all_k2 = 0;
    for (int i = 0; i < 10; i++)
    {
        read_keys(keys, table, count);
        tb = tick();
        bubble_keys(keys, count);
        te = tick();
        all_k1 += te - tb;
        read_keys(keys, table, count);
        tb = tick();
        qsort(keys->name, count, NAME_LENGHT, cmp_str);
        te = tick();
        all_k2 += te - tb;
    }
    if (all_k1 >= all_k2)
    {
        result = (all_k1 - all_k2)/(float)all_k1 * 100;
        printf("\nБыстрая сортировка быстрее сортировки пузырьком на %.3f %%", result);
    }
    else if (all_k1 < all_k2)
    {
        result = (all_k2 - all_k1)/(float)all_k2 * 100;
        printf("\nСортировка пузырьком быстрее быстрой сортировки на %.3f %%", result);
    }
}

