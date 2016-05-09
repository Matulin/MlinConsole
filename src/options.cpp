#include "options.h"

optionFunctions::optionFunctions(gameData * gameData)
{
    thisGameData = gameData;
}

void optionFunctions::exitApp()
{
    QApplication::quit();
}

void optionFunctions::restartGame()
{

    gameData * newGameData = new gameData(thisGameData->outerWindow, true);
    for(unsigned int count = 0; count < numOfLayers; count++)
    {
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
            {
                if(thisGameData->board[count][count2][count3].colour != invalidToken)
                {
                    newGameData->board[count][count2][count3].locImg = thisGameData->board[count][count2][count3].locImg;
                    newGameData->board[count][count2][count3].locImg->setPixmap(*newGameData->board[count][count2][count3].locImg->defaultImg);
                }
            }
        }
    }
    thisGameData->~gameData();
    *thisGameData = *newGameData;

    thisGameData->outerWindow->setInterfaceWidgets();
}
void optionFunctions::loadOption()
{
    saveDialog * loadWindow = new saveDialog(thisGameData, true);

    loadWindow->show();
}


void optionFunctions::saveGame(bool exit)
{
    if((thisGameData->saveData.saveStatus == false) || (exit == true))
    {
        if(thisGameData->saveData.saveName == "")
            if(exit == true)
                saveAsGame(true);
            else
                saveAsGame();
        else
        {
            if(exit == false)
            {
                saveDialog * saveWindow = new saveDialog(thisGameData, false, false);
                saveWindow->createFile();
                thisGameData->saveData.saveStatus = true;
            }
            else
            {
                saveDialog * saveWindow = new saveDialog(thisGameData, false, false, true);
                saveWindow->createFile();
            }
        }
    }
}

void optionFunctions::saveAsGame(bool exit)
{

    saveDialog * saveWindow;
    if(exit == false)
        saveWindow = new saveDialog(thisGameData);
    else
        saveWindow = new saveDialog(thisGameData, false, true, true);
    saveWindow->show();


}

void optionFunctions::saveAndExit()
{
    saveGame(true);
    //exitApp();
}


