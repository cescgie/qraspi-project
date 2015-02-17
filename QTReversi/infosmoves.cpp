#include "infosmoves.h"

infosMoves::infosMoves()
{
        currentPlayer = -1;
        pawnsTurnedDownList.clear();
        regularMovesList.clear();
}

//Setzen eines Steines in die Liste
void infosMoves::addPawnsTurnedDown(imove m)
{
        pawnsTurnedDownList.push_back(m);
}

//regelmaessiges sichern der Werte
void infosMoves::saveRegularMoves(vector<imove> v)
{
        regularMovesList = v;
}

//Speichern der aktuellen Spieler
void infosMoves::saveCurrentPlayer(int id)
{
        currentPlayer = id;
}

//Zugriffsvariable 'currentPlayer'
int infosMoves::getCurrentPlayer()
{
        return currentPlayer;
}

//Zugriffsvariable 'pawnsTurnedDownList'
vector<imove> infosMoves::getPawnsTurnedDownList()
{
        return pawnsTurnedDownList;
}

//Zugriffsvariable 'regularMovesList'
vector<imove> infosMoves::getRegularMovesList()
{
        return regularMovesList;
}

//Gibt die Anzahl von 'pawnsTurnedDownList'
int infosMoves::getSizePawnsTurnedDownList()
{
        return pawnsTurnedDownList.size();
}

//Gibt die Anzahl von 'regularMovesList'
int infosMoves::getSizeRegularMovesList()
{
        return regularMovesList.size();
}

//Gibt die Anzahl der Zuege 'regularMovesList'
imove infosMoves::getRegularMovesList(int i)
{
        imove m;
        if( i>=0 && i<regularMovesList.size() )
        {
                m = regularMovesList[i];
        }
        return m;
}

//Gibt die Anzahl der Zuege 'pawnsTurnedDownList'
imove infosMoves::getPawnsTurnedDownList(int i)
{
        imove m;
        if( i>=0 && i<pawnsTurnedDownList.size() )
        {
                m = pawnsTurnedDownList[i];
        }
        return m;
}

//Anzeige im Fenster
void infosMoves::affichage()
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
        cout << "## Ende infosMoves ##" << endl;
}
