#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "chunk.h"

typedef struct {
  void*   front;
  void*   rear;
}queue_t;

queue_t*  que_create();
void      que_free(queue_t** que);
void      enqueue(queue_t* que, chunk_t* data);
chunk_t*  dequeue(queue_t* que);

#endif //__QUEUE_H__
