#include "headers/board.h"

using namespace Minesweeper;

Board::Board(const std::pair <int, int> &gridSize, int numberOfMines)
{
    totalCells = gridSize.first * gridSize.second;

    setGrid(gridSize);
    generateMines(numberOfMines);
    setNearbyMinesCellsValues();
    setOutOfBoundsCells();
}

void Board::draw()
{
    std::cout << "MS ";
    for (unsigned i = 1; i < grid[0].size() - 1; i++)
        drawGridNumbers(i);
    std::cout << "J\n";

    for (unsigned i = 1; i < grid.size() - 1; i++)
    {
        drawGridNumbers(i);
        for (unsigned j = 1; j < grid[i].size() - 1; j++)
            drawGridCell(grid[i][j]);
        std::cout << "\n";
    }

    std::cout << " I\n";
}

void Board::revealAll()
{
    for (unsigned i = 0; i < grid.size(); i++)
        for (unsigned j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].isRevealed = true;
            revealedCells++;
        }
}

void Board::revealMines()
{
    for (auto i : minesPositions)
        grid[i.first][i.second].isRevealed = true;

    aMineHasBeenFound = true;
}

int Board::revealCell(const std::pair <int, int> &cellPosition)
{
    if (grid[cellPosition.first][cellPosition.second].isRevealed)
        return 0;

    grid[cellPosition.first][cellPosition.second].isRevealed = true;
    revealedCells++;

    if (grid[cellPosition.first][cellPosition.second].isMine)
    {
        aMineHasBeenFound = true;
        return 0;
    }

    int accumulatedScore {0};
    if (grid[cellPosition.first][cellPosition.second].nearbyMines == 0)
    {
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


int Board::countNearbyMines(const std::pair<int, int> &cellPosition)
{
    int nearbyMines {0};
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <=1; j++)
            if(grid[cellPosition.first + i][cellPosition.second + j].isMine)
                nearbyMines++;

    return nearbyMines;
}

bool Board::hasCellBeenRevealed(const std::pair <int, int> &cellPosition)
{
    return grid[cellPosition.first][cellPosition.second].isRevealed;
}

bool Board::hasAllCellsBeenRevealed()
{
    return (unsigned)revealedCells >= (totalCells - minesPositions.size()); 
}

bool Board::hasMineBeenFound()
{
    return aMineHasBeenFound;
}

int Board::getRevealedCells()
{
    return revealedCells;
}

int Board::getTotalCells()
{
    return totalCells;
}

std::pair <int, int> Board::getGridDimensions()
{
    return {grid.size(), grid[0].size()};
}

std::vector <std::pair<int, int>> Board::getMinesPositions()
{
    return minesPositions;
}

void Board::drawGridNumbers(int number)
{
    if (number < 10)
        std::cout << "0" + std::to_string(number) << " ";
    else
        std::cout << number << " ";
}

void Board::drawGridCell(Cell cell)
{
    if (!cell.isRevealed)
        std::cout << "-" << "  ";
    else if (cell.isMine)
        std::cout << redText << "X" << defaultText << "  ";
    else if (cell.nearbyMines == 0)
        std::cout << greyText << cell.nearbyMines << defaultText << "  ";
    else
        std::cout << yellowText << cell.nearbyMines << defaultText << "  ";
}

void Board::setGrid(const std::pair <int, int> &gridSize)
{
    grid.resize(gridSize.first + 2);
    for (unsigned i = 0; i < grid.size(); i++)
        grid[i].resize(gridSize.second + 2);
}

void Board::setOutOfBoundsCells()
{
    for (unsigned i = 0; i < grid[0].size(); i++)
        grid[0][i].isRevealed = true;

    for (unsigned i = 0; i < grid[0].size(); i++)
        grid[grid.size() - 1][i].isRevealed = true;

    for(unsigned i = 0; i < grid.size(); i++)
        grid[i][0].isRevealed = true;

    for(unsigned i = 0; i < grid.size(); i++)
        grid[i][grid[0].size() - 1].isRevealed = true;
}

void Board::generateMines(int numberOfMines)
{
    std::random_device randomEngine;
    std::uniform_int_distribution <int> distbutionI(1, grid.size() - 2);
    std::uniform_int_distribution <int> distbutionJ(1, grid[0].size() - 2);

    int distinctPositions = 0;
    while (distinctPositions < numberOfMines)
    {
        std::pair <int, int> minePosition = {distbutionI(randomEngine), distbutionJ(randomEngine)};
        if (std::find(minesPositions.begin(), minesPositions.end(), minePosition) == minesPositions.end())
        {
            grid[minePosition.first][minePosition.second].isMine = true;
            minesPositions.push_back(minePosition);

            distinctPositions++;
        }
    }
}

void Board::setNearbyMinesCellsValues()
{
    for (unsigned i = 1; i < grid.size() - 1; i++)
        for (unsigned j = 1; j < grid[i].size() - 1; j++)
            if (!grid[i][j].isMine)
                grid[i][j].nearbyMines = countNearbyMines({i, j});
}
