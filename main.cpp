#include <iostream>
#define boardLayerWidth 3
#define boardLayerHeight 3
#define numOfLayers 3
#include "include\board.h"

using namespace std;

int main()
{
    // Tests the initialisation of the board
    struct gameData gameData;
    initGame(&gameData);
    displayBoard(gameData.board);
    return 0;
}
