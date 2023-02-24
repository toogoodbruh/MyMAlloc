CC = gcc
all: test memgrind
test: test.c mymalloc.c mymalloc.h
	$(CC) -o test test.c mymalloc.c
memgrind: memgrind.c mymalloc.c mymalloc.h
	$(CC) -o memgrind memgrind.c mymalloc.c
clean:
	rm -f test *.o
	rm -f memgrind *.o
