#include "game.h"
#include <sstream>
#include <QDebug>

//Konstruktor
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

    //Initialisiert Spielzuege regelmaessig in regularMovesList, fuer die Speicherung des ersten Zugs
        regularMovesListTemp.push_back( imove(2,3,Black) );
        regularMovesListTemp.push_back( imove(3,2,Black) );
        regularMovesListTemp.push_back( imove(4,5,Black) );
        regularMovesListTemp.push_back( imove(5,4,Black) );
        regularMovesListTemp.push_back( imove(5,3,White) );
        regularMovesListTemp.push_back( imove(4,2,White) );
        regularMovesListTemp.push_back( imove(2,4,White) );
        regularMovesListTemp.push_back( imove(3,5,White) );

        redoAllowed = false;
        undoAllowed = false;
 
        //sounds
        effectWhite.setSource(QUrl::fromLocalFile(":/sounds/stein2.wav"));
        effectBlack.setSource(QUrl::fromLocalFile(":/sounds/stein1.wav"));
        //effectError.setSource(QUrl::fromLocalFile(":/sounds/error.wav"));

        //QIntegerForSize *soundsValue = new QIntegerForSize();
        int soundsValue = 1.0f;
        effectWhite.setLoopCount(1);
        effectWhite.setVolume(soundsValue);
        effectBlack.setLoopCount(1);
        effectBlack.setVolume(1.0f);
        //effectError.setLoopCount(1);
        //effectError.setVolume(1.0f);

// cout << "regularMovesListTemp.size() = " << regularMovesListTemp.size() << endl;  
}

//Destruktor
game::~game()
{
        delete board;
        delete playerTable[p1];
        delete playerTable[p2];
}

//startet die Partie
void game::startGame()
{
        askMove();
}

//Zugriffsfunktion der Variable 'Board'
Board* game::getBoard()
{
        return board;
}



//Zugriffsfunktion der Variable 'player'
Player* game::getPlayer( int id )
{
        return playerTable[id];
}


Player** game::getPlayer()
{
        return playerTable;
}



//Zugriffsfunktion der Variable 'movesList'
vector<imove> game::getMovesList()
{
        return movesList;
}


               
//Zugriffsfunktion der Variable 'regularMovesListTemp'
vector<imove> game::getRegularMovesListTemp()
{
        return regularMovesListTemp;
}



//Zugriffsfunktion der Variable 'currentPlayer'
int game::getCurrentPlayer()
{
        return currentPlayer;
}



//Initialisierung der Anzeige
void game::initializationDisplay()
{
        playerInitializationDisplay();
        updatingMovesListDisplay();
}



/* Initialisierung der Variablen der Partie
**
** Initialisiert die Daten, um ein neues Spiel zu starten
*/
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
   
//Initialisiert die Spielzuege regelmae�ig in regularMovesList fuer die Speicherung des ersten Zugs
        regularMovesListTemp.push_back( imove(2,3,Black) );
        regularMovesListTemp.push_back( imove(3,2,Black) );
        regularMovesListTemp.push_back( imove(4,5,Black) );
        regularMovesListTemp.push_back( imove(5,4,Black) );
        regularMovesListTemp.push_back( imove(5,3,White) );
        regularMovesListTemp.push_back( imove(4,2,White) );
        regularMovesListTemp.push_back( imove(2,4,White) );
        regularMovesListTemp.push_back( imove(3,5,White) );

        redoAllowed = false;
        undoAllowed = false;

//Aktualisierung Anzeige
        updatingScoreDisplay();
        updatingNumMovesDisplay();
 
//Automatischer Neustart
        askMove();    
}



//Wiederherstellung des Spielzueges
void game::recupMove(int x,int y)
{      
//      cout << "Entre ds game::recupMove()" << endl;
        emit enableUndoMoveAction(false);
        emit enableRedoMoveAction(false);
        playMove( imove(x,y) );
}



//Startet den naechsten Zug, wenn die Partei nicht vorbei ist
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

//Wechsel 'isFinished'
void game::setIsFinished(bool b)
{
    isFinished = b;
}



