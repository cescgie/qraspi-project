#include "infoAI.h"

infoAI::infoAI()
{
        score = 0;
}

void infoAI::setScore(int sc)
{
        score = sc;
}

int infoAI::getScore()
{
        return score;
}

void infoAI::setMove(move m)
{
        _move = m;
}

move infoAI::getMove()
{
        return _move;
}

