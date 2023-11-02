CC     = g++
CFLAGS = -std=c++11 -Wall -Wextra

SRC  = src
BIN  = bin
EXEC = $(BIN)/minesweeper

all: $(BIN) $(EXEC)

$(BIN):
	mkdir -p $@

$(EXEC):
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $@

clean:
	$(RM) -r $(BIN)