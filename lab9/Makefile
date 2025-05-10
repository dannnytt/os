TARGET = main
BIN_DIR = bin
SRC  = main.cpp

$(BIN_DIR)/$(TARGET) : $(SRC)
	g++ -o $@ $^

run:
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -rf $(BIN_DIR)/$(TARGET)