#include "toolbar.h"


gameToolbar::gameToolbar(optionFunctions * optionClass)
{
    options = optionClass;
    //gameMenu = new QMenuBar(this);
    toolbarLayout = new QHBoxLayout;
    setVisible(TRUE);
    gameButton = new QMenu("Game");
    addMenu(gameButton);

    saveButton = new QAction(tr("&Save"), this);
    saveButton->setStatusTip(tr("Save this game"));
    connect(saveButton, SIGNAL(triggered()), options, SLOT(saveGame()));
    gameButton->addAction(saveButton);


    saveAsButton = new QAction(tr("Save as"), this);
    saveAsButton->setStatusTip(tr("Save this game as a new file"));
    connect(saveAsButton, SIGNAL(triggered()), options, SLOT(saveAsGame()));
    gameButton->addAction(saveAsButton);

    loadButton = new QAction(tr("Load game"), this);
    loadButton->setStatusTip(tr("Load a previously saved game"));
    connect(loadButton, SIGNAL(triggered()), options, SLOT(loadOption()));
    gameButton->addAction(loadButton);

    gameButton->addSeparator();

    restartButton = new QAction(tr("&Restart Game"), this);
    restartButton->setStatusTip(tr("Restart this game"));
    connect(restartButton, SIGNAL(triggered()), options, SLOT(restartGame()));
    gameButton->addAction(restartButton);

    saveAndExitButton = new QAction(tr("&Save and Exit"), this);
    saveAndExitButton->setStatusTip(tr("Save this game and close the app"));
    connect(saveAndExitButton, SIGNAL(triggered()), options, SLOT(saveAndExit()));
    gameButton->addAction(saveAndExitButton);

    gameButton->addSeparator();

    returnButton = new QAction(tr("&Return to menu"), this);
    returnButton->setStatusTip(tr("Return to the main menu"));
    //connect(returnButton, SIGNAL(triggered()), options, SLOT(returnToMenu()));
    gameButton->addAction(returnButton);

    exitButton = new QAction(tr("&Exit"), this);
    exitButton->setStatusTip(tr("Close this application"));
    connect(exitButton, SIGNAL(triggered()), options, SLOT(exitApp()));
    gameButton->addAction(exitButton);

    optionButton = new QMenu("Settings");
    addMenu(optionButton);

    languageButton = new QAction(tr("&Language"), this);
    languageButton->setStatusTip(tr("Change the language settings"));
    optionButton->addAction(languageButton);
}

gameToolbar::~gameToolbar()
{

}

