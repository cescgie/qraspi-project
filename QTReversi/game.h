#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

#include <QObject>
#include <vector>
#include "board.h"
#include "player.h"
#include "moves.h"
#include "infosmoves.h"
#include <QSoundEffect>

class game : public QObject
    {
        Q_OBJECT

private:

    Board* board;

    Player* playerTable[2];

    vector<moves> movesList;

    vector<moves> regularMovesListTemp;

    int currentPlayer;

    bool isFinished;

    int numCurrentMove;

    vector<InfosMoves> movesSavedList;

    bool redoAllowed;
    bool undoAllowed;

    //sounds. Setzt ( QT += core gui multimedia ) in pro-Datei ein.
    QSoundEffect effectP1;
    QSoundEffect effectP2;

    void initStartBoard();
    void soundsConfiguration();

public:
    game();
    ~game();

    void startGame();

    Board* getBoard();

    Player* getPlayer(int);

    Player** getPlayer();

    vector<moves> getMovesList();

    vector<moves> getRegularMovesListTemp();

    int getCurrentPlayer();

    void initializationDisplay();

    vector<InfosMoves> getMovesSavedList();
    int getNumCurrentMove();

public slots:

    void initialization();

    void recupMove(int,int);

    void nextTurn();

    void undoMoveGlobal();
    void redoMoveGlobal();

private:

    void setIsFinished(bool);
    bool getIsFinished();

    void nextPlayer();

    bool playMove(moves);

    void definingRegularMoves();
    void updateRegularMove();
    void increaseRegularMove(ColorPawn);
    bool checkRegularMove( int, int, int, int);

    void turnDownPawn(int,int);

    void addMoveList(moves);
    void clearMovesList();

    void updateScore();

    bool updateGame(moves);
    void updateRow(moves);
    void updateColumn(moves);
    void updateDiagonal(moves);

    void askMove();

    void whoWins();

    void updatingScoreDisplay();
    void updatingNumMovesDisplay();
    void updatingMovesListDisplay();
    void playerInitializationDisplay();

    void boardHasModified();

    void initializationSavingMove();
    void savePawnTurnedDown(int,int);
    void saveRegularMoves();
    void saveCurrentPlayer();

    void undoLastMove();
    void redoLastMove();

    void affichageSavedList();
    void affichageMovesList();

signals:

    void boardModified();

    void playerScoreModified();
    void playerNumMovesModified();
    void playerNameModified(Player*);
    void playerColorModified(Player*);
    void playerTypeModified(Player*);
    void movesListModified(QString);

    void sendInfosGameDisplay(IdMsgInfos);

    void askingLocalMove();
    void askingAIMove(game*);

    void playerWins( Player* );

    void enableUndoMoveAction(bool);
    void enableRedoMoveAction(bool);
};

#endif // GAME_H
