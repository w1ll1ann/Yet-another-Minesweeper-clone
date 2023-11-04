#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

namespace Minesweeper
{
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
            void drawGridCell(Cell cell);

            void setGrid(const std::pair <int, int> &gridSize);
            void setOutOfBoundsCells();
            void generateMines(int numberOfMines);
            void setNearbyMinesCellsValues();

            int countNearbyMines(const std::pair<int, int> &cellPosition);
    };
}

#endif