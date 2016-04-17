#ifndef OPTIONS_H
#define OPTIONS_H


#include <QApplication>
#include <QtGui>
#include <QDialog>
#include <board.h>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QRegularExpression>
#include <QString>


class QApplication;
class gameData;

class optionFunctions : public QWidget
{
   Q_OBJECT
public:
    explicit optionFunctions(gameData * gameData, QApplication * thisApp);
public:
    QApplication * runningApp;
    gameData * thisGameData;

public slots:
    void exitApp();
    void restartGame();
    void saveGame(bool exit = false);
    void saveAsGame(bool exit = false);
    void loadOption();
    void saveAndExit();
};

class saveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveDialog(gameData * gameData, bool loadBool = false, bool saveAs = true, bool exit = false);

public:
    QPushButton * saveButton;
    QPushButton * cancelButton;
    QLabel * saveLabel;
    QLineEdit * inputText;
    QString inputTextString;
    gameData * thisGameData;
    bool exitBool;

public slots:
    void createFile();
    void loadFile();
    void recordInputText(const QString input);
    void closeDialog();

};

#endif // OPTIONS_H
