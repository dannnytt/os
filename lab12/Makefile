TARGETS = example1 \
          example2 \
          example3 \
          example4 \
          example5 \
          example6 \
          example7 \
          example8 \
          example9

CXX = g++

BIN_DIR = bin
SRC_DIR = src

.PHONY: all clean

all: $(BIN_DIR) $(TARGETS:%=$(BIN_DIR)/%)

# Создание директории bin, если она не существует
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) -o $@ $<

clean:
	rm -f $(BIN_DIR)/*