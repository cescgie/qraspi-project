#ifndef _AI_H
#define _AI_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <QObject>

#include "define.h"
#include "game.h"
#include "player.h"
#include "imove.h"
#include "board.h"
#include "infosmoves.h"
#include "infoai.h"

#include <iostream>
using namespace std;

class ai : public QObject
{
        Q_OBJECT

    private:
        //Spielbrett
        Board* board;
        //2 Spieler im Spiel
        Player* playerTable[2];
        //Liste der Bewegungen der Steine
        vector<imove> movesList;
        //Temporäre Liste, um die legalen Züge zu speichern
        vector<imove> regularMovesListTemp;
        //Spieler, der gespielt hat
        int currentPlayer;
        //Spiel abgeschlossen?
        bool isFinished;
        //möglicher Zug
        vector<imove> movesPlay;
        vector<imove>* movesPlaySaved;
        int INFINITY;
        //Id des Spieler in Auswertung
        int idEvaluationPlayer;
        vector<infosMoves> movesSavedList;
        int numCurrentMove;
        int scorePattern[8][8];
        int cptMiniMax;
        int cptAlphaBeta;
        int alphabreak, betabreak;

    public:
        ai();
        ~ai();
        void connecting( game* );

    public slots:
        //Wählt den Wechsel zwischen Spieler
        void chooseMove( game* );

    private:
        //Initialisiert das Modell Punktzahl
        void initializationScorePattern();
        //Funktion, die die KI-Engine initialisiert
        void initialization(game*);
        //Wählt zufällig einen Zug
        imove randomMove();
        //MinMax Funktion
        infoAI miniMax(int);
        //AlphaBeta Funktion
        infoAI alphaBeta( int, infoAI, infoAI );
        //Bewertungsfunktion
        infoAI evaluateGame();
        //Gibt die Punktzahl aus
        infoAI getScore();
        //Spielt einen Zug in der Partie
        bool playMove(imove);
        //den letzten rueckgaengig machen
        void undoLastMove();
        //Update Spieldaten nach dem Spiel eines Zuges: Reversi Stein, Reversi Punkte
        bool updateGame(imove);
        //Aktualisiert eine Reihe der Steine
        void updateRow(imove);
        //Aktualisiert eine Spalte der Steine
        void updateColumn(imove);
        //Aktualisiert Steine diagonal
        void updateDiagonal(imove);
        //dreht ein Stein um
        void turnDownPawn(int,int);
        //aktuallisiert die Punkte nach einem Zug
        void updateScore();
        //definiert gueltige Zuege
        void definingRegularMoves();
        //aktuallisiert gueltige Zuege
        void updateRegularMove();
        //Inkrementiert die Anzahl nach Farbe
        void increaseRegularMove(ColorPawn);
        //Einen legalen Zug pruefen nach mehreren Parametern...
        bool checkRegularMove( int, int, int, int);
        void initializationSavingMove();
        void addMoveList(imove m);
        void nextPlayer();
        void saveCurrentPlayer();
        void saveRegularMoves();
        void savePawnTurnedDown(int x, int y);
        void affiche_movesPlay();
        void updateScoreEvaluate(int, ColorPawn, int &, int &);
        infoAI evaluateGameEvolutive();

    signals:
        //fragt nach dem Zug der AI
        void sendingMove( int, int );
};

#endif
