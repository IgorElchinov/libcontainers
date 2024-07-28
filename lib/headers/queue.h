#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include "deque.h"

typedef Deque Queue;

extern void q_free(Queue *q);
extern void q_enqueue(Queue *q, int val);
extern int q_dequeue(Queue *q);
extern int q_first(Queue *q);
extern int q_empty(Queue *q);
#endif
