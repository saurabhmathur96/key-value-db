#include "keyvaluedb.h"
#include "keyvaluefile.h"
#include "linearhashtable.h"
#include <stdlib.h>

void
keyvaluedb_create(KeyValueDB *db, char *name, KeyValueDBOptions *opts) {
	db->index = malloc(sizeof(*(db->index)));
	db->file = malloc(sizeof(*(db->file)));
	if (!opts) {
		
		linearhashtable_init(db->index, DEFAULT_INDEX_LEN);
		keyvaluefile_create(db->file, name, DEFAULT_BLOCKSIZE);
	} else {
		
		linearhashtable_init(db->index, opts->index_len);
		keyvaluefile_create(db->file, name, opts->blocksize);
	}
}

void
keyvaluedb_load(KeyValueDB *db, char *name) {
	db->index = malloc(sizeof(*(db->index)));
	db->file = malloc(sizeof(*(db->file)));
	keyvaluefile_load(db->file, name);
	linearhashtable_init(db->index, DEFAULT_INDEX_LEN);
}

char *
keyvaluedb_get(KeyValueDB *db, char *key) {
	long pos = linearhashtable_get(db->index, key);
	if (pos != -1) {
		// found in index
		return keyvaluefile_getat(db->file, pos);
	}
	// read from file
	pos = keyvaluefile_getpos(db->file, key);
	if (pos == -1) {
		// does not exist in file
		return NULL;
	}

	char *value = keyvaluefile_getat(db->file, pos);

	if (value) {
		// add to index
		linearhashtable_put(db->index, key, pos);
	}

	return value;
}

void
keyvaluedb_put(KeyValueDB *db, char *key, char *value) {
	long pos = linearhashtable_get(db->index, key);
	
	if (pos != -1) {
		// if already exists in file then replace
		pos = keyvaluefile_putat(db->file, pos, value);
	} else {
		// else create new entry
		pos = keyvaluefile_put(db->file, key, value);
	}
	
	// add to index
	linearhashtable_put(db->index, key, pos);
}

void
keyvaluedb_close(KeyValueDB *db) {
	keyvaluefile_close(db->file);
	linearhashtable_destroy(db->index);
	free(db->index);
}
