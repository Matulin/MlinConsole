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
#include <QMainWindow>
#include <QPixmap>
#include <graphics.h>
#include <game.h>
#include "interface.h"


using namespace std;
class squareGraphic;
class interfaceWindow;


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
    taking,
    blackWin,
    whiteWin,
    draw,
    beginning
};

struct saveData
{
    bool saveStatus;
    QString saveName;
};

struct tokenImage
{
    QPixmap * blackTokenMap;
    QPixmap * whiteTokenMap;
    QPixmap * emptyTokenMap;
    QPixmap * blackTokenMlinMap;
    QPixmap * whiteTokenMlinMap;

    QPixmap * blackTokenHoverMap;
    QPixmap * whiteTokenHoverMap;
    QPixmap * blackTokenSelectMap;
    QPixmap * whiteTokenSelectMap;
    QPixmap * blackTokenDeleteMap;
    QPixmap * whiteTokenDeleteMap;

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

enum coordType
{
    layer,
    x,
    y
};

class moveNode
{
public:
    unsigned int moveNum;
    unsigned int layNum;
    unsigned int xCoord;
    unsigned int yCoord;
    enum status moveType;
    enum coordType movedCoord;
    int change;
    posColour moveColour;
    QString genString();
    bool mlinStatus;

public:
    explicit moveNode();
    explicit moveNode(unsigned int inputLay, unsigned int inputX, unsigned int inputY, moveNode * givenLastNode, enum posColour turn, enum status givenMoveType = placing, bool givenMlinStatus = false);
    explicit moveNode(unsigned int inputLay, unsigned int inputX, unsigned int inputY, unsigned int oldInputLay, unsigned int oldInputX, unsigned int oldInputY, moveNode * givenLastNode, enum posColour turn, bool givenMlinStatus = false);
    moveNode * lastNode;
    moveNode * nextNode;
};


class gameData
{
public:
    explicit gameData(interfaceWindow * parentWindow, bool restart = false);
    enum status gameStatus;
    struct position board[numOfLayers][boardLayerHeight][boardLayerWidth];
    struct pieces whitePieces;
    struct pieces blackPieces;
    bool valMove(int oldx, int oldy, int oldlay, int newx, int newy, int newlay);
    QWidget * boardWidget;
    struct tokenImage tokenImage;
    enum posColour currentTurn;
    enum posColour selectedToken;
    struct position selectedPosition;
    enum posColour startingColour;

    interfaceWindow * outerWindow;
    bool checkForMove(unsigned int count, unsigned int count2, unsigned int count3);
    void changeTurns();
    struct saveData saveData;
    class moveNode * gameMoveHead;
    class moveNode * currentMoveNode;
    class moveNode * selectedMoveNode;
    unsigned int moveListSize;
    void appendMoveList(unsigned int layNum, unsigned int xCoord, unsigned int yCoord, status givenGameStatus, bool givenMlinStatus = false);


public:
    bool valPos(int xcoord, int ycoord, int layerNum);
    void displayBoard();

    bool moveToken(int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken);
    bool initBoard();
    gameData();
    bool takeToken(int xcoord, int ycoord, int laynum);
    enum posColour checkForMlin();
    void removeMlin(int xcoord, int ycoord, int laynum);
    void checkForWin();
    int checkForNewMlin(unsigned int xcoord, unsigned int ycoord, unsigned int laynum);
    bool initBoardWidget();
    bool gameFunction(unsigned int arrayXCoord, unsigned int arrayYCoord, unsigned int arrayLayNum);
    bool placePiece(unsigned int xcoord, unsigned int ycoord, unsigned int lay, enum posColour blackToken);
    bool moveSelect(unsigned int arrayXCoord, unsigned int arrayYCoord, unsigned int arrayLayNum, enum posColour currentColour);
    bool checkForTakableToken();



};

#endif // BOARD_H
