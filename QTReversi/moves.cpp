#include "moves.h"


//Konstruktor
moves::moves()
{
    numMove = 1;
    x = -1;
    y = -1;
    color = White;
}



//Konstruktor
moves::moves(int x, int y)
{
    numMove = 0;
    this->x = x;
    this->y = y;
    color = White;
}



//Konstruktor
moves::moves(int x, int y, ColorPawn color)
{
    numMove = 0;
    this->x = x;
    this->y = y;
    this->color = color;
}



//wechsel Variable 'numMove'
void moves::setNumMove(int num)
{
    if( num>0 && num<=60 )
    {
        this->numMove = num;
    }
}



//wechsel Variable 'x'
void moves::setX(int x)
{
    if( x>=0 && x<8 )
    {
        this->x = x;
    }
}



//wechsel Variable 'y'
void moves::setY(int y)
{
    if( y>=0 && y<8 )
    {
        this->y = y;
    }
}



//wechsel Variable 'color'
void moves::setColor(ColorPawn color)
{
    this->color = color;
}



//Zugriffsvariable 'numMove'
int moves::getNumMove()
{
    return numMove;
}



//Zugriffsvariable 'x'
int moves::getX()
{
    return x;
}



//Zugriffsvariable 'y'
int moves::getY()
{
    return y;
}



//Zugriffsvariable 'color'
ColorPawn moves::getColor()
{
    return color;
}


//Anzeige in Konsole
void moves::affichage()
{
        cout << "\t\tWechsel: X=" << getX() << "  Y= " << getY() << " Farbe= " ;
        if( getColor()==White )
        {
                cout << "Weiß" << endl;
        }
        else
        {
                cout << "Schwarz" << endl;
        }
}
