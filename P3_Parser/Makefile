CC=gcc
CFLAGS=-Wall -g

all: P3

P3: main.o scanner.o parser.o testTree.o staticSemantics.o symbolTable.o
	$(CC) $(CFLAGS) -o P3 main.o scanner.o parser.o testTree.o staticSemantics.o symbolTable.o

main.o: main.c scanner.h token.h
	$(CC) $(CFLAGS) -c main.c

scanner.o: scanner.c scanner.h token.h
	$(CC) $(CFLAGS) -c scanner.c

parser.o: parser.c parser.h scanner.c scanner.h token.h testTree.h
	$(CC) $(CFLAGS) -c parser.c

testTree.o: testTree.c testTree.h
	$(CC) $(CFLAGS) -c testTree.c

staticSemantics.o: staticSemantics.c staticSemantics.h testTree.h symbolTable.h
	$(CC) $(CFLAGS) -c staticSemantics.c

symbolTable.o: symbolTable.c symbolTable.h
	$(CC) $(CFLAGS) -c symbolTable.c

clean:
	rm -f *.o P3
