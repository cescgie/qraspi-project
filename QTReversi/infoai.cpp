#include "infoai.h"
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

void infoAI::setMove(imove m)
{
        move_i = m;
}

imove infoAI::getMove()
{
        return move_i;
}

