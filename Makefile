CC := g++
CFLAGS := -Wall

matrix.exe: matrix.o
	$(CC) $(CFLAGS) -o matrix.exe matrix.o

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(CFLAGS) -c matrix.cpp -o matrix.o
