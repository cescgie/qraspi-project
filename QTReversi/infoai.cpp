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

void infoAI::setMove(moves m)
{
        _move = m;
}

moves infoAI::getMove()
{
        return _move;
}

