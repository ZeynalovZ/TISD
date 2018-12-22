#include <stdio.h>

#include "err.h"
#include "io.h"
#include "search.h"

void usage()
{
    printf("please, input as ' app.exe in.txt (graph's includer)\n");
}

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    int code_error = OK;
    int **matrix1 = NULL;
    int **matrix2 = NULL;
    int n, m;
    int start, end;
    int crossroad[BUFSIZE];
    FILE *f;
    if (argc != 2)
    {
        usage();
        code_error = ERR_CMD;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (!f)
        {
            usage();
            code_error = ERR_READ;
        }
        else
        {
            code_error = read_graph_from_file(f, &matrix1, &matrix2, &n, &m);
            if (code_error == OK)
            {
                printf("Первая ");
                print_graph(matrix1, n, m);
                printf("\n");
                printf("Вторая ");
                print_graph(matrix2, n, m);
                printf("Введите вершину из которой ищем, введите вершины в которую ищем\n");
                if (scanf("%d %d", &start, &end) == 2)
                {
                    if (start >= 1 && end >= 1)
                    {
                        overal_matrix_creation(matrix1, matrix2, n, crossroad);
                        search_Dijkstra(matrix1, n, start, end, matrix2);
                    }
                    else
                    {
                        printf("Вершина из которой ищем не может быть меньше 1\n");
                        printf("Вершина поиска не может быть меньше либо равной вершине, из которой ищем путь\n");
                        code_error = ERR_READ;
                    }
                }
                else
                {
                    printf("Ошибка ввода !\n");
                    code_error = ERR_READ;
                }
            }
            fclose(f);
        }
    }

    return code_error;
}
