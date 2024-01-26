CC = gcc
CFLAGS = -Wall
LDFLAGS = -lws2_32
SERVER_EXEC = server
CLIENT_EXEC = client
SERVER_SRC = server.c
CLIENT_SRC = client.c

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SERVER_SRC) $(LDFLAGS)

$(CLIENT_EXEC): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(CLIENT_SRC) $(LDFLAGS)

clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)
