#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

#include "cell.h"

namespace Minesweeper {
    class Board {
        public:
            Board();
            void draw();
            void drawAll();
        private:
            std::vector <std::pair<int, int>> minesPositions;
            std::vector <std::vector <Cell>> grid;

            void drawTop();

            void setGrid();
            void generateMines(int numberOfMines);
            int countNearbyMines(std::pair<int, int> cellPosition);
            void setNearbyMinesCellsValues();
    };
}

#endif