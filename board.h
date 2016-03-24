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

enum status
{
    placing,
    moving,
    blackWin,
    whiteWin,
    draw
};

class gameData
{
private:
    enum status gameStatus;
    struct position board[numOfLayers][boardLayerHeight][boardLayerWidth];
    struct pieces whitePieces;
    struct pieces blackPieces;
    bool valMove(int oldx, int oldy, int oldlay, int newx, int newy, int newlay);

public:
    bool valPos(int xcoord, int ycoord, int layerNum);
    void displayBoard();
    bool placePiece(int xcoord, int ycoord, int lay, enum posColour newToken);
    bool moveToken(int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken);
    bool initBoard();
    gameData();
    bool takeToken(int xcoord, int ycoord, int laynum, enum posColour token);
    enum posColour checkForMlin();
    void removeMlin(int xcoord, int ycoord, int laynum);
    void checkForWin();
    int checkForNewMlin(int xcoord, int ycoord, int laynum);
};




#endif // BOARD_H
