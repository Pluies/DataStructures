#include "Queue.h"

/* Helper functions */

node* createNode(void* value){
	node* n = malloc(sizeof(node));
	n->value = value;
	n->next = NULL;
	return n;
}

int isEmpty(Queue* q){
	return q->size == 0;
}

int displayNodes(node* n){
	if (n != NULL) {
		printf("Value %d, ", *((int*)n->value));
		if (n->next == NULL){
			printf("last node.\n");
			return EXIT_SUCCESS;
		} else {
			printf("next node at %p\n", n->next);
			return displayNodes(n->next);
		}
	}
	return EXIT_SUCCESS;
}


/* Interface */

Queue* create(){
	Queue* q = malloc(sizeof(Queue));
	q->size = 0;
	q->head = q->tail = NULL;
	return q;
}

int push(Queue* q, void* value){
	node* n = createNode(value);
	if (isEmpty(q)) {
		q->head = n;
	} else {
		q->tail->next = n;
	}
	q->tail = n;
	q->size += 1;
	return EXIT_SUCCESS;
}

void* pop(Queue* q){
	if (isEmpty(q)) return NULL;

	node* toPop = q->tail;
	void* value;

	if (q->head == q->tail) {
		q->head = q->tail = NULL;
	} else {
		node* n = q->head;
		while (n->next != q->tail) n = n->next;
		q->tail = n;
		n->next = NULL;
	}

	value = toPop->value;
	free(toPop);
	q->size -= 1;
	return value;
}

int display(Queue* q){
	if (isEmpty(q)) {
		printf("Queue is empty.\n");
	} else {
		printf("Queue has %d element(s).\n", q->size);
	}
	return displayNodes(q->head);
}

int cleanup(Queue* q){
	// Recursively free nodes if need be
	node* n = q->head;
	node* toDelete;
	while (n != NULL){
		toDelete = n;
		n = n->next;
		free(toDelete);
	}
	free(q);
	return EXIT_SUCCESS;
}

