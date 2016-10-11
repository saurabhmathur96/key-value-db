#ifndef _LINEARHASHTABLE_
#define _LINEARHASHTABLE_ 

#include <stdlib.h>

/*
 * Caches keys and their position in file
 * replaces pairs on hash value conflict
 */

typedef struct Pair {
	char *key;
	long  pos;
} Pair;


typedef struct LinearHashTable {
	size_t len;
	Pair  *pairs;
} LinearHashTable;

size_t hash(char *str);
void linearhashtable_init(LinearHashTable *ht, size_t len);
void linearhashtable_put(LinearHashTable *ht, char *key, long pos);
long linearhashtable_get(LinearHashTable *ht, char *key);
void linearhashtable_destroy(LinearHashTable *ht);

#endif
