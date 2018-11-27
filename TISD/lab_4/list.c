#include "arr.h"
#include "err.h"
#include "list.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
void look_back(Stack *list)
{
    void *array_mem[ARRAY_SIZE];
    int count = 0;
    while (list)
    {
        if (list->kind1 == NUMBER)
        {
            printf("%d ", list->u.num);
            array_mem[count] = &list->u.num;
        }
        else
        {
            printf("%c ", list->u.sign);
            array_mem[count] = &list->u.sign;
        }
        count++;
        list = list->prev;
    }
    printf("\n");
    printf("Массив занятых областей\n");
    for (int i = 0; i < count; i++)
    {
        printf("%p ", array_mem[i]);
    }
    printf("\n");
}
void *pop(Stack **list)
{
    void *data = NULL;
    if (*list != NULL)
    {
        if ((*list)->kind1 == SIGN)
        {
            data = &(*list)->u.sign;
        }
        else
        {
            data = &(*list)->u.sign;
        }
        Stack *element = *list;
        *list = (*list)->prev;
        free(element);
        return data;
    }
    else
    {
        printf("Стек пуст !\n");
    }
    return data;
}
void free_list(Stack *list)
{
    while (list)
    {
        Stack *element = list->prev;
        free(list);
        list = element;
    }
}
Stack *add_to_list(Stack **list)
{

    Stack *element = malloc(sizeof(Stack));
    if (element)
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
            ch = fgetc(stdin);
            if (ch == '\n' || (ch != '+' && ch != '-' && ch != '*' && ch != '/'))
            {
                printf("Не могу записать в стек знак, ибо это не знак :(\n");
                return NULL;
            }
            element->kind1 = SIGN;
            element->u.sign = ch;
            if (list)
            {
                element->prev = *list;
                *list = element;
            }
            else
                element->prev = NULL;
        }
        else
        {
            if (fgets(number, NUM_LEN, stdin) == NULL)
            {
                printf("Не могу записать в стек число, ибо это не число :(\n");
                return NULL;
            }
            element->kind1 = NUMBER;
            num = atoi(number);
            if (num != 0)
            {
                element->u.num = num;
                if (list)
                {
                    element->prev = *list;
                    *list = element;
                }
                else
                    element->prev = NULL;
            }
            else
            {
                printf("Не могу записать в стек число, ибо это не число :(\n");
                return NULL;
            }
        }
    }
    return element;
}
void from_arr_to_list(base *array, int n, Stack **head)
{
    for (int i = 0; i < n; i++)
    {
        Stack *element = malloc(sizeof(Stack));
        if (array[i].kind == NUMBER)
        {
            element->kind1 = NUMBER;
            element->u.num = array[i].u.num;
            if (head)
            {
                element->prev = *head;
                *head = element;
            }
            else
            {
                element->prev = NULL;
            }
        }
        else
        {
            element->kind1 = SIGN;
            element->u.sign = array[i].u.sign;
            if (head)
            {
                element->prev = *head;
                *head = element;
            }
            else
            {
                element->prev = NULL;
            }
        }
    }
}
int calculate_list(Stack **head, int *result)
{
    Stack *tmp;
    if (*head == NULL )
    {
        return -1;
    }
    if ((*head)->kind1 == SIGN)
    {
        printf("is sign\n");
        return -1;
    }
    if (!(*head)->prev)
    {
        printf("prev doesn't exist\n");
        return -1;
    }
    *result = (*head)->u.num;
    //printf("num is %d\n", *result);
    *head = (*head)->prev;
    while (*head)
    {
        if ((*head)->kind1 != SIGN)
        {
            printf("kind is not sign\n");
            return -1;
        }
        if ((*head)->u.sign == '+')
        {
            if ((*head)->prev)
            {
                *result = *result + (*head)->prev->u.num;
            }
            else
            {
                printf("prev doesnt exist\n");
                return -1;
            }
        }
        else if ((*head)->u.sign == '-')
        {
            if ((*head)->prev)
            {
                *result = *result - (*head)->prev->u.num;
            }
            else
            {
                printf("prev doesnt exist\n");
                return -1;
            }
        }
        tmp = (*head)->prev->prev;
        pop(&(*head)->prev);
        pop(&(*head));
        *head = tmp;
    }
    return OK;
}
