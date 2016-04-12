#ifndef BOARD_H
#define BOARD_H

#define boardLayerWidth 3
#define boardLayerHeight 3
#define numOfLayers 3
#define numPieces 9
#define boardWidgetWidth 12
#define boardWidgetHeight 14

#include <iostream>
#include <QLabel>
#include <QGridLayout>
#include <QtGui>
#include <QTCore>
#include <QMainWindow>
#include <QPixmap>
#include <graphics.h>
#include <game.h>


using namespace std;
class squareGraphic;


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
    unsigned int mlinStatus;
    squareGraphic * locImg;
    int xCoordWidget;
    int yCoordWidget;
    unsigned int arrayLayNum;
    unsigned int arrayXCoord;
    unsigned int arrayYCoord;

    void setCoords(unsigned int layNum, unsigned int XCoord, unsigned int YCoord);
    bool placePiece(enum posColour newToken);
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

enum currentTurn
{
    black,
    white
};

struct tokenImage
{
    QPixmap * blackTokenMap;
    QPixmap * whiteTokenMap;
    QPixmap * emptyTokenMap;
    QPixmap * blackTokenMlinMap;
    QPixmap * whiteTokenMlinMap;
    QPixmap * cornerBottomLeftMap;
    QPixmap * cornerBottomRightMap;
    QPixmap * cornerTopLeftMap;
    QPixmap * cornerTopRightMap;
    QPixmap * horizontalLineMap;
    QPixmap * verticalLineMap;
    QPixmap * intersectionBottomMap;
    QPixmap * intersectionTopMap;
    QPixmap * intersectionLeftMap;
    QPixmap * intersectionRightMap;
    QPixmap * intersectionMiddleMap;

    QPixmap * cornerBottomLeftHoverMap;
    QPixmap * cornerBottomRightHoverMap;
    QPixmap * cornerTopLeftHoverMap;
    QPixmap * cornerTopRightHoverMap;
    QPixmap * horizontalLineHoverMap;
    QPixmap * verticalLineHoverMap;
    QPixmap * intersectionBottomHoverMap;
    QPixmap * intersectionTopHoverMap;
    QPixmap * intersectionLeftHoverMap;
    QPixmap * intersectionRightHoverMap;
    QPixmap * intersectionMiddleHoverMap;
};


class gameData
{
public:
    enum status gameStatus;
    struct position board[numOfLayers][boardLayerHeight][boardLayerWidth];
    struct pieces whitePieces;
    struct pieces blackPieces;
    bool valMove(int oldx, int oldy, int oldlay, int newx, int newy, int newlay);
    QWidget * boardWidget;
    struct tokenImage tokenImage;
    enum currentTurn currentTurn;
    enum posColour selectedToken;


public:
    bool valPos(int xcoord, int ycoord, int layerNum);
    void displayBoard();

    bool moveToken(int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken);
    bool initBoard();
    gameData();
    bool takeToken(int xcoord, int ycoord, int laynum, enum posColour token);
    enum posColour checkForMlin();
    void removeMlin(int xcoord, int ycoord, int laynum);
    void checkForWin();
    int checkForNewMlin(int xcoord, int ycoord, int laynum);
    bool initBoardWidget();
    bool gameFunction(unsigned int arrayXCoord, unsigned int arrayYCoord, unsigned int arrayLayNum);
    bool placePiece(unsigned int xcoord, unsigned int ycoord, unsigned int lay, enum posColour blackToken);



};

#endif // BOARD_H
