#include <stdio.h>
#include <windows.h>
#include "bst.h"
#include "avl.h"
#include "io.h"
#include "bst_to_avl.h"
#include "hash_table.h"
#include "search.h"
#include "err.h"
#define IMG_VIEWER "mspaint.exe"
#define DOT "C:\\release\\bin\\dot.exe" //Path to dot.exe
#define BSTDOTNAME "BST.gv"
#define BSTIMGNAME "BST.png"
#define APPFOLDER "C:\\Trash"  //Path to trash folder C:\Graphviz2.38\bin C:\Users\зейнал\AppData\Local\Temp
#define AVLDOTNAME "AVL.gv"
#define AVLIMGNAME "AVL.png"
#define TMPFILE "tmp"
#define FILENAME_LEN 70
#define N 100

unsigned long long tick()
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void print_error(int rc)
{
    if (rc == ERR_FOPEN)
        printf("Error while opening file\n");
    else if (rc == ERR_IO)
        printf("Input error\n");
    else if (rc == ERR_INTERNAL)
        printf("Internal error\n");
    else if (rc == ERR_MEM)
        printf("Memory error\n");

}

int main()
{
    setbuf(stdout, NULL);
    int rc = OK;
    char finname[FILENAME_LEN] = { 0 };
    printf("Enter input file name:\n");
    if (!fgets(finname, FILENAME_LEN, stdin) || !finname[1])
        rc = ERR_IO;
    if (rc == OK)
    {
        if (finname[strlen(finname) - 1] == '\n')
            finname[strlen(finname) - 1] = '\0';
        BST *bstroot = NULL;
        AVL *avlroot = NULL;
        table_t *table = NULL;
        int table_size = 0;
        rc = fread_bst(finname, &bstroot);
        if (rc == OK)
            rc = bst_export(APPFOLDER "\\" BSTDOTNAME, "BST", bstroot);
        if (rc == OK)
        {
            system(DOT " -Tpng " APPFOLDER "\\" BSTDOTNAME " -o" APPFOLDER "\\" BSTIMGNAME);
            system("start " IMG_VIEWER " " APPFOLDER "\\" BSTIMGNAME);
        }
        if (rc == OK)
        {
            bst_to_avl(bstroot, &avlroot);
            if (rc == OK)
                rc = avl_export(APPFOLDER "\\" AVLDOTNAME, "AVL", avlroot);
            if (rc == OK)
            {
                system(DOT " -Tpng " APPFOLDER "\\" AVLDOTNAME " -o" APPFOLDER "\\" AVLIMGNAME);
                system("start " IMG_VIEWER " " APPFOLDER "\\" AVLIMGNAME);
            }
        }
        if (rc == OK)
        {
            rc = create_table(&table, finname, &table_size);
            print_hash_table(table, table_size);
        }
        if (rc == OK)
        {
            int search, maxcmp;
            printf("Enter a number to delete:\n");
            scanf("%d", &search);
            printf("Enter max comparisons number:\n");
            scanf("%d", &maxcmp);
            if (maxcmp > 0)
            {
                unsigned long long tb, te;
                tb = tick();
                int cmp_bst = search_bst(bstroot, search);
                te = tick();
                unsigned long long time_bst = te - tb;
                tb = tick();
                int cmp_avl = search_avl(avlroot, search);
                te = tick();
                unsigned long long time_avl = te - tb;
                tb = tick();
                int cmp_table = search_table(table, table_size, search);
                te = tick();
                unsigned long long time_table = te - tb;
                tb = te = 0;
                FILE *fsearch = fopen(finname, "r");
                int cmp_file = 0;
                unsigned long long time_file = 0;
                if (fsearch)
                {
                    tb = tick();
                    cmp_file = search_file(fsearch, search);
                    te = tick();
                    time_file = te - tb;
                    fclose(fsearch);
                }
                int elements_count = count_peaks(bstroot);
                printf("Structure\tSize (bytes)\tTackts\tComparisons\n");
                printf("BST:% 17d% 15d% 10d\n", elements_count *
                       (int)(sizeof(BST)),(int)(time_bst), cmp_bst);
                printf("AVL:% 17d% 15d% 10d\n", elements_count *
                       (int)(sizeof(AVL)), (int)(time_avl), cmp_avl);
                printf("Table:% 15d% 15d% 10d\n", table_size * (int)(sizeof(table_t)) +
                       elements_count * (int)(sizeof(table)), (int)(time_table), cmp_table);
                printf("File:% 16d% 15d% 10d\n", 0, (int)(time_file), cmp_file);
                printf("Note: file size was not considered\n");

                if (cmp_table > maxcmp)
                {
                    printf("\nAfter restructing hash table:\n");
                    table_t *res = NULL;
                    int new_size = 0;
                    cmp_table = restruct(table, table_size, search, &res, &new_size, maxcmp);
                    if (res)
                    {
                        free(table);
                        table = res;
                        table_size = new_size;
                        delete_from_table(table, search, table_size);
                        print_hash_table(table, table_size);
                        printf("Table size:% 15d\n", table_size *(int)(sizeof(table_t))
                               + elements_count * (int)(sizeof(table)));
                        printf("Comparisons amount: %d\n", cmp_table);
                    }
                    else
                        rc = ERR_MEM;
                }

            }
            else
                rc = ERR_IO;
        }
        if (bstroot)
            bst_free(bstroot);
        if (avlroot)
            avl_free(avlroot);

        if (table)
            free(table);

        bstroot = NULL;
        avlroot = NULL;
        table = NULL;
        table_size = 0;
        if (rc == OK)
        {
            int arr[N];
            //fwrite_array(TMPFILE, N, arr);
            rc = fread_bst(finname, &bstroot);
            if (rc == OK)
            {
                bst_to_avl(bstroot, &avlroot);
                rc = create_table(&table, finname, &table_size);

            }
            if (rc == OK)
            {

                fwrite_array(TMPFILE "1", N, arr);
                FILE *fin = fopen(TMPFILE "1", "r");
                FILE *fsearch = fopen(TMPFILE, "r");
                if (fin && fsearch)
                {
                    unsigned long long tb = 0, te = 0;
                    unsigned long long tacts_bst = 0, tacts_avl = 0, tacts_table = 0, tacts_file = 0;
                    int cmp_bst = 0, cmp_avl = 0, /*cmp_table = 0,*/ cmp_file = 0;

                    int num;
                    char dummy;
                    int got;
                    do
                    {

                        got = fscanf(fin, "%d%c", &num, &dummy);
                        if (got)
                        {
                            tb = tick();

                            cmp_bst += search_bst(bstroot, num);

                            te = tick();
                            tacts_bst += te - tb;
                            tb = tick();
                            cmp_avl += search_avl(avlroot, num);
                            te = tick();
                            tacts_avl += te - tb;
                            tb = tick();

                            //cmp_table = search_table(table, table_size, num);

                            te = tick();
                            tacts_table += te - tb;
                            tb = tick();
                            cmp_file += search_file(fsearch, num);
                            te = tick();
                            tacts_file += te - tb;
                        }
                    } while (got > 0);
                    printf("\n\nAverage results (N = %d)\n\n", N);
                    printf("Structure\tTackts\tComparisons\n");
                    printf("BST:% 15g% 10g\n", tacts_bst / (double)(N), cmp_bst / (double)(N));
                    printf("AVL:% 15g% 10g\n", (int)(tacts_avl) / (double)(N), cmp_avl / (double)(N));
                    //printf("Table:% 13g% 10g\n", (int)(tacts_table) / (double)(N), cmp_table / (double)(N));
                    printf("File:% 14g% 10g\n", (int)(tacts_file) / (double)(N), cmp_file / (double)(N));
                    fclose(fin);
                    fclose(fsearch);
                }
            }
            if (bstroot)
                bst_free(bstroot);
            if (avlroot)
                avl_free(avlroot);

            if (table)
                free(table);

            bstroot = NULL;
            avlroot = NULL;
            table = NULL;
            table_size = 0;
        }
    }
    print_error(rc);
}
