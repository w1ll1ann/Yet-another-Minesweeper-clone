#ifndef CELL_H
#define CELL_H

namespace Minesweeper {
    struct Cell {
        bool isRevealed {false};
        bool isMine {false};

        int nearbyMines {0};
    };
}

#endif