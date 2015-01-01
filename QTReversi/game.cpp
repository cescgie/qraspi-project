#include "game.h"

//Constructeur
game::game()
{
    numCurrentMove = 0;
    board = new Board();
    playerTable[p1] = new Player(p1, tr("Player 1"), Local, Black);
    playerTable[p2] = new Player(p2, tr("Player 2"), Local, White);
    clearMovesList();
    regularMovesListTemp.clear();
    currentPlayer = p1;
    isFinished = false;
    movesSavedList.clear();

    //Initialisiert SpielZuege regelmaeﬂig in regularMovesList, für die Sicherung/Speicherung des ersten Zugs ...
    regularMovesListTemp.push_back( move(2,3,Black) );
    regularMovesListTemp.push_back( move(3,2,Black) );
    regularMovesListTemp.push_back( move(4,5,Black) );
    regularMovesListTemp.push_back( move(5,4,Black) );
    regularMovesListTemp.push_back( move(5,3,White) );
    regularMovesListTemp.push_back( move(4,2,White) );
    regularMovesListTemp.push_back( move(2,4,White) );
    regularMovesListTemp.push_back( move(3,5,White) );

    redoAllowed = false;
    undoAllowed = false;
}

game::~game()
{
    delete board;
    delete playerTable[p1];
    delete playerTable[p2];
}

void game::startGame()
{
    askMove();
}


Board* game::getBoard()
{
    return board;
}

Player* game::getPlayer( int id )
{
    return playerTable[id];
}


Player** game::getPlayer()
{
    return playerTable;
}

vector<move> game::getMovesList()
{
    return movesList;
}

vector<move> game::getRegularMovesListTemp()
{
    return regularMovesListTemp;
}

int game::getCurrentPlayer()
{
    return currentPlayer;
}

void game::initializationDisplay()
{
    playerInitializationDisplay();
    updatingMovesListDisplay();
}

void game::initialization()
{
    board->initialization();
    playerTable[p1]->initialization();
    playerTable[p2]->initialization();
    clearMovesList();
    regularMovesListTemp.clear();
    currentPlayer = p1;
    isFinished = false;
    numCurrentMove = 0;
    movesSavedList.clear();

    //Initialisiert die SpielZuege regelmaeﬂig in regularMovesList für die Speicherung des ersten Zugs...
    regularMovesListTemp.push_back( move(2,3,Black) );
    regularMovesListTemp.push_back( move(3,2,Black) );
    regularMovesListTemp.push_back( move(4,5,Black) );
    regularMovesListTemp.push_back( move(5,4,Black) );
    regularMovesListTemp.push_back( move(5,3,White) );
    regularMovesListTemp.push_back( move(4,2,White) );
    regularMovesListTemp.push_back( move(2,4,White) );
    regularMovesListTemp.push_back( move(3,5,White) );

    updatingScoreDisplay();
    updatingNumMovesDisplay();

    askMove();
}



void game::recupMove(int x,int y)
{
    emit enableUndoMoveAction(false);
    emit enableRedoMoveAction(false);
    playMove( move(x,y) );
}

void game::nextTurn()
{
    if( getIsFinished() )
    {
        whoWins();
    }
    else
    {
        askMove();
    }
}

void game::setIsFinished(bool b)
{
    isFinished = b;
}

bool game::getIsFinished()
{
    return isFinished;
}

void game::nextPlayer()
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

bool game::playMove(move m)
{
    bool ret;   //value returned

    m.setColor( playerTable[currentPlayer]->getColor() );
    ret = board->addPawn( m.getX(), m.getY(), m.getColor() );

    if( ret )
    {
        initializationSavingMove();

        playerTable[currentPlayer]->increaseScore();
        addMoveList(m);
        updateGame(m);
        updatingScoreDisplay();

        nextPlayer();

        definingRegularMoves();
        updatingNumMovesDisplay();

        if( playerTable[currentPlayer]->getNumMoves() == 0 )
        {
            nextPlayer();
            if( playerTable[currentPlayer]->getNumMoves() == 0 )
            {
                isFinished = true;
            }
        }

        if( !isFinished )
        {
            updateRegularMove();
            saveCurrentPlayer();
            saveRegularMoves();

            numCurrentMove ++;
        }

        affichageMovesList();
        affichageSavedList();

        boardHasModified();
        undoAllowed = true;
    }
    else
    {
        askMove();
    }
    return ret;
}

