#include "keyvaluedb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Command {CREATE, GET, PUT, INVALID};

enum Command parse_command(char *text) {
    if (strcmp(text, "CREATE") == 0) {
        return CREATE;
    } else if (strcmp(text, "GET") == 0) {
        return GET;
    } else if (strcmp(text, "PUT") == 0) {
        return PUT;
    } else {
        return INVALID;
    }
    
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf ("Usage: kvdb [dbname] [command] [params]\n");
        return 0;
    }
    char *dbname = argv[1];
    enum Command command = parse_command(argv[2]);

    KeyValueDB db;
    char *key;
    char *value;
    switch (command) {
        case CREATE:
            keyvaluedb_create(&db, dbname, NULL);
            keyvaluedb_close(&db);
            break;
        case GET:
            if (argc != 4) {
                printf ("Usage: kvdb [dbname] GET [key]\n");
                return 0;
            }
            key = argv[3];
            keyvaluedb_load(&db, dbname);
                value = keyvaluedb_get(&db, key);
            keyvaluedb_close(&db);

            if (!value) {
                printf ("Not Found.\n");
            } else {
                printf ("Found.\n");
                printf ("%s: %s\n", key, value);
                free(value);
            }
            break;
        case PUT:
            if (argc != 5) {
                printf ("Usage: kvdb [dbname] PUT [key] [value]\n");
                return 0;
            }
            key = argv[3];
            value = argv[4];
            keyvaluedb_load(&db, dbname);
                keyvaluedb_put(&db, key, value);
            keyvaluedb_close(&db);
            printf ("Saved.\n", key, value);
            break;
        default:
            printf("Invalid.\n");
            break;
    }

    return 0;
}