#include "move.h"


//Konstruktor
move::move()
{
    numMove = 1;
    x = -1;
    y = -1;
    color = White;
}



//Konstruktor
move::move(int x, int y)
{
    numMove = 0;
    this->x = x;
    this->y = y;
    color = White;
}



//Konstruktor
move::move(int x, int y, ColorPawn color)
{
    numMove = 0;
    this->x = x;
    this->y = y;
    this->color = color;
}



//wechsel Variable 'numMove'
void move::setNumMove(int num)
{
    if( num>0 && num<=60 )
    {
        this->numMove = num;
    }
}



//wechsel Variable 'x'
void move::setX(int x)
{
    if( x>=0 && x<8 )
    {
        this->x = x;
    }
}



//wechsel Variable 'y'
void move::setY(int y)
{
    if( y>=0 && y<8 )
    {
        this->y = y;
    }
}



//wechsel Variable 'color'
void move::setColor(ColorPawn color)
{
    this->color = color;
}



//Zugriffsvariable 'numMove'
int move::getNumMove()
{
    return numMove;
}



//Zugriffsvariable 'x'
int move::getX()
{
    return x;
}



//Zugriffsvariable 'y'
int move::getY()
{
    return y;
}



//Zugriffsvariable 'color'
ColorPawn move::getColor()
{
    return color;
}


//Anzeige in Konsole
void move::affichage()
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
