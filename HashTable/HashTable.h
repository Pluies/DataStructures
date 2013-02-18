#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* Settings */

#define INIT_BUCKET_CAPACITY 1
#define INIT_HASHTABLE_SIZE 1

/* Type declarations */

typedef struct {
	char* key;
	void* value;
} record;

typedef struct {
	int size;
	int capacity;
	record** records;
} bucket;

typedef struct HashTable {
	int size;
	int capacity;
	bucket** buckets;
} HashTable;

/* Interface */

HashTable* create();
int set(HashTable* h, const char* key, void* value);
void* lookup(HashTable* h, const char* key);
int unset(HashTable* h, const char* key);
void display(HashTable* h);
int cleanup(HashTable* h);
int check(HashTable* h);

/* Private (!) - for testing purpose only */
int hash(const char* key);

#endif