//Zugriffsfunktion der Variable 'isFinished'
bool game::getIsFinished()
{
    return isFinished;
}



/* Naechster Spieler
**
** Aendert den aktuellen Spieler
*/
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



//Spiel eines Zueges in der Partie
/*Die Funtion stellt die Spielfigur des Spielzugs auf dem Brett dar. Wenn der Spielzug ungueltig ist, gibt die Funktion 'false' zurueck,
ansonsten wird der Spielstein gesetzt, das Brett und der Spielstand werden aktualisiert und die Funtion gibt'true' zurueck.
*/
bool game::playMove(imove m)
{
    bool ret;   //Wert zurueckgegeben
    //Wiederherstellung und aktualisieren der Farbe des gespielten Zueges
    m.setColor( playerTable[currentPlayer]->getColor() );
    //Hinzufuegen eines Spielsteins auf dem Brett
    ret = board->addPawn( m.getX(), m.getY(), m.getColor() );

    if( ret )  //Wenn Spielzug gueltig, dann...
    {
                redoAllowed = false;
//              enableRedoMoveAction(false);
        initializationSavingMove();  //Initialisierung der Liste der gespeicherten SpielZuege
//      saveRegularMoves();  //regelmae�iger Backup der Spielzuege
//      saveCurrentPlayer();  //Backup aktueller Spieler

        playerTable[currentPlayer]->increaseScore();  //1 pt neben der Spielfigur platzieren
        addMoveList(m);  //Hinzufuegen eines Spielzugs auf die Liste
        updateGame(m);  //Update der Spieldaten
        updatingScoreDisplay();  //Update der Anzeige des Spielstandes

        nextPlayer();  //naechster Spieler

        definingRegularMoves();  //Definition der neuen gueltigen Zuege
                updatingNumMovesDisplay();  //Update der Anzeige der gueltigen Zuege
               
        if( playerTable[currentPlayer]->getNumMoves() == 0 ) //Wenn der Spieler nicht spielen kann
        {
            nextPlayer();
            if( playerTable[currentPlayer]->getNumMoves() == 0 ) //Kein Spieler kann spielen
            {
                isFinished = true;
            }
        }

        if( !isFinished )
        {
            updateRegularMove();    //Aktualisierung der gueltigen Zuege des aktuellen Spielers
                        saveCurrentPlayer();
                        saveRegularMoves();  //regelmaessiges Backup der Spielzuege
                        //Update von 'numCurrentMove'
                        numCurrentMove ++;
        }
                boardHasModified();
                               
                undoAllowed = true;
    }
    else  //Zug ungueltig
    {
        askMove();
                 //Anzeige : "ungueltiger Zug... Wiederholen.
    }
    return ret;
}



