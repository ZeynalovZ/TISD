#include <stdlib.h>
#include "search.h"
#include "bst.h"
#include "avl.h"

int search_bst(BST *root, int search)
{
    int cmp = 0;
    while (root)
    {
        ++cmp;
        if (root->value == search)
        {
            return cmp;
        }
        else
        {
            ++cmp;
            if (search > root->value)
                root = root->right;
            else
                root = root->left;
        }
    }
    return cmp;
}

int search_avl(AVL *root, int search)
{
    int cmp = 0;
    while (root)
    {
        ++cmp;
        if (root->value == search)
        {
            return cmp;
        }
        else
        {
            ++cmp;
            if (search > root->value)
                root = root->right;
            else
                root = root->left;
        }
    }
    return cmp;
}

int search_file(FILE *fsearch, int search)
{
    rewind(fsearch);
    int cmp = 0;
    int num;
    char dummy;
    int got;
    do
    {
        got = fscanf(fsearch, "%d%c", &num, &dummy);
        ++cmp;
        if (got && num == search)
            return cmp;
    } while (got > 0);
    return cmp;
}
