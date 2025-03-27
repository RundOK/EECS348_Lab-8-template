CC := g++
CFLAGS := -Wall

matrix.exe: matrix.o
	$(CC) $(CFLAGS) -o matrix.exe matrix.o

football.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c -o matrix.o