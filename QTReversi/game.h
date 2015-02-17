#ifndef _GAME_H
#define _GAME_H

#include <iostream>
using namespace std;

#include <QObject>
#include <vector>
#include "board.h"
#include "player.h"
#include "imove.h"
#include "infosmoves.h"
#include <QSoundEffect>

class game : public QObject
{
        Q_OBJECT

    private:
        //Spielbrett
        Board* board;
        //2 Spieler im Spiel
        Player* playerTable[2];
        //Liste der Bewegungen der Steine
        vector<imove> movesList;
        //Temporäre Liste, um die legalen Züge speichern
        vector<imove> regularMovesListTemp;
        //Spieler, der gespielt hat
        int currentPlayer;
        //Spiel abgeschlossen?
        bool isFinished;
        //Aktuelle Anzahl der gültigen Züge
        int numCurrentMove;
        //Sichern der Zuege in Liste
        vector<infosMoves> movesSavedList;
        //Anzeige der Aktion Redo/Undo
        bool redoAllowed;
        bool undoAllowed;
        //sounds. Setzt ( QT += core gui multimedia ) in pro-Datei ein.
        QSoundEffect effectWhite;
        QSoundEffect effectBlack;

    public:
        //Konstruktor
        game();
        //Destruktor
        ~game();
        //startet das Spiel
        void startGame();
        //Zugriffsvariable 'Brett'
        Board* getBoard();
        //Zugriffsvariable 'Spieler'
        Player* getPlayer(int);
        Player** getPlayer();
        //Zugriffsvariable 'movesList'
        vector<imove> getMovesList();
        //Zugriffsvariable 'regularMovesListTemp'
        vector<imove> getRegularMovesListTemp();
        //Zugriffsvariable 'currentPlayer'
        int getCurrentPlayer();
        //Initialisiert die Anzeige
        void initializationDisplay();
        vector<infosMoves> getMovesSavedList();
        int getNumCurrentMove();
        std::string toString();
        void fromString(const std::string str);

    public slots:
        //Initilisiert die Spielrunde
        void initialization();
        //Wiederherstellung des Zuges
        void recupMove(int,int);
        //Startet den nächsten Zug, wenn die Partie nicht vorbei ist
        void nextTurn();
        void undoMoveGlobal();
        void redoMoveGlobal();
        //Anfordern eines Zuges
        void askMove();

    private:
        //Bool 'isFinished'
        void setIsFinished(bool);
        //Zugriffsvariable 'isFinished'
        bool getIsFinished();
        //Spielerwechsel
        void nextPlayer();
        //ein Zug im Spiel
        bool playMove(imove);
        //definiert regelgemäße Züge
        void definingRegularMoves();
        //aktualisiert die gueltigen Zuege 'regularMovesList'
        void updateRegularMove();
        //Erhöht die Anzahl der legalen Zuege der Spieler je nach Farbe
        void increaseRegularMove(ColorPawn);
        //Einen legalen Zug nach mehreren Parametern ueberprüfen...
        bool checkRegularMove( int, int, int, int);
        //dreht ein Stein
        void turnDownPawn(int,int);
        //Fuegt den Zug in die Liste
        void addMoveList(imove);
        //Loescht die Liste der gespielten Züge
        void clearMovesList();
        //Aktualisiert die Punkte der Spieler nach der Löschung eines Steines
        void updateScore();
        //Update Spieldaten nach dem Spiel eines Zuges: Reversi Stein, Reversi Punkte
        bool updateGame(imove);
        //Aktualisiert eine Reihe der Steine
        void updateRow(imove);
        //Aktualisiert eine Spalte der Steine
        void updateColumn(imove);
        //Aktualisiert Steine diagonal
        void updateDiagonal(imove);
        //Informationen über den Sieger
        void whoWins();
        //Verwaltung der Anzeige
        void updatingScoreDisplay();
        void updatingNumMovesDisplay();
        void updatingMovesListDisplay();
        void playerInitializationDisplay();
        void boardHasModified();
        //Speichermanagement von Zügen
        //Initialisiert
        void initializationSavingMove();
        //speichert abgelehnte Zuege
        void savePawnTurnedDown(int,int);
        //speichert gueltige Zuege in die Liste
        void saveRegularMoves();
        //Speichert den aktuellen Spieler
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

#endif

