#ifndef _IMOVE_H
#define _IMOVE_H

#include <iostream>
using namespace std;

#include "define.h"

class imove
{
    private:
        //Anzahl der Zuege für diese Runde
        int numMove;
        //X-Koordinate des Zuges
        int x;
        //Y-Koordinate des Zuges
        int y;
        //Farbe des Steines
        ColorPawn color;

    public:
        //Konstruktor
        imove();
        imove(int,int);
        imove(int,int,ColorPawn);
        //Wechsel 'nummove'
        void setNumMove(int);
        //Wechsel 'x'
        void setX(int);
        //Wechsel 'y'
        void setY(int);
        //Wechsel 'color'
        void setColor(ColorPawn);
        //Zugriffsvariable 'nummove'
        int getNumMove();
        //Zugriffsvariable 'x'
        int getX();
        //Zugriffsvariable 'y'
        int getY();
        //Zugriffsvariable 'color'
        ColorPawn getColor();
        void affichage();

};

#endif