//Definition der gueltigen Spielzuege
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


    //Berechnung der gueltigen Spielzuege auf dem Spielbrett
    for( int y=0 ; y<8 ; y++ )
    {
        for( int x=0 ; x<8 ; x++ )
        {

    //Durchlaufen aller Felder auf dem Brett

                        //Wenn das Feld leer ist = gueltiger Zug moeglich
            if( board->getTypeSquareBoard(x,y)==Empty )
            {

                //Reseten der Indikatoren eines gueltigen Zueges im Feld
                BlackRegularMove = false;
                WhiteRegularMove = false;


                //Durchlaufe Nachbarfelder
                for( int j=-1 ; j<2 ; j++ )
                {
                    //ueberprueft, ob das Feld ein gueltiger Zug fuer den Vektor (i,j) ist

                    if( (y+j)>=0 && (y+j)<8 )
                    {
                        for( int i=-1 ; i<2 ; i++ )
                        {
                            if( (x+i)>=0 && (x+i)<8 )
                            {

                                if( !(i==0 && j==0) )
                                {

                                    //ueberprueft, ob das Feld ein gueltiger Zug fuer den Vektor (i,j) ist
                                    if( checkRegularMove(x, y, i, j) )
                                    {
                                        //Wiederherstellung der Farbe der gerahmten Spielfiguren
                                        colorTmp = board->getColorPawnBoard(x+i,y+j);
                                        //Wenn die Spielfiguren wei� sind und das Schwarze immer noch kein gueltiger Zug dieses Feld ist
                                        if( colorTmp == White && !BlackRegularMove )
                                        {
                                            //gueltiger Zug schwarz
                                            BlackRegularMove = true;
                                            increaseRegularMove(Black);
                                            //Hinzufuegen eines gueltigen Zugs auf der temporaeren Liste
                                            regularMovesListTemp.push_back( imove(x,y,Black) );
                                        }
                                        //Wenn die Spielfiguren schwarz sind und die Weissen immer noch kein gueltiger Zug dieses Feld sind
                                        else if( colorTmp == Black && !WhiteRegularMove )
                                        {
                                            //gueltiger Zug weiss
                                            WhiteRegularMove = true;
                                            increaseRegularMove(White);
                                            //Hinzufuegen eines gueltigen Zugs auf der temporaeren Liste
                                            regularMovesListTemp.push_back( imove(x,y,White) );
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

                }  //Ende Strecke benachbarter Felder

            }
        }
    }  //Ende Strecke des Spielbretts
}



//Aktualisieren der gueltigen Zuege, welche in 'regularMovesList' enthalten sind
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



//Erhoehen eines gueltigen Zugs
//Funktion erhoeht die Anzahl der gueltigen Zuege des Spielers, dessen Farbe ist "color"
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



/*�berpruefung eines gueltigen Spielzugs nach mehreren Parametern...
  Prueft, ob die Felder des Spielbretts (� partir de la case [squareX,squareY]) entlang des Linienvektors
  (i,j) eine Konfiguration fuer einen gueltigen Spielzug darstellt/repraesentiert.*/
bool game::checkRegularMove(int squareX, int squareY, int i, int j)
{
    bool ret = false,  //value returned
         done = false; //end of boucle
    int x = squareX + i,
        y = squareY + j;

    //ueberprueft, ob das naechste Feld belegt ist
    if( board->getTypeSquareBoard(x,y)==Occupied )
    {
        ColorPawn colorTmp = board->getColorPawnBoard(x,y);
        x += i;
        y += j;
        while( x>=0 && x<8 && y>=0 && y<8 && !done)
        {
            if( board->getTypeSquareBoard(x,y)==Occupied )  //Wenn Feld belegt ist
            {
                if( board->getColorPawnBoard(x,y)==colorTmp )
                {
                    x += i;
                    y += j;
                }
                else  //Spielfigur einer anderen Farbe, gueltiger Zug
                {
                    ret = true;
                    done = true;
                }
            }
            else  //Feld leer, ungueltiger Zug
            {
                done = true;
            }
        }
    }
    return ret;
}



//dreht ein Stein
void game::turnDownPawn(int x, int y)
{
        board->turnDownPawn(x,y);
        savePawnTurnedDown(x,y);
}



/* Hinzufuegen einen Zugs 'm' in die Liste gespielter Zuege
**
** Abrufen der Anzahl der gespielten Zuege.
** Hinzufuegen Spielzugs am Ende des Vektors 'movesList'
*/
void game::addMoveList(imove m)
{
       
        //Wenn numCurrentMove nicht mit dem letzten gespielten Zug uebereinstimmt, werden die SpielZuege eliminiert
        if( numCurrentMove != movesList.size() )
        {
                movesList.erase( movesList.begin()+numCurrentMove, movesList.end() );
        }
        //Update der Nummer der gespielten Zuege
        m.setNumMove( numCurrentMove + 1 );
        //Hinzufuegen eines Spielzugs ans Ende der Liste
        movesList.push_back(m);
        //Aktualisierung der Anzeige
        updatingMovesListDisplay();
}

//Loescht die Liste der gespielten Zuege
void game::clearMovesList()
{
        movesList.clear();
        updatingMovesListDisplay();
}

/* Update der Spielstaende (aufgerufen, wenn ein Token des aktiven Spielers zurueck ist)
**
** Die Funktion fuegt einen Punkt auf den aktuellen Spieler hinzu und subtrahiert einen Punkt von seinen Gegner.
*/
void game::updateScore()
{
    if( currentPlayer == p1 )
    {
        playerTable[p1]->increaseScore();
        playerTable[p2]->decreaseScore();
        effectBlack.play();         //sounds
    }
    else
    {
        playerTable[p1]->decreaseScore();
        playerTable[p2]->increaseScore();
        effectWhite.play();         //sounds
    }
}

/* Update der Spielfiguren und der Spielstaende der Partie nach dem Spielzug 'm'
**
**
*/
bool game::updateGame(imove m)
{
    updateRow(m);
    updateColumn(m);
    updateDiagonal(m);
    return true;
}

//Update der Spielfiguren von der Linie des Spielzugs
void game::updateRow(imove m)
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
                                    turnDownPawn(i,yMove);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i--;  //Es geht in das naechste Feld links
                }
            }
        }
    }


//Aktualisiert die Spielsteine der Reihe des Spielzuges
void game::updateColumn(imove m)
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
                                    turnDownPawn(xMove,i);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i++;  //Es geht in das naechste Feld nach unten
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
                    turnDownPawn(xMove,i);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i--;  //Es geht in das naechste Feld nach oben
                }
            }
        }
    }

