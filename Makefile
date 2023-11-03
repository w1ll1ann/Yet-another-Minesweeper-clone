CC     = g++
CFLAGS = -std=c++11 -Wall -Wextra

SRC = src
BIN = bin
OBJ = obj

MSW = $(SRC)/minesweeper
HDR = $(MSW)/headers

OBJS = $(OBJ)/game.o $(OBJ)/board.o $(OBJ)/player.o
EXEC = $(BIN)/minesweeper

all: $(BIN) $(OBJ) $(EXEC)

$(BIN):
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(OBJ)/%.o: $(MSW)/%.cpp $(HDR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(OBJS) $(SRC)/main.cpp -o $@

clean:
	$(RM) -r $(BIN) $(OBJ)