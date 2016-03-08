#ifndef GAME_H
#define GAME_H
#include "board.h"

enum status
{
    placing,
    moving,
    blackWin,
    whiteWin,
    draw
};

struct gameData
{
    enum status gameStatus;
    struct position board[numOfLayers][boardLayerHeight][boardLayerWidth];
    struct pieces whitePieces;
    struct pieces blackPieces;
};
#endif // GAME_H
