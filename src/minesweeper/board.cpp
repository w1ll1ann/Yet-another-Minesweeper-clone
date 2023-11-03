#include "headers/board.h"

using namespace Minesweeper;

Board::Board() {
    Board({8, 8}, 10);
}

Board::Board(std::pair <int, int> gridSize, int numberOfMines) {
    totalCells = gridSize.first * gridSize.second;

    setGrid(gridSize);
    generateMines(numberOfMines);
    setNearbyMinesCellsValues();
    setOutOfBoundsCells();
}

void Board::draw() {
    std::cout << "MS ";
    for (unsigned int i = 0; i < grid[0].size() - 2; i++)
        if (i < 10)
            std::cout << "0" + std::to_string(i) << " ";
        else
            std::cout << i << " ";
    std::cout << "J\n";

    for (unsigned int i = 1; i < grid.size() - 1; i++) {
        if (i < 10)
            std::cout << "0" + std::to_string(i - 1) << "  ";
        else
            std::cout << i << "  ";

        for (unsigned int j = 1; j < grid[i].size() - 1; j++)
            if (!grid[i][j].isRevealed)
                std::cout << "-" << "  ";
            else if (grid[i][j].isMine)
                std::cout << redText << "X" << defaultText << "  ";
            else if (grid[i][j].nearbyMines == 0)
                std::cout << greyText << grid[i][j].nearbyMines << defaultText << "  ";
            else
                std::cout << yellowText << grid[i][j].nearbyMines << defaultText << "  ";
        std::cout << "\n";
    }

    std::cout << " I\n";
}

void Board::revealAll() {
    for (unsigned int i = 0; i < grid.size(); i++)
        for (unsigned int j = 0; j < grid[i].size(); j++)
            grid[i][j].isRevealed = true;
}

void Board::revealMines() {
    for (auto i : minesPositions)
        grid[i.first][i.second].isRevealed = true;
}

int Board::revealCell(std::pair <int, int> cellPosition) {
    if (grid[cellPosition.first][cellPosition.second].isRevealed)
        return 0;

    grid[cellPosition.first][cellPosition.second].isRevealed = true;
    revealedCells++;

    if (grid[cellPosition.first][cellPosition.second].isMine) {
        hasMineBeenFound = true;
        return 0;
    }

    int accumulatedScore {0};
    if (grid[cellPosition.first][cellPosition.second].nearbyMines == 0) {
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <=1; j++)
                if (grid[cellPosition.first + i][cellPosition.second + j].isMine)
                    continue;
                else
                    accumulatedScore += revealCell({cellPosition.first + i, cellPosition.second + j});
    }
    else
        accumulatedScore = grid[cellPosition.first][cellPosition.second].nearbyMines * 100;

    return accumulatedScore;
}

bool Board::hasCellBeenRevealed(std::pair <int, int> cellPosition) {
    return grid[cellPosition.first][cellPosition.second].isRevealed;
}

bool Board::hasAllCellsBeenRevealed() {
    return (unsigned)revealedCells == (totalCells - minesPositions.size()); 
}

void Board::setGrid(std::pair <int, int> gridSize) {
    grid.resize(gridSize.first + 2);
    for (unsigned int i = 0; i < grid.size(); i++)
        grid[i].resize(gridSize.second + 2);
}

void Board::setOutOfBoundsCells() {
    for (unsigned int i = 0; i < grid[0].size(); i++)
        grid[0][i].isRevealed = true;

    for (unsigned int i = 0; i < grid[0].size(); i++)
        grid[grid.size() - 1][i].isRevealed = true;

    for(unsigned int i = 0; i < grid.size(); i++)
        grid[i][0].isRevealed = true;

    for(unsigned int i = 0; i < grid.size(); i++)
        grid[i][grid[0].size() - 1].isRevealed = true;
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