#include <stdio.h>
#include "list.h"

enum {N = 10};

void 
print_list(List *list) {
    for (int i = 0; i < l_len(list); ++i) {
        printf("%d ", l_get(list, i));
    } 
    printf("\n");
    return;
}

int
main(void) {
    List *list = {0};
    for (int i = 0; i < N; ++i) {
       list = l_push_back(list, i);
    }
    print_list(list);
    for (int i = l_len(list); i >= 0; --i) {
        List *cur = l_find(list, i);
        printf("%p ", cur);
	if (cur != NULL) {
            printf("%d", cur->data);
	}
	printf("\n");
    }
    for (; list != NULL;) {
        list = l_erase(list, l_len(list) - 1);
    	print_list(list);
    }
    for (int i = 0; i < N / 2; ++i) {
        list = l_push_back(list, i);
    }
    list = l_insert(list, 10, 0);
    list = l_insert(list, 11, l_len(list));
    list = l_insert(list, 12, l_len(list) / 2);
    list = l_set(list, 20, l_len(list) / 3);
    print_list(list);
    l_free(list); 
    return 0;
}
