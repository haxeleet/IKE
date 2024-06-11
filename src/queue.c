#include "queue.h"

#include <stdlib.h>

typedef struct _node_t _node_t;
struct _node_t {
	chunk_t*	ptr;
	_node_t*	prev;
	_node_t*	next;
};

_node_t*	_node_create(chunk_t* data);
void			_node_free(_node_t** node);

queue_t* que_create()
{
	queue_t* que = calloc(1, sizeof(queue_t));

	return que;
}

_node_t* _node_create(chunk_t* data)
{
	_node_t* node = calloc(1, sizeof(_node_t));
	node->ptr = data;

	return node;
}

void que_free(queue_t** que)
{
	_node_t* node = (*que)->rear;
	_node_t* pre;
	while(node != NULL) {
		pre = node->prev;
		_node_free(&node);
		node = pre;
	}
}

void _node_free(_node_t** node)
{
	if((*node)->ptr)
		chk_free(&((*node)->ptr));
	free(*node);
}

void enqueue(queue_t* que, chunk_t* data)
{
	_node_t* node = _node_create(data);

	if(que->rear == NULL) {
		que->rear = que->front = node;
	}
	else {
		((_node_t*)que->front)->prev = node;
		node->next = que->front;
		que->front = node;
	}
}

chunk_t* dequeue(queue_t* que)
{
	chunk_t* data = NULL;

	if(que->rear != NULL) {
		_node_t* node = que->rear;
		// if only 1 node
		if(que->rear == que->front) {
			que->rear = que->front = NULL;
		} else {
			(node->prev)->next = NULL;
			que->rear = node->prev;
		}

		data = node->ptr;
		node->ptr = NULL;
		_node_free(&node);
	}

	return data;
}