//Definition der gültigen Spielzüge
void game::definingRegularMoves()
/*Durchlaufe das Spielbrett und zaehle die Anzahl der gueltigen Zuege fuer jeden eingetragenen Spieler*/
{
    ColorPawn colorTmp;
    bool WhiteRegularMove = false,  //laesst keine gueltigen Zuege mehrfach fuer einen Spieler zu
         BlackRegularMove = false;

    //Reseten von gueltigen Spielzuegen eines jeden Spielers
    playerTable[p1]->RazNumMoves();
    playerTable[p2]->RazNumMoves();
    //Reseten der Liste der gueltigen Spielzuege
    regularMovesListTemp.clear();


    /************ Berechnung der gueltigen Spielzuege auf dem Spielbrett ********/
    for( int y=0 ; y<8 ; y++ )
    {
        for( int x=0 ; x<8 ; x++ )
        {

    /*********** Durchlaufen aller Felder auf dem Brett ********************/

                        //Wenn das Feld leer ist = gueltiger Zug moeglich
            if( board->getTypeSquareBoard(x,y)==Empty )
            {

                //Reseten der Indikatoren eines gueltigen Zueges im Feld
                BlackRegularMove = false;
                WhiteRegularMove = false;


                /*********** Durchlaufe Nachbarfelder *********************/
                for( int j=-1 ; j<2 ; j++ )
                {
                    //ueberprueft, ob das Feld ein gueltiger Zug für den Vektor (i,j) ist

                    if( (y+j)>=0 && (y+j)<8 )
                    {
                        for( int i=-1 ; i<2 ; i++ )
                        {
                            if( (x+i)>=0 && (x+i)<8 )
                            {

                                if( !(i==0 && j==0) )
                                {

                                    //ueberprueft, ob das Feld ein gueltiger Zug für den Vektor (i,j) ist
                                    if( checkRegularMove(x, y, i, j) )
                                    {
                                        //Wiederherstellung der Farbe der gerahmten Spielfiguren
                                        colorTmp = board->getColorPawnBoard(x+i,y+j);
                                        //Wenn die Spielfiguren weiﬂ sind und das Schwarze immer noch kein gueltiger Zug dieses Feld ist
                                        if( colorTmp == White && !BlackRegularMove )
                                        {
                                            //gueltiger Zug schwarz
                                            BlackRegularMove = true;
                                            increaseRegularMove(Black);
                                            //Hinzufuegen eines gueltigen Zugs auf der temporaeren Liste
                                            regularMovesListTemp.push_back( move(x,y,Black) );
                                        }
                                        //Wenn die Spielfiguren schwarz sind und die Weißen immer noch kein gültiger Zug dieses Feld sind
                                        else if( colorTmp == Black && !WhiteRegularMove )
                                        {
                                            //gueltiger Zug weiss
                                            WhiteRegularMove = true;
                                            increaseRegularMove(White);
                                            //Hinzufuegen eines gueltigen Zugs auf der temporaeren Liste
                                            regularMovesListTemp.push_back( move(x,y,White) );
                                        }

                                        //Prueft, ob zwei Farben einen gueltigen Zug auf dem Feld haben
                                        //In diesem Fall ist es beendet/abgeschlossen fuer dieses Feld
                                        if( BlackRegularMove && WhiteRegularMove )
                                        {
                                            i=2;  j=2;  //Unterbrechung von Schleifen ...
                                        }
                                    }
                                }

                            }
                        }
                    }

                }  //End Pfad/Strecke benachbarter Felder

            }
        }
    }  //End Pfad/Strecke des Spielbretts
}

void game::updateRegularMove()
{
    for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
    {
        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
        {
            board->addRegularMove( regularMovesListTemp[i].getX(), regularMovesListTemp[i].getY() );
        }
    }
}

void game::increaseRegularMove(ColorPawn color)
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

