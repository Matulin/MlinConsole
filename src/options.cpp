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


void optionFunctions::testFunction()
{
    std::cout << "Test" << std::endl;
}
