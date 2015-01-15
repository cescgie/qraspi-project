#ifndef _AI_H
#define _AI_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <QObject>

#include "define.h"
#include "game.h"
#include "player.h"
#include "move.h"
#include "board.h"
#include "infosmoves.h"
#include "infoAI.h"

#include <iostream>
using namespace std;

class ai : public QObject
{
        Q_OBJECT

private:

        //Spielbrett
        Board* board;

        //Tabelle 2 Spieler im Spiel
        Player* playerTable[2];

        //Liste der Schübe des Brettes
        vector<move> movesList;

        //Temporäre Liste, um die "legale Züge" speichern
        vector<move> regularMovesListTemp;

        //Spieler, der gespielt hat
        int currentPlayer;

        //Partie abgeschlossen?
        bool isFinished;

        //möglicher Zug
        vector<move> movesPlay;
        vector<move>* movesPlaySaved;

        int INFINITY;

        //Id des Spieler in Auswertung
        int idEvaluationPlayer;

        vector<InfosMoves> movesSavedList;
        int numCurrentMove;

        int scorePattern[8][8];

        int cptMiniMax;
        int cptAlphaBeta;
        int alphabreak, betabreak;

public:

        ai();
        ~ai();

        //Anschluss Funktionsmodule
        void connecting( game* );

        public slots:

        //Wählt den Wechsel zu spielen (globale Verarbeitung)
        void chooseMove( game* );

private:

        //Initialisiert das Gittermodell Punktzahl
        void initializationScorePattern();

        //Funktion, die die KI-Engine initialisiert
        void initialization(game*);

        //Wählt zufällig einen Zug
        move randomMove();

        //MinMax Funktion
        infoAI miniMax(int);

        //AlphaBeta Funktion
        infoAI alphaBeta( int, infoAI, infoAI );

        //Bewertungsfunktion
        infoAI evaluateGame();

        //Gibt die Punktzahl
        infoAI getScore();

        //Spielt einen Zug in der Partie
        bool playMove(move);

        //den letzten rueckgaengig machen
        void undoLastMove();

        //Update Spieldaten nach dem Spiel ein Schuss: othellier SHIFT, SHIFT Score
        bool updateGame(move);

        //Verschieben Sie die Stücke von der Linie der Schuss gespielt
        void updateRow(move);

        //Verschieben Sie die Stücke aus der Spalte der Schuss gespielt
        void updateColumn(move);

        //SHIFT Bauern diagonal plötzlich spielte
        void updateDiagonal(move);

        //Gibt ein Token
        void turnDownPawn(int,int);

        //Aktualisieren Sie die Noten der Spieler nach der Auflösung von einem Stift
        void updateScore();

        //Definition von regelgemäßen Zügen
        void definingRegularMoves();

        //SHIFT legalen Züge Inhalt des 'regularMovesList' auf der othellier
        void updateRegularMove();

        //Inkrementieren der Anzahl 'Coup Rechts' Spieler je nach Farbe
        void increaseRegularMove(ColorPawn);

        //Einen legalen Zug Überprüfung nach mehreren Parametern ...
        bool checkRegularMove( int, int, int, int);
        void initializationSavingMove();
        void addMoveList(move m);
        void nextPlayer();
        void saveCurrentPlayer();
        void saveRegularMoves();
        void savePawnTurnedDown(int x, int y);

        void affiche_movesPlay();

        void updateScoreEvaluate(int, ColorPawn, int &, int &);
        infoAI evaluateGameEvolutive();

        signals:

        //Fragt nach dem Zug des AI
        void sendingMove( int, int );
};

#endif
