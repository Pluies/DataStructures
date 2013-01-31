#ifndef __STACK_H__
#define __STACK_H__

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
} Stack;

/* Interface */

Stack* create();
int push(Stack* l, void* value);
void* pop(Stack* l);
int display(Stack* l);
int cleanup(Stack* l);

#endif

