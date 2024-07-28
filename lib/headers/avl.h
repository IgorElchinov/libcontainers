#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include "vector.h"

typedef struct AVLNode {
    int data;
    size_t counter;
    size_t height;
    struct AVLNode *left;
    struct AVLNode *right;
    struct AVLNode *parent;
} AVLNode;
 
typedef struct AVLTree {
    AVLNode *root;
} AVLTree;

typedef enum NodeType {
    LEFT_CHILD,
    ROOT,
    RIGHT_CHILD
} NodeType;

extern void avl_free(AVLTree *tree);
extern void avl_print(AVLTree *tree);
extern void avl_insert(AVLTree *tree, int elem);
extern int avl_find(AVLTree *tree, int elem);
extern void avl_erase(AVLTree *tree, int elem);
extern Vector avl_to_vector(AVLTree *tree);
#endif
