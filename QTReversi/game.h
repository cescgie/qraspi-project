#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

#include <QObject>
#include <vector>
#include "board.h"
#include "player.h"
#include "move.h"
#include "infosmoves.h"
#include <QSoundEffect>

class game : public QObject
    {
        Q_OBJECT

private:

    Board* board;

    Player* playerTable[2];

    vector<move> movesList;

    vector<move> regularMovesListTemp;

    int currentPlayer;

    bool isFinished;

    int numCurrentMove;

    vector<InfosMoves> movesSavedList;

    bool redoAllowed;
    bool undoAllowed;

    //sounds. Setzt ( QT += core gui multimedia ) in pro-Datei ein.
    QSoundEffect effectP1;
    QSoundEffect effectP2;

public:
    game();
    ~game();

    void startGame();

    Board* getBoard();

    Player* getPlayer(int);

    Player** getPlayer();

    vector<move> getMovesList();

    vector<move> getRegularMovesListTemp();

    int getCurrentPlayer();

    void initializationDisplay();

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

    bool playMove(move);

    void definingRegularMoves();
    void updateRegularMove();
    void increaseRegularMove(ColorPawn);
    bool checkRegularMove( int, int, int, int);

    void turnDownPawn(int,int);

    void addMoveList(move);
    void clearMovesList();

    void updateScore();

    bool updateGame(move);
    void updateRow(move);
    void updateColumn(move);
    void updateDiagonal(move);

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
