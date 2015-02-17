#include <QtGui>
#include "listmoves.h"
#include "game.h"
#include "player.h"
#include <QMainWindow>
#include <QApplication>

ListMoves::ListMoves(QWidget *parent)
        : QWidget(parent)
{
        initComponent();
        this->setLayout(mainLayout);
        this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
}

ListMoves::~ListMoves()
{
}

void ListMoves::initComponent()
{
    movesListLabel = new QLabel( tr("<b>List of played moves</b>") );
    listMoves = new QTextEdit( "" );
    listMoves->setReadOnly(true);
    listMoves->setMaximumWidth(145);
    listMoves->setMaximumHeight(768);
    mainLayout = new QGridLayout();
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(movesListLabel,0,0);
    mainLayout->addWidget(listMoves,1,0,1,1);
}

void ListMoves::setListMoves( QString list )
{
        listMoves->setText( list );
}

void ListMoves::connecting( game* ge )
{
        playerTable = ge->getPlayer();

        connect( ge, SIGNAL( movesListModified(QString) ), this, SLOT( setListMoves(QString) ) );
}

Player* ListMoves::getPlayer( int id )
{
        return playerTable[id];
}
