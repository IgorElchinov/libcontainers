#ifndef BST_H
#define BST_H
#include "vector.h"

typedef struct BSTreeNode {
    int data;
    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
} BSTreeNode;

typedef struct BSTree {
    BSTreeNode *root;
} BSTree;

extern void bst_free(BSTree *tree);
extern void bst_print(BSTree *tree);
extern void bst_insert(BSTree *tree, int elem);
extern void bst_erase(BSTree *tree, int elem);
extern int bst_find(BSTree *tree, int elem);
extern Vector bst_to_vector(BSTree *tree);
#endif
