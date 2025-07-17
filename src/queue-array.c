#include "include/queue-array.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_CHUNK 2
bool _grow_queue(struct RBTraversalQueue *q) {
  if (q->front > 0 && q->back - q->front > 1) {
    memmove(q->queue, &q->queue[q->front],
            (q->back + 1 - q->front) * sizeof(*q->queue));
    q->back = q->back - q->front;
    q->front = 0;
    return true;
  }

  int o = q->back == -1 ? 0 : q->back;
  void *tmp = realloc(q->queue, (q->size + QUEUE_CHUNK) * sizeof(*q->queue));
  if (tmp) {
    q->size += QUEUE_CHUNK;
    q->queue = tmp;
  }

  return tmp != NULL;
}

#define IS_QUEUE_EMPTY(q) ((q)->front == -1)

void _rbtt_enq(struct RBTraversalQueue *q, void *node) {
  if (IS_QUEUE_EMPTY(q)) {
    q->front = 0;
  }
  if ((q->back + 1 > q->size) || q->back < 0) {
    if (!_grow_queue(q)) {
      return;
    }
  }
  q->back++;
  q->queue[q->back] = node;
}

struct RBNode *_rbtt_deq(struct RBTraversalQueue *q) {
  if (IS_QUEUE_EMPTY(q)) {
    return NULL;
  }
  struct RBNode *n = q->queue[q->front];
  if (q->front == q->back) {
    q->front = -1;
    q->back = -1;
  } else {
    q->front++;
  }
  return n;
}
