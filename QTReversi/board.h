#ifndef BOARD_H
#define BOARD_H

#include "define.h"
#include "square.h"

class Board
{

private:

    Square boardTable[8][8];

    bool animated;

public:
    Board();

    void initialization();

    bool addPawn(int,int,ColorPawn);

    bool turnDownPawn(int,int);

    bool addRegularMove(int,int);

    void clearAnimation();

    void setAnimated(bool);

    bool getAnimated();

    TypeSquare getTypeSquareBoard(int,int);

    ColorPawn getColorPawnBoard(int,int);

    bool getAnimatedSquare(int,int);

    bool getLastMoveSquare(int,int);

    void emptySquare(int,int);

    void enableLastMoveSquare(int,int);

    void clearRegularMove();


private:

    void emptyBoard();

    void clearLastMove();
};

#endif // BOARD_H
