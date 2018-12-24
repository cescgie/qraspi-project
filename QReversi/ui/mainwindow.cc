#include "mainwindow.h"

#include "ui/checkerboard/checkerboardwidget.h"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_battle(new Battle(this)),
      m_checkerBoardWidget(new CheckerBoardWidget(this)),
      m_gameMenu(menuBar()->addMenu("Game")),
      m_startGame(new QAction("Start a new game", this)),
      m_stopGame(new QAction("End game", this)),
      m_exitGame(new QAction("Exit", this)),
      m_newGameDialog(new NewGameDialog(this))
{
    // Main control
    setCentralWidget(m_checkerBoardWidget);

    initMenuBar();
    initSignalsAndSlots();

    m_newGameDialog->setBattle(m_battle);

    m_battle->endBattle(); // First reset
}

MainWindow::~MainWindow()
{

}

void MainWindow::initMenuBar()
{
    // Game menu
    m_gameMenu->addAction(m_startGame);
    m_gameMenu->addAction(m_stopGame);
    m_gameMenu->addSeparator();
    m_gameMenu->addAction(m_exitGame);
}

void MainWindow::initSignalsAndSlots()
{
    // menu actions
    connect(m_exitGame, &QAction::triggered, this, [](){QApplication::quit();});
    connect(m_startGame, &QAction::triggered, this, &MainWindow::startNewGame);
    connect(m_stopGame, &QAction::triggered, this, &MainWindow::stopGame);

    // battle and checkerboardwidget
    connect(m_battle, &Battle::sigCheckerBoardChanged, m_checkerBoardWidget, &CheckerBoardWidget::setCheckerBoard);
    connect(m_checkerBoardWidget, &CheckerBoardWidget::sigMoved, m_battle, &Battle::slotHumanMove);

    // battle and mainwindow
    connect(m_battle, &Battle::sigBattleEnded, this, &MainWindow::showWinnerInfo);
    connect(m_battle, &Battle::sigChanged, this, &MainWindow::updateStatusBar);
}

void MainWindow::startNewGame()
{
    m_newGameDialog->show();
}

void MainWindow::stopGame()
{
    m_battle->endBattle();
}

void MainWindow::showWinnerInfo(GamePlay::PlayerColor winner)
{
    QMessageBox* mb = new QMessageBox(this);
    mb->setAttribute(Qt::WA_DeleteOnClose, true);
    mb->setWindowTitle(" ");
    if (winner == GamePlay::Unknown)
        mb->setText("Draw!");
    else
        mb->setText(m_battle->getPlayer(winner)->getName() + " victory!");
    mb->show();
}

void MainWindow::updateStatusBar()
{
    if (m_battle->isBattleRunning())
    {
        QString currentPlayerName = m_battle->getPlayer(m_battle->currentPlayerColor())->getName();
        statusBar()->showMessage("Please " + currentPlayerName + " on the move", 0);
    }
    else
    {

        statusBar()->showMessage("Start a new game", 0);
    }
}
