#ifndef AI_H
#define AI_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <QObject>

#include "game.h"
#include "player.h"
#include "move.h"

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

    public:
        ai();
        ~ai();

        //Anschluss Funktionsmodule
        void connecting( game* );

    public slots:
        //Wählt den Wechsel zu spielen (globale Verarbeitung)
        void chooseMove( game* );

    private:
        //Funktion, die die KI-Engine initialisiert
        void initialization(game*);

        //Wählt zufällig einen Zug
        move randomMove();

    signals:
        //Fragt nach dem Zug des AI
        void sendingMove( int, int );

};


#endif // AI_H
