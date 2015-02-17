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
        INFINITY = 10000;
        initializationScorePattern();
}


ai::~ai()
{
        delete board;
        delete playerTable[p1];
        delete playerTable[p2];
}


//Anschluss Funktionsmodule
void ai::connecting( game* ge )
{
        connect( ge, SIGNAL( askingAIMove(game*) ), this, SLOT( chooseMove(game*) ) );
        connect( this, SIGNAL( sendingMove(int,int) ), ge, SLOT( recupMove(int,int) ) );
}


//Wählt den Wechsel zu spielen
void ai::chooseMove( game* ge )
{
        initialization(ge);

        int level = 0;
        imove m;

        switch( playerTable[idEvaluationPlayer]->getType() )
        {
                case AI_1:
                /************** Random Mode ******************/
                        m = randomMove();
                        break;

                case AI_2:
                        level = 2;
                        break;
                case AI_3:
                        level = 5;
                        break;
                default:
                        level = 1;
                        break;
        }

        if( level != 0 )
        {
/************** AlphaBeta Mode *********************/
                infoAI alpha, beta;
                alpha.setScore( -INFINITY );
                beta.setScore( INFINITY );
//              cout << "##########################" << endl << "nb moves= " << movesPlay.size() << endl;
                infoAI res = alphaBeta( level, alpha, beta );
                m = res.getMove();
/***************************************************/
        }

        emit sendingMove( m.getX(), m.getY() );
}


//Eine Funktion, die die Suche von IA initialisiert
void ai::initialization(game* ge)
{
//      cout << "Enter ds ai::initialization()" << endl;
        *board = *( ge->getBoard() );
        *playerTable[p1] = *( ge->getPlayer(p1) );
        *playerTable[p2] = *( ge->getPlayer(p2) );
        movesList = ge->getMovesList();
        regularMovesListTemp = ge->getRegularMovesListTemp();
        movesPlay.clear();
        currentPlayer = ge->getCurrentPlayer();
        idEvaluationPlayer = currentPlayer;
        movesSavedList.clear();
        movesSavedList = ge->getMovesSavedList();
        numCurrentMove = ge->getNumCurrentMove();

        //Initialisieren von movesPlay
        for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
        {
        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
        {
                        movesPlay.push_back(regularMovesListTemp[i]);
                }
        }
}

//Wählt zufällig einen Spielzug
imove ai::randomMove()
{
//      cout << "Enter ds ai::randomMove()" << endl;
//      cout << "currentPlayer = " << currentPlayer << endl;

        if( !regularMovesListTemp.empty() )
        {
//              cout << "Liste regularMovesListTemp" << endl;
            for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
            {
//              regularMovesListTemp[i].affichage();
                if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
                {
                        movesPlay.push_back(regularMovesListTemp[i]);
                }
            }

            //Generierung eines zufallsbedingten Ganzen
            int num = (int) (0 + ((float) rand() / RAND_MAX * (movesPlay.size()-1 - 0 + 1)));
            return movesPlay[num];
        }
        else
        {
                return imove(-1,-1);
        }
}

infoAI ai::miniMax( int depth )
{
        cptMiniMax++;
//      cout << "cptMiniMax=" << cptMiniMax << endl;

        if ( isFinished )  //Wenn der Teil beendet wird
        {
                return getScore();
        }
        else if( depth == 0 )  // Wenn die maximale Tiefe erreicht wird
        {
                return evaluateGame();
        }

        infoAI result, bestResult;

        if ( idEvaluationPlayer == playerTable[currentPlayer]->getId() )  // node Max = Program
        {
                bestResult.setScore(-INFINITY);
//              cout << "       movesPlay size: " << movesPlay.size() << endl;

                for( int i=0 ; i<movesPlay.size() ; i++ )
                {
                        playMove( movesPlay[i] );  //Spiele den Zug i
                        result = miniMax( depth-1 );
//                      cout << "            Score= " << result.getScore() << endl;
                        undoLastMove();  //Annulliere den letzten Zug
                        if (result.getScore() > bestResult.getScore())
                        {
                                bestResult.setScore( result.getScore() );
                                bestResult.setMove( movesPlay[i] );
                        }

                }
        }
        else  // node MIN = opponent
        {
                bestResult.setScore( INFINITY );
//              cout << "       movesPlay size 3: " << movesPlay.size() << endl;

                for( int i=0 ; i<movesPlay.size() ; i++ )
                {
                        playMove( movesPlay[i] );  //Spiele den Zug i
                        result = miniMax( depth-1 );
                        undoLastMove();  //Annulliere den letzten Zug
//                      cout << "            Score= " << result.getScore() << endl;
                        if( result.getScore() < bestResult.getScore() )
                        {
                                bestResult.setScore( result.getScore() );
                                bestResult.setMove( movesPlay[i] );
                        }
                }
        }
        return bestResult ;
}


