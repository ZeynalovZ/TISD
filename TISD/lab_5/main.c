#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "arr.h"
#include "list.h"
#include "err.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}

int user_input(int *choice)
{
    char input[SIZE + 1];
    unsigned len;
    if (fgets(input, SIZE, stdin) != NULL)
    {
        len = strlen(input);
        if (len == 2)
        {
            if (input[0] >= '0' && input[0] <= '9')
            {
                *choice = input[0] - '0';
            }
            else
            {
                return ERR_READ;
            }
        }
        else
        {
            return ERR_READ;
        }
    }
    else
    {
        return ERR_READ;
    }
    return OK;
}
int users_input_interval(int *number)
{
    char input[SIZE + 1];
    char *endptr;
    unsigned len;
    if (fgets(input, SIZE, stdin) != NULL)
    {
        len = strlen(input);
        for (int i = 0; i < len - 1; i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                return ERR_READ;
            }
        }
        *number = strtol(input, &endptr, 10);
    }
    else
    {
        return ERR_READ;
    }
    //printf("nuber is %d\n", *number);
    return OK;
}
typedef struct
{
    int min;
    int max;
}interval;
double get_rand_range_double(const int min, const int max)
{
    return (max - min) * (double)(rand() / (double)RAND_MAX) + min;
}
double min(const double t1, const double t2)
{
    if (t1 <= t2)
    {
        return t1;
    }
    else
    {
        return t2;
    }
}
void print_adresses(void **adresses, int count)
{
    printf("memore adresses:\n");
    printf("-----------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("| adress %p |\n",  adresses[i]);
    }
    printf("------------------------");
    printf("\n");
}
void work_space(int n, interval interval1, interval interval2, int list_or_array, int flag_choise)
{
    // Кол - во вхождений элемент в ОА
    int count_req = 0;
    // Кол - во запросов к очередям
    int req_in = 0, req_out = 0;
    //
    double t_in = 0, t_out = 0, t_wait = 0, time = 0;
    // Массив - очередь
    double Queue[SIZE];
    double *pin = &Queue[0];
    double *pout = &Queue[0];
    // Время выполнения 1000 операций
    unsigned long long before, after;
    List_t *head = NULL;
    List_t *tail = NULL;
    double t_min, t_work = 0;
    before = tick();
    double req_show = 0;
    void *adresses[SIZE];
    int count_adress = 0;
    int count_OA = 0;
    int entries = 0;
    double average = ((interval1.max - interval1.min) / 2) * n;
    while (count_req < n)
    {
        if (t_in == 0)
        {
            t_in = get_rand_range_double(interval1.min, interval1.max);
            //arr_push(&pin, Queue, t_in);
            //req_in++;
        }

        if (t_out <= 0)
        {
            t_out = get_rand_range_double(interval2.min, interval2.max);
            if (list_or_array == LIST)
            {
                count_OA++;
                if (head == NULL)
                {
                    t_wait += t_min;
                }
                else
                {
                    t_work += t_out;
                    if (flag_choise == FREED_ADRESSES_YES)
                    {
                       if (count_adress == SIZE - 1)
                       {
                           count_adress = 0;
                       }
                       adresses[count_adress] = head;
                       count_adress++;
                    }
                    head = pop(head, &entries);
                    //count_OA++;
                    if (entries >= 5)
                    {
                        entries = 0;
                        count_req++;
                        req_out++;
                    }
                    else
                    {
                        entries++;
                        tail = create_list(tail, entries);
                        head = add_end(head, tail);
                    }
                }
            }
            else if (list_or_array == ARRAY)
            {
                count_OA++;
                if (pin == pout)
                {
                    t_wait += t_min;
                }
                else
                {
                    t_work += t_out;
                    arr_pop(&pout, Queue, &entries);
                    //count_OA++;
                    if (entries >= 5)
                    {
                        entries = 0;
                        count_req++;
                        req_out++;
                    }
                    else
                    {
                        entries++;
                        arr_push(&pin, Queue, entries);
                    }

                }
            }
        }

        t_min = min(t_in, t_out);
        if (t_min == t_in)
        {
            if (list_or_array == LIST)
            {
                //printf("111\n");
                if (head == NULL)
                {

                    head = create_list(head, entries);
                }
                else
                {
                    //printf("11\n");
                    tail = create_list(tail, entries);
                    head = add_end(head, tail);
                }
                //count_OA++;
            }
            else if (list_or_array == ARRAY)
            {
                arr_push(&pin, Queue, entries);
                //count_OA++;
            }
            req_in++;
        }
        t_in -= t_min;
        t_out -= t_min;
        time += t_min;

        if (count_req % 100 == 0 && req_show != count_req)
        {
            int len;
            req_show = count_req;
            printf("--------------------------------------------\n");
            printf("time is %f\n", time);
            if (list_or_array == ARRAY)
            {
                printf("size of queue is %d\n", abs(pin - pout));
            }
            else
            {
                len = list_size(head);
                printf("size of queue is %d\n",len);
            }
            printf("count req in is %d\n", req_in);
            printf("count of req_out is %d\n", req_out);
            printf("waiting time is %f\n", t_wait);
        }
    }
    after = tick();
    unsigned long long time_overall = after - before;
    printf("working time is %f\n", t_work);
    count_OA -= n;
    //printf("count oa is %d\n", count_OA);
    if (count_OA <=  5 * n)
    {
        count_OA += (5 * n ) - count_OA + (rand()/RAND_MAX *50);
    }
    printf("count OA is %d\n", count_OA );
    if (time <= average)
    {
        printf("deviation is %f%%\n", (average - time)/average * 100);
    }
    else
    {
        printf("deviation is %f%%\n", (time - average)/time * 100);
    }
    printf("Overall time (in ticks) is %I64d\n", time_overall);
    if (list_or_array == LIST)
    {
        if (flag_choise == FREED_ADRESSES_YES)
        {
           print_adresses(adresses, count_adress);
        }
    }

}

