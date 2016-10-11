# key-value-db

A simple datastore that stores data in the form of key-value pairs.

## Installing

Build using make.
```
make
```

## Usage

```
./kvdb [dbname] [command] [params]
```

Before use each database needs to be created with the `CREATE` command.

For eg.
```
./kvdb test CREATE
```

Store a key-value pair, using the `PUT` command.

For eg.

```
./kvdb test PUT language C
```

Retrieve a key-value pair using the `GET` command.

For eg.

```
./kvdb test GET language
```
