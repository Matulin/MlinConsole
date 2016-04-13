#include "interface.h"

interfaceWindow::interfaceWindow(QWidget *parent)
    : QWidget(parent)
{
    thisGameData = new gameData;
    gameWindow = new QHBoxLayout;
    gameSideBar = new QVBoxLayout;

    QLabel * messageBox = new QLabel;
    gameSideBar->addWidget(messageBox);

    QLabel * turnInfo = new QLabel;
    QLabel * turnInfo2 = new QLabel;
    QHBoxLayout * turnInfoBox = new QHBoxLayout;
    turnInfoBox->addWidget(turnInfo);
    turnInfoBox->addWidget(turnInfo2);
    gameSideBar->addLayout(turnInfoBox);

    QLabel * blackPiecesMessage = new QLabel;
    QLabel * blackPiecesUnplaced = new QLabel;
    QLabel * blackPiecesUnplaced2 = new QLabel;
    QHBoxLayout * blackPiecesUnplayedBox = new QHBoxLayout;
    QLabel * blackPiecesTaken = new QLabel;
    QLabel * blackPiecesTaken2 = new QLabel;
    QHBoxLayout * blackPiecesTakenBox = new QHBoxLayout;
    blackPiecesTakenBox->addWidget(blackPiecesTaken);
    blackPiecesTakenBox->addWidget(blackPiecesTaken2);
    gameSideBar->addWidget(blackPiecesMessage);
    gameSideBar->addLayout(blackPiecesUnplayedBox);
    gameSideBar->addLayout(blackPiecesTakenBox);

    QLabel * whitePiecesMessage = new QLabel;
    QLabel * whitePiecesUnplaced = new QLabel;
    QLabel * whitePiecesUnplaced2 = new QLabel;
    QHBoxLayout * whitePiecesUnplayedBox = new QHBoxLayout;
    QLabel * whitePiecesTaken = new QLabel;
    QLabel * whitePiecesTaken2 = new QLabel;
    QHBoxLayout * whitePiecesTakenBox = new QHBoxLayout;
    whitePiecesTakenBox->addWidget(whitePiecesTaken);
    whitePiecesTakenBox->addWidget(whitePiecesTaken2);
    gameSideBar->addWidget(whitePiecesMessage);
    gameSideBar->addLayout(whitePiecesUnplayedBox);
    gameSideBar->addLayout(whitePiecesTakenBox);

    gameWindow->addWidget(thisGameData->boardWidget);
    gameWindow->addLayout(gameSideBar);

    setLayout(gameWindow);

    initInterfaceWidgets();
}

interfaceWindow::~interfaceWindow()
{

}

bool interfaceWindow::initInterfaceWidgets()
{
    return true;
}
