LIBNAME = list
LIBFILE = lib$(LIBNAME).so
MAIN = main

CC = gcc
INCLUDE = -Iinclude
CFLAGS = -fpic -Wall -Wextra
LDFLAGS = -shared 

BIN_DIR = bin

OBJ_DIR = obj
OBJ_LIST = $(OBJ_DIR)/list
OBJ_KEYREADER = $(OBJ_DIR)/keyreader
OBJ_UTILS = $(OBJ_DIR)/utils
OBJ_MAIN = $(OBJ_DIR)/main

SRC_DIR = src
SRC_LIST = $(SRC_DIR)/list
SRC_KEYREADER = $(SRC_DIR)/keyreader
SRC_UTILS = $(SRC_DIR)/utils
SRC_MAIN = $(SRC_DIR)/main

MAIN_OBJECTS = $(patsubst $(SRC_KEYREADER)/%.c, $(OBJ_KEYREADER)/%.o, $(wildcard $(SRC_KEYREADER)/*.c)) \
               $(patsubst $(SRC_UTILS)/%.c, $(OBJ_UTILS)/%.o, $(wildcard $(SRC_UTILS)/*.c)) \
               $(patsubst $(SRC_MAIN/%.c), $(OBJ_MAIN)/%.o, $(wildcard $(SRC_MAIN)/*.c))

$(BIN_DIR)/$(MAIN): $(MAIN_OBJECTS)
	$(CC) -o $@ $^ -Llibs -l$(LIBNAME) -Wl,-rpath,libs $(INCLUDE)

$(OBJ_KEYREADER)/%.o: $(SRC_KEYREADER)/%.c
	mkdir -p $(OBJ_KEYREADER)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(OBJ_UTILS)/%.o: $(SRC_UTILS)/%.c
	mkdir -p $(OBJ_UTILS)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(OBJ_MAIN)/%.o: $(SRC_MAIN)/%.c
	mkdir -p $(OBJ_MAIN)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	rm -rf $(OBJ_KEYREADER) 
	rm -rf $(OBJ_MAIN) 
	rm -rf $(OBJ_UTILS) 
	rm -rf $(BIN_DIR)/$(MAIN) 