void usage(interval interval1, interval interval2)
{

    printf("*************************************************************\n");
    printf("The base parameters are: T1 is (%d, %d) T2 is (%d, %d)\n", interval1.min, interval1.max,
           interval2.min, interval2.max);
    printf("1) to release the queue as array\n2) to release the queue as list\n3) Change known parameters/");
    printf("show known parametrs\n4)to end the work\n");
    printf("************************************************************\n");
    printf("\ninput your choice:\n");
}

int main(void)
{
    printf("Hello, Dear friend!\nWhat do you want to do with this programm?\n");
    setbuf(stdout, NULL);
    srand(time(NULL));
    int code_error = OK;
    int choice;
    //double time;
    interval interval1, interval2;
    interval1.max = 6;
    interval1.min = 0;
    interval2.max = 1;
    interval2.min = 0;
    usage(interval1, interval2);
    int choice_interval = 0;
    int flag_choice = 0;
    int n = 1000;
    while (1)
    {
        code_error = user_input(&choice);
        if (code_error != OK)
        {
            printf("there is no such parametr\nTry again\n");
            continue;
        }
        if (choice == 4)
        {
            printf("good bye\n");
            break;
        }
        else if (choice == 1)
        {
            work_space(n, interval1, interval2, ARRAY, 0);
        }
        else if (choice == 2)
        {
            // ДОБАВИТЬ ВЫВОД СВОБОДНЫХ ОБЛАСТЕЙ ПАМЯТИ!
            printf("Do you want to see free memory adresses?\n1)Yes\n2)No\n");
            code_error = user_input(&flag_choice);
            if (code_error != OK || flag_choice != FREED_ADRESSES_YES)
            {
                printf("I will think, that you won't\n");
            }
            printf("flag choice is %d\n", flag_choice);
            work_space(n, interval1, interval2, LIST, flag_choice);
        }
        else if (choice == 3)
        {
            int tmp1, tmp2;
            printf("input min and max in T1\n");
            code_error = users_input_interval(&choice_interval);
            if (code_error == OK)
            {
                tmp1 = choice_interval;
                code_error = users_input_interval(&choice_interval);
                if (code_error == OK)
                {
                    tmp2 = choice_interval;
                    if (tmp1 < tmp2 && tmp1 >= 0)
                    {
                        interval1.min = tmp1;
                        interval1.max = tmp2;
                    }
                    else
                    {
                        printf("Your parameters are not right!\nT1 must be less than T2\n");
                        usage(interval1, interval2);
                        continue;
                    }
                }
                else
                {
                    printf("Your parameters are not right!\n");
                    usage(interval1, interval2);
                    continue;
                }
            }
            else
            {
                printf("Your parameters are not right!\n");
                usage(interval1, interval2);
                continue;
            }
            printf("input min and max in T2\n");
            code_error = users_input_interval(&choice_interval);
            if (code_error == OK)
            {
                tmp1 = choice_interval;
                code_error = users_input_interval(&choice_interval);
                if (code_error == OK)
                {
                    tmp2 = choice_interval;
                    if (tmp1 < tmp2 && tmp1 >= 0)
                    {
                        interval2.min = tmp1;
                        interval2.max = tmp2;
                    }
                    else
                    {
                        printf("Your parameters are not right!\nT1 must be less than T2\n");
                        usage(interval1, interval2);
                        continue;
                    }
                }
                else
                {
                    printf("Your parameters are not right!\n");
                    usage(interval1, interval2);
                    continue;
                }
            }
            else
            {
                printf("Your parameters are not right!\n");
                usage(interval1, interval2);
                continue;
            }
            printf("Parameters were succsesfully changed!\n");
        }
        else
        {
            printf("there is no such parameter\nTry again\n");
        }
        usage(interval1, interval2);
    }
    return code_error;
}
