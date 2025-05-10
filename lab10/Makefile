TARGETS = example1 example2 example3 example4
CXX = g++

INCLUDE = -Iinclude

# Папки
BIN_DIR = bin
SRC_DIR = src
ROOT_DIR = .

all: $(TARGETS:%=$(BIN_DIR)/%)

$(BIN_DIR)/example1: $(ROOT_DIR)/example1.cpp $(SRC_DIR)/peterson_mutex.cpp
	$(CXX) -o $@ $< $(SRC_DIR)/peterson_mutex.cpp $(INCLUDE)

$(BIN_DIR)/example3: $(ROOT_DIR)/example3.cpp $(SRC_DIR)/peterson_mutex.cpp
	$(CXX) -o $@ $< $(SRC_DIR)/peterson_mutex.cpp $(INCLUDE)

$(BIN_DIR)/example2: $(ROOT_DIR)/example2.cpp $(SRC_DIR)/modified_peterson_mutex.cpp
	$(CXX) -o $@ $< $(SRC_DIR)/modified_peterson_mutex.cpp $(INCLUDE)

$(BIN_DIR)/example4: $(ROOT_DIR)/example4.cpp $(SRC_DIR)/modified_peterson_mutex.cpp
	$(CXX) -o $@ $< $(SRC_DIR)/modified_peterson_mutex.cpp $(INCLUDE)

clean:
	rm -rf $(BIN_DIR)/*