infoAI ai::getScore()
{
//Gibt die Punktzahl des Spielers
//      cout << "entre ds getScore()" << endl;
        infoAI res;
        res.setScore(playerTable[idEvaluationPlayer]->getScore());
        return res;
}



//Auswertung der Tabelle 'scorePattern'
infoAI ai::evaluateGame()
{
        int scoreP1 = 0, scoreP2 = 0;

        for( int x=0 ; x<8 ; x++ )
        {
                for( int y=0 ; y<8 ; y++ )
                {
                        if( board->getTypeSquareBoard(x,y) == Occupied )
                        {
                                if( board->getColorPawnBoard(x,y) == playerTable[p1]->getColor() )
                                {
                                        scoreP1 += scorePattern[x][y];
                                }
                                else
                                {
                                        scoreP2 += scorePattern[x][y];
                                }
                        }
                }
        }
//      cout << "ScoreP1=" << scoreP1 << endl << "ScoreP2= " << scoreP2 << endl;
        infoAI res;
        if( p1 == idEvaluationPlayer )
        {
                res.setScore(scoreP1-scoreP2);
        }
        else
        {
                res.setScore(scoreP2-scoreP1);
        }
        return res;
}



//Auswertung von der Tabelle 'scorePattern'
infoAI ai::evaluateGameEvolutive()
{
        int y,x;
        int scoreP1 = 0, scoreP2 = 0;

        for( x=0 ; x<8 ; x++ )
        {
                for( y=0 ; y<8 ; y++ )
                {
                        if( board->getTypeSquareBoard(x,y) == Occupied )
                        {
                                if( board->getColorPawnBoard(x,y) == playerTable[p1]->getColor() )
                                {
                                        scoreP1 += scorePattern[x][y];
                                }
                                else
                                {
                                        scoreP2 += scorePattern[x][y];
                                }
                        }
                }
        }

        //Analysiert die Struktur des Bords
        ColorPawn colorTmp;
        bool rowFull[4];
        for( x=0 ; x<4 ; x++ )
                rowFull[x] = false;

        //coin 0,0
        if( board->getTypeSquareBoard(0,0) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(0,0);
                //Bord (leiten/obere) -> row 0
                x = 1;
                while( board->getTypeSquareBoard(x,0) == Occupied && x<7 )
                {
                        if( board->getColorPawnBoard(x,0) == colorTmp )
                        {
                                updateScoreEvaluate( x, colorTmp, scoreP1, scoreP2 );
                                if( x == 6 ) //row full
                                {
                                        rowFull[0] = true;
                                }
                                x++;
                        }
                        else
                        {
                                x = 7;
                        }
                }
                //Bord linksbündig -> column 0
                y = 1;
                while( board->getTypeSquareBoard(0,y) == Occupied && y<7 )
                {
                        if( board->getColorPawnBoard(0,y) == colorTmp )
                        {
                                updateScoreEvaluate( y, colorTmp, scoreP1, scoreP2 );
                                if( y == 6 )
                                {
                                        rowFull[3] = true;
                                }
                                y++;
                        }
                        else
                        {
                                y = 7;
                        }
                }

        }

        //coin 7,0
        if( board->getTypeSquareBoard(7,0) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(7,0);
                //Bord leiten/obere -> row 0
                if( rowFull[0] == false )  //die Linien ändern sich nie, wenn es bereits mit einer Farbe gefüllt ist
                {
                        x = 6;
                        while( board->getTypeSquareBoard(x,0) == Occupied && x>0 )
                        {
                                if( board->getColorPawnBoard(x,0) == colorTmp )
                                {
                                        updateScoreEvaluate( x, colorTmp, scoreP1, scoreP2 );
                                        x--;
                                }
                                else
                                {
                                        x = 0;
                                }
                        }
                }
                //Bord rechtsbündig -> column 7
                y = 1;
                while( board->getTypeSquareBoard(7,y) == Occupied && y<7 )
                {
                        if( board->getColorPawnBoard(7,y) == colorTmp )
                        {
                                updateScoreEvaluate( y, colorTmp, scoreP1, scoreP2 );
                                if( y == 6 )
                                {
                                        rowFull[1] = true;
                                }
                                y++;
                        }
                        else
                        {
                                y = 7;
                        }
                }

        }

        //coin 7,7
        if( board->getTypeSquareBoard(7,7) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(7,7);
                //Bord rechtsbündig -> column 7
                if( rowFull[1] == false )  //die Linien ändern sich nie, wenn es bereits mit einer Farbe gefüllt ist
                {
                        y = 6;
                        while( board->getTypeSquareBoard(7,y) == Occupied && y>0 )
                        {
                                if( board->getColorPawnBoard(7,y) == colorTmp )
                                {
                                        updateScoreEvaluate( y, colorTmp, scoreP1, scoreP2 );
                                        y--;
                                }
                                else
                                {
                                        y = 0;
                                }
                        }
                }
                //Bord unten -> row 7
                x = 6;
                while( board->getTypeSquareBoard(x,7) == Occupied && x>0 )
                {
                        if( board->getColorPawnBoard(x,7) == colorTmp )
                        {
                                updateScoreEvaluate( x, colorTmp, scoreP1, scoreP2 );
                                if( x == 1 )
                                {
                                        rowFull[2] = true;
                                }
                                x--;
                        }
                        else
                        {
                                x = 0;
                        }
                }
        }

        //coin 0,7
        if( board->getTypeSquareBoard(0,7) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(0,7);
                //Bord untere -> row 7
                if( rowFull[2] == false )  //die Linie ändern sich nie, wenn es bereits mit einer Farbe gefüllt ist
                {
                        x = 0;
                        while( board->getTypeSquareBoard(x,7) == Occupied && x<7 )
                        {
                                if( board->getColorPawnBoard(x,7) == colorTmp )
                                {
                                        updateScoreEvaluate( x, colorTmp, scoreP1, scoreP2 );
                                        x++;
                                }
                                else
                                {
                                        x = 7;
                                }
                        }
                }
                //Bord linksbündig -> column 0
                if( rowFull[3] == false )
                {
                        y = 6;
                        while( board->getTypeSquareBoard(0,y) == Occupied && y>0 )
                        {
                                if( board->getColorPawnBoard(0,y) == colorTmp )
                                {
                                        updateScoreEvaluate( y, colorTmp, scoreP1, scoreP2 );
                                        y--;
                                }
                                else
                                {
                                        y = 0;
                                }
                        }
                }
        }

        //case X 1,1
        if( board->getTypeSquareBoard(1,1) == Occupied && board->getTypeSquareBoard(0,0) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(1,1);
                if( colorTmp == board->getColorPawnBoard(0,0) ) //Ecke der gleichen Farbe wie Feld X
                {
                        updateScoreEvaluate( 5, colorTmp, scoreP1, scoreP2 );
                        if( board->getColorPawnBoard(0,1) == colorTmp && board->getColorPawnBoard(1,0) == colorTmp ) //Spielfigur definieren
                        {
                                updateScoreEvaluate(1, colorTmp, scoreP1, scoreP2);
                        }
                }
        }
        //case X 6,1
        if( board->getTypeSquareBoard(6,1) == Occupied && board->getTypeSquareBoard(7,0) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(6,1);
                if( colorTmp == board->getColorPawnBoard(7,0) ) //Ecke der gleichen Farbe wie Feld X
                {
                        updateScoreEvaluate( 5, colorTmp, scoreP1, scoreP2 );
                        if( board->getColorPawnBoard(6,0) == colorTmp && board->getColorPawnBoard(7,1) == colorTmp ) //Spielfigur definieren
                        {
                                updateScoreEvaluate(1, colorTmp, scoreP1, scoreP2);
                        }
                }
        }
        //case X 6,6
        if( board->getTypeSquareBoard(6,6) == Occupied && board->getTypeSquareBoard(7,7) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(6,6);
                if( colorTmp == board->getColorPawnBoard(7,7) ) //Ecke der gleichen Farbe wie Feld X
                {
                        updateScoreEvaluate( 5, colorTmp, scoreP1, scoreP2 );
                        if( board->getColorPawnBoard(6,7) == colorTmp && board->getColorPawnBoard(7,6) == colorTmp ) //Spielfigur definieren
                        {
                                updateScoreEvaluate(1, colorTmp, scoreP1, scoreP2);
                        }
                }
        }
        //case X 1,6
        if( board->getTypeSquareBoard(1,6) == Occupied && board->getTypeSquareBoard(0,7) == Occupied )
        {
                colorTmp = board->getColorPawnBoard(1,6);
                if( colorTmp == board->getColorPawnBoard(0,7) ) //Ecke der gleichen Farbe wie Feld X
                {
                        updateScoreEvaluate( 5, colorTmp, scoreP1, scoreP2 );
                        if( board->getColorPawnBoard(0,6) == colorTmp && board->getColorPawnBoard(1,7) == colorTmp ) //Spielfigur definieren
                        {
                                updateScoreEvaluate(1, colorTmp, scoreP1, scoreP2);
                        }
                }
        }


        //Berechnung der Rückgabewert
//      cout << "ScoreP1=" << scoreP1 << endl << "ScoreP2= " << scoreP2 << endl;
        infoAI res;
        if( p1 == idEvaluationPlayer )
        {
                res.setScore(scoreP1-scoreP2);
        }
        else
        {
                res.setScore(scoreP2-scoreP1);
        }
        return res;
}


