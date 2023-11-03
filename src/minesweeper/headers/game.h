#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

namespace Minesweeper {
    class Game {
        public:
            Game() = default;
            Game(std::pair <int, int> gridSize, int numberOfMines);

            void run();
        private:
            Board board;
            Player player;

            std::string gameOverMessage = redText + "A mine has detonated!!! Game Over!!!" + defaultText;

            bool isGameOver();

            void playGame();
            void endGame();
    };
}

#endif