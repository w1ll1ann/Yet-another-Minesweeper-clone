#include "headers/game.h"

using namespace Minesweeper;

Game::Game(std::pair <int, int> gridSize, int numberOfMines) {
    board = Board(gridSize, numberOfMines);
}

void Game::run() {
    std::cout << yellowText << "Yet another Minesweeper clone - version 0.1\n\n" << defaultText;

    std::string gameOverMessage = redText + "A mine has detonated!!! Game Over!!!" + defaultText;
    int turn {1};

    while (true) {
        std::cout << yellowText << "[Turn " +  turn + "\n" + defaultText;

        board.draw();
        std::cout << "\nScore: " << player.getScore() << "\n\n";

        while !player.input();

        turn++;

        if (board.hasCellBeenRevealed()) {
            gameOverMessage = greenText << "You did it!!! You revealed all cells!!! Congratulations!!!" << defaultText;
            break;
        }

        if (board.hasMineBeenFound())
            break;
    }

    board.revealMines();
    std::cout << "\nFinal score: " << player.getScore() << "\n";
}