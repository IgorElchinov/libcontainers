#include "queue.h"

inline void
q_free(Queue *q) {
    dq_free(q);
    return;
}

inline void
q_enqueue(Queue *q, int val) {
    dq_push_back(q, val);
    return;
}

inline int
q_dequeue(Queue *q) {
    return dq_pop_front(q);
}

inline int
q_first(Queue *q) {
    return q->head->data;
}

inline int
q_empty(Queue *q) {
    return q->size == 0;
}
