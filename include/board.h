#ifndef BOARD_H
#define BOARD_H
#define boardLayerWidth 3
#define boardLayerHeight 3
#define numOfLayers 3
#define numPieces 9
#include <iostream>

using namespace std;

enum posColour
{
    blackToken,
    whiteToken,
    noToken,
    invalidToken
};

enum posType
{
    corner,
    intersection,
    centre
};

struct position
{
    posType type;
    posColour colour;
    int mlinStatus;
};



struct pieces
{
    int piecesOnBoard;
    int piecesUnplaced;
    int piecesTaken;
};



bool moveToken(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken);
bool placePiece(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int xcoord, int ycoord, int lay, enum posColour newToken);
void displayBoard(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth]);
bool valMove(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int oldx, int oldy, int oldlay, int newx, int newy, int newlay);
bool valPos(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int xcoord, int ycoord, int layerNum);
bool initBoard(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth]);
void initGame(struct gameData * gameData);


#endif // BOARD_H
