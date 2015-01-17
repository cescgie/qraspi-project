#include "graphics.h"
#include "game.h"
#include "player.h"
#include "QMessageBox"
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QtGui>
#include <assert.h>

graphics::graphics()
{
    centralWindow = new QWidget(this);
    scene = new glView(this);
    infos = new InfoView(this);
    list_moves = new ListMoves(this);

    HighscoreView();
    initComponent();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    soundConfiguration();

    setUnifiedTitleAndToolBarOnMac ( true );
    setWindowTitle(QtVersion);
}

graphics::~graphics()
{
    delete centralWindow;
    delete scene;
    delete infos;
    delete list_moves;

}
void graphics::initialization( game *ge )
{
    connecting( ge );
    refreshHighScore();
    ge->initializationDisplay();
}

void graphics::connecting( game *ge )
{
    if( ge != NULL )
    {
        connect( this, SIGNAL( startNewGame() ), ge, SLOT( initialization() ) );
        connect( ge, SIGNAL( playerWins(Player*) ), this, SLOT( displayWinner(Player*) ) );
        connect( this, SIGNAL( undoMoveAsked() ), ge, SLOT( undoMoveGlobal() ) );
        connect( this, SIGNAL( redoMoveAsked() ), ge, SLOT( redoMoveGlobal() ) );
        connect( ge, SIGNAL( enableUndoMoveAction(bool) ), this, SLOT( setDisplayUndoMoveAction(bool) ) );
        connect( ge, SIGNAL( enableRedoMoveAction(bool) ), this, SLOT( setDisplayRedoMoveAction(bool) ) );

        scene->connecting( ge );
        infos->connecting( ge );
        list_moves->connecting(ge);

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
    viewMenu->addAction(regularMovesAction);
    viewMenu->addAction(lastMoveAction);
}

void graphics::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/NewGame.png"));
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Play a new game"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setIcon(QIcon(":/images/Quit.png"));
    exitAction->setShortcut(tr("Ctrl+X"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    animationAction = new QAction(tr("Animations"), this);
    animationAction->setCheckable(true);
    animationAction->setChecked(true);
    animationAction->setStatusTip(tr("Show or hide animations"));
    connect(animationAction, SIGNAL(triggered()), this, SLOT(updateSettingAnimation()));

    preferencesAction = new QAction(tr("&Preferences"), this);
    preferencesAction->setIcon(QIcon(":/images/Preferences.png"));
    preferencesAction->setShortcut(tr("Ctrl+P"));
    preferencesAction->setStatusTip(tr("Configure the options game"));
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(preferences()));

    regularMovesAction = new QAction(tr("Regular Moves"), this);
    regularMovesAction->setCheckable(true);
    regularMovesAction->setChecked(true);
    regularMovesAction->setStatusTip(tr("Show or hide regular moves"));
    connect(regularMovesAction, SIGNAL(triggered()), this, SLOT(updateSettingRegularMoves()));

    lastMoveAction = new QAction(tr("Last Move"), this);
    lastMoveAction->setCheckable(true);
    lastMoveAction->setChecked(true);
    lastMoveAction->setStatusTip(tr("Show or hide last move"));
    connect(lastMoveAction, SIGNAL(triggered()), this, SLOT(updateSettingLastMove()));

    undoMoveAction = new QAction(tr("&Undo Move"), this);
    undoMoveAction->setIcon(QIcon(":/images/UndoMove.png"));
    undoMoveAction->setShortcut(tr("Ctrl+U"));
    undoMoveAction->setStatusTip(tr("Undo the last move"));
    connect(undoMoveAction, SIGNAL(triggered()), this, SLOT(undoMove()));
    undoMoveAction->setEnabled(false);

    redoMoveAction = new QAction(tr("&Redo Move"), this);
    redoMoveAction->setIcon(QIcon(":/images/RedoMove.png"));
    redoMoveAction->setShortcut(tr("Ctrl+R"));
    redoMoveAction->setStatusTip(tr("Redo the last move canceled"));
    connect(redoMoveAction, SIGNAL(triggered()), this, SLOT(redoMove()));
    redoMoveAction->setEnabled(false);

    //fullscreen
    fullScreenAction = new QAction(tr("&Fullscreen"), this);
    fullScreenAction->setIcon(QIcon(":/images/Fullscreen.png"));
    fullScreenAction->setShortcut(tr("Ctrl+L"));
    fullScreenAction->setStatusTip(tr("Set Full Screen"));
    connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(fullScreen()));
}

void graphics::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);

    toolsToolBar = addToolBar(tr("&Tools"));
    toolsToolBar->addAction(undoMoveAction);
    toolsToolBar->addAction(redoMoveAction);
    toolsToolBar->addAction(preferencesAction);
    toolsToolBar->addAction(fullScreenAction);
    toolsToolBar->addAction(exitAction);
}

void graphics::newGame()
{
    effectBounce.play();
    int r = QMessageBox::information(this, QtVersion, tr("Play new game?"),
            QMessageBox::Yes, QMessageBox::No | QMessageBox::Default);
    if(r == QMessageBox::Yes){
        effectStart.play();
        emit startNewGame();
    }
}

