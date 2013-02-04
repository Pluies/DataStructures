#include "Tree.h"
#include <time.h>

unsigned int randr(unsigned int min, unsigned int max) {
	// Stolen from StackOverflow
	double scaled = (double)rand()/RAND_MAX;
	return (max - min +1)*scaled + min;
}

int main(int argc, char** argv){
	
	Tree* t = create();

	int a=1, b=2, c=3, d=4, e=5, f=6;

	printf("Pushing all data...\n");
	insert(t, &e);
	insert(t, &c);
	insert(t, &a);
	insert(t, &d);
	insert(t, &b);
	insert(t, &f);
	display(t);

	printf("\nRemoving c...\n");
	delete(t, &c);
	display(t);

	printf("\nRemoving b...\n");
	delete(t, &b);
	display(t);

	printf("\nRemoving d, f, a...\n");
	delete(t, &d);
	delete(t, &f);
	delete(t, &a);
	display(t);
	printf("\nRemoving e...\n");
	delete(t, &e);
	display(t);

	printf("\nRe-pushing two elements...\n");
	insert(t, &a);
	insert(t, &f);
	display(t);

	printf("\nCleaning up...\n");
	cleanup(t);

	// More advanced testing
#define TESTS 1000
	Tree* t2 = create();
	int values[TESTS];
	int* positions[TESTS];
	int i;
	srand(time(NULL));

	for (i=0; i<TESTS; i++) {
		values[i] = i;
	}

	printf("\n\nExtensive testing. Adding %d elements.\n", TESTS);
	for (i=0; i<TESTS; i++) {
		positions[i] = &values[randr(0, TESTS-1)];
		insert(t2, positions[i]);
	}

	printf("t2 size is %d (should be slightly less than %d because of duplicates)\n", t2->size, TESTS);
	check(t2);
	//display(t2);

	int elemsToDelete = TESTS;
	printf("Deleting %d elements.\n", elemsToDelete);
	for (i=0; i<elemsToDelete; i++) {
		delete(t2, positions[i]);
	}
	check(t2);

	printf("\nCleaning up t2...\n");
	cleanup(t2);

	return 0;
}
