all: kvdb

kvdb: keyvaluedb.o keyvaluefile.o linearhashtable.o main.o
	gcc keyvaluedb.o  keyvaluefile.o linearhashtable.o main.o -o kvdb

main.o: main.c
	gcc -c main.c 

keyvaluedb.o: keyvaluedb.c 
	gcc -c keyvaluedb.c 

linearhashtable.o: linearhashtable.c
	gcc -c linearhashtable.c 
	
keyvaluefile.o: keyvaluefile.c
	gcc -c keyvaluefile.c 

clean:
	rm *.o
