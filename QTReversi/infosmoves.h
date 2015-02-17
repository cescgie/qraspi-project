#ifndef _INFOSMOVES_
#define _INFOSMOVES_

#include <vector>
#include "imove.h"
class imove;
class infosMoves
{
        public:
                //Konstruktor
                infosMoves();

        private:
                //Anzahl der Steine in Liste
                vector<imove> pawnsTurnedDownList;
                //Anzahl der gueltigen Bewegungen
                vector<imove> regularMovesList;
                //aktuelle Spieler ID
                int currentPlayer;

        public:
                //setzt ein Stein in die Liste
                void addPawnsTurnedDown(imove);
                //sichern der gueltigen Bewegungen
                void saveRegularMoves(vector<imove>);
                //sichern der aktuellen Spieler
                void saveCurrentPlayer(int);
                //Zugriffsvariable 'currentPlayer'
                int getCurrentPlayer();
                //Zugriffsvariable 'pawnsTurnedDownList'
                vector<imove> getPawnsTurnedDownList();
                //Zugriffsvariable 'regularMovesList'
                vector<imove> getRegularMovesList();
                //gibt die Anzahl von 'pawnsTurnedDownList'
                int getSizePawnsTurnedDownList();
                //gibt die Anzahl von 'regularMovesList'
                int getSizeRegularMovesList();
                //Gibt die Anzahl der Zuege 'regularMovesList'
                imove getRegularMovesList(int);
                //Gibt die Anzahl der Zuege 'pawnsTurnedDownList'
                imove getPawnsTurnedDownList(int);
                //Anzeige im Fenster
                void affichage();
};

#endif