void ai::updateScoreEvaluate( int square, ColorPawn color, int &scoreP1, int &scoreP2 )
{
        int value;
        switch( square )
        {
                case 1:
                case 6:
                        value = 300; //+150 um das anfängliche Spielergebnis zu annulieren und +150 um das Spielergebnis im Feld anzugeben
                        break;
                case 2:
                case 3:
                case 4:
                case 5:
                        value = 100; //fügt 100 zum Anfangswert hinzu
                        break;
                default:
                        value = 0;
                        break;
        }

        if( color == playerTable[p1]->getColor() )
        {
                scoreP1 += value;
        }
        else
        {
                scoreP2 += value;
        }
}



bool ai::playMove(imove m)
{
    bool ret;   //Rückgabewert

    //Wiedererlangung und Update der Farbe des Spielzugs
    m.setColor( playerTable[currentPlayer]->getColor() );
    //Hinzufügen einer Spielfigur
    ret = board->addPawn( m.getX(), m.getY(), m.getColor() );

    if( ret )  //Wenn legaler Zug, dann...
    {
        initializationSavingMove();  //Initialisieren einer Liste mit den gespeicherten Spielzügen

        playerTable[currentPlayer]->increaseScore();  //1 pt für die Spielfigur
        addMoveList(m);  //Hinzufügen eines Sielzugs auf die Liste
        updateGame(m);  //Update der Spieldaten

        nextPlayer();  //nächster Spieler

        definingRegularMoves();  //Definition der neuen "legalen Züge"

        if( playerTable[currentPlayer]->getNumMoves() == 0 ) //Wenn der Spielen nicht spielen kann
        {
            nextPlayer();
            if( playerTable[currentPlayer]->getNumMoves() == 0 ) //Kein Spieler kann spielen
            {
                isFinished = true;
            }
        }

        if( !isFinished )
        {
            updateRegularMove();    //Update der legalen Spielzüge der aktuellen Spieler
        }
                saveCurrentPlayer();
                saveRegularMoves();  //regelmäßiges Backup der Spielzüge
                numCurrentMove ++;

        }
        //Initialisieren von movesPlay
        movesPlay.clear();
        for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
        {
        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
        {
                        movesPlay.push_back(regularMovesListTemp[i]);
                }
        }

    return ret;
}



