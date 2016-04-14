#include "interface.h"

interfaceWindow::interfaceWindow(QWidget *parent)
    : QWidget(parent)
{
    thisGameData = new gameData(this);
    gameWindow = new QHBoxLayout;
    gameSideBar = new QVBoxLayout;

    QFont * boldFont = new QFont;
    boldFont->setBold(true);
    QFont * boldRedFont = new QFont;
    boldRedFont->setBold(true);

    messageBox = new QLabel;
    messageBox2 = new QLabel;
    messageBox3 = new QLabel;
    messageBox->setFont(*boldFont);
    messageBox2->setFont(*boldRedFont);
    messageBox3->setFont(*boldRedFont);
    gameSideBar->addWidget(messageBox);
    gameSideBar->addWidget(messageBox2);
    gameSideBar->addWidget(messageBox3);

    turnInfo = new QLabel;
    turnInfo2 = new QLabel;
    turnInfoBox = new QHBoxLayout;
    turnInfoBox->addWidget(turnInfo);
    turnInfoBox->addWidget(turnInfo2);
    gameSideBar->addLayout(turnInfoBox);

    blackPiecesMessage = new QLabel;
    blackPiecesMessage->setText("Black pieces:");
    blackPiecesMessage->setFont(*boldFont);
    blackPiecesTakenMessage = new QLabel;
    blackPiecesUnplacedMessage = new QLabel;
    blackPiecesUnplaced = new QLabel;
    blackPiecesUnplaced2 = new QLabel;
    blackPiecesUnplacedBox = new QHBoxLayout;
    blackPiecesTaken = new QLabel;
    blackPiecesTaken2 = new QLabel;
    blackPiecesUnplacedBox->addWidget(blackPiecesUnplaced);
    blackPiecesUnplacedBox->addWidget(blackPiecesUnplaced2);
    blackPiecesTakenBox = new QHBoxLayout;
    blackPiecesTakenBox->addWidget(blackPiecesTaken);
    blackPiecesTakenBox->addWidget(blackPiecesTaken2);
    gameSideBar->addWidget(blackPiecesMessage);
    gameSideBar->addWidget(blackPiecesUnplacedMessage);
    gameSideBar->addLayout(blackPiecesUnplacedBox);
    gameSideBar->addWidget(blackPiecesTakenMessage);
    gameSideBar->addLayout(blackPiecesTakenBox);

    whitePiecesMessage = new QLabel;
    whitePiecesMessage->setText("White pieces:");
    whitePiecesMessage->setFont(*boldFont);
    whitePiecesUnplacedMessage = new QLabel;
    whitePiecesTakenMessage = new QLabel;
    whitePiecesUnplaced = new QLabel;
    whitePiecesUnplaced2 = new QLabel;
    whitePiecesUnplacedBox = new QHBoxLayout;
    whitePiecesTaken = new QLabel;
    whitePiecesTaken2 = new QLabel;
    whitePiecesTakenBox = new QHBoxLayout;
    whitePiecesUnplacedBox->addWidget(whitePiecesUnplaced);
    whitePiecesUnplacedBox->addWidget(whitePiecesUnplaced2);
    whitePiecesTakenBox->addWidget(whitePiecesTaken);
    whitePiecesTakenBox->addWidget(whitePiecesTaken2);
    gameSideBar->addWidget(whitePiecesMessage);
    gameSideBar->addWidget(whitePiecesUnplacedMessage);
    gameSideBar->addLayout(whitePiecesUnplacedBox);
    gameSideBar->addWidget(whitePiecesTakenMessage);
    gameSideBar->addLayout(whitePiecesTakenBox);

    gameWindow->addWidget(thisGameData->boardWidget);
    gameWindow->addLayout(gameSideBar);

    setLayout(gameWindow);

    setInterfaceWidgets();
}

interfaceWindow::~interfaceWindow()
{

}

