#include "headers/game.h"

using namespace Minesweeper;

Game::Game(const std::pair <int, int> &gridSize, int numberOfMines)
{
    board = Board(gridSize, numberOfMines);
}

bool Game::isGameOver()
{
    if (board.hasAllCellsBeenRevealed())
    {
        gameOverMessage = greenText + "You did it!!! You revealed all cells!!! Congratulations!!!" + defaultText;
        return true;
    }

    if (board.hasMineBeenFound())
        return true;

    return false;
}

void Game::run()
{
    std::cout << yellowText << "Yet another Minesweeper clone - version 0.1\n\n" << defaultText;

    playGame();
    endGame();
}

Board* Game::getBoard()
{
    return &board;
}

std::string Game::getGameOverMessage()
{
    return gameOverMessage;
}

void Game::playGame()
{
    int turn {1};
    while (true)
    {
        std::cout << yellowText << "[Turn " << turn << "]\n" << defaultText;

        board.draw();
        std::cout << "\nScore: " << player.getScore() << "\n\n";

        while (!player.input(board));

        if (isGameOver())
            break;

        turn++;
    }
}

void Game::endGame()
{
    board.revealMines();
    board.draw();

    std::cout << "\n" << gameOverMessage << "\n";
    std::cout << "\nFinal score: " << player.getScore() << "\n";
}