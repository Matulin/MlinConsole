#ifndef BOARD_H
#define BOARD_H
#define boardLayerWidth 3
#define boardLayerHeight 3
#define numOfLayers 3
#include <iostream>

using namespace std;

typedef enum posColour
{
    blackToken,
    whiteToken,
    noToken,
    invalidToken
};

typedef enum posType
{
    corner,
    intersection,
    centre
};

typedef struct position
{
    posType type;
    posColour colour;
};

typedef position boardLayer[boardLayerHeight][boardLayerWidth];

typedef boardLayer totalBoard[numOfLayers];

#endif // BOARD_H