saveDialog::saveDialog(gameData * gameData, bool loadBool, bool saveAs, bool exit)
{
    thisGameData = gameData;
    exitBool = exit;
    if(saveAs == true)
    {
        QHBoxLayout * saveDialogBox = new QHBoxLayout;
        QHBoxLayout * saveDialogBox2 = new QHBoxLayout;
        QVBoxLayout * saveDialogLayout = new QVBoxLayout;
        gameSaveList = new QVBoxLayout;
        saveDialogLayout->addLayout(gameSaveList);
        saveDialogLayout->addLayout(saveDialogBox);
        saveDialogLayout->addLayout(saveDialogBox2);
        exitBool = exit;

        if(loadBool == false)
            saveLabel = new QLabel(tr("Save name: "));
        else if (loadBool == true)
            saveLabel = new QLabel(tr("File name: "));
        inputText = new QLineEdit;
        saveDialogBox->addWidget(saveLabel);
        saveDialogBox->addWidget(inputText);
        connect(inputText, SIGNAL(textChanged(const QString &)), this, SLOT(recordInputText(const QString &)));

        if(loadBool == false)
            saveButton = new QPushButton(tr("Save"));
         else if (loadBool == true)
            saveButton = new QPushButton(tr("Load"));
        cancelButton = new QPushButton(tr("Cancel"));
        saveDialogBox2->addWidget(cancelButton);
        saveDialogBox2->addWidget(saveButton);
        saveButton->setStatusTip(tr("Save this game"));
        if(loadBool == false)
        {
             connect(saveButton, SIGNAL(clicked()), this, SLOT(createFile()));
        }
        else if(loadBool == true)
            connect(saveButton, SIGNAL(clicked()), this, SLOT(loadFile()));

        connect(cancelButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

        displayFileList();

        setLayout(saveDialogLayout);
    }
    else
    {
        inputTextString = thisGameData->saveData.saveName;
    }
}

void saveDialog::createFile()
{

    QRegularExpression fileNameRegex("^[a-zA-Z0-9\\-\\_@]{1,50}$");
    if(!(fileNameRegex.match(inputTextString).hasMatch()))
    {
        std::cout << "File name doesn't match regex" << std::endl;
        std::cout << inputTextString.toStdString() << std::endl;
        return;
    }
    QString fileName =  "saveFiles/" + inputTextString + ".xml";
    QFile * outputFile = new QFile(fileName);
    if(outputFile->open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter * fileStream = new QXmlStreamWriter();
        fileStream->setDevice(outputFile);
        fileStream->writeStartDocument();
        fileStream->writeStartElement("gameData");
            fileStream->writeTextElement("gameStatus", QString::number(thisGameData->gameStatus));
            fileStream->writeTextElement("currentTurn", QString::number(thisGameData->currentTurn));
            fileStream->writeTextElement("blackPiecesTaken", QString::number(thisGameData->blackPieces.piecesTaken));
            fileStream->writeTextElement("blackPiecesUnplaced", QString::number(thisGameData->blackPieces.piecesUnplaced));
            fileStream->writeTextElement("blackPiecesOnBoard", QString::number(thisGameData->blackPieces.piecesOnBoard));
            fileStream->writeTextElement("whitePiecesTaken", QString::number(thisGameData->whitePieces.piecesTaken));
            fileStream->writeTextElement("whitePiecesUnplaced", QString::number(thisGameData->whitePieces.piecesUnplaced));
            fileStream->writeTextElement("whitePiecesOnBoard", QString::number(thisGameData->whitePieces.piecesOnBoard));

            for(unsigned int count = 0; count < numOfLayers; count++)
            {
                for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
                {
                    for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
                    {
                        if(thisGameData->board[count][count2][count3].colour != invalidToken)
                        {
                            fileStream->writeStartElement("position");
                                fileStream->writeTextElement("layerNum", QString::number(thisGameData->board[count][count2][count3].arrayLayNum));
                                fileStream->writeTextElement("xCoord", QString::number(thisGameData->board[count][count2][count3].arrayXCoord));
                                fileStream->writeTextElement("yCoord", QString::number(thisGameData->board[count][count2][count3].arrayYCoord));
                                fileStream->writeTextElement("colour", QString::number(thisGameData->board[count][count2][count3].colour));
                                fileStream->writeTextElement("mlinStatus", QString::number(thisGameData->board[count][count2][count3].mlinStatus));
                            fileStream->writeEndElement();
                        }
                    }
                }
            }
        fileStream->writeEndElement();

        thisGameData->saveData.saveStatus = true;
        thisGameData->saveData.saveName = inputTextString;

    }
    else
        std::cout << "File creation error" << std::endl;

    outputFile->close();
    closeDialog();

    recordSave(inputTextString);
    if(exitBool == true)
    {
        std::cout << "Test1" << std::endl;
        QApplication::quit();
    }
}

void saveDialog::loadFile()
{
    QString fileName =  "saveFiles/" + inputTextString + ".xml";
    QFile * readFile = new QFile(fileName);
    status newGameStatus;
    posColour currentTurn;
    int blackPiecesTaken;
    int blackPiecesUnplaced;
    int blackPiecesOnBoard;
    int whitePiecesTaken;
    int whitePiecesUnplaced;
    int whitePiecesOnBoard;

    if(readFile->open(QIODevice::ReadOnly))
    {
        //optionFunctions::restartGame();
        QXmlStreamReader * fileStream = new QXmlStreamReader();
        fileStream->setDevice(readFile);
        if(fileStream->readNextStartElement())
        {
            if(fileStream->name() == "gameData")
            {
                    if(fileStream->readNextStartElement() && (fileStream->name() == "gameStatus"))
                    {
                        newGameStatus = (status)(fileStream->readElementText().toInt());
                    }
                    else
                        std::cout << "Error1" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "currentTurn"))
                    {
                        currentTurn = (posColour)(fileStream->readElementText().toInt());
                    }
                    else
                        std::cout << "Error2" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "blackPiecesTaken"))
                    {
                        blackPiecesTaken = fileStream->readElementText().toInt();
                    }
                    else
                        std::cout << "Error3" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "blackPiecesUnplaced"))
                    {
                        blackPiecesUnplaced = fileStream->readElementText().toInt();
                    }
                    else
                        std::cout << "Error4" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "blackPiecesOnBoard"))
                    {
                        blackPiecesOnBoard = fileStream->readElementText().toInt();
                    }
                    else
                        std::cout << "Error5" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "whitePiecesTaken"))
                    {
                        whitePiecesTaken = fileStream->readElementText().toInt();
                    }
                    else
                        std::cout << "Error6" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "whitePiecesUnplaced"))
                    {
                        whitePiecesUnplaced = fileStream->readElementText().toInt();
                    }
                    else
                        std::cout << "Error7" << std::endl;
                    if(fileStream->readNextStartElement() && (fileStream->name() == "whitePiecesOnBoard"))
                    {
                        whitePiecesOnBoard = fileStream->readElementText().toInt();
                    }
                    else
                        std::cout << "Error8" << std::endl;
                }

        }

        gameData * newGameData = new gameData(thisGameData->outerWindow, true);
        newGameData->blackPieces.piecesOnBoard = blackPiecesOnBoard;
        newGameData->blackPieces.piecesUnplaced = blackPiecesUnplaced;
        newGameData->blackPieces.piecesTaken = blackPiecesTaken;
        newGameData->whitePieces.piecesOnBoard = whitePiecesOnBoard;
        newGameData->whitePieces.piecesUnplaced = whitePiecesUnplaced;
        newGameData->whitePieces.piecesTaken = whitePiecesTaken;
        newGameData->currentTurn = currentTurn;
        newGameData->gameStatus = newGameStatus;



        while(fileStream->readNextStartElement() && (fileStream->name() == "position"))
        {
            unsigned int layNum;
            unsigned int xCoord;
            unsigned int yCoord;
            enum posColour colour;
            unsigned int mlinStatus;
            if(fileStream->readNextStartElement() && (fileStream->name() == "layerNum"))
            {
               layNum = fileStream->readElementText().toInt();
            }
            if(fileStream->readNextStartElement() && (fileStream->name() == "xCoord"))
            {
                xCoord = fileStream->readElementText().toInt();
            }
            if(fileStream->readNextStartElement() && (fileStream->name() == "yCoord"))
            {
                yCoord = fileStream->readElementText().toInt();
            }
            if(fileStream->readNextStartElement() && (fileStream->name() == "colour"))
            {
                colour = (posColour)(fileStream->readElementText().toInt());
            }
            if(fileStream->readNextStartElement() && (fileStream->name() == "mlinStatus"))
            {
                mlinStatus = fileStream->readElementText().toInt();
            }
            newGameData->board[layNum][xCoord][yCoord].locImg = thisGameData->board[layNum][xCoord][yCoord].locImg;
            newGameData->board[layNum][xCoord][yCoord].colour = colour;
            newGameData->board[layNum][xCoord][yCoord].mlinStatus = mlinStatus;
            if(newGameData->board[layNum][xCoord][yCoord].colour == noToken)
                newGameData->board[layNum][xCoord][yCoord].locImg->setPixmap(*newGameData->board[layNum][xCoord][yCoord].locImg->defaultImg);
            else if((newGameData->board[layNum][xCoord][yCoord].colour == blackToken) && (newGameData->board[layNum][xCoord][yCoord].mlinStatus == 0))
                newGameData->board[layNum][xCoord][yCoord].locImg->setPixmap(*newGameData->tokenImage.blackTokenMap);
            else if((newGameData->board[layNum][xCoord][yCoord].colour == blackToken) && (newGameData->board[layNum][xCoord][yCoord].mlinStatus > 0))
                newGameData->board[layNum][xCoord][yCoord].locImg->setPixmap(*newGameData->tokenImage.blackTokenMlinMap);
            else if((newGameData->board[layNum][xCoord][yCoord].colour == whiteToken) && (newGameData->board[layNum][xCoord][yCoord].mlinStatus == 0))
                newGameData->board[layNum][xCoord][yCoord].locImg->setPixmap(*newGameData->tokenImage.whiteTokenMap);
            else if((newGameData->board[layNum][xCoord][yCoord].colour == whiteToken) && (newGameData->board[layNum][xCoord][yCoord].mlinStatus > 0))
                newGameData->board[layNum][xCoord][yCoord].locImg->setPixmap(*newGameData->tokenImage.whiteTokenMlinMap);

            fileStream->skipCurrentElement();
        }
        newGameData->saveData.saveStatus = true;
        newGameData->saveData.saveName = inputTextString;
        thisGameData->~gameData();
        *thisGameData = *newGameData;
        thisGameData->outerWindow->setInterfaceWidgets();

        closeDialog();
    }
}

