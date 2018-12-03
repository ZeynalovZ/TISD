#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "err.h"
List_t *add(List_t *head, double time)
{
    List_t *tmp = NULL;
    tmp = malloc(sizeof(List_t));
    if (tmp == NULL)
    {
        return NULL;
    }
    else
    {
        if (head == NULL)
        {
            tmp->time = time;
            tmp->next = NULL;
            head = tmp;
            return head;
        }
        else
        {
            List_t *head_last = head;
            while (head->next)
            {
                head = head->next;
            }
            tmp->time = time;
            tmp->next = NULL;
            head->next = tmp;
            return head_last;
        }
    }

}
List_t *add_end(List_t *head, List_t *language)
{
    List_t *cur = head;

    if (!head)
        return language;

    for (; cur->next; cur = cur->next);

    cur->next = language;

    return head;
}
List_t *create_list(List_t *head, double time)
{
    List_t *tmp = malloc(sizeof(List_t));
    if (tmp)
    {
        tmp->time = time;
        tmp->next = NULL;
        head = tmp;
    }
    return head;
}

List_t *create_list1(List_t *head, int entries)
{
    List_t *tmp = malloc(sizeof(List_t));
    if (tmp)
    {
        tmp->time = entries;
        tmp->next = NULL;
        head = tmp;
    }
    return head;
}


List_t *pop(List_t *head, int *entries)
{
    List_t *tmp;
    tmp = head;
    //printf("tmp is %p\n", tmp);
    *entries = head->time;
    head = head->next;
    free(tmp);
    return head;
}
int list_size(List_t *head)
{
    int count = 0;
    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}
void free_all(List_t *head)
{
    List_t *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}
