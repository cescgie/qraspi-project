#ifndef AI_H
#define AI_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <QObject>

#include "game.h"
#include "player.h"
#include "move.h"

#include <iostream>
using namespace std;

class ai : public QObject
{
    Q_OBJECT

    private:
        Board* board;

        Player* playerTable[2];

        vector<move> movesList;

        vector<move> regularMovesListTemp;

        int currentPlayer;

        bool isFinished;

        vector<move> movesPlay;

    public:
        ai();
        ~ai();

        void connecting( game* );

    public slots:
        void chooseMove( game* );

    private:
        void initialization(game*);

        move randomMove();

    signals:
        void sendingMove( int, int );

};


#endif // AI_H
