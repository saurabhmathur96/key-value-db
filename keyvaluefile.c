#include "keyvaluefile.h"
#include <stdlib.h>
#include <string.h>


void
keyvaluefile_load(KeyValueFile *f, char *filename) {
	
	f->instream = fopen(filename, "rb"); // open filestream for reading
	fread((void *)&f->blocksize, sizeof(f->blocksize), 1, f->instream); // read block size
	
	f->outstream = fopen(filename, "ab"); // // open filestream for appending
}

void 
keyvaluefile_create(KeyValueFile *f, char *filename, size_t blocksize) {
	f->blocksize = blocksize;
	f->outstream = fopen(filename, "wb"); // create file
	fwrite((void *)&blocksize, sizeof(blocksize), 1, f->outstream); // write blocksize
	fflush(f->outstream); 
	f->instream = fopen(filename, "rb");
}

long
keyvaluefile_getpos(KeyValueFile *f, char *key) {
	

	fseek(f->instream, sizeof(f->blocksize), SEEK_SET);

	char *k = malloc(sizeof(*k) * f->blocksize);
	char *v = malloc(sizeof(*v) * f->blocksize);

	long pos = -1;
	while(!feof(f->instream)) {
		pos = ftell(f->instream);
		fread((void *)k, sizeof(*k), f->blocksize, f->instream);
		fread((void *)v, sizeof(*v), f->blocksize, f->instream);


		if (strcmp(k, key) == 0){
			break;
		}
	}
	free(k);
	free(v);
	if(feof(f->instream)) {
		fseek(f->instream, sizeof(f->blocksize), SEEK_SET);
		return -1;
	}
	return pos;

}

char *
keyvaluefile_getat(KeyValueFile *f, long pos) {
	
	fseek(f->instream, pos + f->blocksize, SEEK_SET);

	if (feof(f->instream)) {
		fseek(f->instream, sizeof(f->blocksize), SEEK_SET);
		return NULL;
	}

	char *v = malloc(sizeof(*v) * f->blocksize);

	fread((void *)v, sizeof(*v), f->blocksize, f->instream);

	return v;

}

long 
keyvaluefile_put(KeyValueFile *f, char *key, char *value) {
	fseek(f->outstream, 0, SEEK_END);
	long pos = ftell(f->outstream);
	fwrite((void *)key, sizeof(*key), f->blocksize, f->outstream);
	fwrite((void *)value, sizeof(*value), f->blocksize, f->outstream);
	fflush(f->outstream);
	return pos;
}

long 
keyvaluefile_putat(KeyValueFile *f, long pos, char *value) {
	fseek(f->outstream, pos + f->blocksize, SEEK_SET);
	fwrite((void *)value, sizeof(*value), f->blocksize, f->outstream);
	fflush(f->outstream);
	return pos;
}

void 
keyvaluefile_close(KeyValueFile *f) {
	fclose(f->instream);
	fclose(f->outstream);
}