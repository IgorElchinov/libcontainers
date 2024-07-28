#include <stdio.h>
#include "list_str.h"

enum { N = 7 };

void 
print_list(ListStr *list) {
    for (ListStr *cur = list; cur != NULL; cur = cur->next) {
        printf("%s ", cur->data);
    } 
    printf("\n");
    return;
}

char *arr[N] = {"one", "two", "three", "four", "five", "six", "seven"};
char *add = "qwerty123";
int
main(void) {
    ListStr *list = {0};
    for (int i = 0; i < N; ++i) {
       list = ls_push_back(list, arr[i]);
    }
    print_list(list);
    for (int i = ls_len(list) - 1; i >= 0; --i) {
        ListStr *cur = ls_find(list, arr[i]);
        printf("%p ", cur);
	if (cur != NULL) {
            printf("%s", cur->data);
	}
	printf("\n");
    }
    ListStr *cur = ls_find(list, add);
    printf("%s: %p\n", add, cur);
    fflush(stdout);
    for (; list != NULL;) {
        list = ls_erase(list, arr[ls_len(list) - 1]);
    	print_list(list);
    }
    for (int i = 0; i < N; ++i) {
       list = ls_push_back(list, arr[i]);
    }
    print_list(list);
    ls_free(list); 
    list = NULL;
    list = ls_erase(list, add);
    print_list(list);
    return 0;
}
