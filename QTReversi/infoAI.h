#ifndef _INFOAI_H
#define _INFOAI_H

#include "moves.h"

class moves;
class infoAI
{
        public:
                infoAI();
                void setScore(int);
                int getScore();
                void setMove(moves);
                moves getMove();

        private:
                moves _move;
                int score;
};

#endif

