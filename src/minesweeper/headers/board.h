#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <algorithm>

const std::string redText {"\033[91m"};
const std::string greyText {"\033[90m"};
const std::string greenText {"\033[92m"};
const std::string yellowText {"\033[93m"};
const std::string defaultText {"\033[m"};

namespace Minesweeper {
    struct Cell {
        bool isRevealed {false};
        bool isMine {false};

        int nearbyMines {0};
    };

    class Board {
        public:
            Board();
            Board(std::pair <int, int> gridSize, int numberOfMines);

            void draw();

            void revealAll();
            void revealMines();

            int revealCell(std::pair <int, int> cellPosition);

            bool hasCellBeenRevealed(std::pair <int, int> cellPosition);
            bool hasAllCellsBeenRevealed();

        private:
            int revealedCells {0};
            int totalCells {0};

            bool hasMineBeenFound {false};

            std::vector <std::pair<int, int>> minesPositions;
            std::vector <std::vector <Cell>> grid;

            void setGrid(std::pair <int, int> gridSize);
            void setOutOfBoundsCells();
            void generateMines(int numberOfMines);
            void setNearbyMinesCellsValues();

            int countNearbyMines(std::pair<int, int> cellPosition);
    };
}

#endif