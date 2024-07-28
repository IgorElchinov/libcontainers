#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int
main(void) {
    int n;
    printf("Input number of elements: ");
    scanf("%d", &n);
    BSTree tree = {0};
    printf("Input %d numbers:\n", n);
    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        bst_insert(&tree, x);
    }

    Vector v = {0};
    v = bst_to_vector(&tree);
    v_print(&v);
    free(v.data);
    
    printf("Input numbers of quaries: ");
    scanf("%d", &n);
    getchar();
    printf("Input %d queries: \"+ x\" to add x," 
            "\"? x\" to ask whether x is in tree, \"- x\" to erase x:\n", n);
    char q;
    for (int i = 0; i < n; ++i) {
        scanf("%c %d", &q, &x);
        getchar();
        switch (q) {
            case '+':
                bst_insert(&tree, x);
                printf("Added:\n");
                v = bst_to_vector(&tree);
                v_print(&v);
                free(v.data);
                break;
            case '-':
                bst_erase(&tree, x);
                printf("Erased:\n");
                v = bst_to_vector(&tree);
                v_print(&v);
                free(v.data);
                break;
            case '?':
                printf("Has %d: %s\n", x, bst_find(&tree, x) ? "True" : "False");
                break;
            default:
                printf("No such command.\n");
                printf("Input queries: \"+ x\" to add x," 
                        "\"? x\" to ask whether x is in tree, \"- x\" to erase x:\n");
                break;
        }
    }

    bst_print(&tree);
    bst_free(&tree);
//    free_tree(NULL);
    return 0;
}
