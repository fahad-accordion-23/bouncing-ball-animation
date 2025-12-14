CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra

all: main

main: main.o draw.o
	$(CC) $(CFLAGS) main.o draw.o -o main 

main.o: main.c draw.h
	$(CC) $(CFLAGS) main.c -c

draw.o: draw.h draw.c
	$(CC) $(CFLAGS) draw.c -c

clean:
	rm -f main.o draw.o main
