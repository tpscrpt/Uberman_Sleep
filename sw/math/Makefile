CC=gcc
CFLAGS=-I. -I./test

test: logreg.o matrix.o test/_logreg.o
	$(CC) -g -lm -o _logreg logreg.o matrix.o test/_logreg.o
