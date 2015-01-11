#include "infoview.h"
#include <QtGui>
#include "game.h"
#include "player.h"
#include <QMainWindow>
#include <QApplication>

InfoView::InfoView(QWidget *parent)
    : QWidget(parent)
{
    nameP1 = new QLabel( "" );
    nameP2 = new QLabel( "" );
    typeP1 = new QLabel("( )");
    typeP2 = new QLabel("( )");
    namepar1 = new QLabel("Name ");
    namepar2 = new QLabel("Name ");
    levelpar1  = new QLabel("Level ");
    levelpar2 = new QLabel("level ");
    line = new QLabel("----------------------------------------------");
    line2 = new QLabel("----------------------------------------------");
    scoreLabel = new QLabel( tr("Score") );
    scoreP1 = new QLabel( "0" );
    scoreP2 = new QLabel( "0" );
    movesLabel = new QLabel( tr("Moves") );
    movesP1 = new QLabel( "0" );
    movesP2 = new QLabel( "0" );

    dot1 = new QLabel(":");
    dot2 = new QLabel(":");
    dot3 = new QLabel(":");
    dot4 = new QLabel(":");
    dot5 = new QLabel(":");

    QPixmap pix(60,60);
    pix.fill(Qt::transparent);
    painterBlack= new QPainter(&pix);
    painterBlack->setBrush(QBrush(Qt::black));
    painterBlack->drawEllipse(5.0, 5.0, 50.0, 50.0);
    delete painterBlack;
    pawnBlack = new QLabel("Black");
    pawnBlack->setAlignment(Qt::AlignCenter);
    pawnBlack->setPixmap(pix);
    pawnBlack->setStyleSheet("QLabel { color : black; }");

    QPixmap pix2(60,60);
    pix2.fill(Qt::transparent);
    painterWhite= new QPainter(&pix2);
    painterWhite->setBrush(QBrush(Qt::white));
    painterWhite->drawEllipse(5.0, 5.0, 50.0, 50.0);
    delete painterWhite;
    pawnWhite = new QLabel("");
    pawnWhite->setAlignment(Qt::AlignCenter);
    pawnWhite->setPixmap(pix2);
    pawnWhite->setStyleSheet("QLabel { color : black; }");

    nameP1->setAlignment(Qt::AlignCenter);
    nameP2->setAlignment(Qt::AlignCenter);
    typeP1->setAlignment(Qt::AlignCenter);
    typeP2->setAlignment(Qt::AlignCenter);
    scoreP1->setAlignment(Qt::AlignCenter);
    scoreP2->setAlignment(Qt::AlignCenter);
    movesP1->setAlignment(Qt::AlignCenter);
    movesP2->setAlignment(Qt::AlignCenter);
    QFont f( "Verdana", 50, QFont::Bold);
    QFont f2( "Verdana", 20, QFont::Bold);

    scoreP1->setFont(f);
    scoreP2->setFont(f);
    scoreLabel->setFont(f2);
    dot5->setFont(f2);

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

    listMoves = new QTextEdit( "Empty" );
    listMoves->setReadOnly(true);

    topLayout = new QGridLayout;
    topLayout->addWidget(namepar1,1,0);
    topLayout->addWidget(levelpar1,2,0);
    topLayout->addWidget(scoreLabel,4,0);
    topLayout->addWidget(movesLabel,3,0);
    topLayout->addWidget(dot1,1,1);
    topLayout->addWidget(dot2,2,1);
    topLayout->addWidget(dot3,3,1);
    topLayout->addWidget(dot4,4,1);

    topLayout->addWidget(pawnBlack,0,2);
    topLayout->addWidget(nameP1,1,2);
    topLayout->addWidget(typeP1,2,2);
    topLayout->addWidget(scoreP1,4,2);
    topLayout->addWidget(movesP1,3,2);

    topLayout->addWidget(dot5, 4,3);

    topLayout->addWidget(pawnWhite,0,4);
    topLayout->addWidget(nameP2,1,4);
    topLayout->addWidget(typeP2,2,4);
    topLayout->addWidget(scoreP2,4,4);
    topLayout->addWidget(movesP2,3,4);

    toptopLayout = new QHBoxLayout;
    toptopLayout->addLayout(topLayout);
    toptopLayout->addStretch();

    centerLayout = new QHBoxLayout;
    centerLayout->addStretch();
    centerLayout->addWidget(movesListLabel);
    centerLayout->addStretch();

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(line);
    mainLayout->addStretch();
    mainLayout->addLayout(toptopLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(line2);
    mainLayout->addStretch();
    mainLayout->addWidget(infosGame);
    mainLayout->addStretch();
    mainLayout->addLayout(centerLayout);
    mainLayout->addWidget(listMoves);
    mainLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainLayout);

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

}

