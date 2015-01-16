#ifndef _INFOSMOVES_
#define _INFOSMOVES_

#include <vector>
#include "moves.h"

class InfosMoves
{
        public:

                //Konstruktor
                InfosMoves();
//              infosMoves(int,vector<moves>,vector<moves>);


        private:

                //Anzahl der Steine in Liste
                vector<moves> pawnsTurnedDownList;

                //Anzahl der gueltigen Bewegungen
                vector<moves> regularMovesList;

                //aktuelle Spieler ID
                int currentPlayer;


        public:

                //Setzen Sie eines Steins in die Liste
                void addPawnsTurnedDown(moves);

                //sichern der gueltigen Bewegungen
                void saveRegularMoves(vector<moves>);

                //sichern der aktuellen Spieler
                void saveCurrentPlayer(int);

                //Zugriffsvariable 'currentPlayer'
                int getCurrentPlayer();

                //Zugriffsvariable 'pawnsTurnedDownList'
                vector<moves> getPawnsTurnedDownList();

                //Zugriffsvariable 'regularMovesList'
                vector<moves> getRegularMovesList();

                //gibt die Anzahl von 'pawnsTurnedDownList'
                int getSizePawnsTurnedDownList();
                //gibt die Anzahl von 'regularMovesList'
                int getSizeRegularMovesList();
                //Gibt die Anzahl der Zuege 'regularMovesList'
                moves getRegularMovesList(int);
                //Gibt die Anzahl der Zuege 'pawnsTurnedDownList'
                moves getPawnsTurnedDownList(int);

                //Anzeige im Fenster
                void affichage();
};

#endif
