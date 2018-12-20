#include "arr.h"
#include "err.h"
#include "list.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
void arr_push(base *array, unsigned *curr)
{
    int type_choice;
    char ch;
    int num = 0;
    char number[NUM_LEN + 1] = "";
    printf("Выберите тип добавляемого элемента:\n1) char (знак + -)\n2) int (число)\n");
    while ((user_input(&type_choice)) != OK)
    {
        err_output(err_choice_1);
    }
    if (type_choice == 1)
    {
        printf("Введите знак!\n");
        ch = fgetc(stdin);
        if (ch == '\n' || (ch != '+' && ch != '-' && ch != '*' && ch != '/'))
        {
            printf("Не могу записать в стек знак, ибо это не знак :(\n");
            return;
        }
        array[*curr].kind = SIGN;
        array[*curr].u.sign = ch;
    }
    else
    {
        printf("Введите число!\n");
        if (fgets(number, NUM_LEN, stdin) == NULL)
        {
            printf("Не могу записать в стек число, ибо это не число :(\n");
            return;
        }
        array[*curr].kind = NUMBER;
        num = atoi(number);
        if (num != 0)
        {
            array[*curr].u.num = num;
        }
        else
        {
            printf("Не могу записать в стек число, ибо это не число :(\n");
            return;
        }
    }
    *curr = *curr + 1;
}
void arr_pop(base *array, unsigned *last)
{
    if (*last == 0)
    {
        printf("Нет элементов для удаления!\n");
    }
    else
    {
        *last = *last - 1;
    }
}
int calculate_arr(base *array, int last, int *result)
{
    //printf("last is %d\n", last);
    //printf("arra %d", array[last - 1].u.num);
    if (array[last - 1].kind == SIGN)
    {
        printf("is not sign\n");
        return -1;
    }
    *result = array[last - 1].u.num;
    for (int i = last - 2; i >= 1; i--)
    {
        if (array[i].kind != SIGN)
        {
            printf("is not sign!\n");
            return -1;
        }
        //printf("arr num is %d\n", array[i - 1].u.num);
        if (array[i].u.sign == '+')
        {
            *result = *result + array[i - 1].u.num;
        }
        else if (array[i].u.sign == '-')
        {
            *result = *result - array[i - 1].u.num;
        }
        i--;
    }
    return OK;
}
