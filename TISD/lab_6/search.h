#ifndef _SEARCH_H_
#define _SEARCH_H_
#include <stdio.h>
#include "bst.h"
#include "avl.h"
int search_bst(BST *root, int search);
int search_avl(AVL *root, int search);
int search_file(FILE *fsearch, int search);
#endif
