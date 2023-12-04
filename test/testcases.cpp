#include <catch2/catch.hpp>
#include "../src/minesweeper/headers/game.h"

//Unit tests

//1
TEST_CASE("testing the board's default constructor", "[board]")
{
    Minesweeper::Board board;

    REQUIRE(board.getGridDimensions() == std::pair <int, int>{10, 10});
}

//2
TEST_CASE("testing if the board grid size is defined correctly", "[board]")
{
    Minesweeper::Board board({16, 16}, 40);

    REQUIRE(board.getGridDimensions() == std::pair <int, int>{18, 18});
}

//3
TEST_CASE("testing if the total cells value is defined correctly", "[board]")
{
    Minesweeper::Board board({16, 30}, 10);

    REQUIRE(board.getTotalCells() == 480);
}

//4
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

//5
TEST_CASE("testing the reveal all cells operation", "[board]")
{
    Minesweeper::Board board;

    board.revealAll();

    REQUIRE(board.hasAllCellsBeenRevealed());
}

//6
TEST_CASE("testing the reveal cell operation on a board without mines", "[board]")
{
    //A board without any mines
    Minesweeper::Board board({8, 8}, 0);

    //this action will reveal all cells in the board, recursively
    board.revealCell({1, 1});

    REQUIRE(board.hasAllCellsBeenRevealed());
}

//7
TEST_CASE("testing the reveal cell operation on a board full of mines", "[board]")
{
    Minesweeper::Board board({8, 8}, 64);

    board.revealCell({1, 1});

    REQUIRE(board.getRevealedCells() == 1);
}

//8
TEST_CASE("testing the mine reveal check operation", "[board]")
{
    Minesweeper::Board board;

    board.revealMines();

    REQUIRE(board.hasMineBeenFound());
}

//9
TEST_CASE("testing if all mines generated are in distinct positions", "[board]")
{
    Minesweeper::Board board({8, 8}, 20);

    std::vector <std::pair<int, int>> minesPositions = board.getMinesPositions();

    std::sort(minesPositions.begin(), minesPositions.end());

    REQUIRE(std::adjacent_find(minesPositions.begin(), minesPositions.end()) == minesPositions.end());
}

//10
TEST_CASE("testing the couting nearby cells operation", "[board]")
{
    Minesweeper::Board board({8, 8}, 64);

    REQUIRE(board.countNearbyMines({1, 1}) == 4);
    REQUIRE(board.countNearbyMines({2, 2}) == 9);
}

//11
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

//12
TEST_CASE("testing the game win condition", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealAll();

    REQUIRE(minesweeper.isGameOver());
}

//13
TEST_CASE("testing the game lose condition", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealMines();

    REQUIRE(minesweeper.isGameOver());
}

//14
TEST_CASE("testing if the game over win message is defined propely", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealAll();

    minesweeper.isGameOver();

    REQUIRE(minesweeper.getGameOverMessage() == (greenText + "You did it!!! You revealed all cells!!! Congratulations!!!" + defaultText));
}

//15
TEST_CASE("testing if the game over lose message is defined propely", "[game]")
{
    Minesweeper::Game minesweeper;
    minesweeper.getBoard()->revealMines();

    minesweeper.isGameOver();

    REQUIRE(minesweeper.getGameOverMessage() == (redText + "A mine has detonated!!! Game Over!!!" + defaultText));
}

//Integration/System tests

//1
TEST_CASE("testing if the player valid input is proccessed correctly", "[player/board]")
{
    Minesweeper::Board board;
    Minesweeper::Player player;

    REQUIRE(player.input(board));
}

//2
TEST_CASE("testing if the player invalid input by inserting a out of bounds cell position is proccessed correctly", "[player/board]")
{
    Minesweeper::Board board;
    Minesweeper::Player player;

    REQUIRE_FALSE(player.input(board));
}

//3
TEST_CASE("testing if the player invalid input by inserting a revealed cell position is proccessed correctly", "[player/board]")
{
    Minesweeper::Board board;
    Minesweeper::Player player;

    board.revealAll();

    REQUIRE_FALSE(player.input(board));
}

//4
TEST_CASE("testing gameflow where the player is garanted to win", "[game/player]")
{
    Minesweeper::Game minesweeper({8, 8}, 0);
    minesweeper.run();

    REQUIRE(minesweeper.getGameOverMessage() == (greenText + "You did it!!! You revealed all cells!!! Congratulations!!!" + defaultText));
}

//5
TEST_CASE("testing gameflow where the player is garanted to lose", "[game/player]")
{
    Minesweeper::Game minesweeper({8, 8}, 64);
    minesweeper.run();

    REQUIRE(minesweeper.getGameOverMessage() == (redText + "A mine has detonated!!! Game Over!!!" + defaultText));
}