#include "interface.h"

interfaceWindow::interfaceWindow(MainWindow *parent)
{

    thisGameData = new gameData(this);
    gameWindow = new QHBoxLayout;
    gameSideBar = new QVBoxLayout;
    mainWindowWidget = parent;
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

    optionFunctions * options = new optionFunctions(thisGameData);
    toolbar = new gameToolbar(options);

    gameMoveListLayout = new QVBoxLayout;
    gameMoveListLayout->setAlignment(Qt::AlignTop);

    gameWindow->addWidget(thisGameData->boardWidget);
    gameWindow->addLayout(gameSideBar);
    gameWindow->addLayout(gameMoveListLayout);
    addLayout(gameWindow);
    setMenuBar(toolbar);
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
        blackPiecesUnplaced->clear();
        blackPiecesUnplaced2->clear();
    }

    if((thisGameData->blackPieces.piecesUnplaced == 0) && (thisGameData->blackPieces.piecesTaken == 0))
        blackPiecesMessage->hide();
    else
        blackPiecesMessage->show();

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
        whitePiecesTaken->clear();
        whitePiecesTaken2->clear();
    }

    if((thisGameData->whitePieces.piecesUnplaced == 0) && (thisGameData->whitePieces.piecesTaken == 0))
        whitePiecesMessage->hide();
    else
        whitePiecesMessage->show();

    setMoveList();
    return true;
}


