#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <algorithm>

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
            void drawAll();
        private:
            std::vector <std::pair<int, int>> minesPositions;
            std::vector <std::vector <Cell>> grid;

            void setGrid(std::pair <int, int> gridSize);
            void generateMines(int numberOfMines);
            void setNearbyMinesCellsValues();

            int countNearbyMines(std::pair<int, int> cellPosition);
    };
}

#endif