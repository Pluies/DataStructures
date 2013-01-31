#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdio.h>

/* Type declarations */

typedef struct node node;
struct node {
	void* value;
	node* next;
};

typedef struct {
	int size;
	node* head;
	node* tail;
} Queue;

/* Interface */

Queue* create();
int push(Queue* q, void* value);
void* pop(Queue* q);
int display(Queue* q);
int cleanup(Queue* q);

#endif

