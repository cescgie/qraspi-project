#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <QMainWindow>
#include "glview.h"
#include "infoview.h"
#include "game.h"
#include "playersetting.h"
#include "QSoundEffect"
#include "listmoves.h"
#include "highscore.h"
#include <QtGui>
#include <QPrinter>
#include <QPrintDialog>
#include <QTableView>
#include <QPixmap>
#include <QTextDocument>
#include <QSqlQueryModel>

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
        bool saveGame();
        bool saveFile();
        void loadGame();
        bool maybeSave();
        void choose_pic();
        void preferences();
        void undoMove();
        void redoMove();
        void fullScreen();
        void showGlNormal();
        void displayWinner(Player*);
        void updateSettingRegularMoves();
        void updateSettingLastMove();
        void updateSettingAnimation();
        void updateSettingVolume();
        void setDisplayUndoMoveAction(bool);
        void setDisplayRedoMoveAction(bool);
        void onButtonHelpPressed();
        void onButtonAboutPressed();
        void refreshHighScore();
        void cleanHighScore();
        void printHighScore();
        void deleteHighscores();

    private:
        void initComponent();
        void HighscoreView();
        void soundsConfiguration();
        void createActions();
        void createMenus();
        void createToolBars();
        void createStatusBar();
        void connecting( game * );
        QDialog *helpDialog;
        QDialog *aboutDialog;
        void writeSettings();
        void readSettings();
        QWidget *centralWindow;
        glView *scene;
        infoView *infos;
        game *savlo;
        ListMoves *list_moves;
        QLabel *statusBarLabel;
        QMenu *fileMenu;
        QMenu *viewMenu;
        QMenu *toolsMenu;
        QMenu *helpMenu;
        QToolBar *fileToolBar;
        QToolBar *toolsToolBar;

//Aktionsmenues "Datei"
        QAction *newAction;
        QAction *saveAction;
        QAction *loadAction;
        QAction *exitAction;

//Aktionsmenues "Ansicht"
        QAction *regularMovesAction;
        QAction *lastMoveAction;
        QAction *animationAction;
        QAction *volumeAction;

//Aktionsmenues "Werkzeuge"
        QAction *undoMoveAction;
        QAction *redoMoveAction;
        QAction *preferencesAction;
        QAction *loadBoard;
        QAction *fullScreenAction;

//Aktionsmenues "Hilfe"
        QAction *aboutAction;
        QAction *helpAction;
        //board background
        QPixmap image;
        QImage  *imageObject;
        //sound
        QSoundEffect effectStart;
        QSoundEffect effectEnd;
        QSoundEffect effectBounce;
        QSoundEffect effectPrev;
        QSoundEffect effectNext;
        Highscore _highscore;
        QPushButton *buttonPrint;
        QPushButton *buttonRefreshHS;
        QPushButton *buttonClearHS;
        QVBoxLayout *verticalLayout;
        QVBoxLayout *verticallayout2;
        QVBoxLayout *topverticalLayout;
        QHBoxLayout *horizontalLayout;
        QHBoxLayout *buttonLayout;
        QLabel *highscoresLabel;
        QAction *printAction;
        QAction *RefreshHSAction;
        QAction *ClearHSAction;
        QAction *HSAction;
        QGridLayout *gridLayout;
        QTableView *tableViewHighscores;
        QGroupBox *groupBoxHighscores;
        void createHighscore(QString, int);

        signals:
                void startNewGame();
                void undoMoveAsked();
                void redoMoveAsked();
};

#endif
