CC = gcc
CFLAGS = -Wall
BIN_DIR = /tmp/bin

all: $(BIN_DIR)/cmd1 $(BIN_DIR)/cmd2 $(BIN_DIR)/cmd3 $(BIN_DIR)/myshell

$(BIN_DIR)/cmd1: cmd1.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/cmd2: cmd2.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/cmd3: cmd3.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/myshell: myshell.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN_DIR)/cmd1 $(BIN_DIR)/cmd2 $(BIN_DIR)/cmd3 $(BIN_DIR)/myshell
