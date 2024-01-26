CC = gcc
CFLAGS = -Wall -pthread

all: main

main: main.c
	$(CC) $(CFLAGS) -o $@ $^ -lrt

clean:
	rm -f main
