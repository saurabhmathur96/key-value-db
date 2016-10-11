#include "linearhashtable.h"
#include <stdlib.h>
#include <string.h>

char *
_str_duplicate(char *dest, char *src) {

    int len = strlen(src);
    if (dest == NULL) {
            
        // if no memory allocated
        dest = malloc((len + 1) * sizeof(*dest));
    } else if (strlen(dest) < len) {
            
        // if memory allocated is insufficient
        dest = realloc(dest, (len + 1) * sizeof(*dest) );
    }

    // sufficent memory allocated
    // proceed with strcpy
    strcpy(dest, src);
    return dest;
}

size_t 
hash(char *str) {
	int i = 0, len = strlen(str);
	size_t hval = 0;
	for(i=0; i<len; i++) {
		hval += str[i];
	}
	return hval;
}


void linearhashtable_init(LinearHashTable *ht, size_t len) {
	Pair *pairs = malloc(sizeof(*pairs) * len);
	int i = 0;
	for (i=0; i<len; i++) {
		pairs[i].key = NULL;
		pairs[i].pos = -1;
	}
	
	ht->pairs = pairs;
	ht->len = len;
	
}


void linearhashtable_put(LinearHashTable *ht, char *key, long pos) {
	size_t index = hash(key) % ht->len;
	ht->pairs[index].key = _str_duplicate(ht->pairs[index].key, key);
	ht->pairs[index].pos = pos;
}


long linearhashtable_get(LinearHashTable *ht, char *key) {
	size_t index = hash(key) % ht->len;
	if (!ht->pairs[index].key || (strcmp(key, ht->pairs[index].key) == 0)) 
		return ht->pairs[index].pos;
	else
		return -1;
}


void linearhashtable_destroy(LinearHashTable *ht) {
	free(ht->pairs);
	ht->len = 0;
}
