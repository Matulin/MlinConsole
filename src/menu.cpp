#include "menu.h"

mainMenu::mainMenu(MainWindow * givenWindow)
{
    parentWindow = givenWindow;
    newGame = new QPushButton("New Game");
    loadGame = new QPushButton("Load Game");
    howToPlay = new QPushButton("How to Play");
    settings = new QPushButton("Settings");
    exitButton = new QPushButton("Exit");
    connect(newGame, SIGNAL(clicked()), parentWindow, SLOT(startGame()));
    connect(loadGame, SIGNAL(clicked()), parentWindow, SLOT(loadGame()));
    connect(exitButton, SIGNAL(clicked()), parentWindow, SLOT(exitApp()));

    addWidget(newGame);
    addWidget(loadGame);
    addWidget(howToPlay);
    addWidget(settings);
    addWidget(exitButton);

}

mainMenu::~mainMenu()
{

}

void mainMenu::deleteMainMenu()
{
    delete newGame;
    delete loadGame;
    delete howToPlay;
    delete settings;
    delete exitButton;
    delete this;
}