void saveDialog::recordInputText(const QString input)
{
    inputTextString = input;
    for(saveFileLabel * labelPt : fileLabelVector)
    {
        if(labelPt->fileName != inputTextString)
        {
            labelPt->deselectLabel();
        }
        else
            labelPt->selectLabel();
    }

}

void saveDialog::closeDialog()
{

    close();
}

bool saveDialog::recordSave(QString fileName)
{
    QFile * saveFileListStream = new QFile("appData/saveFileList.xml");

    if(saveFileListStream->open(QIODevice::ReadWrite))
    {
        QXmlStreamReader * fileReadStream = new QXmlStreamReader();
        fileReadStream->setDevice(saveFileListStream);

        if(fileReadStream->readNextStartElement() && (fileReadStream->name() == "fileList"))
        {
            std::vector<QString> fileListVector;
            while(fileReadStream->readNextStartElement() && (fileReadStream->name() == "file"))
            {
                    QString readFileName = fileReadStream->readElementText();
                    if(readFileName == fileName)
                    {
                        saveFileListStream->close();
                        fileReadStream->~QXmlStreamReader();
                        return true;
                    }
                    else
                    {
                        fileListVector.push_back(readFileName);

                    }
            }
            fileReadStream->~QXmlStreamReader();
            saveFileListStream->seek(0);
            QXmlStreamWriter * fileWriteStream = new QXmlStreamWriter();
            fileWriteStream->setDevice(saveFileListStream);
            fileWriteStream->writeStartDocument();
            fileWriteStream->writeStartElement("fileList");
                if(fileListVector.size() > 0)
                {
                    for(QString readName : fileListVector)
                    {
                            fileWriteStream->writeTextElement("file", readName);
                    }
                }
                    fileWriteStream->writeTextElement("file", fileName);
            fileWriteStream->writeEndElement();
            fileWriteStream->writeEndDocument();
            saveFileListStream->close();
        }
        else
            return false;
    }
    else
        return false;
    return false;

}

