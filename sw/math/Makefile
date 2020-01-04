CC=gcc
CFLAGS=-I. -lm

_logreg: obj/matrix.o obj/logreg.o obj/_logreg.o
	$(CC) $(CFLAGS) -g obj/matrix.o obj/logreg.o obj/_logreg.o -o bin/_logreg

obj/matrix.o:
	$(CC) $(CFLAGS) -c src/matrix.c -o obj/matrix.o

obj/logreg.o:
	$(CC) $(CFLAGS) -c src/logreg.c -o obj/logreg.o

obj/_logreg.o:
	$(CC) $(CFLAGS) -c test/_logreg.c -o obj/_logreg.o
