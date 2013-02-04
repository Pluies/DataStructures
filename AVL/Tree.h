#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Type declarations */

typedef struct node node;
struct node {
	void* value;
	node* parent; // For easier manipulation
	node* rhc; // Right-hand child
	node* lhc; // Left-hand child
};

typedef struct {
	int size;
	node* head;
} Tree;

/* Interface */

Tree* create();
int insert(Tree* t, void* value);
int delete(Tree* t, void* value);
int display(Tree* t);
int cleanup(Tree* t);
int check(Tree* t);

#endif

