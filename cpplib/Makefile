CC=g++
CFLAGS=-g -std=c++11 --static -O4

all: ethnopred

ethnopred: main.o
		$(CC) $(CFLAGS) main.o -o ethnopred

main.o: ./cpp_code/main.cpp
		$(CC) -c $(CFLAGS)  ./cpp_code/main.cpp -o main.o

clean:
	rm -f main.o

remove:
	rm -f main.o ethnopred
