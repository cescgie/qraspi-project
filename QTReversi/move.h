#ifndef _MOVE_H
#define _MOVE_H

#include <iostream>
using namespace std;

#include "define.h"

class move
{
    private:

        //Anzahl der Zuege für diese Partie
        int numMove;

        //X-Koordinate des Zuges
        int x;

        //Y-Koordinate des Zuges
        int y;

        //Farbaufnahme
        ColorPawn color;

    public:

        //Konstruktor
        move();
        move(int,int);
        move(int,int,ColorPawn);

        //Wechsel Variable 'nummove'
        void setNumMove(int);
        //Wechsel Variable 'x'
        void setX(int);
        //Wechsel Variable 'y'
        void setY(int);
        //Wechsel Variable 'color'
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
