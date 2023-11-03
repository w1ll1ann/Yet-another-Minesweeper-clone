#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

namespace Minesweeper {
    class Player {
        public:
            int getScore();
            bool input(Board &board);
        private:
            int score {0};
    };
}

#endif