#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct HeapNode {
    int data;
    struct HeapNode *left;
    struct HeapNode *right;
    struct HeapNode *parent;
} HeapNode;

typedef struct Heap {
    HeapNode *root;
    size_t depth;
    size_t last_node_ind;
} Heap;

extern void heap_free(Heap *heap);
extern void heap_print(Heap *heap);
extern void heap_insert(Heap *heap, int elem);
extern int heap_erase(Heap *heap);

#endif
