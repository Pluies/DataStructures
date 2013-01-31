#include "Stack.h"

/* Helper functions */

node* createNode(void* value){
	node* n = malloc(sizeof(node));
	n->value = value;
	n->next = NULL;
	return n;
}

int isEmpty(Stack* s){
	return s->size == 0;
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

Stack* create(){
	Stack* s = malloc(sizeof(Stack));
	s->size = 0;
	s->head = NULL;
	return s;
}

int push(Stack* s, void* value){
	node* n = createNode(value);
	n->next = s->head;
	s->head = n;
	s->size += 1;
	return EXIT_SUCCESS;
}

void* pop(Stack* s){
	if (isEmpty(s)) return NULL;

	node* toPop = s->head;
	void* value = toPop->value;
	s->head = toPop->next;
	free(toPop);
	s->size -= 1;
	return value;
}

int display(Stack* s){
	if (isEmpty(s)) {
		printf("Stack is empty.\n");
	} else {
		printf("Stack has %d element(s).\n", s->size);
	}
	return displayNodes(s->head);
}

int cleanup(Stack* s){
	// Recursively free nodes if need be
	node* n = s->head;
	node* toDelete;
	while (n != NULL){
		toDelete = n;
		n = n->next;
		free(toDelete);
	}
	free(s);
	return EXIT_SUCCESS;
}

