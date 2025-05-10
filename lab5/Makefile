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

LIB_OBJECTS = $(patsubst $(SRC_LIST)/%.c, $(OBJ_LIST)/%.o, $(wildcard $(SRC_LIST)/*.c))

MAIN_OBJECTS = $(patsubst $(SRC_KEYREADER)/%.c, $(OBJ_KEYREADER)/%.o, $(wildcard $(SRC_KEYREADER)/*.c)) \
               $(patsubst $(SRC_UTILS)/%.c, $(OBJ_UTILS)/%.o, $(wildcard $(SRC_UTILS)/*.c)) \
               $(patsubst $(SRC_MAIN/%.c), $(OBJ_MAIN)/%.o, $(wildcard $(SRC_MAIN)/*.c))

$(BIN_DIR)/$(MAIN): $(MAIN_OBJECTS) $(BIN_DIR)/$(LIBFILE)
	$(CC) -o $@ $^ -L$(BIN_DIR) -l$(LIBNAME) -Wl,-rpath,$(BIN_DIR) $(INCLUDE)

$(BIN_DIR)/$(LIBFILE): $(LIB_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ 

$(OBJ_KEYREADER)/%.o: $(SRC_KEYREADER)/%.c
	mkdir -p $(OBJ_KEYREADER)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(OBJ_LIST)/%.o: $(SRC_LIST)/%.c
	mkdir -p $(OBJ_LIST)
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
	rm -rf $(OBJ_LIST) 
	rm -rf $(OBJ_MAIN) 
	rm -rf $(OBJ_UTILS) 
	rm -rf $(BIN_DIR)/$(MAIN) 
	rm -rf $(BIN_DIR)/$(LIBFILE)
