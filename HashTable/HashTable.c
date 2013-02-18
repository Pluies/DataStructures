#include "HashTable.h"

/* Helper functions */

int isEmpty(HashTable* h){
	return h->size == 0;
}

// Hash function borrowed from:
// http://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200101/homework10/hashfuncs.html
// Tested in HashFunTest.c
int hash(const char* key) {
	assert(key != NULL);
	unsigned int g = 0,
			   h = 0,
			   i = 0,
			   keyLen = strlen(key);
	for(i = 0; i < keyLen; i++) {
		// The top 4 bits of h are all zero
		h = (h << 4) + key[i];  // shift h 4 bits left, add in ki
		g = h & 0xf0000000;     // get the top 4 bits of h
		if (g != 0){            // if the top 4 bits aren't zero,
			h = h ^ (g >> 24); // move them to the low end of h
			h = h ^ g;         // The top 4 bits of h are again all zero
		}
	}
	return h;
}

void fillWithNulls(void** array, int c){
	int i;
	for (i=0; i<c; i++)
		array[i] = NULL;
}

record* createRecord(const char* key, void* value){
	// Make a copy of the key to store
	int keyLen = strlen(key);
	char* keyToStore = malloc(keyLen * sizeof(char) + 1);
	strcpy(keyToStore, key);

	record* r = malloc(sizeof(record));
	r->key = keyToStore;
	r->value = value;
	return r;
}
void freeRecord(record* r){
	if (r == NULL) return;
	free(r->key);
	free(r);
}

int setInBucket(bucket* b, const char* key, void* value) {
	assert(b != NULL);
	if (b->size >= b->capacity){
		// Bucket resizing!
		b->capacity *= 2;
		b->records = realloc(b->records, b->capacity * sizeof(record*));
		fillWithNulls((void**)&(b->records[b->size]), b->capacity - b->size);
	}
	b->records[b->size] = createRecord(key, value);
	b->size += 1;
	return EXIT_SUCCESS;
}

int unsetInBucket(bucket* b, const char* key){
	if(b == NULL) return EXIT_FAILURE;
	int i = 0;
	for (i=0; i < b->size; i++) {
		record* r = b->records[i];
		if (strcmp(key,r->key) == 0) {
			freeRecord(r);
			// Contract array
			for(; (i+1) < b->size; i++)
				b->records[i] = b->records[i+1];
			// NULLify last if needed
			b->records[b->size-1] = NULL;
			b->size -= 1;
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

bucket* createBucket() {
	bucket* b = malloc(sizeof(bucket));
	b->size = 0;
	b->capacity = INIT_BUCKET_CAPACITY;
	b->records = malloc(INIT_BUCKET_CAPACITY * sizeof(record*));
	fillWithNulls((void**)b->records, b->capacity);
	return b;
}
void freeBucket(bucket* b){
	if (b == NULL) return;
	int i;
	for (i = 0; i<b->size; i++){
		freeRecord(b->records[i]);
	}
	free(b->records);
	free(b);
}

int checkOrCreateBucket(HashTable* h, int b) {
	assert(h != NULL);
	if (h->buckets[b] == NULL)
		h->buckets[b] = createBucket();
	return EXIT_SUCCESS;
}

/* Helpers */

int resize(HashTable* h, int newCapacity){

	int oldCapacity = h->capacity,
	    newElements = newCapacity - oldCapacity;
	
	h->buckets = realloc(h->buckets, newCapacity * sizeof(record*));
	
	// Bit black-magic-ky, but basically just fill NULLs the newly 
	// created elements of the h->buckets array; starting at the first
	// new memory location: (&h->buckets[oldCapacity]).
	// The (void**) casting is needed to conform to fillWithNulls type
	// signature.
	fillWithNulls((void**)(&h->buckets[oldCapacity]), newElements);

	int bi, i, oldHash;
	for(bi = 0; bi < oldCapacity; bi++) {
		bucket* b = h->buckets[bi];
		if (b == NULL) continue;
		oldHash = bi;
		i = 0;
		// For each record in the bucket...
		while(i < b->size) {
			record* r = b->records[i];
			int newHash = hash(r->key) % newCapacity;
			if (newHash != oldHash) {
				// Hash changed, move to new bucket
				checkOrCreateBucket(h, newHash);
				setInBucket(h->buckets[newHash], r->key, r->value);
				unsetInBucket(b, r->key);
			} else {
				// Hash unchanged, leave alone
				i++;
			}
		}
		if (b->size == 0) {
			// Release empty buckets for better memory usage
			freeBucket(b);
			h->buckets[bi] = NULL;
		}
	}
	h->capacity = newCapacity;
	return EXIT_SUCCESS;
}

/* Interface */

HashTable* create(){
	HashTable* h = malloc(sizeof(HashTable));
	h->size = 0;
	h->capacity = INIT_HASHTABLE_SIZE;
	h->buckets = malloc(INIT_HASHTABLE_SIZE * sizeof(bucket*));
	fillWithNulls((void**)h->buckets, h->capacity);
	return h;
}


int set(HashTable* h, const char* key, void* value){
	assert(h != NULL);
	assert(key != NULL);

	// Due to fast access in hash tables, we can get away with not
	// updating the record itself if the key already exists and
	// unset+set instead.
	unset(h, key);

	int b = hash(key) % h->capacity;
	checkOrCreateBucket(h, b);
	if (setInBucket(h->buckets[b], key, value) == EXIT_SUCCESS) {
		h->size += 1;
		if (h->size >= (0.75 * h->capacity))
			resize(h, (2*h->capacity)+1);
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}

int unset(HashTable* h, const char* key) {
	assert(h != NULL);
	assert(key != NULL);
	int r = unsetInBucket(h->buckets[hash(key) % h->capacity], key);
	if (r == EXIT_SUCCESS) {
		h->size -= 1;
	}
	return r;
}

void* lookup(HashTable* h, const char* key){
	assert(h != NULL);
	int bi = hash(key) % h->capacity;
	bucket* b = h->buckets[bi];
	if (b == NULL) return NULL;
	int i = 0;
	for (i=0; i < b->size; i++) {
		record* r = b->records[i];
		if (strcmp(key,r->key) == 0)
			return r->value;
	}
	return NULL;
}

void displayRecord(record* r){
	if (r == NULL) return;
	printf("(k: %s, v: %p)", r->key, r->value);
}
void displayBucket(bucket* b, int in){
	int i = 0;
	printf("Bucket %d at %p, ", in, b);
	if (b == NULL) {
		printf("not initialised.");
	} else {
		printf("capacity %d, ", b->capacity);
		if (b->size == 0) {
			printf("empty.");
		} else {
			printf("size %d: ", b->size);
			for (i=0; i<b->size; i++)
				displayRecord(b->records[i]);
		}
	}
	printf("\n");
}
void display(HashTable* h){
	int i = 0;
	if (isEmpty(h)) {
		printf("HashTable is empty.\n");
	} else {
		printf("HashTable has %d element(s).\n", h->size);
		for (i=0; i<h->capacity; i++)
			displayBucket(h->buckets[i], i);
		printf("\n");
	}
}

int cleanup(HashTable* h){
	int i = 0;
	for (i=0; i<h->capacity; i++) {
		freeBucket(h->buckets[i]);
	}
	free(h->buckets);
	free(h);
	return EXIT_SUCCESS;
}

