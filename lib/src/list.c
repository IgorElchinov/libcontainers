#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *
l_init(int val) {
    List *list = calloc(1, sizeof(*list));
    list->data = val;
    return list;
}

void
l_free(List *list) {
    while (list != NULL) {
        List *next = list->next;
        free(list);
        list = next;
    }
    return;
}

size_t
l_len(List *list) {
    if (list == NULL) {
        return 0;
    }
    size_t size = 1;
    while (list->next != NULL) {
        list = list->next;
        ++size;
    }
    return size;
}

void
l_check_pos(List *list, size_t pos, const char func_name[]) {
    if (pos >= l_len(list)) {
        l_free(list);
        fprintf(stderr, "%s:ist index is out of range\n", func_name);
        exit(1);
    }
    return;
}

List *
l_push_back(List *list, int val) {
    if (list == NULL) {
        return l_init(val);
    }
    List *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = calloc(1, sizeof(*cur));
    cur->next->data = val;
    cur->next->next = NULL;
    return list;
}

List *
l_insert(List *list, int val, size_t pos) {
    size_t size = l_len(list);
    if (pos > size) {
        l_free(list);
	fprintf(stderr, "%s: list index is out of range\n", __func__);
	exit(1);
    }
    if (list == NULL) {
        return l_init(val);
    }
    if (pos == 0) {
        List *cur = l_init(val);
        cur->next = list;
        return cur;
    }
    if (pos == size) {
        List *cur = list;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = l_init(val);
        return list;
    }
    List *cur = list;
    size_t i = 1;
    while (cur->next != NULL) {
        if (i == pos) {
            List *new_node = l_init(val);
            new_node->next = cur->next;
            cur->next = new_node;
            break;
        }
        cur = cur->next;
        ++i;
    }
    return list;
}

List *
l_erase(List *list, size_t pos) {
    l_check_pos(list, pos, __func__);
    if (pos == 0) {
        List *cur = list->next;
        free(list);
        return cur;
    }
    List *cur = list;
    size_t i = 0;
    while (i < pos) {
        if (i == pos - 1) {
	    List *new_next = cur->next->next;
            free(cur->next);
            cur->next = new_next;
            break;
        }
        cur = cur->next;
        ++i;
    }
    return list;        
}

List *
l_set(List *list, int val, size_t pos) {
    l_check_pos(list, pos, __func__);
    size_t i = 0;
    List *cur = list;
    while (i <= pos) {
        if (i == pos) {
            cur->data = val;
            break;
        }
        cur = cur->next;
        ++i;
    }
    return list;
}

inline List *
l_update(List *list, int val, size_t pos) {
    return l_set(list, val, pos);
}

int
l_get(List *list, size_t pos) {
    l_check_pos(list, pos, __func__);
    List *cur = list;
    size_t i = 0;
    while (i <= pos) {
        if (i == pos) {
            return cur->data;
        }
        cur = cur->next;
        ++i;
    }
    return -1;
}

List *
l_find(List *list, int val) {
    List *cur = list;
    while (cur != NULL) {
        if (cur->data == val) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

