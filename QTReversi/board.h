#ifndef _BOARD_H
#define _BOARD_H

#include "define.h"
#include "square.h"
//#include <QSoundEffect>

class Board
{
    private:
        //2D-Array, des Brettes
        square boardTable[8][8];
        //Brettanimation = mindestens ein Feld in der Animation
        bool animated;

    public:
        //Konstruktor
        Board();
        //Initialisiert ein neues Spiel für Reversi
        void initialization();
        //setzt ein Stein auf Brett
        bool addPawn(int,int,ColorPawn);
        //dreht ein Stein
        bool turnDownPawn(int,int);
        //macht ein gueltigen Zug
        bool addRegularMove(int,int);
        //entfernt die Animationen
        void clearAnimation();
        //BoolVariable 'animiert'
        void setAnimated(bool);
        //Zugriffsvariable, der den Zustand der Animation Bord kehrt
        bool getAnimated();
        //Zugriffsvariable, gibt die Art eines Kastens zurueck
        TypeSquare getTypeSquareBoard(int,int);
        //Zugriffsvariable, gibt die Farbe eines Steines zurueck
        ColorPawn getColorPawnBoard(int,int);
        //Zugriffsvariable, gibt den Zustand der Animation zurück
        bool getAnimatedSquare(int,int);
        //Zugriffsvariable, liefert den Wert von 'lastMove'
        bool getLastMoveSquare(int,int);
        //Leeres Feld (x, y)
        void emptySquare(int,int);
        //letzter Zug 'lastMove'(x,y)
        void enableLastMoveSquare(int,int);
        //Entfernt gueltige Zuege
        void clearRegularMove();

    private:
        //leert das Brett
        void emptyBoard();
        //Entfernt den letzten Zug
        void clearLastMove();
};

#endif