void ai::undoLastMove()
{
        //Abbruch des Spielzuges der Partie, welche nicht unbedingt beendet wurde
        isFinished = false;
        if( numCurrentMove > 0 )
        {
                imove moveTmp;
        //Neuausrichten des vorherigen Spielzugs
                numCurrentMove--;
        //einen aktuellen Spieler wiederherstellen
                if( numCurrentMove == 0 ) //Konfigurieren des Anfangs
                {
                        //Der Spieler, der beginnt, ist die schwarze Spielfigur
                        if( playerTable[p1]->getColor() == Black )
                        {
                                currentPlayer = p1;
                        }
                        else
                        {
                                currentPlayer = p2;
                        }
                }
                else
                {
                        currentPlayer = movesSavedList[numCurrentMove-1].getCurrentPlayer();
                }
                //Entfernt die letzten,platzierten Spielfiguren
                board->emptySquare(movesList[numCurrentMove].getX(),movesList[numCurrentMove].getY());
                playerTable[currentPlayer]->decreaseScore();  //Update der Spielstände
                //Update letzter Spielzug auf dem Brett, wenn er existiert
                if(numCurrentMove > 0)
                {
                        board->enableLastMoveSquare(movesList[numCurrentMove-1].getX(),movesList[numCurrentMove-1].getY());
                }
                //Zurückkehren der Spielfiguren
                for( int i=0 ; i<movesSavedList[numCurrentMove].getSizePawnsTurnedDownList() ; i++ )
                {
                        moveTmp = movesSavedList[numCurrentMove].getPawnsTurnedDownList(i);
                        board->turnDownPawn(moveTmp.getX(),moveTmp.getY());
                        //Update der Spielstände
                        if( currentPlayer == p1 )
                        {
                                playerTable[p1]->decreaseScore();
                                playerTable[p2]->increaseScore();
                        }
                        else
                        {
                                playerTable[p1]->increaseScore();
                                playerTable[p2]->decreaseScore();
                        }
                }
                board->clearAnimation();  //keine Animation
                //Update der legalen Spielzüge
                board->clearRegularMove();
                regularMovesListTemp.clear();
                int numMovesCurPlayer = 0;
                //Abrufen der gueltigen Spielzüge von 'regularMovesListTemp'
                if( numCurrentMove == 0 ) //Konfigurieren des Anfangs
                {
                        regularMovesListTemp.clear();
                        regularMovesListTemp.push_back( imove(2,3,Black) );
                        regularMovesListTemp.push_back( imove(3,2,Black) );
                        regularMovesListTemp.push_back( imove(4,5,Black) );
                        regularMovesListTemp.push_back( imove(5,4,Black) );
                        regularMovesListTemp.push_back( imove(5,3,White) );
                        regularMovesListTemp.push_back( imove(4,2,White) );
                        regularMovesListTemp.push_back( imove(2,4,White) );
                        regularMovesListTemp.push_back( imove(3,5,White) );
                }
                else
                {
                        regularMovesListTemp = movesSavedList[numCurrentMove-1].getRegularMovesList();
                }
                //Update der gueltigen Spielzüge auf dem Brett
                for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
                {
                        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
                        {
                                board->addRegularMove( regularMovesListTemp[i].getX(), regularMovesListTemp[i].getY() );
                                numMovesCurPlayer++;
                        }
                }

                if( currentPlayer == p1 )
                {
                        playerTable[p1]->setNumMoves(numMovesCurPlayer);
                        playerTable[p2]->setNumMoves(regularMovesListTemp.size()-numMovesCurPlayer);
                }
                else
                {
                        playerTable[p1]->setNumMoves(regularMovesListTemp.size()-numMovesCurPlayer);
                        playerTable[p2]->setNumMoves(numMovesCurPlayer);
                }

                //Initialisieren von movesPlay
                movesPlay.clear();
                for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
                {
                        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
                        {
                                movesPlay.push_back(regularMovesListTemp[i]);
                        }
                }

        }
}

