#ifndef __IO__H__
#define __IO__H__
#include <stdio.h>
typedef struct GRAPH graph;
struct GRAPH
{
    int weight;
};
int read_graph_from_file(FILE *f, int ***matrix1, int ***matrix2, int *n, int *m);
void print_graph(int **matrix, int n, int m);
#endif
