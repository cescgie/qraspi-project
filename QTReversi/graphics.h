#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include "glview.h"
#include "infoview.h"
#include <QtWidgets>
#include "playersetting.h"
#include "listmoves.h"
#include "highscore.h"
#include <QtGui>
#include <QTableView>
#include <QPixmap>
#include <QTextDocument>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>

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

    QSqlQueryModel* getHighscores();
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

    void refreshHighScore();
    void printHighScore();
    void cleanHighScore();
    void deleteHighscores();
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
     QMenu *toolsMenu;

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

     void HighscoreView();

     Highscore _highscore;
     QVBoxLayout *verticalLayout;
     QVBoxLayout *verticallayout2;
     QVBoxLayout *topverticalLayout;
     QHBoxLayout *horizontalLayout;
     QLabel *highscoresLabel;
     QAction *printAction;
     QAction *RefreshHSAction;
     QAction *ClearHSAction;
     QAction *HSAction;
     QPushButton *buttonPrint;
     QHBoxLayout *buttonLayout;

     QGridLayout *gridLayout;
     QTableView *tableViewHighscores;
     QGroupBox *groupBoxHighscores;

     void createHighscore(QString, int);
signals:
    void startNewGame();
    void undoMoveAsked();
    void redoMoveAsked();
};

#endif // GRAPHICS_H
