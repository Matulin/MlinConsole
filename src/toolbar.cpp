#include "toolbar.h"


gameToolbar::gameToolbar(optionFunctions * optionClass)
{
    options = optionClass;
    gameMenu = new QMenuBar(this);
    toolbarLayout = new QHBoxLayout;
    toolbarLayout->addWidget(gameMenu);

    gameButton = new QMenu("Game");
    gameMenu->addMenu(gameButton);

    saveButton = new QAction(tr("&Save"), this);
    saveButton->setStatusTip(tr("Save this game"));
    gameButton->addAction(saveButton);


    saveAsButton = new QAction(tr("&Save as"), this);
    saveAsButton->setStatusTip(tr("Save this game as a new file"));
    gameButton->addAction(saveAsButton);

    gameButton->addSeparator();

    restartButton = new QAction(tr("&Restart Game"), this);
    restartButton->setStatusTip(tr("Restart this game"));
    connect(restartButton, SIGNAL(triggered()), options, SLOT(restartGame()));
    gameButton->addAction(restartButton);

    saveAndExitButton = new QAction(tr("&Save and Exit"), this);
    saveAndExitButton->setStatusTip(tr("Save this game and close the app"));
    gameButton->addAction(saveAndExitButton);

    gameButton->addSeparator();

    exitButton = new QAction(tr("&Exit"), this);
    exitButton->setStatusTip(tr("Close this application"));
    connect(exitButton, SIGNAL(triggered()), options, SLOT(exitApp()));
    //options->testFunction();
    gameButton->addAction(exitButton);



    optionButton = new QMenu("Options");
    gameMenu->addMenu(optionButton);

    languageButton = new QAction(tr("&Language"), this);
    languageButton->setStatusTip(tr("Change the language settings"));
    optionButton->addAction(languageButton);

}

gameToolbar::~gameToolbar()
{

}

