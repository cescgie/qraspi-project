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
    QFont f( "Verdana", 50, QFont::Bold);

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

    topLayout->addWidget(pawnBlack,0,2);
    topLayout->addWidget(nameP1,1,2);
    topLayout->addWidget(typeP1,2,2);

    topLayout->addWidget(pawnWhite,0,4);
    topLayout->addWidget(nameP2,1,4);
    topLayout->addWidget(typeP2,2,4);

    toptopLayout = new QHBoxLayout;
    toptopLayout->addLayout(topLayout);
    toptopLayout->addStretch();

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(line);
    mainLayout->addStretch();
    mainLayout->addLayout(toptopLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(line2);
    mainLayout->addStretch();
    mainLayout->addWidget(infosGame);

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


void InfoView::connecting( game* ge )
{
    playerTable = ge->getPlayer();
    connect( ge, SIGNAL( playerNameModified(Player*) ), this, SLOT( updatingName(Player*) ) );
    connect( ge, SIGNAL( playerColorModified(Player*) ), this, SLOT( updatingColor(Player*) ) );
    connect( ge, SIGNAL( playerTypeModified(Player*) ), this, SLOT( updatingType(Player*) ) );
    connect( ge, SIGNAL( sendInfosGameDisplay(IdMsgInfos) ), this, SLOT( setInfosGame(IdMsgInfos) ) );

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
