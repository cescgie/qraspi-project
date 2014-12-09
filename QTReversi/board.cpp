#include "board.h"

Board::Board()
{
    emptyBoard();
}

/* Initialisiert ein neues Spiel für othello
**
** Das Brett wird zuerst geleert und wird
** und wird dann mit 4 Pins und 4 Start legalen
** Züge des ersten Spielers vorbereitet.
** Schließlich wird festgestellt, dass der
** Vorstand wurde geändert.
*/
void Board::initialization()
{
    //Brett wird gelert
    emptyBoard();

    //4 Pins werden positioniert
    boardTable[3][3].setSquare(Occupied,White);
    boardTable[4][4].setSquare(Occupied,White);
    boardTable[4][3].setSquare(Occupied,Black);
    boardTable[3][4].setSquare(Occupied,Black);

    //Fügt 4 legalen Züge für den ersten Spieler hinzu
    boardTable[3][2].setType(RegularMove);
    boardTable[2][3].setType(RegularMove);
    boardTable[5][4].setType(RegularMove);
    boardTable[4][5].setType(RegularMove);
}



/* Fügen Sie ein Stück Farbe "Farbe" in der [x] [y] des Othello Bord.
**
** Ein Stück kann nur auf einem Feld einen legalen Zug enthält gemacht werden.
** Der Stift wird auf dem letzten Schlag auf dem Othello Brett gelegt.
** Die legale Züge werden vom Brett entfernt.
** Ist mit dem [x] [y] Werte "Belegt" und "Farbe" zugeordnet.
** Es wurde festgestellt, dass othellier geändert hat.
**
** Die Funktion gibt true zurück, wenn der Stift wurde
** anderweitig an der Platte, 'false' aufgenommen.
*/
bool Board::addPawn(int x, int y, ColorPawn color)
{
    //Rückgabewert
    bool ret = false;

    //Überprüfung der Angaben nicht aus dem Bild
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        //Testen Sie, ob die Box ist ein legaler Zug
        if( boardTable[x][y].getType() == RegularMove )
        {
            //Löscht den letzten Zug
            clearLastMove();
            //Löscht die legale Züge der Platte
            clearRegularMove();
            //Setzen Sie den Stift auf dem Brett
            boardTable[x][y].setSquare(Occupied,color);
            //Aktivieren Sie das Kennzeichen 'LastMove'
            boardTable[x][y].setLastMove(true);
            //Rückgabewert Umschalttaste
            ret = true;
        }
    }
    return ret;
}



/* Gibt die in der [x] [y] enthaltenen Token der Platte.
**
** Die [x] [y] muss einen Bauern enthalten.
** Die Farbe des Stücks umgekehrt und das Kennzeichen 'animiert' gesetzt.
** Es wurde festgestellt, dass othellier geändert hat.
*/
bool Board::turnDownPawn(int x, int y)
{
        //Rückgabewert
        bool ret = false;
    //Überprüfung der Angaben nicht aus dem Bild
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        //Testen Sie, ob die Box enthält ein Stück
        if( boardTable[x][y].getType() == Occupied )
        {
            //Ändern Sie die Farbe der Spielball
            if( boardTable[x][y].getColor() == White )
            {
                boardTable[x][y].setColor(Black);
            }
            else
            {
                boardTable[x][y].setColor(White);
            }
            //Anreise Animation Box
            boardTable[x][y].setAnimated(true);
            //Zeigt an, dass das Board-Boxen in der Animation
            setAnimated(true);
            //Rückgabewert Umschalttaste
            ret = true;
        }
    }
    return ret;
}



/* Hinzufügen eines legalen Zug in der [x] [y] des Othello Bord.
**
** Um einen legalen Zug hinzuzufügen, muss der Kasten leer sein.
** Ist mit dem [x] [y] Wert 'RegularMove zugeordnet.
*/
bool Board::addRegularMove(int x, int y)
{
        //Rückgabewert
        bool ret = false;
    //Überprüfung der Angaben nicht aus dem Bild
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        //Testen Sie, ob das Feld leer ist
        if( boardTable[x][y].getType() == Empty )
        {
            //Hinzugefügt legalen Zug
            boardTable[x][y].setType(RegularMove);
            ret = true;
        }
    }
    return ret;
}



/* Entfernt Unterhaltungsfach
** und Plätze der Platine
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



/* Schalter der Variable 'animiert'
*/
void Board::setAnimated(bool b)
{
        animated = b;
}



/*
Accessor variable 'animiert'
*/
bool Board::getAnimated()
{
        return animated;
}



/*
** Accessor, der den Typ des [x] [y] des Othello Bord zurück.
** Die zu der Funktion und dem Wert von der Art der Kasten
** mit seinem öffentliche Zugriffs zurückgegeben gebenen
** Koordinaten geprüft.
*/
TypeSquare Board::getTypeSquareBoard(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getType();
    }
}



/* Accessor, die die Farbe des Stückes in der [x] [y] enthalten kehrt
** die Othello Bord.
**
** Die mit der Funktion und dem Wert der Farbe der Stift durch
** seine öffentliche Zugriffs zurückgegeben gebenen Koordinaten geprüft.
*/
ColorPawn Board::getColorPawnBoard(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getColor();
    }
}



/*
*/
bool Board::getAnimatedSquare(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getAnimated();
    }
}



/*
*/
bool Board::getLastMoveSquare(int x, int y)
{
    if( x>=0 && y>=0 && x<8 && y<8 )
    {
        return boardTable[x][y].getLastMove();
    }
}



/* Leeren Sie die othellier alle Stücke die es enthält.
**
** Selbstverständlich sind alle Felder auf dem Brett und
** initialisiert den "Typ" der Prüfwert "Empty".
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



/* Beseitigung der rechtlichen Schritte des Othello Bord.
**
** Wir reisen alle Kästen in der Othello Bord.
** Wenn die aktuelle Zelle enthält eine Rechts Schuss,
** ein leeres Feld durch Zuweisung des Wertes "Empty".
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



/* Löschen des letzten Takt auf der Othello Bord.
**
** Natürlich alle Kästen in der Othello Bord.
** Wenn die aktuelle Zelle enthält den letzten Zug,
** Deaktivierung der Anzeige und Schleifenpfad unterbrochen.
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
                x=8;  y=8;  //Unterbrechung Schleifen natürlich
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
