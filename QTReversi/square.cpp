#include "square.h"

//Konstruktor: initialisiert alle Variablen
Square::Square()
{
    type = Empty;
    color = White;
    animated = false;
    lastMove = false;
}


//Wechsel der Variable 'Typ' und 'Farbe'
void Square::setSquare(TypeSquare type, ColorPawn color)
{
    this->type = type;
    this->color = color;
}


//Wechsel der Variable 'Typ'
void Square::setType(TypeSquare type)
{
    this->type = type;
}


//Wechsel der Variable 'Farbe'
void Square::setColor(ColorPawn color)
{
    this->color = color;
}


//Wechsel der Variable 'animiert'
void Square::setAnimated(bool b)
{
    animated = b;
}


//Wechsel der Variable 'Letzter Zug'
void Square::setLastMove(bool b)
{
    lastMove = b;
}


//Zugriffsvariable 'Typ'
TypeSquare Square::getType()
{
    return type;
}


//Zugriffsvariable 'Farbe'
ColorPawn Square::getColor()
{
    return color;
}


//Zugriffsvariable 'animiert'
bool Square::getAnimated()
{
    return animated;
}


//Zugriffsvariable 'Letzter Zug'
bool Square::getLastMove()
{
    return lastMove;
}

