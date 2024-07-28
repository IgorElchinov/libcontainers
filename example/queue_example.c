#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

enum {
    N = 10,
    TEST_NUM1 = 10,
    TEST_NUM2 = -10,
};

typedef int * DequeDataType;


int
main(void) {
    Queue q = {0};
    
    printf("Insert elements\n");
    q_enqueue(&q, TEST_NUM1 * (q.size + 1));
    q_enqueue(&q, TEST_NUM1 * (q.size + 1));
    q_enqueue(&q, TEST_NUM2 * (q.size + 1));
    q_enqueue(&q, TEST_NUM2 * (q.size + 1));
    printf("Is empty: %d, size: %lu\n", q_empty(&q), q.size);
    
    printf("First element: %d\n", q_first(&q));

    printf("Delete elements\n");
    printf("First element: %d\n", q_dequeue(&q));
    printf("First element: %d\n", q_dequeue(&q));
    printf("Is empty: %d, size: %lu\n", q_empty(&q), q.size);
    
    printf("Free queue\n");
    q_free(&q);
    printf("Is empty: %d, size: %lu\n", q_empty(&q), q.size);
    return 0;
}








