#include "imove.h"

//Konstruktor
imove::imove()
{
    numMove = 1;
    x = -1;
    y = -1;
    color = White;
}

//Konstruktor
imove::imove(int x, int y)
{
    numMove = 0;
    this->x = x;
    this->y = y;
    color = White;
}

//Konstruktor
imove::imove(int x, int y, ColorPawn color)
{
    numMove = 0;
    this->x = x;
    this->y = y;
    this->color = color;
}

//wechsel 'numMove'
void imove::setNumMove(int num)
{
    if( num>0 && num<=60 )
    {
        this->numMove = num;
    }
}

//wechsel 'x'
void imove::setX(int x)
{
    if( x>=0 && x<8 )
    {
        this->x = x;
    }
}

//wechsel 'y'
void imove::setY(int y)
{
    if( y>=0 && y<8 )
    {
        this->y = y;
    }
}

//wechsel 'color'
void imove::setColor(ColorPawn color)
{
    this->color = color;
}

//Zugriffsvariable 'numMove'
int imove::getNumMove()
{
    return numMove;
}

//Zugriffsvariable 'x'
int imove::getX()
{
    return x;
}

//Zugriffsvariable 'y'
int imove::getY()
{
    return y;
}

//Zugriffsvariable 'color'
ColorPawn imove::getColor()
{
    return color;
}

//Anzeige in Konsole
void imove::affichage()
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
