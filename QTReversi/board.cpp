#include "board.h"

/* Konstruktor
**
** Initialisiert das Brett für ein neues Spiel.
*/
Board::Board()
{
        emptyBoard();
}



/* Initialisiert ein neues Spiel für Reversi
**
** Das Brett wird zuerst geleert und wird
** dann mit 4 Pins vorbereitet.
*/
void Board::initialization()
{
    //Brett wird gelert
    emptyBoard();

    //4 Pins werden positioniert
    boardTable[3][3].setSquare(Occupied,White);
    boardTable[3][3].setAnimated(true);
    boardTable[4][4].setSquare(Occupied,White);
    boardTable[4][4].setAnimated(true);
    boardTable[4][3].setSquare(Occupied,Black);
    boardTable[4][3].setAnimated(true);
    boardTable[3][4].setSquare(Occupied,Black);
    boardTable[3][4].setAnimated(true);

    //Fügt 4 legale Züge für den ersten Spieler hinzu
    boardTable[3][2].setType(RegularMove);
    boardTable[2][3].setType(RegularMove);
    boardTable[5][4].setType(RegularMove);
    boardTable[4][5].setType(RegularMove);

    setAnimated(true);
}

bool Board::addPawn(int x, int y, ColorPawn color)
{
    //Rückgabewert
    bool ret = false;

    //Überprüfung der Daten
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        //Testen, ob die Box ein legaler Zug ist
        if( boardTable[x][y].getType() == RegularMove )
        {
            //Löscht den letzten Zug
            clearLastMove();
            //Löscht die legale Züge vom Brett
            clearRegularMove();
            //Setzt ein Stein auf dem Brett
            boardTable[x][y].setSquare(Occupied,color);
            //Aktiviert 'LastMove'
            boardTable[x][y].setLastMove(true);
            //Rückgabewert
            ret = true;
        }
    }

    boardTable[x][y].setAnimated(true);
    setAnimated(true);
    return ret;
}

/* Funktion dreht ein Stein um
 */
bool Board::turnDownPawn(int x, int y)
{
        //Rückgabewert
        bool ret = false;
    //Überprüfung der Daten
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        //Testen, ob die Box ein Stein enthält
        if( boardTable[x][y].getType() == Occupied )
        {
            //Ändert die Farbe des Steines
            if( boardTable[x][y].getColor() == White )
            {
                boardTable[x][y].setColor(Black);
            }
            else
            {
                boardTable[x][y].setColor(White);
            }
            //animiert die Box
            boardTable[x][y].setAnimated(true);
            //Zeigt die Animation
            setAnimated(true);
            //Rückgabewert
            ret = true;
        }
    }
    return ret;
}

/* Funktion fuegt ein Stein hinzu
 */
bool Board::addRegularMove(int x, int y)
{
        //Rückgabewert
        bool ret = false;
    //Überprüfung der Daten
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        //Testen, ob das Feld leer ist
        if( boardTable[x][y].getType() == Empty )
        {
            //fuegt legalen Zug hinzu
            boardTable[x][y].setType(RegularMove);
            ret = true;
        }
    }
    return ret;
}

/* Funktion löscht Inhalt aus der Box
 */
void Board::clearAnimation()
{
        setAnimated( false );
    for( int y=0 ; y<8 ; y++ )
    {
        for( int x=0 ; x<8 ; x++ )
        {
                boardTable[x][y].setAnimated( false );
        }
    }
}



/* Wechsel 'animiert'
*/
void Board::setAnimated(bool b)
{
        animated = b;
}

/*Zugriffsvariable 'animiert'
*/
bool Board::getAnimated()
{
        return animated;
}

/* Funktion gibt Koordinaten des Typs zurueck
 */
TypeSquare Board::getTypeSquareBoard(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getType();
    }
}

/* Funktion gibt Koordinaten der Farbe zurueck
 */
ColorPawn Board::getColorPawnBoard(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getColor();
    }
}

bool Board::getAnimatedSquare(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getAnimated();
    }
}

bool Board::getLastMoveSquare(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getLastMove();
    }
}

/* Funktion leert das Brett
 */
void Board::emptyBoard()
{
    for( int x=0 ; x<8 ; x++ )
    {
        for( int y=0 ; y<8 ; y++ )
        {
            boardTable[x][y].setType(Empty);
        }
    }
}

/* Funktion loescht die moeglichen Zuege
 */
void Board::clearRegularMove()
{
    for( int x=0 ; x<8 ; x++ )
    {
        for( int y=0 ; y<8 ; y++ )
        {
            if( boardTable[x][y].getType() == RegularMove )
            {
                boardTable[x][y].setType(Empty);
            }
        }
    }
}

/* Funktion loescht die letzten Zuege
 */
void Board::clearLastMove()
{
    for( int y=0 ; y<8 ; y++ )
    {
        for( int x=0 ; x<8 ; x++ )
        {
                if( boardTable[x][y].getLastMove() == true )
                {
                boardTable[x][y].setLastMove(false);
                x=8;  y=8;
                }
        }
    }
}

void Board::emptySquare(int x, int y)
{
        boardTable[x][y].setType(Empty);
        boardTable[x][y].setLastMove(false);
}


void Board::enableLastMoveSquare(int x, int y)
{
        boardTable[x][y].setLastMove(true);
}
