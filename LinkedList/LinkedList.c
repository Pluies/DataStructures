#include "LinkedList.h"

/* Helper functions */

node* createNode(void* value){
	node* n = malloc(sizeof(node));
	n->value = value;
	n->next = NULL;
	return n;
}

int isEmpty(LinkedList* l){
	return l->size == 0;
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

LinkedList* create(){
	LinkedList* l = malloc(sizeof(LinkedList));
	l->size = 0;
	l->head = NULL;
	return l;
}

int insert(LinkedList* l, void* value){
	if (isEmpty(l)) {
		l->head = createNode(value);
	} else {
		// Insert after the last element
		node* n = l->head;
		while (n->next != NULL) {
			n = n->next;
		}
		n->next = createNode(value);
	}
	l->size += 1;
	return EXIT_SUCCESS;
}

int delete(LinkedList* l, void* value){
	if (isEmpty(l)) return EXIT_FAILURE;

	// If we need to delete the head
	if (l->head->value == value) {
		node* toDelete = l->head;
		l->head = l->head->next;
		free(toDelete);
		l->size -= 1;
		return EXIT_SUCCESS;
	}

	// Otherwise, sequential search
	node* n = l->head;
	do {
		if(n->next->value == value){
			node* toDelete = n->next;
			n->next = n->next->next;
			free(toDelete);
			l->size -= 1;
			return EXIT_SUCCESS;
		}
		n = n->next;
	} while (n->next != NULL);

	return EXIT_FAILURE;
}

int display(LinkedList* l){
	if (isEmpty(l)) {
		printf("List is empty.\n");
	} else {
		printf("List has %d element(s).\n", l->size);
	}
	return displayNodes(l->head);
}

int cleanup(LinkedList* l){
	// Recursively free nodes if need be
	node* n = l->head;
	node* toDelete;
	while (n != NULL){
		toDelete = n;
		n = n->next;
		free(toDelete);
	}
	free(l);
	return EXIT_SUCCESS;
}

