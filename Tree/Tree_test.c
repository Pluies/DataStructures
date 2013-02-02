#include "Tree.h"

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
	return 0;
}
