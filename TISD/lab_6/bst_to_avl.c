//#include <stdio.h>
//#include <stddef.h>
#include "bst_to_avl.h"
#include "bst.h"
#include "avl.h"

void bst_to_avl(BST *tree, AVL **root)
{
    if (tree && root)
    {
        //printf("bst_to_avl: %u\n", (unsigned)offsetof(AVL, right));
        *root = avl_add(*root, tree->value);
        bst_to_avl(tree->left, root);
        bst_to_avl(tree->right, root);
    }
}