bool ai::updateGame(imove m)
{
    updateRow(m);
    updateColumn(m);
    updateDiagonal(m);
}

//Update der Spielfiguren von der Reihe des gespielten Zugs
void ai::updateRow(imove m)
{
    //Rückgewinnungder Koordinaten des Zuges
    int xMove = m.getX(),
        yMove = m.getY();
    //Wiederherstellen der Farbe
    ColorPawn colorMove = m.getColor();

    int i; //Indexbegriff


/*--------------- Verifikation LINKS/LEFT des Zugs 'm' ---------------------*/
    i = xMove-1;
    /*Es verschiebt sich nach links, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i>=0 && board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)!=colorMove )
    {
        i--;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i>=0 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i++;//Es ist auf das erste gegnerische Feld ausgerichtet (die zuerst nach rechts ...)
            while( i<xMove )
            {
                                turnDownPawn(i,yMove);  //Umdrehen der Spielfigur
                this->updateScore();  //Anpassen der Spielstände
                i++;  //Es geht in das nächste Feld rechts
            }
        }
    }

/*--------------- Verifikation RECHTS/RIGHT des Zugs 'm' ---------------------*/
    i = xMove+1;
    /*Es verschiebt sich nach rechts, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i<8 && board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)!=colorMove )
    {
        i++;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i<8 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i--;//Neuausrichtung auf das erste gegnerische Feld (die erste nach links)
            while( i>xMove )
            {
                                turnDownPawn(i,yMove);
                this->updateScore();  //Anpassen der Spielstände
                i--;  //Es geht in das nächste Feld links
            }
        }
    }
}


//Update der Spielfiguren in der Spalte des gespielten Zugs
void ai::updateColumn(imove m)
{
    //Rückgewinnung der Koordinaten des Zuges
    int xMove = m.getX(),
        yMove = m.getY();
    //Wiederherstellung der Farbe
    ColorPawn colorMove = m.getColor();

    int i; //Indexbegriff


/*--------------- Verifikation OBEN Zug 'm' ---------------------*/
    i = yMove-1;
    /*Es verschiebt sich nach oben, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i>=0 && board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)!=colorMove )
    {
        i--;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i>=0 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i++;//Neuausrichtung auf das erste gegnerische Feld (der erste unten ...)
            while( i<yMove )
            {
                                turnDownPawn(xMove,i);
                this->updateScore();  //Anpassen der Spielstände
                i++;  //Es geht in das nächste Feld nach unten
            }
        }
    }

/*--------------- Verifikation UNTEN Zug 'm' ---------------------*/
    i = yMove+1;
    /*Es verschiebt sich nach unten, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i<8 && board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)!=colorMove )
    {
        i++;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i<8 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i--;//Neuausrichtung auf das erste gegnerische Feld (der erste oben ...)
            while( i>yMove )
            {
                turnDownPawn(xMove,i);
                this->updateScore();  //Anpassen der Spielstände
                i--;  //Es geht in das nächste Feld nach oben
            }
        }
    }
}


//Update der Spielfiguren auf den Diagonalen des gespielten Zugs
void ai::updateDiagonal(imove m)
{
    //Rückgewinnung Koordinaten des Zuges
    int xMove = m.getX(),
        yMove = m.getY();
    //Wiederherstellung der Farbe
    ColorPawn colorMove = m.getColor();

    int i,j; //Indexbegriff


/*--------------- Verifikation Diagonale OBEN LINKS Zug 'm' ---------------------*/
    i = xMove-1;
    j = yMove-1;
    /*Es verschiebt sich nach oben links, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i>=0 && j>=0 && board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)!=colorMove )
    {
        i--;
        j--;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i>=0 && j>=0 )
    {
        /*Überprüfen, ob das Feld einen Token-Player/Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i++; j++;//Neuausrichtung auf das erste gegnerische Feld (die erste unten rechts ...)
            while( i<xMove && j<yMove )
            {
                                turnDownPawn(i,j);
                this->updateScore();  //Anpassen der Spielstände
                i++; j++; //Es geht in das nächste Feld nach unten rechts
            }
        }
    }

/*--------------- Verifikation UNTEN RECHTS Zug 'm' ---------------------*/
    i = xMove+1;
    j = yMove+1;

    /*Es verschiebt sich nach unten rechts, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i<8 && j<8 && board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)!=colorMove )
    {
        i++;
        j++;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i<8 && j<8 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i--;  j--;//Neuausrichtung auf das erste gegnerische Feld (die erste oben links ...)
            while( i>xMove && j>yMove )
            {
                turnDownPawn(i,j);
                this->updateScore();  //Anpassen der Spielstände
                i--;  j--;//Es geht in das nächste Feld nach oben links
            }
        }
    }

/*--------------- Verifikation OBEN RECHTS Zug 'm' ---------------------*/
    i = xMove+1;
    j = yMove-1;
    /*Es verschiebt sich nach oben rechts, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i<8 && j>=0 && board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)!=colorMove )
    {
        i++;
        j--;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i<8 && j>=0 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i--; j++;//Neuausrichtung auf das erste gegnerische Feld (die erste unten links ...)
            while( i>xMove && j<yMove )
            {
                turnDownPawn(i,j);
                this->updateScore();  //Anpassen der Spielstände
                i--; j++; //Es geht in das nächste Feld nach unten links
            }
        }
    }

/*--------------- Verifikation UNTEN LINKS Zug 'm' ---------------------*/
    i = xMove-1;
    j = yMove+1;

    /*Es verschiebt sich nach unten links, was immer noch das Board und das Feld von einer gegnerischen Figur enthält*/
    while( i>=0 && j<8 && board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)!=colorMove )
    {
        i--;
        j++;
    }
    /*Überprüfen, ob man noch auf dem Brett ist*/
    if( i>=0 && j<8 )
    {
        /*Überprüfen, ob das Feld eine Spielfigur des Spielers enthält*/
        if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
        {
            /*Gegnerischen Figuren sind umrahmt, sie können die Spielfiguren im Feld zurückspielen*/
            i++;  j--;//Neuausrichtung auf das erste gegnerische Feld (die erste oben rechts ...)
            while( i<xMove && j>yMove )
            {
                turnDownPawn(i,j);
                this->updateScore();  //Anpassen der Spielstände
                i++;  j--;//Es geht in das nächste Feld nach oben rechts
            }
        }
    }
}