bool game::checkRegularMove(int squareX, int squareY, int i, int j)
{
    bool ret = false,  //value returned
         done = false; //end of boucle
    int x = squareX + i,
        y = squareY + j;

    if( board->getTypeSquareBoard(x,y)==Occupied )
    {
        ColorPawn colorTmp = board->getColorPawnBoard(x,y);
        x += i;
        y += j;
        while( x>=0 && x<8 && y>=0 && y<8 && !done)
        {
            if( board->getTypeSquareBoard(x,y)==Occupied )
            {
                if( board->getColorPawnBoard(x,y)==colorTmp )
                {
                    x += i;
                    y += j;
                }
                else
                {
                    ret = true;
                    done = true;
                }
            }
            else
            {
                done = true;
            }
        }
    }
    return ret;
}

void game::turnDownPawn(int x, int y)
{
    board->turnDownPawn(x,y);
    savePawnTurnedDown(x,y);
}

void game::addMoveList(move m)
{
    if( numCurrentMove != movesList.size() )
    {
        movesList.erase( movesList.begin()+numCurrentMove, movesList.end() );
    }
    m.setNumMove( numCurrentMove + 1 );
    movesList.push_back(m);
    updatingMovesListDisplay();
}

void game::clearMovesList()
{
    movesList.clear();
    updatingMovesListDisplay();
}

void game::updateScore()
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

bool game::updateGame(move m)
{
    updateRow(m);
    updateColumn(m);
    updateDiagonal(m);
}

//Update der Spielfiguren von der Linie des Spielzugs
void game::updateRow(move m)
{
    //Rueckgewinnung/Wiedererlangung Spielzug (coord du coup)
    int xMove = m.getX(),
        yMove = m.getY();
    //Rueckgewinnung/Wiedererlangung der Farbe
    ColorPawn colorMove = m.getColor();

    int i; //Indexbegriff


    /*--------------- Verifikation LINKS des Zugs 'm' ---------------------*/
        i = xMove-1;
        /*Es verschiebt sich nach links, was immer noch das Brett und das Feld von eines gegnerischen Stein enthaelt*/
        while( i>=0 && board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)!=colorMove )
        {
            i--;
        }
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i>=0 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i++;//Es ist auf das erste gegnerische Feld ausgerichtet (zuerst nach rechts)
                while( i<xMove )
                {
    //                board->turnDownPawn(i,yMove);  //Umdrehen des Steines
                    turnDownPawn(i,yMove);  //Umdrehen des Steines
                    this->updateScore();  //aktualisieren der Spielstaende
                    i++;  //Es geht in das naechste Feld rechts
                }
            }
        }

    /*--------------- Verifikation RECHTS des Zugs 'm' ---------------------*/
        i = xMove+1;
        /*Es verschiebt sich nach rechts, was immer noch das Brett und das Feld von eines gegnerischen Stein enthaelt*/
        while( i<8 && board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)!=colorMove )
        {
            i++;
        }
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i<8 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(i,yMove)==Occupied && board->getColorPawnBoard(i,yMove)==colorMove )
            {
                 /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i--;//Es ist auf das erste gegnerische Feld ausgerichtet (zuerst nach rechts)
                while( i>xMove )
                {
    //                board->turnDownPawn(i,yMove);  //Umdrehen des Steines
                                    turnDownPawn(i,yMove);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i--;  //Es geht in das nächste Feld links
                }
            }
        }
    }


//Aktualisiert die Spielsteine der Reihe des Spielzuges
void game::updateColumn(move m)
{
    //Wiederherstellung des Zuges
        int xMove = m.getX(),
            yMove = m.getY();
        //Wiederherstellung der Farbe
        ColorPawn colorMove = m.getColor();

        int i; //Indexbegriff


    /*--------------- Verifikation OBEN des Zuges 'm' ---------------------*/
        i = yMove-1;
        /*Es verschiebt sich nach oben, was immer noch das Brett und das Feld von eines gegnerischen Stein enthaelt*/
        while( i>=0 && board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)!=colorMove )
        {
            i--;
        }
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i>=0 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i++;//Es ist auf das erste gegnerische Feld ausgerichtet (zuerst nach oben)
                while( i<yMove )
                {
    //                board->turnDownPawn(xMove,i);  //Umdrehen des Steines
                                    turnDownPawn(xMove,i);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i++;  //Es geht in das nächste Feld nach unten
                }
            }
        }

    /*--------------- Verifikation UNTEN des Zuges 'm' ---------------------*/
        i = yMove+1;
        /*Es verschiebt sich nach unten, was immer noch das Brett und das Feld von eines gegnerischen Stein enthaelt*/
        while( i<8 && board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)!=colorMove )
        {
            i++;
        }
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i<8 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(xMove,i)==Occupied && board->getColorPawnBoard(xMove,i)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i--;//Neuausrichtung auf das erste gegnerische Feld (der erste oben ...)
                while( i>yMove )
                {
    //                board->turnDownPawn(xMove, i);  //Umdrehen des Steines
                    turnDownPawn(xMove,i);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i--;  //Es geht in das nächste Feld nach oben
                }
            }
        }
    }