//Update der Spielfiguren auf den Diagonalen des gespielten Zugs
void game::updateDiagonal(imove m)
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
        /*Es verschiebt sich nach oben links, was immer noch das Board und das Feld von einer gegnerischen Figur enthaelt*/
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
                                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i++; j++; //Es geht in das naechste Feld nach unten rechts
                }
            }
        }

    /*--------------- Verifikation UNTEN RECHTS Zug 'm' ---------------------*/
        i = xMove+1;
        j = yMove+1;

        /*Es verschiebt sich nach unten rechts, was immer noch das Board und das Feld von einer gegnerischen Figur enthaelt*/
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
                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i--;  j--;//Es geht in das naechste Feld nach oben links
                }
            }
        }

    /*--------------- Verifikation OBEN RECHTS Zug 'm' ---------------------*/
        i = xMove+1;
        j = yMove-1;
       /*Es verschiebt sich nach oben rechts, was immer noch das Board und das Feld von einer gegnerischen Figur enthaelt*/
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
                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i--; j++; //Es geht in das naechste Feld nach unten links
                }
            }
        }

    /*--------------- Verifikation UNTEN LINKS Zug 'm' ---------------------*/
        i = xMove-1;
        j = yMove+1;

        /*Es verschiebt sich nach unten links, was immer noch das Board und das Feld von einer gegnerischen Figur enthaelt*/
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
                    turnDownPawn(i,j);
                    this->updateScore();  //aktualisieren der Spielstaende
                    i++;  j--;//Es geht in das naechste Feld nach oben rechts
                }
            }
        }
    }





