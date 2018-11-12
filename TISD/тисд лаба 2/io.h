#ifndef __IO_H__
#define __IO_H__
#include "err.h"
#define TABLE 45

typedef struct
{
    int index;
    char name[NAME_LENGHT + 1];
}key;
typedef struct
{
    int index;
    char name[NAME_LENGHT + 1];
    char surname[SURNAME_LENGHT + 1];
    char phone_number[PHONE_NUMBER_LENGTH + 1];
    char adress[ADRESS_LENGHT + 1];
    enum{KIND_PERSON, KIND_SERVICE} kind;
    union
    {
        struct
        {
            char post[POST_LENGHT + 1];
            char service_name[SERVICE_LENGHT + 1];
        } service;
        struct
        {
            int day;
            int month;
            int year;
        } personal;
    } type_user;
} user;

int read_base(user *base);

int read_line(char *str, int size);

int read_int(int *a, int n);

void print_table(user *base, int count);

void print_string(user *base, int kind);

void read_keys(key *keys, user *base, int count);

void print_keys(key *keys, int count);

#endif