InfoView::~InfoView()
{
}

void InfoView::setNameP1( QString name )
{
    QString str = "<b>" + name + "</b>";
    nameP1->setText(str);
}

void InfoView::setNameP2( QString name )
{
    QString str = "<b>" + name + "</b>";
    nameP2->setText(str);
}

void InfoView::setTypeP1( TypePlayer t )
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

void InfoView::setTypeP2( TypePlayer t )
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

void InfoView::setScoreP1( int score )
{
        scoreP1->setNum( score );
}

void InfoView::setScoreP2( int score )
{
        scoreP2->setNum( score );
}

void InfoView::setMovesP1( int moves )
{
        movesP1->setNum( moves );
}

void InfoView::setMovesP2( int moves )
{
        movesP2->setNum( moves);
}

void InfoView::connecting( game* ge )
{
    playerTable = ge->getPlayer();
    connect( ge, SIGNAL( playerNameModified(Player*) ), this, SLOT( updatingName(Player*) ) );
    connect( ge, SIGNAL( playerColorModified(Player*) ), this, SLOT( updatingColor(Player*) ) );
    connect( ge, SIGNAL( playerTypeModified(Player*) ), this, SLOT( updatingType(Player*) ) );
    connect( ge, SIGNAL( sendInfosGameDisplay(IdMsgInfos) ), this, SLOT( setInfosGame(IdMsgInfos) ) );
    connect( ge, SIGNAL( playerScoreModified() ), this, SLOT( updatingScore() ) );
    connect( ge, SIGNAL( playerNumMovesModified() ), this, SLOT( updatingMoves() ) );
    connect( ge, SIGNAL( movesListModified(QString) ), this, SLOT( setListMoves(QString) ) );

}

void InfoView::updatingType( Player *p )
{
    //      cout << " \"InfoView::updatingType(Player*)\"" << endl;

    if( p->getId() == p1 )
    {
            setTypeP1( p->getType() );
    }
    else
    {
            setTypeP2( p->getType() );
    }
}

void InfoView::updatingName( Player *p )
{
    //      cout << " \"InfoView::updatingName(Player*)\"" << endl;

    if( p->getId() == p1 )
    {
            setNameP1( p->getName() );
    }
    else
    {
            setNameP2( p->getName() );
    }
}

void InfoView::updatingScore()
{
        setScoreP1( playerTable[p1]->getScore() );
        setScoreP2( playerTable[p2]->getScore() );
}

void InfoView::updatingMoves()
{
        setMovesP1( playerTable[p1]->getNumMoves() );
        setMovesP2( playerTable[p2]->getNumMoves() );
}

void InfoView::writeSettings()
{
    QSettings settings("Version", "Reversiv1.1");
    settings.setValue( "name_p1", playerTable[p1]->getName() );
    settings.setValue( "name_p2", playerTable[p2]->getName() );
}

void InfoView::readSettings()
{
    QSettings settings("Version", "Reversi v1.1");
    playerTable[p1]->setName( settings.value("name_p1", tr("Player 1")).toString() );
    playerTable[p2]->setName( settings.value("name_p2", tr("Player 2")).toString() );
}


Player* InfoView::getPlayer( int id )
{
return playerTable[id];
}

void InfoView::setInfosGame(IdMsgInfos idMsg)
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

void InfoView::setListMoves( QString list )
{
    listMoves->setText( list );
}