void interfaceWindow::setMoveList()
{
    QLayoutItem * layoutWidget;
    while((layoutWidget = gameMoveListLayout->takeAt(0)) != 0 )
    {
        QLayout * innerLayout;
        innerLayout = layoutWidget->layout();
        QLayoutItem * innerLayoutWidget;
        while((innerLayoutWidget = innerLayout->takeAt(0)) != 0 )
        {
            QWidget * tempWidget;
            tempWidget = innerLayoutWidget->widget();
            delete tempWidget;
        }
        delete layoutWidget;
    }

    QHBoxLayout * arrowBox = new QHBoxLayout;
    QPushButton * backAllButton = new QPushButton;
    QPushButton * backOneButton = new QPushButton;
    QPushButton * forwardOneButton = new QPushButton;
    QPushButton * forwardAllButton = new QPushButton;
    backAllButton->setStyleSheet("background-image:url(resources/backAllArrow.png);");
    backOneButton->setStyleSheet("background-image:url(resources/backArrow.png);");
    forwardOneButton->setStyleSheet("background-image:url(resources/forwardArrow.png);");
    forwardAllButton->setStyleSheet("background-image:url(resources/forwardAllArrow.png);");
    formatArrowButton(backAllButton);
    formatArrowButton(backOneButton);
    formatArrowButton(forwardAllButton);
    formatArrowButton(forwardOneButton);
    arrowBox->addWidget(backAllButton);
    arrowBox->addWidget(backOneButton);
    arrowBox->addWidget(forwardOneButton);
    arrowBox->addWidget(forwardAllButton);

    connect(backOneButton, SIGNAL(clicked()), this, SLOT(scrollBack()));
    connect(forwardOneButton, SIGNAL(clicked()), this, SLOT(scrollForward()));
    connect(backAllButton, SIGNAL(clicked()), this, SLOT(scrollBackAll()));
    connect(forwardAllButton, SIGNAL(clicked()), this, SLOT(scrollForwardAll()));


    QHBoxLayout * moveListTitleBox = new QHBoxLayout;
    QLabel * titleBox1 = new QLabel("   Black   ");
    QLabel * titleBox2 = new QLabel("   White   ");
    titleBox1->setAlignment(Qt::AlignHCenter);
    titleBox2->setAlignment(Qt::AlignHCenter);
    QPalette whiteTitlePalette;
    whiteTitlePalette.setColor(QPalette::WindowText, Qt::white);
    titleBox2->setPalette(whiteTitlePalette);

    if(thisGameData->startingColour == blackToken)
    {
        moveListTitleBox->addWidget(titleBox1);
        moveListTitleBox->addWidget(titleBox2);
    }
    else if(thisGameData->startingColour == whiteToken)
    {
        moveListTitleBox->addWidget(titleBox2);
        moveListTitleBox->addWidget(titleBox1);
    }
    gameMoveListLayout->addLayout(arrowBox);
    gameMoveListLayout->addLayout(moveListTitleBox);


    QScrollArea * moveListScrollArea = new QScrollArea;
    moveListScrollArea->setFrameShape(QFrame::NoFrame);
    QVBoxLayout * moveListInnerLayout = new QVBoxLayout;
    QWidget * moveListWidget = new QWidget;
    moveListWidget->setLayout(moveListInnerLayout);

    moveListScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    moveListScrollArea->setVerticalScrollBarPolicy(Qt::	ScrollBarAsNeeded);
    QVBoxLayout * scrollAreaLayout = new QVBoxLayout;
    scrollAreaLayout->addWidget(moveListScrollArea);
    gameMoveListLayout->addLayout(scrollAreaLayout);
    gameMoveListLayout->setAlignment(scrollAreaLayout, Qt::AlignHCenter);
    scrollAreaLayout->setAlignment(moveListScrollArea, Qt::AlignHCenter);
    moveListInnerLayout->setGeometry(gameMoveListLayout->geometry());

    if(thisGameData->gameMoveHead->nextNode != NULL)
    {
        QHBoxLayout * gameStatusBox = new QHBoxLayout;
        QLabel * placingLabel = new QLabel("Placing");
        gameStatusBox->addWidget(placingLabel);
        gameStatusBox->setAlignment(placingLabel, Qt::AlignHCenter);

        moveListInnerLayout->addLayout(gameStatusBox);
        moveListInnerLayout->setAlignment(gameStatusBox, Qt::AlignHCenter);
        moveNode * tempNode = thisGameData->gameMoveHead;

        while((tempNode->nextNode) != NULL)
        {
            tempNode = tempNode->nextNode;

            if(tempNode->moveType == placing)
            {
                QString moveName1 = tempNode->genString();
                QHBoxLayout * tempRowBox = new QHBoxLayout;
                QLabel * rowLabel1 = new QLabel(moveName1);
                tempRowBox->addWidget(rowLabel1);
                QLabel * rowLabel2 = new QLabel();
                tempRowBox->addWidget(rowLabel2);
                rowLabel1->setAlignment(Qt::AlignHCenter);
                rowLabel2->setAlignment(Qt::AlignHCenter);
                moveListInnerLayout->addLayout(tempRowBox);
                styleMoveLabel(tempNode, rowLabel1);
                //gameStatusBox->setAlignment(placingLabel, Qt::AlignHCenter);


                if(tempNode->nextNode != NULL)
                {
                    QHBoxLayout * tempRowBox2;
                    if(tempNode->nextNode->moveType == taking)
                    {
                        tempNode = tempNode->nextNode;
                        addTakingMove(tempNode, moveListInnerLayout);
                        tempRowBox2 = new QHBoxLayout;
                        QLabel * emptyLabel = new QLabel("      ");
                        tempRowBox2->addWidget(emptyLabel);
                    }
                    else
                        tempRowBox2 = tempRowBox;

                    if((tempNode->nextNode != NULL) && (tempNode->nextNode->moveType == placing))
                    {
                        tempNode = tempNode->nextNode;
                        QString moveName2 = tempNode->genString();
                        rowLabel2->setText(moveName2);
                        tempRowBox2->addWidget(rowLabel2);
                        if(tempRowBox2 != tempRowBox)
                            moveListInnerLayout->addLayout(tempRowBox2);

                        styleMoveLabel(tempNode, rowLabel2);

                        if((tempNode->nextNode != NULL) && (tempNode->nextNode->moveType == taking))
                        {
                            addTakingMove(tempNode, moveListInnerLayout);
                        }
                    }

                    // This should also be an "else if".
                    if((tempNode->nextNode != NULL) && (tempNode->nextNode->moveType == moving))
                    {
                        QHBoxLayout * gameStatusBox2 = new QHBoxLayout;
                        QLabel * movingLabel = new QLabel("Moving");
                        gameStatusBox2->addWidget(movingLabel);
                        gameStatusBox2->setAlignment(movingLabel, Qt::AlignHCenter);
                        moveListInnerLayout->addLayout(gameStatusBox2);
                    }
                }
            }
            else if(tempNode->moveType == moving)
            {
                QString moveName1 = tempNode->genString();
                QHBoxLayout * tempRowBox = new QHBoxLayout;
                QLabel * rowLabel1 = new QLabel(moveName1);
                tempRowBox->addWidget(rowLabel1);
                QLabel * rowLabel2 = new QLabel();
                rowLabel1->setAlignment(Qt::AlignHCenter);
                rowLabel2->setAlignment(Qt::AlignHCenter);
                tempRowBox->addWidget(rowLabel2);
                moveListInnerLayout->addLayout(tempRowBox);
                styleMoveLabel(tempNode, rowLabel1);

                if(tempNode->nextNode != NULL)
                {
                    QHBoxLayout * tempRowBox2;
                    if(tempNode->nextNode->moveType == taking)
                    {
                        tempNode = tempNode->nextNode;
                        addTakingMove(tempNode, moveListInnerLayout);
                        tempRowBox2 = new QHBoxLayout;
                        QLabel * emptyLabel = new QLabel("      ");
                        tempRowBox2->addWidget(emptyLabel);
                    }
                    else
                        tempRowBox2 = tempRowBox;

                    if((tempNode->nextNode != NULL) && (tempNode->nextNode->moveType == moving))
                    {
                        tempNode = tempNode->nextNode;
                        QString moveName2 = tempNode->genString();
                        rowLabel2->setText(moveName2);
                        tempRowBox2->addWidget(rowLabel2);
                        if(tempRowBox2 != tempRowBox)
                            moveListInnerLayout->addLayout(tempRowBox2);

                        styleMoveLabel(tempNode, rowLabel2);
                    }

                    if((tempNode->nextNode != NULL) && (tempNode->nextNode->moveType == taking))
                        addTakingMove(tempNode, moveListInnerLayout);
                }
            }
        }
    }  
    QLabel * emptyLabel = new QLabel("                      ");
    QHBoxLayout * emptyLayout = new QHBoxLayout;
    emptyLayout->addWidget(emptyLabel);
    moveListInnerLayout->addLayout(emptyLayout);
    moveListScrollArea->setWidget(moveListWidget);
};


