#include "HashTable.h"

int main (int argc, char** argv){

	const char* str[] = { "a", "b", "c", "Borborygmes", "Dedecaedre", "Polymorphism", "Extraneous" };
	int i = 0;

	if (argc <= 1) {
		printf("Use: %s base [key1 key2 ...]\n", argv[0]);
		return 0;
	}

	int base = atoi(argv[1]);

	for (i=0; i<7; i++) {
		printf("Hashing %s gives %d or %d with base %d\n", str[i], hash(str[i]), hash(str[i])%base, base);
	}

	printf("------\n");

	for (i=0; i<argc; i++) {
		printf("Hashing %s gives %d or %d with base %d\n", argv[i], hash(argv[i]), hash(argv[i])%base, base);
	}

	return 0;
}
