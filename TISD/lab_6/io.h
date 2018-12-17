#ifndef _IO_H_
#define _IO_H_
#include "bst.h"
#include "avl.h"
#include "hash_table.h"
int fread_bst(char *filename, BST **tree);
int fread_avl(char *filename, AVL **tree);
int bst_export(char *filename, char *tree_name, BST *tree);
int avl_export(char *filename, char *tree_name, AVL *tree);
int fwrite_array(char *filename, int n, int *arr);
#endif
