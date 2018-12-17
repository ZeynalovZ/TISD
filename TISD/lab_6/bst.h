#ifndef _BST_H_
#define _BST_H_
typedef struct BST BST;

struct BST
{
    BST *left, *right;
    int value;
};

BST *bst_add(BST *root, int num);
void bst_free(BST *root);
int count_peaks(BST *root);
#endif
