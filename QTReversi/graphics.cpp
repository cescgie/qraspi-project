#include "graphics.h"
#include "define.h"
#include "QMessageBox"
#include "QtWidgets"

graphics::graphics(QWidget *parent)
    : QMainWindow(parent)
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

}

void graphics::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
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

}

void graphics::newGame()
{
    QMessageBox::information(this, QtVersion, tr("New Game!"),
            QMessageBox::Ok | QMessageBox::Default);
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
        statusBarLabel->setAlignment(Qt::AlignHCenter);
        statusBar()->addWidget(statusBarLabel,1);
}

