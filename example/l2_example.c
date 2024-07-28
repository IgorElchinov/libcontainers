#include <stdio.h>
#include <stdlib.h>
#include "l2.h"

enum {
    N = 10,
    TEST_NUM = 0,
    TEST_IND1 = 0,
    TEST_IND2 = 5,
    TEST_IND3 = 22,
};

void
l2_print(L2 list) {
    L2Node *cur = list.head;
    while(cur != NULL) {
        printf("%d ", cur->data);
    	cur = cur->next;
    }
    printf("\n");
    return;
}

int
main(void) {
    L2 list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;

    printf("Push_back number from 1 to 10\n");
    for (int i = 0; i < N; ++i) {
        l2_push_back(&list, i + 1);
    }
    l2_print(list);
    printf("List2 size: %lu\n", list.size);

    printf("Push_front number from -10 to -1\n");
    for (int i = N; i > 0; --i) {
        l2_push_front(&list, -i);
    }
    l2_print(list);
    printf("List2 size: %lu\n", list.size);

    printf("Insert %d to %d, %d and %d\n", TEST_NUM, TEST_IND1, TEST_IND2, TEST_IND3);
    l2_insert(&list, TEST_NUM, TEST_IND1);
    l2_insert(&list, TEST_NUM, TEST_IND2);
    l2_insert(&list, TEST_NUM, TEST_IND3);
    l2_print(list);
    printf("List2 size: %lu\n", list.size);

    printf("Erase %d, %d and %d\n", TEST_IND3, TEST_IND2, TEST_IND1);
    l2_erase(&list, TEST_IND3);
    l2_erase(&list, TEST_IND2);
    l2_erase(&list, TEST_IND1);
    l2_print(list);
    printf("List2 size: %lu\n", list.size);

    printf("Set %d, %d and %d to %d\n", TEST_IND1, TEST_IND2, TEST_IND3, TEST_NUM);
    l2_set(&list, TEST_NUM, TEST_IND1);
    l2_set(&list, TEST_NUM, TEST_IND2);
    l2_set(&list, TEST_NUM, TEST_IND3 - 5);
    l2_print(list);
    printf("List2 size: %lu\n", list.size);

    printf(
        "Get %d, %d and %d: %d %d %d\n",
        TEST_IND1, TEST_IND2, TEST_IND3,
        l2_get(&list, TEST_IND1),
        l2_get(&list, TEST_IND2),
        l2_get(&list, TEST_IND3 - 5)
    );

    L2Node *tmp = l2_find(&list, TEST_NUM);
    printf("Find %d : %p (data - %d, prev - %p, next - %p)\n",
        TEST_NUM, tmp, tmp->data, tmp->prev, tmp->next);

    tmp = l2_get_node(&list, TEST_IND2);
    printf("Get node %d : %p (data - %d, prev - %p, next - %p)\n",
        TEST_IND2, tmp, tmp->data, tmp->prev, tmp->next);

    printf("Free list\n");
    l2_free(&list);
    printf("List: head - %p, tail - %p, size - %lu\n", list.head, list.tail, list.size);

    printf("List is safe\n");
    fflush(stdout);
//    l2_set(&list, TEST_NUM, list.size);
//    l2_set(NULL, TEST_NUM, list.size);
//    l2_get(&list, list.size);
//    l2_insert(&list, TEST_NUM, list.size);
    l2_insert(&list, TEST_NUM, list.size + 1);
    return 0;
}








