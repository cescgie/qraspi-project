#ifndef INFOAI_H
#define INFOAI_H

#include "imove.h"

class infoAI
{
        public:
                infoAI();
                void setScore(int);
                int getScore();
                void setMove(imove);
                imove getMove();

        private:
                imove move_i;
                int score;
};
#endif
