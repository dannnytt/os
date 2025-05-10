TARGETS = end_buffer ring_buffer
CC = gcc

BIN_DIR = bin
SRC_DIR = src

.PHONY: all clean

all: $(TARGETS:%=$(BIN_DIR)/%)

$(BIN_DIR)/% : $(SRC_DIR)/%.c
	$(CC) -o $@ $<

clean:
	rm -f $(BIN_DIR)/*