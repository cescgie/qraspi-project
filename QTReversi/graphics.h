#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include "glview.h"
#include "infoview.h"
#include <QtWidgets>
#include "playersetting.h"
#include "listmoves.h"

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
    void fullScreen();
    void showGlNormal();
private:
     void initComponent();
     void createActions();
     void createMenus();
     void createStatusBar();
     void createToolBars();
     void soundConfiguration();

     void connecting( game * );

     QWidget *centralWindow;
     glView *scene;
     InfoView *infos;
     ListMoves *list_moves;

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

     //sound
     QSoundEffect effectStart;
     QSoundEffect effectEnd;
     QSoundEffect effectBounce;
     QSoundEffect effectPrev;
     QSoundEffect effectNext;

     QAction *fullScreenAction;

signals:
    void startNewGame();
    void undoMoveAsked();
    void redoMoveAsked();
};

#endif // GRAPHICS_H