void ai::updateScore()
{
    if( currentPlayer == p1 )
    {
        playerTable[p1]->increaseScore();
        playerTable[p2]->decreaseScore();
    }
    else
    {
        playerTable[p1]->decreaseScore();
        playerTable[p2]->increaseScore();
    }
}


void ai::turnDownPawn(int x, int y)
{
        board->turnDownPawn(x,y);
        savePawnTurnedDown(x,y);
}


void ai::definingRegularMoves()
/*Strecken des Spielbretts und Berechnung der Anzahl der legalen Spielzüge für alle Spieler*/
{
    ColorPawn colorTmp;
    bool WhiteRegularMove = false,  //Lässt nicht zu, dass ein legaler Zug mehrfach für einen Spieler gezählt wird
         BlackRegularMove = false;

    //Reset (RAZ) der legalen Züge eines jeden Spielers
    playerTable[p1]->RazNumMoves();
    playerTable[p2]->RazNumMoves();
    //Reset (RAZ) der Liste der legalen Züge
    regularMovesListTemp.clear();


    /************ Berechnung der legalen Spielzüge auf dem Brett ********/
    for( int y=0 ; y<8 ; y++ )
    {
        for( int x=0 ; x<8 ; x++ )
        {

/*********** Strecke aller Felder auf dem Brett ********************/

            //Wenn das Feld leer ist = möglicher legaler Zug
            if( board->getTypeSquareBoard(x,y)==Empty )
            {

                //Reset (RAZ) der Indikatoren des legalen Zugs für das Feld
                BlackRegularMove = false;
                WhiteRegularMove = false;


/*********** Strecken der Nachbar-Felder *********************/
                for( int j=-1 ; j<2 ; j++ )
                {

                    if( (y+j)>=0 && (y+j)<8 )  //wenn es die Tabelle ist
                    {
                        for( int i=-1 ; i<2 ; i++ )
                        {
                            if( (x+i)>=0 && (x+i)<8 )  //wenn es die Tabelle ist
                            {

                                if( !(i==0 && j==0) )  //Man überprüft das Feld nicht selbst
                                {

                                    //Überprüft, ob das Feld ist ein legaler Zug für den Linienvektor (i,j)
                                    if( checkRegularMove(x, y, i, j) )
                                    {
                                        //Wiederherstellung der Farbe gerahmter Spielfiguren
                                        colorTmp = board->getColorPawnBoard(x+i,y+j);
                                        //Wenn die gerahmten Spielfiguren weiß sind und das Schwarze immer noch kein legaler/gültiger Zug auf diesem Feld ist
                                        if( colorTmp == White && !BlackRegularMove )
                                        {
                                            //gültiger Zug schwarz
                                            BlackRegularMove = true;
                                            increaseRegularMove(Black);
                                            //Hinzugefügt eines gültigen Zugs in der temporären Liste
                                            regularMovesListTemp.push_back( imove(x,y,Black) );
                                        }
                                        //Wenn die gerahmten Spielfiguren schwarz sind und das Weiße immer noch kein gültiger Zug auf diesem Feld ist
                                        else if( colorTmp == Black && !WhiteRegularMove )
                                        {
                                            //gültiger Zug weiß
                                            WhiteRegularMove = true;
                                            increaseRegularMove(White);
                                            //Hinzugefügt eines gültigen Zuges in der temporären Liste
                                            regularMovesListTemp.push_back( imove(x,y,White) );
                                        }

                                        //Prüft, ob die zwei Farben einen gültigen Zug für dieses Feld haben
                                        //In diesem Fall ist es abgeschlossen für dieses Feld
                                        if( BlackRegularMove && WhiteRegularMove )
                                        {
                                            i=2;  j=2;  //Unterbrechung von Schleifen ...
                                        }
                                    }
                                }

                            }
                        }
                    }

                }  //Ende Strecke benachbarter Quadrate

            }
        }
    }  //End Strecke des Brettes
}



