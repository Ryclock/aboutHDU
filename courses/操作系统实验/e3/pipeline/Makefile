CC = gcc
CFLAGS = -Wall
LDFLAGS = -lpthread

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)

clean:
	rm -f $(TARGET)
