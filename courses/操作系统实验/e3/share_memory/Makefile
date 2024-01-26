CC = gcc
CFLAGS = -Wall

all: sender receiver

sender: sender.c
	$(CC) $(CFLAGS) sender.c -o sender -lrt

receiver: receiver.c
	$(CC) $(CFLAGS) receiver.c -o receiver -lrt

clean:
	rm -f sender receiver
