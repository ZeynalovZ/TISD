#include "err.h"
#include "io.h"
#include <stdio.h>
#include <malloc.h>
#include <limits.h>

void overal_matrix_creation(int **matrix1, int **matrix2, int n, int *crossroad)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix1[i][j] != 0 && matrix2[i][j] != 0 && matrix2[i][j] < matrix1[i][j])
            {
                matrix1[i][j] = matrix2[i][j];
                crossroad[k] = j;
            }
        }
    }
}
void search_Dijkstra(int **VES, int n, int start, int end)
{
    int infinity=1000;                     // Бесконечность

    int x[100];                            //Массив, содержащий единицы и нули для каждой вершины,
    // x[i]=0 - еще не найден кратчайший путь в i-ю вершину,
    // x[i]=1 - кратчайший путь в i-ю вершину уже найден

    int DlinaPuti[100];                    //t[i] - длина кратчайшего пути от вершины s в i

    int PredVertex[100];                   //h[i] - вершина, предшествующая i-й вершине
    //на кратчайшем пути
    int VERTEX = n;
    int p = VERTEX;
    int v;
    // Будем искать путь из вершины s в вершину g по циклу
    start=start-1;
    for (int prosto=0; prosto<VERTEX; prosto++)
    {
        end=prosto;                         //цикл прогоняет алгоритм Флойда p-ое количество раз преврашая его в алгоритм Дейкстры
        if (end==start) continue;            //исключаем просчет растояния между одной и той же точкой
        else
        {
            // Инициализируем начальные значения массивов
            int u;                                // Счетчик вершин
            for (u=0;u<p;u++)
            {
                DlinaPuti[u]=infinity;                    //Сначала все кратчайшие пути из s в i
                //равны бесконечности
                x[u]=0;                            // и нет кратчайшего пути ни для одной вершины
            }
            PredVertex[start]=0;                     // s - начало пути, поэтому этой вершине ничего не предшествует
            DlinaPuti[start]=0;                      // Кратчайший путь из s в s равен 0
            x[start]=1;                              // Для вершины s найден кратчайший путь
            v=start;                                 // Делаем s текущей вершиной

            while(1)
            {
                // Перебираем все вершины, смежные v, и ищем для них кратчайший путь
                for(u=0;u<p;u++)
                {
                    if(VES[v][u]==0)continue;      // Вершины u и v несмежные
                    if(x[u]==0 && DlinaPuti[u]>DlinaPuti[v]+VES[v][u]) //Если для вершины 'u' еще не
                        //найден кратчайший путь
                        // и новый путь в 'u' короче чем
                        //старый, то
                    {
                        DlinaPuti[u]=DlinaPuti[v]+VES[v][u];            //запоминаем более короткую длину пути в
                        //массив t[и]
                        PredVertex[u]=v;                     //запоминаем, что v->u часть кратчайшего
                        //пути из s->u
                    }
                }

                // Ищем из всех длин некратчайших путей самый короткий
                int w=infinity;                   // Для поиска самого короткого пути
                v=-1;                             // В конце поиска v - вершина, в которую будет
                // найден новый кратчайший путь. Она станет
                // текущей вершиной
                for(u=0;u<p;u++)                  // Перебираем все вершины.
                {
                    if(x[u]==0 && DlinaPuti[u]<w)           // Если для вершины не найден кратчайший
                        // путь и если длина пути в вершину 'u' меньше
                        // уже найденной, то
                    {
                        v=u;                         // текущей вершиной становится 'u'-я вершина
                        w= DlinaPuti[u];
                    }
                }
                if (v == -1)
                {
                    printf("there is no such way\n");
                    break;
                }
                if(v==end)                            // Найден кратчайший путь,
                {                                 // выводим его
                    printf("Кратчайший путь из вершины %d в вершину %d :\n", start + 1, end + 1);
                    u=end;
                    while(u!=start)
                    {
                        printf(" %d\n", u + 1);
                        u=PredVertex[u];
                    }
                    printf("Длина пути - %d\n\n", DlinaPuti[end]);
                    break;
                }
                x[v]=1;
            }
        }
    }
}
