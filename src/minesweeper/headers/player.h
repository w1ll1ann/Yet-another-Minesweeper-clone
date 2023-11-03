#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

namespace Minesweeper {
    class Player {
        public:
            void addScore(int score);
            int getScore();

            void input();

        private:
            int score {0};
    };
}

#endif