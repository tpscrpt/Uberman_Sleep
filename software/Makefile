CC=gcc
CFLAGS=-I include/ -lm -g

_logreg: .obj/matrix.o .obj/logreg.o .obj/_logreg.o
	$(CC) $(CFLAGS) .obj/matrix.o .obj/logreg.o .obj/_logreg.o -o .bin/_logreg

#_titanic: .obj/matrix.o .obj/logreg.o .obj/csv.o .obj/_titanic.o
#	$(CC) $(CFLAGS) .obj/matrix.o .obj/logreg.o .obj/csv.o .obj/_titanic.o -o bin/_titanic

titanic: .obj/matrix.o .obj/csv.o
	$(CC) $(CFLAGS) .obj/matrix.o .obj/csv.o experiments/titanic/src/titanic.c -o .bin/titanic

_titanic:
	$(CC) $(CFLAGS) src/matrix.c src/logreg.c src/csv.c experiments/titanic/_titanic.c -o .bin/_titanic

.obj/matrix.o:
	$(CC) $(CFLAGS) -c src/matrix.c -o .obj/matrix.o

.obj/logreg.o:
	$(CC) $(CFLAGS) -c src/logreg.c -o .obj/logreg.o

.obj/csv.o:
	$(CC) $(CFLAGS) -c src/csv.c -o .obj/csv.o

.obj/_logreg.o:
	$(CC) $(CFLAGS) -c test/_logreg.c -o .obj/_logreg.o

.obj/_titanic.o:
	$(CC) $(CFLAGS) -g -c test/titanic/_titanic.c -o .obj/_titanic.o
