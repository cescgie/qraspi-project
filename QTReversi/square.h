#ifndef _SQUARE_H
#define _SQUARE_H

#include "define.h"

class square
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
        square();
        //Wechsel 'Typ' und 'Farbe'
        void setSquare(TypeSquare,ColorPawn);
        //Wechsel 'Typ'
        void setType(TypeSquare);
        //Wechsel 'Farbe'
        void setColor(ColorPawn);
        //Wechsel 'animiert'
        void setAnimated(bool);
        //Wechsel 'Letzter Zug'
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

#endif

