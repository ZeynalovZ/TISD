#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "err.h"
#include "io.h"
#include "list.h"
#include "arr.h"


unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}

int my_atoi(char *string)
{
    int num = 0;
    int i = 0;
    unsigned len = strlen(string) - 1;
    while (string[i] != '\0')
    {
        //printf("%c", string[i]);
        num += (string[i] - '0') * pow(10, len - i);
        i++;
    }
    return num;
}
void usage()
{
    printf("\n\nДанная программа способна реализовывать действия добавления, удаления,\nвычисления введенного выражения.\n\n");
    printf("Для начала вам будет предложено выбрать реализацию стека или замер времени...\n");
    printf("----------------------------------------------------------\n");
    printf("1 - Реализовать стек массивом\n");
    printf("2 - Реализовать стек списком\n");
    printf("3 - Замерить время\n");
    printf("Для выхода из приложения нажмите ctrl + Z\n");
    printf("----------------------------------------------------------\n");
    printf("Введите действие: \n");
}

void usage_array()
{
    printf("----------------------------------------------------------\n");
    printf("Выберите действие, которое хотите выполнить:\n");
    printf("1) Добавить элемент в стек\n");
    printf("2) Удалить элемент из стека\n");
    printf("3) Вычислить выражение с помощью стека\n");
    printf("Для выхода из приложения нажмите ctrl + Z\n");
    printf("----------------------------------------------------------\n");
    printf("Введите действие: \n");
}
int main(void)
{
    setbuf(stdout, NULL);
    srand (time(NULL));
    double result_time = 0;
    long int t1, t2, s1_time = 0, s2_time = 0;
    int code_error = OK;
    int users_choice, users_choice_w_stack;
    base array[ARRAY_SIZE];
    unsigned count_readed = 0;
    Stack *list = NULL;
    void *array_mem[ARRAY_SIZE];
    void *tmp1;
    int count_arr = 0;
    int tmp = 0;
    int result = 0;
    usage();
    while ((user_input(&users_choice)) != OK)
    {
        err_output(err_choice_1);
    }
    //printf("users is %d\n", users_choice);

    switch (users_choice) {

    case 1:
        while(1)
        {
            usage_array();
            //printf("11111\n");
            while ((user_input(&users_choice_w_stack)) != OK)
            {
                err_output(err_choice_1);
            }
            switch (users_choice_w_stack) {

            case 1:
                printf("----------------------------------------------------------\n");

                arr_push(array, &count_readed);
                printf("Стек - массив:\n");
                print_arr(array, count_readed);
                printf("----------------------------------------------------------\n");
                break;

            case 2:
                printf("----------------------------------------------------------\n");
                arr_pop(array, &count_readed);
                printf("Стек - массив:\n");
                print_arr(array, count_readed);
                printf("----------------------------------------------------------\n");
                break;

            case 3:
                code_error = read_expression(array, &count_readed);
                if (code_error == OK)
                {
                    code_error = calculate_arr(array, count_readed, &result);
                    if (code_error == OK)
                    {
                        printf("----------------------------------------------------------\n");
                        printf("Стек - массив:\n");
                        print_arr(array, count_readed);
                        printf(" = %d\n", result);
                        count_readed = 0;
                        printf("----------------------------------------------------------\n");
                    }
                    else
                    {
                        count_readed = 0;
                    }
                }
                else
                {
                    printf("code_Error\n");
                }
                break;

            default:
                break;
            }
        }
        break;

    case 2:
        while(1)
        {
            usage_array();
            while ((user_input(&users_choice_w_stack)) != OK)
            {
                err_output(err_choice_1);
            }
            switch (users_choice_w_stack) {

            case 1:
                list = add_to_list(&list);
                printf("----------------------------------------------------------\n");
                printf("Стек - список:\n");
                look_back(list);
                printf("----------------------------------------------------------\n");
                break;

            case 2:
                // Добить!
                printf("before\n");
                look_back(list);
                if (list != NULL)
                {
                    tmp1 = pop(&list);
                    if (tmp1 != 0)
                    {
                        array_mem[count_arr] = tmp1;
                        count_arr++;
                    }
                    printf("----------------------------------------------------------\n");
                    printf("Стек - список:\n");
                    look_back(list);
                    print_array(array_mem, count_arr);
                    printf("----------------------------------------------------------\n");
                }
                else
                {
                    print_array(array_mem, count_arr);
                    printf("Стек пуст!\n");
                }

                //count_arr++;

                break;

            case 3:
                code_error = read_expression(array, &count_readed);
                if (code_error == OK)
                {
                    from_arr_to_list(array, count_readed, &list);
                    look_back(list);
                    code_error = calculate_list(&list, &result);
                    if (code_error == OK)
                    {
                        printf("----------------------------------------------------------\n");
                        printf("Стек - список:\n");
                        look_back(list);
                        printf(" = %d\n", result);
                        printf("----------------------------------------------------------\n");
                    }
                    else
                    {
                        free_list(list);
                        list = NULL;
                        printf("Error in 3 in list\n");
                    }
                }
                else
                {
                    printf("code_Error\n");
                }
                break;

            default:
                break;
            }
        }
        break;

    case 3:
        code_error = read_expression(array, &count_readed);
        if (code_error == OK)
        {
            from_arr_to_list(array, count_readed, &list);
            t1 = tick();
            calculate_list(&list, &result);
            t2 = tick();
            s1_time = t2 - t1;
            tmp = result;
            t1 = tick();
            calculate_arr(array, count_readed, &result);
            t2 = tick();
            s2_time = t2 - t1;
            printf("tmp is %d\n", tmp);
            printf("result is %d\n", result);
            printf(" Размер элемента списка is %d\n", sizeof(Stack));
            printf(" Размер элемента массива is %d\n", sizeof(base));
            printf("s1_time is %ld\n", s1_time);
            printf("s2_time is %ld\n", s2_time);
            if (s1_time <= s2_time)
            {
                result_time = ((double)(s2_time - s1_time)/s2_time) * 100;
                printf("вычисление значения выражения списком быстрее массива на %lf процентов\n", result_time);
            }
            else
            {
                result_time = ((double)(s1_time - s2_time)/s1_time) * 100;
                printf("вычисление значения выражения массивом быстрее списка на %lf процентов\n", result_time);
            }
        }
        else
        {
            printf("code_Error\n");
        }
        break;

    default:
        break;
    }
    return code_error;
}
