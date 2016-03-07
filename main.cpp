#include <iostream>
#include "include\board.h"
#include "game.h"

using namespace std;

int main()
{
    // Tests the initialisation of the board
    struct gameData gameData;
    initGame(&gameData);
    displayBoard(gameData.board);
    return 0;
}
