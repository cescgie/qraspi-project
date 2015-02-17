#include "square.h"

//Konstruktor: initialisiert alle Variablen
square::square()
{
    type = Empty;
    color = White;
    animated = false;
    lastMove = false;
}


//Wechsel 'Typ' und 'Farbe'
void square::setSquare(TypeSquare type, ColorPawn color)
{
    this->type = type;
    this->color = color;
}

//Wechsel 'Typ'
void square::setType(TypeSquare type)
{
    this->type = type;
}

//Wechsel 'Farbe'
void square::setColor(ColorPawn color)
{
    this->color = color;
}

//Wechsel 'animiert'
void square::setAnimated(bool b)
{
    animated = b;
}

//Wechsel 'Letzter Zug'
void square::setLastMove(bool b)
{
    lastMove = b;
}

//Zugriffsvariable 'Typ'
TypeSquare square::getType()
{
    return type;
}

//Zugriffsvariable 'Farbe'
ColorPawn square::getColor()
{
    return color;
}

//Zugriffsvariable 'animiert'
bool square::getAnimated()
{
    return animated;
}

//Zugriffsvariable 'Letzter Zug'
bool square::getLastMove()
{
    return lastMove;
}
