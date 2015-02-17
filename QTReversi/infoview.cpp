#include <QtGui>
#include "infoview.h"
#include "game.h"
#include "player.h"
#include <QMainWindow>
#include <QApplication>

infoView::infoView(QWidget *parent)
        : QWidget(parent)
{
        initComponent();
        this->setLayout(mainLayout);
        this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
}


infoView::~infoView()
{
}

void infoView::initComponent()
{
    colorP1 = new QLabel( "" );
    colorP2 = new QLabel( "" );
    scoreP1Label = new QLabel( tr("Score") );
    scoreP2Label = new QLabel( tr("Score") );
    movesP1Label = new QLabel( tr("Moves") );
    movesP2Label = new QLabel( tr("Moves") );
    nameP1 = new QLabel( "" );
    nameP2 = new QLabel( "" );
    scoreP1 = new QLabel( "" );
    scoreP2 = new QLabel( "" );
    movesP1 = new QLabel( "" );
    movesP2 = new QLabel( "" );
    typeP1 = new QLabel("( )");
    typeP2 = new QLabel("( )");
    namepar1 = new QLabel("Name ");
    namepar2 = new QLabel("Name ");
    levelpar1  = new QLabel("Level ");
    levelpar2 = new QLabel("level ");

    dot1 = new QLabel(":");
    dot2 = new QLabel(":");
    dot3 = new QLabel(":");
    dot4 = new QLabel(":");
    dot5 = new QLabel(":");

    QPixmap pix(60,60);
    pix.fill(Qt::transparent);
    hit= new QPainter(&pix);
    hit->setBrush(QBrush(Qt::black));
    hit->drawEllipse(5.0, 5.0, 50.0, 50.0);
    delete hit;
    pawnBlack = new QLabel("Black");
    pawnBlack->setAlignment(Qt::AlignCenter);
    pawnBlack->setPixmap(pix);
    pawnBlack->setStyleSheet("QLabel { color : black; }");

    QPixmap pix2(60,60);
    pix2.fill(Qt::transparent);
    hit2= new QPainter(&pix2);
    hit2->setBrush(QBrush(Qt::white));
    hit2->drawEllipse(5.0, 5.0, 50.0, 50.0);
    delete hit2;
    pawnWhite = new QLabel("");
    pawnWhite->setAlignment(Qt::AlignCenter);
    pawnWhite->setPixmap(pix2);
    pawnWhite->setStyleSheet("QLabel { color : black; }");

    colorP1->setAlignment(Qt::AlignCenter);
    colorP2->setAlignment(Qt::AlignCenter);
    nameP1->setAlignment(Qt::AlignCenter);
    nameP2->setAlignment(Qt::AlignCenter);
    typeP1->setAlignment(Qt::AlignCenter);
    typeP2->setAlignment(Qt::AlignCenter);
    scoreP1->setAlignment(Qt::AlignCenter);
    QFont f( "Verdana", 35, QFont::Bold);
    scoreP1->setFont(f);
    scoreP1->setText("0");
    scoreP2->setAlignment(Qt::AlignCenter);
    scoreP2->setFont(f);
    scoreP2->setText("0");
    movesP1->setAlignment(Qt::AlignCenter);
    movesP1->setText("0");
    movesP2->setAlignment(Qt::AlignCenter);
    movesP2->setText("0");
    dot5->setAlignment(Qt::AlignCenter);
    dot5->setFont(f);
    QFont f2( "Audiowide", 15, QFont::Bold);
    scoreP1Label->setFont(f2);
    infosGame = new QLabel( "" );
    infosGame->setAlignment(Qt::AlignCenter);
    infosGame->setFrameStyle(QFrame::Box|QFrame::Raised);
    infosGame->setFixedSize(350,50);
    infosGame->setLineWidth(3);
    infosGame->setAutoFillBackground(true);
    infosGame->setText("Good Luck!");
    QPalette palette=infosGame->palette();
    palette.setColor(QPalette::Window,QColor(Qt::green));
    infosGame->setPalette(palette);

    topLayout = new QGridLayout;
    topLayout->addWidget(namepar1,1,0);
    topLayout->addWidget(levelpar1,2,0);
    topLayout->addWidget(movesP1Label,3,0);
    topLayout->addWidget(scoreP1Label,4,0);
    topLayout->addWidget(dot1,1,1);
    topLayout->addWidget(dot2,2,1);
    topLayout->addWidget(dot3,3,1);
    topLayout->addWidget(dot4,4,1);

    topLayout->addWidget(pawnBlack,0,2);
    topLayout->addWidget(nameP1,1,2);
    topLayout->addWidget(typeP1,2,2);
    topLayout->addWidget(movesP1,3,2);
    topLayout->addWidget(scoreP1,4,2);

    topLayout->addWidget(dot5, 4,3);

    topLayout->addWidget(pawnWhite,0,4);
    topLayout->addWidget(nameP2,1,4);
    topLayout->addWidget(typeP2,2,4);
    topLayout->addWidget(movesP2,3,4);
    topLayout->addWidget(scoreP2,4,4);

    toptopLayout = new QHBoxLayout;
    toptopLayout->addLayout(topLayout);
    toptopLayout->addStretch();

    mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(toptopLayout);
    mainLayout->addStretch();
    mainLayout->addStretch();
    mainLayout->addWidget(infosGame);
    mainLayout->addStretch();
    mainLayout->addStretch();

}

