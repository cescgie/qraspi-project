#include "player.h"

//Default-Konstruktor
Player::Player( int id )
{
    this->id = id;
    name = "Player 1";
    type = Local;
    color = White;
    initialization();
}



//Konstruktor mit Parametern
Player::Player( int id, QString name, TypePlayer type, ColorPawn color )
{
        this->id = id;
        setName( name );
        setType( type );
        setColor( color );
    initialization();
}



//Wechsel Variable 'name'
void Player::setName(QString name)
{
    this->name = name;
}



//Wechsel Variable 'type'
void Player::setType(TypePlayer type)
{
    this->type = type;
}



//Wechsel Variable 'color'
void Player::setColor(ColorPawn color)
{
    this->color = color;
}



//Wechsel Variable 'score'
void Player::setScore(int score)
{
    this->score = score;
}



//Wechsel Variable 'numMoves'
void Player::setNumMoves(int num)
{
    this->numMoves = num;
}



//Zugriffsvariable 'Id'
int Player::getId()
{
        return id;
}



//Zugriffsvariable 'name'
QString Player::getName()
{
    return name;
}



//Zugriffsvariable 'type'
TypePlayer Player::getType()
{
    return type;
}



//Zugriffsvariable 'color'
ColorPawn Player::getColor()
{
    return color;
}



//Zugriffsvariable 'score'
int Player::getScore()
{
    return score;
}



//Zugriffsvariable 'numMoves'
int Player::getNumMoves()
{
    return numMoves;
}



//rücksetzen 'numMoves'
void Player::RazNumMoves()
{
        numMoves = 0;
}





//Initialisieren der Variablen 'Score', 'numMoves' von Spieler
void Player::initialization()
{
    setScore(2);
    setNumMoves(4);
}



//Erhoehen der Punkte
void Player::increaseScore()
{
        score++;
}



//Senken der Punkte
void Player::decreaseScore()
{
        if( score != 0 )
        {
                score--;
        }
}



//Erhoehen der "legalen Zuege"
void Player::increaseRegularMove()
{
    numMoves++;
}


