#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

//Software Version
const QString QtVersion = "QtReversi";

//Boxen Typ
enum TypeSquare
{
    Empty,
    Occupied,
    RegularMove
};


//Farbe des Stein
enum ColorPawn
{
    White,
    Black
};


//Spielertyp
enum TypePlayer
{

    Local,
    Distant,
    AI_1,
    AI_2,
    AI_3
};


//ID des Spielers
const int p1 = 0;
const int p2 = 1;


//Anzeige konstant
const int AngleSpeedAnimation = 3;
const float WidthBorderText = 7.029;
const float WidthSquareText = 10.743;
const float WidthRadiusPawn = 5.3715;


//ID Informationsmeldungen
enum IdMsgInfos
{
        P1_Playing,
        P2_Playing
};


#endif // DEFINE_H
