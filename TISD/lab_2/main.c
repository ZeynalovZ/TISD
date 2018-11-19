#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "err.h"
#include "io.h"
#include "operations.h"
#include <locale.h>

//БЫСТРАЯ СОРТРОВКА todo
void menu()
{
    printf("Введите действие\n");
    printf("1 - Добавить строку в базу\n");
    printf("2 - Удалить строку из базы по имени\n");
    printf("3 - Вывести таблицу\n");
    printf("4 - Отсортировать ключи по именам и вывести их\n");
    printf("5 - Отсортировать таблицу по именам и вывести ее\n");
    printf("6 - Отсортировать ключи по именам и вывести базу \n");
    printf("7 - Сравнить сортировку по ключам и сортировку базу \n");
    printf("8 - Сравнить быструю сортировку и сортировку пузырьком\n");
    printf("9 - Выйти\n");
    printf("input your choice: ");
    printf("\nВведите действие: ");
}

int main(void)
{
    setbuf(stdout, NULL);
    //setlocale(LC_ALL, "Russian");
    int rc = OK;
    int action = 0; //Для запуска цикла
    user base[N];
    key keys[TABLE];
    int count;
    count = read_base(base);
    printf("count is %d\n", count);
    do
    {
        printf("\n\n-------------------------------\n");
        menu();
        if ((rc = read_int(&action, MENU_LEN)) == OK)
        {
            switch (action)
            {
            case 1:
                rc = add_line(base, count);
                count ++;
                break;
            case 2:
                delete_line(base, &count);
                break;
            case 3:
                print_table(base, count);
                break;
            case 4:
                read_keys(keys, base, count);
                bubble_keys(keys, count);
                print_keys(keys, count);
                break;
            case 5:
                bubble_sort_table(base, count);
                read_keys(keys, base, count);
                print_table(base, count);
                break;
            case 6:
                read_keys(keys, base, count);
                bubble_keys(keys, count);
                print_table_by_keys(base, keys, count);
                break;
            case 7:
                time_table(base, keys, count);
                break;
            case 8:
                time_keys(base, keys, count);
                break;
            case 9:
                printf("Пока !\n");
                break;
            default :
                printf("incorrect input\n");
                break;
            }
            if (rc != OK)
            {
                printf("Your input is not right. Try again\n");
            }
        }
        else
        {
            printf("incorrect input\n");
        }
    }
    while (action != 9);

    //user a[N];
    /*
    FILE *file_out;
    file_out = fopen("table2.txt", "w");
    if (!file_out)
    {
        return FILE_CREATE;
    }

    user client;
    strcpy(client.name, "Зейнал");
    strcpy(client.surname, "Зейналов");
    strcpy(client.adress, "Аваин-4");
    strcpy(client.phone_number, "+7(928)-054-26-12");
    strcpy(client.type_user.service.post, "manager");
    strcpy(client.type_user.service.service_name, "OOO");
    client.kind = 0;
    client.type_user.personal.day =  25;
    client.type_user.personal.month = 03;
    client.type_user.personal.year = 2000;
    for (int i = 0; i < 20; i++)
    {
        fprintf(file_out,"%s %s %s %s %d %d %d %d\n", client.name, client.surname,
                client.adress, client.phone_number, client.kind, client.type_user.personal.day,
                client.type_user.personal.month, client.type_user.personal.year);
        client.type_user.personal.year += 1;
    }
    //fprintf(file_out, "%s ", client.type_user.service.post);
    //fprintf(file_out, "%s ", client.type_user.service.service_name);
    fclose(file_out);
    */
    return rc;
}
