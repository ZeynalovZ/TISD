#include <stdlib.h>
#include "bst.h"

BST *bst_add(BST *root, int num)
{
    if (root)
    {
        if (num > root->value)
            root->right = bst_add(root->right, num);
        else if (num < root->value)
            root->left = bst_add(root->left, num);
        return root;
    }
    else
    {
        BST *newel = malloc(sizeof(BST));
        newel->value = num;
        newel->left = newel->right = NULL;
        return newel;
    }
}

void bst_free(BST *root)
{
    if (root)
    {
        bst_free(root->right);
        bst_free(root->left);
        free(root);
    }
}

int count_peaks(BST *root)
{
    if (root)
    {
        int count = 1;
        if (root->left)
            count += count_peaks(root->left);
        if (root->right)
            count += count_peaks(root->right);
        return count;
    }
    return 0;
}
