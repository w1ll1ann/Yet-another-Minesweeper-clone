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

namespace Minesweeper
{
    struct Cell
    {
        bool isRevealed {false};
        bool isMine {false};

        int nearbyMines {0};
    };

    class Board
    {
        public:
            Board();
            Board(const std::pair <int, int> &gridSize, int numberOfMines);

            void draw();

            void revealAll();
            void revealMines();

            int revealCell(const std::pair <int, int> &cellPosition);

            bool hasCellBeenRevealed(const std::pair <int, int> &cellPosition);
            bool hasAllCellsBeenRevealed();

            bool hasMineBeenFound();

            std::pair <int, int> getGridDimensions();

        private:
            int revealedCells {0};
            int totalCells {0};

            bool aMineHasBeenFound {false};

            std::vector <std::pair<int, int>> minesPositions;
            std::vector <std::vector <Cell>> grid;

            void drawGridNumbers(int number);

            void setGrid(const std::pair <int, int> &gridSize);
            void setOutOfBoundsCells();
            void generateMines(int numberOfMines);
            void setNearbyMinesCellsValues();

            int countNearbyMines(const std::pair<int, int> &cellPosition);
    };
}

#endif