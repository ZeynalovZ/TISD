#ifndef __LIST_H__
#define __LIST_H__
typedef enum{NUMBER, SIGN} type;
typedef struct Stack Stack;
struct Stack
{
    Stack *prev;
    type kind1;
    union
    {
        char sign;
        int num;
    }u;
};
typedef enum {err_choice_1} err_type;

typedef struct
{
    type kind;
    union
    {
        char sign;
        int num;
    }u;
}base;
void look_back(Stack *list);
void *pop(Stack **list);
void free_list(Stack *list);
Stack *add_to_list(Stack **list);
void from_arr_to_list(base *array, int n, Stack **head);
int calculate_list(Stack *head, int *result);

#endif
