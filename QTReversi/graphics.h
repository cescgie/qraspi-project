#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include "glview.h"
#include "infoview.h"
#include <QtWidgets>
#include "preferencesdialog.h"

class game;
class Player;
class QAction;
class QLabel;
class QWidget;

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
    void preferences();
    void displayWinner(Player*);
    void updateSettingAnimation();
    void updateSettingRegularMoves();
    void updateSettingLastMove();
    void undoMove();
    void redoMove();
    void setDisplayUndoMoveAction(bool);
    void setDisplayRedoMoveAction(bool);

private:
     void createActions();
     void createMenus();
     void createStatusBar();
     void createToolBars();

     void connecting( game * );

     QWidget *centralWindow;
     glView *scene;
     InfoView *infos;

      QLabel *statusBarLabel;

     QMenu *fileMenu;
     QMenu *viewMenu;

     QToolBar *fileToolBar;
     QToolBar *toolsToolBar;

     QAction *newAction;
     QAction *exitAction;

     QAction *animationAction;
     QAction *preferencesAction;
     QAction *regularMovesAction;
     QAction *lastMoveAction;
     QAction *undoMoveAction;
     QAction *redoMoveAction;

signals:
    void startNewGame();
    void undoMoveAsked();
    void redoMoveAsked();
};

#endif // GRAPHICS_H
