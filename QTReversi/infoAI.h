#ifndef _INFOAI_H
#define _INFOAI_H

#include "move.h"

class move;
class infoAI
{
        public:
                infoAI();
                void setScore(int);
                int getScore();
                void setMove(move);
                move getMove();

        private:
                move _move;
                int score;
};

#endif

