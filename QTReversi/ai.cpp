#include "ai.h"

ai::ai()
{
    board = new Board();
    playerTable[p1] = new Player( p1 );
    playerTable[p2] = new Player( p2 );
    movesList.clear();
    regularMovesListTemp.clear();
    currentPlayer = p1;
    isFinished = false;
    movesPlay.clear();
}

ai::~ai()
{
    delete board;
    delete playerTable[p1];
    delete playerTable[p2];
}

void ai::connecting( game* ge )
{
    connect( ge, SIGNAL( askingAIMove(game*) ), this, SLOT( chooseMove(game*) ) );
    connect( this, SIGNAL( sendingMove(int,int) ), ge, SLOT( recupMove(int,int) ) );
}

void ai::chooseMove( game* ge )
{
    initialization(ge);
    move m = randomMove();
    emit sendingMove( m.getX(), m.getY() );
}

void ai::initialization(game* ge)
{
    *board = *( ge->getBoard() );
    *playerTable[p1] = *( ge->getPlayer(p1) );
    *playerTable[p2] = *( ge->getPlayer(p2) );
    movesList = ge->getMovesList();
    regularMovesListTemp = ge->getRegularMovesListTemp();
    movesPlay.clear();
    currentPlayer = ge->getCurrentPlayer();
}

move ai::randomMove()
{
    if( !regularMovesListTemp.empty() )
    {
        for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
        {
            if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
            {
                movesPlay.push_back(regularMovesListTemp[i]);
            }
        }

        int num = (int) (0 + ((float) rand() / RAND_MAX * (movesPlay.size()-1 - 0 + 1)));
        return movesPlay[num];
    }
    else
    {
        return move(-1,-1);
    }
}
