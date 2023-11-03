#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

namespace Minesweeper {
    class Game {
        public:
            Game();
            Game(std::pair <int, int> gridSize, int numberOfMines);

            void run();
        private:
            Board board;
            Player player;
    };
}

#endif