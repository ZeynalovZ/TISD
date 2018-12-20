#ifndef __LIST_H__
#define __LIST_H__
typedef struct List List_t;
struct List
{
    int entry;
    double time;
    List_t *next;
};
typedef struct
{
    int entry;
    double time;
}QUEUE;
List_t *add(List_t *head, double time);
List_t *pop(List_t *head, int *entries);
void free_all(List_t *head);
List_t *create_list(List_t *head, double time);
List_t *add_end(List_t *head, List_t *language);
int list_size(List_t *head);
#endif
