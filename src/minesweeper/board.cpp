#include "headers/board.h"

using namespace Minesweeper;

Board::Board() {
    setGrid();
    generateMines(10);
    setNearbyMinesCellsValues();
}

void Board::draw() {
    drawTop();
    for (unsigned int i = 1; i < grid.size() - 1; i++) {
        std::cout << i - 1 << " ";
        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (!grid[i][j].isRevealed)
                std::cout << "- ";
            else
                std::cout << grid[i][j].nearbyMines << " ";
        std::cout << "\n";
    }
}

void Board::drawAll() {
    drawTop();
    for (unsigned int i = 1; i < grid.size() - 1; i++) {
        std::cout << i - 1 << " ";
        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (grid[i][j].isMine)
                std::cout << "X ";
            else
                std::cout << grid[i][j].nearbyMines << " ";

        std::cout << "\n";
    }
}

void Board::drawTop() {
    std::cout << "  ";
    for (unsigned int i = 1; i < grid.size() - 1; i++)
        std::cout << i - 1 << " ";
    std::cout << "\n";
}

void Board::setGrid() {
    grid.clear();

    grid.resize(10);
    for (unsigned int i = 0; i < grid.size(); i++)
        grid[i].resize(10);
}

void Board::generateMines(int numberOfMines) {
    minesPositions.clear();

    std::random_device rd;
    std::uniform_int_distribution <int> dist(1, 8);

    int distinctPositions = 0;
    while (distinctPositions < numberOfMines) {
        std::pair <int, int> minePosition = {dist(rd), dist(rd)};

        if (std::find(minesPositions.begin(), minesPositions.end(), minePosition) == minesPositions.end()) {
            grid[minePosition.first][minePosition.second].isMine = true;
            minesPositions.push_back(minePosition);

            distinctPositions++;
        }
    }
}

int Board::countNearbyMines(std::pair<int, int> cellPosition) {
    int nearbyMines {0};
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <=1; j++)
            if(grid[cellPosition.first + i][cellPosition.second + j].isMine)
                nearbyMines++;

    return nearbyMines;
}

void Board::setNearbyMinesCellsValues() {
    for (unsigned int i = 1; i < grid.size() - 1; i++)
        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (!grid[i][j].isMine)
                grid[i][j].nearbyMines = countNearbyMines({i, j});
}