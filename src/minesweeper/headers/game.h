#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

namespace Minesweeper
{
    class Game
    {
        public:
            Game() = default;
            Game(const std::pair <int, int> &gridSize, int numberOfMines);

            bool isGameOver();

            void run();

            Board* getBoard();

            std::string getGameOverMessage();

        private:
            Board board;
            Player player;

            std::string gameOverMessage = redText + "A mine has detonated!!! Game Over!!!" + defaultText;

            void playGame();
            void endGame();
    };
}

#endif