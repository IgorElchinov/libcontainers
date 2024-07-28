#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct List {
    int data;
    struct List *next;
} List;

extern List *l_init(int val);
extern void l_free(List *list);
extern size_t l_len(List *list);
extern List *l_push_back(List *list, int val);
extern List *l_insert(List *list, int val, size_t pos);
extern List *l_erase(List *list, size_t pos);
extern List *l_set(List *list, int val, size_t pos);
extern List *l_update(List *list, int val, size_t pos);
extern int l_get(List *list, size_t pos);
extern List *l_find(List *list, int val);
#endif
