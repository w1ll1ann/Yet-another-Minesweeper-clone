#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "cell.h"

namespace Minesweeper {
    class Board {
        public:
            Board();
            void draw();
        private:
            std::vector < std::vector < Cell > > grid;
    };
}

#endif