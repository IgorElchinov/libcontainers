#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int
main(void) {
    int n;
    printf("Input number of elements: ");
    scanf("%d", &n);
    Heap heap = {0};
    printf("Input %d numbers:\n", n);
    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        heap_insert(&heap, i);
        heap_print(&heap);
    }
    for (int i = 0; i < n; ++i) {
        printf("Max: %d\n", heap_erase(&heap));
        heap_print(&heap);
    }
    heap_free(&heap);
//    heap_free(NULL);
    return 0;
}
