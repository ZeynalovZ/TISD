#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define ERROR 5
#define N 30
#define OK 1
void show_result(const char *a, const int number)
{
    printf("massive is: ");
    for (int i = 0; i < number; i++)
    {
        printf("%c ",a[i]);
    }
    printf("\n");
}
void show_result1(const int *a, const int number)
{

    for (int i = 0; i < number; i++)
    {
        if (i ==0 && a[i] == 0)
        {
            ;
        }
        else
        {
            printf("%d",a[i]);
        }
    }
    printf("\n");
}
void show_to_user(const int *result, const int por)
{
    if (por == 0)
    {
        printf("0.");
        show_result1(result, por);
        printf(" E %d", por+1);
    }
    else
    {
        printf("0.");
        show_result1(result, por);
        printf(" E %d", por);
    }
}
int get_from_user(char *a, int *number, int *por)
{
    char mantis[N+1];
    int flag = 0;
    int count_flag = 0;
    int flag_minus = 0;
    int pos, i;
    *number = 0;
    printf("Введите мантиссу:\n");
    scanf("%s", mantis);
    printf("Введите порядок  числа:\n");
    scanf("%d", por);
    printf("por is %d \n", *por);
    for (i = 0; mantis[i] != '\0';i++)
    {
        if (mantis[i] == '.' && count_flag < 1)
        {
            flag = 1;
            count_flag += 1;
            pos = i;
        }
        else if (mantis[i] == '-' && i == 0)
        {
            flag_minus = 1;
        }
        else if( mantis[i] < '0' || mantis[i] > '9')
        {
            return ERROR;
        }
    }
    if (flag == 1 && flag_minus == 1)
    {

        *por += pos - 1;
    }
    else if (flag == 1 && flag_minus == 0)
    {

        *por += pos;
    }
    else if (flag == 0 && flag_minus == 0 && *por!=0)
    {

        *por += i;
    }
    for (int i = 0; mantis[i] != '\0';i++)
    {
        if (mantis[i] != '.' && mantis[i] != '-')
        {
            a[*number] = mantis[i];
            *number += 1;
        }
    }
    return OK;
}

int multiply(char *a, char *b, int number, int number1)
{
    int c[N] = {0};
    int sum = 0;
    for (int i = number-1; i >= 0; i--)
    {
        sum = 0;
        for (int j = number1-1; j >= 0; j--)
        {
            c[i + j + 1] += sum + ((a[i] - '0') * (b[j] - '0'));
            sum = c[i+j+1]/10;
            c[i+j+1]%=10;
        }
        c[i] += sum;
    }
    show_to_user(c, number + number1);
    return OK;
}
/*
int multiply(char *a, char *b, int number, int number1)
{
    //int a[] = {1,2};
    //int b[] = {0};
    //int c[N];
    int quotient = 0;
    int residue;
    int prozv;
    int total = 0;
    int sum = 0;
    int count = 0;
    for (int i = number-1; i >= 0; i--)
    {
        int count1 = count;
        sum = 0;
        for (int j = number1-1; j >= 0; j--)
        {
            prozv = (a[i] - '0') * (b[j] - '0');
            prozv += quotient;
            quotient = prozv / 10;
            residue = prozv % 10;
            sum += residue * pow(10, count1);
            count1 += 1;
        }
        sum += quotient * pow(10,count1);
        printf("sum is here %d\n------", sum);
        quotient = 0;
        residue = 0;
        total += sum;
        count += 1;
    }
    return total;
}
*/
int main(void)
{
    setbuf(stdout, NULL);
    char a[N];
    char b[N];
    int number, por;
    int number1, por1;
    int por_S;
    int result;
    //int number = N;
    //Проверить на правильность ввода
    get_from_user(a, &number, &por);
    get_from_user(b,&number1, &por1);
    show_result(a, number);
    printf("вторая мантиса\n");
    show_result(b, number1);
    printf("Result is:\n");
    result = multiply(a,b,number, number1);
    por_S = por1 + por;
    show_to_user(&result, por_S);
    return OK;
}
