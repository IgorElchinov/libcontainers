#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include "deque.h"

typedef Deque Stack;

extern void st_free(Stack *stack);
extern void st_push(Stack *stack, int val);
extern int st_pop(Stack *stack);
extern int st_top(Stack *stack);
extern int st_empty(Stack *stack);
#endif
