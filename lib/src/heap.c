#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

void 
check_heap(Heap *heap, const char func_name[]) {
    if (heap == NULL) {
        fprintf(stderr, "%s: tree is NULL\n", func_name);
        fflush(stderr);
        exit(1);
    }
    return;
}

void
free_heap_node(HeapNode *node) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        free_heap_node(node->left);
    }
    if (node->right != NULL) {
        free_heap_node(node->right);
    }
    free(node);
    return;
}

void
heap_free(Heap *heap) {
    check_heap(heap, __func__);
    if (heap->root != NULL) {
        free_heap_node(heap->root);
    }
    heap->root = NULL;
    return;
}

static void
print_node(HeapNode *node, size_t depth) {
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
    printf("ptr: %p; data: %d; parent: %p; left: %p; right: %p\n", 
            node, node->data, node->parent, node->left, node->right);
    return;
}

void
print_heap_helper(HeapNode *node, size_t depth) {
    print_node(node, depth);
    if (node->left != NULL) {
        print_heap_helper(node->left, depth + 1);
    }
    if (node->right != NULL) {
        print_heap_helper(node->right, depth + 1);
    }
    return;
}

void
heap_print(Heap *heap) {
    check_heap(heap, __func__);
    printf("STRUCT HEAP\n");
    printf("root: %p; depth: %lu; last node index: %lu\n", 
            heap->root, heap->depth, heap->last_node_ind);
    if (heap->root == NULL) {
        printf("Heap is empty\n");
        return;
    }
    print_heap_helper(heap->root, 0);
    return;
}

static void
swap(int *a, int * b) {
    int c = *b;
    *b = *a;
    *a = c;
}

static HeapNode *
add_node(int elem, HeapNode *par) {
    HeapNode *node = calloc(1, sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "%s: Memory allocation problem\n", __func__);
        fflush(stderr);
        exit(1);
    }
    node->data = elem;
    node->left = NULL;
    node->right = NULL;
    node->parent = par;
    return node;
}

void
heap_insert(Heap *heap, int elem) {
    check_heap(heap, __func__);
    if (heap->root == NULL) {
        heap->root = add_node(elem, NULL);
        heap->depth = 1;
        heap->last_node_ind = 1;
        return;
    }
    HeapNode *cur = heap->root;
    if (heap->last_node_ind == 1 << (heap->depth - 1)) {
        heap->depth++;
        heap->last_node_ind = 1;
        while (cur->left != NULL) {
            cur = cur->left;
        }
        cur->left = add_node(elem, cur);
        cur = cur->left;
    } else {
        heap->last_node_ind++;
        size_t cur_ind = heap->last_node_ind;
        size_t cur_depth = 1;
        while (cur != NULL && cur_depth < heap->depth - 1) {
            if (cur_ind > 1 << (heap->depth - cur_depth - 1)) {
                cur = cur->right;
                cur_ind -= 1 << (heap->depth - cur_depth - 1);
                cur_depth++;
            } else {
                cur = cur->left;
                cur_depth++;
            }
        }
        if (cur_ind == 1) {
            if (cur->left != NULL) {
                fprintf(stdout, "liberror\n");
            }
            cur->left = add_node(elem, cur);
            cur = cur->left;
        } else {
            if (cur->right != NULL) {
                fprintf(stdout, "liberror\n");
            }
            cur->right = add_node(elem, cur);
            cur = cur->right;
        }
    }
    while (cur != NULL && cur->parent != NULL && cur->data > cur->parent->data) {
        swap(&cur->data, &cur->parent->data);
        cur = cur->parent;
    }
    return;
}

void
heap_erase_raise_error(Heap *heap, const char func_name[]) {
    check_heap(heap, __func__);
    fprintf(stderr, "%s: heap is empty", func_name);
    heap_free(heap);
    exit(2);
    return;
}

int
heap_erase(Heap *heap) {
    check_heap(heap, __func__);
    if (heap->root == NULL || heap->depth == 0) {
        heap_erase_raise_error(heap, __func__);
    }
    
    int result = heap->root->data;
    if (heap->depth == 1) {
        free(heap->root);
        heap->depth = 0;
        heap->last_node_ind = 0;
        heap->root = NULL;
        return result;
    }
    
    HeapNode *cur = heap->root;
    if (heap->last_node_ind == 1) {
        heap->depth--;
        heap->last_node_ind = 1 << (heap->depth - 1);
        while (cur->left != NULL) {
            cur = cur->left;
        }
        cur->parent->left = NULL;
    } else {
        size_t cur_ind = heap->last_node_ind;
        size_t cur_depth = 1;
        while (cur != NULL && cur_depth < heap->depth - 1) {
            if (cur_ind > 1 << (heap->depth - cur_depth - 1)) {
                cur = cur->right;
                cur_ind -= 1 << (heap->depth - cur_depth - 1);
                cur_depth++;
            } else {
                cur = cur->left;
                cur_depth++;
            }
        }
        if (cur_ind == 1) {
            if (cur->left == NULL) {
                fprintf(stderr, "liberror\n");
            }
            cur = cur->left;
            cur->parent->left = NULL;
        } else {
            if (cur->right == NULL) {
                fprintf(stderr, "liberror\n");
            }
            cur = cur->right;
            cur->parent->right = NULL;
        }
        heap->last_node_ind--;
    } 
    swap(&cur->data, &heap->root->data);
    free(cur);
    
    cur = heap->root;
    while (cur != NULL) {
        int swapped = 0;
        if (cur->left != NULL && cur->right != NULL) {
            if (cur->left->data > cur->right->data) {
                if (cur->data < cur->left->data) {
                    swap(&cur->data, &cur->left->data);
                    cur = cur->left;
                    swapped = 1;
                }
            } else {
                if (cur->data < cur->right->data) {
                    swap(&cur->data, &cur->right->data);
                    cur = cur->right;
                    swapped = 1;
                }
            }
        } else if (cur->left == NULL && cur->right != NULL) {
            if (cur->data < cur->right->data) {
                swap(&cur->data, &cur->right->data);
                cur = cur->right;
                swapped = 1;
            }
        } else if (cur->left != NULL && cur->right == NULL) {
            if (cur->data < cur->left->data) {
                swap(&cur->data, &cur->left->data);
                cur = cur->left;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return result;
}






