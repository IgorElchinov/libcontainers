#include "l2.h"
#include <stdio.h>
#include <stdlib.h>

void
l2_check_pos(L2 *list, size_t pos, CheckType type, const char func_name[]) {
    if (list == NULL) {
        fprintf(stderr, "%s: list is NULL\n", func_name);
        fflush(stderr);
        exit(1);
    }
    if (type == NOT_NULL) {
        return;
    }
    if (type == STRONG && pos >= list->size) {
        fprintf(stderr, "%s: list index is out of range\n", func_name);
        fflush(stderr);
        l2_free(list);
        exit(1);
    }
    if (type == SOFT && pos > list->size) {
        fprintf(stderr, "%s: list index is out of range\n", func_name);
        fflush(stderr);
        l2_free(list);
        exit(1);
    }
    return;
}

void
l2_free(L2 *list) {
    l2_check_pos(list, 0, NOT_NULL, __func__);
    L2Node *cur = list->head;
    while (cur != NULL) {
        L2Node *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void
l2_push_back(L2 *list, int val) {
    l2_check_pos(list, 0, NOT_NULL, __func__); 
    if (list->size == 0) {
        list->head = calloc(1, sizeof(*list->head));
        if (list->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            l2_free(list);
            exit(1);
        }
        list->head->data = val;
        list->tail = list->head;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->size = 1;
    } else {
        list->tail->next = calloc(1, sizeof(*list->head));
        if (list->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            l2_free(list);
            exit(1);
        }
        list->tail->next->data = val;
        list->tail->next->next = NULL;
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->size++;
    }
}

void
l2_push_front(L2 *list, int val) {
    l2_check_pos(list, 0, NOT_NULL, __func__); 
    if (list->size == 0) {
        list->head = calloc(1, sizeof(*list->head));
        if (list->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            l2_free(list);
            exit(1);
        }
        list->head->data = val;
        list->tail = list->head;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->size = 1;
    } else {
        list->head->prev = calloc(1, sizeof(*list->head));
        if (list->head == NULL) {
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            fflush(stderr);
            l2_free(list);
            exit(1);
        }
        list->head->prev->data = val;
        list->head->prev->next = list->head;
        list->head->prev->prev = NULL;
        list->head = list->head->prev;
        list->size++;
    }
}

L2Node *
l2_get_node(L2 *list, size_t pos) {
    l2_check_pos(list, 0, STRONG, __func__); 
    if (pos < list->size / 2) {
        L2Node *cur = list->head;
        int i = 0;
        while (cur != NULL) {
            if (i == pos) {
                return cur;
            }
            ++i;
            cur = cur->next;
        }
    } else {
        L2Node *cur = list->tail;
        int i = list->size - 1;
        while (cur != NULL) {
            if (i == pos) {
                return cur;
            }
            --i;
            cur = cur->prev;
        }
    }
    return NULL;
}

void
l2_insert(L2* list, int val, size_t pos) {
    l2_check_pos(list, pos, SOFT, __func__); 
    if (pos == 0) {
        l2_push_front(list, val);
        return;
    }
    if (pos == list->size) {
        l2_push_back(list, val);
        return;
    }
    L2Node *cur = l2_get_node(list, pos - 1);
    L2Node *tmp = cur->next;
    cur->next = calloc(1, sizeof(*cur));
    if (cur->next == NULL) {
        fprintf(stderr, "%s: memory allocation error\n", __func__);
        fflush(stderr);
        l2_free(list);
        exit(1);
    }
    tmp->prev = cur->next;
    cur->next->data = val;
    cur->next->prev = cur;
    cur->next->next = tmp;
    list->size++;
    return;
}       

void
l2_erase(L2* list, size_t pos) {
    l2_check_pos(list, pos, STRONG, __func__);
    if (pos == 0) {
        L2Node *new_head = list->head->next;
        free(list->head);
        list->head = new_head;
        list->size--;
        if (list->head == NULL) {
            list->tail = NULL;
        } else {
            list->head->prev = NULL;
        }
        return; 
    }
    if (pos == list->size - 1) {
        L2Node *new_tail = list->tail->prev;
        free(list->tail);
        list->tail = new_tail;
        list->size--;
        if (list->tail == NULL) {
            list->head = NULL;
        } else {
            list->tail->next = NULL;
        }
        return;
    }
    L2Node *cur = l2_get_node(list, pos);
    L2Node *prev = cur->prev;
    L2Node *next = cur->next;
    free(cur);
    prev->next = next;
    next->prev = prev;
    list->size--;
}       


void
l2_set(L2 *list, int val, size_t pos) {
    l2_check_pos(list, pos, STRONG, __func__);
    L2Node *cur = l2_get_node(list, pos);    
    cur->data = val;
    return;
}

inline void
l2_update(L2 *list, int val, size_t pos) {
    l2_set(list, val, pos);
    return;
}

int
l2_get(L2 *list, size_t pos) {
    l2_check_pos(list, pos, STRONG, __func__);
    L2Node *cur = l2_get_node(list, pos);
    return cur->data;
}    

L2Node *
l2_find(L2 *list, int val) {
    l2_check_pos(list, 0, NOT_NULL, __func__);
    L2Node *cur = list->head;
    while (cur != NULL) {
        if (cur->data == val) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
