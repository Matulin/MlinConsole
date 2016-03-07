#include <iostream>
#define boardLayerWidth 3
#define boardLayerHeight 3
#define numOfLayers 3
#include "include\board.h"

using namespace std;

int main()
{
    // Tests the initialisation of the board
    struct position totalBoard[numOfLayers][boardLayerHeight][boardLayerWidth];
    initBoard(totalBoard);
    displayBoard(totalBoard);
    return 0;
}