//Update der gültigen Züge, welche in 'regularMovesList' enthalten sind
void ai::updateRegularMove()
{
    for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
    {
        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
        {
            board->addRegularMove( regularMovesListTemp[i].getX(), regularMovesListTemp[i].getY() );
        }
    }
}


void ai::increaseRegularMove(ColorPawn color)
{
    if( playerTable[p1]->getColor() == color )
    {
        playerTable[p1]->increaseRegularMove();
    }
    else
    {
        playerTable[p2]->increaseRegularMove();
    }
}



/*Verifikation/Überprüfung eines legalen Zugs nach mehreren Parametern ...
  Prüft, ob die Felder des Brettes (start von dem Feld [squareX,squareY]) entlang der Linie
  (i,j) eine Stellung für einen gültigen Zug darstellt.
*/
bool ai::checkRegularMove(int squareX, int squareY, int i, int j)
{
    bool ret = false,  //Wert zurück
         done = false; //Schleifenende
    int x = squareX + i,
        y = squareY + j;

    //Überprüft, ob das nächste Feld belegt ist
    if( board->getTypeSquareBoard(x,y)==Occupied )
    {
        ColorPawn colorTmp = board->getColorPawnBoard(x,y);
        x += i;
        y += j;
        while( x>=0 && x<8 && y>=0 && y<8 && !done)
        {
            if( board->getTypeSquareBoard(x,y)==Occupied )  //Wenn Feld besetzt
            {
                if( board->getColorPawnBoard(x,y)==colorTmp )
                {
                    x += i;
                    y += j;
                }
                else  //Spielfigur einer anderen Farbe --> gültiger Zug
                {
                    ret = true;
                    done = true;
                }
            }
            else  //Feld leer --> kein gültiger Zug
            {
                done = true;
            }
        }
    }
    return ret;
}


void ai::initializationScorePattern()
{
        for( int x=0 ; x<8 ; x++ )
                for( int y=0 ; y<8 ; y++ )
                        scorePattern[x][y] = 0;

        //Coins
        scorePattern[0][0]=500;  scorePattern[0][7]=500;  scorePattern[7][0]=500;  scorePattern[7][7]=500;

        scorePattern[1][1]=-250;  scorePattern[1][6]=-250;  scorePattern[6][1]=-250;  scorePattern[6][6]=-250;

        scorePattern[0][1]=-150;  scorePattern[0][6]=-150;  scorePattern[1][0]=-150;  scorePattern[1][7]=-150;
        scorePattern[6][0]=-150;  scorePattern[6][7]=-150;  scorePattern[7][1]=-150;  scorePattern[7][6]=-150;

        scorePattern[0][2]=30;  scorePattern[0][5]=30;  scorePattern[2][0]=30;  scorePattern[2][7]=30;
        scorePattern[5][0]=30;  scorePattern[5][7]=30;  scorePattern[7][2]=30;  scorePattern[7][5]=30;

        scorePattern[0][3]=10;  scorePattern[0][4]=10;  scorePattern[3][0]=10;  scorePattern[3][7]=10;
        scorePattern[4][0]=10;  scorePattern[4][7]=10;  scorePattern[7][3]=10;  scorePattern[7][4]=10;

        scorePattern[3][3]=16;  scorePattern[3][4]=16;  scorePattern[4][3]=16;  scorePattern[4][4]=16;

        scorePattern[3][2]=2;  scorePattern[4][2]=2;  scorePattern[3][5]=2;  scorePattern[4][5]=2;
        scorePattern[2][3]=2;  scorePattern[2][4]=2;  scorePattern[5][3]=2;  scorePattern[5][4]=2;

        scorePattern[2][2]=1;  scorePattern[2][5]=1;  scorePattern[5][2]=1;  scorePattern[5][5]=1;
}


