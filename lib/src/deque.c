#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

void
dq_check(Deque *d, const char func_name[]) {
    if (d == NULL) {
        fprintf(stderr, "%s: deque is NULL\n", func_name);
        fflush(stderr);
        exit(1);
    }
    return;
}

void
dq_free(Deque *d) {
    dq_check(d, "dq_free\0");
    DequeNode *cur = d->head;
    while (cur != NULL) {
        DequeNode *next = cur->next;
        free(cur);
        cur = next;
    }
    d->head = NULL;
    d->tail = NULL;
    d->size = 0;
    return;
}

void
dq_check_empty(Deque *d, const char func_name[]) {
    if (d->size == 0) {
        fprintf(stderr, "%s: deque is empty\n", func_name);
        fflush(stderr); 
        dq_free(d);
        exit(1);
    }
    return;
}

void
dq_print(Deque *d) {
    fprintf(stderr, "size: %ld head: %p tail %p\n", d->size, d->head, d->tail);
    for (DequeNode *node = d->head; node != NULL; node = node->next) {
        fprintf(stderr, "%p: %p %d %p\n", node, node->prev, node->data, node->next);
    }
    fflush(stderr);
}

void
dq_push_back(Deque *d, int val) {
    dq_check(d, __func__);
    if (d->size == 0) {
        d->head = calloc(1, sizeof(*d->head));
        if (d->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            dq_free(d);
            exit(1);
        }
        d->head->data = val;
        d->tail = d->head;
        d->head->prev = NULL;
        d->head->next = NULL;
        d->size = 1;
    } else {
        d->tail->next = calloc(1, sizeof(*d->head));
        if (d->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            dq_free(d);
            exit(1);
        }
        d->tail->next->data = val;
        d->tail->next->next = NULL;
        d->tail->next->prev = d->tail;
        d->tail = d->tail->next;
        d->size++;
    }
    return;
}

void
dq_push_front(Deque *d, int val) {
    dq_check(d, __func__);
    if (d->size == 0) {
        d->head = calloc(1, sizeof(*d->head));
        if (d->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            dq_free(d);
            exit(1);
        }
        d->head->data = val;
        d->tail = d->head;
        d->head->prev = NULL;
        d->head->next = NULL;
        d->size = 1;
    } else {
        d->head->prev = calloc(1, sizeof(*d->head));
        if (d->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            dq_free(d);
            exit(1);
        }
        d->head->prev->data = val;
        d->head->prev->next = d->head;
        d->head->prev->prev = NULL;
        d->head = d->head->prev;
        d->size++;
    }
    return;
}

int
dq_pop_back(Deque *d) {
    dq_check(d, __func__);
    dq_check_empty(d, __func__);
    int res = d->tail->data;
    DequeNode *new_tail = d->tail->prev;
    free(d->tail);
    d->tail = new_tail;
    d->size--;
    if (d->tail == NULL) {
        d->head = NULL;
    } else {
        d->tail->next = NULL;
    }
    return res;
}

int
dq_pop_front(Deque *d) {
    dq_check(d, __func__);
    dq_check_empty(d, __func__);
    int res = d->head->data;
    DequeNode *new_head = d->head->next;
    free(d->head);
    d->head = new_head;
    d->size--;
    if (d->head == NULL) {
        d->tail = NULL;
    } else {
        d->head->prev = NULL;
    }
    return res; 
}       

inline int
dq_front(Deque *d) {
    dq_check(d, __func__);
    dq_check_empty(d, __func__);
    return d->head->data;
}

inline int
dq_back(Deque *d) {
    dq_check(d, __func__);
    dq_check_empty(d, __func__);
    return d->tail->data;
}

inline int
dq_empty(Deque *d) {
    return d->size == 0;
}


