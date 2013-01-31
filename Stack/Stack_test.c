#include "Stack.h"

int main(int argc, char** argv){
	
	Stack* l = create();

	int a=1, b=2, c=3, d=4, e=5, f=6;
	int* result;

	//printf("Pushing all data...\n");
	push(l, &a);
	push(l, &b);
	push(l, &c);
	push(l, &d);
	push(l, &e);
	push(l, &f);
	//display(l);

	result = (int*)pop(l);
	//printf("\nPopping an element... Got %d\n", *result);
	//display(l);

	result = (int*)pop(l);
	//printf("\nPopping an element... Got %d\n", *result);

	//printf("Popping 4 elements...\n");
	result = (int*)pop(l);
	result = (int*)pop(l);
	result = (int*)pop(l);
	result = (int*)pop(l);
	//display(l);

	//printf("\nRe-pushing two elements...\n");
	push(l, &a);
	push(l, &f);
	//display(l);

	//printf("\nCleaning up...\n");
	cleanup(l);
	return 0;
}
