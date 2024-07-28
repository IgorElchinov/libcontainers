#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

enum {
    N = 10,
    TEST_NUM1 = 10,
    TEST_NUM2 = -10,
};

typedef int * DequeDataType;


int
main(void) {
    Deque d = {0};
    
    printf("Insert elements\n");
    dq_push_front(&d, TEST_NUM1 * (d.size + 1));
    dq_push_front(&d, TEST_NUM1 * (d.size + 1));
    dq_push_back(&d, TEST_NUM2 * (d.size + 1));
    dq_push_back(&d, TEST_NUM2 * (d.size + 1));
    printf("Is empty: %d, size: %lu\n", dq_empty(&d), d.size);
    
    printf("First element: %d\n", dq_front(&d));
    printf("Last element: %d\n", dq_back(&d));

    printf("Delete elements\n");
    printf("First element: %d\n", dq_pop_front(&d));
    printf("Last element: %d\n", dq_pop_back(&d));
    printf("Is empty: %d, size: %lu\n", dq_empty(&d), d.size);
    
    printf("Free list\n");
    dq_free(&d);
    printf("Is empty: %d, size: %lu\n", dq_empty(&d), d.size);
    return 0;
}