void ai::initializationSavingMove()
{
        if( movesSavedList.size() != numCurrentMove )  //Wenn der Vektor mehr als einmal, die Anzahl eines üblich Zugs
        {
                movesSavedList.erase(movesSavedList.begin()+numCurrentMove, movesSavedList.end() );
        }
        //Hinzufügen eines infosMoves am Ende
        movesSavedList.push_back( infosMoves() );
}


void ai::addMoveList(imove m)
{
        //Wenn numCurrentMove mit dem letzten Zug nicht übereinstimmt, werden die Bewegungen eliminiert
        if( numCurrentMove != movesList.size() )
        {
                movesList.erase( movesList.begin()+numCurrentMove, movesList.end() );
        }
        //Update der Anzahl des Spielzugs
        m.setNumMove( numCurrentMove + 1 );
        //Hinzufügen des Zugs an das Ende der Liste
        movesList.push_back(m);
}


void ai::nextPlayer()
{
    if( currentPlayer == p1 )
    {
        currentPlayer = p2;
    }
    else
    {
        currentPlayer = p1;
    }
}

void ai::saveCurrentPlayer()
{
        movesSavedList[numCurrentMove].saveCurrentPlayer(currentPlayer);
}


//regelmäßiges Speichern der Spielzüge des aktuellen Spielzugs
void ai::saveRegularMoves()
{
        movesSavedList[numCurrentMove].saveRegularMoves(regularMovesListTemp);
}


void ai::savePawnTurnedDown(int x, int y)
{
        movesSavedList[numCurrentMove].addPawnsTurnedDown( imove(x,y) );
}


void ai::affiche_movesPlay()
{
        cout << "       *** movesPlay: " << endl;
        for( int i=0 ; i<movesPlay.size() ; i++ )
        {
                movesPlay[i].affichage();
        }
}


infoAI ai::alphaBeta(int depth, infoAI alpha, infoAI beta)
{
        cptAlphaBeta++;
//      cout << "cptAlphaBeta=" << cptAlphaBeta << endl;

        if ( isFinished )  //Wenn das Spiel vorbei ist
        {
                return getScore();
        }
        else if( depth == 0 )  // Wenn die Maximaltiefe erreicht ist
        {
                return evaluateGameEvolutive();
        }

        infoAI result;
        if( idEvaluationPlayer == playerTable[currentPlayer]->getId() )  // node MAX = Program
        {
//              cout << "       movesPlay size: " << movesPlay.size() << endl;
                for ( int i=0 ; i<movesPlay.size() ; i++ )
                {
//                      cout <<         "       !!!! eval de";
//                      movesPlay[i].affichage();

                        playMove( movesPlay[i] );  //Spiele des Zug i
                        result = alphaBeta( depth - 1, alpha, beta );
                        undoLastMove();  //Annuliere den letzten Zug

//                      cout << "            Score= " << result.getScore() << endl;

                        if( result.getScore() > alpha.getScore() )
                        {
                                alpha.setScore( result.getScore() );
                                alpha.setMove( movesPlay[i] );
//                              cout << "               AlphaScore= " << alpha.getScore() << endl;
//                              cout << "               AlphaMove= ";

                                if( alpha.getScore() >= beta.getScore() )  // alpha break/Pause
                                {
//                                      cout << "-------- Alpha Break ------------" << endl;
                                        alphabreak++;
                                        break;
                                }
                        }
                }

                return alpha ;
        }
        else  // node MIN = opponent
        {
//              cout << "       movesPlay size: " << movesPlay.size() << endl;
                for ( int i=0 ; i<movesPlay.size() ; i++ )
                {
//                      cout <<         "       !!!! eval de";
                        playMove( movesPlay[i] );  //Spiele den Zug i
                        result = alphaBeta( depth - 1, alpha, beta );
                        undoLastMove();  //Annuliere den letzten Zug

//                      cout << "            Score= " << result.getScore() << endl;

                        if( result.getScore() < beta.getScore() )
                        {
                                beta.setScore( result.getScore() );
                                beta.setMove( movesPlay[i] );
//                              cout << "               BetaScore= " << beta.getScore() << endl;
//                              cout << "               BetaMove= ";

                                if( alpha.getScore() >= beta.getScore() )  // beta break/Pause
                                {
//                                      cout << "-------- Beta Break ------------" << endl;
                                        betabreak++;
                                        break;
                                }
                        }
                }
                return beta;
        }
}
