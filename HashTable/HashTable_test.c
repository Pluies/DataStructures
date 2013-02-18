#include "HashTable.h"
#include <time.h>

unsigned int randr(unsigned int min, unsigned int max) {
	// Stolen from StackOverflow
	double scaled = (double)rand()/RAND_MAX;
	return (max - min +1)*scaled + min;
}

int main(int argc, char** argv){
	
	HashTable* h = create();

	int a=1, b=2, c=3, d=4, e=5, f=6;

	printf("Pushing all data...\n");
	set(h, "e", &e);
	set(h, "c", &c);
	set(h, "a", &a);
	set(h, "d", &d);
	set(h, "b", &b);
	set(h, "f", &f);
	display(h);

	printf("Value of a and c: %d and %d (should be 1 and 3)\n", *((int*)lookup(h,"a")), *((int*)lookup(h,"c")));

	printf("\nRemoving c...\n");
	unset(h, "c");
	display(h);

	printf("\nSetting a and c to 1...\n");
	set(h, "a", &a);
	set(h, "c", &a);
	display(h);

	printf("Value of a and c: %d and %d (should be 1 and 1)\n", *((int*)lookup(h,"a")), *((int*)lookup(h,"c")));

	printf("\nCleaning up...\n");
	cleanup(h);

	return 0;

	printf("\nRemoving b...\n");
	unset(h, "b");
	display(h);

	printf("\nRemoving d, f, a...\n");
	unset(h, "d");
	unset(h, "f");
	unset(h, "a");
	display(h);
	printf("\nRemoving e...\n");
	unset(h, "e");
	display(h);

	printf("\nRe-pushing two elements...\n");
	set(h, "a", &a);
	set(h, "f", &f);
	display(h);

	printf("\nCleaning up...\n");
	cleanup(h);

	// More advanced testing
	/*
#define TESTS 1000
	HashTable* t2 = create();
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
		set(t2, positions[i]);
	}

	printf("t2 size is %d (should be slightly less than %d because of duplicates)\n", t2->size, TESTS);
	check(t2);
	//display(t2);

	int elemsToDelete = TESTS;
	printf("Deleting %d elements.\n", elemsToDelete);
	for (i=0; i<elemsToDelete; i++) {
		unset(t2, positions[i]);
	}
	check(t2);

	printf("\nCleaning up t2...\n");
	cleanup(t2);
	*/

	return 0;
}
