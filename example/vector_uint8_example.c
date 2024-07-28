#include <stdio.h>
#include <stdlib.h>
#include "vector_uint8.h"

int
main(void) {
    int n;
    scanf("%d", &n);
    Vector_uint8 v1 = vu8_init(0);
    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        vu8_push_back(&v1, x);
    }
    vu8_print(v1);
    Vector_uint8 v2 = vu8_init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        vu8_set(&v2, x, i);
    }
    vu8_print(v2);
    int pos, elem;
    scanf("%d%d", &pos, &elem);
    vu8_insert(&v1, elem, pos);
    vu8_print(v1);
    vu8_erase(&v2, pos);
    vu8_print(v2);
    //printf("vget is safe:\n");
    //printf("vget(v1, -1): ");
    //fflush(stdout);
    //printf("%d", vu8_get(v1, -1));
    free(v1.data);
    free(v2.data);
    return 0;
}
