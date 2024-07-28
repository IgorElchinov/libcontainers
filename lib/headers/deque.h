#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

typedef struct DequeNode {
    int data;
    struct DequeNode *next;
    struct DequeNode *prev;
} DequeNode;

typedef struct Deque {
    DequeNode *head;
    DequeNode *tail;
    size_t size;
} Deque;

extern void dq_print(Deque *d);
extern void dq_free(Deque *d);
extern void dq_push_front(Deque *d, int val);
extern void dq_push_back(Deque *d, int val);
extern int dq_pop_front(Deque *d);
extern int dq_pop_back(Deque *d);
extern int dq_front(Deque *d);
extern int dq_back(Deque *d);
extern int dq_empty(Deque *d);
#endif
