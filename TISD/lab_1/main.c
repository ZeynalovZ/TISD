#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ERROR -1
#define ERR_POR -2
#define ERR_LEN -3
#define N 30
#define N1 60
#define OK 0
//Объявим функцию замены \n на \0
int change_str(char *str, int count);
//функция вывода массива на печать
void show_result(const char *a, const int number)
{
    printf("massive is: ");
    for (int i = 0; i < number; i++)
    {
        printf("%c ",a[i]);
    }
    printf("\n");
}

void show_result2(const int *a, const int number)
{
    printf("massive is: ");
    for (int i = 0; i <= number; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}
//функция вывода резульатата на пачеть
void show_result1(const int *a, int number)
{
    //printf("number u want is %d\n", number);
    // выводим массив мантиссы
    printf("0.");
    if (number < 0)
    {
        printf("0");
    }
    for (int i = 0; i < number; i++)
    {
        printf("%d",a[i]);
    }
    if (a[number] != 0)
    {
        printf("%d",a[number]);
    }
}
// функция вывода результата
void show_to_user(const int *result, const int por, int number, int flag)
{
    if (flag == 0)
    {
        printf("-");
        show_result1(result, number);
        printf(" E %d", por);
    }
    else
    {
        printf("+");
        show_result1(result, number);
        printf(" E %d", por);
    }
}
//считывание целого числа
int get_from_user1(char *b, int *number1, int *flag)
{
    char number[31];
    int count = 0;
    int rc = OK;
    if (fgets(number, 32, stdin) == NULL)
    {
        return ERROR;
    }
    rc = change_str(number, 32);
    if (rc != OK)
    {
        return ERROR;
    }
    for (int i = 0; number[i] != '\0'; i++)
    {
        //printf("b[i] = %c\n", number[i]);
        if (number[i] == '-' && i == 0 && *flag < 1)
        {
            *flag = 1;
        }
        else if (number[i] < '0' || number[i] > '9')
        {
            return ERROR;
        }
        else
        {
            //printf("b[i] = %c\n", number[i]);
            b[count] = number[i];
            count += 1;
            //printf("count is %d", count);
        }
    }
    *number1 = count;
    //show_result(b, *number1);
    return rc;
}
// перемножение мантисс
/* а - мантисса 1 числа number - размер 1 мантиссы
 * с - мантиса 2 числа number1 - размер 2 мантиссы
 * res - результирующий массив целочисленных элементов
 *
 *
 */
int multiply(char *a, char *b, int number, int number1, int *res)
{
    int sum;
    for (int i = number-1; i >= 0; i--)
    {
        sum = 0;
        for (int j = number1-1; j >= 0; j--)
        {
            res[i + j + 1] += sum + ((a[i] - '0') * (b[j] - '0'));
            sum = res[i+j+1] / 10;
            res[i+j+1] %= 10;
        }
        res[i] += sum;
    }
    //printf("result massive is real here\n");
    //for (int i = 0; i < number1 + number; i++)
    //{
    //    printf("%d", res[i]);
    //}
    //printf("\n");
    return OK;
}
// определение позиции символа Е и обработка строки
int pos_e(char *a, int *pos, int *count1, int *flag)
{
    int count = 0;      // кол-во символов Е
    int count_num = 0;  // кол-во считанных элементов
    for (int i = 0; a[i] != '\0'; i++)
    {
        // Если нашли символ е и он единственный, иначе ошибка
        if (a[i] == 'E' || a[i] == 'e')
        {
            if (count < 1)
            {
                count += 1;
                *pos = i;
                *flag = 1;
            }
            else
            {
                return ERROR;
            }
        }
        else if (a[i] == '.' || a[i] == '-' || a[i] == '+')
        {
            ;     // Если найжена точка или минус - ничего страшного
        }
        else if (a[i] < '0' || a[i] > '9')
        {
            return ERROR;
        }
        count_num += 1;
    }
    if (count == 0)
    {
        *pos = count_num;
        *flag = 0;
    }
    *count1 = count_num;
    return OK;
}
//функция чтения и обработки мантиссы вещественного числа
/*
 * pos - позиция символа Е или е
 * pos_por - кол-во элементов до точки в мантиссе
 * flag_min - наличие минуса
 * count_bef - кол-во элементов без учета знаков и точек
 */
int read_mant(const char* a, char* b, int *pos, int *pos_por, int *flag_min, int *count_bef, int *flag1)
{
    int count_flag = 0;
    int count_null = 0; // кол-во нулей до точки
    int flag = 0;       // если найдены символы не равные нулю до точки
    //printf("*pos is %d\n", *pos);
    for (int i = 0; i < *pos; i++)
    {
        //printf("a[i] is %c\n", a[i]);
        // Если найдена точка и она единственная
        if (a[i] == '.' && count_flag < 1)
        {
            count_flag += 1;
        }
        // Если найден минус и он первый
        else if (a[i] == '-' && i == 0)
        {
            *flag_min = 1;
        }
        else if (a[i] == '0' && count_flag < 1 && flag == 0)
        {
            count_null += 1;
        }
        else if(a[i] == '+' && i == 0)
        {
            continue;
        }
        // Является ли числом все остальное, кроме описанных выше ситуаций
        else if( a[i] < '0' || a[i] > '9')
        {
            return ERROR;
        }
        else
        {
            flag = 1;
            b[*count_bef] = a[i];
            *count_bef += 1;
        }
    }

    int j = 0;
    int post = 0;
    while (a[j] != '.' && a[j] != '\0' && j != *pos)
    {
        if (a[j] != '-')
        {
            post += 1;
        }
        j++;
    }
    //printf("post is %d\n", post);
    //printf("count_null is %d\n", count_null);
    //вычитаем из позиции точки кол-во нулей до точки, так как их не читаем
    if (count_null != 1)
        *pos_por = post - count_null;
    else
        *pos_por = post;
    if (count_null == 1 && post == 1)
    {
        *flag1 = 1;
    }
    while (b[*count_bef - 1] == '0')
    {
        *count_bef = *count_bef - 1;
    }
    return OK;
}
// функция чтения и обработки порядка вещественного числа
int read_por(const char *a, int pos, int *por)
{
    int flag_minus = 0;
    int poryadok[N];
    int count = -1;
    for (int i = pos + 1; a[i] != '\0'; i++)
    {
        // Если в порядке обнаружен минус и он единственный и он первый
        if (a[i] == '-' && flag_minus < 1 && i == pos + 1)
        {
            flag_minus = 1;
        }
        // Является ли введенный порядок числом
        else if( a[i] < '0' || a[i] > '9')
        {
            return ERROR;
        }
        // если все устраивает - записываем посимвольно в массив из символов порядка
        else
        {
            count += 1;
            poryadok[count] = a[i] - '0';
        }
    }

    if (count < 0)
    {
        return ERROR;
    }
    // переменная для перевода массива символов в число
    int count1 = 0;
    // Перевод массива символов порядка в целочисленное значение
    for (int i = count; i >= 0; i--)
    {
        *por += poryadok[count1] * pow(10,i);
        count1 += 1;
    }
    if (flag_minus == 1)
    {
        *por *= -1;
    }
    //printf("--------por in por is %d-----------\n", *por);
    return OK;
}

//функция округления
void round_mant(int *r, int *count)
{
    *count = 30;
    if (r[*count] >= 5)
    {
        r[*count - 1] += 1;
    }
    *count -= 1;
    while (r[*count] >= 9 )
    {
        r[*count - 1] += 1;
        *count -= 1;
    }

}
//вывод информации для пользователя
void inf()
{
    printf("Программа умножает вещественное число на целое\n");
    printf("примеры ввода вещественного числа:\n");
    printf("0.123Е-5\n");
    printf("123\n");
    printf("0.123Е-5\n");
    printf("мантиса числа - не более 30 символов\n");
    printf("порядок числа не более 5 символов\n");
    printf("целое число - не более 30 символов\n");
    printf("знак мантиса Е порядок\n");
}
// функция замены \n на \0 в строке и проверки на кол-во символов
int change_str(char *str, int count)
{
    int i = 0;
    int position = -1;
    while (i != count)
    {

        if (str[i] == '\n')
        {
            position = i;
        }
        i++;
    }
    if (position < 0)
    {
        return ERROR;
    }
    str[position] = '\0';
    return OK;
}
void add_to_por(int *a, int *size, int *por)
{
    int flag = 0;
    //printf("size is: %d ", *size);
    for (int i = 0; i < *size; i++)
    {
        if (a[i] != 0)
        {
            flag = 1;
        }
        if (a[i] == 0 && flag == 0)
        {
            //printf("\n--%d\n", a[i]);
            for (int j = i; j <= *size; j++)
            {
                a[j] = a[j+1];
            }
            i--;
            *por -= 1;
            *size -= 1;
        }
    }
}
int main(void)
{
    setbuf(stdout, NULL);
    char b[N];                  // вещественное число
    char c[N];                  // целое число
    int flag_e;                 // был ли найден символ Е или е
    int count_c = 0;            // кол-во символов в целом числе
    int r[N1] = {0};            //непосредственно результат
    int rc = OK;                //возвращает код ошибки
    int flag_min = 0;           // есть ли минус в мантиссе
    int flag_min1 = 0;          // Есть ли минус в целом числе
    int pos, count = 0;         // позиция буквы E и кол-во считанных символов
    int pos_por = - 1;          // позиция точки до Е для порядка
    char first_num[40];         // строка обработки
    int count_bef = 0;          // кол-во цифр в мантиссе
    int por = 0;                // Порядок числа
    int size;                   // Итоговое кол-во элементов
    inf();
    printf("---------------------------------------------\n");
    printf("Введите вещественное число:\n");
    printf("---------------------------------------------\n");
    //scanf("%s", first_num);
    if (fgets(first_num, 40, stdin) == NULL)
    {
        printf("Не могу считать число :(\n");
        return ERROR;
    }
    rc = change_str(first_num, 40);
    if (rc != OK)
    {
        printf("Слишком много элементов для 1 числа, прочтите информацию :)\n");
        return rc;
    }
    rc = pos_e(first_num, &pos, &count, &flag_e);
    if (rc != OK)
    {
        printf("Вы ввели некорректное число\n");
        return ERROR;
    }
    else
    {
        int flag_por = 0;
        if (flag_e == 1)
        {
            rc = read_mant(first_num, b, &pos, &pos_por, &flag_min, &count_bef, &flag_por);
            //printf("count bef = %d\n", count_bef);
            //show_result(b, count_bef);
            //printf("pos bef is %d", pos_por);
            if (rc == OK && count_bef > 0)
            {
                if (count_bef > 30)
                {
                    printf("Превышено кол-во элементов в мантиссе\n");
                    return ERR_LEN;
                }
                rc = read_por(first_num, pos, &por);
                if (por > 99999 || por < -99999)
                {
                    printf("В порядке слишком много сиволов, прочтите информацию :) \n");
                    return ERROR;
                }
                if (pos_por >= 0)
                {
                    //printf("por is %d\n", por);
                    //printf("before first por = %d\n", por);
                    // Если найдена одна цифра до и после точки
                    if ( flag_por == 1)
                    {
                        pos_por = 0;
                    }
                    else
                    {
                        por += pos_por;
                    }
                    //printf("after first por = %d\n", por);
                }
                if (rc == OK)
                {
                    printf("---------------------------------------------\n");
                    printf("Введите целое число:\n");
                    printf("---------------------------------------------\n");
                    rc = get_from_user1(c, &count_c, &flag_min1);
                    if (rc == OK)
                    {

                        multiply(b,c, count_bef, count_c, r);
                        size = count_bef + count_c;
                        // удалим символы 0 до результата
                        if (r[0] == 0)
                        {
                            for (int i = 0; i < size - 1; i++)
                            {
                                r[i] = r[i+1];

                            }
                            r[size - 1] = 0;
                            size = size - 1;
                        }
                        // удалим незначащие нули
                        while (r[size - 1] == 0)
                        {
                            size--;
                        }
                        por += count_c - 1;
                        if (por > 99999 || por < -99999)
                        {
                            printf("машинный ноль или переполнение порядка\n");
                            return ERR_POR;
                        }
                        if (size > 30)
                        {
                            round_mant(r, &size);
                            por += 1;
                        }
                        add_to_por(r, &size, &por);
                        printf("Ответ:\n");
                        if (flag_min + flag_min1 == 0 || flag_min + flag_min1 == 2)
                        {
                            show_to_user(r,por, size, 1);
                        }
                        else
                        {
                            show_to_user(r,por, size, 0);
                        }
                        printf("\n---------------------------------------------\n");
                    }
                    else
                    {
                        printf("введенное целое число - неверное, проверьте правильность ввода\n");
                    }
                }
                else
                {
                    printf("ошибка чтения порядка\n");
                }
            }
            else
            {
                printf("ошибка чтения мантиссы\n");
            }
        }
        else
        {
            int flag_por = 0;
            rc = read_mant(first_num, b, &pos, &pos_por, &flag_min, &count_bef, &flag_por);
            //printf("count bef is %d\n", count_bef);
            if (rc == OK)
            {
                if (count_bef > 30)
                {
                    printf("Превышено кол-во элементов в мантиссе\n");
                    return ERR_LEN;
                }
                if ( flag_por == 1)
                {
                    pos_por = 0;
                }
                else
                {
                    por += pos_por;
                }

                //printf("pos_por is %d\n", pos_por);
                //printf("por is %d\n", por);
                //por += pos_por;
                printf("---------------------------------------------\n");
                printf("введите целое число\n");
                printf("---------------------------------------------\n");
                rc = get_from_user1(c, &count_c, &flag_min1);
                if (rc == OK)
                {
                    //printf("count_c is %d\n", count_c);
                    multiply(b,c, count_bef, count_c, r);
                    //printf("count_c after is %d\n", count_c);
                    //printf("count_c and count bef are %d %d\n", count_c, count_bef);
                    size = count_bef + count_c;
                    if (r[0] == 0)
                    {
                        for (int i = 0; i < size - 1; i++)
                        {
                            r[i] = r[i+1];

                        }
                        r[size - 1] = 0;
                        size = size - 1;
                    }
                    while (r[size - 1] == 0)
                    {
                        size--;
                    }
                    por += count_c - 1;
                    if (por > 99999 || por < -99999)
                    {
                        printf("машинный ноль или переполнение порядка\n");
                        return ERR_POR;
                    }
                    printf("---------------------------------------------\n");
                    add_to_por(r, &size, &por);
                    printf("Ответ :\n");
                    if (size > 30)
                    {
                        round_mant(r, &size);
                        por += 1;
                    }
                    //printf("size is %d\n", size);
                    if (flag_min + flag_min1 == 0 || flag_min + flag_min1 == 2)
                    {
                        show_to_user(r,por,size, 1);
                    }
                    else
                    {
                        show_to_user(r,por,size, 0);
                    }
                    printf("\n---------------------------------------------\n");
                }
                else
                {
                    printf("введенное целое число - неверное, проверьте правильность ввода\n");
                }
            }
            else
            {
                printf("ошибка чтения мантиссы\n");
            }
        }
    }
    return OK;
}
//1999999999999999999999999999999
//999999999999999999999999999999
//-777777777777777777777777777777
//1999999999999999999999999999998
//199999999999999999999999999998
//199999999999999999999999999998
//199999999999999999999999999998
