#include "err.h"
#include "io.h"
#include <stdio.h>
#include <malloc.h>
#include <limits.h>
typedef unsigned short word_t;
typedef unsigned char  byte_t;

typedef struct node {
    struct node* next;
    word_t v;
} node_t;

typedef struct {
    node_t* h, *t;
} queue_t;

void   queue_init(queue_t* q){ q->h = q->t = NULL; }
int    queue_empty(queue_t* q){ return (q->h == NULL); }
word_t queue_front(queue_t* q) { return q->h->v; }
int    queue_push(queue_t* q, word_t v);
void   queue_pop(queue_t* q);
void   queue_clear(queue_t* q);

typedef struct {
    word_t v, p;
} vert_t;
byte_t** graph_input(FILE* _in, int* n);
void     graph_free(byte_t** g, int n);
word_t*  graph_bfs(byte_t** g, int n, word_t s, word_t e, int* m);

int main(void){
    int      i, n, m;
    word_t*  p, s, e;
    byte_t** g;
    setbuf(stdout, NULL);
/*   ввод из файла
    FILE* f = fopen("graph.txt", "rt");
    if(f == NULL)
        return 1;
    g = graph_input(f, &n);
    fclose(f);
*/
    g = graph_input(stdin, &n);
    if(g == NULL)
        return 1;

    s = 3;//старт
    e = 4;//конец
    p = graph_bfs(g, n, s, e, &m);
    if(p != NULL){
        printf("path: ");
        for(i = 0; i < m; ++i)
            printf("%u ", p[i]);
        putchar('\n');

        free(p);
    } else
        fputs("error find bfs!\n", stderr);

    graph_free(g, n);
    return 0;
}

//поиск в ширину
word_t* graph_bfs(byte_t** g, int n, word_t s, word_t e, int* m){
    int     i, y;
    queue_t q;
    vert_t* vs;
    word_t  v, *p, *d, *j;

    p  = NULL;
    vs = (vert_t*)malloc((size_t)n * sizeof(vert_t));
    if(vs == NULL)
        return NULL;
    for(i = 0; i < n; ++i)
        vs[i].p = vs[i].v = USHRT_MAX;

    vs[s].v = 0;
    queue_init(&q);
    queue_push(&q, s);

    y = 0;
    while(! queue_empty(&q)){
        v = queue_front(&q);
        queue_pop(&q);
        if(v == e){
            y = 1;
            break;
        }
        for(i = 0; i < n; ++i){
            if((g[v][i] != 0) && (vs[i].v > (vs[v].v + 1))){
                queue_push(&q, (word_t)i);
                vs[i].p = v;
                vs[i].v = vs[v].v + 1;
            }
        }
    }
    queue_clear(&q);

    if(y){
        v = e;
        i = 1;
        while(v != s){
            v = vs[v].p;
            ++i;
        }
        p = (word_t*)malloc((size_t)i * sizeof(word_t));
        if(p == NULL)
            return NULL;

        d = p;
        for(*d++ = e; e != s; e = vs[e].p)
            *d++ = vs[e].p;

        for(--d, j = p; j < d; ++j, --d){
            v  = *d;
            *d = *j;
            *j = v;
        }
        *m = i;
    }
    free(vs);
    return p;
}

/*
ввод неориентированного графа, формат
    N - кол-во вершин  M - кол-во рёбер
*/
byte_t** graph_input(FILE* _in, int* n){
    int      i, j, vn, em, a, b;
    byte_t** g;
    printf("input  count of points and  count \n");
    if((fscanf(_in, "%d %d", &vn, &em) != 2) || (vn <= 1) || (em <= 1))
        return NULL;

    g = (byte_t**)malloc((size_t)vn * sizeof(byte_t*));
    if(g == NULL)
        return NULL;

    for(i = 0; i < vn; ++i){
        g[i] = (byte_t*)calloc((size_t)vn, sizeof(byte_t));
        if(g[i] == NULL){
            i -= 1;
            goto err;
        }
    }

    for(i = 0; i < em; ++i){
        if(fscanf(_in, "%d %d", &a, &b) == 2){
            if((a < vn) && (b < vn))
                g[a][b] = g[b][a] = 1;
        } else
            break;
    }
    *n = vn;
    return g;
err:
    for(j = i; j >= 0; --j)
        free(g[j]);
    free(g);
    return NULL;
}

//удаление графа из памяти
void graph_free(byte_t** g, int n){
    int i;
    for(i = 0; i < n; ++i)
        free(g[i]);
    free(g);
}

//---------------
//вставка
int queue_push(queue_t* q, word_t v){
    node_t* p = (node_t*)malloc(sizeof(node_t));
    if(p != NULL){
        p->v    = v;
        p->next = NULL;
        if(q->h == NULL)
            q->h = q->t = p;
        else {
            q->t->next = p;
            q->t = p;
        }
    }
    return (p != NULL);
}

//извлечение
void queue_pop(queue_t* q){
    node_t* t;
    if(q->h != NULL){
        t    = q->h;
        q->h = q->h->next;
        free(t);
        if(q->h == NULL)
            q->t = NULL;
    }
}

//удаление всех
void queue_clear(queue_t* q){
    while(! queue_empty(q))
        queue_pop(q);
}

//Описание функции алгоритма поиска в ширину

void Breadth_First_Search(int n, int **Graph, bool *Visited, int Node){

    int *List = new int[n]; //очередь

    int Count, Head; // указатели очереди

    int i;

    // начальная инициализация

    for (i = 0; i < n ; i++)
        List[i] = 0;
    Count = Head = 0;
    // помещение в очередь вершины Node
    List[Count++] = Node;
    Visited[Node] = true;
    while (Head < Count) {

        //взятие вершины из очереди

        Node = List[Head++];

        cout << Node + 1 << endl;

        // просмотр всех вершин, связанных с вершиной Node

        for (i = 0 ; i < n ; i++)

            // если вершина ранее не просмотрена

            if (Graph[Node][i] && !Visited[i]){

                // заносим ее в очередь

                List[Count++] = i;

                Visited[i] = true;

            }

    }
}
