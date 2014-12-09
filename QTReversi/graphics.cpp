#include "graphics.h"
#include "game.h"
#include "player.h"
#include "QMessageBox"
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QtGui>

graphics::graphics()
{
    centralWindow = new QWidget(this);
    scene = new glView(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(scene);
    centralWindow->setLayout(layout);
    setCentralWidget(centralWindow);

    createActions();
    createMenus();
    createStatusBar();

    setUnifiedTitleAndToolBarOnMac ( true );

    setWindowTitle(QtVersion);
}

graphics::~graphics()
{
    delete centralWindow;
    delete scene;

}
void graphics::initialization( game *ge )
{
    connecting( ge );
    ge->initializationDisplay();
}

void graphics::connecting( game *ge )
{
    if( ge != NULL )
    {
        connect( this, SIGNAL( startNewGame() ), ge, SLOT( initialization() ) );
        connect( ge, SIGNAL( playerWins(Player*) ), this, SLOT( displayWinner(Player*) ) );

        scene->connecting( ge );

    }
}


void graphics::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(animationAction);
}

void graphics::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon("NewGame.png"));
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Play a new game"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setIcon(QIcon("Quit.png"));
    exitAction->setShortcut(tr("Ctrl+X"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    animationAction = new QAction(tr("Animations"), this);
    animationAction->setCheckable(true);
    animationAction->setChecked(true);
    animationAction->setStatusTip(tr("Show or hide animations"));
    connect(animationAction, SIGNAL(triggered()), this, SLOT(updateSettingAnimation()));

}

void graphics::newGame()
{
    QMessageBox::information(this, QtVersion, tr("New Game!"),
            QMessageBox::Ok | QMessageBox::Default);
    emit startNewGame();
}

void graphics::closeEvent(QCloseEvent *event)
{
        int r = QMessageBox::warning(this,QtVersion,tr("Do you really want to exit the game?"),
                                QMessageBox::Yes, QMessageBox::No | QMessageBox::Default);
        if(r == QMessageBox::Yes){
                event->accept();
        }
        else{
                event->ignore();
        }
}
void graphics::createStatusBar()
{
        statusBarLabel = new QLabel("");
        statusBar()->addWidget(statusBarLabel,1);
}

\
void graphics::displayWinner(Player *p)
{
    if( p != NULL )
    {
        QString str = p->getName() + " wins the game !";
        QMessageBox::information(this,QtVersion,str,
                QMessageBox::Ok | QMessageBox::Default);
    }
    else
    {
        QMessageBox::information(this,QtVersion,tr("Deuce !"),
                QMessageBox::Ok | QMessageBox::Default);
    }

    emit startNewGame();
}

void graphics::updateSettingAnimation()
{
    scene->setAnimationSetting( animationAction->isChecked() );
}

