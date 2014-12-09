#ifndef _INFOSMOVES_
#define _INFOSMOVES_

#include <vector>
#include "move.h"

class InfosMoves
{
        public:

                //Konstruktor
                InfosMoves();
//              infosMoves(int,vector<move>,vector<move>);


        private:

                //Anzahl der Steine in Liste
                vector<move> pawnsTurnedDownList;

                //Anzahl der gueltigen Bewegungen
                vector<move> regularMovesList;

                //aktuelle Spieler ID
                int currentPlayer;


        public:

                //Setzen Sie eines Steins in die Liste
                void addPawnsTurnedDown(move);

                //sichern der gueltigen Bewegungen
                void saveRegularMoves(vector<move>);

                //sichern der aktuellen Spieler
                void saveCurrentPlayer(int);

                //Zugriffsvariable 'currentPlayer'
                int getCurrentPlayer();

                //Zugriffsvariable 'pawnsTurnedDownList'
                vector<move> getPawnsTurnedDownList();

                //Zugriffsvariable 'regularMovesList'
                vector<move> getRegularMovesList();

                //gibt die Anzahl von 'pawnsTurnedDownList'
                int getSizePawnsTurnedDownList();
                //gibt die Anzahl von 'regularMovesList'
                int getSizeRegularMovesList();
                //Gibt die Anzahl der Zuege 'regularMovesList'
                move getRegularMovesList(int);
                //Gibt die Anzahl der Zuege 'pawnsTurnedDownList'
                move getPawnsTurnedDownList(int);

                //Anzeige im Fenster
                void affichage();
};

#endif
