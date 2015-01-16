#include "infosmoves.h"

InfosMoves::InfosMoves()
{
        currentPlayer = -1;
        pawnsTurnedDownList.clear();
        regularMovesList.clear();
}



//Setzen eines Steines in die Liste des Wertes
void InfosMoves::addPawnsTurnedDown(moves m)
{
        pawnsTurnedDownList.push_back(m);
}



//regelmaessiges sichern der Werte
void InfosMoves::saveRegularMoves(vector<moves> v)
{
        regularMovesList = v;
}



//Speichern der aktuellen Spieler
void InfosMoves::saveCurrentPlayer(int id)
{
        currentPlayer = id;
}



//Zugriffsvariable 'currentPlayer'
int InfosMoves::getCurrentPlayer()
{
        return currentPlayer;
}



//Zugriffsvariable 'pawnsTurnedDownList'
vector<moves> InfosMoves::getPawnsTurnedDownList()
{
        return pawnsTurnedDownList;
}



//Zugriffsvariable 'regularMovesList'
vector<moves> InfosMoves::getRegularMovesList()
{
        return regularMovesList;
}



//Gibt die Anzahl von 'pawnsTurnedDownList'
int InfosMoves::getSizePawnsTurnedDownList()
{
        return pawnsTurnedDownList.size();
}


//Gibt die Anzahl von 'regularMovesList'
int InfosMoves::getSizeRegularMovesList()
{
        return regularMovesList.size();
}


//Gibt die Anzahl der Zuege 'regularMovesList'
moves InfosMoves::getRegularMovesList(int i)
{
        moves m;
        if( i>=0 && i<regularMovesList.size() )
        {
                m = regularMovesList[i];
        }
        return m;
}


//Gibt die Anzahl der Zuege 'pawnsTurnedDownList'
moves InfosMoves::getPawnsTurnedDownList(int i)
{
        moves m;
        if( i>=0 && i<pawnsTurnedDownList.size() )
        {
                m = pawnsTurnedDownList[i];
        }
        return m;
}




//Anzeige im Konsole
void InfosMoves::affichage()
{
        cout << "\t aktueller Spieler: ";
        if( currentPlayer == p1 )
                cout << "Schwarz" << endl;
        else
                cout << "Weiß" << endl;

        cout << "\t Anzahl der Steine:" << endl;
        for( int i=0 ; i<pawnsTurnedDownList.size() ; i++ )
                pawnsTurnedDownList[i].affichage();

        cout << "\t Anzahl der Bewegungen:" << endl;
        for( int i=0 ; i<regularMovesList.size() ; i++ )
                regularMovesList[i].affichage();
        cout << "## Ende InfosMoves ##" << endl;
}
