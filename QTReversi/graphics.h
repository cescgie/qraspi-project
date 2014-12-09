#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include "glview.h"
#include <QtWidgets>

class game;
class Player;
class QAction;
class QLabel;
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTextEdit;
class QSizePolicy;

#include <iostream>
#include <cstring>
using namespace std;

class graphics : public QMainWindow
{
    Q_OBJECT

public:
    graphics();
    ~graphics();
    void initialization( game * );


protected:
        void closeEvent(QCloseEvent *event);

private slots:
    void newGame();
    void displayWinner(Player*);
    void updateSettingAnimation();

private:
     void createActions();
     void createMenus();
     void createStatusBar();

     void connecting( game * );

     QWidget *centralWindow;
     glView *scene;

      QLabel *statusBarLabel;

     QMenu *fileMenu;
     QMenu *viewMenu;

     QAction *newAction;
     QAction *exitAction;

     QAction *animationAction;

signals:
    void startNewGame();

};

#endif // GRAPHICS_H
