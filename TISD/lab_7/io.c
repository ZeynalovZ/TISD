#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "err.h"
#include "io.h"

#define IMG_VIEWER "mspaint.exe"
#define DOT "C:\\Graphviz2.38\\bin\\dot.exe" //Path to dot.exe
#define APPFOLDER "C:\\Trash"  //Path to trash folder C:\Graphviz2.38\bin C:\Users\зейнал\AppData\Local\Temp

void free_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}


int **allocate_matrix(int n, int m)
{
    int **matrix = NULL;
    matrix = calloc(n, sizeof(int*));
    if (matrix)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i] = malloc(m * sizeof(int));
            if (!matrix[i])
            {
                free_matrix(matrix, i);
                break;
            }
        }
    }
    return matrix;
}

void fill_by_null(int **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void print_graph(int **matrix, int n, int m)
{
    printf("матрица:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void digraph_init(FILE *f)
{
    fprintf(f, "digraph graphname1 {\nrankdir = LR;\n");
}

int read_graph_from_file(FILE *f, int ***matrix1, int ***matrix2, int *n, int *m)
{
    int code_error = OK;
    int **matrix1_tmp = NULL;
    int **matrix2_tmp = NULL;
    int i, j;
    int weight;
    char buffer[BUFSIZE];
    FILE *f1, *f2;
    f1 = fopen(APPFOLDER "\\" "digraph1.gv", "w");
    f2 = fopen(APPFOLDER "\\" "digraph2.gv", "w");
    if (f && f1 && f2)
    {
        if (fscanf(f, "%d %d", n, m) == 2)
        {
            if ( *n <= 1 || *m <= 1)
            {
                printf("Почему то здесь одна вершина, ooops\n");
                code_error = ERR_READ;
            }
            else
            {
                matrix1_tmp = allocate_matrix(*n, *m);
                matrix2_tmp = allocate_matrix(*n, *m);
                //*n = *n - 1;
                //*m = *m - 1;
                fill_by_null(matrix1_tmp, *n, *m);
                fill_by_null(matrix2_tmp, *n, *m);
                digraph_init(f1);
                digraph_init(f2);
                if (matrix1_tmp && matrix2_tmp)
                {
                    while (fscanf(f, "%s", buffer) == 1)
                    {
                        while (fscanf(f, "%d %d %d", &i, &j, &weight) == 3)
                        {
                            if (strcmp("first", buffer) == 0)
                            {
                                matrix1_tmp[i - 1][j - 1] = weight;
                                fprintf(f1, "%d -> %d [label=%d] ;\n", i , j, weight);
                            }
                            else if (strcmp("second", buffer) == 0)
                            {
                                matrix2_tmp[i - 1][j - 1] = weight;
                                fprintf(f2, "%d -> %d [label=%d] ;\n", i , j, weight);
                            }
                        }
                    }
                    *matrix1 = matrix1_tmp;
                    *matrix2 = matrix2_tmp;
                    fprintf(f1, "}\n");
                    fprintf(f2, "}\n");
                    fclose(f1);
                    fclose(f2);
                    system("start " DOT " -Tpng " APPFOLDER "\\" "digraph1.gv" " -o" APPFOLDER "\\" "digraph1.png");
                    system("start " IMG_VIEWER " " APPFOLDER "\\" "digraph1.png");
                    system("start " DOT " -Tpng " APPFOLDER "\\" "digraph2.gv" " -o" APPFOLDER "\\" "digraph2.png");
                    system("start " IMG_VIEWER " " APPFOLDER "\\" "digraph2.png");
                }
                else
                {
                    code_error = ERR_MEM;
                }
            }
        }
        else
        {
            code_error = ERR_READ;
        }
    }
    else
    {
        code_error = ERR_READ;
    }
    return code_error;
}


