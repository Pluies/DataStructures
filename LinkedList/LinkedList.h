#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

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
} LinkedList;

/* Interface */

LinkedList* create();
int insert(LinkedList* l, void* value);
int delete(LinkedList* l, void* value);
int display(LinkedList* l);
int cleanup(LinkedList* l);

#endif