void game::askMove()
{
        //Sendet msg aktuellen Spieler
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
                case Local:  //Wenn der aktuelle Spieler ein okaler Nutzer ist
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
    //erstellte Zeichenfolge anzeigen
           QString str = "";
   //      if( numCurrentMove == 0 )
           if( movesList.empty() )
       {
           str = "No Moves played";
       }
       //Wenn keine Rueckgewinnung des Namen des letzten Zugs und Erhoehung um 1
       else
       {
                   QString str_temp;
           vector<imove>::iterator iv = movesList.begin();
           int coord;
   // 'numCurrentMove'
   //--- Es wird nicht angezeigt ( borne-- ) es wurde abgesagt mit undoMove (dc si redoAllowed == true )...
                   int borne = numCurrentMove+1;
                   if( redoAllowed )
                   {
                           borne--;
                   }
                   //Um den Vektor im Speicher nicht zu ueberschreiten ...
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



//Initialisierung der Speicherung des aktuellen Zugs
void game::initializationSavingMove()
{
        if( movesSavedList.size() != numCurrentMove )  //Wenn der Vektor mehr SpielZuege enthaelt als die Anzahl eines aktuellen Spielzugs
        {
                //Entfernen zusaetzlicher Zuege
                movesSavedList.erase(movesSavedList.begin()+numCurrentMove, movesSavedList.end() );
        }
        //Hinzufuegen eines infosMoves am Ende
        movesSavedList.push_back( infosMoves() );
}



//Wieder Hinzufuegen einer Spielfigur in die Liste der Spielfiguren des aktuellen Zugs
void game::savePawnTurnedDown(int x, int y)
{
        movesSavedList[numCurrentMove].addPawnsTurnedDown( imove(x,y) );
}



//Regelmae�iges Speichern der Spielliste eines aktuellen Zugs
void game::saveRegularMoves()
{
        movesSavedList[numCurrentMove].saveRegularMoves(regularMovesListTemp);
}



//Speicher aktuellen Spieler
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


void game::undoLastMove()
{
        if( numCurrentMove > 0 )
        {
                imove moveTmp;
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
       //regelmae�iges Abrufen/Rueckgewinnen der SpielZuege in 'regularMovesListTemp'
                if( numCurrentMove == 0 ) //Konfiguration des Starts
                {
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
                //regelmae�iges Update der Zuege aud dem Brett
                for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
                {
                        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
                        {
                                board->addRegularMove( regularMovesListTemp[i].getX(), regularMovesListTemp[i].getY() );
                                numMovesCurPlayer++;
                        }
                }
               
//              cout << "!!!!! CPT= " << CPT << endl;
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
                imove moveTmp;
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
                //regelmae�iges Kopieren der SpielZuege in 'regularMovesListTemp'
                regularMovesListTemp = movesSavedList[numCurrentMove].getRegularMovesList();
                int numMovesCurPlayer = 0;
//              cout << "!!!! getSizeRegularMoveList()= " << movesSavedList[numCurrentMove].getSizeRegularMovesList() << endl;
//              int CPT = 0;
                //regelmae�iges Anzeigen der SpielZuege auf dem board
                for( int i=0 ; i<regularMovesListTemp.size() ; i++ )
                {
//                      CPT++;
                        if( regularMovesListTemp[i].getColor() == playerTable[currentPlayer]->getColor() )
                        {
                                board->addRegularMove( regularMovesListTemp[i].getX(), regularMovesListTemp[i].getY() );
                                numMovesCurPlayer++;
                        }
                }
//              cout << "!!!!! CPT= " << CPT << endl;
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
                //Update Anzeige
                //Update Anzeige 'undoAction' and 'redoAction'
                undoAllowed = true;
                if( numCurrentMove == (movesList.size()) )
                {
                        redoAllowed = false;
                }      
        }
}

void game::affichageMovesList()
{
        for( int i=0 ; i<movesList.size() ; i++ )
        {
                cout << "Move " << i << " : ";
                movesList[i].affichage();
        }
}

void game::undoMoveGlobal()
{
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
                        //Wenn der Gegner ein AI ist, man muss die SpielZuege rueckgaengig machen, sodass
                        // der aktuelle Spieler seinen letzten Spielzug rueckgaengig macht
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
        //Starten Sie das Spiel-Engine bekommen eine Chance auf eine angemessene Motor
        askMove();
}

void game::redoMoveGlobal()
{
        //Ermitteln des Falls & Annulieren der Zuege entsprechend
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
                        //Wenn der Gegner ein AI ist, man muss die SpielZuege annulieren/rueckgaengig machen, sodass
                        // der aktuelle Spieler seinen letzten Spielzug rueckgaengig macht
                        do
                        {
                                redoLastMove();
                        }
                        while( currentPlayer == idTmp && numCurrentMove != movesList.size() );
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
        askMove();

}

vector<infosMoves> game::getMovesSavedList()
{
        return movesSavedList;
}

int game::getNumCurrentMove()
{
        return numCurrentMove;
}

std::string game::toString(){
    std::stringstream result;

    result << currentPlayer << std::endl;
    result << numCurrentMove<< std::endl;
    result << isFinished << std::endl;


    return result.str();
}
void game::fromString(const std::string in){

    std::stringstream result(in);
    std::string status,player, fins;

    result.seekg(0,std::ios::beg);

    std::getline(result, player,'\n');
    currentPlayer = atoi(player.c_str());
    std::getline(result, status,'\n');
    numCurrentMove = atoi(status.c_str());
    std::getline(result, fins,'\n');
    isFinished = atoi(fins.c_str());


}