void graphics::preferences()
{
    effectBounce.play();
    QString name_p1 = infos->getPlayer(p1)->getName(),
            name_p2 = infos->getPlayer(p2)->getName();
    int type_p1, type_p2;
    switch( infos->getPlayer(p1)->getType() )
    {
        case AI_1:
            type_p1 = 1;
            break;
        case AI_2:
            type_p1 = 2;
            break;
        case AI_3:
            type_p1 = 3;
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
        case AI_2:
            type_p2 = 2;
            break;
        case AI_3:
            type_p2 = 3;
            break;
        case Local:
        default:
            type_p2 = 0;
            break;
    }
    //Erstellen des Dialogs
   PlayerSetting dialog(this);

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
                case 2:
                    infos->getPlayer(p1)->setType( AI_2 );
                    infos->setTypeP1( AI_2 );
                    break;
                case 3:
                    infos->getPlayer(p1)->setType( AI_3 );
                    infos->setTypeP1( AI_3 );
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
                case 2:
                    infos->getPlayer(p2)->setType( AI_2 );
                    infos->setTypeP2( AI_2 );
                    break;
                case 3:
                    infos->getPlayer(p2)->setType( AI_3 );
                    infos->setTypeP2( AI_3 );
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
            effectStart.play();
            emit startNewGame();
        }
    }
}

void graphics::closeEvent(QCloseEvent *event)
{
        effectBounce.play();
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
    effectEnd.play();
    if( p != NULL )
    {
        QString namo = p->getName();
        int punkte = p->getScore();
        createHighscore(namo,punkte);
        QString str = p->getName() + " wins the game !";
        QMessageBox::information(this,QtVersion,str,
                QMessageBox::Ok | QMessageBox::Default);
    }
    else
    {
        QMessageBox::information(this,QtVersion,tr("Deuce !"),
                QMessageBox::Ok | QMessageBox::Default);
    }
    effectEnd.stop();
    emit preferences();
}

void graphics::updateSettingAnimation()
{
    scene->setAnimationSetting( animationAction->isChecked() );
}

void graphics::updateSettingRegularMoves()
{
    scene->setRegularMovesSetting( regularMovesAction->isChecked() );
}

void graphics::updateSettingLastMove()
{
    scene->setLastMoveSetting( lastMoveAction->isChecked() );
}

void graphics::undoMove()
{
    effectPrev.play();
    scene->setMoveAsked(false);
    emit undoMoveAsked();
}

void graphics::redoMove()
{
    effectNext.play();
    scene->setMoveAsked(false);
    emit redoMoveAsked();
}

void graphics::setDisplayUndoMoveAction(bool b)
{
        undoMoveAction->setEnabled(b);
}

void graphics::setDisplayRedoMoveAction(bool b)
{
        redoMoveAction->setEnabled(b);
}

//fullscreen
void graphics::fullScreen()
{
    effectBounce.play(); //sound
    QDialog *dlg = new QDialog(this);
    QHBoxLayout *dlg_layout = new QHBoxLayout(dlg);
        dlg_layout->setContentsMargins(0, 0, 0, 0);
        dlg_layout->addWidget(scene);
        dlg->setLayout(dlg_layout);
        dlg->showFullScreen();

        bool r = connect(dlg, SIGNAL(rejected()), this, SLOT(showGlNormal()));
        assert(r);
        r = connect(dlg, SIGNAL(accepted()), this, SLOT(showGlNormal()));
        assert(r);

}

//Normalscreen
void graphics::showGlNormal() {
    centralWindow = new QWidget(this);
    HighscoreView();
    initComponent();
}

void graphics::initComponent()
{
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *topverticalLayout = new QVBoxLayout;
    topverticalLayout->addWidget(infos);
    topverticalLayout->addLayout(gridLayout);
    layout->addWidget(list_moves);
    layout->addWidget(scene);
    layout->addLayout(topverticalLayout);
    centralWindow->setLayout(layout);
    setCentralWidget(centralWindow);
}

//sounds configuration
void graphics::soundConfiguration()
{
   effectBounce.setSource(QUrl::fromLocalFile(":/sounds/bounce.wav"));
   effectBounce.setLoopCount(1);
   effectBounce.setVolume(1.0f);
   effectStart.setSource(QUrl::fromLocalFile(":/sounds/start.wav"));
   effectStart.setLoopCount(1);
   effectStart.setVolume(1.0f);
   effectEnd.setSource(QUrl::fromLocalFile(":/sounds/end.wav"));
   effectEnd.setLoopCount(1);
   effectEnd.setVolume(1.0f);
   effectNext.setSource(QUrl::fromLocalFile(":/sounds/next.wav"));
   effectNext.setLoopCount(1);
   effectNext.setVolume(1.0f);
   effectPrev.setSource(QUrl::fromLocalFile(":/sounds/prev.wav"));
   effectPrev.setLoopCount(1);
   effectPrev.setVolume(1.0f);
}

QSqlQueryModel* graphics::getHighscores()
{
  return _highscore.getHighscore();
}

void graphics::createHighscore(QString nam, int punk)
{
    cout<<"punk :"<<punk<<endl;
  _highscore.insertHighscore(nam, punk);
}

void graphics::refreshHighScore()
{
    tableViewHighscores->setModel(getHighscores());
    tableViewHighscores->resizeColumnToContents(1);

}

void graphics::HighscoreView()
{
    gridLayout = new QGridLayout();
    groupBoxHighscores = new QGroupBox();
    horizontalLayout = new QHBoxLayout(groupBoxHighscores);
    horizontalLayout->setAlignment(Qt::AlignHCenter);
    tableViewHighscores = new QTableView(groupBoxHighscores);
    horizontalLayout->addWidget(tableViewHighscores);
    highscoresLabel = new QLabel("Highscores");
    highscoresLabel->setAlignment(Qt::AlignHCenter);
    verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(highscoresLabel);
    verticalLayout->addStretch();
    verticalLayout->addWidget(tableViewHighscores);
    verticalLayout->addStretch();
    gridLayout->addLayout(verticalLayout,0, 0, 1, 1);
}
