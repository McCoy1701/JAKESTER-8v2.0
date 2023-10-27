CC = gcc

CINC = -Iinclude
CFLAGS = -lwiringPi -lwiringPiDev

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

.PHONY = all, clean, always

all: $(BIN_DIR)

$(OBJ_DIR)/keypad.o: $(SRC_DIR)/keypad/keypad.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c $(CINC) -o $@

$(BIN_DIR): always $(OBJ_DIR)/keypad.o $(OBJ_DIR)/main.o
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/keypad.o $(OBJ_DIR)/main.o $(CFLAGS) -o $(BIN_DIR)/$@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	clear

always:
	mkdir -p $(OBJ_DIR)
