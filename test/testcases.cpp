#include <catch2/catch.hpp>
#include "../src/minesweeper/headers/game.h"

//Unit tests

TEST_CASE("testing the board's default constructor", "[board]")
{
    Minesweeper::Board board;

    REQUIRE(board.getGridDimensions() == std::pair <int, int>{10, 10});
}

TEST_CASE("testing if the board grid size is defined correctly", "[board]")
{
    Minesweeper::Board board({16, 16}, 40);

    REQUIRE(board.getGridDimensions() == std::pair <int, int>{18, 18});
}

TEST_CASE("testing if the total cell value is defined correctly", "[board]")
{
    Minesweeper::Board board({16, 30}, 10);

    REQUIRE(board.getTotalCells() == 480);
}

TEST_CASE("testing if the out of bounds cells are defined correctly", "[board]")
{
    Minesweeper::Board board({8, 8}, 10);

    //Inbound cell
    REQUIRE_FALSE(board.hasCellBeenRevealed({1, 1}));

    //The out of bounds cells at the 4 corners of the board 
    REQUIRE(board.hasCellBeenRevealed({0, 0}));
    REQUIRE(board.hasCellBeenRevealed({0, 9}));
    REQUIRE(board.hasCellBeenRevealed({9, 0}));
    REQUIRE(board.hasCellBeenRevealed({9, 9}));
}

TEST_CASE("testing the reveal cell operation", "[board]")
{
    //A board without any mines
    Minesweeper::Board board({8, 8}, 0);

    //this action will reveal all cell in the board, recursively, and returns score 0
    REQUIRE(board.revealCell({1, 1}) == 0);
}

TEST_CASE("testing the reveal all cells operation", "[board]")
{
    Minesweeper::Board board;

    board.revealAll();

    REQUIRE(board.hasAllCellsBeenRevealed());
}

TEST_CASE("testing the mine reveal check operation", "[board]")
{
    Minesweeper::Board board;

    board.revealMines();

    REQUIRE(board.hasMineBeenFound());
}

TEST_CASE("testing if all mines generated are in distinct positions", "[board]")
{
    Minesweeper::Board board({8, 8}, 20);

    std::vector <std::pair<int, int>> minesPositions = board.getMinesPositions();

    std::sort(minesPositions.begin(), minesPositions.end());

    REQUIRE(std::adjacent_find(minesPositions.begin(), minesPositions.end()) == minesPositions.end());
}

TEST_CASE("testing if the player valid input is proccessed correctly", "[player]")
{
    Minesweeper::Board board;
    Minesweeper::Player player;

    REQUIRE(player.input(board));
}

TEST_CASE("testing if the player invalid input is proccessed correctly", "[player]")
{
    Minesweeper::Board board;
    Minesweeper::Player player;

    REQUIRE_FALSE(player.input(board));
}

TEST_CASE("testing if the game board is setted correctly for the 3 main difficult settings", "[game]")
{
    Minesweeper::Game minesweeper_0({8, 8}  , 10);
    Minesweeper::Game minesweeper_1({16, 16}, 40);
    Minesweeper::Game minesweeper_2({16, 30}, 90);

    REQUIRE(minesweeper_0.getBoard()->getGridDimensions() == std::pair <int, int>{10, 10});
    REQUIRE(minesweeper_0.getBoard()->getMinesPositions().size() == 10);

    REQUIRE(minesweeper_1.getBoard()->getGridDimensions() == std::pair <int, int>{18, 18});
    REQUIRE(minesweeper_1.getBoard()->getMinesPositions().size() == 40);

    REQUIRE(minesweeper_2.getBoard()->getGridDimensions() == std::pair <int, int>{18, 32});
    REQUIRE(minesweeper_2.getBoard()->getMinesPositions().size() == 90);
}

TEST_CASE("testing the game win condition", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealAll();

    REQUIRE(minesweeper.isGameOver());
}

TEST_CASE("testing the game lose condition", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealMines();

    REQUIRE(minesweeper.isGameOver());
}

TEST_CASE("testing if the game over win message is setted propely", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealAll();

    minesweeper.isGameOver();

    REQUIRE(minesweeper.getGameOverMessage() == (greenText + "You did it!!! You revealed all cells!!! Congratulations!!!" + defaultText));
}

TEST_CASE("testing if the game over lose message is setted propely", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealMines();

    minesweeper.isGameOver();

    REQUIRE(minesweeper.getGameOverMessage() == (redText + "A mine has detonated!!! Game Over!!!" + defaultText));
}