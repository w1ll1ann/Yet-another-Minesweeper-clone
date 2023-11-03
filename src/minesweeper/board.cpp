#include "headers/board.h"

using namespace Minesweeper;

const std::string redText {"\033[91m"};
const std::string greyText {"\033[90m"};
const std::string yellowText {"\033[93m"};
const std::string defaultText {"\033[m"};

Board::Board() {
    Board({8, 8}, 10);
}

Board::Board(std::pair <int, int> gridSize, int numberOfMines) {
    setGrid(gridSize);
    generateMines(numberOfMines);
    setNearbyMinesCellsValues();
}

void Board::draw() {
    for (unsigned int i = 1; i < grid.size() - 1; i++) {
        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (!grid[i][j].isRevealed)
                std::cout << "- ";
            else if (grid[i][j].nearbyMines == 0)
                std::cout << greyText << grid[i][j].nearbyMines << defaultText << " ";
            else
                std::cout << yellowText << grid[i][j].nearbyMines << defaultText << " ";
        std::cout << "\n";
    }
}

void Board::drawAll() {
    for (unsigned int i = 1; i < grid.size() - 1; i++) {
        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (grid[i][j].isMine)
                std::cout << redText << "X " << defaultText;
            else if (grid[i][j].nearbyMines == 0)
                std::cout << greyText << grid[i][j].nearbyMines << defaultText << " ";
            else
                std::cout << yellowText << grid[i][j].nearbyMines << defaultText << " ";
        std::cout << "\n";
    }
}

void Board::setGrid(std::pair <int, int> gridSize) {
    grid.resize(gridSize.first + 2);
    for (unsigned int i = 0; i < grid.size(); i++)
        grid[i].resize(gridSize.second + 2);
}

void Board::generateMines(int numberOfMines) {
    std::random_device rd;
    std::uniform_int_distribution <int> distI(1, grid.size() - 2);
    std::uniform_int_distribution <int> distJ(1, grid[0].size() - 2);

    int distinctPositions = 0;
    while (distinctPositions < numberOfMines) {
        std::pair <int, int> minePosition = {distI(rd), distJ(rd)};

        if (std::find(minesPositions.begin(), minesPositions.end(), minePosition) == minesPositions.end()) {
            grid[minePosition.first][minePosition.second].isMine = true;
            minesPositions.push_back(minePosition);

            distinctPositions++;
        }
    }
}

void Board::setNearbyMinesCellsValues() {
    for (unsigned int i = 1; i < grid.size() - 1; i++)
        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (!grid[i][j].isMine)
                grid[i][j].nearbyMines = countNearbyMines({i, j});
}

int Board::countNearbyMines(std::pair<int, int> cellPosition) {
    int nearbyMines {0};
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <=1; j++)
            if(grid[cellPosition.first + i][cellPosition.second + j].isMine)
                nearbyMines++;

    return nearbyMines;
}