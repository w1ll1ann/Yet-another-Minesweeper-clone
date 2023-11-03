#include "headers/player.h"

using namespace Minesweeper;

int Player::getScore()
{
    return score;
}

bool Player::input(Board &board)
{
    std::pair <int, int> cellPosition;
    std::cout << "Insert a coordinate[I J]\n";
    std::cout << "> ";

    std::cin >> cellPosition.first >> cellPosition.second;

    std::pair <int, int> boardDimensions = board.getGridDimensions();

    if ((cellPosition.first  < 1) 
    ||  (cellPosition.first  > boardDimensions.first) 
    ||  (cellPosition.second < 1)
    ||  (cellPosition.second > boardDimensions.second))
    {
        std::cerr << redText << "Invalid cell position!\n" << defaultText;
        return false;
    }

    if (board.hasCellBeenRevealed(cellPosition))
    {
        std::cerr << redText << "This cell has already been revealed!\n" << defaultText;
        return false;
    }

    score += board.revealCell(cellPosition);
    std::cout << "\n";

    return true;
}