void interfaceWindow::formatArrowButton(QPushButton * thisButton)
{
    thisButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    thisButton->setMaximumWidth (arrowBorderSize);
    thisButton->setMinimumWidth (arrowBorderSize);
    thisButton->setMaximumHeight(arrowBorderSize);
    thisButton->setMinimumHeight(arrowBorderSize);
};


void interfaceWindow::addTakingMove(moveNode * tempNode, QVBoxLayout * listLayout)
{
    if(thisGameData->startingColour != tempNode->moveColour)
    {
        QHBoxLayout * takingMoveBox = new QHBoxLayout;
        QString takingMoveName = tempNode->genString();
        QLabel * takingLabel1 = new QLabel("      ");
        QLabel * takingLabel2 = new QLabel(takingMoveName);
        takingLabel2->setAlignment(Qt::AlignHCenter);

        QPalette takingPalette;
        takingPalette.setColor(QPalette::WindowText, Qt::red);
        takingLabel2->setPalette(takingPalette);

        takingMoveBox->addWidget(takingLabel1);
        takingMoveBox->addWidget(takingLabel2);
        listLayout->addLayout(takingMoveBox);
    }
    else if(thisGameData->startingColour == tempNode->moveColour)
    {
        QHBoxLayout * takingMoveBox = new QHBoxLayout;
        QString takingMoveName = tempNode->genString();
        QLabel * takingLabel1 = new QLabel(takingMoveName);
        QLabel * takingLabel2 = new QLabel("      ");
        takingLabel1->setAlignment(Qt::AlignHCenter);

        QPalette takingPalette;
        takingPalette.setColor(QPalette::WindowText, Qt::red);
        takingLabel1->setPalette(takingPalette);

        takingMoveBox->addWidget(takingLabel1);
        takingMoveBox->addWidget(takingLabel2);
        listLayout->addLayout(takingMoveBox);
    }
}

void interfaceWindow::styleMoveLabel(moveNode * tempNode, QLabel * rowLabel)
{
    if(tempNode->mlinStatus == true)
    {
        QPalette mlinPalette;
        mlinPalette.setColor(QPalette::WindowText, Qt::blue);
        rowLabel->setPalette(mlinPalette);
    }
    else if(tempNode == thisGameData->selectedMoveNode)
    {
        QPalette mlinPalette;
        mlinPalette.setColor(QPalette::Window, Qt::yellow);
        rowLabel->setPalette(mlinPalette);
        rowLabel->setAutoFillBackground(TRUE);
    }
}

void interfaceWindow::scrollBack()
{
    if(thisGameData->selectedMoveNode->lastNode->lastNode != NULL)
    {
        thisGameData->selectedMoveNode = thisGameData->selectedMoveNode->lastNode;
        setInterfaceWidgets();
    }
}

void interfaceWindow::scrollForward()
{
    if(thisGameData->selectedMoveNode->nextNode != NULL)
    {
        thisGameData->selectedMoveNode = thisGameData->selectedMoveNode->nextNode;
        setInterfaceWidgets();
    }
}

void interfaceWindow::scrollBackAll()
{
    if(thisGameData->gameMoveHead->nextNode != NULL)
    {
        thisGameData->selectedMoveNode = thisGameData->gameMoveHead->nextNode;
        setInterfaceWidgets();
    }
}

void interfaceWindow::scrollForwardAll()
{
    thisGameData->selectedMoveNode = thisGameData->currentMoveNode;
    setInterfaceWidgets();
}
