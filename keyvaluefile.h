#ifndef _KEYVALUEFILE_H_
#define _KEYVALUEFILE_H_ 

#include <stdio.h>

/*
 * stores key-value pairs, each of size `blocksize` in binary file;
 * after each write outstream is flushed.
 */
typedef struct KeyValueFile {
	FILE   *instream;
	FILE   *outstream;
	size_t  blocksize; 
} KeyValueFile;

void keyvaluefile_create(KeyValueFile *f, char *filename, size_t blocksize);
void keyvaluefile_load(KeyValueFile *f, char *filename);

long keyvaluefile_getpos(KeyValueFile *f, char *key);
char *keyvaluefile_getat(KeyValueFile *f, long pos);
long keyvaluefile_put(KeyValueFile *f, char *key, char *value);
long keyvaluefile_putat(KeyValueFile *f, long pos, char *value);

void keyvaluefile_close(KeyValueFile *f);

#endif
