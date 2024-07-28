#include <stdio.h>
#include "list_of_map_nodes.h"

enum { N = 7 };

void 
print_list(ListOfMapNodes *list) {
    for (ListOfMapNodes *cur = list; cur != NULL; cur = cur->next) {
        printf("%s : %s\n", cur->data.key, cur->data.value);
    } 
    printf("\n");
    return;
}

char *keys[N] = {"one", "two", "three", "four", "five", "six", "seven"};
char *values[N] = {"value one", "value two", "value three",
        "value four", "value five", "value six", "value seven"};
char *add_key = "qwerty123";
char *add_value = "additional value";

int
main(void) {
    ListOfMapNodes *list = {0};
    for (int i = 0; i < N; ++i) {
       list = lmn_push_back(list, keys[i], values[i]);
    }
    print_list(list);
    for (int i = lmn_len(list) - 1; i >= 0; --i) {
        ListOfMapNodes *cur = lmn_find(list, keys[i]);
        printf("%p ", cur);
	if (cur != NULL) {
            printf("%s : %s\n", cur->data.key, cur->data.value);
	}
	printf("\n");
    }
    ListOfMapNodes *cur = lmn_find(list, add_key);
    printf("%s : %s; %p\n", add_key, add_value, cur);
//    printf("Erasing non-existing key\n");
    fflush(stdout);
//    list = lmn_erase(list, add_key);
    while (list != NULL) {
        list = lmn_erase(list, keys[lmn_len(list) - 1]);
    	print_list(list);
    }
    for (int i = 0; i < N; ++i) {
       list = lmn_push_back(list, keys[i], values[i]);
    }
    lmn_set(list, keys[N/2], add_value);
    for (int i = 0; i < N; ++i) {
        printf("Get %s: %s\n", keys[i], lmn_get(list, keys[i]));
    }
    print_list(list);
    lmn_free(list); 
    list = NULL;
    list = lmn_erase(list, add_key);
    print_list(list);
    return 0;
}
