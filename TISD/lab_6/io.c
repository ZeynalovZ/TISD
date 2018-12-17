#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "bst.h"
#include "avl.h"
#include "err.h"
#include <time.h>

int is_permited(char sym)
{
    switch (sym)
    {
    case ' ':
        return 1;
    case '\n':
        return 1;
    case '\t':
        return 1;
    default:
        return 0;
    }
}

void arrgen(int n, int *arr)
{
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
        arr[i] = rand();
}

int fread_bst(char *filename, BST **tree)
{
    int rc = OK;
    FILE *fin = fopen(filename, "r");
    if (fin)
    {
        *tree = NULL;
        int num;
        char dummy;
        int got;
        do
        {
            got = fscanf(fin, "%d%c", &num, &dummy);
            if (got == 1 || (got == 2 && is_permited(dummy)))
                *tree = bst_add(*tree, num);
        } while (got == 1 || (got == 2 && is_permited(dummy)));
        if (!feof(fin))
            rc = ERR_IO;
        fclose(fin);
    }
    else
        rc =  ERR_FOPEN;
    return rc;
}

int fread_avl(char *filename, AVL **tree)
{
    int rc = OK;
    FILE *fin = fopen(filename, "r");
    if (fin)
    {
        *tree = NULL;
        int num;
        char dummy;
        int got;
        do
        {
            got = fscanf(fin, "%d%c", &num, &dummy);
            if (got == 1 || (got == 2 && is_permited(dummy)))
                *tree = avl_add(*tree, num);
        } while (got == 1 || (got == 2 && is_permited(dummy)));
        if (!feof(fin))
            rc = ERR_IO;
        fclose(fin);
    }
    else
        rc =  ERR_FOPEN;
    return rc;
}

void bst_to_dot(FILE *fout, BST *root)
{
    if (fout && root)
    {
        if (root->left)
            fprintf(fout, "%d -> %d;\n", root->value, root->left->value);
        if (root->right)
            fprintf(fout, "%d -> %d;\n", root->value, root->right->value);
        bst_to_dot(fout, root->left);
        bst_to_dot(fout, root->right);
    }
}

int bst_export(char *filename, char *tree_name, BST *tree)
{
    if (filename && tree_name)
    {
        FILE *fout = fopen(filename, "w");
        if (fout)
        {
            fprintf(fout, "digraph %s {\n", tree_name);
            bst_to_dot(fout, tree);
            fprintf(fout, "}\n");
            fclose(fout);
            return OK;
        }
        else
            return ERR_FOPEN;
    }
    else
        return ERR_INTERNAL;
}

void avl_to_dot(FILE *fout, AVL *root)
{
    if (fout && root)
    {
        if (root->left)
            fprintf(fout, "%d -> %d;\n", root->value, root->left->value);
        if (root->right)
            fprintf(fout, "%d -> %d;\n", root->value, root->right->value);
        avl_to_dot(fout, root->left);
        avl_to_dot(fout, root->right);
    }
}

int avl_export(char *filename, char *tree_name, AVL *tree)
{
    if (filename && tree_name)
    {
        FILE *fout = fopen(filename, "w");
        if (fout)
        {
            fprintf(fout, "digraph %s {\n", tree_name);
            avl_to_dot(fout, tree);
            fprintf(fout, "}\n");
            fclose(fout);
            return OK;
        }
        else
            return ERR_FOPEN;
    }
    else
        return ERR_INTERNAL;
}

int fwrite_array(char *filename, int n, int *arr)
{
    if (filename && arr && n)
    {
        FILE *fout = fopen(filename, "w");
        if (fout)
        {
            arrgen(n, arr);
            for (int i = 0; i < n; ++i)
                fprintf(fout, "%d ", arr[i]);
            fclose(fout);
            return OK;
        }
        else
            return ERR_FOPEN;
    }
    else
        return ERR_INTERNAL;
}