void saveDialog::displayFileList()
{

    QFile * saveFileListStream = new QFile("appData/saveFileList.xml");
    std::vector<QString> fileListVector;
    if(saveFileListStream->open(QIODevice::ReadWrite))
    {
        QXmlStreamReader * fileReadStream = new QXmlStreamReader();
        fileReadStream->setDevice(saveFileListStream);

        if(fileReadStream->readNextStartElement() && (fileReadStream->name() == "fileList"))
        {

            while(fileReadStream->readNextStartElement() && (fileReadStream->name() == "file"))
            {
                    QString readFileName = fileReadStream->readElementText();
                    fileListVector.push_back(readFileName);
            }
        }
    }
    if(fileListVector.size() < 1)
    {
        QLabel * testLabel = new QLabel("No saved games");
        gameSaveList->addWidget(testLabel);
        gameSaveList->addSpacing(40);
    }
    else
    {
        fileLabelVector.clear();
        for(QString readName : fileListVector)
        {
            saveFileLabel * tempLabel = new saveFileLabel(readName);
            gameSaveList->addWidget(tempLabel);
            fileLabelVector.push_back(tempLabel);
            connect(tempLabel, SIGNAL(clicked(QString)), inputText, SLOT(setText(QString)));
        }
        for(saveFileLabel * labelPt : fileLabelVector)
        {
            labelPt->addVector(fileLabelVector);
        }
    }

    gameSaveList->setContentsMargins(0,0,0,0);
    gameSaveList->setAlignment(Qt::AlignHCenter);
}

saveFileLabel::saveFileLabel(QString givenFileName)
{
    fileName = givenFileName;
    setText(fileName);
    setAlignment(Qt::AlignCenter);

}

void saveFileLabel::addVector(std::vector<saveFileLabel *> givenVector)
{
    fileLabelVector = givenVector;
}

void saveFileLabel::mousePressEvent(QMouseEvent *)
{
    for(saveFileLabel * labelPt : fileLabelVector)
    {
        std::cout << labelPt->fileName.toStdString() << std::endl;
        if(labelPt != this)
        {
            labelPt->deselectLabel();
        }
    }
    emit clicked(fileName);
}

saveFileLabel::~saveFileLabel()
{

}

void saveFileLabel::deselectLabel()
{
    setText("<font color=\"Black\">" + fileName + "</font>");
    setStyleSheet("");
}

void saveFileLabel::selectLabel()
{
    setText("<font color=\"Goldenrod\">" + fileName + "</font>");
    setStyleSheet("QLabel { background-color : blue; }");
}
