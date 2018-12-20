#include "arr.h"
#include "err.h"
#include "list.h"
#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int user_input(int *choice)
{
    char string[SIZE_READ + 1] = "";

    if (fgets(string, SIZE_READ + 1, stdin) == NULL)
    {
        return ERR_IO;
    }
    //printf("string is %s\n", string);
    int len = strlen(string);
    if (len == 2)
    {
        if (string[0] > '3' || string[0] < '1')
        {
            return ERR_IO;
        }
        *choice = string[0] - '0';
    }
    else
    {
        return ERR_IO;
    }
    return OK;
}
void err_output(int err_type)
{
    switch (err_type) {
    case err_choice_1:
        printf("Введенное цифра - неверная, попробуйте еще раз!\n");
        printf("Для завершения программы нажмите ctrl + Z \n");
        break;
    default:
        break;
    }
}
void print_arr(base *array, int readed_count)
{
    for (int i = 0; i < readed_count; i++)
    {
        if (array[i].kind == NUMBER)
        {
            printf("%d ", array[i].u.num);
        }
        else if (array[i].kind == SIGN)
        {
            printf("%c ", array[i].u.sign);
        }
    }
    printf("\n");
}
int read_expression(base *array, unsigned *count_readed)
{
    int code_error = OK;
    char expression[EXP_LEN + 1] = "";
    char number[NUM_LEN + 1] = "";
    int num = 0;
    int flag_read_num = 1; // равен единице, ибо читаем сразу число, или равен -1 если читаем знак
    printf("Введите выражение в формате: число|знак|число|знак|число|\n");
    if (fgets(expression, EXP_LEN + 1, stdin) != NULL)
    {
        if (expression[0] == '\n')
        {
            code_error = ERR_IO;
            printf("expression == '\n");
            return code_error;
        }
        int i = 0, i_for_num = 0;
        char sign;
        while (expression[i] != '\n')
        {
            if (expression[i] == '|')
            {
                if (flag_read_num == 1)
                {
                    number[i_for_num] = '\0';
                    //printf("number is %s\n", number);
                    array[*count_readed].kind = NUMBER;
                    num = atoi(number); // my_atoi is quite well
                    array[*count_readed].u.num = num;
                    //printf("array[i] num is %d", array[*count_readed].u.num);
                    *count_readed = *count_readed + 1;
                }
                else
                {
                    //printf("sign is %c\n", sign);
                    array[*count_readed].kind = SIGN;
                    array[*count_readed].u.sign = sign;
                    *count_readed = *count_readed + 1;
                }
                i_for_num = 0;
                flag_read_num *= -1;
                i++;
                continue;
            }
            if (flag_read_num == 1)
            {
                if (expression[i] >= '0' && expression[i] <= '9')
                {
                    number[i_for_num] = expression[i];
                    i_for_num++;
                }
                else
                {
                    code_error = ERR_IO;
                    printf("< 0 || > 9");
                    return code_error;
                }
            }
            else if (flag_read_num == -1)
            {
                sign = expression[i];
                if (sign != '-' && sign != '*' && sign != '+' && sign != '/')
                {
                    code_error = ERR_IO;
                    printf("sign != ...\n");
                    return code_error;
                }
            }
            else
            {
                printf("not read num\n");
                return ERR_IO;
            }
            i++;
        }
    }
    else
    {
        printf("fgets error\n");
        code_error = ERR_IO;
    }
    /*)
    if (flag_read_num == -1)
    {
        code_error = ERR_IO;
        return code_error;
    }
    */
    return code_error;
}
int user_input_type(int *choice)
{
    char string[SIZE_READ + 1] = "";

    if (fgets(string, SIZE_READ + 1, stdin) == NULL)
    {
        return ERR_IO;
    }
    int len = strlen(string);
    if (len == 2)
    {
        if (string[0] > '2' || string[0] < '1')
        {
            return ERR_IO;
        }
        *choice = string[0] - '0';
    }
    else
    {
        return ERR_IO;
    }
    return OK;
}
void print_array(void **array, int count)
{
    printf("\nМассив свободных областей памяти:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%p ", array[i]);
    }
    printf("\n\n");
}
