#include "menu.h"

mainMenu::mainMenu(MainWindow * givenWindow)
{
    parentWindow = givenWindow;
    newGame = new QPushButton("New Game");
    loadGame = new QPushButton("Load Game");
    howToPlay = new QPushButton("How to Play");
    settings = new QPushButton("Settings");
    exitButton = new QPushButton("Exit Button");
    connect(newGame, SIGNAL(clicked()), parentWindow, SLOT(startGame()));

    addWidget(newGame);
    addWidget(loadGame);
    addWidget(howToPlay);
    addWidget(settings);
    addWidget(exitButton);

}

mainMenu::~mainMenu()
{

}

