#include "Tree.h"

/* Helper functions */

node* createNode(void* value){
	node* n = malloc(sizeof(node));
	n->value = value;
	n->rhc = n->lhc = n->parent = NULL;
	return n;
}

int isEmpty(Tree* t){
	return t->size == 0;
}

int displayNodes(int leadingDashes, node* n){
	if (n != NULL) {
		displayNodes(leadingDashes+1, n->lhc);
		int i;
		for (i=0; i<leadingDashes; i++) printf("- ");
		printf("Value %d, at %p, rhc at %p, lhc at %p, ", *((int*)n->value), n, n->rhc, n->lhc);
		if (n->parent == NULL) printf("root.\n");
		else                   printf("parent at %p.\n", n->parent);
		displayNodes(leadingDashes+1, n->rhc);
	}
	return EXIT_SUCCESS;
}

int cleanupNodes(node* n){
	if (n != NULL){
		cleanupNodes(n->rhc);
		cleanupNodes(n->lhc);
		free(n);
	}
	return EXIT_SUCCESS;
}

int insertNode(node* n, node* head){
	// Sorting on addresses. Why not!
	if (n->value == head->value) return EXIT_SUCCESS; // Do not allow duplicates
	if (n->value >  head->value) {
		if (head->rhc == NULL){
			head->rhc = n;
			n->parent = head;
			return EXIT_SUCCESS;
		} else {
			return insertNode(n, head->rhc);
		}
	}
	if (n->value <  head->value) {
		if (head->lhc == NULL){
			head->lhc = n;
			n->parent = head;
			return EXIT_SUCCESS;
		} else {
			return insertNode(n, head->lhc);
		}
	}
}

void rebalance(Tree* t){
	// TODO
	return;
}


/* Interface */

Tree* create(){
	Tree* t = malloc(sizeof(Tree));
	t->size = t->insertsSinceBalancing = 0;
	t->head = NULL;
	return t;
}

int insert(Tree* t, void* value){
	node* n = createNode(value);
	if (isEmpty(t)) {
		t->head = n;
	} else {
		insertNode(n, t->head);
	}
	t->size += 1;
	t->insertsSinceBalancing += 1;
	if (t->insertsSinceBalancing > (0.25 * t->size))
		rebalance(t);
	return EXIT_SUCCESS;
}

node* findSuccessor(node* n){
	assert(n != NULL);
	if (n->rhc == NULL)
		return n;
	else
		return findSuccessor(n->rhc);
}

node* deleteInTree(node* n, void* value){
	assert(n != NULL);
	while (n->value != value){
		if (value > n->value) n = n->rhc;
		if (value < n->value) n = n->lhc;
		if (n == NULL) return NULL;
	}
	// We now have the correct node to delete
	if (n->parent == NULL){
		// Deleting root
		return n;
	}
	if (n->lhc == NULL) {
		if (n->parent->lhc == n) n->parent->lhc = n->rhc;
		if (n->parent->rhc == n) n->parent->rhc = n->rhc;
		if (n->rhc != NULL) n->rhc->parent = n->parent;
		return n;
	}
	if (n->rhc == NULL) {
		if (n->parent->lhc == n) n->parent->lhc = n->lhc;
		if (n->parent->rhc == n) n->parent->rhc = n->lhc;
		if (n->lhc != NULL) n->lhc->parent = n->parent;
		return n;
	}
	// Hard case: we're deleting a node with two children.
	// We'll keep the right-hand successor as new value
	node* successor = findSuccessor(n->lhc);
	n->value = successor->value;
	return deleteInTree(successor, successor->value);
}

int delete(Tree* t, void* value){
	if (isEmpty(t)) return EXIT_FAILURE;

	node* toFree = deleteInTree(t->head, value);

	if(toFree == NULL){
		// Didn't find the node to delete
		return EXIT_FAILURE;
	} else {
		free(toFree);
		t->size -= 1;
		if(isEmpty(t)) t->head = NULL;
		return EXIT_SUCCESS;
	}
}

int display(Tree* t){
	if (isEmpty(t)) {
		printf("Tree is empty.\n");
	} else {
		printf("Tree has %d element(s).\n", t->size);
	}
	return displayNodes(0, t->head);
}

int cleanup(Tree* t){
	// Recursively free nodes if need be
	cleanupNodes(t->head);
	free(t);
	return EXIT_SUCCESS;
}

