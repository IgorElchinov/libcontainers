#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

enum {
    N = 10,
    TEST_NUM1 = 10,
    TEST_NUM2 = -10,
};

int
main(void) {
    Stack s = {0};
    
    printf("Insert elements\n");
    st_push(&s, TEST_NUM1 * (s.size + 1));
    st_push(&s, TEST_NUM1 * (s.size + 1));
    st_push(&s, TEST_NUM2 * (s.size + 1));
    st_push(&s, TEST_NUM2 * (s.size + 1));
    printf("Is empty: %d, size: %lu\n", st_empty(&s), s.size);
    
    printf("Top element: %d\n", st_top(&s));

    printf("Delete elements\n");
    printf("Top element: %d\n", st_pop(&s));
    printf("Top element: %d\n", st_pop(&s));
    printf("Is empty: %d, size: %lu\n", st_empty(&s), s.size);
    
    printf("Free stack\n");
    st_free(&s);
    printf("Is empty: %d, size: %lu\n", st_empty(&s), s.size);
    return 0;
}








