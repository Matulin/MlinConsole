#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QtGui>
#include <QString>
#include <QFont>
#include "toolbar.h"
#include "options.h"

class gameData;
class gameToolbar;
class optionFunctions;

class interfaceWindow : public QVBoxLayout
{
    Q_OBJECT

public:

    explicit interfaceWindow();
    explicit interfaceWindow(class gameData * data, QWidget *parent = 0);
    ~interfaceWindow();
public:
    class gameData * thisGameData;
    QVBoxLayout * gameSideBar;
    QHBoxLayout * gameWindow;
    bool setInterfaceWidgets();
    static void testPrint();

    QLabel * messageBox;
    QLabel * messageBox2;
    QLabel * messageBox3;
    QLabel * turnInfo;
    QLabel * turnInfo2;
    QHBoxLayout * turnInfoBox;
    QLabel * blackPiecesMessage;
    QLabel * blackPiecesUnplaced;
    QLabel * blackPiecesUnplaced2 = new QLabel;
    QHBoxLayout * blackPiecesUnplacedBox;
    QLabel * blackPiecesTaken;
    QLabel * blackPiecesTaken2;
    QHBoxLayout * blackPiecesTakenBox;
    QLabel * blackPiecesUnplacedMessage;
    QLabel * blackPiecesTakenMessage;
    gameToolbar * toolbar;


    QLabel * whitePiecesMessage;
    QLabel * whitePiecesUnplaced = new QLabel;
    QLabel * whitePiecesUnplaced2;
    QHBoxLayout * whitePiecesUnplacedBox;
    QLabel * whitePiecesTaken;
    QLabel * whitePiecesTaken2;
    QHBoxLayout * whitePiecesTakenBox;
    QLabel * whitePiecesUnplacedMessage;
    QLabel * whitePiecesTakenMessage;

};



#endif // INTERFACE_H
