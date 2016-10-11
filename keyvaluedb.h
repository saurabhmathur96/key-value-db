#ifndef _KEYVALUEDB_H_
#define _KEYVALUEDB_H_ 

#include "keyvaluefile.h"
#include "linearhashtable.h"
#include <stdlib.h>

/*
 * stores keyvalue pairs in a file, indexed by a hash based index;
 * the index is not persisted to disk.
 */

#define DEFAULT_BLOCKSIZE ((size_t)256)
#define DEFAULT_INDEX_LEN ((size_t)64)

typedef struct KeyValueDBOptions {
	size_t blocksize;
	size_t index_len;
} KeyValueDBOptions;

typedef struct KeyValueDB {
	KeyValueFile      *file;
	LinearHashTable   *index;
} KeyValueDB;

void keyvaluedb_create(KeyValueDB *db, char *name, KeyValueDBOptions *opts);
void keyvaluedb_load(KeyValueDB *db, char *name);

char *keyvaluedb_get(KeyValueDB *db, char *key);
void keyvaluedb_put(KeyValueDB *db, char *key, char *value);

void keyvaluedb_close(KeyValueDB *db);

#endif
