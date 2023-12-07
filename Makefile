CC = gcc
CINC = -Iinclude
CFLAGS = -lJakestering

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

.PHONY: all
all: $(BIN_DIR)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c $(CFLAGS) -o $@

$(BIN_DIR): always $(OBJ_DIR)/main.o
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/main.o $(CFLAGS) -o $(BIN_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	clear

.PHONY: always
always:
	mkdir -p $(OBJ_DIR)
