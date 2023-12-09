CC=gcc
CFLAGS=-Wall -g

all: P2

P2: main.o scanner.o parser.o testTree.o
	$(CC) $(CFLAGS) -o P2 main.o scanner.o parser.o testTree.o

main.o: main.c scanner.h token.h
	$(CC) $(CFLAGS) -c main.c

scanner.o: scanner.c scanner.h token.h
	$(CC) $(CFLAGS) -c scanner.c

parser.o: parser.c parser.h scanner.c scanner.h token.h testTree.h
	$(CC) $(CFLAGS) -c parser.c

testTree.o: testTree.c testTree.h
	$(CC) $(CFLAGS) -c testTree.c

clean:
	rm -f *.o P2