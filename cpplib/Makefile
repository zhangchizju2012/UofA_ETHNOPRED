CC=g++
#CFLAGS=-std=c++11 --static -O4
CFLAGS=-std=c++11 -g --static
CFLAGS=-g -std=c++11 --static -O4
#CFLAGS=-std=c++11

all: ethnopred_once ethnopred_twice

ethnopred_once: main_once.o
		$(CC) $(CFLAGS) main_once.o -o ethnopred_once

main_once.o: ./cpp_code/main_once.cpp
		$(CC) -c $(CFLAGS)  ./cpp_code/main_once.cpp -o main_once.o

ethnopred_twice: main_twice.o
		$(CC) $(CFLAGS) main_twice.o -o ethnopred_twice

main_twice.o: ./cpp_code/main_twice.cpp
		$(CC) -c $(CFLAGS)  ./cpp_code/main_twice.cpp -o main_twice.o

clean:
	rm -f main_once.o main_twice.o

remove:
	rm -f main_once.o ethnopred_once main_twice.o ethnopred_twice
