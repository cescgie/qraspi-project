#ifndef SQUARE_H
#define SQUARE_H
#include "define.h"

class Square
{

private:

    //Feldtypen: 'leer', 'besetzt' oder 'gueltig'
    TypeSquare type;

    //Farbe des Spielsteines: 'Weiß' oder 'Schwarz'
    ColorPawn color;

    //Animation ja oder nein?
    bool animated;

    //Letzter Zug?
    bool lastMove;

public:
    //Konstruktor
    Square();

    //Wechsel der Variable 'Typ' und 'Farbe'
    void setSquare(TypeSquare,ColorPawn);
    //Wechsel der Variable 'Typ'
    void setType(TypeSquare);
    //Wechsel der Variable 'Farbe'
    void setColor(ColorPawn);
    //Wechsel der Variable 'animiert'
    void setAnimated(bool);
    //Wechsel der Variable 'Letzter Zug'
    void setLastMove(bool);

    //Zugriffsvariable 'Typ'
    TypeSquare getType();
    //Zugriffsvariable 'Farbe'
    ColorPawn getColor();
    //Zugriffsvariable 'animiert'
    bool getAnimated();
    //Zugriffsvariable 'Letzter Zug'
    bool getLastMove();

};

#endif // SQUARE_H