void infoView::setColorP1( ColorPawn c )
{
        if( c == Black )
        {
                colorP1->setText( QString(tr("<b>Black</b>")) );
        }
        else
        {
                colorP1->setText( QString(tr("<b>White</b>")) );
        }
}

void infoView::setColorP2( ColorPawn c )
{
        if( c == Black )
        {
                colorP2->setText( QString(tr("<b>Black</b>")) );
        }
        else
        {
                colorP2->setText( QString(tr("<b>White</b>")) );
        }
}

void infoView::setNameP1( QString name )
{
        QString str = "<b>" + name + "</b>";
        nameP1->setText(str);
}

void infoView::setNameP2( QString name )
{
        QString str = "<b>" + name + "</b>";
        nameP2->setText(str);
}

void infoView::setTypeP1( TypePlayer t )
{
        switch( t )
        {
                case Local:
                        typeP1->setText( QString(tr("( Human Local )")) );
                        break;
                case Distant:
                        typeP1->setText( QString(tr("( Human Distant )")) );
                        break;
                case AI_1:
                        typeP1->setText( QString(tr("( Computer Level1 )")) );
                        break;
                case AI_2:
                        typeP1->setText( QString(tr("( Computer Level2 )")) );
                        break;
                case AI_3:
                        typeP1->setText( QString(tr("( Computer Level3 )")) );
                        break;
                default:
                        typeP1->setText( QString(tr("( )")) );
                        break;
        }
}

void infoView::setTypeP2( TypePlayer t )
{
        switch( t )
        {
                case Local:
                        typeP2->setText( QString(tr("( Human Local )")) );
                        break;
                case Distant:
                        typeP2->setText( QString(tr("( Human Distant )")) );
                        break;
                case AI_1:
                        typeP2->setText( QString(tr("( Computer Level 1 )")) );
                        break;
                case AI_2:
                        typeP2->setText( QString(tr("( Computer Level 2)")) );
                        break;
                case AI_3:
                        typeP2->setText( QString(tr("( Computer Level 3 )")) );
                        break;
                default:
                        typeP2->setText( QString(tr("( )")) );
                        break;
        }
}

void infoView::setScoreP1( int score )
{
        scoreP1->setNum( score );
}

void infoView::setScoreP2( int score )
{
        scoreP2->setNum( score );
}

void infoView::setMovesP1( int moves )
{
        movesP1->setNum( moves );
}

void infoView::setMovesP2( int moves )
{
        movesP2->setNum( moves);
}

void infoView::connecting( game* ge )
{
        playerTable = ge->getPlayer();
        connect( ge, SIGNAL( playerNameModified(Player*) ), this, SLOT( updatingName(Player*) ) );
        connect( ge, SIGNAL( playerScoreModified() ), this, SLOT( updatingScore() ) );
        connect( ge, SIGNAL( playerNumMovesModified() ), this, SLOT( updatingMoves() ) );
        connect( ge, SIGNAL( playerColorModified(Player*) ), this, SLOT( updatingColor(Player*) ) );
        connect( ge, SIGNAL( playerTypeModified(Player*) ), this, SLOT( updatingType(Player*) ) );
        connect( ge, SIGNAL( sendInfosGameDisplay(IdMsgInfos) ), this, SLOT( setInfosGame(IdMsgInfos) ) );
}

