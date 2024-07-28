#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int
main(void) {
    int n;
    scanf("%d", &n);
    Vector v1 = v_init(0);
    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
         v_push_back(&v1, x);
    }
    v_print(&v1);
    Vector v2 = v_init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        v_set(&v2, x, i);
    }
    v_print(&v2);
    int pos, elem;
    scanf("%d%d", &pos, &elem);
    v_insert(&v1, elem, pos);
    v_print(&v1);
    v_erase(&v2, pos);
    v_print(&v2);
    //printf("vget is safe:\n");
    //printf("vget(v1, -1): ");
    //fflush(stdout);
    //printf("%d", vget(v1, -1));
    v_free(&v1);
    v_free(&v2);
    v1.data = v2.data = NULL;

    printf("Copy test. Input number of elements: ");
    scanf("%d", &n);
    v1 = v_init(n);
    printf("Input %d elements:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        v_set(&v1, x, i);
    }
    v_copy(&v1, &v2);
    v_print(&v2);

    v_free(&v1);
    v_free(&v2);
    return 0;
}
