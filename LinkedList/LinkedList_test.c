#include "LinkedList.h"

int main(int argc, char** argv){
	
	LinkedList* l = create();

	int a=1, b=2, c=3, d=4, e=5, f=6;

	printf("Inserting all data...\n");
	insert(l, &a);
	insert(l, &b);
	insert(l, &c);
	insert(l, &d);
	insert(l, &e);
	insert(l, &f);
	display(l);

	printf("\nDeleting 'b'...\n");
	delete(l, &b);
	display(l);

	printf("\nDeleting 'f'...\n");
	delete(l, &f);
	display(l);
	
	printf("\nDeleting 'a'...\n");
	delete(l, &a);
	display(l);

	printf("\nDeleting the rest...\n");
	delete(l, &c);
	delete(l, &d);
	delete(l, &e);
	display(l);

	printf("\nRe-inserting two elements...\n");
	insert(l, &a);
	insert(l, &f);
	display(l);

	printf("\nCleaning up...\n");
	cleanup(l);
	return 0;
}
