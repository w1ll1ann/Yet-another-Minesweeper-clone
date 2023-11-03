#include "headers/game.h"

using namespace Minesweeper;

Game::Game() {

}

Game::Game(std::pair <int, int> gridSize, int numberOfMines) {
    board = Board(gridSize, numberOfMines);
}

void Game::run() {
    board.draw();
    std::cout << '\n';
    board.drawAll();
}