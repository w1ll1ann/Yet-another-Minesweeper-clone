#include "minesweeper/headers/game.h"

void printHelp()
{
    std::cout << "To start Minesweeper: ./minesweeper [command]\n\n";

    std::cout << "<Command options>\n";
    std::cout << "    [easy | normal | hard] to start the game with said difficult option\n";
    std::cout << "        [easy]  :  8 x  8 Grid, 10 mines\n";
    std::cout << "        [normal]: 16 x 16 Grid, 40 mines\n";
    std::cout << "        [hard]  : 16 x 30 Grid, 90 mines\n\n";

    std::cout << "    [manual]: explains how to play the game\n\n";

    std::cout << "    [credits]: show the game's credits\n";
}

void printManual()
{
    std::cout << "<How to play Yet Another Minesweep clone>\n\n";

    std::cout << "The game starts with a board full with unrevealed cells.\n";
    std::cout << "The main objective of the game is to reveal all of them.\n";
    std::cout << "However, some of them contain deadly mines. Revealing one will result in a game over.\n";
    std::cout << "To help the player, each cell that doesn't contain a mine will inform the number of mines nearby.\n";
    std::cout << "Cells that don't contain any nearby mines will automaticaly reveal it's neighboors.\n";
    std::cout << "Use that information to precisely choose wich cell reveal and win the game.\n";
    std::cout << "Also, each revealed cell will gave the player points: 100 * Revealed cell number of nearby mines.\n\n";

    std::cout << greenText <<"Good luck :)\n" << defaultText;
}

void printCredits()
{
    std::cout << "Trabalho prático - Engenharia de Software II - 2023_2\n";
    std::cout << yellowText << "Yet another Minesweeper clone - version 0.1\n\n" << defaultText;
    std::cout << "Authors: Luana Oliveira\n"; 
    std::cout << "         Willian Braga \n";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << redText << "Incorrect number of arguments!\n\n" << defaultText;
        printHelp();
        return 0;
    }

    const std::string command {argv[1]};

    if (command == "manual")
    {
        printManual();
        return 0;
    }

    if (command == "credits")
    {
        printCredits();
        return 0;
    }

    Minesweeper::Game minesweeper;

    if (command == "easy")
        minesweeper = Minesweeper::Game({8, 8}, 10);
    else if (command == "normal")
        minesweeper = Minesweeper::Game({16, 16}, 40);
    else if (command == "hard")
        minesweeper = Minesweeper::Game({16, 30}, 90);
    else
    {
        std::cerr << redText << "Invalid command!\n\n" << defaultText;
        printHelp();
        return 0;
    }

    minesweeper.run();

    return 0;
}