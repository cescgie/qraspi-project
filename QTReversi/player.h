#ifndef _PLAYER_H
#define _PLAYER_H

#include "define.h"
#include <QString>

class Player
{

    private:

                //Spielernummer
                int id;

                //Spielername
                QString name;

                //Spielertyp: 'Lokal', 'Global', 'IA_1', 'IA_2', 'IA_3'
                TypePlayer type;

                //Farbe des Spielersteines
        ColorPawn color;

        //Spielerpunkte
        int score;

        //Anzahl der Wechsel
        int numMoves;

    public:

        //Konstruktor
        Player( int );
        Player( int, QString, TypePlayer, ColorPawn );

        //Wechsel Variable 'name'
        void setName(QString);
        //Wechsel Variable 'type'
        void setType(TypePlayer);
        //Wechsel Variable 'color'
        void setColor(ColorPawn);
        //Wechsel Variable 'score'
        void setScore(int);
        //Wechsel Variable 'numMoves'
        void setNumMoves(int);

        //Zugriffsvariable 'ID'
        int getId();
        //Zugriffsvariable 'name'
        QString getName();
        //Zugriffsvariable 'type'
        TypePlayer getType();
        //Zugriffsvariable 'color'
        ColorPawn getColor();
        //Zugriffsvariable 'score'
        int getScore();
        //Zugriffsvariable 'numMoves'
        int getNumMoves();

        //ruecksetzen 'numMoves'
        void RazNumMoves();

        //Initialisierung von 'score', 'numMoves', 'timePlayed' der Spieler
        void initialization();

        //Erhoehen der Punkte
        void increaseScore();
        //Senken der Punkte
        void decreaseScore();
        //Erhoehen der legalen Züge
        void increaseRegularMove();


};

#endif