void infoView::updatingColor( Player *p )
{
//      cout << "Entre ds \"infoView::updatingColor(Player*)\"" << endl;

        if( p->getId() == p1 )
        {
                setColorP1( p->getColor() );
        }
        else
        {
                setColorP2( p->getColor() );
        }
}

void infoView::updatingType( Player *p )
{
//      cout << " \"infoView::updatingType(Player*)\"" << endl;

        if( p->getId() == p1 )
        {
                setTypeP1( p->getType() );
        }
        else
        {
                setTypeP2( p->getType() );
        }
}

void infoView::updatingName( Player *p )
{
//      cout << " \"infoView::updatingName(Player*)\"" << endl;

        if( p->getId() == p1 )
        {
                setNameP1( p->getName() );
        }
        else
        {
                setNameP2( p->getName() );
        }
}

void infoView::updatingScore()
{
        setScoreP1( playerTable[p1]->getScore() );
        setScoreP2( playerTable[p2]->getScore() );
}

void infoView::updatingMoves()
{
        setMovesP1( playerTable[p1]->getNumMoves() );
        setMovesP2( playerTable[p2]->getNumMoves() );
}

void infoView::setInfosGame(IdMsgInfos idMsg)
{
        QString msg;
        switch( idMsg )
        {
                case P1_Playing:
                        msg = playerTable[p1]->getName() + " ( ";
                        if( playerTable[p1]->getColor() == Black )
                        {
                                msg += "black";
                        }
                        else
                        {
                                msg += "white";
                        }
                        msg += " pawns ) is playing ...";
                        break;

                case P2_Playing:
                        msg = playerTable[p2]->getName() + " ( ";
                        if( playerTable[p2]->getColor() == Black )
                        {
                                msg += "black";
                        }
                        else
                        {
                                msg += "white";
                        }
                        msg += " pawns ) is playing ...";
                        break;

                default:
                        break;
        }

        infosGame->setText(msg);
}

void infoView::writeSettings()
{
        QSettings settings("Version", "Reversiv1.1");
        settings.setValue( "name_p1", playerTable[p1]->getName() );
        settings.setValue( "name_p2", playerTable[p2]->getName() );
        switch( playerTable[p1]->getType() )
        {
                case AI_1:
                        settings.setValue( "type_p1", 1 );
                        break;
                case AI_2:
                        settings.setValue( "type_p1", 2 );
                        break;
                case AI_3:
                        settings.setValue( "type_p1", 3 );
                        break;
                case Local:
                default:
                        settings.setValue( "type_p1", 0 );
                        break;
        }
        switch( playerTable[p2]->getType() )
        {
                case AI_1:
                        settings.setValue( "type_p2", 1 );
                        break;
                case AI_2:
                        settings.setValue( "type_p2", 2 );
                        break;
                case AI_3:
                        settings.setValue( "type_p2", 3 );
                        break;
                case Local:
                default:
                        settings.setValue( "type_p2", 0 );
                        break;
        }
}

void infoView::readSettings()
{
        QSettings settings("Version", "Reversi v1.1");
        playerTable[p1]->setName( settings.value("name_p1", tr("Player 1")).toString() );
        playerTable[p2]->setName( settings.value("name_p2", tr("Player 2")).toString() );

        switch( settings.value("type_p1", 0).toInt() )
        {
                case 1:
                        playerTable[p1]->setType( AI_1 );
                        break;
                case 2:
                        playerTable[p1]->setType( AI_2 );
                        break;
                case 3:
                        playerTable[p1]->setType( AI_3 );
                        break;
                case 0:
                default:
                        playerTable[p1]->setType( Local );
                        break;
        }
        switch( settings.value("type_p2", 0).toInt() )
        {
                case 1:
                        playerTable[p2]->setType( AI_1 );
                        break;
                case 2:
                        playerTable[p2]->setType( AI_2 );
                        break;
                case 3:
                        playerTable[p2]->setType( AI_3 );
                        break;
                case 0:
                default:
                        playerTable[p2]->setType( Local );
                        break;
        }
}

Player* infoView::getPlayer( int id )
{
        return playerTable[id];
}