//Update der Spielfiguren auf den Diagonalen des gespielten Zugs
void game::updateDiagonal(move m)
{
    //Wiederherstellung des Zuges
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
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i>=0 && j>=0 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i++; j++;//Neuausrichtung auf das erste gegnerische Feld (die erste unten rechts ...)
                while( i<xMove && j<yMove )
                {
    //                board->turnDownPawn(i,j);  //Umdrehen des Steines
                                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
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
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i<8 && j<8 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i--;  j--;//Neuausrichtung auf das erste gegnerische Feld (die erste oben links ...)
                while( i>xMove && j>yMove )
                {
    //                board->turnDownPawn(i, j);  //Umdrehen des Steines
                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
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
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i<8 && j>=0 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i--; j++;//Neuausrichtung auf das erste gegnerische Feld (die erste unten links ...)
                while( i>xMove && j<yMove )
                {
    //                board->turnDownPawn(i,j);  //Umdrehen des Steines
                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
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
        /*ueberpruefen, ob man noch auf dem Brett ist*/
        if( i>=0 && j<8 )
        {
            /*ueberpruefen, ob das Feld ein Stein des Spielers enthaelt*/
            if ( board->getTypeSquareBoard(i,j)==Occupied && board->getColorPawnBoard(i,j)==colorMove )
            {
                /*Gegnerische Figuren sind umrahmt, sie koennen die Steine im Feld zurueckspielen*/
                i++;  j--;//Neuausrichtung auf das erste gegnerische Feld (die erste oben rechts ...)
                while( i<xMove && j>yMove )
                {
    //                board->turnDownPawn(i, j);  //Umdrehen des Steines
                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i++;  j--;//Es geht in das nächste Feld nach oben rechts
                }
            }
        }
    }





void game::askMove()
{

    if( currentPlayer == p1 )
    {
        emit sendInfosGameDisplay(P1_Playing);
    }
    else
    {
        emit sendInfosGameDisplay(P2_Playing);
    }

    switch( playerTable[currentPlayer]->getType() )
    {
        case Local:
            emit enableRedoMoveAction(redoAllowed);
            emit enableUndoMoveAction(undoAllowed);
            emit askingLocalMove();
            break;
        case AI_1:
        case AI_2:
        case AI_3:
            emit askingAIMove(this);
            break;
        default:
            break;
    }
}



void game::whoWins()
{
    if( playerTable[p1]->getScore() > playerTable[p2]->getScore() )
    {
        emit playerWins( playerTable[p1] );
    }
    else if( playerTable[p1]->getScore() < playerTable[p2]->getScore() )
    {
        emit playerWins( playerTable[p2] );
    }
    else
    {
        emit playerWins( NULL );
    }

}



void game::updatingScoreDisplay()
{
    emit playerScoreModified();
}



void game::updatingNumMovesDisplay()
{
    emit playerNumMovesModified();
}



void game::updatingMovesListDisplay()
{

    QString str = "";
    if( movesList.empty() )
    {
        str = "No Moves played";
    }
    else
    {
        QString str_temp;
        vector<move>::iterator iv = movesList.begin();
        int coord;
       int borne = numCurrentMove+1;

        if( borne > movesList.size() )
        {
            borne = movesList.size();
        }
//-----------------------------------------------------------------//
        while( iv != (movesList.begin()+/*numCurrentMove+1*/borne) )
        {
            str_temp.setNum( iv->getNumMove() );
            str += str_temp;
            str += ":  ";
            coord = iv->getX();
            str += 'A' + coord;
            str_temp.setNum( iv->getY() + 1 );
            str += str_temp;
            str += "  ";
            if( iv->getColor() == Black )
            {
                str += "Black";
            }
            else
            {
                str += "White";
            }
            str += "\n";
            iv++;
        }
//-----/
    }
    emit movesListModified(str);
}



void game::playerInitializationDisplay()
{
    emit playerColorModified(playerTable[p1]);
    emit playerColorModified(playerTable[p2]);

    emit playerNameModified(playerTable[p1]);
    emit playerNameModified(playerTable[p2]);

    emit playerTypeModified(playerTable[p1]);
    emit playerTypeModified(playerTable[p2]);

}



void game::boardHasModified()
{
    emit boardModified();
}

void game::initializationSavingMove()
{
    if( movesSavedList.size() != numCurrentMove )
    {
        movesSavedList.erase(movesSavedList.begin()+numCurrentMove, movesSavedList.end() );
    }
    movesSavedList.push_back( InfosMoves() );
}



void game::savePawnTurnedDown(int x, int y)
{
    movesSavedList[numCurrentMove].addPawnsTurnedDown( move(x,y) );
}

void game::saveRegularMoves()
{
    movesSavedList[numCurrentMove].saveRegularMoves(regularMovesListTemp);
}

void game::saveCurrentPlayer()
{
    movesSavedList[numCurrentMove].saveCurrentPlayer(currentPlayer);
}

void game::affichageSavedList()
{
    cout << "#---- Saved List:" << endl;
    for( int i=0 ; i<movesSavedList.size() ; i++ )
    {
        cout << "\t" << i << ":" << endl;
        movesSavedList[i].affichage();
    }
}


        //-------------------------unred

void game::affichageMovesList()
{
    for( int i=0 ; i<movesList.size() ; i++ )
    {
        cout << "Move " << i << " : ";
        movesList[i].affichage();
    }
}

void game::undoLastMove()
{
        if( numCurrentMove > 0 )
        {
                move moveTmp;
        //wird auf der vorherigen Spielzug neu ausgerichtet
                numCurrentMove--;
        //Holen den aktiven/aktuellen Player
                if( numCurrentMove == 0 ) //Konfigurieren des Starts
                {
                        //Der Spieler, der beginnt, ist der Spieler mit dem schwarzen Spielfiguren
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
        //-->sende 'aktiver Spieler' an Schnittstelle
        //Entfernen des letzen platzierten Spielers
                board->emptySquare(movesList[numCurrentMove].getX(),movesList[numCurrentMove].getY());
                playerTable[currentPlayer]->decreaseScore();  //Update der Spielstaende
        //Update des letzten Spielszugs auf dem Spielbrett, wenn er existiert
                if(numCurrentMove > 0)
                {
                        board->enableLastMoveSquare(movesList[numCurrentMove-1].getX(),movesList[numCurrentMove-1].getY());
                }
        //Wiederbringen der Spielfiguren
                for( int i=0 ; i<movesSavedList[numCurrentMove].getSizePawnsTurnedDownList() ; i++ )
                {
                        moveTmp = movesSavedList[numCurrentMove].getPawnsTurnedDownList(i);
                        board->turnDownPawn(moveTmp.getX(),moveTmp.getY());
                        //Update der Spielstaende
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
                board->clearAnimation();  //Keine Animation
        //Update der gueltigen SpielZuege
                board->clearRegularMove();
                regularMovesListTemp.clear();
                int numMovesCurPlayer = 0;
             //regelmaeﬂiges Abrufen/Rueckgewinnen der SpielZuege in 'regularMovesListTemp'
                if( numCurrentMove == 0 ) //Konfiguration des Starts
                {
                        regularMovesListTemp.push_back( move(2,3,Black) );
                        regularMovesListTemp.push_back( move(3,2,Black) );
                        regularMovesListTemp.push_back( move(4,5,Black) );
                        regularMovesListTemp.push_back( move(5,4,Black) );
                        regularMovesListTemp.push_back( move(5,3,White) );
                        regularMovesListTemp.push_back( move(4,2,White) );
                        regularMovesListTemp.push_back( move(2,4,White) );
                        regularMovesListTemp.push_back( move(3,5,White) );
                }
                else
                {
                        regularMovesListTemp = movesSavedList[numCurrentMove-1].getRegularMovesList();
                }
                //regelmaeﬂiges Update der Zuege aud dem Brett
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
        //Anzeige aktualisieren
        //Anzeige aktualisieren 'undoAction' and 'redoAction'
                redoAllowed = true;
                if( numCurrentMove == 0 )
                {
                        undoAllowed = false;
                }
        }
}


void game::redoLastMove()
{
        if( numCurrentMove < (movesList.size()) )  //Wenn ein Zug noch einmal gespielt wird
        {
                move moveTmp;
        //Hinzufuegen der zuletzt platzierten Spielfigur
                board->addPawn(movesList[numCurrentMove].getX(), movesList[numCurrentMove].getY(),playerTable[currentPlayer]->getColor() );
                playerTable[currentPlayer]->increaseScore();  //Update der Spielstaende
        //Wiederbringen der Spielfiguren
                for( int i=0 ; i<movesSavedList[numCurrentMove].getSizePawnsTurnedDownList() ; i++ )
                {
                        moveTmp = movesSavedList[numCurrentMove].getPawnsTurnedDownList(i);
                        board->turnDownPawn(moveTmp.getX(),moveTmp.getY());
                        //Update der Spielstaende
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
                board->clearAnimation();  //keine Animation
        //Holen/Wiederbringen des aktuellen Spielers
                currentPlayer = movesSavedList[numCurrentMove].getCurrentPlayer();
        //Speichern der gueltigen SpielZuege
                board->clearRegularMove();
                regularMovesListTemp.clear();
                //regelmaeﬂiges Kopieren der SpielZuege in 'regularMovesListTemp'
                regularMovesListTemp = movesSavedList[numCurrentMove].getRegularMovesList();
                int numMovesCurPlayer = 0;
                cout << "!!!! getSizeRegularMoveList()= " << movesSavedList[numCurrentMove].getSizeRegularMovesList() << endl;
//              int CPT = 0;
                //regelmaeﬂiges Anzeigen der SpielZuege auf dem board
                for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
                {
                        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
                        {
                                board->addRegularMove( regularMovesListTemp[i].getX(), regularMovesListTemp[i].getY() );
                                numMovesCurPlayer++;
                        }
                }
                //Update 'numMoves' der Spieler
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
        //bringen den naechsten Zug
                numCurrentMove++;
        //Update Anzeige 'undoAction' and 'redoAction'
                undoAllowed = true;
                if( numCurrentMove == (movesList.size()) )
                {
                        redoAllowed = false;
                }
        }
}

void game::undoMoveGlobal()
{
        //Ermitteln des Falls & Annulieren/stonieren der Zuege entsprechend
        int idTmp = p1;
        if( currentPlayer == p1 ) //Ruft die ID des langfristigen Spielers
        {
                idTmp = p2;
        }
        switch( playerTable[idTmp]->getType() )
        {
                case AI_1:
                case AI_2:
                case AI_3:
                        do
                        {
                                undoLastMove();
                        }
                        while( currentPlayer == idTmp && numCurrentMove != 0 ); //Tant que le joueur courant est l'IA ou ke l on revienne au premier coup
                        break;
                case Local:
                        undoLastMove();
                        break;
                default:
                        break;
        }
        //Update Anzeige
        updatingScoreDisplay();
        updatingNumMovesDisplay();
        updatingMovesListDisplay();
        boardHasModified();
        //Starten Sie das Spiel-Engine bekommen eine Chance auf eine angemessene Motor (Relancer le moteur de jeu en demandant un coup au moteur adÈquate)
        askMove();
}

void game::redoMoveGlobal()
{
        //Ermitteln des Falls & Annulieren/stonieren der Zuege entsprechend
        int idTmp = p1;
        if( currentPlayer == p1 ) //Ruft die ID des langfristigen Spielers
        {
                idTmp = p2;
        }
        switch( playerTable[idTmp]->getType() )
        {
                case AI_1:
                case AI_2:
                case AI_3:
                        do
                        {
                                redoLastMove();
                        }
                        while( currentPlayer == idTmp && numCurrentMove != movesList.size() ); //Tant que le joueur courant est l'IA ou ke l on revienne au premier coup
                        break;
                case Local:
                        redoLastMove();
                        break;
                default:
                        break;
        }
        //Update Anzeige
        updatingScoreDisplay();
        updatingNumMovesDisplay();
        updatingMovesListDisplay();
        boardHasModified();
        //Starten Sie das Spiel-Engine bekommen eine Chance auf eine angemessene Motor (Relancer le moteur de jeu en demandant un coup au moteur adÈquate)
        askMove();

}
