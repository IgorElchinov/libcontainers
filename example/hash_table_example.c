#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { N = 7 };

char *arr[N] = {"one", "two", "three", "four", "five", "six", "seven"};
char *add = "qwerty123";

void
h_print_first_n(HashTable h, uint16_t n) {
    for (int i = 0; i < 10; ++i) {
        printf("%d: ", i);
        if (h.arr[i] == NULL) {
            printf("(nil)");
        } else {
            ListStr *cur = h.arr[i];
            while (cur != NULL) {
                printf("%s; ", cur->data);
                cur = cur->next;
            }
        }
        printf("\n");
    }
    return;
}

int
main(void) {
    HashTable h;
    srand(time(NULL));
    h_init(&h, MURMUR_3_16, rand());
    printf("Hash func: %p\n", h.hash);
    h_init(&h, MURMUR_3_FAKE32, rand());
    printf("Hash func: %p\n", h.hash);
    for (int i = 0; i < N; ++i) {
        h_insert(&h, arr[i]);
    }
    for (int i = 0; i < N; ++i) {
        printf("%s: %d\n", arr[i], h_find(&h, arr[i]));
    }
    h_print_first_n(h, N);
    printf("%s: %d\n", add, h_find(&h, add));
    
    for (int i = 0; i < N; ++i) {
        h_erase(&h, arr[i]);
        if (i == N / 2) {
            h_print_first_n(h, N);
        }
    }
    for (int i = 0; i < N; ++i) {
        printf("%s: %d\n", arr[i], h_find(&h, arr[i]));
    }
    printf("%s: %d\n", add, h_find(&h, add));

    h_free(&h);
    return 0;
}
