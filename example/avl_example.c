#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int
main(void) {

    int n;
    printf("Input number of elements: ");
    scanf("%d", &n);
    AVLTree tree = {0};
    printf("Input %d numbers:\n", n);
    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        avl_insert(&tree, x);
//        avl_print(&tree);
    }
//    avl_print(&tree);

    Vector v = {0};
    v = avl_to_vector(&tree);
    v_print(&v);
    v_free(&v);

    printf("Input numbers of quaries: ");
    scanf("%d", &n);
    getchar();
    printf("Input %d queries: \"+ x\" to add x," 
            "\"? x\" to ask whether x is in tree, \"- x\" to erase x:\n", n);
    char q;
    for (int i = 0; i < n; ++i) {
        scanf("%c %d", &q, &x);
        getchar();
        printf("Entered: %c %d\n", q, x);
        switch (q) {
            case '+':
                avl_insert(&tree, x);
                printf("Added:\n");
                v = avl_to_vector(&tree);
                v_print(&v);
                v_free(&v);
                break;
            case '-':
                avl_erase(&tree, x);
                printf("Erased:\n");
                v = avl_to_vector(&tree);
                v_print(&v);
                v_free(&v);
                break;
            case '?':
                printf("Has %d: %s\n", x, avl_find(&tree, x) ? "True" : "False");
                break;
            default:
                printf("No such command.\n");
                printf("Input queries: \"+ x\" to add x," 
                        "\"? x\" to ask whether x is in tree, \"- x\" to erase x:\n");
                break;
        }
    }

    avl_print(&tree);
    avl_free(&tree);
//    avl_free(NULL);
    return 0;
}
