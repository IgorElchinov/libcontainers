#include "stack.h"

inline void
st_free(Stack *stack) {
    dq_free(stack);
    return;
}

inline void
st_push(Stack *stack, int val) {
    dq_push_back(stack, val);
    return;
}

inline int
st_pop(Stack *stack) {
    return dq_pop_back(stack);
}

inline int
st_top(Stack *stack) {
    return dq_back(stack);
}

inline int
st_empty(Stack *stack) {
    return dq_empty(stack);
}
