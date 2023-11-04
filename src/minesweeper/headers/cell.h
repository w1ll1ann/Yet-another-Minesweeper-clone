#ifndef CELL_H
#define CELL_H

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
}

#endif