bool interfaceWindow::setInterfaceWidgets()
{
    // Sets the value of "messageBox"
    if(thisGameData->currentTurn == blackToken)
    {
        if(thisGameData->gameStatus == placing)
        {
            messageBox->setText("Black Placing");
        }
        else if(thisGameData->gameStatus == moving)
        {
            messageBox->setText("Black Moving");
        }
        else if(thisGameData->gameStatus == taking)
        {
            messageBox->setText("Black Taking");
        }
    }
    else if(thisGameData->currentTurn == whiteToken)
    {
        if(thisGameData->gameStatus == placing)
        {
            messageBox->setText("White Placing");
        }
        else if(thisGameData->gameStatus == moving)
        {
            messageBox->setText("White Moving");
        }
        else if(thisGameData->gameStatus == taking)
        {
            messageBox->setText("White Taking");
        }
    }

    if(thisGameData->gameStatus == whiteWin)
    {
        messageBox->setText("White wins!");
    }
    else if(thisGameData->gameStatus == blackWin)
    {
        messageBox->setText("Black wins!");
    }

    if(thisGameData->blackPieces.piecesUnplaced > 0)
    {
        blackPiecesUnplacedMessage->setText("Pieces Unplaced: ");
        blackPiecesUnplaced->setPixmap(*thisGameData->tokenImage.blackTokenMap);
        QString tokenText = QString::fromStdString("x" + std::to_string(thisGameData->blackPieces.piecesUnplaced));
        blackPiecesUnplaced2->setText(tokenText);
    }
    else if(thisGameData->blackPieces.piecesUnplaced == 0)
    {
        blackPiecesUnplacedMessage->clear();
        //blackPiecesUnplaced->setPixmap(*thisGameData->tokenImage.emptyTokenMap);
        blackPiecesUnplaced->clear();
        blackPiecesUnplaced2->clear();
    }

    if(thisGameData->whitePieces.piecesUnplaced > 0)
    {
       whitePiecesUnplacedMessage->setText("Pieces Unplaced: ");
       whitePiecesUnplaced->setPixmap(*thisGameData->tokenImage.whiteTokenMap);
       QString tokenText = QString::fromStdString("x" + std::to_string(thisGameData->whitePieces.piecesUnplaced));
       whitePiecesUnplaced2->setText(tokenText);
    }
    else if(thisGameData->blackPieces.piecesUnplaced == 0)
    {
        whitePiecesUnplacedMessage->clear();
        // whitePiecesUnplaced->setPixmap(*thisGameData->tokenImage.emptyTokenMap);
        whitePiecesUnplaced->clear();
        whitePiecesUnplaced2->clear();
    }

    if(thisGameData->blackPieces.piecesTaken > 0)
    {
       blackPiecesTakenMessage->setText("Pieces Taken: ");
       blackPiecesTaken->setPixmap(*thisGameData->tokenImage.blackTokenMap);
       QString tokenText = QString::fromStdString("x" + std::to_string(thisGameData->blackPieces.piecesTaken));
       blackPiecesTaken2->setText(tokenText);
    }
    else if(thisGameData->blackPieces.piecesTaken == 0)
    {
        blackPiecesTakenMessage->clear();
        //blackPiecesTaken->setPixmap(*thisGameData->tokenImage.emptyTokenMap);
        blackPiecesTaken->clear();
        blackPiecesTaken2->clear();
    }

    if(thisGameData->whitePieces.piecesTaken > 0)
    {
        whitePiecesTakenMessage->setText("Pieces Taken: ");
        whitePiecesTaken->setPixmap(*thisGameData->tokenImage.whiteTokenMap);
        QString tokenText = QString::fromStdString("x" + std::to_string(thisGameData->whitePieces.piecesTaken));
        whitePiecesTaken2->setText(tokenText);
    }
    else if(thisGameData->whitePieces.piecesUnplaced == 0)
    {
        whitePiecesTakenMessage->clear();
        //whitePiecesTaken->setPixmap(*thisGameData->tokenImage.emptyTokenMap);
        whitePiecesTaken->clear();
        whitePiecesTaken2->clear();
    }
    return true;
}

void interfaceWindow::testPrint()
{
    std::cout << "test" << std::endl;
}
