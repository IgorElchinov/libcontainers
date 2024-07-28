#ifndef L2_H
#define L2_H

#include <stddef.h>

typedef struct L2Node {
    int data;
    struct L2Node *next;
    struct L2Node *prev;
} L2Node;

typedef struct L2 {
    L2Node *head;
    L2Node *tail;
    size_t size;
} L2;

typedef enum CheckType {
    SOFT,
    STRONG,
    NOT_NULL
} CheckType;

extern void l2_check_pos(L2 *list, size_t pos, CheckType type, const char func_name[]);
extern void l2_free(L2 *list);
extern void l2_push_back(L2 *list, int val);
extern void l2_push_front(L2 *list, int val);
extern L2Node *l2_get_node(L2 *list, size_t pos);
extern void l2_insert(L2 *list, int val, size_t pos);
extern void l2_erase(L2 *list, size_t pos);
extern void l2_set(L2 *list, int val, size_t pos);
extern void l2_update(L2 *list, int val, size_t pos);
extern int l2_get(L2 *list, size_t pos);
extern L2Node *l2_find(L2 *list, int val);
#endif
