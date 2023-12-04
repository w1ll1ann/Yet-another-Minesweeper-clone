CC     = g++
CFLAGS = -std=c++11 -Wall -Wextra

SRC = src
BIN = bin
OBJ = obj

TST = test
TST_BIN = test/bin
TST_OBJ = test/obj

MSW = $(SRC)/minesweeper
HDR = $(MSW)/headers

OBJS = $(OBJ)/game.o $(OBJ)/board.o $(OBJ)/player.o
EXEC = $(BIN)/minesweeper

TESTCASES = $(TST_BIN)/mstestcases

all: $(BIN) $(OBJ) $(EXEC)

$(BIN):
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(OBJ)/%.o: $(MSW)/%.cpp $(HDR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(OBJS) $(SRC)/main.cpp -o $@

tests: $(OBJ) $(TST_BIN) $(TST_OBJ) $(TESTCASES)

$(TST_BIN):
	mkdir -p $@

$(TST_OBJ):
	mkdir -p $@

$(TST_OBJ)/catch2.o: $(TST)/catch2.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTCASES): $(OBJS) $(TST_OBJ)/catch2.o $(TST)/testcases.cpp
	$(CC) $(CFLAGS) $(OBJS) $(TST_OBJ)/catch2.o $(TST)/testcases.cpp -o $@
	./$(TESTCASES) < $(TST)/testinput.txt

clean:
	$(RM) -r $(BIN) $(OBJ) $(TST_OBJ) $(TST_BIN)