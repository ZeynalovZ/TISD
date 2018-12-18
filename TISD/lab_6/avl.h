#ifndef _AVL_H_
#define _AVL_H_
typedef struct AVL AVL;

struct AVL
{
    int value;
    unsigned char height;
    AVL *left, *right;
};

AVL *balance(AVL *p);
AVL *avl_add(AVL *root, int num);
void avl_free(AVL *root);
AVL* del(AVL* p, int k);
#endif
