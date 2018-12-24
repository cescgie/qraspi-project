#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/gameplay.h"
#include "core/battle.h"
#include "core/players/virtualplayer.h"
#include "ui/checkerboard/checkerboardwidget.h"
#include "ui/newgamedialog.h"

#include <QMainWindow>

/// \brief The main form.
///
/// The main form of the program, initializes and places the user interface controls.
///
/// The main form is a bridge that connects other components.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// \brief Start a new game interactively.
    ///
    /// This function will pop up a dialog that lets the user select the game settings to start a new game.
    void startNewGame();
    /// \brief End the current game interactively.
    ///
    /// This function will pop up a dialog asking the user whether to end the game.
    void stopGame();
    /// \brief The winner information is displayed after the game is over.
    ///
    /// Update the status bar. This function pops up a dialog box and displays the winner, which contains some necessary information, such as the winner's nickname.
    void showWinnerInfo(GamePlay::PlayerColor winner);
    /// \brief Update the status bar.
    void updateStatusBar();

private:
    // Game
    Battle *m_battle;
    // Checkboard
    CheckerBoardWidget *m_checkerBoardWidget;
    // Menu bar component
    QMenu *m_gameMenu;
    QAction *m_startGame;
    QAction *m_stopGame;
    QAction *m_exitGame;

    NewGameDialog* m_newGameDialog;

    void initMenuBar();
    void initSignalsAndSlots();
};

#endif // MAINWINDOW_H
