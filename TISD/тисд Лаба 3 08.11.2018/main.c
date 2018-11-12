#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERR_IO -1
#define ERR_INPUT -2

#define N_RAND 50

void print_matrix(int n, int m, int (*p)[m])
{
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j ++)
            printf("%4d ", p[i][j]);
        puts("");
    }
    puts("");
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}

void auto_fill(int n, int m, int percentage, int (*matr)[m])
{
    int zeroes = (n * m) * percentage / 100;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
            matr[i][j] = (rand() % (2*N_RAND) - N_RAND);
    while (zeroes > 0)
    {
        int k = rand() % n;
        int f = rand() % m;
        if (matr[k][f] != 0)
        {
            matr[k][f] = 0;
            zeroes --;
        }
    }
}

void multiply_matrix_form(int *JA, int *IA, int *A, int n, int (*arr)[n], int (*res)[1])
{
    for (int i = 0; i < n; i ++)
    {
        res[i][0] = 0;
        for (int j = JA[i]; j < JA[i+1]; j ++)
        {
            res[i][0] += A[j] * arr[0][IA[j]];
        }
    }
}

void multiply_matrix(int (*res)[1], int n, int m, int n1, int (*matrix1)[m], int (*matrix2)[1])
{
    int sum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            sum = 0;
            for (int k = 0; k < n1; k++)
                sum += matrix1[i][k] * matrix2[k][j];
        }
        res[i][0] = sum;
    }
}
/*
for (int i = 0; i < n1; i++)
           {
               for (int j = 0; j < m2; j++)
               {
                   double sum = 0;
                   for (int k = 0; k < n2; k++)
                   {
                       sum += matrix1[i][k] * matrix2[k][j];
                   }
                   buf[i][j] = sum;
               }
*/
void print(const int *mas, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", mas[i]);
    }
    printf("\n");
}
int non_zeros_elements(int n, int m, int (*matrix)[m])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}
int non_zeros_string(int n, int m, int (*matrix)[m])
{
    int count = 0;
    int flag;
    for (int i = 0; i < n; i++)
    {
        flag = 0;
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != 0)
            {
                flag = 1;
            }
        }
        if (flag == 1)
        {
            count++;
        }
    }
    return count;
}
int count_non_zeros_elem(int n, int m, int (*p)[m])
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (p[i][j] != 0)
            {
                count++;
            }
        }
    return count;
}
void make_matrix_zero(int n, int m, int (*matrix)[m])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = 0;
        }
}
void change_matrix_mean(int *A, int *JA, int *IA, int n, int m, int (*matrix)[m])
{
    int allocated_count = 0;//Кол-во заполненных элементов в массиве А
    int IA_count = 0;
    for (int i = 0; i < n; i++)
    {
        int flag_IA = 0;
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != 0)
            {
                A[allocated_count] = matrix[i][j];
                JA[allocated_count] = j;
                if (flag_IA == 0)
                {
                    IA[IA_count] = allocated_count;
                    flag_IA = 1;
                    IA_count++;
                }
                allocated_count++;
            }
        }
    }
}
int main(void)
{
    setbuf(stdout, NULL);
    srand (time(NULL));
    int code_error = OK;
    long int t1, t2, s1_time = 0, s2_time = 0;
    double result_time = 0;
    int choice, n, m;
    int vector_len;
    int percantage;
    int index_i;
    int index_i_vector;
    int index_j;
    int count_nonzeros_elem = 0;
    int non_zero_elem;
    int non_zeros_strings, non_zeros_strings_res;
    int non_zero_elem_vector;
    size_t memory;
    printf("Введите размерность разреженной матрицы:\n");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Вы ввели неверную размерность!");
        code_error = ERR_INPUT;
    }
    else
    {
        if (scanf("%d", &m) != 1 || m <= 0)
        {
            printf("Вы ввели неверную размерность!");
            code_error = ERR_INPUT;
        }
        else
        {
            int matrix[n][m];
            make_matrix_zero(n, m, matrix);
            printf("Введите кол-во элементов в векторе столбце:\n");
            if (scanf("%d", &vector_len) != 1 || vector_len <= 0)
            {
                printf("Ошибка ввода элементов вектора столбца");
                code_error = ERR_INPUT;
            }
            else
            {
                if (m != vector_len)
                {
                    printf("Размерности матрицы и вектора столбца не совпадают, невозможно найти результат их произведения\n");
                    return -1;
                }
                int vector[1][vector_len];
                int result[vector_len][1];
                if (code_error == OK)
                {
                    printf("Как заполнить матрицу?:\n 1) - Вручную\n 2) Автоматически\n 3) Замерить время\nВыберите цифру:");
                    if (scanf("%d", &choice) != 1)
                    {
                        printf("Неверный ввод!\n");
                        code_error = ERR_IO;
                    }
                    else
                    {
                        switch (choice) {
                        case 1:

                            printf("Введите кол-во ненулевых элементов вектора столбца:\n");
                            if (scanf("%d", &non_zero_elem_vector) == 1 && non_zero_elem_vector <= vector_len )
                                for (int i = 0; i < non_zero_elem_vector; i++)
                                {
                                    printf("Введите индекс строки, а затем ненулевое значение\n");
                                    while (scanf("%d ", &index_i_vector) != 1 || index_i_vector >= vector_len || index_i_vector < 0)
                                    {
                                        printf("Вы допустили ошибку, попробуйте ввести еще раз\n");
                                    }
                                    while (scanf("%d", &vector[0][index_i_vector]) != 1 || vector[0][index_i_vector] == 0)
                                    {
                                        printf("Введите ненулевой элемент!:\n");
                                    }
                                }
                            else
                            {
                                printf("ошибка ввода!");
                                code_error = -2;
                            }
                            if (code_error != OK)
                            {
                                return -2;
                            }
                            printf("Введите кол-во ненулевых элементов в матрице:\n");
                            if (scanf("%d", &count_nonzeros_elem) == 1 && count_nonzeros_elem <= n*m)
                            {
                                for (int i = 0; i < count_nonzeros_elem; i++)
                                {
                                    printf("Введите индексы строки и столбца, а затем ненулевое значение\n");
                                    while (scanf("%d %d", &index_i, &index_j) != 2 || index_i < 0 || index_j < 0 || index_i >=  n || index_j >= m)
                                    {
                                        printf("Вы допустили ошибку, попробуйте ввести еще раз\n");
                                    }
                                    printf("Введите ненулевой элемент!\n");
                                    while (scanf("%d", &non_zero_elem) != 1 || non_zero_elem == 0)
                                    {
                                        printf("Введите ненулевой элемент!:\n");
                                    }
                                    matrix[index_i][index_j] = non_zero_elem;
                                }
                                print_matrix(n, m, matrix);
                                non_zeros_strings = non_zeros_string(n, m, matrix);
                                int JA[count_nonzeros_elem];
                                int A[count_nonzeros_elem];
                                int IA[vector_len];
                                change_matrix_mean(A, JA, IA, n, m, matrix);
                                IA[non_zeros_strings] = count_nonzeros_elem;
                                for (int i = non_zeros_strings + 1; i < vector_len + 1; i++ )
                                {
                                    IA[i] = 0;
                                }
                                printf("A is: ");
                                print(A, count_nonzeros_elem);
                                printf("JA is: ");
                                print(JA, count_nonzeros_elem);
                                printf("IA is: ");
                                print(IA, non_zeros_strings + 1);
                                printf("\n");
                                multiply_matrix_form(IA, JA, A, vector_len, vector, result);
                                printf("result is \n");
                                print_matrix(vector_len, 1, result);
                                int JA1[count_nonzeros_elem];
                                int A1[count_nonzeros_elem];
                                int IA1[vector_len];
                                change_matrix_mean(A1, JA1, IA1, vector_len, 1, result);
                                non_zeros_strings_res = non_zeros_string(vector_len, 1, result);
                                IA1[non_zeros_strings] = non_zeros_strings_res;
                                printf("A1 is: ");
                                print(A1, count_nonzeros_elem);
                                printf("JA1 is: ");
                                print(JA1, count_nonzeros_elem);
                                printf("IA1 is: ");
                                print(IA1, non_zeros_strings_res + 1);
                                printf("\n");
                            }
                            break;
                        case 2:
                            printf("Введите процент заполнения матрицы нулями:");
                            if ((scanf("%d", &percantage)) == 1)
                            {
                                if (percantage > 0 && percantage < 100)
                                {
                                    auto_fill(n, m, percantage, matrix);
                                    auto_fill(vector_len, 1, percantage, vector);
                                    print_matrix(n, m, matrix);
                                    print_matrix(vector_len, 1, vector);
                                    non_zeros_strings = non_zeros_string(n, m, matrix);
                                    count_nonzeros_elem = non_zeros_elements(n, m, matrix);
                                    int JA[count_nonzeros_elem];
                                    int A[count_nonzeros_elem];
                                    int IA[vector_len];
                                    change_matrix_mean(A, JA, IA, n, m, matrix);
                                    IA[non_zeros_strings] = count_nonzeros_elem;
                                    for (int i = non_zeros_strings + 1; i < vector_len + 1; i++ )
                                    {
                                        IA[i] = 0;
                                    }
                                    if (m == vector_len)
                                    {
                                        multiply_matrix_form(IA, JA, A, vector_len, vector, result);
                                        printf("result is \n");
                                        //print_matrix(vector_len, 1, result);
                                        print_matrix(vector_len, 1, result);
                                        count_nonzeros_elem = count_non_zeros_elem(vector_len, 1, result);
                                        int JA1[count_nonzeros_elem];
                                        int A1[count_nonzeros_elem];
                                        int IA1[vector_len];
                                        change_matrix_mean(A1, JA1, IA1, vector_len, 1, result);
                                        non_zeros_strings_res = non_zeros_string(vector_len, 1, result);
                                        IA1[non_zeros_strings] = non_zeros_strings_res;
                                        printf("A1 is: ");
                                        print(A1, count_nonzeros_elem);
                                        printf("JA1 is: ");
                                        print(JA1, count_nonzeros_elem);
                                        printf("IA1 is: ");
                                        print(IA1, non_zeros_strings_res + 1);
                                        printf("\n");
                                    }
                                    else
                                    {
                                        printf("Матрицы невозможно перемножить\n");
                                    }

                                }
                                else
                                {
                                    printf("Процент не может быть равен %d", percantage);
                                }

                            }
                            break;
                        case 3:
                            printf("Введите процент заполнения матрицы нулями:");
                            if ((scanf("%d", &percantage)) == 1)
                            {
                                if (percantage >= 0 && percantage < 100)
                                {

                                    for (int i = 0; i < 50; i ++)
                                    {
                                        auto_fill(n, m, percantage, matrix);
                                        auto_fill(vector_len, 1, percantage, vector);
                                        non_zeros_strings = non_zeros_string(n, m, matrix);
                                        count_nonzeros_elem = non_zeros_elements(n, m, matrix);
                                        int JA[count_nonzeros_elem];
                                        int A[count_nonzeros_elem];
                                        int IA[vector_len];
                                        change_matrix_mean(A, JA, IA, n, m, matrix);
                                        IA[non_zeros_strings] = count_nonzeros_elem;
                                        for (int i = non_zeros_strings + 1; i < vector_len + 1; i++ )
                                        {
                                            IA[i] = 0;
                                        }
                                        /*
                                        printf("count non_zeros is %d\n", count_nonzeros_elem);
                                        IA[non_zeros_strings] = count_nonzeros_elem;
                                        IA[non_zeros_strings + 1] = 0;
                                        printf("A is: ");
                                        print(A, count_nonzeros_elem);
                                        printf("JA is: ");
                                        print(JA, count_nonzeros_elem);
                                        printf("IA is: ");
                                        print(IA, non_zeros_strings + 2);
                                        printf("\n");
                                        print_matrix(n, m, matrix);
                                        print_matrix(vector_len, 1, vector);
                                        */

                                        t1 = tick();
                                        multiply_matrix_form(IA, JA, A, vector_len, vector, result);
                                        t2 = tick();
                                        //print(result, vector_len);
                                        s1_time += (t2 - t1);
                                        memory = sizeof(A) + sizeof(JA);
                                    }
                                    for (int i = 0; i < 50; i ++)
                                    {
                                        auto_fill(n, m, percantage, matrix);
                                        auto_fill(vector_len, 1, percantage, vector);
                                        t1 = tick();
                                        multiply_matrix(result, n, m, vector_len, matrix, vector);
                                        //break;
                                        t2 = tick();
                                        s2_time += (t2 - t1);
                                    }

                                    printf("Занимаемая память:\n");
                                    printf("Обычная: %I64d\n", sizeof(matrix));
                                    printf("В разреженном формате: %I64d\n", memory);
                                    printf("Время умножения обьыным умножением матриц: %ld\n", (long int)(s2_time/50));
                                    printf("Время умножения данным методом: %ld\n", (long int)(s1_time/50));
                                    if (s1_time <= s2_time)
                                    {
                                        result_time = ((double)(s2_time - s1_time)/s2_time) * 100;
                                        printf("метод быстрее простого умножения матриц на %lf процентов\n", result_time);
                                    }
                                    else
                                    {
                                        result_time = ((double)(s1_time - s2_time)/s1_time) * 100;
                                        printf("простое умножение матриц быстрее метода на %lf процентов\n", result_time);
                                    }
                                }
                                else
                                {
                                    printf("Процент не может быть равен %d", percantage);
                                }
                            }
                            break;
                        default:
                            printf("Вы ввели некоректные данные. Можете выбрать только 1, 2 или 3!\n");
                            break;
                            }
                        }
                    }
                }
            }

        }

    return code_error;
}
