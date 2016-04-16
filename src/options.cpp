#include "options.h"

optionFunctions::optionFunctions(gameData * gameData, QApplication * thisApp)
{
    thisGameData = gameData;
    runningApp = thisApp;
}

void optionFunctions::exitApp()
{
    runningApp->quit();
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


void optionFunctions::saveGame()
{
    //std::cout << "Saving" << std::endl;
    saveDialog * saveTest = new saveDialog;
    saveTest->show();
    thisGameData->saveData.saveStatus = true;
}

saveDialog::saveDialog()
{
    QHBoxLayout * saveDialogBox = new QHBoxLayout;
    QHBoxLayout * saveDialogBox2 = new QHBoxLayout;
    QVBoxLayout * saveDialogLayout = new QVBoxLayout;
    QVBoxLayout * gameSaveList = new QVBoxLayout;
    saveDialogLayout->addLayout(gameSaveList);
    saveDialogLayout->addLayout(saveDialogBox);
    saveDialogLayout->addLayout(saveDialogBox2);

    saveLabel = new QLabel(tr("Save name: "));
    inputText = new QLineEdit;
    saveDialogBox->addWidget(saveLabel);
    saveDialogBox->addWidget(inputText);
    connect(inputText, SIGNAL(textChanged(const QString &)), this, SLOT(recordInputText(const QString &)));


    saveButton = new QPushButton(tr("Save"));
    cancelButton = new QPushButton(tr("Cancel"));
    saveDialogBox2->addWidget(cancelButton);
    saveDialogBox2->addWidget(saveButton);
    saveButton->setStatusTip(tr("Save this game"));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(createFile()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

    QLabel * testLabel = new QLabel("No files to display");
    gameSaveList->addWidget(testLabel);
    gameSaveList->addSpacing(100);
    gameSaveList->setAlignment(Qt::AlignHCenter);


    setLayout(saveDialogLayout);

}

void saveDialog::createFile()
{
    QString fileName =  "saveFiles/" + inputTextString + ".xml";
    QString fileNameRegex = "/^[a-zA-Z0-9\\-\\_@]{1,50}$/";
    // Regex-checking will go here
    QFile * outputFile = new QFile(fileName);
    if(outputFile->open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter * fileStream = new QXmlStreamWriter();
        fileStream->setDevice(outputFile);
        fileStream->writeStartDocument();
        fileStream->writeEndDocument();
        closeDialog();

    }
    else
        std::cout << "File creation error" << std::endl;

    outputFile->close();

}

void saveDialog::recordInputText(const QString input)
{

    inputTextString = input;

}

void saveDialog::closeDialog()
{

    close();
}
