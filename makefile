CC = gcc

CFLAGS = -lwiringPi -lwiringPiDev

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

.PHONY = all, clean, always

all: $(BIN_DIR)

$(BIN_DIR): always
	mkdir -p $(BIN_DIR)
	$(CC) $(SRC_DIR)/main.c $(CFLAGS) -o $(BIN_DIR)/$@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	clear

always:
	mkdir -p $(OBJ_DIR)
