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
    infos = new InfoView(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(scene);
    layout->addWidget(infos);
    centralWindow->setLayout(layout);
    setCentralWidget(centralWindow);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    setUnifiedTitleAndToolBarOnMac ( true );

    setWindowTitle(QtVersion);
}

graphics::~graphics()
{
    delete centralWindow;
    delete scene;
    delete infos;

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
        infos->connecting( ge );

    }
}


void graphics::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(preferencesAction);
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

    preferencesAction = new QAction(tr("&Preferences"), this);
    preferencesAction->setIcon(QIcon("Preferences.png"));
    preferencesAction->setShortcut(tr("Ctrl+P"));
    preferencesAction->setStatusTip(tr("Configure the options game"));
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(preferences()));

}

void graphics::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);

    toolsToolBar = addToolBar(tr("&Tools"));
    toolsToolBar->addAction(preferencesAction);
    toolsToolBar->addAction(exitAction);
}

void graphics::newGame()
{
    QMessageBox::information(this, QtVersion, tr("New Game!"),
            QMessageBox::Ok | QMessageBox::Default);
    emit startNewGame();
}

void graphics::preferences()
{
    QString name_p1 = infos->getPlayer(p1)->getName(),
            name_p2 = infos->getPlayer(p2)->getName();
    int type_p1, type_p2;
    switch( infos->getPlayer(p1)->getType() )
    {
        case AI_1:
            type_p1 = 1;
            break;
        case Local:
        default:
            type_p1 = 0;
            break;
    }
    switch( infos->getPlayer(p2)->getType() )
    {
        case AI_1:
            type_p2 = 1;
            break;
        case Local:
        default:
            type_p2 = 0;
            break;
    }
    //Erstellen des Dialogs
   PreferencesDialog dialog(this);

    cout << "## Preferences ##"<< endl;
    cout << "	type_p1: " << type_p1 << "	type_p2: " << type_p2 << endl;
    dialog.setNames( name_p1, name_p2 );
    dialog.setTypes(type_p1,type_p2);


    if( dialog.exec() )
    {
        bool modif_type = false;

        if( name_p1 != dialog.lineEdit_name_p1->text() )
        {
            infos->getPlayer(p1)->setName( dialog.lineEdit_name_p1->text() );
            infos->setNameP1( dialog.lineEdit_name_p1->text() );
        }
        if( name_p2 != dialog.lineEdit_name_p2->text() )
        {
            infos->getPlayer(p2)->setName( dialog.lineEdit_name_p2->text() );
            infos->setNameP2( dialog.lineEdit_name_p2->text() );
        }
        if( type_p1 != dialog.comboBox_type_p1->currentIndex() )
        {
            switch( dialog.comboBox_type_p1->currentIndex() )
            {
                case 1:
                    infos->getPlayer(p1)->setType( AI_1 );
                    infos->setTypeP1( AI_1 );
                    break;
                case 0:
                default:
                    infos->getPlayer(p1)->setType( Local );
                    infos->setTypeP1( Local );
                    break;
            }
            modif_type = true;
        }
        if( type_p2 != dialog.comboBox_type_p2->currentIndex() )
        {
            switch( dialog.comboBox_type_p2->currentIndex() )
            {
                case 1:
                    infos->getPlayer(p2)->setType( AI_1 );
                    infos->setTypeP2( AI_1 );
                    break;
                case 0:
                default:
                    infos->getPlayer(p2)->setType( Local );
                    infos->setTypeP2( Local );
                    break;
            }
            modif_type = true;
        }
        if( modif_type )
        {
            emit startNewGame();
        }
    }
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

